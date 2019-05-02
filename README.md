
# Sujet:
Calcul de densité d'état de particule pour la modélisation de nanoparticule transition de spin.

## Implementation Parrallèle avec OpenMP du modèle Ising:
Language de programmation : C 


### Compiler du projet 
  
```
 gcc -o mainOmpPar carlo_ising_Openmp.c -fopenmp -lm

```

```
export OMP_NUM_THREADS = <nb_thread> nb_thread max 16/proc

```
### Exécution 

```
  ./mainOmpPar <nb_iter de MC> <température>

```
