#include <math.h>
#include "format.h"

int* get_significance_matrix(float* pixeldata, uint32_t width, uint32_t height, float lref, float aref, float bref)
{
        int* sig_mat = (int*)malloc(sizeof(int)*width*height);
        if(sig_mat == NULL)
        {
                std::cerr << "could not assign pointer in get_significance_matrix" << std::endl;
                return NULL;
        }
        float ldat, adat, bdat;
        float ldif, adif, bdif;
        for(unsigned long i = 0; i<width*height; i++)
        {
                ldat = *(pixeldata+i*3);
                adat = *(pixeldata+i*3+1);
                bdat = *(pixeldata+i*3+2);

                ldif = ldat-lref;
                adif = adat-aref;
                bdif = bdat-bref;

                *(sig_mat+i) = 10*sqrt(ldif*ldif + adif*adif + bdif*bdif);
        }

        return sig_mat;
}

float* matrix_rgb_to_lab(png_bytep pixeldata, uint32_t width, uint32_t height)
{
        float* lab_mat = (float*)malloc(sizeof(float)*width*height*3);
        if(lab_mat == NULL)
        {
                std::cerr << "could not assign pointer in matrix_rgb_to_lab" << std::endl;
                return NULL;
        }
        png_byte rdat, gdat, bdat;
        for(unsigned long i = 0; i < width*height; i++)
        {
                rdat = *(pixeldata +i*3);
                gdat = *(pixeldata +i*3 +1);
                bdat = *(pixeldata +i*3 +2);
                
                float* lab = lab_mat +i*3;
                rgb_to_lab(lab, rdat, gdat, bdat);
        }
        return lab_mat;
}

void rgb_to_lab(float* lab, png_byte rdat, png_byte gdat, png_byte bdat)
{

        std::cout << (int)rdat << " " << (int)gdat << " " << (int)bdat << " -> ";
        float tempx, tempy, tempz;

        tempx = (float)rdat*0.4124564 + (float)gdat*0.3575761 + (float)bdat*0.1804375;
        tempy = (float)rdat*0.2126729 + (float)gdat*0.7151522 + (float)bdat*0.0721750;
        tempz = (float)rdat*0.0193339 + (float)gdat*0.1191920 + (float)bdat*0.9503041;

        *(lab) = (116*pow(tempy/100, 1/3)) - 16;
        *(lab+1) = 500*(pow(tempx/94.811, 1/3) - pow(tempy/100, 1/3));
        *(lab+2) = 200*(pow(tempy/100, 1/3) - pow(tempz/107.304, 1/3));

        std::cout << *lab << " " << *(lab+1) << " " << *(lab+2) << std::endl;
}
