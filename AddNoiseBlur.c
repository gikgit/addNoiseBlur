#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "Function.h"

#define NAME_IMG_IN  "photograph"
#define NAME_IMG_OUT "photograph_degraded"

int main(int argc,char** argv)
{
	int i,j,k;
  	int length,width;
  	float var;
  	int size_filter; 

  	float** image; 
	float** mask;  
  	float** degrad_image;  
   	
  	printf("Input the size of filter: ");
  	scanf("%d",&size_filter);
	
	printf("Input the variance of bruit : ");
  	scanf("%f",&var);

	image = LoadImagePgm(NAME_IMG_IN,&length,&width);
	mask = fmatrix_allocate_2d(length,width);
	degrad_image = fmatrix_allocate_2d(length,width);

	/* initialize array*/
	for(i=0;i<length;i++){
		for(j=0;j<width;j++){
			mask[i][j]=0.0;
			degrad_image[i][j]=0.0;
		}
	}

  	/* add blur to original image */
	blur_mask(mask,size_filter,length,width);
	convolution(degrad_image,image,mask,length,width);
	Recal(degrad_image,length,width);

	/* add noise to blur image */
	add_gaussian_noise(degrad_image,length,width,var);
	Recal(degrad_image,length,width);

  	/* save image */
	SaveImagePgm(NAME_IMG_OUT,degrad_image,length,width);
	system("display photograph_degraded.pgm&");
        
  
  	/* free memory*/
	free_fmatrix_2d(image);  
	free_fmatrix_2d(mask);
	free_fmatrix_2d(degrad_image);
  	
  	printf("\n Ending ... \n\n\n");
  	return 0; 	 
}



