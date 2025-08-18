#include "Menu.h"

Menu::Menu(){}

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
    auto inicio = chrono::high_resolution_clock::now();
    for (int i = 0; i < tamanhoLista; i++) {
        lista[i] = rand() % 1501;
    }
    auto fim = chrono::high_resolution_clock::now();
    auto duracao = chrono::duration_cast<chrono::microseconds>(fim - inicio);
    cout << "Tempo gerar: " << duracao.count() << " microssegundos\n";
}

void Menu::ordena(){
    auto inicio = chrono::high_resolution_clock::now();
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
    auto fim = chrono::high_resolution_clock::now();
    auto duracao = chrono::duration_cast<chrono::microseconds>(fim - inicio);
    std::cout << "Tempo ordenar: " << duracao.count() << " microssegundos\n";
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

    auto inicio = chrono::high_resolution_clock::now();
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

    auto fim = chrono::high_resolution_clock::now();
    auto duracao = chrono::duration_cast<chrono::microseconds>(fim - inicio);

    if (numPrimos == 0){
        cout << "Nenhum número primo encontrado na lista." << endl << endl;
        return;
    }else {
        cout << "Números primos encontrados:" << endl;
        for (int i = 0; i < numPrimos; i++){
            cout << primos[i] << endl;
        }    
       } 
        cout << "N primos: " << numPrimos;
    
    cout << "    Tempo primos: " << duracao.count() << " microssegundos\n" ;
}

void Menu::rodadas(){
    cout << "rodada 1:" << endl;
    auto iniciorodada = chrono::high_resolution_clock::now();
    criaLista();
    ordena();
    verificaPrimos();
    auto fimrodada = chrono::high_resolution_clock::now();
    auto duracaorodada = chrono::duration_cast<chrono::microseconds>(fimrodada - iniciorodada);
    cout << endl;
    cout << "Tempo TOTAL: " << duracaorodada.count() << " microssegundos\n";
    cout << "rodada 2:" << endl;
    iniciorodada = chrono::high_resolution_clock::now();
    ordena();
    verificaPrimos();
    fimrodada = chrono::high_resolution_clock::now();
    duracaorodada = chrono::duration_cast<chrono::microseconds>(fimrodada - iniciorodada);
    cout << endl << "----------------------------------------------------------------" << endl;
    cout << "Tempo TOTAL: " << duracaorodada.count() << " microssegundos\n";
}