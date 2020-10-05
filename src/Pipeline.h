#ifndef PIPELINE_H
#define PIPELINE_H

#include <vector>
#include <thread>
#include <functional>
#include <mutex>

enum Step
{
    LOWERING,
    TOKENIZING,
    DELETING_PUNC,
    NUMBERS_TO_LETTERS
};

struct TextBloc
{
	std::string str;
	Step step;
};

class Pipeline
{
    static const int NB_OF_STEPS = 4;
    
    // Pipeline* en paramètre 1 pour le 'this' implicite
    // std::function<void(Pipeline*, std::vector<TextBloc>&)> op[Pipeline::NB_OF_STEPS];
    std::vector<TextBloc> text;
	std::mutex* mut;
	

    std::thread th[Pipeline::NB_OF_STEPS];

    void lowering(std::vector<TextBloc>& blocs);
    void tokenizing(std::vector<TextBloc>& blocs);
    void deletingPunc(std::vector<TextBloc>& blocs);
    void numbersToLetters(std::vector<TextBloc>& blocs);

  public:
    Pipeline(std::vector<std::string> input);
    ~Pipeline();
};



#endif