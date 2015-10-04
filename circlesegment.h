#ifndef CircleSegment_H
#define CircleSegment_H

#include <cmath>

class CircleSegment
{

private:
        int* segmentData;
        int* ringMatrix;
        int* dotArea;

public:
        static int* getCircleMatrix(int diameter);

private:
        void invertCircleshape(int* matrix, int matrixwidth, int diameter);
}

#endif
