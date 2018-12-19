#include <stdio.h>
#include <stdlib.h>

int size;

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


void Method_Approach(int matSpin[size][size])
{
	int i,j,c1=0,	c2=0, c3=0 , c4=0, SpinBord=0;

	int cP=0, mP=0;


/*===============Calcul constante m' : les spin vers le bas dans la grill============*/

for ( i = 0; i< size; ++i)
	for(j=0; j< size; ++j)
		if(matSpin[i][j] == -1)
			mP++;


/*==============Calcul de la constante C' : les spin vers bas sur les côtés dans la grill=================*/

	for (i = 1; i < size-1; ++i)
	{
		if(matSpin[i][0] == -1)
			c1++;		// spin vers le bas sur la gauche

		if(matSpin[i][size -1] == -1)
			c3++;  // nbr de spin vers le bas sur la haute
	}	

	
	for (j = 0; j < size; ++j)
		{
			if(matSpin[0][j]== -1)
				c2++;  // nbr de spin vers le bas sur la droite

			if(matSpin[size -1][j] == -1)
			c4++;  // nbr de spin vers le bas sur le bas						
		}


/*==================Calcul de la constante S' : le nombre de paires d'atomes adjacents ayant différentes spins========*/
		int s = 0;

		for (i = 0; i < size-1; ++i)
			for(j = 0; j < size-2; ++j)
				if(matSpin[i][j] != matSpin[i][j+1])
					s+=1;
					
				
		for (i = 0; i < size-1; ++i)
			for(j = 0; j < size-2; ++j)
				if(matSpin[i][j] != matSpin[i+1][j])
					s+=1;

	cP = c1+c2+c3+c4;			
	printf("c1 %d\n", c1);
	printf("c3 %d\n", c3);
	printf("c2 %d\n", c2);
	printf("c4 %d\n", c4);
	printf("c\' vaut %d\n", cP);
	printf("m\' vaut %d\n", mP);
	printf("s\' vaut %d\n", s);
	printf("\n");

/*===================================================*/
}

int main(int argc, char const *argv[]){

	size = atoi(argv[1]);
	int Mat[size][size];
	
	//imInitAllDown(matLattice, Rows);
	
	//imInitAllUp(matLattice, Rows);
	
	imInitWarm(Mat);
	Method_Approach(Mat);
	displayMatSpin(Mat);
	
}