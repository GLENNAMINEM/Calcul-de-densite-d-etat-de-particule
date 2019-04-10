#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "list.h"
#define N 6     // grid size
#define runs 10   // number of Monte Carlo simulations


// returns up (1) or down (-1)
int updown()
{
  double randomNumber;
  randomNumber = rand()%2;
  if (randomNumber < 0.5) return (-1);
  else return 1;
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
node Method_Approach(int matSpin[N][N])
{
  node z;/// = malloc(sizeof(*z));
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

    for (i = 0; i < N-1; ++i){
      for(j = 0; j < N-1; ++j){
        if(matSpin[i][j] != matSpin[i][j+1]){
          s+=1;
        }
      }
    }

          
        
    for (j = 0; j < N-1; ++j){
      for(i = 0; i < N-1; ++i){
        if(matSpin[i][j] != matSpin[i+1][j]){
          s+=1;
        }
      }
    }         


  cP = c1+c2+c3+c4;     

  z.m = mP;
  z.s = s;
  z.c = cP;
  //z.conf;

  return z; // retourne noeud
/*===================================================*/
}


void monte_carlo(int spin[N][N],ListNode *list_node,int run){

    int ai,aj,*pt;
    double en_old,en_new,H,r;
    time_t t;
    node d;

      //srand(time(NULL));
      //srand48(5123);
      //srand((unsigned) time(&t));
    ai=rand()%(N-1);
    aj=rand()%(N-1);

    spin[ai][aj];
 
    en_old = energy(spin);  // energy before flip

    // flip
    spin[ai][aj] = -spin[ai][aj];

    en_new = energy(spin);  // energy after flip

    H = en_new - en_old;    // difference in energy

    if (H>0)
    {
       r = (rand()%N)/(N-1);  //drand48();
       if (r>exp(-H)){
        //printf("ai=%d aj=%d faux\n",ai,aj);
        spin[ai][aj] = -spin[ai][aj];  // Undo flip

        }else {
        //printf("ai=%d aj=%d :vrai 1\n",ai,aj);
          d = Method_Approach(spin);
          //insertion(list_node, d.m,d.s,d.c);
          searchListCmdElment(list_node, d.m,d.s,d.c);
        }
    }    
    else {
    //printf("ai=%d aj=%d :vrai 2\n",ai,aj);
         d = Method_Approach(spin);
              insertion(list_node, d.m,d.s,d.c);
              searchListCmdElment(list_node, d.m,d.s,d.c);
     }
}


int main(int argc , char** argv)
{
  ListNode *list_node = initialisation();
  //int i,j,run,spin[N][N];//spinAccum[N][N][N];
  int i,j,go,run,spin[N][N];
  //node *z;


  //srand48(5123);
  //FILE *data;

  // initial fill
  for (i=0; i<N; i++)
  {
    for (j=0; j<N; j++)
    {
      spin[i][j] = updown();
      //spinAccum[0][i][j] = spin[i][j];
    }
  }
  
  for(run = 0; run<runs; run++)
  {
    monte_carlo(spin,list_node,run);
    //printf("Completed run #%i\n",run);

  
} 
 afficherListCmd(list_node);
 free(list_node);
//fclose(data);
  return 0;
}
