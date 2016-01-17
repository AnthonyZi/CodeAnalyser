#ifndef CircleSegment_H
#define CircleSegment_H

#include <cmath>
#include <stdlib.h>
#include <iostream> //penis

class CircleSegment
{

private:
        bool* segmentData;
        int diameter;
        int dotwidth;
        bool* dotkernel;
        int dotkernelsum;

        void setDiameter(int pdiameter);
        static void invertCircleshape(bool* matrix, int matrixwidth, int diameter);

public:
        CircleSegment(bool* pdata, int pdiameter);

        void setData(bool* pdata, int pdiameter);

        static bool* getCircleMatrix(int pdiameter);
        static int count_ones(bool *pmat, int pdiameter);
};

#endif
