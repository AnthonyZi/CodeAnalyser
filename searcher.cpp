#include "searcher.h"

Searcher::Searcher(bool* pbitmat, int pwidth, int pheight, int dia) : bitmatrix(pbitmat), bitmatwidth(pwidth), bitmatheight(pheight)
{
        setDia(dia);
}

Searcher::Searcher(bool* pbitmat, int pwidth, int pheight) : bitmatrix(pbitmat), bitmatwidth(pwidth), bitmatheight(pheight)
{
        setDia(pwidth < pheight ? pwidth : pheight);
}

void Searcher::setDia(int dia)
{
        diameter = dia;
        circlekernel = CircleSegment::getCircleMatrix(diameter);
        dotwidth = sqrt(2*diameter*diameter);
        kernelsum = circle_sum();
        std::cout << "dia " << diameter << std::endl; //penis
        std::cout << kernelsum << " kernelsum" << std::endl; //penis
}

void Searcher::searchSegments()
{
        std::time_t at;
        std::time_t bt;
        while(diameter > 10)
        {
                at = std::time(NULL);
                for(int i = 0; i< bitmatheight-diameter; i++)
                {
                        for(int j = 0; j< bitmatwidth-diameter; j++)
                        {
                                if((double)conv2d_and_sum(j, i)/kernelsum > 0.9)
                                {
                                        std::cout << (double)conv2d_and_sum(j, i) << " / " << kernelsum << " - ";
                                        std::cout << diameter << "conv>0.9 at " << j << ", " << i << std::endl;
                                }
                        }
                }
                bt = std::time(NULL);
                std::cout << "diameter: " << diameter << " , t_elapsed: " << bt-at << std::endl;
                setDia(diameter-1);
        }
}

int Searcher::conv2d_and_sum(int xoff, int yoff)
{
        int sum = 0;

        for(int i = 0; i < diameter; i++)
        {
                for(int j = 0; j < diameter; j++)
                {
                        sum += *(circlekernel+i*diameter+j) * *(bitmatrix+(i+yoff)*bitmatwidth+j+xoff);
                }
        }
        return sum;
}

int Searcher::circle_sum()
{
        int sum = 0;
        for(int i = 0; i< diameter; i++)
        {
                for(int j = 0; j<diameter; j++)
                {
                        sum += *(circlekernel+i*diameter+j);
                }
        }
        return sum;
}
