#include <stdio.h>
#include <mpi.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "include.h"




int main(int argc, char**argv)
{

  //int N = atoi(argv[2]);
  int i,j,spin[N][N],runs,size,rank,tag1=0;
  int k=0;
  double en_old,en_new,H,r;

  
    MPI_Status sta;
    MPI_Request req;
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    runs = atoi(argv[1]);
    int t = clock();
    int run,o;
    int *buf= (int*)malloc(sizeof(int)*runs*4);
    int* tab = NULL;
    tab = malloc(sizeof(int)*runs/*((int)pow(2,N))*/*4);
    //int *ta=malloc(sizeof(int)*runs/*((int)pow(2,N))*/*4);

  srand(t*rank); //ne fonction du temps et du rang
  // initial fill
  for (i=0; i<N; i++)
  {
    for (j=0; j<N; j++)
    { 	
      spin[i][j] = updown(rank);

    }
  }

 

  //srand(t*rank); //ne fonction du temps et du rang

    for(run = 0; run<runs; run++)
    {
      //  #pragma omp parallel num_threads(2) private(ta)
      // {  	
	//srand(t*omp_get_thread_num());

        monte_carlo(spin,tab,run,rank);
  

       /*   if( runs -run == 1){
            #pragma omp critical
           {  

               fusion(tab, ta, cnt); 
               printf(" je suis la %d\n",omp_get_thread_num());
            }

                            } */
      //}
   }


//communication to send array

   if(rank != 0){

	//printf("je suis %d et cnt=%d\n",rank,cnt);

        MPI_Send(tab, runs*4, MPI_INT, 0, tag1, MPI_COMM_WORLD);

   free(tab);
                 }

   if(rank == 0){
 
       for(int i=1;i<size;i++){

        MPI_Recv(buf, runs*4, MPI_INT,i, tag1, MPI_COMM_WORLD, &sta);
        fusion(tab, buf, cnt); 

	                       }
   }


  if(rank == 0){
	//printf("je suis %d et cnt=%d\n",rank,cnt);
   display(tab,cnt);
   free(buf);
   //free(tab);

  }

   //free(tab);
   MPI_Finalize();

  return 0;
}
