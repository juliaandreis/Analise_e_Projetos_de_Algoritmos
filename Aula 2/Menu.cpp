#include "Menu.h"

#define tamanhoLista 1000

Menu::Menu(){
    inicio, fim = 0;
    tempo_gasto = 0;

    struct timeval tv;
}

Menu::~Menu(){}

int Menu::exibeMenu(){
    int opção;
    cout << "Escolha uma opção: " << endl;
    cout << "1. Criar nova lista" << endl;
    cout << "2. Ordenar lista" << endl;
    cout << "3. Exibir lista" << endl;
    cout << "4. Verificar números primos" << endl;
    cout << "5. Sair" << endl;

    cin >> opção;
    cout << endl;
    return opção;
}

void Menu::criaLista(){
    mingw_gettimeofday(&tv,NULL);/////////////////////////////////////////////////////////////////////////////////////////////////////////
    inicio = 1000000 * tv.tv_sec + tv.tv_usec;
    for (int i = 0; i < tamanhoLista; i++) {
        lista[i] = rand() % 1501;
    }
    gettimeofday(&tv,NULL);
    fim = 1000000 * tv.tv_sec + tv.tv_usec;
    cout << "Tempo decorrido: " << double(fim - inicio)/1000 << " milissegundos\n";
}

void Menu::ordena(){
    inicio = clock();
    int ordenada[tamanhoLista];
    int maior = -1;
    int indiceMaior = 0;

    for (int i = tamanhoLista - 1; i >= 0; i--) {
        for (int j = 0; j < tamanhoLista; j++){
            if (lista[j] > maior){
                maior = lista[j];
                indiceMaior = j;
            }
        }
        ordenada[i] = maior;
        lista[indiceMaior] = -1; // Marca o número como já ordenado
        maior = -1;
    }

    for (int i = 0; i < tamanhoLista; i++) {
        lista[i] = ordenada[i];
    }
    gettimeofday(&tv,NULL);
    fim = 1000000 * tv.tv_sec + tv.tv_usec;
    cout << "Tempo decorrido: " << double(fim - inicio)/1000 << " milissegundos\n";
}

void Menu::imprimeLista(){
    cout << "Lista de números:"<< endl;
    for (int i = 0; i < tamanhoLista; i++) {
        cout << i+1 << ". " << lista[i] << endl;
    }
    cout << endl;
}

void Menu::verificaPrimos(){
    int primos[tamanhoLista];
    int limite = 0;
    int numPrimos = 0;
    bool ehPrimo;

    inicio = clock();
    for (int i = 0; i < tamanhoLista; i++){
        limite = sqrt(lista[i]);
        ehPrimo = true;

        if(lista[i] < 2) {
            ehPrimo = false;
        } else {
            for (int j = 2; j <= limite; j++){
                if (lista[i] % j == 0){
                    ehPrimo = false;
                    break;
                } 
            }
        }

        if (ehPrimo){
            primos[numPrimos] = lista[i];
            numPrimos++;
        }
    }

    fim = clock();

    if (numPrimos == 0){
        cout << "Nenhum número primo encontrado na lista." << endl << endl;
        return;
    } else {
        cout << "Números primos encontrados:" << endl;
        for (int i = 0; i < numPrimos; i++){
            cout << primos[i] << endl;
        }
        cout << endl << numPrimos << endl;
    }
    tempo_gasto = double(fim - inicio) / CLOCKS_PER_SEC * 1000;
    cout << "Tempo decorrido: " << tempo_gasto << " milissegundos\n";
}