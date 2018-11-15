# Groupe-Calcul-de-densit-d-tat-de-particule-pour-la-mod-lisation-de-nanoparticule-transition-de-s


Soit une particule composée de n atomes. Le calcul de densité d’état à une complexité de 2n. Afin de modéliser une nano-particule SCO, les physiciens peuvent utiliser des techniques de Monte Carlo. Ainsi la méthode la plus couramment utilisée est la méthode de Monte-Carlo Metropolis. Celle-ci approche directement les quantités physiques souhaitées telle que la température pour une particule en fonction d’autres paramètres.

Une autre technique consiste à approcher la densité d’état de la particule par la technique de Monte Carlo Entropic Sampling [1,2] et ainsi pouvoir calculer directement une quantité physique quelque soit les paramètres de l’équation.

Dans le cas de particule 1D ou 2D (n = n1 × n2) dont les atomes sont disposés sur une grille cartésienne, Il est possible de calculer la densité d’état de manière exacte avec une complexité de n1(7/2) * 2n2 au lieu de 2(n1 × n2) . Dans [3,4] cette technique a été employée et permet une plus grande précision pour le calcul des quantités physiques..

Dans ce projet nous nous intéressons à la technique de Monte-Carlo Entropic Sampling pour approcher la densité d’état. L’objectif est de comparer cette technique d’approximation en terme de précision numérique et de complexité arithmétique avec la méthode de programmation dynamique employée dans [3,4]. La parallélisation de cette méthode et ces performances seront discutées au second semestre.

Mots clefs : méthode de Monte Carlo, Spin crossover nano particle, programmation 
