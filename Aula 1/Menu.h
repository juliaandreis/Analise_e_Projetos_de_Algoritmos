
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <chrono>

#define tamanhoLista 1000

using namespace std;

class Menu{
    private:
        int lista[tamanhoLista];

    public:
        Menu();
        ~Menu();
        int exibeMenu();
        void criaLista();
        void ordena();
        void imprimeLista();
        void verificaPrimos();
        void rodadas();
};