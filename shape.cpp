#include "shape.h"

Shape::Shape(int shape, int psize)
{
        std::cout << "constructor" << std::endl;
        switch(shape)
        {
        case CIRCLE :
                matrix = getCircleShape(size);
                size = psize;
                break;
        default :
                break;
        }
}

bool* Shape::getCircleShape(int size)
{
        std::cout << "bla";
        bool* shape = (bool*)malloc(sizeof(bool)*size*size);

        for(int i = 0; i<size*size; i++)
                *(shape+i) = 0;

        int mathhalfleftborder = (size/2)-1;
        int mathhalfrightborder;
        int tmpVal = 0;
        float x, y;

        if(size%2 == 0)
        {
                mathhalfrightborder = mathhalfleftborder+1;

                //iteration over the width
                for(int w = 0; w<size/2; w++)
                {
                        x = 0.5+w;

                        //iteration over the height
                        for(int h = 0; h<size/2; h++)
                        {
                                y = 0.5+h;

                                tmpVal = (sqrt((x*x) + (y*y)) <= size/2 ? 1 : 0);
                                *(shape + (mathhalfleftborder-h)*size + (mathhalfrightborder-w)) = tmpVal;
                                *(shape + (mathhalfleftborder-h)*size + (mathhalfrightborder+w)) = tmpVal;
                                *(shape + (mathhalfleftborder+h)*size + (mathhalfrightborder-w)) = tmpVal;
                                *(shape + (mathhalfleftborder+h)*size + (mathhalfrightborder+w)) = tmpVal;
                        }
                }
        }
        else
        {
                mathhalfrightborder = mathhalfleftborder+2;

                //iteration over the width
                for(int w = 0; w<size/2; w++)
                {
                        x = 1+w;

                        //iteration over the height
                        for(int h = 0; h<size/2; h++)
                        {
                                y = 1+h;

                        tmpVal = (sqrt((x*x) + (y*y)) <= ((float)size/2)) ? 1 : 0;

                        *(shape + (mathhalfleftborder-h)*size + (mathhalfleftborder - w)) = tmpVal;
                        *(shape + (mathhalfleftborder-h)*size + (mathhalfrightborder + w)) = tmpVal;
                        *(shape + (mathhalfrightborder+h)*size + (mathhalfleftborder - w)) = tmpVal;
                        *(shape + (mathhalfrightborder+h)*size + (mathhalfrightborder + w)) = tmpVal;
                }
        }

        int middle = (size/2);
        for(int i = 0; i < middle; i++)
        {
                *(shape + (middle*size) + i) = 1;
                *(shape + (i*size) + middle) = 1;
                *(shape + (middle*size) + middle + i + 1) = 1;
                *(shape + ((middle+i+1)*size) + middle) = 1;
        }
        *(shape + (middle*size) + middle) = 1;
        }
        std::cout << "fertisch";
        
        return shape;
}

bool Shape::get(int xoff, int yoff)
{
        return 1;
}

int Shape::getSize()
{
        return size;
}
