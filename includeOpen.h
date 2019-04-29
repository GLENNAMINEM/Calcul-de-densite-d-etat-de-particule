#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

#define N 5
//#define runs 100 // number of Monte Carlo simulations

 int cnt=0;
int ok = 0;

//add new configuration in array

void add_bloc(int * tab,int a,int b, int c){

	int faux=0;
	int p,test=0;

    	if(cnt==0){
    		test++;
    	}


     for(p=0;p<cnt;p=p+4){

    	   if(tab[(p)]==a && tab[(1)+(p)]==b && tab[(2)+(p)]==c){
    	      tab[(3)+(p)]+= 1;
    	   }
    		else{ 
         			faux+=4;
      				if(faux == cnt) test++;
        		}

      }
    
       if(test){

    		  tab[cnt]=a;tab[(1)+(cnt)]=b;tab[(2)+(cnt)]=c;
    		  tab[(3)+(cnt)]=1;
    			cnt+=4;
       	}

  }

  

//output as file array

void ising_output(int* tab, int cnttt){

	int j;
	long long Z = 0;

	FILE *data;

	data = fopen("ising-output_Par4.dat","w");

	for(j=0;j<cnttt;j=j+4){

		fprintf(data,"%i\t%i\t%i\t%i\n",tab[j],tab[1+j],tab[2+j],tab[3+j]);
		printf("%llu\n",Z+=tab[3+j]);
	}

  fclose(data);
}


// returns up (1) or down (-1)
int updown()
{
  double randomNumber;
  randomNumber = rand()%2;
  if (randomNumber < 0.5) return (1);
  else return -1;
}

// Calculate energy
double ith_energy(int spin[N][N])
{
  int i,j;
  double E=0.;

  for (i=0; i<N; i++)
    for (j=0; j<N; j++)
    {
      if (i-1>=0) E -= 0.5*(spin[i][j]*spin[i-1][j]-1.);
      if (j-1>=0) E -= 0.5*(spin[i][j]*spin[i][j-1]-1.);
      if (i+1<N)  E -= 0.5*(spin[i][j]*spin[i+1][j]-1.);
      if (j+1<N)  E -= 0.5*(spin[i][j]*spin[i][j+1]-1.);
    }

  return E;
}



 int* Method_Approach(int matSpin[N][N])
{

  int *t=malloc(sizeof(int)*3);
  int i,j; 
  int cP=0, mP=0;

/*===============Calcul constante m : la somme des spins de la grill============*/

for ( i = 0; i< N; ++i)
  for(j=0; j< N; ++j)
    mP+=matSpin[i][j];


/*==============Calcul de la constante C : la somme des spins vers bas sur les côtés dans la grill=================*/

  for (i = 1; i < N-1; ++i)
  {
    //if(matSpin[i-1][0] == -1)
      cP+=matSpin[i-1][0];   // spin vers le bas sur la gauche

    //if(matSpin[i][N-1] == -1)
      cP+=matSpin[i][N-1];  // nbr de spin vers le bas sur la haute

    //if(matSpin[0][i]== -1)
      cP+=matSpin[0][i];  // nbr de spin vers le bas sur la droite

    //if(matSpin[N -1][i-1] == -1)
      cP+=matSpin[N -1][i-1];  // nbr de spin vers le bas sur le bas
  }


/*==================Calcul de la constante S : la somme des spins paires d'atomes adjacents ayant différentes sens========*/
    int s = 0;

    for (i = 0; i < N; ++i){
      for(j = 0; j < N; ++j){

        if(matSpin[i][j] != matSpin[i][j+1] && j != N-1  ){  //voisin à droite
          s+=matSpin[i][j];
        }
		if(matSpin[i][j] != matSpin[i+1][j] && i != N-1){ //voisin en bas
          s+=matSpin[i][j];
		}
      }
    }



  t[0]=mP;t[1]=cP;t[2]=s;


  return t;
}

// METROPOLIS MONTE_CARLO

void monte_carlo(int spin[N][N],int* tab,int run, double beta){


  	int ai,aj;

  	int cnt2 = 0;
  	double en_old,en_new,deltaE,r,Etotal = 0.;
  
  	int *ta=malloc(sizeof(int)*3);


	srand48(5123);

      ai=rand()%(N);
      aj=rand()%(N);
  

        spin[ai][aj];

       en_old = ith_energy(spin);  // energy before flip


      spin[ai][aj] = -spin[ai][aj];// flip

      en_new = ith_energy(spin);  // energy after flip
      
      Etotal += en_new;

      deltaE = en_new - en_old;    // difference in energy

     //#pragma omp critical 
     //{  
        if (deltaE>0)
        {
           r = drand48();
           if (r < exp(-deltaE*beta)){
  		        spin[ai][aj] = -spin[ai][aj];  // Undo flip

           }else {
           		
  		        ta=Method_Approach(spin);
             	
  		        add_bloc(tab,ta[0],ta[1],ta[2]);
            } 

  		  }
        else {
      		
              ta=Method_Approach(spin);
             
              add_bloc(tab,ta[0],ta[1],ta[2]);
            }  
            
      //}
  

 free(ta);
}


        