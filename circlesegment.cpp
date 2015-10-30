#include "circlesegment.h"

int* CircleSegment::getCircleMatrix(int diameter)
{
        int* circlemat;
        circlemat = (int*)malloc(sizeof(int)*diameter*diameter);

        invertCircleshape(circlemat, diameter, diameter);

        return circlemat;
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

                        *(matrix + (mathalfleftborder-j)*matrixwidth + (mathalfleftborder - i)) = tmpVal;
                        *(matrix + (mathalfleftborder-j)*matrixwidth + (mathalfrightborder + i)) = tmpVal;
                        *(matrix + (mathalfrightborder+j)*matrixwidth + (mathalfleftborder - i)) = tmpVal;
                        *(matrix + (mathalfrightborder+j)*matrixwidth + (mathalfrightborder + i)) = tmpVal;
                }
        }
}
