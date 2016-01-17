#ifndef WRITEPNG_H
#define WRITEPNG_H

#include <png.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/* Write "bitmap" to a PNG file specified by "path"; returns 0 on
   success, non-zero on error. */

int save_png(png_bytep pixeldata, png_uint_32 width, png_uint_32 height, const char *path)
{
        FILE * fp;
        png_structp png_ptr = NULL;
        png_infop info_ptr = NULL;
        png_byte** row_pointers = NULL;
        /* "status" contains the return value of this function. At first
        it is set to a value which means 'failure'. When the routine
        has finished its work, it is set to a value which means
        'success'.*/
        int status = -1;
        /* The following number is set by trial and error only. I cannot
        see where it it is documented in the libpng manual.
        */
        int depth = 8;
    
        fp = fopen (path, "wb");
        if (! fp) {
                return -1;
        }

        png_ptr = png_create_write_struct (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
        if (png_ptr == NULL) {
                return -1;
        }
    
        info_ptr = png_create_info_struct (png_ptr);
        if (info_ptr == NULL) {
                return -1;
        }
        
        /* Set up error handling. */
        if (setjmp (png_jmpbuf (png_ptr))) {
                return -1;
        }
    
        /* Set image attributes. */

        png_set_IHDR (png_ptr,
                info_ptr,
                width,
                height,
                depth,
                PNG_COLOR_TYPE_RGB,
                PNG_INTERLACE_NONE,
                PNG_COMPRESSION_TYPE_DEFAULT,
                PNG_FILTER_TYPE_DEFAULT);
    
        /* Initialize rows of PNG. */

        row_pointers = (png_byte**)png_malloc(png_ptr, height*sizeof(png_bytep));

        for (png_uint_32 y = 0; y < height; ++y)
        {
                row_pointers[y] = pixeldata+y*width*3;
        }

        /* Write the image data to "fp". */

        png_init_io (png_ptr, fp);
        png_set_rows (png_ptr, info_ptr, row_pointers);
        png_write_png (png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);

        /* The routine has successfully written the file, so we set
        "status" to a value which indicates success. */

        status = 0;
    
        for (png_uint_32 y = 0; y < height; y++) {
//                png_free (png_ptr, row_pointers[y]);
        }
//        png_free (png_ptr, row_pointers);
    
        png_destroy_write_struct (&png_ptr, &info_ptr);
        fclose (fp);
        return status;
}

int save_png(bool* pixeldata, png_uint_32 width, png_uint_32 height, const char *path)
{
        FILE * fp;
        png_structp png_ptr = NULL;
        png_infop info_ptr = NULL;
        png_byte** row_pointers = NULL;
        /* "status" contains the return value of this function. At first
        it is set to a value which means 'failure'. When the routine
        has finished its work, it is set to a value which means
        'success'. */ int status = -1;
        /* The following number is set by trial and error only. I cannot
        see where it it is documented in the libpng manual.
        */
        int depth = 8;
    
        fp = fopen (path, "wb");
        if (! fp) {
                return -1;
        }

        png_ptr = png_create_write_struct (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
        if (png_ptr == NULL) {
                return -1;
        }
    
        info_ptr = png_create_info_struct (png_ptr);
        if (info_ptr == NULL) {
                return -1;
        }
        
        /* Set up error handling. */
        if (setjmp (png_jmpbuf (png_ptr))) {
                return -1;
        }
    
        /* Set image attributes. */

        png_set_IHDR (png_ptr,
                info_ptr,
                width,
                height,
                depth,
                PNG_COLOR_TYPE_RGB,
                PNG_INTERLACE_NONE,
                PNG_COMPRESSION_TYPE_DEFAULT,
                PNG_FILTER_TYPE_DEFAULT);
    
        /* Initialize rows of PNG. */

        row_pointers = (png_byte**)malloc(sizeof(png_bytep)*height);

        png_bytep tmpdata = (png_bytep)malloc(sizeof(png_bytep)*width*3*height);

        for(png_uint_32 h = 0; h < height; h++)
        {
                for(png_uint_32 w = 0; w < width; w++)
                {
                        *(tmpdata+h*width*3+w*3) = *(pixeldata+h*width+w) ? 0 : 0xfe;
                        *(tmpdata+h*width*3+w*3+1) = *(pixeldata+h*width+w) ? 0 : 0xfe;
                        *(tmpdata+h*width*3+w*3+2) = *(pixeldata+h*width+w) ? 0 : 0xfe;
                }
        }
        
        for (png_uint_32 y = 0; y < height; ++y)
        {
                row_pointers[y] = tmpdata+y*width*3;
        }

        /* Write the image data to "fp". */

        png_init_io (png_ptr, fp);
        png_set_rows (png_ptr, info_ptr, row_pointers);
        png_write_png (png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);

        /* The routine has successfully written the file, so we set
        "status" to a value which indicates success. */

        status = 0;
    
        for (png_uint_32 y = 0; y < height; y++) {
//                png_free (png_ptr, row_pointers[y]);
        }
//        png_free (png_ptr, row_pointers);
    
        png_destroy_write_struct (&png_ptr, &info_ptr);
        fclose (fp);
        return status;
}

#endif
