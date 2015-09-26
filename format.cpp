#include "format.h"

int* get_significance_matrix(png_bytep pixeldata, uint32_t width, uint32_t height, int rref, int gref, int bref)
{
        int* sig_mat = (int*)malloc(sizeof(int)*width*height);
        if(sig_mat == NULL)
        {
                std::cerr << "could not assign pointer in format.cpp" << std::endl;
                return NULL;
        }
        png_bytep dataBlock = pixeldata;
        png_byte rdat, gdat, bdat;
        int rsig, gsig, bsig;
        for(unsigned long i = 0; i<width*height; i++)
        {
                rdat = *(dataBlock+i*3);
                gdat = *(dataBlock+i*3+1);
                bdat = *(dataBlock+i*3+2);

                rsig = ((int)rdat-rref);
                rsig = rsig*rsig/10;
                gsig = ((int)gdat-gref);
                gsig = gsig*gsig/10;
                bsig = ((int)bdat-bref);
                bsig = bsig*bsig/10;
                
                *(sig_mat+i) = rsig+gsig+bsig;
                *(sig_mat+i) = (*(sig_mat+i))*1000 / 19506; //max-wert = 255*255/10 (integer-rechnung) .. = 19506
        }

        return sig_mat;
}
