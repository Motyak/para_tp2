#include "ThreadPool.h"

#include <thread>
#include <cmath>    //std::pow
#include <iostream>
#include <iomanip>

ThreadPool::ThreadPool(unsigned short nbOfCores)
{
    this->i = 0;
    this->res = 0.f;

    for(int k = 1 ; k <= nbOfCores ; ++k)
    {
        this->th.push_back(std::thread(
            &ThreadPool::callbackFn, 
            this, 
            std::ref(this->i), 
            std::ref(this->res),
            std::ref(this->mut_i),
            std::ref(this->mut_res)
        ));
    }

    for(auto& t : this->th)
        t.join();
}

ThreadPool::~ThreadPool()
{
    ;
}

float ThreadPool::calculate(int i)
{
    float a = std::pow(-1, i);
    float b = 1.f;
    for(int k = 1.f ; k <= i ; ++k)
        b *= k;

    return a / b;
}

void ThreadPool::callbackFn(int& i, float& res, std::mutex& mut_i, std::mutex& mut_res)
{
    int local_i;
    float local_res;
    do 
    {
        // récupérer de maniere safe la valeur de i puis l'incrémenter
        mut_i.lock();
        local_i = i;
        ++i;
        mut_i.unlock();

        // faire le calcul a partir de local_i
        local_res = this->calculate(local_i);

        // ajouter le resultat a res, de manière safe, l'afficher
        mut_res.lock();
        res += local_res;
        std::cout<<std::setprecision(10)<<res<<std::endl;
        mut_res.unlock();

        // répéter tant que i n'atteint pas un certain stade
    } while(i < ThreadPool::LIMIT);
}