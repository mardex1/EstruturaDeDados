#include <iostream>
using namespace std;

class Noh{
    friend class Fila;
    private:
        Noh *mproximo;
        int mvalor;
    public:
        Noh(int valor);
};

Noh::Noh(int valor){
    mproximo = NULL;
    mvalor = valor;
}

class Fila{
    private:
        Noh *minicio;
        Noh *mfim;
        int mtamanho;
    public:
        Fila();
        ~Fila();
        void Enfileira(int valor);
        int Desenfileira();
        bool Vazia();
        int Inicio();
        int Tamanho();
        void Escreve();
        void Mescla(Fila& fb);
};

Fila::Fila(){
    minicio = NULL;
    mfim = NULL;
    mtamanho = 0;
}

Fila::~Fila(){
    while(mtamanho > 0){
        Desenfileira();
    }
}

void Fila::Enfileira(int valor){
    Noh *temp = new Noh(valor);
    if(Vazia()){
        minicio = temp;
    }else{
        mfim->mproximo = temp;
    }
    mfim = temp;
    mtamanho++;
}

int Fila::Desenfileira(){
    int valor = minicio->mvalor;
    Noh *temp = minicio;
    minicio = minicio->mproximo;
    delete temp;
    mtamanho--;
    if(mtamanho == 0){
    mfim = NULL;
    }
    return valor;
}

bool Fila::Vazia(){
    if(mtamanho == 0){
        return true;
    }else{
        return false;
    }
}

int Fila::Inicio(){
    return minicio->mvalor;
}

int Fila::Tamanho(){
    return mtamanho;
}

void Fila::Mescla(Fila& fb){
    Fila aux;

    while(!fb.Vazia() or !Vazia()){
        if(fb.Inicio() > Inicio()){
            aux.Enfileira(Desenfileira());
        }else{
            aux.Enfileira(fb.Desenfileira());
        }if(fb.Vazia()){
            while(!Vazia()){
                aux.Enfileira(Desenfileira());
            }
        }else if(Vazia()){
            while(!fb.Vazia()){
                aux.Enfileira(fb.Desenfileira());
            }
        }
    }

    aux.Escreve();
}

void Fila::Escreve(){
    Noh *aux = minicio;
    while(aux != NULL){
        cout << aux->mvalor << " ";
        aux = aux->mproximo;
    }cout << endl;
    delete[] aux;
}

int main(){
    char opcao;
    char fila;
    Fila fa;
    Fila fb;
    int num;
    do{
        cin >> opcao;
        switch(opcao){
            cin >> opcao;
            case 'i':
                cin >> fila;
                cin >> num;
                if(fila == 'a'){
                    fa.Enfileira(num);
                }else if(fila == 'b'){
                    fb.Enfileira(num);
                }
                break;
            case 'e':
                cin >> fila;
                if(fila == 'a'){
                    fa.Escreve();
                }if(fila == 'b'){
                    fb.Escreve();
                }
                break;
            case 'm':
                fa.Mescla(fb);
                break;
        }
    }while(opcao != 't');

    return 0;
}