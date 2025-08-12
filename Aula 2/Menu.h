#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

class Menu{
    private:
        int lista[1000];
        clock_t inicio, fim;
        double tempo_gasto;

    public:
        Menu();
        ~Menu();
        int exibeMenu();
        void criaLista();
        void ordena();
        void imprimeLista();
        void verificaPrimos();
};