/*
    MaxHeap, para alteração de prioridade
    by joukim & bruno, 2019
*/

#include <iostream>
#include <utility> // para usar swap
#include <stdexcept> // para usar exceção com runtime_error

using namespace std;

struct dado {
    int prioridade;
    int valor;
};

bool operator>(dado d1, dado d2) {
    return d1.prioridade > d2.prioridade;
}

bool operator<(dado d1, dado d2) {
    return d1.prioridade < d2.prioridade;
}

ostream& operator<<(ostream& output,const dado& d) {
    output << "[" << d.valor << "/" << d.prioridade << "]"; 
    return output;
}

class MaxHeap {
private:
    dado* heap;
    int capacidade;
    int tamanho;
    inline int pai(int i);
    inline int esquerdo(int i);
    inline int direito(int i); 
    void corrigeDescendo(int i); 
    void corrigeSubindo(int i);
public:
    MaxHeap(int cap);
    ~MaxHeap();
    void imprime();
    dado retiraRaiz();
    void insere(dado d);
    void alteraPrioridade(int umValor, int novaPrioridade);
};

MaxHeap::MaxHeap(int cap) {
    capacidade = cap;
    heap = new dado[capacidade];
    tamanho = 0;
}

MaxHeap::~MaxHeap() {
    delete[] heap;

}

int MaxHeap::pai(int i) {
    return (i-1)/2;

}
    
int MaxHeap::esquerdo(int i) {
    return 2*i + 1;

}
    
int MaxHeap::direito(int i) {
    return 2*i + 2;

}
    
void MaxHeap::corrigeDescendo(int i) {
    int esq = esquerdo(i);
    int dir = direito(i);
    int maior = i;
    //Primeira condicao usada para verificar se o filho existe ou nao
    if(esq < tamanho && heap[esq].prioridade > heap[maior].prioridade){
        maior = esq;
    }
    
    if(dir < tamanho && heap[dir].prioridade > heap[maior].prioridade){
        maior = dir;
    }

    if(maior != i) {
        //Funcao da cstdlib
        swap(heap[i], heap[maior]);
        corrigeDescendo(maior);
    }
}

void MaxHeap::corrigeSubindo(int i) {
    int p = pai(i);
    if(heap[i].prioridade > heap[p].prioridade){
        swap(heap[i], heap[p]);
        corrigeSubindo(p);
    }

}
        
void MaxHeap::imprime() {
    for(int i = 0;i < tamanho;i++){
        cout << 
    }
}


dado MaxHeap::retiraRaiz() {
// implemente este método

}


void MaxHeap::insere(dado d){
// implemente este método

}

void MaxHeap::alteraPrioridade(int umValor, int novaPrioridade) {
#error falta implementar o método alteraPrioridade!
    // 1. primeira tarefa: encontrar o dado no vetor de dados


    // 2. segunda tarefa: altera prioridade do dado encontrado, 
    // armazenando prioridade antiga para comparação


    // 3. terceira tarefa: sobe ou desce o dado, de acordo com 
    // a mudança de prioridade   

}

int main () {
    int capacidade;
    cin >> capacidade;
    MaxHeap meuHeap(capacidade);
   
    char opcao;
    cin >> opcao;
    
    dado umDado;
    int valor, novaPrioridade;

    while (opcao != 'Q') {
        switch(opcao) {
            case 'I':
                cin >> umDado.valor;
                cin >> umDado.prioridade;
                meuHeap.insere(umDado);
                break;
            case 'R':
                cout << meuHeap.retiraRaiz().valor << endl;
                break;
            case 'A':
                cin >> valor >> novaPrioridade;
                meuHeap.alteraPrioridade(valor,novaPrioridade); 
                break;               
            case 'P':
                meuHeap.imprime();
                break;
            default:
                cout << "Opção inválida!" << endl;
        }
        cin >> opcao;
    }
    
    return 0;
}
