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
