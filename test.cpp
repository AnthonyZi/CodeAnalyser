#include <iostream>
#include <cstdlib>
#include <ctime>
#include "readpng.h"
//#include "circlesegment.h"
#include "searcher.h"
#include "writepng.h"
#include "shape.h"

#include "rgbimage.h"
#include "labimage.h"
#include "bitimage.h"

int main(int argc, char* argv[])
{
        if(argc != 2)
                return 1;

        //preparing class-pointers
        RGBImage* rgb;
        LABImage* lab;
        BITImage* bit;

        std::clock_t t1, t2; //beta

        //START READ
        t1 = std::clock(); //beta
        rgb = new RGBImage(argv[1]);
        t2 = std::clock(); //beta
        std::cout << "read png: "; //beta
        std::cout << 1000.0*(t2-t1) / CLOCKS_PER_SEC << " ms" << std::endl; //beta
        //END READ

        t1 = std::clock(); //beta
        save_png(rgb->getPixels(), rgb->getWidth(), rgb->getHeight(), "debugpng/copy.png"); //beta
        t2 = std::clock(); //beta
        std::cout << "saving copy: "; //beta
        std::cout << 1000.0*(t2-t1) / CLOCKS_PER_SEC << " ms" << std::endl; //beta


        //START IMAGEPROCESSING
        t1 = std::clock(); //beta
        rgb->quickdownscale(2000);
        t2 = std::clock(); //beta
        std::cout << "downscaling: "; //beta
        std::cout << 1000.0*(t2-t1) / CLOCKS_PER_SEC << " ms" << std::endl; //beta


        save_png(rgb->getPixels(), rgb->getWidth(), rgb->getHeight(), "debugpng/after_scaling.png");


        t1 = std::clock(); //beta
        lab = new LABImage(rgb);
        t2 = std::clock(); //beta
        std::cout << "conversion: "; //beta
        std::cout << 1000.0*(t2-t1) / CLOCKS_PER_SEC << " ms" << std::endl; //beta


        t1 = std::clock(); //beta
        bit = new BITImage(lab);
        t2 = std::clock(); //beta

        unsigned char* rgbref = (unsigned char*)malloc(sizeof(unsigned char)*3);
        rgbref = bit->getREF();
        float* labref = (float*)malloc(sizeof(float)*3);
        labref = lab->getLAB(*(rgbref), *(rgbref+1), *(rgbref+2));
        std::cout << "calculation of bit-matrix: "; //beta
        std::cout << 1000.0*(t2-t1) / CLOCKS_PER_SEC << " ms" << std::endl; //beta
        std::cout << "[ " << (int)*(rgbref) << " " << (int)*(rgbref+1) << " " << (int)*(rgbref+2) << " (rgb) -> " << std::dec << *(labref) << " " << *(labref+1) << " " << *(labref+2) << " (lab) ]" << std::endl; //beta


        save_png(bit->getPixels(), bit->getWidth(), bit->getHeight(), "debugpng/binary_1.png");


        t1 = std::clock(); //beta
        bit->erase_small_structures();
        t2 = std::clock(); //beta
        std::cout << "processing(removal of small structures): "; //beta
        std::cout << 1000.0*(t2-t1) / CLOCKS_PER_SEC << " ms" << std::endl; //beta
        //END IMAGEPROCESSING


        save_png(bit->getPixels(), bit->getWidth(), bit->getHeight(), "debugpng/binary_2.png");

/*
        int* circlemat;

        int dia = 11;
        circlemat = CircleSegment::getCircleMatrix(dia);

        std::cout << "test for circlematrix" << std::endl; //beta

        
        std::cout << "convolution:" << std::endl; //beta

//        Searcher* s = new Searcher(bit->getPixels(), bit->getWidth(), bit->getHeight());

        s->setDia(70);
//        s->searchSegments();
*/
        Searcher *s = new Searcher(*bit);
        s->labelImage();
//        s->setDiameter(20);
//        s->labelImage();

//        Searcher *b = new Searcher(*s);
//        save_png(b->getImage()->getPixels(), b->getImage()->getWidth(), b->getImage()->getHeight(), "debugpng/copysearcher.png");

//        Shape* sh = new Shape(0, 100);
//        save_png(sh->matrix, sh->size, sh->size, "debugpng/shape.png");

//        Shape* sh2 = new Shape(0, 99);
//        save_png(sh2->matrix, sh2->size, sh2->size, "debugpng/shape2.png");


        return 0;
}
