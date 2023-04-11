#include <iostream>
#include <cstdlib>

using namespace std;

struct Compras{
    string nome;
    int quantidade;
};

typedef Compras dado;

class Noh{
    friend class Lista;
    private:   
        const dado mdado;
        Noh *mproximo;
    public:
        Noh(dado d);
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
        void Consulta(string nome, dado valor);//Retorna a posição
        void Imprime();
        inline bool Vazia();
        void Remove_no_fim();
        void Remove_no_inicio();
        void Remove_no_especifico(string nome);
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
    Noh *aux = minicio;

    while((aux != NULL) and (aux->mdado.nome != d.nome)){
        aux = aux->mproximo;
    }
    if(aux == NULL){
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
}

void Lista::Consulta(string nome, dado valor){
    Noh *aux = minicio;

    while((aux != NULL) and (aux->mdado.nome != nome)){
        aux = aux->mproximo;
    }

    if(aux == NULL){
        cout << "item nao existente" << endl;
    }else{
        cout << "(" << aux->mdado.nome << ", " << aux->mdado.quantidade << ")" << endl;
    }

}

void Lista::Imprime(){
    Noh *aux = minicio;
    cout << "[";
    while(aux != NULL){
        if(aux->mproximo == NULL){
            cout << "(" << aux->mdado.nome << ", " << aux->mdado.quantidade << ")";
        }else{
            cout << "(" << aux->mdado.nome << ", " << aux->mdado.quantidade << "), ";
        }
        aux = aux->mproximo;
    }
    cout << "]";
    cout << endl;
}

inline bool Lista::Vazia(){
    return (minicio == NULL);
}

void Lista::Remove_no_fim(){
    if(Vazia()){
        cerr << "Remoção de lista vazia!" << endl;
        exit(EXIT_FAILURE);
    }
    Noh *aux = minicio;
    Noh *anterior;

    while(aux->mproximo != NULL){
        anterior = aux;
        aux = aux->mproximo;
    }

    //Parei no penultimo
    delete mfim;
    anterior->mproximo = NULL;
    mfim = anterior;


    if(Vazia()){
        minicio = NULL;
    }
    mtamanho--;
}   

void Lista::Remove_no_inicio(){
    if(Vazia()){
        cerr << "Remoção de lista vazia!" << endl;
        exit(EXIT_FAILURE);
    }
    Noh* aux = minicio;
    minicio = minicio->mproximo;
    delete aux;

    mtamanho--;
    if(mtamanho == 0){
        mfim = NULL;
    }
    
}

void Lista::Remove_no_especifico(string nome){
    Noh *aux = minicio;
    Noh *anterior;
    while(aux != NULL && aux->mdado.nome != nome){
        anterior = aux;
        aux = aux->mproximo;
    }
    if(aux != NULL){
        if(aux == minicio){
            Remove_no_inicio();
        }else if(aux == mfim){
            Remove_no_fim();
        }else{
            anterior->mproximo = aux->mproximo;
            mtamanho--;
            delete aux;
        }
    }else{
        cout << "item nao existente" << endl;
    }
}

int main(){
    Lista l1;
    Compras produto; 
    char opcao;
    string nome;
    do{
        cin >> opcao;
        switch(opcao){
            case 'i':
                cin >> produto.nome >> produto.quantidade;
                l1.Insere(produto);
                break;
            case 'r':
                cin >> nome;
                l1.Remove_no_especifico(nome);
                break;
            case 'c':
                cin >> nome;
                l1.Consulta(nome, produto);
                break;
            case 'p':
                l1.Imprime();
                break;
            case 'q':
                l1.Imprime();
                break;
        }
    }while(opcao != 'q');

    return 0;
}