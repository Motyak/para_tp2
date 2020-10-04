#include "Pipeline.h"

// g++ -o bin/exo2 src/Pipeline.cpp src/exo2.cpp --std=c++11 -lpthread
int main()
{
    std::vector<std::string> text = {"test", "test"};
    Pipeline p(text);

    return 0;
}