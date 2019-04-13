#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "include.h"




int main(int argc, char**argv)
{


  int i,j,spin[N][N],runs;
  int ai,aj;
  double en_old,en_new,H,r;
  int* tab = NULL;
  
	runs = atoi(argv[1]);

  tab=malloc(sizeof(int)*runs*4);


  // initial fill
  for (i=0; i<N; i++)
  {
    for (j=0; j<N; j++)
    {
      spin[i][j] = updown();

    }
  }
  	 


  for(int run = 0; run<runs; run++)
  {

    monte_carlo(spin,tab,run);
  
  } 

   display(tab,cnt);

   free(tab);

  return 0;
}
