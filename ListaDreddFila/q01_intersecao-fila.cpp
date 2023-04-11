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
        void Intersecao(Fila& f2);
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

void Fila::Intersecao(Fila& f2){
    Fila aux;
    while(!f2.Vazia()){
        while(!Vazia()){
            if(Inicio() == f2.Inicio()){
                Desenfileira();
            }else{
                aux.Enfileira(Desenfileira());
            }
        }
        f2.Desenfileira();
        while(!aux.Vazia()){
            Enfileira(aux.Desenfileira());
        }
    }
}

int main (){
    int n1;
    int n2;
    int num1;
    int num2;
    Fila f1;
    Fila f2;

    cin >> n1;

    for(int i = 0;i < n1;i++){
        cin >> num1;
        f1.Enfileira(num1);
    }

    cin >> n2;

    for(int i = 0;i < n2;i++){
        cin >> num2;
        f2.Enfileira(num2);
    }

    f1.Intersecao(f2);

    while(!f1.Vazia()){
        cout << f1.Desenfileira() << " ";
    }cout << endl;
}