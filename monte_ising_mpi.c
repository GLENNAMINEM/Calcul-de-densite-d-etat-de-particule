#include <stdio.h>
#include <mpi.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "carloMPI.h"




int main(int argc, char**argv)
{

  //int N = atoi(argv[2]);
  int i,j,spin[N][N],runs,size,rank,tag1=0, T;
  int k=0;
  double en_old,en_new,H,r,beta;

  beta = 1/((1.38064852*pow(10,-23))*T);
    
    
    MPI_Status sta;
    MPI_Request req;
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    runs = atoi(argv[1]);
    time_t t = time(NULL);
    int run,cnt=0;
    T = atoi(argv[2]);
    int *buf= (int*)malloc(sizeof(int)*runs*4);
    int* tab = NULL;
    tab = malloc(sizeof(int)*runs/*((int)pow(2,N))*/*4);
    int *ta=malloc(sizeof(int)*runs/*((int)pow(2,N))*/*4);


  // initial fill
  for (i=0; i<N; i++)
  {
    for (j=0; j<N; j++)
    {   
     srand(t+t*rank); //ne fonction du temps et du rang
      spin[i][j] = updown(rank);

    }
  }

 

  //srand(t*rank); //ne fonction du temps et du rang

    for(run = 0; run<runs; run++)
    {
      

        monte_carlo(spin,tab,run,rank,&cnt,beta);
  

   }


   //communication to send array

   if(rank != 0){


        MPI_Send(tab, cnt, MPI_INT, 0, tag1, MPI_COMM_WORLD);


                 }

   if(rank == 0 && size>1){
 
       for(int i=1;i<size;i++){

        MPI_Recv(buf, runs*4, MPI_INT,i, tag1, MPI_COMM_WORLD, &sta);
  ta = buf;
        fusion(tab, ta,&cnt, &ta[0]); 

    
                     }
   ising_output(tab,cnt);
   display(tab,&cnt);
   }

   MPI_Finalize();

  return 0;
}
