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
        png_uint_32 numrowbytes;

        png_bytep pixeldata;
        int* significance_mat;
        //end

        //read png
        if(readpng_init(fp, &png_ptr, &info_ptr))
                return 4;
        std::cout << "Initialisation successfull" << std::endl;

        pixeldata = readpng_get_image(&png_ptr, &info_ptr, NULL);

        height = png_get_image_height(png_ptr, info_ptr);
        width = png_get_image_width(png_ptr, info_ptr);
        numrowbytes = png_get_rowbytes(png_ptr, info_ptr);

        fclose(fp);
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        //read end

        if(pixeldata == NULL)
                return 5;

        significance_mat = get_significance_matrix(pixeldata, width, height, 0xFF, 0xFF, 0xFF);

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
