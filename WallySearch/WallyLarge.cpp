#include "stdafx.h"

//base constructor...
WallyLarge::WallyLarge()
{
}

//wally scene image, utilises matrix...
WallyLarge::WallyLarge(int iHeight, int iWidth, double* input_data) : Matrix(iHeight, iWidth, input_data)
{
}

//method for outputting the final image based on the similarity score, and the corresponding x and y values...
void WallyLarge::PrintImage(double Score, int FinalX, int FinalY)
{
	//load in the large scene, it will then be split appropriately for the final result...
	double* read_data = Matrix::readTXT("../Fileloads/Cluttered_Scene.txt", x, y); 
	WallyLarge* SceneLoad = new WallyLarge(y, x, read_data); 

	//create WallySmall object...
	WallySmall output;

	//create a output name for the image...
	char* Outname = "../SSDImage.pgm"; 

	//create an array for the final images values...
	double* FinArray = new double[x1*y1];

	//declare the score that was the best similarity...
	cout << "The best score for your image is: " << Score << endl; 

	//state the y value and x value for the best result...
	cout << "Wally is at X: " << FinalX << ", " << "Y: " << FinalY << endl;

	//declare to the user what the final output name is for the file...
	cout << "The image has been output to: " << Outname << endl << endl;

	//using the previously created array, split the image with the desired x and y values...
	FinArray = output.ImageSplit(SceneLoad->getData(), FinalX, FinalY);

	//delete the read data...
	delete[] read_data;

	//write this to a pgm file...
	WritePGM(Outname, FinArray, y1, x1, 255);

	//delete the array when it is no longer required, save memory...
	delete[] FinArray;

}

//destructor...
WallyLarge::~WallyLarge()
{

}