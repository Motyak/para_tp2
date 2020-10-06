#include "Pipeline.h"

#include <iostream>

// g++ -o bin/exo2 src/Pipeline.cpp src/exo2.cpp --std=c++11 -lpthread
int main()
{
    std::vector<std::string> text = {
        "Il jouait du piano debout", 
        "C'est peut etre un détail pour vous", 
        "Mais pour moi, ca veut dire beaucoup"
    };

    Pipeline p(text);

    for(const auto& str : text)
        std::cout<<str<<std::endl;

    return 0;
}