#include <iostream>
#include <cstdlib>

using namespace std;

typedef char dado;

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
        char Remove_no_fim();
        char Remove_no_inicio();
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

char Lista::Remove_no_inicio(){
    if(Vazia()){
        cerr << "Remoção de lista vazia!" << endl;
        exit(EXIT_FAILURE);
    }
    Noh* aux = minicio;
    char temp = aux->mdado;
    minicio = aux->mproximo;
    delete aux;

    mtamanho--;
    if(Vazia()){
        mfim = NULL;
    }

    return temp; 
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
        cout << aux->mdado;
        aux = aux->mproximo;
    }
    cout << endl;
}

inline bool Lista::Vazia(){
    if(mtamanho == 0){
        return true;
    }else{
        return false;
    }
}

char Lista::Remove_no_fim(){
    if(Vazia()){
        cerr << "Remoção de lista vazia!" << endl;
        exit(EXIT_FAILURE);
    }
    Noh *aux = minicio;
    Noh *anterior = NULL;

    while(aux->mproximo != NULL){
        anterior = aux;
        aux = aux->mproximo;
    }
    char temp = mfim->mdado;
    //Parei no penultimo
    if(anterior == NULL)
        minicio = NULL;
    else
        anterior->mproximo = NULL;
    
    delete mfim;
    mfim = anterior;
    mtamanho--;

    return temp;
}

int main(){
    Lista l1;
    Lista aux;
    char letra;

    while(cin >> letra && letra != '#'){
        l1.Insere(letra);
        aux.Insere(letra);
    }

    Lista l2;
    char temp1;
    char temp2;
    bool achou = true;

    while(!aux.Vazia() && achou == true){
        temp1 = aux.Remove_no_fim();
        temp2 = l1.Remove_no_inicio();
        if(temp1 != temp2){
            achou = false;
        }
    }

    if(achou == true){
        cout << "sim" << endl;
    }else{
        cout << "nao" << endl;
    }
    
    return 0;
}