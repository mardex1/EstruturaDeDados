#include <iostream>
using namespace std;

class pilha{
    private:
        int capacidade;
        int *dados;
        int posTopo;
        int tamanho;
    public:
        pilha();
        ~pilha();
        void empilha(const int& dado);
        int desempilha();
        int topo();
        int tam();
};

pilha::pilha(){
    dados = new int[254];   
    posTopo = -1;
    tamanho = 0;
}

pilha::~pilha(){
    delete[] dados;
}

void pilha::empilha(const int& dado){
    tamanho++;
    posTopo++;
    dados[posTopo] = dado;
}

int pilha::desempilha(){
    tamanho--;
    posTopo--;
    return dados[posTopo+1];
}

int pilha::tam(){
    return tamanho;
}

int pilha::topo(){
    return dados[posTopo];
}

int main(){
    pilha p1;
    string frase;
    int posicao;
    bool achou = false;
    getline(cin, frase);
    int i = 0;
    while(i < frase.size()){
        if(frase[i] == '('){
            p1.empilha(i);
        }
        if(frase[i] == ')'){
            if(p1.tam() > 0){
                p1.desempilha();
            }else{
                posicao = i;
                achou = true;
            }
        }
        i++;
    }
    if(achou == false){
        if(p1.tam() == 0){
            cout << "correto" << endl;
        }else{
            cout << p1.topo() << endl;
        }
    }else{
        cout << posicao << endl;
    }
    
    return 0;    
}
