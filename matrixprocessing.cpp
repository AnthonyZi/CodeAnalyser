#include "matrixprocessing.h"

bool* get_bitmatrix(int* significance_mat, uint32_t pwidth, uint32_t pheight, int threshold)
{        
        bool* bitmat = (bool*)malloc(sizeof(bool)*pwidth*pheight);
        for(png_uint_32 h = 0; h<pheight; h++)
        {
                for(png_uint_32 w = 0; w<pwidth; w++)
                {
                        int tmp = *(significance_mat+h*pwidth+w);
                        *(bitmat+h*pwidth+w) = tmp>threshold ? false : true;
                }
        }
        return bitmat;
}

png_bytep quickdownscale(png_bytep pixeldata, png_uint_32* pwidth, png_uint_32* pheight)
{
        png_uint_32 width = (*pwidth)/2;
        png_uint_32 height = (*pheight)/2;

        png_bytep tmppixeldata = (png_bytep)malloc(sizeof(png_byte)*width*height*3);

        int sumr, sumg, sumb;
        for(png_uint_32 h = 0; h < height; h++)
        {
                for(png_uint_32  w = 0; w < width; w++)
                {
                        sumr = 0;
                        sumg = 0;
                        sumb = 0;
                        for(int i = 0; i<2; i++)
                        {
                                for(int j = 0; j<=3; j+=3)
                                {
                                        sumr += *(pixeldata+(2*h+i)*(*pwidth)*3+(2*w+j));
                                        sumg += *(pixeldata+(2*h+i)*(*pwidth)*3+(2*w+j)+1);
                                        sumb += *(pixeldata+(2*h+i)*(*pwidth)*3+(2*w+j)+2);
                                }
                        }
                        *(tmppixeldata+h*width*3+w) = sumr/4; 
                        *(tmppixeldata+h*width*3+w+1) = sumg/4;
                        *(tmppixeldata+h*width*3+w+2) = sumb/4;
                }
        }
        *pwidth = width;
        *pheight = height;
        free(pixeldata);
        return tmppixeldata;
}

int* get_significance_matrix(float* pixeldata, uint32_t pwidth, uint32_t pheight, float lref, float aref, float bref)
{
        int* sig_mat = (int*)malloc(sizeof(int)*pwidth*pheight);
        if(sig_mat == NULL)
        {
                std::cerr << "could not assign pointer in get_significance_matrix" << std::endl;
                return NULL;
        }
        float ldat, adat, bdat;
        float ldif, adif, bdif;
        for(unsigned long i = 0; i<pwidth*pheight; i++)
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

float* matrix_rgb_to_lab(png_bytep pixeldata, uint32_t pwidth, uint32_t pheight)
{
        float* lab_mat = (float*)malloc(sizeof(float)*pwidth*pheight*3);
        if(lab_mat == NULL)
        {
                std::cerr << "could not assign pointer in matrix_rgb_to_lab" << std::endl;
                return NULL;
        }
        png_byte rdat, gdat, bdat;
        for(unsigned long i = 0; i < pwidth*pheight; i++)
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

int* get_valuable_chunks(bool* bitmat,uint32_t pwidth, uint32_t pheight)
{
        int* array = (int*)malloc(sizeof(int)*3*100);

        return array;
}

bool* filter_median_square(bool* bitmat, uint32_t pwidth, uint32_t pheight, int kernelradius, bool ones, bool more, int threshold)
{
        bool* tmp = (bool*)malloc(sizeof(bool)*pwidth*pheight);
        if(more)
        {
                for(uint32_t h = 0; h < pheight; h++)
                {
                        for(uint32_t w = 0; w < pwidth; w++)
                        {
                                *(tmp+h*pwidth+w) = count_bits_in_square(bitmat, pwidth, pheight, kernelradius, ones, w, h) > threshold ? ones : !ones;
                        }
                }
        }
        else
        {
                for(uint32_t h = 0; h < pheight; h++)
                {
                        for(uint32_t w = 0; w < pwidth; w++)
                        {
                                *(tmp+h*pwidth+w) = count_bits_in_square(bitmat, pwidth, pheight, kernelradius, ones, w, h) < threshold ? ones : !ones;
                        }
                }
        }
        free(bitmat);
        return tmp;
}

int count_bits_in_square(bool* bitmat, uint32_t pwidth, uint32_t pheight, int kernelradius, bool ones, int xoff, int yoff)
{
        int sum = 0;
        for(int y = -kernelradius; y <= kernelradius; y++)
        {
                for(int x = -kernelradius; x <= kernelradius; x++)
                {
                        if(xoff+x > 0 && (unsigned int)(xoff+x) < pwidth && yoff+y > 0 && (unsigned int)(yoff+y) < pheight)
                        {
                                sum += *(bitmat+(yoff+y)*pwidth+(xoff+x));
                        }
                }
        }
        if(ones)
                return sum;
        else
                return (2*kernelradius+1)*(2*kernelradius+1)-sum;
}
