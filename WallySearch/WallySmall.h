#pragma once

class WallySmall : public Matrix
{
public:
	WallySmall(); //constructor
	~WallySmall(); //destructor
	WallySmall(int iHeight, int iWidth, double * input_data);
	double* ImageSplit(double* image, int iterationX, int iterationY); //will be used to split the image.

private:
};