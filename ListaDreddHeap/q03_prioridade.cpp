#include <iostream>   
#include <cstdlib>

typedef unsigned TCodProcesso;

struct Processo{
    TCodProcesso codigo;
    int prioridade;
};

class Heap {
    // classe Heap (max-heap, o maior fica na raiz/inicio)
    public:
        // Criar heap sem dados e com capacidade informada
        Heap(int cap);
        // Destruttor
        ~Heap();
        // Inserir um dado na heap
        bool Inserir(TCodProcesso codigo, int prioridade);
        // Retira e retorna a raiz
        bool Retirar(TCodProcesso* codigo, int* prioridade);
    private:
        void ArrumarDescendo(int i);
        void ArrumarSubindo(int i);
        inline int Direito(int i){return 2*i+2;}
        inline int Esquerdo(int i){return 2*i+1;}
        inline int Pai(int i){return (i-1)/2;}
        int mcapacidade;
        Processo *heap;
        int mtamanho;
};

using namespace std;

Heap::Heap(int cap) {
    mcapacidade = cap;
    heap = new Processo[mcapacidade];
    mtamanho = 0;
}

Heap::~Heap() {
    delete [] heap;
}

void Heap::ArrumarDescendo(int i) {
    // Arruma as posicoes de i para baixo.
    int esq = Esquerdo(i);
    int dir = Direito(i);
    int maior = i;

    if(esq < mtamanho and heap[esq].prioridade > heap[maior].prioridade){
        maior = esq;
    }

    if(dir < mtamanho and heap[dir].prioridade > heap[maior].prioridade){
        maior = dir;
    }

    if(maior != i){
        swap(heap[i], heap[maior]);
        ArrumarDescendo(maior);
    }
}

void Heap::ArrumarSubindo(int i) {
    // Arruma as posicoes de i para cima.
    int p = Pai(i);

    if(heap[i].prioridade > heap[p].prioridade){
        swap(heap[i], heap[p]);
        ArrumarSubindo(p);
    }
}

bool Heap::Retirar(TCodProcesso* codigo, int* prioridade) {
    // Retira um codigo/prioridade, retornando os dois valores.
    // Retorna falso se o heap estiver vazio.
    if(mtamanho == 0){
        return false;
    }
    Processo aux = heap[0];
    swap(heap[0], heap[mtamanho-1]);
    mtamanho--;
    *codigo = aux.codigo;
    *prioridade = aux.prioridade;
    ArrumarDescendo(0);
    return true;
}

bool Heap::Inserir(TCodProcesso codigo, int prioridade){
    // Insere um codigo/prioridade no heap.
    // Retorna falso se o heap estiver cheio.
    if(mtamanho == mcapacidade){
        return false;
    }
    heap[mtamanho].codigo = codigo;
    heap[mtamanho].prioridade = prioridade;
    ArrumarSubindo(mtamanho);
    mtamanho++;
    return true;
}

int main() {
    unsigned capacidade;
    cin >> capacidade;

    Heap heap(capacidade);
    char comando;
    TCodProcesso codigo;
    int prioridade;

    do {
        cin >> comando;
        switch (comando) {
            case 'i': // inserir um processo no heap
                cin >> codigo >> prioridade;
                heap.Inserir(codigo, prioridade);
                break;
            case 'o': // obter um processo do heap
                if (heap.Retirar(&codigo, &prioridade)){
                    cout << codigo << ' ' << prioridade << endl;
                }else{
                    cout << "Nao encontrado" << endl;
                }
                break;
            case 's': //sair
                break;
        }
    } while (comando != 's');
    return 0;
}   