#include "Pipeline.h"

#include <thread>

void Pipeline::lowering(std::string& text)
{

}

void Pipeline::tokenizing(std::string& text)
{

}

void Pipeline::deletingPunc(std::string& text)
{

}

void Pipeline::numbersToLetters(std::string& text)
{

}

Pipeline::Pipeline(std::vector<std::string> input)
{
    this->op[Step::LOWERING] = &Pipeline::lowering;
    this->op[Step::TOKENIZING] = &Pipeline::tokenizing;
    this->op[Step::DELETING_PUNC] = &Pipeline::deletingPunc;
    this->op[Step::NUMBERS_TO_LETTERS] = &Pipeline::numbersToLetters;

    for(auto& e : input)
    {
        this->text.push_back(e);
        this->progress.push_back(Step::LOWERING);
    }

    for(int i = 0 ; i < Pipeline::NB_OF_STEPS ; ++i)
    {
        this->th[i] = std::thread(
            this->op[this->progress[i]],
            this,
            std::ref(this->text[i])
        );
    }

    for(auto& t : this->th)
        t.join();
        
}

Pipeline::~Pipeline()
{
    ;
}