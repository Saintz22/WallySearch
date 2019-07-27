#pragma once

class WallyLarge : public Matrix
{
public:
	WallyLarge(); //constructor
	WallyLarge(int iHeight, int iWidth, double * input_data); //loads the scene..
	~WallyLarge(); //destructor
	void PrintImage(double Score, int FinalX, int FinalY); //will sort ssd results and output the image.
	
};