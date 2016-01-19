#include "searcher.h"

Searcher::Searcher(BITImage *pimage, int pdiameter) : image(pimage)
{
        setDiameter(pdiameter);
}

Searcher::Searcher(BITImage *pimage) : image(pimage)
{
}

Searcher::Searcher(const Searcher &obj)
{
        std::cout << "call of copy-constructor searcher" << std::endl;
        diameter = obj.diameter;
        dotwidth = obj.dotwidth;
        kernelsum = obj.kernelsum;

        for(unsigned int i = 0; i < obj.matchingSegments.size(); i++)
        {
                matchingSegments.push_back(obj.matchingSegments[i]);
        }
        image = new BITImage(*obj.image);
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

        Shape* circle = new Shape(0, 10);
        filter_median(tmp, circle, 1, 1, 0.8f);
        
        save_png(tmp->getImage()->getPixels(), tmp->getImage()-getWidth(), tmp->getImage()->getHeight(), "debugpng/filtertest.png");
}

BITImage* Searcher::getImage()
{
        return image;
}
