#include "Pipeline.h"

#include <thread>
#include <cctype>
#include <algorithm>

void Pipeline::lowering(std::vector<TextBloc>& blocs)
{
    std::vector<TextBloc>::iterator it;
    do
    {
        // chercher un bloc à l'étape 'lowering' (par son index)
        it = std::find_if(blocs.begin(), blocs.end(), [](const TextBloc& b){
            if(b.step == Step::LOWERING)
                return true;
            return false;
        });
        int index = std::distance(this->text.begin(), it);

        // faire l'opération sur le bloc cible de manière safe
        // et le faire passer à l'étape supérieure
        this->mut[index].lock();
        for(auto& c : blocs[index].str)
            c = std::tolower(c);
        blocs[index].step = Step::TOKENIZING;
        this->mut[index].unlock();

        // boucler tant qu'il reste des blocs à l'étape
        // lowering ou inférieur
    } while(it != blocs.end());
}

void Pipeline::tokenizing(std::vector<TextBloc>& blocs)
{

}

void Pipeline::deletingPunc(std::vector<TextBloc>& blocs)
{

}

void Pipeline::numbersToLetters(std::vector<TextBloc>& blocs)
{

}

Pipeline::Pipeline(std::vector<std::string> input)
{
    this->mut = new std::mutex[this->text.size()];

    // // on associe chaque étape à une fonction membre dédiée
    // this->op[Step::LOWERING] = &Pipeline::lowering;
    // this->op[Step::TOKENIZING] = &Pipeline::tokenizing;
    // this->op[Step::DELETING_PUNC] = &Pipeline::deletingPunc;
    // this->op[Step::NUMBERS_TO_LETTERS] = &Pipeline::numbersToLetters;

    // on ajoute chaque bloc de texte avec son étape
    for(auto& e : input)
        this->text.push_back({e, Step::LOWERING});
        
    for(int i = 0 ; i < Pipeline::NB_OF_STEPS ; ++i)
    {
        this->th[i] = std::thread(
            // this->op[this->text[i].step],
            &Pipeline::lowering,
            this,
            std::ref(this->text)
        );
    }

    for(auto& t : this->th)
        t.join();
        
}

Pipeline::~Pipeline()
{
    delete[] this->mut;
}