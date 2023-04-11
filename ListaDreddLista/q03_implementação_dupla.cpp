#include <iostream>
#include <string>

using namespace std;

class elemento{
    friend class lista;
    private:
        int chave;
        elemento *proximo;
        elemento *anterior;
    public:
        elemento (int c){
            chave = c;
            proximo = NULL;
            anterior = NULL;
        }
};

class lista{
    private:
        elemento *inicio;
        elemento *fim;
    public:
        lista();
        ~lista();        
        void insereInicio(int c);
        void insereFim (int c);
        int removeRepetidos();//retorna a quantidade de elementos restantes na lista
        bool vazia();
        void imprimeLista();
};
    
lista::lista(){
    inicio = NULL;
    fim = NULL;
}
        
lista::~lista(){
    elemento *aux = inicio;
    elemento *temp;

    while(aux != NULL){
        temp = aux;
        aux = aux->proximo;
        delete temp;
    }

    inicio = NULL;
    fim = NULL;
}  

void lista::insereInicio (int c){
    elemento *novo = new elemento(c);

    if(vazia()){
        inicio = novo;
        fim = novo;
    }else{
        novo->proximo = inicio;
        inicio->anterior = novo;
        inicio = novo;
    }
}
        
void lista::insereFim (int c){
    elemento *novo = new elemento(c);

    if(vazia()){
        inicio = novo;
        fim = novo;
    }else{
        fim->proximo = novo;
        novo->anterior = fim;
        fim = novo;
    }
}
        
int lista::removeRepetidos(){
    elemento *aux = inicio;
    elemento *ptr_procura;
    int temp;


    while(aux != NULL){
        ptr_procura = aux->proximo;
        temp = aux->chave;
        while(ptr_procura != NULL){
            if(ptr_procura->chave == temp){
                elemento *anterior = ptr_procura->anterior;
                elemento *proximo = ptr_procura->proximo;
                if(anterior != NULL)
                    anterior->proximo = proximo;
                if(proximo != NULL)
                    proximo->anterior = anterior;
                delete ptr_procura;
                ptr_procura = aux;
            }
            ptr_procura = ptr_procura->proximo;
        }
        aux = aux->proximo;
    }
    
    aux = inicio;
    int quantidade_elementos = 0;

    while(aux != NULL){
        quantidade_elementos++;
        aux = aux->proximo;
    }

    return quantidade_elementos;
}

bool lista::vazia(){
    if(inicio == NULL){
        return true;
    }
    return false;
}
        
void lista::imprimeLista(){
    if (inicio != NULL){
        elemento *auxiliar = inicio;
        while (auxiliar->proximo != NULL){
            cout<<"("<<auxiliar->chave<<") ";
            auxiliar =  auxiliar->proximo;
        }
        cout<<"("<<auxiliar->chave<<")"<<endl;
    } else {
            cout<<"VAZIA";
    }
}       
    
int main(){
    
    lista listaD;
    
    int chave;
    string dado;
    
    cin>>chave;
    
    while (chave != -1){
        listaD.insereFim(chave);        
        cin>>chave;  
    }
    cout<<listaD.removeRepetidos()<<endl;
    listaD.imprimeLista();
    
    
    return 0;
}

