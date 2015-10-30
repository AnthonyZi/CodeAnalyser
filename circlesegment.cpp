#include "circlesegment.h"

int* CircleSegment::getCircleMatrix(int diameter)
{
        int* circlemat;
        circlemat = (int*)malloc(sizeof(int)*diameter*diameter);

        for(int i = 0; i < diameter*diameter; i++)
        {
                *(circlemat+i) = 0;
        }
        invertCircleshape(circlemat, diameter, diameter);

        return circlemat;
}

void CircleSegment::invertCircleshape(int* matrix, int matrixwidth, int diameter)
{
        int mathhalfleftborder = (matrixwidth/2)-1;
        int mathhalfrightborder;
        int tmpVal = 0;
        float x,y;

        if(matrixwidth%2 == 0)
        {
                mathhalfrightborder = mathhalfleftborder+1;

                //iteration over the width
                for(int i = 0; i<matrixwidth/2; i++)
                {
                        x = 0.5+i;

                        //iteration over the height
                        for(int j = 0; j<matrixwidth/2; j++)
                        {
                                y = 0.5+j;

                                tmpVal = (sqrt((x*x) + (y*y)) <= (diameter/2)) ? 1 : 0;

                                *(matrix + (mathhalfleftborder-j)*matrixwidth + (mathhalfleftborder - i)) = tmpVal;
                                *(matrix + (mathhalfleftborder-j)*matrixwidth + (mathhalfrightborder + i)) = tmpVal;
                                *(matrix + (mathhalfrightborder+j)*matrixwidth + (mathhalfleftborder - i)) = tmpVal;
                                *(matrix + (mathhalfrightborder+j)*matrixwidth + (mathhalfrightborder + i)) = tmpVal;
                        }
                }
        }
        else
        {
                mathhalfrightborder = mathhalfleftborder+2;

                //iteration over the width
                for(int i = 0; i<matrixwidth/2; i++)
                {
                        x = 1+i;

                        //iteration over the height
                        for(int j = 0; j<matrixwidth/2; j++)
                        {
                                y = 1+j;

                                tmpVal = (sqrt((x*x) + (y*y)) <= ((float)diameter/2)) ? 1 : 0;

                                *(matrix + (mathhalfleftborder-j)*matrixwidth + (mathhalfleftborder - i)) = tmpVal;
                                *(matrix + (mathhalfleftborder-j)*matrixwidth + (mathhalfrightborder + i)) = tmpVal;
                                *(matrix + (mathhalfrightborder+j)*matrixwidth + (mathhalfleftborder - i)) = tmpVal;
                                *(matrix + (mathhalfrightborder+j)*matrixwidth + (mathhalfrightborder + i)) = tmpVal;
                        }
                }

                int middle = (matrixwidth/2);
                for(int i = 0; i < middle; i++)
                {
                        *(matrix + (middle*matrixwidth) + i) = 1;
                        *(matrix + (i*matrixwidth) + middle) = 1;
                        *(matrix + (middle*matrixwidth) + middle + i + 1) = 1;
                        *(matrix + ((middle+i+1)*matrixwidth) + middle) = 1;
                }
                *(matrix + (middle*matrixwidth) + middle) = 1;
        }
}
