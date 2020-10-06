#include "Pipeline.h"

#include <algorithm>
#include <unordered_map>
#include <thread>
#include <mutex>

void Pipeline::lowering(std::string& bloc)
{
    for(auto& c : bloc)
            c = std::tolower(c);
}

void Pipeline::tokenizing(std::string& bloc)
{
    size_t start_pos = 0;
    while ((start_pos = bloc.find("'", start_pos)) != std::string::npos)
    {
        bloc.replace(start_pos, 1, "'|");
        start_pos += 2;
    }
    start_pos = 0;
    while ((start_pos = bloc.find(" ", start_pos)) != std::string::npos)
    {
        bloc.replace(start_pos, 1, "|");
        start_pos += 1;
    }

    // std::replace(bloc.begin(), bloc.end(), "'", "'|");
    // std::replace(bloc.begin(), bloc.end(), " ", "|");
}

void Pipeline::deletingPunc(std::string& bloc)
{
    const char punc[] = {':', ',', '!', '?', ';', '.'};
    std::remove_if(bloc.begin(), bloc.end(), [punc](char& c){
        return std::find(std::begin(punc), std::end(punc), c);
    });
}

void Pipeline::numbersToLetters(std::string& bloc)
{
    // std::unordered_map<std::string,std::string> map = {
    //     {"0", "zéro"}, {"1", "un"}, {"2", "deux"},
    //     {"3", "trois"}, {"4", "quatre"}, {"5", "cinq"},
    //     {"6", "six"}, {"7", "sept"}, {"8", "huit"}, {"9", "neuf"}
    // };

    // char digitFound;

    // auto pred = [map,&digitFound](char& c){
    //     for(const auto& pair : map)
    //         if(c == pair.first)
    //         {
    //             digitFound = c;
    //             return true;
    //         }         
    //     return false;
    // };

    // std::replace_if(bloc.begin(), bloc.end(), pred, map[digitFound]);
}

void Pipeline::callbackFn(Job* actual, Job* next)
{
    unsigned c = 0;
    while(c != this->nbOfBlocs)
    {
        std::unique_lock<std::mutex> lck(actual->mut);
        actual->cond_var.wait(lck, [actual]{return !actual->work.empty();});
        std::string bloc = actual->work.front();
        actual->work.pop();
        actual->op(this, bloc);
        if(!next)
        {
            std::unique_lock<std::mutex> ul(next->mut);
            next->work.push(bloc);
            next->cond_var.notify_one();
        }
        ++c;
    }
}

Pipeline::Pipeline(std::vector<std::string>& input)
{
    this->nbOfBlocs = input.size();

    // on associe chaque étape à une fonction membre dédiée
    this->jobs[Step::LOWERING].op = &Pipeline::lowering;
    this->jobs[Step::TOKENIZING].op = &Pipeline::tokenizing;
    this->jobs[Step::DELETING_PUNC].op = &Pipeline::deletingPunc;
    this->jobs[Step::NUMBERS_TO_LETTERS].op = &Pipeline::numbersToLetters;

    for(auto& str : input)
    {
        std::unique_lock<std::mutex> lck(this->jobs[Step::LOWERING].mut);
        this->jobs[Step::LOWERING].work.push(str);
        this->jobs[Step::LOWERING].cond_var.notify_one();
    }

    for(auto& j : this->jobs)
        j.th.join();
}

Pipeline::~Pipeline()
{
    ;
}