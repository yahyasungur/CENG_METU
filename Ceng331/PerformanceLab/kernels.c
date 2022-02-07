/********************************************************
 * Kernels to be optimized for the Metu Ceng Performance Lab
 ********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

/* 
 * Please fill in the following team struct 
 */
team_t team = {
    "Contra",                     /* Team name */

    "Yahya SUNGUR",             /* First member full name */
    "e2375723",                 /* First member id */

    "",                         /* Second member full name (leave blank if none) */
    "",                         /* Second member id (leave blank if none) */

    "",                         /* Third member full name (leave blank if none) */
    ""                          /* Third member id (leave blank if none) */
};

/****************
 * EXPOSURE FUSION KERNEL *
 ****************/

/*******************************************************
 * Your different versions of the exposure fusion kernel go here 
 *******************************************************/

/* 
 * naive_fusion - The naive baseline version of exposure fusion
 */
char naive_fusion_descr[] = "naive_fusion: Naive baseline exposure fusion";
void naive_fusion(int dim, int *img, int *w, int *dst) {
  
    int i, j, k; 
    for(k = 0; k < 4; k++){
        for(i = 0; i < dim; i++) {
            for(j = 0; j < dim; j++) {
                    dst[i*dim+j] += w[k*dim*dim+i*dim+j] * img[k*dim*dim+i*dim+j];
            }
        }
    }
}

/* 
 * fusion - Your current working version of fusion
 * IMPORTANT: This is the version you will be graded on
 */
char fusion_descr[] = "fusion: Current working version";
void fusion(int dim, int *img, int *w, int *dst){
    
    int i, j, k,i_dim=0,k_dim_dim = 0;
    int dim_dim = dim*dim;
    for(k = 0; k < 4; k++){
        k_dim_dim = k*dim_dim;
        for(i = 0; i < dim; i++) {
            i_dim = i*dim;
            for(j = 0; j < dim; j+=8) {
                    dst[i_dim+j] += w[k_dim_dim+i_dim+j] * img[k_dim_dim+i_dim+j];
                    dst[i_dim+j+1] += w[k_dim_dim+i_dim+j+1] * img[k_dim_dim+i_dim+j+1];
                    dst[i_dim+j+2] += w[k_dim_dim+i_dim+j+2] * img[k_dim_dim+i_dim+j+2];
                    dst[i_dim+j+3] += w[k_dim_dim+i_dim+j+3] * img[k_dim_dim+i_dim+j+3];
                    dst[i_dim+j+4] += w[k_dim_dim+i_dim+j+4] * img[k_dim_dim+i_dim+j+4];
                    dst[i_dim+j+5] += w[k_dim_dim+i_dim+j+5] * img[k_dim_dim+i_dim+j+5];
                    dst[i_dim+j+6] += w[k_dim_dim+i_dim+j+6] * img[k_dim_dim+i_dim+j+6];
                    dst[i_dim+j+7] += w[k_dim_dim+i_dim+j+7] * img[k_dim_dim+i_dim+j+7];
            }
        }
    }
}

/*********************************************************************
 * register_fusion_functions - Register all of your different versions
 *     of the fusion kernel with the driver by calling the
 *     add_fusion_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_fusion_functions() 
{
    add_fusion_function(&naive_fusion, naive_fusion_descr);  
    add_fusion_function(&fusion, fusion_descr);  
    /* ... Register additional test functions here */
}

/***************************
 * GAUSSIAN BLUR KERNEL *
 ***************************/

/******************************************************
 * Your different versions of the Gaussian blur functions go here
 ******************************************************/

/* 
 * naive_blur - The naive baseline version of Gussian blur
 */
char naive_blur_descr[] = "naive_blur The naive baseline version of Gaussian blur";
void naive_blur(int dim, float *img, float *flt, float *dst) {
  
    int i, j, k, l;

    for(i = 0; i < dim-5+1; i++){
        for(j = 0; j < dim-5+1; j++) {
            for(k = 0; k < 5; k++){
                for(l = 0; l < 5; l++) {
                    dst[i*dim+j] = dst[i*dim+j] + img[(i+k)*dim+j+l] * flt[k*dim+l];
                }
            }
        }
    }
}

/* 
 * blur - Your current working version of Gaussian blur
 * IMPORTANT: This is the version you will be graded on
 */
char blur_descr[] = "blur: Current working version";
void blur(int dim, float *img, float *flt, float *dst){
    int i, j, k, i_dim, i_dim_j,k_dim; 
    float temp=0.0,temp1=0.0,temp2=0.0,temp3=0.0,temp4=0.0;

    for(i = 0; i < dim-5+1; i++){
        i_dim = i*dim;
        for(j = 0; j < dim-5+1; j++) {
            i_dim_j = i_dim + j; 
            for(k = 0; k < 5; k++){
                k_dim = k*dim;
                temp = temp + img[i_dim_j+k_dim] * flt[k_dim];
                temp1 = temp1 + img[i_dim_j+k_dim+1] * flt[k_dim+1];
                temp2 = temp2 + img[i_dim_j+k_dim+2] * flt[k_dim+2];
                temp3 = temp3 + img[i_dim_j+k_dim+3] * flt[k_dim+3];
                temp4 = temp4 + img[i_dim_j+k_dim+4] * flt[k_dim+4];
            }
            dst[i_dim_j] += temp+temp1+temp2+temp3+temp4;
            temp = 0.0;
            temp1 = 0.0;
            temp2 = 0.0;
            temp3 = 0.0;
            temp4 = 0.0;
        }
    }
}

/*********************************************************************
 * register_blur_functions - Register all of your different versions
 *     of the gaussian blur kernel with the driver by calling the
 *     add_blur_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_blur_functions() 
{
    add_blur_function(&naive_blur, naive_blur_descr); 
    add_blur_function(&blur, blur_descr);
    /* ... Register additional test functions here */
}

