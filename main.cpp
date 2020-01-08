#include <iostream>
#include <vector>
#include <exception>
#include <cmath>
#include <utility>

using namespace std;

double** initializeMatrix(int size)
{
	double** gaussMatrix = new double* [size];

	for (int i = 0; i < size; i++)
	{
		gaussMatrix[i] = new double[size + 1];
	}

	return gaussMatrix;
}

double** enterData(int size)
{
	double** gaussMatrix = initializeMatrix(size);

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size + 1; j++)
		{

			cout << "Podaj [" << i << "][" << j << "] wspólczynnik macierzy" << endl;
			cin >> gaussMatrix[i][j];
		}

	}

	return gaussMatrix;

}

void gaussStep(double** gaussMatrix, int size, int iteratorValue)
{
	double multiplier = 0.0;
	for (int i = iteratorValue + 1; i < size; i++)

	{
		multiplier = gaussMatrix[i][iteratorValue] / gaussMatrix[iteratorValue][iteratorValue];
		gaussMatrix[i][iteratorValue] = 0;
		for (int j = iteratorValue; j <= size; j++)
			gaussMatrix[i][j] = gaussMatrix[i][j] - multiplier * gaussMatrix[iteratorValue][j];
	}

}

double findMaxInRow(double**& gaussMatrix, int size, int iteratorValue)
{
	double max = fabs(gaussMatrix[iteratorValue][iteratorValue]);
	int maxIndex = 0;
	for (int i = iteratorValue; i < size; i++)
	{
		if (fabs(gaussMatrix[iteratorValue][i]) > max)
		{
			max = fabs(gaussMatrix[iteratorValue][i]);
			maxIndex = i;
		}
	}

	return maxIndex;
}

double findMaxInCol(double**& gaussMatrix, double* solutionVector, int size, int iteratorValue)
{
	double maxElement = fabs(gaussMatrix[iteratorValue][iteratorValue]);
	int indexOfMaxElement = iteratorValue + 1;
	for (int i = iteratorValue; i < size; i++)
	{
		if (fabs(gaussMatrix[i][iteratorValue]) > maxElement)
		{
			maxElement = gaussMatrix[i][iteratorValue];
			indexOfMaxElement = i;
		}
	}


	return indexOfMaxElement;
}


void swapRows(double**& gaussMatrix, int size, int firstToSwap, int secondToSwap)
{
	double tempVec = 0.0;

	for (int i = 0; i <= size; i++)
	{

		tempVec = gaussMatrix[firstToSwap][i];
		gaussMatrix[firstToSwap][i] = gaussMatrix[secondToSwap][i];
		gaussMatrix[secondToSwap][i] = tempVec;
	}
}

bool whetherZero(double** gaussMatrix, int diagonalIndex)
{

	const double E = pow(10, -6);

	if (fabs(gaussMatrix[diagonalIndex][diagonalIndex]) < E)
		return true;

	return false;

}

void swapColumns(double**& gaussMatrix, double* solutionVector, int size, int firstToSwap, int secondToSwap)
{
	double tempVec = 0.0;

	for (int i = 0; i < size; i++)
	{
		tempVec = gaussMatrix[i][firstToSwap];
		gaussMatrix[i][firstToSwap] = gaussMatrix[i][secondToSwap];
		gaussMatrix[i][secondToSwap] = tempVec;

	}

	tempVec = solutionVector[firstToSwap];
	solutionVector[firstToSwap] = solutionVector[secondToSwap];
	solutionVector[secondToSwap] = tempVec;

}

pair <int,int> findMaxInMatrix(double**& gaussMatrix, int size, int iteratorValue)
{
	double max = gaussMatrix[iteratorValue][iteratorValue];

	pair <int,int> ColRowIndex;

	for (int i = iteratorValue; i < size; i++)
	{

		for (int j = iteratorValue; j < size; j++)
		{
			if (gaussMatrix[i][j] > max)
				{
                max = gaussMatrix[i][j];
                ColRowIndex.first=i;
                ColRowIndex.second=j;
				}
		}

	}

	return ColRowIndex;

}


double* reverseProcedure(double** gaussMatrix, int size)
{
	double* solutionVector = new double[size];

	solutionVector[size - 1] = gaussMatrix[size - 1][size] / gaussMatrix[size - 1][size - 1];

	for (int i = size - 2; i >= 0; i--)
	{
		double sum = 0.0;
		for (int j = i + 1; j < size; j++)
			sum += gaussMatrix[i][j] * solutionVector[j];
		solutionVector[i] = (gaussMatrix[i][size] - sum) / gaussMatrix[i][i];
	}

	return solutionVector;

}

double* gaussEliminationBasic(double** gaussMatrix, int size)
{
	double multiplier = 0.0;

	for (int k = 0; k < size - 1; k++)
	{

		if (whetherZero(gaussMatrix, k) == true)
		{
			return nullptr;
		}

		gaussStep(gaussMatrix, size, k);

	}

	if (gaussMatrix[size - 1][size - 1] == 0)
	{
		if (gaussMatrix[size - 1][size] != 0) cout << "Uklad jest sprzeczny" << endl;
		else cout << "Uklad nieoznaczony" << endl;
		return nullptr;
	}

	double* tempVec = reverseProcedure(gaussMatrix, size);

	return tempVec;

}




/*double* gaussEliminationBasic(double** gaussMatrix, int size)
{
double multiplier=0.0;
double tempVec [size][size+1];
double* solutionVector = new double[size];


for (int i=0; i<size;i++)
{
	for (int j=0; j<size+1;j++)
	{
		tempVec[i][j]=i+j+1;
	}

}

	for (int k = 1; k < size; k++)
	{

for (int i = k + 1; i <= size; i++)
		{
			 multiplier = tempVec[i][k]/ tempVec[k][k];

			tempVec[i][k] = 0;
			for (int j = k + 1; j <= size - 1; j++)
				tempVec[i][j] = tempVec[i][j] - multiplier * tempVec[k][j];


		}
	}


	solutionVector[size-1] = tempVec[size-1][size] / tempVec[size-1][size-1];



	for (int i = size - 1; i >= 0; i--)
	{
		double sum = 0.0;
		for (int j = i + 1; j <= size; j++)
			sum += tempVec[i][j] * solutionVector[j];
		solutionVector[i] = (tempVec[size-1][size] - sum) / tempVec[i][i]; // a[i][i]<>0
	}

	return solutionVector;
}


*/

void checkData(double** gaussMatrix)
{
	gaussMatrix[0][0] = 3;
	gaussMatrix[0][1] = -2;
	gaussMatrix[0][2] = 0;
	gaussMatrix[0][3] = 2;
	gaussMatrix[0][4] = -14;

	gaussMatrix[1][0] = 1.5;
	gaussMatrix[1][1] = -2;
	gaussMatrix[1][2] - 2;
	gaussMatrix[1][3] = 5;
	gaussMatrix[1][4] = -15;

	gaussMatrix[2][0] = 0;
	gaussMatrix[2][1] = -1.5;
	gaussMatrix[2][2] = -7;
	gaussMatrix[2][3] = 6;
	gaussMatrix[2][4] = -8;

	gaussMatrix[3][0] = 3;
	gaussMatrix[3][1] = -3.5;
	gaussMatrix[3][2] = -5;
	gaussMatrix[3][3] = 4;
	gaussMatrix[3][4] = -16;
	gaussMatrix[1][2] = -2;

}

double* gaussRowPivot(double** gaussMatrix, int size)
{
	double positionToSwap = 0;
	for (int i = 0; i < size - 1; i++)
	{
		positionToSwap = findMaxInRow(gaussMatrix, size, i);
		if (positionToSwap != i)
			swapRows(gaussMatrix, size, positionToSwap, i);
		gaussStep(gaussMatrix, size, i);

	}

	double* tempVec = reverseProcedure(gaussMatrix, size);

	return tempVec;

}

void display(double** gaussMatrix, int size)
{

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size + 1; j++)
		{
			if (j != size && j != size - 1)
				cout << gaussMatrix[i][j] << "x" << j + 1 << " + ";
			else
				if (j == size - 1)
					cout << gaussMatrix[i][j] << "x" << j + 1 << " = ";
				else
					if (j == size)
						cout << gaussMatrix[i][j];

		}
		cout << "\n";
	}


}

double *gaussFullChoice(double ** gaussMatrix, double * solutionVector, int size)
{

pair <int,int> pairToSwapColRow;

for (int i=0; i<size-1;i++)
{
        pairToSwapColRow=findMaxInMatrix(gaussMatrix,size,i);

        if (pairToSwapColRow.first!=i)
            swapColumns(gaussMatrix,solutionVector,size,pairToSwapColRow.first,i);
        if (pairToSwapColRow.second!=i)
            swapRows(gaussMatrix,size,pairToSwapColRow.second,i);

         gaussStep(gaussMatrix,size,i);


}

double *tempVec=reverseProcedure(gaussMatrix,size);

return tempVec;
}

int main()
{
	int size = 4;
	int choice;

	double** gaussMatrix = initializeMatrix(size);

	try
	{

		do
		{
			cout << "Zdecyduj czy chcesz dane testowe czy wprowadzic wlasne" << endl;
			cin >> choice;
			switch (choice)
			{
			case 1:
			{
				cout << " Wybierz rozmiarmacierzy kwadratowej (3x3, 2x2, etc.)" << endl;
				cin >> size;

				gaussMatrix = enterData(size);
				break;
			}
			case 2:
				checkData(gaussMatrix);
				break;
			}
			display(gaussMatrix, size);

			cout << "Wybierz metode ktora chcesz rozwiazac rownanie liniowe. 1- Podstawowa Metdoa Eliminacji Guassa, 2- Metoda Eliminaji Gaussa z wyborem wierszy/kolumn, 3- metoda eliminacji Gaussa z pelnym wyborem elementu podstawowego." << "\n";
			cin >> choice;

			double* mySOlution = new double[size];

			for (int i = 0; i < size; i++)
			{
				mySOlution[i] = 0;
			}

			switch (choice)
			{
			case 1:
			{

				mySOlution = gaussEliminationBasic(gaussMatrix, size);
				if (mySOlution != nullptr)
				{
					cout << "Wektor rozwiazan gaussem podstawowym" << endl;

					for (int i = 0; i < size; i++)
					{
						cout << "x" << i + 1 << " :" << mySOlution[i] << endl;
					}
					break;
				}

				else
					cout << "Metoda podstawowa nie da sie rozwiazac tego rownania" << endl;
				break;
			}

			case 2:
			{

				mySOlution = gaussRowPivot(gaussMatrix, size);
				cout << "XD" << endl;
				if (mySOlution != nullptr)
				{
					cout << "Wektor rozwiazan gaussem wybor w rzedzie" << endl;

					for (int i = 0; i < size; i++)
					{
						cout << "x" << i + 1 << " :" << mySOlution[i] << endl;
					}
					break;
				}
				break;
			}

			case 3:
			{
				mySOlution = gaussFullChoice(gaussMatrix,mySOlution,size);
				if (mySOlution != nullptr)
				{
					cout << "Wektor rozwiazan gaussem wybor pelny" << endl;

					for (int i = 0; i < size; i++)
					{
						cout << "x" << i + 1 << " :" << mySOlution[i] << endl;
					}
				}
				break;
			}

			default:
				cerr << "Zly numer" << endl;
			}


		} while (choice != 4);

	}

	catch (exception ex)
	{
		cerr << "Nastapil wyjatek " << ex.what();
	}

}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln

