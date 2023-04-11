#include <iostream>
#include <cstdlib>

using namespace std;

typedef int dado;

class Noh{
    friend class Listadup;
    private:   
        dado mdado;
        Noh *mproximo;
        Noh *manterior;
    public:
        Noh(dado d);
};

Noh::Noh(dado d){
    mdado = d;
    mproximo = NULL;
    manterior = NULL;
} 

class Listadup{
    private:
        Noh *minicio;
        Noh *mfim;
        int mtamanho;
        void Remove_todos();
    public:
        Listadup();
        ~Listadup();
        inline void Insere(dado d);
        void Insere_no_fim(dado d);
        void Imprime();
        void Imprime_Reverso();
        inline bool Vazia();
        void Remove(Listadup& umalista);
};

Listadup::Listadup(){
    mtamanho = 0;
    minicio = NULL;
    mfim = NULL;
}

Listadup::~Listadup(){
    Remove_todos();
}

void Listadup::Remove_todos(){
    Noh *aux = minicio;
    Noh *temp;

    while(aux != NULL){
        temp = aux;
        aux = aux->mproximo;
        delete temp;
    }

    mtamanho = 0;
    minicio = NULL;
    mfim =  NULL;
}
//Como é uma função pequena, foi declarada com inline
void Listadup::Insere(dado d){
    Insere_no_fim(d);
}

void Listadup::Insere_no_fim(dado d){
    Noh *novo = new Noh(d);

    if(Vazia()){
        minicio = novo;
        mfim = novo;
    }else{
        mfim->mproximo = novo;
        novo->manterior = mfim;
        mfim = novo;
    }
    mtamanho++;
}

void Listadup::Imprime(){
    Noh *aux = minicio;

    while(aux != NULL){
        cout << aux->mdado << " ";
        aux = aux->mproximo;
    }
    cout << endl;
}

void Listadup::Imprime_Reverso(){
    Noh *aux = mfim;
    while(aux != NULL){
        cout << aux->mdado << " ";
        aux = aux->manterior;
    }
    cout << endl;
} 

inline bool Listadup::Vazia(){
    return (mtamanho == 0);
}

void Listadup::Remove(Listadup& umalista){
    Noh *aux = umalista.minicio;
    Noh *ptr_procura;
    int temp;

    while(aux != NULL){
        if(!Vazia()){
            temp = aux->mdado;
            ptr_procura = minicio;
        }
        while(ptr_procura != NULL){
            
            if(ptr_procura->mdado == temp){
                Noh *anterior = ptr_procura->manterior;
                Noh *proximo = ptr_procura->mproximo;
                if(anterior != NULL){
                    anterior->mproximo = proximo;
                }else{
                    minicio = ptr_procura->mproximo;
                }
                if(proximo != NULL){
                    proximo->manterior = anterior;
                }else{
                    mfim = ptr_procura->manterior;
                }
                Imprime();
                delete ptr_procura;
                if(Vazia()){
                    minicio = NULL;
                    mfim = NULL;
                }
                if(!Vazia()){
                    ptr_procura = minicio;
                }
            }
            if(!Vazia())
            ptr_procura = ptr_procura->mproximo;
        }
        aux = aux->mproximo;
    }
    if(Vazia()){
        minicio = NULL;
        mfim = NULL;
        cout << -1 << endl;
    }
}

int main(){
    Listadup l1;
    Listadup l2;
    int quantidade_elementos1;
    int quantidade_elementos2;
    int num;
    
    cin >> quantidade_elementos1;

    for(int i = 0; i < quantidade_elementos1; i++){
        cin >> num;
        l1.Insere(num);
    }

    cin >> quantidade_elementos2;

    for(int i = 0; i < quantidade_elementos2; i++){
        cin >> num;
        l2.Insere(num);
    }

    l1.Remove(l2);

    l1.Imprime();
    cout << endl;
    l1.Imprime_Reverso();

    return 0;
}