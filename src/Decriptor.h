#ifndef DECRYPTOR_H
#define DECRYPTOR_H

#include <thread>
#include <mutex>
#include <vector>

struct Result
{
    std::string msg;
    std::string md5;
};

class Decryptor
{
    int i;
    std::mutex mut_i;
    bool found;
    std::vector<std::thread> th;

    Result solve(int i);
    void callbackFn(int& i, bool& found, std::mutex& mut_i);

  public:
    // le nombre de possibilités différentes - 1
    static const unsigned LIMIT = 11881375;
    static const std::string CODE;

    Decryptor(unsigned short nbOfCores);
    ~Decryptor();
};
#endif