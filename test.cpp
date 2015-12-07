#include <iostream>
#include <stdlib.h>
#include <ctime>
#include "readpng.h"
#include "matrixprocessing.h"
#include "circlesegment.h"
#include "searcher.h"
#include "writepng.h"

#include "rgbimage.h"
#include "labimage.h"
#include "bitimage.h"

int main(int argc, char* argv[])
{
        if(argc != 2)
                return 1;
        if(check_png_version())
                return 2;
        
        //load file and load variables to read png
        FILE* fp = fopen(argv[1], "rb");
        if(!fp)
        {
                std::cerr << "couldn't open " << argv[1] << std::endl;
                return 3;
        }
        png_structp png_ptr = NULL;
        png_infop info_ptr = NULL;
        png_uint_32 height;
        png_uint_32 width;
//        png_uint_32 numrowbytes;

        std::time_t at, bt;
//preparing structures
        RGBImage* rgb;
        LABImage* lab;
        BITImage* bit;
        
        //pointer for matrices (picturedata in different formats)
        png_bytep pixeldata;
//        int* significance_mat;
//        float* lab_mat;
//        bool* matrixmask;

        //reference variables (conversion from rgb to lab for better comparison)
//        float labref[3];
        //values to be searched for!
 //       int red = 20;
 //       int green = 0x1c;
 //       int blue = 0x1b;
 //       int labthreshold = 300; //"*10" compared to the standard compared values for lab


        //read png
        at = std::time(NULL);
        if(readpng_init(fp, &png_ptr, &info_ptr))
                return 4;

        pixeldata = readpng_get_image_white_alpha(&png_ptr, &info_ptr, NULL);

        height = png_get_image_height(png_ptr, info_ptr);
        width = png_get_image_width(png_ptr, info_ptr);
//        numrowbytes = png_get_rowbytes(png_ptr, info_ptr);

        fclose(fp);
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        bt = std::time(NULL);
        std::cout << "read png: ";
        std::cout << bt << "-" << at << "=" << bt-at << std::endl;
        //read end

        if(pixeldata == NULL)
                return 5;

        save_png(pixeldata, width, height, "debugpng/copy.png");

        rgb = new RGBImage(pixeldata, width, height);
        free(pixeldata);

        //DOWNSCALE image if either width or height is greater than 1024
        at = std::time(NULL);
        rgb->quickdownscale(2000);
//        width = rgb->getWidth();
//        height = rgb->getHeight();
//        pixeldata = (png_bytep)realloc(pixeldata, sizeof(png_byte)*width*height*3);
//        pixeldata = rgb->getPixels();
        bt = std::time(NULL);
        std::cout << "downscaling: " << bt << "-" << at << "=" << bt-at << std::endl;

        save_png(rgb->getPixels(), rgb->getWidth(), rgb->getHeight(), "debugpng/after_scaling.png");

        //CONVERT rgb-matrix to lab-matrix
        at = std::time(NULL);

//        lab_mat = matrix_rgb_to_lab(pixeldata, width, height);
        lab = new LABImage(rgb);
//        lab_mat = lab->getPixels();
        bt = std::time(NULL);
        std::cout << "conversion: ";
        std::cout << bt << "-" << at << "=" << bt-at << std::endl;
        //directly delete unused references
        //END CONVERT

        //prepare search in lab
//        rgb_to_lab(labref, red, green, blue 

//        std::cout << "searching for: " << red << " " << green << " " << blue << "(rgb)"; std::cout << " -> " << labref[0] << " " << labref[1] << " " << labref[2] << "(lab)" << std::endl;

        //BUILD SIGNIFICANCEMATRIX
//        std::cout << "building up significance-matrix" << std::endl;
//        at = std::time(NULL);
//        significance_mat = get_significance_matrix(lab_mat, width, height, labref[0], labref[1], labref[2]);
        //directly erase reference to lab_mat
//        free(lab_mat);
        //END BUILD SIGNIFICANCEMATRIX
//        std::cout << "build significance-mat: ";
//        bt = std::time(NULL);
//        std::cout << bt << "-" << at << "=" << bt-at << std::endl;

        //BUILD MATRIXMASK
//        std::cout << "checking significance for values under threshold-value: "<< labthreshold << std::endl;

//        at = std::time(NULL);
//        matrixmask = get_bitmatrix(significance_mat, width, height, labthreshold);
//        bt = std::time(NULL);
//        std::cout << "obtain bit-matrix: " << bt << "-" << at << "=" << bt-at << std::endl;
        
        at = std::time(NULL);
        bit = new BITImage(lab);
        bt = std::time(NULL);
//        matrixmask = bit->getPixels();

        unsigned char* rgbref = (unsigned char*)malloc(sizeof(unsigned char)*3);
        rgbref = bit->getREF();
        float* labref = (float*)malloc(sizeof(float)*3);
        labref = lab->getLAB(*(rgbref), *(rgbref+1), *(rgbref+2));
        std::cout << "searching for: " << (int)*(rgbref) << " " << (int)*(rgbref+1) << " " << (int)*(rgbref+2) << " (rgb); " << std::dec << *(labref) << " " << *(labref+1) << " " << *(labref+2) << " (lab)" << std::endl;
        std::cout << "calculation of bit-matrix: ";
        std::cout << bt << "-" << at << "=" << bt-at << std::endl;


        save_png(bit->getPixels(), bit->getWidth(), bit->getHeight(), "debugpng/binary_1.png");


        bool* tmpmatrixmask = (bool*)malloc(sizeof(bool)*bit->getWidth()*bit->getHeight());
        for(uint32_t i = 0; i < (uint32_t)bit->getWidth()*bit->getHeight(); i++)
                *(tmpmatrixmask+i) = *(bit->getPixels()+i);
        int filterclass = (int)log2((bit->getWidth() < bit->getHeight() ? bit->getWidth() : bit->getHeight())/100);
        for(int i = 0; i < filterclass; i++)
                tmpmatrixmask = filter_median_square(tmpmatrixmask, bit->getWidth(), bit->getHeight(), 1, 0, 1, 2);
        tmpmatrixmask = filter_median_square(tmpmatrixmask, bit->getWidth(), bit->getHeight(), filterclass, 1, 1, 1);
        for(uint32_t i = 0; i < (uint32_t)bit->getWidth()*bit->getHeight(); i++)
                *(bit->getPixels()+i) = (*(bit->getPixels()+i)) & (*(tmpmatrixmask+i)); 

        bt = std::time(NULL);
        std::cout << "processing(erase small structures): ";
        std::cout << bt << "-" << at << "=" << bt-at << std::endl;
        save_png(bit->getPixels(), bit->getWidth(), bit->getHeight(), "debugpng/binary_2.png");

        //free pointers used in programm
//        free(significance_mat);

        int* circlemat;

        int dia = 11;
        circlemat = CircleSegment::getCircleMatrix(dia);

        std::cout << "test for circlematrix" << std::endl;

        
        std::cout << "convolution:" << std::endl;

        Searcher* s = new Searcher(bit->getPixels(), bit->getWidth(), bit->getHeight());

        s->setDia(70);
//        s->searchSegments();

        return 0;
}
