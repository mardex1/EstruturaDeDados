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
    Fila f1;
    Fila f2;
    char opcao;
    string placa;
    int cont = 0;
    string aux;
    bool achou = false;

    do{
        cin >> opcao;
        switch(opcao){
            case 'E':
                cin >> placa;
                f1.Enfileira(placa);
                break;
            case 'D':
                cin >> placa;
                achou = false;
                while(!f1.Vazia() and achou == false){
                    cont++;
                    if(f1.Inicio() == placa){
                        cout << cont << endl;
                        achou = true;
                        cont = 0;
                        f1.Desenfileira();
                        while(!f2.Vazia()){
                            f1.Enfileira(f2.Desenfileira()); 
                        }while(!f1.Vazia()){
                            aux = f1.Desenfileira();
                            cout << aux << endl;
                            f2.Enfileira(aux);
                        }while(!f2.Vazia()){
                            f1.Enfileira(f2.Desenfileira());
                        }
                    }else{
                        f2.Enfileira(f1.Desenfileira());
                    }
                }
                if(achou == false){
                    cout << "NAO ENCONTRADO" << endl;
                }
                break;
        }
    }while(opcao != 'S');

    return 0;
}