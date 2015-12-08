#include <iostream>
#include <stdlib.h>
#include <time.h>
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

        std::clock_t t1, t2; //beta

        //preparing class-pointers
        RGBImage* rgb;
        LABImage* lab;
        BITImage* bit;
        
        //pointer for matrices (picturedata in different formats)
        png_bytep pixeldata;


        //START READ
        t1 = std::clock(); //beta
        if(readpng_init(fp, &png_ptr, &info_ptr))
                return 4;

        pixeldata = readpng_get_image_white_alpha(&png_ptr, &info_ptr, NULL);

        height = png_get_image_height(png_ptr, info_ptr);
        width = png_get_image_width(png_ptr, info_ptr);

        fclose(fp);
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        t2 = std::clock(); //beta
        std::cout << "read png: "; //beta
        std::cout << 1000.0*(t2-t1) / CLOCKS_PER_SEC << " ms" << std::endl; //beta
        //END READ

        if(pixeldata == NULL)
                return 5;

        t1 = std::clock(); //beta
        save_png(pixeldata, width, height, "debugpng/copy.png"); //beta
        t2 = std::clock(); //beta
        std::cout << "saving copy: "; //beta
        std::cout << 1000.0*(t2-t1) / CLOCKS_PER_SEC << " ms" << std::endl; //beta

        //START IMAGEPROCESSING
        rgb = new RGBImage(pixeldata, width, height);
        free(pixeldata);


        t1 = std::clock(); //beta
        rgb->quickdownscale(2000);
        t2 = std::clock(); //beta
        std::cout << "downscaling: "; //beta
        std::cout << 1000.0*(t2-t1) / CLOCKS_PER_SEC << " ms" << std::endl; //beta


        save_png(rgb->getPixels(), rgb->getWidth(), rgb->getHeight(), "debugpng/after_scaling.png");


        t1 = std::clock(); //beta
        lab = new LABImage(rgb);
        t2 = std::clock(); //beta
        std::cout << "conversion: "; //beta
        std::cout << 1000.0*(t2-t1) / CLOCKS_PER_SEC << " ms" << std::endl; //beta


        t1 = std::clock(); //beta
        bit = new BITImage(lab);
        t2 = std::clock(); //beta

        unsigned char* rgbref = (unsigned char*)malloc(sizeof(unsigned char)*3);
        rgbref = bit->getREF();
        float* labref = (float*)malloc(sizeof(float)*3);
        labref = lab->getLAB(*(rgbref), *(rgbref+1), *(rgbref+2));
        std::cout << "calculation of bit-matrix: "; //beta
        std::cout << (int)*(rgbref) << " " << (int)*(rgbref+1) << " " << (int)*(rgbref+2) << " (rgb); " << std::dec << *(labref) << " " << *(labref+1) << " " << *(labref+2) << " (lab): "; //beta
        std::cout << 1000.0*(t2-t1) / CLOCKS_PER_SEC << " ms" << std::endl; //beta


        save_png(bit->getPixels(), bit->getWidth(), bit->getHeight(), "debugpng/binary_1.png");


        t1 = std::clock(); //beta
        bool* tmpmatrixmask = (bool*)malloc(sizeof(bool)*bit->getWidth()*bit->getHeight());
        for(uint32_t i = 0; i < (uint32_t)bit->getWidth()*bit->getHeight(); i++)
                *(tmpmatrixmask+i) = *(bit->getPixels()+i);
        int filterclass = (int)log2((bit->getWidth() < bit->getHeight() ? bit->getWidth() : bit->getHeight())/100);
        for(int i = 0; i < filterclass; i++)
                tmpmatrixmask = filter_median_square(tmpmatrixmask, bit->getWidth(), bit->getHeight(), 1, 0, 1, 2);
        tmpmatrixmask = filter_median_square(tmpmatrixmask, bit->getWidth(), bit->getHeight(), filterclass, 1, 1, 1);
        for(uint32_t i = 0; i < (uint32_t)bit->getWidth()*bit->getHeight(); i++)
                *(bit->getPixels()+i) = (*(bit->getPixels()+i)) & (*(tmpmatrixmask+i)); 
        t2 = std::clock(); //beta
        std::cout << "processing(removal of small structures): "; //beta
        std::cout << 1000.0*(t2-t1) / CLOCKS_PER_SEC << " ms" << std::endl; //beta
        //END IMAGEPROCESSING


        save_png(bit->getPixels(), bit->getWidth(), bit->getHeight(), "debugpng/binary_2.png");

/*
        int* circlemat;

        int dia = 11;
        circlemat = CircleSegment::getCircleMatrix(dia);

        std::cout << "test for circlematrix" << std::endl; //beta

        
        std::cout << "convolution:" << std::endl; //beta

        Searcher* s = new Searcher(bit->getPixels(), bit->getWidth(), bit->getHeight());

        s->setDia(70);
//        s->searchSegments();
*/

        return 0;
}
