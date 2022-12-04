#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

class MaxHeap{
    private:
        int *heap;
        int mcapacidade;
        int mtamanho;
        inline int esquerdo(int i){return 2*i+1;}
        inline int direito(int i){return 2*i+2;}
        inline int pai(int i){return (i-1)/2;}
        void Arruma();
        void CorrigeDescendo(int i);
        void CorrigeSubindo(int i);
    public:
        MaxHeap(int vet[], int tam);
        ~MaxHeap();
        void Imprime();
        void Insere(int num);
        int Retira();
};

MaxHeap::MaxHeap(int vet[], int tam){
    mcapacidade = tam;
    heap = new int[mcapacidade];
    /*for(int i = 0;i < tam;i++){
        heap[i] = vet[i];
    
    }*/
    memcpy(heap, vet, 15 * sizeof(int));
    mtamanho = 15;
    Arruma();
}

int MaxHeap::Retira(){
    if(mtamanho == 0){
        cerr << "Erro ao retirar raiz" << endl;    
    }
    int aux = heap[0];
    swap(heap[0], heap[mtamanho-1]);
    mtamanho--;
    CorrigeDescendo(0);
    return aux;
}

MaxHeap::~MaxHeap(){
    delete [] heap;
}

void MaxHeap::Arruma(){
    for(int i = (mtamanho/2-1);i >= 0;i--){
        CorrigeDescendo(i);
    }
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

void MaxHeap::Imprime(){
    for(int i = 0;i < mtamanho;i++){
        cout << heap[i] << " ";
    }cout << endl;
}

void MaxHeap::Insere(int num){
    if(mtamanho == mcapacidade){
        cerr << "Erro ao inserir" << endl;
    }
    heap[mtamanho] = num;
    CorrigeSubindo(mtamanho);
    mtamanho++;
}

void MaxHeap::CorrigeSubindo(int i){
    int p = pai(i);
    //Não é necessário testar se p é maior que zero, uma vez que -1/2 é arredondado para zero.
    if(heap[i] > heap[p]){
        swap(heap[i], heap[p]);
        CorrigeSubindo(p);
    }
}

int main(){
    int vet[15];
    for(int i = 0;i < 15;i++){
        cin >> vet[i];
    }

    MaxHeap *pt = new MaxHeap(vet, 20);

    pt->Imprime();
    int num;

    for(int i = 0;i < 5;i++){
        cin >> num;
        pt->Insere(num);
    }

    pt->Imprime();

    for(int i = 0;i < 20;i++){
        cout << pt->Retira() << " ";
    }cout << endl;

    delete pt;

    return 0;
}