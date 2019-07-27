#include "stdafx.h" //stdafx.h contains all defines, namespaces and includes.

int main()
{
	//introduction text to the program...
	cout << "\t\t\tWhere's Wally Finder..." << endl << endl;
	
	//vector for scores, will display top 5...
	vector <double> SSDScores; 

	//Scene and Wally loads...
	double* read_data = Matrix::readTXT("../Fileloads/Cluttered_Scene.txt", x, y); //reads in the file.
	WallyLarge* SceneLoad = new WallyLarge(y, x, read_data); //used to load the scene.
	read_data = Matrix::readTXT("../Fileloads/Wally_grey.txt", x1, y1); //will overwrite the previous read txt, can then reuse it.
	WallySmall* WallyLoad = new WallySmall(y1, x1, read_data); //used to load wally.

	//object for accessing my calculation methods, ssd, nc etc...
	Matrix SSDSearch; 
	
	//delete the array once it has been placed into the matrix, save memory...
	delete[] read_data;

	//create ints and doubles to get x values, y values, and comparison values in a later if statement. This will compare the scores on the fly...
	int FinalX = 0; int FinalY = 0; double score = 0; double SSD = 0; 

	//communciate to the user...
	cout << "The search is now beginning ..." << endl << endl;

	//for loop, minus a wallyx, and wally y in order to not go over the image...
	for (int i = 0; i < y - y1; i++) //max amount of times to go down on the image...
	{
		for (int b = 0; b < x - x1; b++)//max amount of times to go across the image...
		{
			double* SplitImage = WallyLoad->ImageSplit(SceneLoad->getData(), b, i); //splits the image on each iteration...
			SSD = SSDSearch.SSDCalc(WallyLoad->getData(), SplitImage); //this method will use the split image, and wally image to calculate ssd scores
			delete[] SplitImage; //deletes array when not in use...
			SSDScores.push_back(SSD); //pushes scores into the vector...
		
			while (score == 0) //this will give score a base value, this can then be compared with each iteration...
			{
				score = SSD;
				FinalX = b;
				FinalY = i;
			}
			if (SSD < score) //this will compare the value with the current lowest score...
			{
				score = SSD;
				FinalX = b;
				FinalY = i;
			}
		}
	}

	//communicating to the user again...
	cout << "Search has completed." << endl << endl;

		//will sort the vector...
		sort(SSDScores.begin(), SSDScores.end());

		//have a message to inform the user...
		cout << "\t\t\tThe top 5 SSD scores:" << endl;

		//display 0 - 5, this will show the lowest 5 scores...
		for (int i = 0; i < 5; i++)
		{
			cout << "\t\t\tScore " << i + 1 << ": " << SSDScores[i] << endl;
		}

		//delete vector...
		SSDScores.erase(SSDScores.begin(), SSDScores.end());

		//communicate to the user...
		cout << endl << "The system will now output the image." << endl;

		//Print the final image with the best score and corresponding x and y values. 
		SceneLoad->PrintImage(score, FinalX, FinalY);	

	//now delete pointers from heap.
	delete SceneLoad; 
	delete WallyLoad; 

	//stop auto exit upon completion of the main file...
	system("pause"); 

    return 0;
}

