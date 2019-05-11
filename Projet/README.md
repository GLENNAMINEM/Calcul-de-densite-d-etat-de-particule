
# Sujet:
Calcul de densité d'état de particule pour la modélisation de nanoparticule transition de spin.

## Implementation Parrallèle avec OpenMP et MPI du modèle Ising:
Language de programmation : C 


### Compiler du projet 
  
 #### Compilation Séquentiel 
  
  
```
 gcc carlo_ising.c -o carlo -lm

```
  #### Compilation Parallèle avec OpenMP
```
 gcc -o mainOmpPar carlo_ising_Openmp.c -fopenmp -lm

```

```
export OMP_NUM_THREADS = <nb_thread> nb_thread max 16/proc

```
#### Compilation Parallèle avec MPI

```
 mpicc -o mainMpi carlo_ising_mpi.c -lm

```
### Exécution 

```
  ./mainOmpPar <nb_iter de MC> <température>

```
####
```
  mpirun -np <nb_Proc> ./mainMpi <nb_iter de MC> <température>

```

