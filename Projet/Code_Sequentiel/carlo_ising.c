#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "include.h"


int main(int argc, char**argv)
{

  int n=0;
  int i,j,spin[N][N],runs, Zmax=0, T;
  int ai,aj;
  double en_old,en_new,H,r;
  double beta ;
  int* tab = NULL;
  //long double epsilon = pow(10,-77); // 17x17(-87) ; 18x18(-98) , 19x19 (- 109) , 20x20( -121)
  //long double Propa1  = 0.00 ;
  //long double Propa2 = 0.00;
  //int e = 3 ; 
  runs = atoi(argv[1]);

  tab = malloc(runs*4*sizeof(int));// malloc(sizeof(int)*runs*4);

  // initial fill
  for (i=0; i<N; i++)
  {
    for (j=0; j<N; j++)
    {
      spin[i][j] = updown();
    }
  }
  
  
  beta = 1/((1.38064852*pow(10,-23))*T);

  for(int run = 0; run<runs; run++)
    { 
      int Z = 0;  
      for( int e = 3 ; e < cnt; e += 4)
     { 

      Z += tab[e] ; 
     } 

     if ( Z >= pow(2 , N*N) ) break ;
   
     else monte_carlo(spin,tab,run,beta);

  }


   ising_output(tab,cnt);

   free(tab);

  return 0;
}
