#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

class MaxHeap{
    private:
        int *heap;
        int mcapacidade;
        int mtamanho;
        inline int esquerdo(int i);
        inline int direito(int i);
        void Arruma();
        void CorrigeDescendo(int i);
    public:
        MaxHeap(int vet[], int tam);
        ~MaxHeap();
};

MaxHeap::MaxHeap(int vet[], int tam){
    mcapacidade = tam;
    heap = new int[mcapacidade];
    /*for(int i = 0;i < tam;i++){
        heap[i] = vet[i];
    
    }*/
    memcpy(heap, vet, tam * sizeof(int));
    mtamanho = tam;
    Arruma();
}

MaxHeap::~MaxHeap(){
    delete [] heap;
}

void MaxHeap::Arruma(){
    for(int i = (mtamanho/2-1);i >= 0;i--){
        CorrigeDescendo(i);
        cout << i << ": ";
        for(int i = 0;i < mtamanho;i++){
            cout << heap[i] << " ";
        }cout << endl;
    }
}

int MaxHeap::esquerdo(int i){
    return 2*i + 1;
}

int MaxHeap::direito(int i){
    return 2*i + 2;
}

void MaxHeap::CorrigeDescendo(int i){
    int esq = esquerdo(i);
    int dir = direito(i);
    int maior = i;

    if(esq < mtamanho && heap[esq] > heap[maior]){
        maior = esq;
    }
    
    if(dir < mtamanho && heap[dir] > heap[maior]){
        maior = dir;
    }

    if(maior != i) {
        swap(heap[i], heap[maior]);
        CorrigeDescendo(maior);
    }
}

int main(){
    int quantidade;
    cin >> quantidade;

    int vet[quantidade];

    for(int i = 0;i < quantidade;i++){
        cin >> vet[i];
    }

    MaxHeap(vet, quantidade);

    return 0;
}