#ifndef Searcher_H
#define Searcher_H

#include <cmath>
#include <ctime> //penis
#include <vector>
#include "circlesegment.h"
#include "bitimage.h"
#include "medianfilter.h"
#include "writepng.h"
#include "shape.h"

class Searcher
{
private:
        BITImage *image;
        Shape *segmentkernel, *dotkernel;

        std::vector<BITImage*> matchingSegments;

private:
        Searcher();
        int conv2d_and_sum(int xoff, int yoff);
//        void setDiameter(int pdiameter);

public:
        void setDiameter(int pdiameter);
        Searcher(BITImage pimage, int pdiameter);
        Searcher(BITImage pimage);
        Searcher(const Searcher &psearcher);

        void searchSegments();
        std::vector<BITImage*> getSearchSegments();
        BITImage* getImage();
};

#endif
