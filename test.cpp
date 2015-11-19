#include <iostream>
#include <stdlib.h>
#include "readpng.h"
#include "format.h"
#include "circlesegment.h"

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
        
        //pointer for matrices (picturedata in different formats)
        png_bytep pixeldata;
        int* significance_mat;
        float* lab_mat;
        bool* matrixmask;

        //reference variables (conversion from rgb to lab for better comparison)
        float labref[3];
        //values to be searched for!
        int red = 0;
        int green = 0x71;
        int blue = 0xb9;
        int labthreshold = 300; //"*10" compared to the standard compared values for lab


        //read png
        std::cout << "read png" << std::endl;
        if(readpng_init(fp, &png_ptr, &info_ptr))
                return 4;

        pixeldata = readpng_get_image_white_alpha(&png_ptr, &info_ptr, NULL);

        height = png_get_image_height(png_ptr, info_ptr);
        width = png_get_image_width(png_ptr, info_ptr);
//        numrowbytes = png_get_rowbytes(png_ptr, info_ptr);

        fclose(fp);
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        //read end

        if(pixeldata == NULL)
                return 5;

        /*
        for(png_uint_32 i = 0; i<height; i++)
        {
                for(png_uint_32 j = 0; j<width*3; j++)
                {
                        int tmp = *(pixeldata+i*width*3+j);
                        std::cout << std::hex  << tmp << " ";
                }
                std::cout << std::dec << std::endl;
        }
        */

        //CONVERT rgb-matrix to lab-matrix
        lab_mat = matrix_rgb_to_lab(pixeldata, width, height);
        //directly delete unused references
        free(pixeldata);
        //END CONVERT

        //prepare search in lab
        rgb_to_lab(labref, red, green, blue);
        std::cout << "searching for: " << red << " " << green << " " << blue << "(rgb)";
        std::cout << " -> " << labref[0] << " " << labref[1] << " " << labref[2] << "(lab)" << std::endl;

        /*
        for(png_uint_32 i = 0; i<height; i++)
        {
                for(png_uint_32 j = 0; j<width*3; j++)
                {
                        float tmp = *(lab_mat+i*width*3+j);
                        std::cout << tmp << " ";
                }
                std::cout << std::endl;
        }
        */

        //BUILD SIGNIFICANCEMATRIX
        std::cout << "building up significance-matrix" << std::endl;
        significance_mat = get_significance_matrix(lab_mat, width, height, labref[0], labref[1], labref[2]);
        //directly erase reference to lab_mat
        free(lab_mat);
        //END BUILD SIGNIFICANCEMATRIX

        /*
        for(png_uint_32 i = 0; i<height; i++)
        {
                for(png_uint_32 j = 0; j<width; j++)
                {
                        int tmp = *(significance_mat+i*width+j);
                        std::cout << tmp << "\t";
                }
                std::cout << std::endl;
        }
        */

        //BUILD MATRIXMASK
        std::cout << "checking significance for values under threshold-value: "<< labthreshold << std::endl;

        matrixmask = (bool*)malloc(sizeof(bool)*width*height);
        for(png_uint_32 i = 0; i<height; i++)
        {
                for(png_uint_32 j = 0; j<width; j++)
                {
                        int tmp = *(significance_mat+i*width+j);
                        *(matrixmask+i*width+j) = tmp>labthreshold ? false : true;
                        std::cout << *(matrixmask+i*width+j) << " ";
                }
                std::cout << std::endl;
        }


        //free pointers used in programm
        free(significance_mat);

        int* circlemat;

        int dia = 60;
        circlemat = CircleSegment::getCircleMatrix(dia);

        std::cout << "test for circlematrix" << std::endl;

        for(int i = 0; i< dia; i++)
        {
                for(int j = 0; j<dia; j++)
                {
                        int tmp = *(circlemat + i*dia + j);
                        std::cout << tmp << " ";
                }
                std::cout << std::endl;
        }

        return 0;
}
