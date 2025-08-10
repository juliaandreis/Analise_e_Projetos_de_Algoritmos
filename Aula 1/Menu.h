/*Cria um array de 1.000 valores inteiros randomicamente. 
Ordena esse array de menor a maior.
Verifica e apresenta quais valores são números primos.
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

class Menu{
    private:
        int lista[1000];
        int tamanhoLista = 0;

    public:
        Menu();
        ~Menu();
        int exibeMenu();
        void criaLista();
        void ordena();
        void imprimeLista();
        void verificaPrimos();
};