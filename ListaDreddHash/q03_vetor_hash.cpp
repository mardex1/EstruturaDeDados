#include <iostream>
#include <cstdlib>

using namespace std;

typedef int dado;


int funcao_hash(int k, int n){
    return k % n;
}

struct Vetor{
    int chave;
    string valor;
};

class Noh{
    friend class Hash;
    private:   
        Vetor vetor[4];
        int mtamanho;
    public:
        Noh();
};

Noh::Noh(){
    for(int i = 0;i < 4;i++){
        vetor[i].chave = -1;
        vetor[i].valor = "";
    }
    mtamanho = 0;
}

class Hash{
    private:
        Noh* tabela;
        int capacidade;
    public:
        Hash(int cap);
        ~Hash();
        void Insere_elemento(dado c, string v);
        string Recupera_valor(dado c);
        void Imprime_vetor(int posicao);
};

Hash::Hash(int cap){
    capacidade = cap;
    tabela = new Noh[cap];
}

Hash::~Hash(){
    delete[] tabela;
}

void Hash::Insere_elemento(dado c, string v){
    int posicao = funcao_hash(c, capacidade);
    int cont = -1;
    bool repetido = false;
    bool fim = false;
    do{
        cont++;
        if(tabela[posicao].vetor[cont].chave == c){
            repetido = true;
            fim = true;
            cout << "ITEM JÁ ESTÁ NA TABELA!" << endl;
        }
    }while(tabela[posicao].vetor[cont].chave != -1 and cont <= 4);

    if(tabela[posicao].vetor[cont].chave == -1 and repetido == false){
            tabela[posicao].vetor[cont].chave = c;
            tabela[posicao].vetor[cont].valor = v;
            fim = true;
    }
    if(fim == false){
        cout << "NÚMERO MÁXIMO DE COLISÕES PARA CHAVE!" << endl;
    }
}

string Hash::Recupera_valor(dado c){
    int posicao = funcao_hash(c, capacidade);
    int cont = -1;
    bool achou = false;
    string valor;
    do{
        cont++;
        if(tabela[posicao].vetor[cont].chave == c){
            achou = true;
            valor = tabela[posicao].vetor[cont].valor;
        }
    }while(tabela[posicao].vetor[cont].chave != c and cont <= 4);

    if(achou == false){
        cout << "NÃO ENCONTRADO!";
    }

    return valor;
}

void Hash::Imprime_vetor(int posicao){
    for(int i = 0;i < 4;i++){  
        cout << "[" << tabela[posicao].vetor[i].chave << "/" << tabela[posicao].vetor[i].valor << "]";   
    }
    cout << endl;
}

int main(){
    int tamanho_hash;
    cin >> tamanho_hash;
    Hash tabela(tamanho_hash);
    int quantidade_dados;
    cin >> quantidade_dados;

    int chave;
    string valor;

    for(int i = 0;i < quantidade_dados;i++){
        cin >> chave >> valor;
        tabela.Insere_elemento(chave, valor);
    }

    int recupera;

    for(int i = 0;i < 4;i++){
        cin >> recupera;
        cout << tabela.Recupera_valor(recupera) << endl;
    }
    
    for(int i = 0;i < tamanho_hash;i++){
        cout << i << ":";
        tabela.Imprime_vetor(i);
    }
    cout << endl;

    return 0;
}
