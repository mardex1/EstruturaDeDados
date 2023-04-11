#include <iostream>
using namespace std;

typedef int Dado;

class Noh{
    friend class Pilha;
    private:
        Noh* mproximo;
        Dado mvalor;
    public:
        Noh(Dado mvalor);
};

Noh::Noh(Dado valor){
    mvalor = valor;
    mproximo = NULL;
}

class Pilha{
    private:
        Noh* mtopo;
        int mtamanho;
    public:
        Pilha();
        ~Pilha();
        void empilha(const Dado& valor);
        Dado desempilha();
        void inverter();
};

Pilha::Pilha(){
    mtopo = NULL;
    mtamanho = 0;
}

Pilha::~Pilha(){
    while(mtopo){
        desempilha();
    }
}

void Pilha::empilha(const Dado& valor){
    Noh* temp = new Noh(valor);
    temp->mproximo = mtopo;
    mtopo = temp;
    mtamanho++;
}

Dado Pilha::desempilha(){
    int valor = mtopo->mvalor;
    Noh *temp = mtopo;
    mtopo = mtopo->mproximo;
    delete temp;
    mtamanho--;
    return valor;
}

void Pilha::inverter(){
    Pilha aux;
    int tam = mtamanho;
    for(int i = 0;i < tam;i++){
        aux.empilha(desempilha());
    }


    for(int i = 0;i < tam;i++){
        cout << aux.desempilha() << " ";
    }
}

int main (){
    int num;
    int n;
    Pilha p1;

    cin >> n;

    for(int i = 0;i < n;i++){
        cin >> num;
        p1.empilha(num);
    }

    p1.inverter();

    return 0;
}