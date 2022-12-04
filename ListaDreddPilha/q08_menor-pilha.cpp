#include <iostream>
using namespace std;

class Noh{
    friend class Pilha;
    private:
        Noh *mproximo;
        int mvalor;
    public:
        Noh(int valor);
};

Noh::Noh(int valor){
    mproximo = NULL;
    this->mvalor = valor;
}

class Pilha{
    private:
        Noh *mtopo;
        int mtamanho;
    public:
        Pilha();
        ~Pilha();
        void Empilha(const int& valor);
        int Desempilha();
        int Menor();
        bool Vazio();
};

Pilha::Pilha(){
    mtopo = NULL;
    mtamanho = 0;
}

Pilha::~Pilha(){
    while(mtopo){
        Desempilha();
    }
}

void Pilha::Empilha(const int& valor){
    Noh *temp = new Noh(valor);
    temp->mproximo = mtopo;
    mtopo = temp;
    mtamanho++;
}

int Pilha::Desempilha(){
    int valor = mtopo->mvalor;
    Noh *temp = mtopo;
    mtopo = mtopo->mproximo;
    delete temp;
    mtamanho--;
    return valor;
}

int Pilha::Menor(){
    int menor = 0;
    int temp;
    Pilha aux;
    int tam = mtamanho;

    menor = Desempilha();
    Empilha(menor);

    for(int i = 0;i < tam;i++){
        temp = Desempilha();
        if(temp < menor){
            menor = temp;
        }
        aux.Empilha(temp);
    }

    for(int i = 0;i < tam;i++){
        Empilha(aux.Desempilha());
    }

    return menor;
}

bool Pilha::Vazio(){
    if(mtamanho == 0){
        return true;
    }else{
        return false;
    }
}

int main (){
    Pilha p1;
    char opcao;
    bool sair = false;
    int num;
    
    while(sair == false){
        cin >> opcao;
        switch(opcao){
        case 'e':
            cin >> num;
            p1.Empilha(num);
            break;
        case 'd':
            if(p1.Vazio()){
                cout << "VAZIA" << endl;
            }else{
                cout << p1.Desempilha() << endl;
            }
            break;
        case 'm':
            if(p1.Vazio()){
                cout << "VAZIA" << endl;
            }else{
                cout << p1.Menor() << endl;
            }
            break;
        case 's':
            while(!p1.Vazio()){
                cout << p1.Desempilha() << " ";
                sair = true;
            }cout << endl;
            break;
        }
    }

    return 0;
}

