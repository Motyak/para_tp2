#ifndef PIPELINE_H
#define PIPELINE_H

#include <vector>
#include <thread>
#include <functional>

enum Step
{
    LOWERING,
    TOKENIZING,
    DELETING_PUNC,
    NUMBERS_TO_LETTERS
};

class Pipeline
{
    static const int NB_OF_STEPS = 4;
    
    // Pipeline* en paramètre 1 pour le 'this' implicite
    std::function<void(Pipeline*, std::string&)> op[Pipeline::NB_OF_STEPS];
    std::vector<std::string> text;
    std::vector<Step> progress;
    std::thread th[Pipeline::NB_OF_STEPS];

    void lowering(std::string& text);
    void tokenizing(std::string& text);
    void deletingPunc(std::string& text);
    void numbersToLetters(std::string& text);

  public:
    Pipeline(std::vector<std::string> input);
    ~Pipeline();
};



#endif