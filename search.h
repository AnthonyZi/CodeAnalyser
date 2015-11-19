#ifndef Searcher_H
#define Searcher_H

#include "circlesegment.h"

class Searcher
{
private:
        CircleSegment mysegment;
        int diameter;

private:
        Searcher();
        void searchabc();

public:
        Searcher(int* segmat, int dia);

}

#endif
