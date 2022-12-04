#include <iostream>
using namespace std;


class noh{
    friend class pilha;
    private:
        noh *proximo;
        int mvalor;
    public:
        noh(int valor);  
};

noh::noh(int valor){
    mvalor = valor;
    proximo = NULL;
}

class pilha{
    private:
        noh *topo;
        int tamanho;
    public:
        pilha();
        ~pilha();
        void empilha(const int& valor);
        int desempilha();
        void ordena();
        bool vazia();
        int espia();
};

pilha::pilha(){
    topo = NULL;
    tamanho = 0;
}

pilha::~pilha(){
    while(topo){
        desempilha();
    }
}

void pilha::empilha(const int& valor){
    noh* novo = new noh(valor);
    novo->proximo = topo;
    topo = novo;
    tamanho++;
}

int pilha::desempilha(){
    int aux = topo->mvalor;
    noh* temp = topo;
    topo = topo->proximo;
    delete temp;
    tamanho--;
    return aux;
}

bool pilha::vazia(){
    if(tamanho == 0){
        return true;
    }else{
        return false;
    }
} 


int pilha::espia(){
    return topo->mvalor;
}


int main(){
    pilha p1, p2;
    int n;
    int num;
    int temp;

    cin >> n;

    for(int i = 0;i < n;i++){
        cin >> num;
        p1.empilha(num);
    }

    while(!p1.vazia()){
        temp = p1.desempilha();
        while((!p2.vazia()) and (temp > p2.espia())){
            p1.empilha(p2.desempilha());
        }
        p2.empilha(temp);
    }

    for(int i = 0;i < n;i++){
        cout << p2.desempilha() << " ";
    }cout << endl;

    return 0;
}