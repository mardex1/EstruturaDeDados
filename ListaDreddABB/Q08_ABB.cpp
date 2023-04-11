#include <iostream>
#include <exception>

using namespace std;

typedef int dado;

struct Dado{
    int chave;
    string palavra;
};

class Noh{
    friend class ABB;
    private:
        Dado valor;
        Noh* esquerdo;
        Noh* direito;
    public:
        Noh(int c, string p);
};

Noh::Noh(int c, string p){
    valor.chave = c;
    valor.palavra = p;
    esquerdo = NULL;
    direito = NULL;
}

class ABB{
    private:
        Noh* raiz;
        Noh* Minimo_aux(Noh* raiz_subarvore);
        Noh* Busca_aux(int chave);
        void Remove_pos_ordem_aux(Noh* um_noh);
        Noh* Inserir_rec_aux(Noh* um_noh, int c, string p);
        Noh* Remove_menor(Noh* raiz_sub);
        Noh* Remover_rec_aux(Noh* um_noh, int chave);
        void Percorre_em_ordem(Noh* um_noh);
    public:
        ABB();
        ~ABB();
        void Inserir(int c, string p);
        Noh* Minimo();
        string Busca(int c);
        void Remove_pos_ordem();
        void Remover_recursivamente(Dado um_valor);
        void Imprime();
};

ABB::ABB(){
    raiz = NULL;
}

ABB::~ABB(){
    Remove_pos_ordem();
}

void ABB::Inserir(int c, string p){
    raiz = Inserir_rec_aux(raiz, c, p);
}

Noh* ABB::Inserir_rec_aux(Noh* um_noh, int c, string p){
    if(um_noh == NULL){
        Noh* novo = new Noh(c, p);
        return novo;
    }else{
        //não é folha nula, checa a inserção a direita ou a esquerda
        if(c < um_noh->valor.chave){
            um_noh->esquerdo = Inserir_rec_aux(um_noh->esquerdo, c, p);
        }else{
            um_noh->direito = Inserir_rec_aux(um_noh->direito, c, p);
        }
    }
    return um_noh;
}

Noh* ABB::Busca_aux(int chave){
    Noh* atual = raiz;

    while(atual != NULL){
        if(atual->valor.chave == chave){
            return atual;
        }else if(atual->valor.chave > chave){
            atual = atual->esquerdo;
        }else{
            atual = atual->direito;
        }
    }
    return atual;
}

string ABB::Busca(int c){
    Noh* noh_com_valor = Busca_aux(c);

    if(noh_com_valor == NULL){
        return "INEXISTENTE";
    }else{
        return noh_com_valor->valor.palavra;
    }
}

void ABB::Remove_pos_ordem(){
    Remove_pos_ordem_aux(raiz);
}

void ABB::Remove_pos_ordem_aux(Noh* um_noh){
    if(um_noh != NULL){
        Remove_pos_ordem_aux(um_noh->esquerdo);
        Remove_pos_ordem_aux(um_noh->direito);
        delete um_noh;
    }
}

Noh* ABB::Remove_menor(Noh* raiz_sub){
    if(raiz->esquerdo == NULL){
        return raiz_sub->direito;
    }else{
        raiz_sub->esquerdo = Remove_menor(raiz_sub->esquerdo);
        return raiz_sub;
    }
}

void ABB::Imprime(){
    Percorre_em_ordem(raiz);
    cout << endl;
}

void ABB::Percorre_em_ordem(Noh* um_noh){
    if(um_noh != NULL){
        Percorre_em_ordem(um_noh->esquerdo);
        cout << um_noh->valor.chave << " ";
        Percorre_em_ordem(um_noh->direito);
    }
}

int main(){
    char opcao;
    int chave;
    string palavra;
    ABB a1;
    do{
        cin >> opcao;
        switch(opcao){
            case 'i':
                cin >> chave >> palavra;
                a1.Inserir(chave, palavra);
                break;
            case 'b':
                cin >> chave;
                cout << a1.Busca(chave) << endl;
                break;
            case 'e':
                a1.Imprime();
                break;
        }
    }while(opcao != 'f');
    
    return 0;
}


