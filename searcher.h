#ifndef Searcher_H
#define Searcher_H

#include <cmath>
#include <ctime> //penis
#include <vector>
#include "circlesegment.h"
#include "bitimage.h"
#include "medianfilter.h"
#include "writepng.h"

class Searcher
{
private:
        BITImage *image;
        int diameter;
        int dotwidth;

        std::vector<BITImage*> matchingSegments;

private:
        Searcher();
        int conv2d_and_sum(int xoff, int yoff)
        void setDiameter(int pdiameter);

public:
        Searcher(BITImage *pimage, int pdiameter);
        Searcher(BITImage *pimage);
        Searcher(const Searcher &obj);

        void searchSegments();
        void labelImage();
        BITImage* getImage();
};

#endif
