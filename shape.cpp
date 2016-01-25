#include "shape.h"

Shape::Shape(int shape, int psize)
{
        std::cout << "shape constructor" << std::endl;
        switch(shape)
        {
        case CIRCLE:
                setCircleShape(psize);
                size = psize;
                break;
        default :
                break;
        }
}

Shape::Shape(const Shape &pshape)
{
        size = pshape.size;
        lefthalfsize = pshape.lefthalfsize;
        righthalfsize = pshape.righthalfsize;
        onescounted = pshape.onescounted;

        matrix = (bool*)malloc(sizeof(bool)*size*size);
        for(int offset = 0; offset<size*size; offset++)
        {
                *(matrix+offset) = *(pshape.matrix+offset);
        }
}

Shape::~Shape()
{
        std::cout << "destructor of shape" << std::endl;
        free(matrix);
}

void Shape::setCircleShape(int psize)
{
        matrix = (bool*)malloc(sizeof(bool)*psize*psize);

        for(int i = 0; i<psize*psize; i++)
                *(matrix+i) = 0;

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
                                *(matrix + (lefthalfsize-h)*psize + (lefthalfsize-w)) = tmpVal;
                                *(matrix + (lefthalfsize-h)*psize + (righthalfsize+w)) = tmpVal;
                                *(matrix + (righthalfsize+h)*psize + (lefthalfsize-w)) = tmpVal;
                                *(matrix + (righthalfsize+h)*psize + (righthalfsize+w)) = tmpVal;

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

                                *(matrix + (lefthalfsize-h)*psize + (lefthalfsize - w)) = tmpVal;
                                *(matrix + (lefthalfsize-h)*psize + (righthalfsize + w)) = tmpVal;
                                *(matrix + (righthalfsize+h)*psize + (lefthalfsize - w)) = tmpVal;
                                *(matrix + (righthalfsize+h)*psize + (righthalfsize + w)) = tmpVal;

                                if(tmpVal)
                                        onescounted += 4;                       }
                }

                int middle = (psize/2);
                for(int i = 0; i < middle; i++)
                {
                        *(matrix + (middle*psize) + i) = 1;
                        *(matrix + (i*psize) + middle) = 1;
                        *(matrix + (middle*psize) + middle + i + 1) = 1;
                        *(matrix + ((middle+i+1)*psize) + middle) = 1;
                }
                *(matrix + (middle*psize) + middle) = 1;
        }
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
