#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/IsingModel.h"


// function to intialize spins randomly
void randomly_fill_spin(int matSpin[nl][nc])
{
	double dRan;
	//srand( time(NULL) );
	for (int i=0; i<nl; i++)
	{
		for (int j=0; j<nc; j++)
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
void displayMatSpin(int matSpin[nl][nc])
{
	for (int i = 0; i< nl; ++i)
	{
		for (int  j= 0; j< nc; ++j)
		{
			printf("%d ", matSpin[i][j]);
		}
		printf("\n");
	}
}


node Method_Approach(int matSpin[nl][nc],node nd)
{
	int i,j,c1=0,	c2=0, c3=0 , c4=0, SpinBord=0;
	int cP=0, mP=0;

/*===============Calcul constante m' : les spin vers le bas dans la grill============*/

for ( i = 0; i< nl; ++i)
	for(j=0; j< nc; ++j)
		if(matSpin[i][j] == -1)
			mP++;


/*==============Calcul de la constante C' : les spin vers bas sur les côtés dans la grill=================*/

	for (i = 1; i < nl-1; ++i)
	{
		if(matSpin[i][0] == -1)
			c1++;		// spin vers le bas sur la gauche

		if(matSpin[i][nc-1] == -1)
			c3++;  // nbr de spin vers le bas sur la haute
	}	

	
	for (j = 0; j < nc; ++j)
		{
			if(matSpin[0][j]== -1)
				c2++;  // nbr de spin vers le bas sur la droite

			if(matSpin[nl -1][j] == -1)
			c4++;  // nbr de spin vers le bas sur le bas						
		}


/*==================Calcul de la constante S' : le nombre de paires d'atomes adjacents ayant différentes spins========*/
		int s = 0;

		for (i = 0; i < nl-1; ++i){
			for(j = 0; j < nc-1; ++j){
				if(matSpin[i][j] != matSpin[i][j+1]){
					s+=1;
				}
			}
		}

					
				
		for (j = 0; j < nc-1; ++j){
			for(i = 0; i < nl-1; ++i){
				if(matSpin[i][j] != matSpin[i+1][j]){
					s+=1;
				}
			}
		}					


	cP = c1+c2+c3+c4;			

	nd->m[0] = mP;
	nd->s[1] = s;
	nd->c[2] = cP;

	return nd;
/*===================================================*/
}

int MC_Sampling(node Z, node NewZ, int Mat[nl][nc], int nIter){

	int config = 0;
	for (int i = 0; i < nIter; ++i)
	{
		Z = Method_Approach(Mat,Z);
		
		printf("z[%d %d %d]\n", Z->m[0], Z->s[1], Z->c[2]);
		
		randomly_fill_spin(Mat);

		NewZ = Method_Approach(Mat,NewZ);

		if ( (Z->m[0]!=NewZ->m[0]) || (Z->s[1]!=NewZ->s[1]) || (Z->c[1]!=NewZ->c[1]))
		{
			config++;
		}
	}
	return config;
}

int main(int argc, char const *argv[]){

	nl = atoi(argv[1]);
	nc = atoi(argv[2]);
	int nb_iter = atoi(argv[3]);
	int Total_config;
	clock_t start_t , end_t;
	int Mat[nl][nc];
	

	node z = malloc(3*sizeof(struct node));
	node newZ = malloc(3*sizeof(struct node));

	start_t = clock();
	Total_config = MC_Sampling(z,newZ,Mat,nb_iter);
	end_t = clock();

	printf("Nombre de Config = %d \n", Total_config);
	printf("Temps d'éxecution %f\n", (double)(end_t - start_t)/CLOCKS_PER_SEC);
	//imInitAllDown(matLattice, Rows);
	
	free(z);
	free(newZ);


	//imInitAllUp(matLattice, Rows);	
	
}