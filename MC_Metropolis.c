void  MC_Metropolis(int matSpin[size][size], double dBeta)
{
	int i,j,iPosLine,iPosCol,iNegLine,iNegCol, changed = 0;
	int iOldSpin,iNewSpin,iSpinSum;
	int iOldEnergy,iNewEnergy;
	double dEnergyDiff;
	// utilisation d'une minuterie pour générer le générateur de nombres aléatoires
	double dRan;
	srand( time(NULL) );
	/* Boule sur les sites */
	for (i=0;i<size;i++)
	{
		for (j=0;j<size;j++)
		{
			/* conditions aux limites périodiques */
			iPosLine = (i+1) % size;
			iPosCol = (j+1) % size;
			iNegLine = (i+size-1) % size;
			iNegCol = (j+size-1) % size;
			iOldSpin = matSpin[i][j];
			iNewSpin = - iOldSpin;

			/* Somme des voisins iSpinSum */
			iSpinSum = matSpin[i][iPosCol] + matSpin[iPosLine][j] + matSpin[i][iNegCol] + matSpin[iNegLine][j];
			iOldEnergy = - iOldSpin * iSpinSum;
			iNewEnergy = - iNewSpin * iSpinSum;
			dEnergyDiff = dBeta * (iNewEnergy - iOldEnergy);
			
			/* beta = J/kT ---> K:  constante de Boltzmann k ≈ 1,380 648 52 × 10^−23 J*(K^−1) && T: Température*/
			/* Faire la mise à jour */

			dRan = rand();
			if ( (dEnergyDiff <= 0.0) || (exp(-dEnergyDiff) > dRan ) )
			{
				/* Accept the change */
				matSpin[i][j] = iNewSpin;
				printf("%f\n", dEnergyDiff);
				changed++;
			}

		}
	}
	printf("Changement sur un spin quelconque %d\n", changed);

/* Fin du Boucle sur les sites */
}