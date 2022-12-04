#include <iostream>
using namespace std;

class Noh{
    friend class Pilha;
    private:    
        Noh *mproximo;
        char mvalor;
    public:
        Noh(char valor);
};

Noh::Noh(char valor){
    mproximo = NULL;
    mvalor = valor;
}

class Pilha{
    private:
        Noh *mtopo;
        int mtamanho;
    public:
        Pilha();
        ~Pilha();
        void Empilha(const char& valor);
        char Desempilha();
        int Tamanho();
        char Espia();
        bool Vazia();
};

Pilha::Pilha(){
    mtopo = NULL;
    mtamanho = 0;
}

Pilha::~Pilha(){
    while(mtopo){
        Desempilha();
    }
}

void Pilha::Empilha(const char& valor){
    Noh *temp = new Noh(valor);
    temp->mproximo = mtopo;
    mtopo = temp;
    mtamanho++;
}

char Pilha::Desempilha(){
    char valor = mtopo->mvalor;
    Noh *temp = mtopo;
    mtopo = mtopo->mproximo;
    delete temp;
    mtamanho--;
    return valor;
}

int Pilha::Tamanho(){
    return mtamanho;
}

char Pilha::Espia(){
    return mtopo->mvalor;
}

bool Pilha::Vazia(){
    if(mtamanho == 0){
        return true;
    }else{
        return false;
    }
}

int main(){
    Pilha p1, p2;
    char letra;
    int contador_b = 0;
    bool especial = false;

    do{
        cin >> letra;
        
        if(letra == 'A'){
            p1.Empilha(letra);
        }else if(letra == 'C'){
            p2.Empilha(letra);
        }else if(letra == 'B'){
            contador_b++;
        }else{
            especial = true;
        }
    }
    while(letra != 'X');

    if(p2.Tamanho() == 1){
        especial = true;
    }else if(contador_b == 1){
        while((!p1.Vazia()) and (!p2.Vazia())){
            p1.Desempilha();
            p2.Desempilha();
            p2.Desempilha();
        }
    }
    
    if(!especial){
        cout << "nao" << " " << p1.Tamanho() << " " << p2.Tamanho() << endl;
    }else if(p1.Tamanho() == 0 && p2.Tamanho() == 0){
        cout << "sim" << " " << p1.Tamanho() << " " << p2.Tamanho() << endl;
    }else{
        cout << "nao" << " " << p1.Tamanho() << " " << p2.Tamanho() << endl;
    }
}