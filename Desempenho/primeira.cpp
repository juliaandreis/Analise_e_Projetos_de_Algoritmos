//Feito por Julia, Kauan e Tobias

#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <chrono>
#include <algorithm>

using namespace std;

void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    bool swapped;
  
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
      
        // If no two elements were swapped, then break
        if (!swapped)
            break;
    }
}

void insertionSort(vector<int>& vetor, int n)
{
    for (int i = 1; i < n; ++i) {
        int key = vetor[i];
        int j = i - 1;

        /* Move elements of arr[0..i-1], that are
           greater than key, to one position ahead
           of their current position */
        while (j >= 0 && vetor[j] > key) {
            vetor[j + 1] = vetor[j];
            j--;
        }
        vetor[j + 1] = key;
    }
}

int shellSort(vector<int>& vetor, int n)
{
    // Start with a big gap, then reduce the gap
    for (int gap = n/2; gap > 0; gap /= 2)
    {
        // Do a gapped insertion sort for this gap size.
        // The first gap elements a[0..gap-1] are already in gapped order
        // keep adding one more element until the entire array is
        // gap sorted 
        for (int i = gap; i < n; i += 1)
        {
            // add a[i] to the elements that have been gap sorted
            // save a[i] in temp and make a hole at position i
            int temp = vetor[i];

            // shift earlier gap-sorted elements up until the correct 
            // location for a[i] is found
            int j;            
            for (j = i; j >= gap && vetor[j - gap] > temp; j -= gap)
                vetor[j] = vetor[j - gap];
            
            //  put temp (the original a[i]) in its correct location
            vetor[j] = temp;
        }
    }
    return 0;
}

void selectionSort(vector<int> &arr) {
    int n = arr.size();

    for (int i = 0; i < n - 1; ++i) {

        // Assume the current position holds
        // the minimum element
        int min_idx = i;

        // Iterate through the unsorted portion
        // to find the actual minimum
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[min_idx]) {

                // Update min_idx if a smaller
                // element is found
                min_idx = j; 
            }
        }

        // Move minimum element to its
        // correct position
        swap(arr[i], arr[min_idx]);
    }
}

int main(){
    vector<int> vetor;

    srand(time(0));
    int tamanhoVetor = 1000000;

        auto inicio = std::chrono::high_resolution_clock::now();
        
        for (int i = 0; i < tamanhoVetor; i++){
            vetor.push_back(0+rand()%1500);
        }
    
        auto fim = chrono::high_resolution_clock::now();
        chrono::duration<double, std::milli> duracao = fim - inicio;
        //cout << "Tempo para gerar e popular o vetor: " << duracao.count() << " ms" << endl << endl;


        // ----------- ordenar 1
        inicio = std::chrono::high_resolution_clock::now();

        //bubbleSort(vetor);
        //insertionSort(vetor, tamanhoVetor);
        shellSort(vetor, tamanhoVetor);
        //selectionSort(vetor);

        fim = chrono::high_resolution_clock::now();
        duracao = std::chrono::duration_cast<std::chrono::milliseconds>(fim - inicio);
        cout << "Tempo para ordenar: " << duracao.count() << " ms" << endl;


        // ordenar vetor já ordenado
        auto inicio2 = std::chrono::high_resolution_clock::now();

        //bubbleSort(vetor);
        //insertionSort(vetor, tamanhoVetor);
        shellSort(vetor, tamanhoVetor);
        //selectionSort(vetor);

        auto fim2 = chrono::high_resolution_clock::now();
        auto duracao2 = std::chrono::duration_cast<std::chrono::milliseconds>(fim2 - inicio2);
        cout << "Tempo para ordenar o vetor já ordenado: " << duracao2.count() << " ms" << endl;
};