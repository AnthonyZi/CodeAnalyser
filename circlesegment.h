#ifndef CircleSegment_H
#define CircleSegment_H

#include <cmath>
#include <stdlib.h>

class CircleSegment
{

private:
        int* segmentData;
        int* ringMatrix;
        int* dotArea;

public:
        static int* getCircleMatrix(int diameter);

private:
        static void invertCircleshape(int* matrix, int matrixwidth, int diameter);
};

#endif