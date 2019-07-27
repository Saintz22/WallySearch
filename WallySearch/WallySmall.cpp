#include "stdafx.h"

WallySmall::WallySmall()
{
}

//loads the wally small image...
WallySmall::WallySmall(int iHeight, int iWidth, double* input_data) : Matrix(iHeight, iWidth, input_data)
{
}

//image split function here...
double* WallySmall::ImageSplit(double* image, int X, int Y)
{
	//creates a new blank 1d array for the image part...
	double* imagePart = new double[y1*x1];

	for (int i = Y; i < (Y + y1); i++)
	{
		for (int b = X; b < (X + x1); b++) 
		{
			//breaks up the image based on iteration...
			imagePart[((i - Y)*x1) + (b-X)] = image[i * x + b];
			
		}
	}
	return imagePart;
}

WallySmall::~WallySmall(void)
{

}