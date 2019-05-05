#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "include_mpi.h"



int main(int argc, char**argv)
{

  //int N = atoi(argv[2]);
  int i,j,spin[N][N],runs,size,rank,tag1=0;
  double en_old,en_new,H,r;

  
    MPI_Status sta;
    MPI_Request req;
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    runs = atoi(argv[1]);
    time_t t = time(NULL);
    int run,z=0,cnt=0;
    int *buf=NULL;
    int* tab = NULL;
    double t1,t2;
	
    buf= (int*)malloc(sizeof(int)*runs*4*(size-1));	
    tab = (int*)malloc(sizeof(int)*runs*4+1);


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

  
  for(int run = 0; run<runs; run++)
  { 
  	 int Z = 0;

    for( int e = 4 ; e < cnt; e += 4)
   { 

    Z += tab[e] ; 
   } 
   if ( Z ==  pow(2 , N*N) ) break ;
 
    else monte_carlo(spin,tab,run,rank,&cnt);

   //printf("Z=%d\n",Z);

   }


   //communication to send array
       t1 = MPI_Wtime();
   if(rank != 0){

        MPI_Send(tab, cnt, MPI_INT, 0, tag1, MPI_COMM_WORLD);

                 }

   if(rank == 0 && size>1){
 
       for(int i=1;i<size;i++){

        MPI_Recv(buf + runs*4*(i-1), runs*4, MPI_INT,i, tag1, MPI_COMM_WORLD, &sta);
             }

	t2=MPI_Wtime();
       for(int j=1;j<size;j++){

        fusion(tab, buf + runs*4*(j-1),&cnt, &buf[runs*4*(j-1)]); 

                     }


     ising_output(tab,cnt);
     display(tab,&cnt);
  	printf("MPI_Wtime %f\n", t2-t1);
   //free(buf);
   }
   //display(tab,&cnt);
   //ising_output(tab,cnt);
   //free(buf);
 //MPI_Barrier(MPI_COMM_WORLD);
   //free(tab);
   MPI_Finalize();

  return 0;
}
