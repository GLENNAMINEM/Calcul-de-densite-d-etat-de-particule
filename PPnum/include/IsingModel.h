typedef struct node* node;

struct node  
{
	int m[0];
	int s[1];
	int c[2];
};

static int nc,nl;

void imInitWarm(int matSpin[nl][nc]);

void displayMatSpin(int matSpin[nl][nc]);

node Method_Approach(int matSpin[nl][nc],node nd);

int MC_Sampling(node z, node newZ, int Mat[nl][nc], int nIter);
