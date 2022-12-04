#include <iostream>
using namespace std;

class Fila{
    private:
        int minicio;
        int mfim;
        int *mdados;
        int mcapacidade;
        int mtamanho;
    public:
        Fila(int capacidade);
        ~Fila();
        void Enfileira(int valor);
        int Desenfileira();
        bool Vazia();
        void Info();
};

Fila::Fila(int capacidade){
    minicio = -1;
    mfim = -1;
    mcapacidade = capacidade;
    mdados = new int[mcapacidade];
    mtamanho = 0;
}

Fila::~Fila(){
    delete mdados;
}

void Fila::Enfileira(int valor){
    if(mtamanho <= mcapacidade){
        mfim++;
        mfim = mfim % mcapacidade;
        mdados[mfim] = valor;
        if(mtamanho == 0){
            minicio++;
        }
        mtamanho++;
    }else{
        cerr << "ERRO" << endl;
    }
}   

int Fila::Desenfileira(){
    if(mtamanho > 0){
        int valor = mdados[minicio];
        mtamanho--;
        if(mtamanho > 0){
            minicio++;
            minicio = minicio % mcapacidade;
        }else{
            minicio = -1;
            mfim = -1;
        }
        return valor;
    }else{
        cerr << "Fila Vazia" << endl;
        return -1;
    }   
}

void Fila::Info(){
    cout << "tamanho=" << mtamanho << " ";
    cout << "capacidade=" << mcapacidade << " ";
    cout << "inicio=" << minicio << " ";
    cout << "fim=" << mfim << endl;
    int atual = minicio;
    for (int i = 0; i < mtamanho; i++) {
        cout << mdados[atual] << " ";
        atual++;
        atual = atual % mcapacidade;    
    }cout << endl;
}

int main(){
    char opcao;
    int cap;
    int num;
    cin >> cap;
    Fila f1(cap);

    do{
        cin >> opcao;
        switch(opcao){
            case 'e':
                cin >> num;
                f1.Enfileira(num);
                break;
            case 'd':
                cout << f1.Desenfileira() << endl;
                break;
            case 'i':
                f1.Info();
                break;
        }
    }while(opcao != 't');

    return 0;
}