#ifndef Searcher_H
#define Searcher_H

#include <cmath>
#include <ctime> //penis
#include <vector>
#include "circlesegment.h"

class Searcher
{
private:
        bool* bitmatrix;
        int bitmatwidth, bitmatheight;
        int diameter;
        int dotwidth;
        int* circlekernel;
        int kernelsum;

        std::vector<CircleSegment> matchingSegments;

private:
        Searcher();
        int conv2d_and_sum(int xoff, int yoff);
        int circle_sum();

public:
        Searcher(bool* segmat, int width, int height, int dia);
        Searcher(bool* segmat, int width, int height);

        void setDia(int dia);
        void searchSegments();
};

#endif
