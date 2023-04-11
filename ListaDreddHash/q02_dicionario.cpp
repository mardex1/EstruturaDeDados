#include <iostream>
#include <cstdlib>

using namespace std;

typedef string dado;

const int UMPRIMO = 23;
int funcao_hash(dado c){
    int tamanho_da_palavra = c.size();
    return tamanho_da_palavra % 23;
}

class Noh{
    friend class Lista;
    private:   
        dado chave;
        string valor;
        Noh *mproximo;
    public:
        Noh(dado c, string v);
};

Noh::Noh(dado c, string v){
    chave = c;
    valor = v;
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
        void Insere_no_fim(dado c, string v);
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

void Lista::Insere_no_fim(dado c, string v){
    Noh *novo = new Noh(c, v);

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
        cout << aux->chave << " ";
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

dado Lista::Busca(dado c){
    Noh *aux = minicio;

    while(aux != NULL){
        if(aux->chave == c){
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
        Hash(int cap);
        ~Hash();
        void Insere_elemento(dado c, string v);
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

void Hash::Insere_elemento(dado c, string v){
    int posicao = funcao_hash(c);
    tabela[posicao].Insere_no_fim(c, v);
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
    Hash tabela_hash(UMPRIMO);
    int quantidade_palavras;
    cin >> quantidade_palavras;
    dado palavra;
    string significado;
    for(int i = 0;i < quantidade_palavras;i++){
        cin >> palavra;
        getline(cin, significado);
        tabela_hash.Insere_elemento(palavra, significado);
    }
    dado palavra_buscada;
    string resultado;
    cin >> palavra_buscada;
    while(palavra_buscada != "-1"){
        resultado = tabela_hash.Recupera_valor(palavra_buscada);
        if(resultado == "-1"){
            cout << "[" << palavra_buscada << "]" << " => NULL" << endl;
        }else{
            cout << "[" << palavra_buscada << "]" << " => " << resultado << endl;
        }
        cin >> palavra_buscada;
    }

    return 0;
}
