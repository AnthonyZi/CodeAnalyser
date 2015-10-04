#include "circlesegment.h"

int* CircleSegment::getCircleMatrix(int diameter)
{
        return 0;
}

void CircleSegment::invertCircleshape(int* matrix, int matrixwidth, int diameter)
{
        int mathalfleftborder = matrixwidth/2;
        int mathalfrightborder = matrixwidth - (matrixwidth/2);
        int tmpVal = 0;

        for(int i = 0; i<matrixwidth/2; i++)
        {
                for(int j = 0; j<matrixwidth/2; j++)
                {
                        tmpVal = sqrt((i*i) + (j*j)) <= diameter ? 1 : 0;

                        *(matrix + (jmathalfleftborder-j)*matrixwidth + (mathalfleftborder - i)) = tmpVal;
                        *(matrix + j*matrixwidth + (mathalfrightborder +i)) = tmpVal;
                        *(matrix + 
                }
        }
        for(int i = 0; i< matrixwidth/2; i++)
        {
                for(int j = 0; j<matrixwidth/2; j++)
                {
                        *(matrix + j*matrixwidth + (matrixwidth - ))
                }
        }
}
