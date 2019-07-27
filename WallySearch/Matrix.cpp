#include "stdafx.h"

Matrix::Matrix()
{
}

Matrix::Matrix(int iHeight, int iWidth, double* input_data)
{
	height = iHeight;
	width = iWidth;

	data = new double[height*width];

	for (int i = 0; i < height*width; i++)
	{
		data[i] = input_data[i];
	}
}

double Matrix::SSDCalc(double* WallySma, double* WallySplit) //SSD
{
	double sum = 0; 
	
	for (int i = 0; i < y1*x1; i++)
	{
		//remove the white from the image to make it not search for characters in blank space...
		if (WallySma[i] != 255 && WallySplit[i] != 255) {
			int diff = WallySma[i] - WallySplit[i];
			sum += diff*diff; //pow(diff,2) //inefficient, takes the program longer...
		}
	}

	//the sum will ignore values of 255, blank space...
	return sum;
} 

//method to output the final pgm...
void Matrix::WritePGM(char *filename, double *data, int sizeR, int sizeC, int Q)
{

	int i, j;
	unsigned char *image;
	ofstream myfile;

	image = (unsigned char *) new unsigned char[sizeR*sizeC];

	// convert the integer values to unsigned char

	for (i = 0; i<sizeR*sizeC; i++)
		image[i] = (unsigned char)data[i];

	myfile.open(filename, ios::out | ios::binary | ios::trunc);

	if (!myfile) {
		cout << "Can't open file: " << filename << endl;
		exit(1);
	}

	myfile << "P5" << endl;
	myfile << sizeC << " " << sizeR << endl;
	myfile << Q << endl;

	myfile.write(reinterpret_cast<char *>(image), (sizeR*sizeC)*sizeof(unsigned char));

	if (myfile.fail()) {
		cout << "Can't write image " << filename << endl;
		exit(0);
	}

	myfile.close();

	delete[] image;

}

double* Matrix::readTXT(char *fileName, int sizeR, int sizeC)
{
	double* data = new double[sizeR*sizeC];
	int i = 0;
	ifstream myfile(fileName);
	if (myfile.is_open())
	{

		while (myfile.good())
		{
			if (i>sizeR*sizeC - 1) break;
			myfile >> *(data + i);
			// cout << *(data+i) << ' '; // This line display the converted data on the screen, you may comment it out. 
			i++;
		}
		myfile.close();
	}

	else cout << "Unable to open file";
	//cout << i;

	return data;
}

Matrix::~Matrix()
{
	delete[] data;
}

//----------------------------------------------------------------------------------------------------------------------------------------
//programming that wasnt used in the end, however was in initial concepts for the assignment. Was going to be converted to a 2d array
//segemented as a 2d array, and placed back into a 1d array to be output, slow and inefficient, therefore changed. 

double** Matrix::ConvertTo2DArray(double* inputFile, int iX, int iY) //was used for converting the array to a 2d array before being sent back to 1d. inefficient 
{
	//use this function to convert the pgm arrays to a 2d array.
		double** Array2D = new double*[iY];

		for (int i = 0; i < iY; i++)
		{
			Array2D[i] = new double[iX];

			for (int b = 0; b < iX; b++)
			{
				Array2D[i][b] = inputFile[(i * iX) + b];
			}
		}

		return Array2D;
}	

double* Matrix::ConvertTo1DArray(double** inputData, int iX, int iY) //was used for converting to a 2d array and back again, inefficient. 
{
	double* convData = new double[iX*iY];
	for (int i = 0; i < iY; i++)
	{
		for (int b = 0; b < iX; b++)
		{
			convData[(i * iX) + b] = inputData[i][b];
		}
	}

	return convData;
}
