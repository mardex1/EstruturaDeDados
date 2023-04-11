#include <iostream>
#include <cstdlib>

using namespace std;

struct aluno{
    string nome;
    int matricula;
    int periodo;
};

typedef aluno dado;

class Noh{
    friend class Listadup;
    private:   
        const dado mdado;
        Noh *mproximo;
        Noh *manterior;
    public:
        Noh(dado d);
};

Noh::Noh(dado d) : mdado(d){
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
        inline void Insere(dado &d);
        void Insere_no_fim(dado &d);
        void Imprime();
        void Imprime_Reverso();
        inline bool Vazia();
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
void Listadup::Insere(dado &d){
    Insere_no_fim(d);
}

void Listadup::Insere_no_fim(dado &d){
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
    
    cout << "[";
    while(aux != NULL){
        if(aux->mproximo == NULL){
            cout << aux->mdado.matricula << " - " << aux->mdado.nome;
        }else{
            cout << aux->mdado.matricula << " - " << aux->mdado.nome << ", ";
        }
        aux = aux->mproximo;
    }
    cout << "]";
    cout << endl;
}

void Listadup::Imprime_Reverso(){
    Noh *aux = mfim;

    cout << "[";
    while(aux != NULL){
        if(aux->manterior == NULL){
            cout << aux->mdado.matricula << " - " << aux->mdado.nome;
        }else{
            cout << aux->mdado.matricula << " - " << aux->mdado.nome << ", ";
        }
        aux = aux->manterior;
    }
    cout << "]";
    cout << endl;
} 

inline bool Listadup::Vazia(){
    return (mtamanho == 0);
}

int main(){
    int quantidade_alunos;
    aluno estudante;
    Listadup l1;
    cin >> quantidade_alunos;

    for(int i = 0; i < quantidade_alunos; i++){
        cin >> estudante.matricula >> estudante.nome >> estudante.periodo;
        l1.Insere(estudante);
    }

    l1.Imprime();

    l1.Imprime_Reverso();
    
    return 0;
}