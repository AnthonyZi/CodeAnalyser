#include "readpng.h"

void print_png_version_info()
{
        std::cout << "Compiled with libpng " << PNG_LIBPNG_VER_STRING << " using " << png_libpng_ver << std::endl;
        std::cout << "Compiled with zlib " << ZLIB_VERSION << " using " << zlib_version << std::endl;
}

int check_png_version()
{
        std::string libver = PNG_LIBPNG_VER_STRING;
        std::string zlibver = ZLIB_VERSION;
        if(libver.compare(png_libpng_ver) != 0 || zlibver.compare(zlib_version) != 0)
        {
                std::cerr << "please update your librabries" << std::endl;
                print_png_version_info();
                return VERSIONERR;
        }
        return 0;
}

int readpng_init(FILE* fp, png_structp* png_ptr, png_infop* info_ptr)
{
        png_bytep sigp = (png_bytep)malloc(sizeof(png_byte)*8);
        if(fread(sigp, 1, 8, fp) != 8)
        {
                std::cerr << "couldn't read fileheader" << std::endl;
                return 1;
        }
        if(png_sig_cmp(sigp, 0, 8))
        {
                std::cerr << "file could not be identified as .png" << std::endl;
                return 1;
        }
        *png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
        if(!*png_ptr)
        {
                std::cerr << "couldn't initialize data-structs" << std::endl;
                return 1;
        }

        *info_ptr = png_create_info_struct(*png_ptr);
        if(!*info_ptr)
        {
                png_destroy_read_struct(png_ptr, info_ptr, NULL);
                std::cerr << "couldn't initialize data-structs" << std::endl;
                return 1;
        }

        if(setjmp(png_jmpbuf(*png_ptr)))
        {
                png_destroy_read_struct(png_ptr, info_ptr, NULL);
                std::cerr << "error during setjmp" << std::endl;
                return 1;
        }

        png_init_io(*png_ptr, fp);
        png_set_sig_bytes(*png_ptr, 8);
        png_read_info(*png_ptr, *info_ptr);

        return 0;
}

png_bytep readpng_get_image(png_structp* png_ptr, png_infop* info_ptr, png_infop* end_ptr)
{
        //test for
        if(setjmp(png_jmpbuf(*png_ptr)))
        {
                png_destroy_read_struct(png_ptr, info_ptr, NULL);
                std::cerr << "error during setjmp" << std::endl;
                return NULL;
        }

        png_uint_32 width, height;
        int bit_depth, color_type;
        png_uint_32 numrowbytes;
        png_bytep dataBlock;

        // gamma correction start (optional)
        double display_exponent = 2.2; //standard in most systems + standard in imageprocessing
        int envGamma = 0;
        if(envGamma)
                display_exponent = (double)envGamma;


        double gamma;

        if(png_get_gAMA(*png_ptr, *info_ptr, &gamma))
                png_set_gamma(*png_ptr, display_exponent, gamma);

        // gamma correction end
       
       
        png_get_IHDR(*png_ptr, *info_ptr, &width, &height, &bit_depth, &color_type, NULL, NULL, NULL);


        //transform the png to a standard format
        if(color_type == PNG_COLOR_TYPE_PALETTE)
                png_set_expand(*png_ptr);
        if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
                png_set_expand(*png_ptr);
        if(png_get_valid(*png_ptr, *info_ptr, PNG_INFO_tRNS))
                png_set_expand(*png_ptr);
        if(bit_depth == 16)
                png_set_strip_16(*png_ptr);
        if(color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
                png_set_gray_to_rgb(*png_ptr);

        png_read_update_info(*png_ptr, *info_ptr);
        //end

        //proccessing for the dataBlock (pixeldata)
        numrowbytes = png_get_rowbytes(*png_ptr, *info_ptr);
        png_bytep row_pointers[height];

        dataBlock = (png_bytep)malloc(sizeof(png_byte)*numrowbytes*height);
        for(png_uint_32 i = 0; i<height; i++)
                row_pointers[i] = dataBlock + i*numrowbytes;


        png_read_image(*png_ptr, row_pointers);
        //end

        //optional reading of end in end_ptr and test for consistence
        png_read_end(*png_ptr, NULL);
        
        return dataBlock;
}


png_bytep readpng_get_image_white_alpha(png_structp* png_ptr, png_infop* info_ptr, png_infop* end_ptr)
{
        //test for
        if(setjmp(png_jmpbuf(*png_ptr)))
        {
                png_destroy_read_struct(png_ptr, info_ptr, NULL);
                std::cerr << "error during setjmp" << std::endl;
                return NULL;
        }

        png_uint_32 width, height;
        int bit_depth, color_type;
        png_uint_32 numrowbytes;
        png_bytep dataBlock;
        bool expanded_alpha_channel = false;

        // gamma correction start (optional)
        double display_exponent = 2.2; //standard in most systems + standard in imageprocessing
        int envGamma = 0;
        if(envGamma)
                display_exponent = (double)envGamma;


        double gamma;

        if(png_get_gAMA(*png_ptr, *info_ptr, &gamma))
                png_set_gamma(*png_ptr, display_exponent, gamma);

        // gamma correction end
       
       
        png_get_IHDR(*png_ptr, *info_ptr, &width, &height, &bit_depth, &color_type, NULL, NULL, NULL);


        //transform the png to a standard format
        if(color_type == PNG_COLOR_TYPE_PALETTE)
        {
                png_set_expand(*png_ptr);
                expanded_alpha_channel = true;
        }
        if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
        {
                png_set_expand(*png_ptr);
                expanded_alpha_channel = true;
        }
        if(png_get_valid(*png_ptr, *info_ptr, PNG_INFO_tRNS))
        {
                png_set_expand(*png_ptr);
                expanded_alpha_channel = true;
        }
        if(bit_depth == 16)
                png_set_strip_16(*png_ptr);
        if(color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
                png_set_gray_to_rgb(*png_ptr);

        png_read_update_info(*png_ptr, *info_ptr);
        //end

        //proccessing for the dataBlock (pixeldata)
        numrowbytes = png_get_rowbytes(*png_ptr, *info_ptr);
        png_bytep row_pointers[height];

        dataBlock = (png_bytep)malloc(sizeof(png_bytep)*numrowbytes*height);
        for(png_uint_32 i = 0; i<height; i++)
                row_pointers[i] = dataBlock + i*numrowbytes;


        png_read_image(*png_ptr, row_pointers);

        if(color_type & PNG_COLOR_MASK_ALPHA || expanded_alpha_channel)
        {
                std::cout << "removing alpha" << std::endl;
                png_bytep dataBlock_tmp = (png_bytep)malloc(sizeof(png_bytep)*width*height*3);
                dataBlock_tmp = delete_alpha_white(png_ptr, info_ptr, dataBlock);
                free(dataBlock);
                dataBlock = dataBlock_tmp;
        }
        //end

        //optional reading of end in end_ptr and test for consistence
        png_read_end(*png_ptr, NULL);
        
        return dataBlock;
}

png_bytep delete_alpha(png_structp* png_ptr, png_infop* info_ptr, png_bytep pixeldata)
{
        png_bytep dataBlock;
        png_uint_32 height, width;

        height = png_get_image_height(*png_ptr, *info_ptr);
        width = png_get_image_width(*png_ptr, *info_ptr);

        dataBlock = (png_bytep)malloc(sizeof(png_bytep)*width*height*3);

        for(png_uint_32 i = 0; i<height; i++)
        {
                for(png_uint_32 j = 0; j<width; j++)
                {
                        *(dataBlock + i*width*3 + j*3) = *(pixeldata + i*width*4 + j*4);
                        *(dataBlock + i*width*3 + j*3 + 1) = *(pixeldata + i*width*4 + j*4 + 1);
                        *(dataBlock + i*width*3 + j*3 + 2) = *(pixeldata + i*width*4 + j*4 + 2);
                }
        }

        return dataBlock;
}

png_bytep delete_alpha_white(png_structp* png_ptr, png_infop* info_ptr, png_bytep pixeldata)
{
        png_bytep dataBlock;
        png_uint_32 height, width;

        height = png_get_image_height(*png_ptr, *info_ptr);
        width = png_get_image_width(*png_ptr, *info_ptr);

        dataBlock = (png_bytep)malloc(sizeof(png_bytep)*width*height*3);

        for(png_uint_32 i = 0; i<height; i++)
        {
                for(png_uint_32 j = 0; j<width; j++)
                {
                        *(dataBlock + i*width*3 + j*3) = 0xff - (0xff - *(pixeldata + i*width*4 + j*4))*(*(pixeldata + i*width*4 + j*4 + 3))/0xff;
                        *(dataBlock + i*width*3 + j*3 + 1) = 0xff - (0xff - *(pixeldata + i*width*4 + j*4 + 1))*(*(pixeldata + i*width*4 + j*4 + 3))/0xff;
                        *(dataBlock + i*width*3 + j*3 + 2) = 0xff - (0xff - *(pixeldata + i*width*4 + j*4 + 2))*(*(pixeldata + i*width*4 + j*4 + 3))/0xff;

                }
        }

        return dataBlock;
}
