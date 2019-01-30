
typedef struct  
{
	int m;
	int s;
	int c;
}node ;

static int nc,nl;

void imInitWarm(int matSpin[nl][nc]);

void displayMatSpin(int matSpin[nl][nc]);

node Method_Approach(int matSpin[nl][nc],node nd);

int MontCarlo_Method(node z, node newZ, int Mat[nl][nc], int nIter);
