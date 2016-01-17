#include "searcher.h"

Searcher::Searcher(BITImage *pimage, int pdiameter) : image(pimage)
{
        setDiameter(pdiameter);
}

Searcher::Searcher(BITImage *pimage) : image(pimage)
{
}

void Searcher::setDiameter(int pdiameter)
{
        diameter = pdiameter;
        circlekernel = CircleSegment::getCircleMatrix(diameter);
        dotwidth = sqrt(2*diameter*diameter);
        kernelsum = CircleSegment::count_ones(circlekernel, diameter);
        std::cout << "dia " << diameter << std::endl; //penis
        std::cout << kernelsum << " kernelsum" << std::endl; //penis
}

void Searcher::filter_median_kernel(BITImage *pimage, bool* pkernel, int pkernelwidth, int pkernelheight, bool ones, bool more, int threshold)
{
       if(more)
       {
               for(int h = 0; h<pimage->getHeight(); h++)
               {
                       for(int w = 0; w<pimage->getWidth(); w++)
                       {
                               *(pimage->getPixels()+h*pimage->getWidth()+w) = 0;
                       }
               }
       }
       else
       {
       }
}

/*
int count_overlapping_bits_image_kernel(Kernel *pkern, int xoff, int yoff)
{

}
*/

void Searcher::searchSegments()
{
        std::time_t at;
        std::time_t bt;
        while(diameter > 10)
        {
                at = std::time(NULL);
                for(int i = 0; i< image->getHeight()-diameter; i++)
                {
                        for(int j = 0; j< image->getWidth()-diameter; j++)
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
                setDiameter(diameter-1);
        }
}

int Searcher::conv2d_and_sum(int xoff, int yoff)
{
        int sum = 0;

        for(int i = 0; i < diameter; i++)
        {
                for(int j = 0; j < diameter; j++)
                {
                        sum += *(circlekernel+i*diameter+j) * *(image->getPixels()+(i+yoff)*image->getHeight()+j+xoff);
                }
        }
        return sum;
}

void Searcher::labelImage()
{
        BITImage *tmp = new BITImage(*image);
}

BITImage* Searcher::getImage()
{
        return image;
}
