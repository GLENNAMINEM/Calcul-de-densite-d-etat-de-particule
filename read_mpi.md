 compilation: mpicc monte_ising_mpi.c -lm
 execution : mpiexec -n nb_pro ./a.out <nb_iterations> <température>


 gnuplot>
 p 'ising-output_Par4.dat' using 1:4 w p ls 7
