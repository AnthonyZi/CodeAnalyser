#include <png.h>
#include <iostream>
#include <stdint.h>
#include <stdlib.h>
#include <cmath>

/* result means:
 * 0 - perfect matching
 * 10 - recognizable of a professional
 * 25 - recognizable of a normal person
 * 60-70 - tolerable difference in media
 * >100 - clearly recognizable difference
 */
//datamatrix, width, height, lref, aref, bref
int* get_significance_matrix(float*, uint32_t, uint32_t, float, float, float);

//datamatrix, widht, height --> datamatrix in Lab
float* matrix_rgb_to_lab(png_bytep, uint32_t, uint32_t);

//lab-array, rdat, gdat, bdat
void rgb_to_lab(float lab[3], png_byte, png_byte, png_byte);

//bitmatrix, width, height
int* get_valuable_chunks(bool*, uint32_t, uint32_t);

//significance_matrix, width, height, threshold
bool* get_bitmatrix(int*, uint32_t, uint32_t, int);

//datamatrix(pixeldata), address of width-var, address of height-var, maxlength(width or height)
void quickdownscale(png_bytep, png_uint_32*, png_uint_32*);

//bitmatrix, width, height, kernelradius, extend ones or zeros,[search criteria:] more or less of (ones/zeros), threshold for extension
bool* filter_median_square(bool*, uint32_t, uint32_t, int, bool, bool, int);

//bitmatrix, width, height, kernelradius, ones, xoff, yoff
int count_bits_in_square(bool*, uint32_t, uint32_t, int, bool, int, int);

//bitmatrix, width, height
int* get_valuable_chunks(bool*, uint32_t, uint32_t);
