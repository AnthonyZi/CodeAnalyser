#include <png.h>
#include <iostream>
#include <stdint.h>
#include <stdlib.h>
#include <cmath>

//datamatrix, width, height, lref, aref, bref
int* get_significance_matrix(float*, uint32_t, uint32_t, float, float, float);

//datamatrix, widht, height --> datamatrix in Lab
float* matrix_rgb_to_lab(png_bytep, uint32_t, uint32_t);

//lab-array, rdat, gdat, bdat
void rgb_to_lab(float lab[3], png_byte, png_byte, png_byte);
