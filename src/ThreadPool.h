#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <thread>
#include <mutex>
#include <vector>

class ThreadPool
{
    static const int LIMIT = 12;

    int i;
    float res;
    std::mutex mut_i, mut_res;
    std::vector<std::thread> th;

    float calculate(int i);
    void callbackFn(int& i, float& res, std::mutex& mut_i, std::mutex& mut_res);

  public:
    ThreadPool(unsigned short nbOfCores);
    ~ThreadPool();
};
#endif