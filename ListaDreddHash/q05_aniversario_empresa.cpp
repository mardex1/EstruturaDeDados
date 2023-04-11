#include <iostream>
#include <cstdlib>

using namespace std;

typedef string dado;

const int UMPRIMO = 23;
int funcao_hash(int dia, int mes, int capacidade){
    return (dia * mes - 1) % capacidade;
}

class Noh{
    friend class Lista;
    private:   
        int dia;
        int mes;
        string nome;
        int ano;
        Noh *mproximo;
    public:
        Noh(string n, int d, int m, int a);
};

Noh::Noh(string n, int d, int m, int a){
    dia = d;
    mes = m;
    nome = n;
    ano = a;
    mproximo = NULL;
}

class Lista{
    friend class Hash;
    private:
        Noh *minicio;
        Noh *mfim;
        int mtamanho;
        void Remove_todos();
    public:
        Lista();
        ~Lista();
        void Insere_no_fim(string nome, int dia, int mes, int ano;);
        void Insere_na_posicao(int posicao, dado c);
        void Imprime();
        inline bool Vazia();
        void Remove_no_fim();
        void Remove_no_inicio();
        void remove_valor(dado c);
        dado Busca(dado c);
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

void Lista::Insere_no_fim(string nome, int dia, int mes, int ano){
    Noh *novo = new Noh(nome, dia, mes, ano);

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
        cout << aux->nome << " ";
        aux = aux->mproximo;
    }
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
    Noh *anterior = NULL;

    while(aux->mproximo != NULL){
        anterior = aux;
        aux = aux->mproximo;
    }

    //int temp = aux->chave;
    //Parei no penultimo
    if(anterior == NULL){
        minicio = NULL;
    }else{
        anterior->mproximo = NULL;
    }

    delete mfim;
    mfim = anterior;
    mtamanho--;
}   

void Lista::Remove_no_inicio(){
    if(Vazia()){
        cerr << "Remoção de lista vazia!" << endl;
        exit(EXIT_FAILURE);
    }
    Noh* aux = minicio;
    //int temp = aux->chave;
    minicio = aux->mproximo;
    delete aux;

    mtamanho--;
    if(Vazia()){
        mfim = NULL;
    }
}

dado Lista::Busca(string nome){
    Noh *aux = minicio;

    while(aux != NULL){
        if(aux->nome == nome){
            return aux->valor;
        }else{
            aux = aux->mproximo;
        }
    }

    return "NAO ENCONTRADO";
}

class Hash{
    friend class Lista;
    private:
        Lista* tabela;
        int capacidade;
    public:
        Hash(unsigned cap);
        ~Hash();
        void Insere_elemento(string nome, int dia, int mes, int ano);
        dado Recupera_valor(dado c);
};

Hash::Hash(int cap){
    capacidade = cap;
    tabela = new Lista[cap];
}

Hash::~Hash(){
    for(int i = 0;i < capacidade;i++){
        tabela[i].Remove_todos();
    }
    delete[] tabela;
}

void Hash::Insere_elemento(string nome, int dia, int mes, int ano){
    int posicao = funcao_hash(dia, mes, capacidade);
    tabela[posicao].Insere_no_fim(nome, dia, mes, ano);
}

dado Hash::Recupera_valor(dado c){
    int posicao = funcao_hash(c);
    dado elemento = tabela[posicao].Busca(c);
    if(elemento == "NAO ENCONTRADO"){
        return "-1";
    }else{
        return elemento; 
    }
}

int main(){
    unsigned quantidade_posicoes;
    cin >> quantidade_posicoes;
    Hash tabela(quantidade_posicoes);
    unsigned quantidade_funcionarios;
    cin >> quantidade_funcionarios;

    string nome;
    int dia;
    int mes;
    int ano;

    for(unsigned i = 0;i < quantidade_funcionarios;i++){
        cin >> nome >> dia >> mes >> ano;
        tabela.Insere_elemento(nome, dia, mes, ano);
    }

    return 0;
}