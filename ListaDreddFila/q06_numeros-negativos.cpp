#include <iostream> 
using namespace std;

class Noh{
    friend class Fila;
    private:
        Noh *mproximo;
        int mdado;
    public:
        Noh(int valor);
};

Noh::Noh(int valor){
    mproximo = NULL;
    mdado = valor;
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
    int valor = minicio->mdado;
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
    return minicio->mdado;
}

int main(){
    Fila f1;
    Fila f2;
    int num;
    int N;
    cin >> N;

    for(int i = 0;i < N;i++){
        cin >> num;
        f1.Enfileira(num);
    }

    int K;
    int j = 0;
    int cont = 0;
    bool achou = false;
    cin >> K;

    while(K <= N){
        while((cont < K) and (achou == false)){
            if(f1.Inicio() < 0){
                cout << f1.Inicio() << " ";
                achou = true;
            }
            cont++;
            f2.Enfileira(f1.Desenfileira());
        }
        while(!f1.Vazia()){
            f2.Enfileira(f1.Desenfileira());
        }while(!f2.Vazia()){
            f1.Enfileira(f2.Desenfileira());
        }
        if(achou == false){
            cout << "inexistente" << " ";
        }
        f1.Desenfileira();
        K++;
        j++;
        cont = j;
        achou = false;        
    }
    
    return 0;
}