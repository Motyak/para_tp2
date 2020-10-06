#include "Decriptor.h"

#include <iostream>

// g++ -o bin/exo3 src/MD5/md5.cpp src/Decryptor.cpp src/exo3.cpp --std=c++11 -lpthread
int main()
{
    const int NB_OF_CORES = 4;

    Decryptor decryptor(NB_OF_CORES);

    return 0;
}