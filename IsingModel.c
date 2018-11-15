#include <stdio.h>
#include <stdlib.h>

#define size 4

// function to intialize all spins to -1
void imInitAllDown(int matSpin[size][size])
{
	for (int i=0; i<size; i++)
	{
		for (int j=0; j<size; j++)
		{
			matSpin[i][j] = -1;
		}
	}
}

// function to intialize all spins to +1
void imInitAllUp(int matSpin[size][size])
{
	for (int i=0; i<size; i++)
	{
		for (int j=0; j<size; j++)
		{
			matSpin[i][j] = 1;
		}
	}
}

// function to intialize spins randomly
void imInitWarm(int matSpin[size][size])
{
	double dRan;

	for (int i=0; i<size; i++)
	{
		for (int j=0; j<size; j++)
		{
			dRan = rand()%2;
			if (dRan <= 0.5)
			{
			matSpin[i][j] = 1;
			}
			else matSpin[i][j] = -1;
		}
	}
}

//function to display spins
void displayMatSpin(int matSpin[size][size])
{
	for (int i = 0; i< size; ++i)
	{
		for (int  j= 0; j< size; ++j)
		{
			printf("%d ", matSpin[i][j]);
		}
		printf("\n");
	}
}


int main(int argc, char const *argv[]){


	int Mat[size][size];
	
	//imInitAllDown(matLattice, Rows);
	
	//imInitAllUp(matLattice, Rows);
	
	imInitWarm(Mat);
	displayMatSpin(Mat);
	
}