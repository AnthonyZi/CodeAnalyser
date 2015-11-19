#ifndef CircleSegment_H
#define CircleSegment_H

#include <cmath>
#include <stdlib.h>
#include <iostream> //penis

class CircleSegment
{

private:
        int* segmentData;
        int* ringMatrix;
        int* dotArea;
        int diameter

public:
        static int* getCircleMatrix(int diameter);

        void setData(int* data, int diameter);

private:
        static void invertCircleshape(int* matrix, int matrixwidth, int diameter);
};

#endif
