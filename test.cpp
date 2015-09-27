#include <iostream>
#include <stdlib.h>
#include "readpng.h"
#include "format.h"

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

        png_bytep pixeldata;
        int* significance_mat;
        float* lab_mat;
        //end

        //read png
        if(readpng_init(fp, &png_ptr, &info_ptr))
                return 4;

        pixeldata = readpng_get_image(&png_ptr, &info_ptr, NULL);

        height = png_get_image_height(png_ptr, info_ptr);
        width = png_get_image_width(png_ptr, info_ptr);
//        numrowbytes = png_get_rowbytes(png_ptr, info_ptr);

        fclose(fp);
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        //read end

        if(pixeldata == NULL)
                return 5;

        for(png_uint_32 i = 0; i<height; i++)
        {
                for(png_uint_32 j = 0; j<width*3; j++)
                {
                        int tmp = *(pixeldata+i*width*3+j);
                        std::cout << tmp << " ";
                }
                std::cout << std::endl;
        }

        float labref[3];
        rgb_to_lab(labref, 0xff, 0xff, 0xff);
        std::cout << "searching for: 0xff, 0xff, 0xff --> " << labref[0] << " " << labref[1] << " " << labref[2] << std::endl;

        lab_mat = matrix_rgb_to_lab(pixeldata, width, height);

        for(png_uint_32 i = 0; i<height; i++)
        {
                for(png_uint_32 j = 0; j<width*3; j++)
                {
                        float tmp = *(lab_mat+i*width*3+j);
                        std::cout << tmp << " ";
                }
                std::cout << std::endl;
        }

        std::cout << "significance" << std::endl;
        significance_mat = get_significance_matrix(lab_mat, width, height, labref[0], labref[1], labref[2]);

        for(png_uint_32 i = 0; i<height; i++)
        {
                for(png_uint_32 j = 0; j<width; j++)
                {
                        int tmp = *(significance_mat+i*width+j);
                        std::cout << tmp << "\t";
                }
                std::cout << std::endl;
        }

        //free pointers used in programm
        free(pixeldata);

        return 0;
}
