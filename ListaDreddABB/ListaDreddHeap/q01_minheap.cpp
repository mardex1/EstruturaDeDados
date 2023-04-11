#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

class MinHeap{
    private:
        int *heap;
        int mcapacidade;
        int mtamanho;
        inline int esquerdo(int i);
        inline int direito(int i);
        void Arruma();
        void CorrigeDescendo(int i);
    public:
        MinHeap(int vet[], int tam);
        ~MinHeap();
};

MinHeap::MinHeap(int vet[], int tam){
    mcapacidade = tam;
    heap = new int[mcapacidade];
    /*for(int i = 0;i < tam;i++){
        heap[i] = vet[i];
    
    }*/
    memcpy(heap, vet, tam * sizeof(int));
    mtamanho = tam;
    Arruma();
}

MinHeap::~MinHeap(){
    delete [] heap; 
}

void MinHeap::Arruma(){
    for(int i = (mtamanho/2-1);i >= 0;i--){
        CorrigeDescendo(i);
        cout << i << ": ";
        for(int i = 0;i < mtamanho;i++){
            cout << heap[i] << " ";
        }cout << endl;
    }
}

int MinHeap::esquerdo(int i){
    return 2*i + 1;
}

int MinHeap::direito(int i){
    return 2*i + 2;
}

void MinHeap::CorrigeDescendo(int i){
    int esq = esquerdo(i);
    int dir = direito(i);
    int menor = i;

    if(esq < mtamanho && heap[esq] < heap[menor]){
        menor = esq;
    }
    
    if(dir < mtamanho && heap[dir] < heap[menor]){
        menor = dir;
    }

    if(menor != i) {
        swap(heap[i], heap[menor]);
        CorrigeDescendo(menor);
    }
}

int main(){
    int quantidade;
    cin >> quantidade;

    int vet[quantidade];

    for(int i = 0;i < quantidade;i++){
        cin >> vet[i];
    }

    MinHeap(vet, quantidade);

    return 0;
}
