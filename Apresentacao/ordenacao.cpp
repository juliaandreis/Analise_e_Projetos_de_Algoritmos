#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <chrono>
#include <algorithm>
using namespace std;

// Merges two subarrays of arr[].
// First subarray is arr[left..mid]
// Second subarray is arr[mid+1..right]
void merge(vector<int>& arr, int left, int mid, int right){                
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temp vectors
    vector<int> L(n1), R(n2);

    // Copy data to temp vectors L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0;
    int k = left;

    // Merge the temp vectors back 
    // into arr[left..right]
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], 
    // if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], 
    // if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// begin is for left index and end is right index
// of the sub-array of arr to be sorted
void mergeSort(vector<int>& arr, int left, int right){
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

int mediana (int a, int b, int c){
    if ((a > b) != (a > c)) return a;
    else if ((b > a) != (b > c)) return b;
    else return c;
}

// Quick Sort
int partition(vector<int>& arr, int low, int high) {
    // choose the pivot
    int mid = low + (high - low) / 2;
    int pivot = mediana(arr[low], arr[mid], arr[high]);
  
    // undex of smaller element and indicates 
    // the right position of pivot found so far
    int i = low - 1;

    // Traverse arr[low..high] and move all smaller
    // elements on left side. Elements from low to 
    // i are smaller after every iteration
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
  
    // move pivot after smaller elements and
    // return its position
    swap(arr[i + 1], arr[high]);  
    return i + 1;
}

// the QuickSort function implementation
void quickSort(vector<int>& arr, int low, int high) {
  
    if (low < high) {
      
        // pi is the partition return index of pivot
        int pi = partition(arr, low, high);

        // recursion calls for smaller elements
        // and greater or equals elements
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
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

int main(){
    vector<int> vetor;

    srand(time(0));
    int tamanhoVetor = 1000;

    for (int i = 0; i < tamanhoVetor; i++){
        vetor.push_back(0+rand()%1500);
    }
    //cout << "Tempo para gerar e popular o vetor: " << duracao.count() << " ms" << endl << endl;

    // ----------- ordenar 1
    auto inicio = std::chrono::high_resolution_clock::now();

    //mergeSort(vetor, 0, tamanhoVetor-1);
    quickSort(vetor, 0, tamanhoVetor - 1);
    //shellSort(vetor, tamanhoVetor);


    auto fim = chrono::high_resolution_clock::now();
    chrono::duration<double, std::milli> duracao = fim - inicio;
    cout << "Tempo para ordenar: " << duracao.count() << " ms" << endl;


    // ordenar vetor já ordenado
    auto inicio2 = std::chrono::high_resolution_clock::now();

    //mergeSort(vetor, 0, tamanhoVetor-1);
    quickSort(vetor, 0, tamanhoVetor - 1);
    //shellSort(vetor, tamanhoVetor);

    auto fim2 = chrono::high_resolution_clock::now();
    chrono::duration<double, std::milli> duracao2 = fim2 - inicio2;
    cout << "Tempo para ordenar o vetor já ordenado: " << duracao2.count() << " ms";
};