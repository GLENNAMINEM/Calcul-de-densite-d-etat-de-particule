#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>

// on a une matrice dont les spins sont tous de mêmes signe, on change le signe d'un spin sur chaque condition et on calcul les configurantions msc à chaque changement de spin.


//array boolean
bool **array(bool **tab;int n,m){

  for(int i=0;i<n;i++)
    for(int j=0;j<m;j++){
      
      tab[i][j]=false;
    }

      return tab;
}

//calcul energy state

double energy(bool** tab;int n,m,double J){
  
  double E=0;
    
  for(int i=0;i<n;n++)
    for(int j=0;j<m;m++)

      E+=tab[i][j];
  
      return J*E;
}
//research m,s,c,z

int* research(bool**tab;int n,m,ai,aj){

  int mscz[3];

  for(int i=1;i<n;n++)
    for(int j=1;j<m;m++){


      if(ai==0 && aj==0 || ai==n && aj==0 || ai==0 && aj==m || ai==n && aj==m){

	mscz[0]=1;mscz[1]=2;mscz[2]=1;mscz[3]=4;
      }

	 
	if(ai=i && aj=1 || ai=1 && aj=j || ai=i && aj=m || ai=n et aj=j){
	  mscz[0]=1;mscz[1]=3;mscz[2]=1;mscz[3]=2*m+2*n-4;
	}

	else{mscz[0]=1;mscz[1]=4;mscz[2]=0;mscz[3]=n*m-2*n-2*m-8;  }

    }
  return mscz;
}

//monte_carlo

int *monte_carlo(bool** tab,int n,int m;double T,double K,double J,double Si,double Sj){

  
  int* z,c,s,mscz[4]; 
  int ai(rand()%n-1),aj(rand()%m-1);
  double P(rand()%1);

  
  //generate alea
  srand(time(0));

  //changement spin signe
  tab[ai][aj]=true;
  
  if( energy(tab,n,m,J)<0){

    mscz=research(bool**tab;int n,m,ai,aj);

  }
  else{

    if(P<exp(-energy(tab,n,m,J)/K*T))
      
     mscz=research(bool**tab;int n,m,ai,aj);
  }  

  return mscz;
}




int main()
{







return 0;
}



