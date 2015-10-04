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
        float tempx, tempy, tempz;
        float tempr, tempg, tempb;

        tempr = (float)rdat / 255;
        tempg = (float)gdat / 255;
        tempb = (float)bdat / 255;

        if(tempr > 0.04045)
                tempr = pow( (tempr+0.055)/1.055, 2.4);
        else
                tempr /= 12.92;
        if(tempg > 0.04045)
                tempg = pow( (tempg+0.055)/1.055, 2.4);
        else
                tempg /= 12.92;
        if(tempb > 0.04045)
                tempb = pow( (tempb+0.055)/1.055, 2.4);
        else
                tempb /= 12.92;

        tempr *= 100;
        tempg *= 100;
        tempb *= 100;
        
        tempx = tempr*0.4124 + tempg*0.3576 + tempb*0.1805;
        tempy = tempr*0.2126 + tempg*0.7152 + tempb*0.0722;
        tempz = tempr*0.0193 + tempg*0.1192 + tempb*0.9505;

        tempx /= 95.047;
        tempy /= 100;
        tempz /= 108.883;

        if(tempx > 0.008856)
                tempx = pow(tempx, 1.0/3);
        else
                tempx = (7.787*tempx) + (16.0/116);
        if(tempy > 0.008856)
                tempy = pow(tempy, 1.0/3);
        else
                tempy = (7.787*tempy) + (16.0/116);
        if(tempz > 0.008856)
                tempz = pow(tempz, 1.0/3);
        else
                tempz = (7.787*tempz) + (16.0/116);

        *(lab) = (116*tempy) - 16;
        *(lab+1) = 500*(tempx - tempy);
        *(lab+2) = 200*(tempy - tempz);
}
