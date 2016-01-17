#ifndef SHAPE_H
#define SHAPE_H

#include <cstdlib>
#include <cmath>
#include <iostream>

#define CIRCLE 0

class Shape
{
public: // penis
        bool* matrix;
        int size;
        
        Shape();

public:
        Shape(int shape, int size);

        bool get(int xoff, int yoff);
        int getSize();

        static bool* getCircleShape(int size);
};

#endif
