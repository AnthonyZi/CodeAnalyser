#ifndef SHAPE_H
#define SHAPE_H

#include <cstdlib>
#include <cmath>
#include <iostream>

#define CIRCLE 0

class Shape
{
public:
        bool* matrix;
        int size, lefthalfsize, righthalfsize;
        int onescounted;
        
        Shape();

public:
        Shape(int shape, int size);

        bool* getmatrix();
        int getSize();
        int getonescounted();

        static bool* getCircleShape(int size);
};

#endif
