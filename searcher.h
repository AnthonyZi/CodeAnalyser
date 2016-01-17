#ifndef Searcher_H
#define Searcher_H

#include <cmath>
#include <ctime> //penis
#include <vector>
#include "circlesegment.h"
#include "bitimage.h"

class Searcher
{
private:
        BITImage *image;
        int diameter;
        int dotwidth;
        bool* circlekernel;
        int kernelsum;

        std::vector<CircleSegment> matchingSegments;

private:
        Searcher();
        int conv2d_and_sum(int xoff, int yoff);
        void setDiameter(int pdiameter);

public:
        Searcher(BITImage *pimage, int pdiameter);
        Searcher(BITImage *pimage);

        void filter_median_kernel(BITImage *pimage, bool* pkernel, int pkernelwidth, int pkernelheight, bool ones, bool more, int threshold);
        void searchSegments();
        void labelImage();
        BITImage* getImage();

};

#endif
