#include <stdio.h>
#include <time.h>
#include <stdlib.h>
//#include<omp.h>
#define N 5

 int cnt=0; 


//add new configuration in array

void add_bloc(int * tab,int a,int b, int c){


 int faux=0;
 int p,test=0;


	if(cnt==0){
		test++;
	}


 for(p=0;p<cnt;p=p+4){

	if(tab[(p)]==a && tab[(1)+(p)]==b && tab[(2)+(p)]==c ){

	   tab[(3)+(p)]+= 1;
	}
	
	else  { faux+=4;
		if(faux == cnt)
		test++;}
	
       }

	
      if(test){   
			
		tab[cnt]=a;tab[(1)+(cnt)]=b;tab[(2)+(cnt)]=c;
		tab[(3)+(cnt)]=1;
			cnt+=4;
	}

	          		
}
//display array

void display(int* tab, int cnttt){

     int j;

for(j=0;j<cnttt;j=j+4){

  printf("m=%d c=%d s=%d z=%d\n",tab[j],tab[1+j],tab[2+j],tab[3+j]);

  	}

 }

//fusion to array

 void fusion(int *tab, int *buf, int size){
 

 for(int i=0;i<size;i+=4){

    for(int j=0;j<size;j+=4){

     add_bloc(tab,buf[j],buf[j+1], buf[j+2]);}


     }


 }

// returns up (1) or down (-1)
int updown(int rang)
{
  int t=clock();
  double randomNumber;
  srand(rang*t);
  randomNumber = (rand()%N)/(N-1);
  if (randomNumber < 0.5) return (1);
  else return -1;
}


// Calculate energy
double energy(int spin[N][N])
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


//Méthode (type node) qui nous permet de retourner un noeud de "z", ex: z[m][s][c]
 int* Method_Approach(int matSpin[N][N])
{

  int *t=malloc(sizeof(int)*3);
  int i,j,c1=0, c2=0, c3=0 , c4=0;
  int cP=0, mP=0;

/*===============Calcul constante m' : les spin vers le bas dans la grill============*/

for ( i = 0; i< N; ++i)
  for(j=0; j< N; ++j)
    if(matSpin[i][j] == -1)
      mP++;


/*==============Calcul de la constante C' : les spin vers bas sur les côtés dans la grill=================*/

  for (i = 1; i < N-1; ++i)
  {
    if(matSpin[i][0] == -1)
      c1++;   // spin vers le bas sur la gauche

    if(matSpin[i][N-1] == -1)
      c3++;  // nbr de spin vers le bas sur la haute
  }


  for (j = 0; j < N; ++j)
    {
      if(matSpin[0][j]== -1)
        c2++;  // nbr de spin vers le bas sur la droite

      if(matSpin[N -1][j] == -1)
      c4++;  // nbr de spin vers le bas sur le bas
    }


/*==================Calcul de la constante S' : le nombre de paires d'atomes adjacents ayant différentes spins========*/
    int s = 0;

    for (i = 0; i < N; ++i){
      for(j = 0; j < N; ++j){

        if(matSpin[i][j] != matSpin[i][j+1] && j != N-1  ){  //voisin à droite
          s++;
        }
	if(matSpin[i][j] != matSpin[i+1][j] && i != N-1){ //voisin en bas
          s++;
	}
      }
    }




  cP = c1+c2+c3+c4;

 
  t[0]=mP;t[1]=cP;t[2]=s;
  

  return t;
}

// METROPOLIS MONTE_CARLO

void monte_carlo(int spin[N][N],int* tab,int run,int rang){

  int ai,aj;
  int t = clock();
  float tt1,tt2;
  double en_old,en_new,H,r;
  int *ta=malloc(sizeof(int)*3);
  
	srand48(5123*rang);
      //srand(t*rang);

	ai=rand()%(N);aj=rand()%(N);
      //printf("i=%d j=%d\n",ai,aj);
        spin[ai][aj];
   
       en_old = energy(spin);  // energy before flip


      spin[ai][aj] = -spin[ai][aj];// flip
 
      en_new = energy(spin);  // energy after flip

      H = en_new - en_old;    // difference in energy


      if (H>0)
      {
            r = (rand()%N)/(N-1);  
            if (r>exp(-H)){
             //printf("pas pris i=%d j=%d\n",ai,aj);
		 spin[ai][aj] = -spin[ai][aj];  // Undo flip

            }else {
		 ta=Method_Approach(spin);
		 add_bloc(tab,ta[0],ta[1],ta[2]);
		}
      }else {   
		ta=Method_Approach(spin);	
		add_bloc(tab,ta[0],ta[1],ta[2]);
     }

  
 free(ta);
}
