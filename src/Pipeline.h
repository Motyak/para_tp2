#ifndef PIPELINE_H
#define PIPELINE_H

#include <vector>
#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <queue>

enum Step
{
    LOWERING,
    TOKENIZING,
    DELETING_PUNC,
    NUMBERS_TO_LETTERS
};

class Pipeline;

struct Job
{
	std::queue<std::string> work;
    // Pipeline* en paramètre 1 pour le 'this' implicite
	std::function<void(Pipeline*, std::string&)> op;
    std::thread th;
    std::mutex mut;
    std::condition_variable cond_var;
};

class Pipeline
{
    static const int NB_OF_STEPS = 4;

    unsigned nbOfBlocs;
    Job jobs[Pipeline::NB_OF_STEPS];

    void callbackFn(Job* actual, Job* next);

    void lowering(std::string& bloc);
    void tokenizing(std::string& bloc);
    void deletingPunc(std::string& bloc);
    void numbersToLetters(std::string& bloc);

  public:
    Pipeline(std::vector<std::string>& input);
    ~Pipeline();
};



#endif