#include <png.h>
#include <iostream>
#include <stdint.h>
#include <stdlib.h>

#define SQR(a) (a*a)

//datamatrix, width, height, rref, gref, bref
int* get_significance_matrix(png_bytep, uint32_t, uint32_t, int, int, int);
