#include "shape.h"

Shape::Shape(int shape, int psize)
{
        std::cout << "constructor" << std::endl;
        switch(shape)
        {
        case CIRCLE:
                matrix = getCircleShape(psize);
                size = psize;
                break;
        default :
                break;
        }
}

bool* Shape::getCircleShape(int psize)
{
        bool* shape = (bool*)malloc(sizeof(bool)*psize*psize);

        for(int i = 0; i<psize*psize; i++)
                *(shape+i) = 0;

        lefthalfsize = (psize/2)-1;
        int tmpVal = 0;
        onescounted = 0;
        float x, y;

        if(psize%2 == 0)
        {
                righthalfsize = lefthalfsize+1;

                //iteration over the width
                for(int w = 0; w<=lefthalfsize; w++)
                {
                        x = 0.5+w;

                        //iteration over the height
                        for(int h = 0; h<=lefthalfsize; h++)
                        {
                                y = 0.5+h;

                                tmpVal = ((x*x)+(y*y)) <= psize*psize/4 ? 1 : 0;
                                *(shape + (lefthalfsize-h)*psize + (lefthalfsize-w)) = tmpVal;
                                *(shape + (lefthalfsize-h)*psize + (righthalfsize+w)) = tmpVal;
                                *(shape + (righthalfsize+h)*psize + (lefthalfsize-w)) = tmpVal;
                                *(shape + (righthalfsize+h)*psize + (righthalfsize+w)) = tmpVal;

                                if(tmpVal)
                                        onescounted += 4;
                        }
                }
        }
        else
        {
                righthalfsize = lefthalfsize+2;

                //iteration over the width
                for(int w = 0; w<psize/2; w++)
                {
                        x = 1+w;

                        //iteration over the height
                        for(int h = 0; h<psize/2; h++)
                        {
                                y = 1+h;

                                tmpVal = (((x*x)+(y*y)) <= psize*psize/4) ? 1 : 0;

                                *(shape + (lefthalfsize-h)*psize + (lefthalfsize - w)) = tmpVal;
                                *(shape + (lefthalfsize-h)*psize + (righthalfsize + w)) = tmpVal;
                                *(shape + (righthalfsize+h)*psize + (lefthalfsize - w)) = tmpVal;
                                *(shape + (righthalfsize+h)*psize + (righthalfsize + w)) = tmpVal;

                                if(tmpVal)
                                        onescounted += 4;                       }
                }

                int middle = (psize/2);
                for(int i = 0; i < middle; i++)
                {
                        *(shape + (middle*psize) + i) = 1;
                        *(shape + (i*psize) + middle) = 1;
                        *(shape + (middle*psize) + middle + i + 1) = 1;
                        *(shape + ((middle+i+1)*psize) + middle) = 1;
                }
                *(shape + (middle*psize) + middle) = 1;
        }
                
        return shape;
}

//for ease : shapes with an even siz
bool* Shape::getmatrix()
{
        return matrix;
}

int Shape::getSize()
{
        return size;
}

int Shape::getonescounted()
{
        return onescounted;
}
