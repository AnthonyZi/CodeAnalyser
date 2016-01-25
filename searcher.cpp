#include "searcher.h"

Searcher::Searcher(BITImage pimage, int pdiameter)
{
        image = &pimage;
        setDiameter(pdiameter);
}

Searcher::Searcher(BITImage pimage)
{
        image = &pimage;
        int segmentsize = image->getWidth() > image->getHeight() ? image->getHeight()/5 : image->getWidth()/5;
        setDiameter(segmentsize);
}

Searcher::Searcher(const Searcher &psearcher)
{
        std::cout << "call of copy-constructor searcher" << std::endl;
        segmentkernel = psearcher.segmentkernel;
        dotkernel = psearcher.dotkernel;

        for(unsigned int i = 0; i < psearcher.matchingSegments.size(); i++)
        {
                matchingSegments.push_back(psearcher.matchingSegments[i]);
        }
        image = new BITImage(*psearcher.image);
}

void Searcher::setDiameter(int pdiameter)
{
        std::cout << "setting diameter" << std::endl;
        segmentkernel = new Shape(0, pdiameter);
        dotkernel = new Shape(0, pdiameter/7);


//        dotwidth = sqrt(2*diameter*diameter);
}

void Searcher::searchSegments()
{
        std::time_t at;
        std::time_t bt;
        while(segmentkernel->getSize() > 10)
        {
                at = std::time(NULL);
                for(int i = 0; i< image->getHeight()-segmentkernel->getSize(); i++)
                {
                        for(int j = 0; j< image->getWidth()-segmentkernel->getSize(); j++)
                        {
                                if((double)conv2d_and_sum(j, i)/segmentkernel->getonescounted() > 0.9)
                                {
                                        std::cout << (double)conv2d_and_sum(j, i) << " / " << segmentkernel->getonescounted() << " - ";
                                        std::cout << segmentkernel->getSize() << "conv>0.9 at " << j << ", " << i << std::endl;
                                }
                        }
                }
                bt = std::time(NULL);
                std::cout << "segmentkernel->getSize(): " << segmentkernel->getSize() << " , t_elapsed: " << bt-at << std::endl;
                setDiameter(segmentkernel->getSize()-1);
        }
}

int Searcher::conv2d_and_sum(int xoff, int yoff)
{
        int sum = 0;

        for(int i = 0; i < segmentkernel->getSize(); i++)
        {
                for(int j = 0; j < segmentkernel->getSize(); j++)
                {
                        sum += *((segmentkernel->getmatrix())+i*(segmentkernel->getSize())+j) * *(image->getPixels()+(i+yoff)*image->getHeight()+j+xoff);
                }
        }
        return sum;
}

std::vector<BITImage*> Searcher::getSearchSegments()
{
        BITImage *tmp = new BITImage(*image);

        Shape* circle = new Shape(0, image->getWidth() > image->getHeight() ? image->getHeight()/5 : image->getWidth()/5);
        extend_image(tmp, circle, 1);
        save_png(tmp->getPixels(), tmp->getWidth(), tmp->getHeight(), "debugpng/bla.png");

/*
        filter_median(tmp, circle, 1, 1, 0.8f);
        save_png(tmp->getPixels(), tmp->getWidth(), tmp->getHeight(), "debugpng/filtertest1.png");
        filter_median(tmp, circle, 1, 1, 0.8f);
        save_png(tmp->getPixels(), tmp->getWidth(), tmp->getHeight(), "debugpng/filtertest2.png");
        filter_median(tmp, circle, 1, 1, 0.8f);
        save_png(tmp->getPixels(), tmp->getWidth(), tmp->getHeight(), "debugpng/filtertest3.png");
        filter_median(tmp, circle, 1, 1, 0.8f);
        save_png(tmp->getPixels(), tmp->getWidth(), tmp->getHeight(), "debugpng/filtertest4.png");
        filter_median(tmp, circle, 1, 1, 0.8f);
        save_png(tmp->getPixels(), tmp->getWidth(), tmp->getHeight(), "debugpng/filtertest5.png");
        filter_median(tmp, circle, 1, 1, 0.8f);
        save_png(tmp->getPixels(), tmp->getWidth(), tmp->getHeight(), "debugpng/filtertest6.png");
        filter_median(tmp, circle, 1, 1, 0.8f);
        save_png(tmp->getPixels(), tmp->getWidth(), tmp->getHeight(), "debugpng/filtertest7.png");
        filter_median(tmp, circle, 1, 1, 0.8f);
        save_png(tmp->getPixels(), tmp->getWidth(), tmp->getHeight(), "debugpng/filtertest8.png");
*/
}

BITImage* Searcher::getImage()
{
        return image;
}
