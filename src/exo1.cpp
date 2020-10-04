#include "ThreadPool.h"

// g++ -o bin/exo1 src/ThreadPool.cpp src/exo1.cpp --std=c++11 -lpthread
int main()
{
    /* Note : L'ajout des sous-résultats ne se fait
        pas de manière séquentielle, donc uniquement la
        dernière valeur affichée sera cohérente.
    */

    const int NB_OF_CORES = 2;

    ThreadPool pool(NB_OF_CORES);

    return 0;
}