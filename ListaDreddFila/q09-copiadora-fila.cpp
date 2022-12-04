#include <iostream>
using namespace std;

class Noh{
    friend class Fila;
    private:
        Noh* mproximo;
        string mvalor;
    public:
        Noh(string valor);
};

Noh::Noh(string valor){
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
        void Enfileira(string valor);
        string Desenfileira();
        bool Vazia();
        string Inicio();
};

Fila::Fila(){
    minicio = NULL;
    mfim = NULL;
    mtamanho = 0;
}

Fila::~Fila(){
    while(!Vazia()){
        Desenfileira();
    }
}

void Fila::Enfileira(string valor){
    Noh *temp = new Noh(valor);
    if(mtamanho == 0){
        minicio = temp;
    }else{
        mfim->mproximo = temp;
    }
    mfim = temp;
    mtamanho++;
}

string Fila::Desenfileira(){
    string valor = minicio->mvalor;
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

string Fila::Inicio(){
    return minicio->mvalor;
}

int main(){
    Fila f_normal;
    Fila f_prioritario;
    string nome;
    string acao;
    int cont = 0;

    do{
        cin >> acao;
        if(acao == "normal"){
            cin >> nome;
            f_normal.Enfileira(nome);
        }else if(acao == "prioridade"){
            cin >> nome;
            f_prioritario.Enfileira(nome);
        }else if(acao == "atender"){
            if(f_normal.Vazia() and f_prioritario.Vazia()){
                cout << "AGUARDE" << endl;
            }else if(!f_prioritario.Vazia() and cont < 3){
                cout << f_prioritario.Desenfileira() << endl;
                cont++;
            }else if(!f_normal.Vazia()){
                cout << f_normal.Desenfileira() << endl;
                cont = 0;
            }else if(f_normal.Vazia()){
                cout << f_prioritario.Desenfileira() << endl;
            }

        }

    }while(acao != "fim");

    return 0;
}