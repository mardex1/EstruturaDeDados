#include <iostream>
#include <cstdlib>

using namespace std;

typedef int dado;

class Noh{
    friend class Lista;
    private:   
        const dado mdado;
        Noh *mproximo;
    public:
        Noh(dado d = 0);
};

Noh::Noh(dado d) : mdado(d){
    mproximo = NULL;
} 

class Lista{
    private:
        Noh *minicio;
        Noh *mfim;
        int mtamanho;
        void Remove_todos();
    public:
        Lista();
        ~Lista();
        inline void Insere(dado d);
        void Insere_no_fim(dado d);
        void Imprime();
        inline bool Vazia();
        int Remove_no_inicio();
        void Divide(int pos);   
};

Lista::Lista(){
    mtamanho = 0;
    minicio = NULL;
    mfim = NULL;
}

Lista::~Lista(){
    Remove_todos();
}

void Lista::Remove_todos(){
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
void Lista::Insere(dado d){
    Insere_no_fim(d);
}

void Lista::Insere_no_fim(dado d){
    Noh *novo = new Noh(d);

    if(Vazia()){
        minicio = novo;
        mfim = novo;
    }else{
        mfim->mproximo = novo;
        mfim = novo;
    }
    mtamanho++;
}

void Lista::Imprime(){
    Noh *aux = minicio;

    while(aux != NULL){
        cout << aux->mdado << " ";
        aux = aux->mproximo;
    }
    cout << endl;
}

inline bool Lista::Vazia(){
    return (minicio == NULL);
}

int Lista::Remove_no_inicio(){
    Noh* aux = minicio;
    minicio = minicio->mproximo;
    int temp = aux->mdado;
    delete aux;

    mtamanho--;
    if(mtamanho == 0){
        mfim = NULL;
    }
    return temp;
}

void Lista::Divide(int pos){
    Lista aux;
    if(pos+1 > mtamanho){
        Imprime();
        cout << -1 << endl;
    }else{
        for(int i = 0; i < pos+1;i++){
            aux.Insere(Remove_no_inicio());
        }
        aux.Imprime();
        Imprime();
    }
}


int main(){
    Lista l1;

    int elementos;
    int num;

    cin >> elementos;

    for(int i = 0; i < elementos; i++){
        cin >> num;
        l1.Insere(num);
    }

    int pos;
    cin >> pos;

    l1.Divide(pos);

    return 0;
}