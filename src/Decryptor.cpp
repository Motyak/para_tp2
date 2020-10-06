#include "Decriptor.h"

#include "MD5/md5.h"

#include <cmath>

const std::string Decryptor::CODE = "3ed7dceaf266cafef032b9d5db224717";

Decryptor::Decryptor(unsigned short nbOfCores)
{
    this->i = 0;
    this->found = false;

    for(int k = 1 ; k <= nbOfCores ; ++k)
    {
        this->th.push_back(std::thread(
            &Decryptor::callbackFn, 
            this, 
            std::ref(this->i), 
            std::ref(this->found),
            std::ref(this->mut_i)
        ));
    }

    for(auto& t : this->th)
        t.join();
}

Decryptor::~Decryptor()
{
    ;
}

Result Decryptor::solve(int i)
{
    // générer la chaîne correspondant à 
    // la ième combinaison de 5 lettres (minuscules)
    std::string str = "*****";
    int tmp;
    for(int k = 0 ; k < 5 ; ++k)
    {
        tmp = (int)(i / pow(26, 4-i));
        str[i] = tmp + 97;
        i -= tmp * pow(26, 4-i);
    }

    // on retourne la combinaison en clair et en chiffré
    return {str, md5(str)};
}

void Decryptor::callbackFn(int& i, bool& found, std::mutex& mut_i)
{
    int local_i;
    Result res;
    do 
    {
        // récupérer de maniere safe la valeur de i puis l'incrémenter
        mut_i.lock();
        local_i = i;
        ++i;
        mut_i.unlock();

        res = this->solve(local_i);

        if(res.md5 == Decryptor::CODE)
        {
            this->found = true;
            std::cout<<"Le message clair est : ";
            std::cout<<res.msg<<std::endl;
        }
            

        // répéter tant que le message n'a pas été cracké
    } while(!this->found);
}