#include "Menu.h"

int main(){
    srand(time(0));
    Menu menu;

    int opcao = 0;

    while (opcao != 5) {
        opcao = menu.exibeMenu();
        
        switch (opcao) {
        case 1:
            menu.criaLista();
            break;
        case 2:
            menu.ordena();
            break;
        case 3:
            menu.imprimeLista();
            break;
        case 4:
            menu.verificaPrimos();
            break;
        case 5:
            cout << "Saindo do programa." << endl;
            break;
        default:
            cout << "Opção inválida. Tente novamente." << endl;
            break;
        }   
    }

    return 0;
}