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
    string inicio = "1";
    int n;
    int cont = 1;
    cin >> n;
    f1.Enfileira(inicio);
    for(int i = 0;i < n/2;i++){
        inicio = f1.Inicio();
        f1.Enfileira(inicio + "0");
        cont++;
        if(cont < n){
            f1.Enfileira(inicio + "1");
            cont++;
        }
        f2.Enfileira(f1.Desenfileira());
    }
    while(!f1.Vazia()){
        f2.Enfileira(f1.Desenfileira());
    }

    while(!f2.Vazia()){
        cout << f2.Desenfileira() << " ";
    }cout << endl;
}