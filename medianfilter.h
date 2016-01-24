#ifndef MEDIANFILTER_H
#define MEDIANFILTER_H

#include "bitimage.h"
#include "shape.h"

float bits_in_shape(BITImage *sourceimage, Shape *kernel, bool ones, int xoff, int yoff);

void filter_median(BITImage *sourceimage, Shape *kernel, bool ones, bool more, float threshold);

#endif
