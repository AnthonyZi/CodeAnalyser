#include <iostream>
#include <stdlib.h>
#include <ctime>
#include "readpng.h"
#include "matrixprocessing.h"
#include "circlesegment.h"
#include "searcher.h"

void printarr(bool* arr,unsigned int width,unsigned int height)
{
        for(unsigned int i = 0; i<height; i++)
        {
                for(unsigned int j = 0; j<width; j++)
                {
                        std::cout << (*(arr+i*width+j) ? "0" : "/" );
                }
                std::cout << std::endl;
        }
        std::cout << "----" << std::endl;
}

void printarr(int* arr,unsigned int width,unsigned int height)
{
        for(unsigned int i = 0; i<height; i++)
        {
                for(unsigned int j = 0; j<width; j++)
                {
                        std::cout << (*(arr+i*width+j) ? "0" : "/" );
                }
                std::cout << std::endl;
        }
        std::cout << "----" << std::endl;
}

void printarrhex(png_bytep arr, unsigned int width, unsigned int height)
{
        for(png_uint_32 i = 0; i<height/100; i++)
        {
                for(png_uint_32 j = 0; j<width/33; j++)
                {
                        int tmp = *(arr+i*width*3+j);
                        std::cout << std::hex  << tmp << " ";
                }
                std::cout << std::dec << std::endl;
        }
        std::cout << "----" << std::endl;
}

void printarrhexlim(png_bytep arr, unsigned int width, unsigned int height)
{
        for(png_uint_32 i = 0; i < 30; i++)
        {
                for(png_uint_32 j = 0; j < 90; j++)
                {
                        int tmp = *(arr+i*width*3+j);
                        std::cout << std::hex << tmp << " ";
                }
                std::cout << std::dec << std::endl;
        }
        std::cout << "----" << std::endl;
}

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
        
        //pointer for matrices (picturedata in different formats)
        png_bytep pixeldata;
        int* significance_mat;
        float* lab_mat;
        bool* matrixmask;

        //reference variables (conversion from rgb to lab for better comparison)
        float labref[3];
        //values to be searched for!
        int red = 20;
        int green = 0x1c;
        int blue = 0x1b;
        int labthreshold = 300; //"*10" compared to the standard compared values for lab


        //read png
        at = std::time(NULL);
        std::cout << "read png: ";
        if(readpng_init(fp, &png_ptr, &info_ptr))
                return 4;

        pixeldata = readpng_get_image_white_alpha(&png_ptr, &info_ptr, NULL);

        height = png_get_image_height(png_ptr, info_ptr);
        width = png_get_image_width(png_ptr, info_ptr);
//        numrowbytes = png_get_rowbytes(png_ptr, info_ptr);

        fclose(fp);
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        bt = std::time(NULL);
        std::cout << bt-at << std::endl;
        //read end

        if(pixeldata == NULL)
                return 5;

        printarrhexlim(pixeldata, width, height);

        at = std::time(NULL);
        //DOWNSCALE image if either width or height is greater than 1024
        while(width > 780 || height > 780)
        {
                quickdownscale(pixeldata, &width, &height);
                printarrhexlim(pixeldata, width, height);
        }
        bt = std::time(NULL);
        std::cout << "(" << width << "," << height << ") rescale: ";
        std::cout << bt-at << " - new width/height: " << width << "/" << height << std::endl;

//        printarrhex(pixeldata, width, height);

        //CONVERT rgb-matrix to lab-matrix
        std::cout << "conversion: ";
        at = std::time(NULL);
        lab_mat = matrix_rgb_to_lab(pixeldata, width, height);
        bt = std::time(NULL);
        std::cout << bt-at << std::endl;
        //directly delete unused references
        free(pixeldata);
        //END CONVERT

        //prepare search in lab
        rgb_to_lab(labref, red, green, blue);
        std::cout << "searching for: " << red << " " << green << " " << blue << "(rgb)";
        std::cout << " -> " << labref[0] << " " << labref[1] << " " << labref[2] << "(lab)" << std::endl;

        //printarr(lab_mat, width, height);

        //BUILD SIGNIFICANCEMATRIX
        std::cout << "building up significance-matrix" << std::endl;
        at = std::time(NULL);
        significance_mat = get_significance_matrix(lab_mat, width, height, labref[0], labref[1], labref[2]);
        //directly erase reference to lab_mat
        free(lab_mat);
        //END BUILD SIGNIFICANCEMATRIX
        std::cout << "build significance-mat: ";
        bt = std::time(NULL);
        std::cout << bt-at << std::endl;

        //printarr(significance_mat, width, height);

        //BUILD MATRIXMASK
        std::cout << "checking significance for values under threshold-value: "<< labthreshold << std::endl;

        at = std::time(NULL);
        matrixmask = get_bitmatrix(significance_mat, width, height, labthreshold);
        bt = std::time(NULL);
        std::cout << "obtain bit-matrix: " << bt-at << std::endl;

        printarr(matrixmask, width, height);
        std::cout << std::endl;
        at = std::time(NULL);
        std::cout << "processing(erase small structures): ";
        bool* tmpmatrixmask = (bool*)malloc(sizeof(bool)*width*height);
        for(uint32_t i = 0; i < width*height; i++)
                *(tmpmatrixmask+i) = *(matrixmask+i);
        int filterclass = (int)log2((width < height ? width : height)/100);
        for(int i = 0; i < filterclass; i++)
                tmpmatrixmask = filter_median_square(tmpmatrixmask, width, height, 1, 0, 1, 2);
        tmpmatrixmask = filter_median_square(tmpmatrixmask, width, height, filterclass, 1, 1, 1);
        for(uint32_t i = 0; i < width*height; i++)
                *(matrixmask+i) = (*(matrixmask+i)) & (*(tmpmatrixmask+i)); 

        bt = std::time(NULL);
        std::cout << bt-at << std::endl;
        printarr(matrixmask, width, height);

        //free pointers used in programm
        free(significance_mat);

        int* circlemat;

        int dia = 11;
        circlemat = CircleSegment::getCircleMatrix(dia);

        std::cout << "test for circlematrix" << std::endl;

        printarr(circlemat, dia, dia);
        
        std::cout << "convolution:" << std::endl;

        Searcher* s = new Searcher(matrixmask, width, height);

        s->setDia(70);
//        s->searchSegments();

        return 0;
}
