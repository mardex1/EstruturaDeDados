#include <iostream>

using namespace std;

typedef int dado;

class Noh{
    friend class ABB;
    private:
        dado valor;
        Noh* esquerdo;
        Noh* direito;
    public:
        Noh(dado um_valor);
};

Noh::Noh(dado um_valor){
    valor = um_valor;
    esquerdo = NULL;
    direito = NULL;
}

class ABB{
    private:
        Noh* raiz;
        Noh* Minimo_aux(Noh* raiz_subarvore);
        Noh* Busca_aux(dado um_valor);
        void Remove_pos_ordem_aux(Noh* um_noh);
        Noh* Inserir_rec_aux(Noh* um_noh, dado um_valor);
        Noh* Remove_menor(Noh* raiz_sub);
        Noh* Remover_rec_aux(Noh* um_noh, dado um_valor);
        unsigned Percorre_em_ordem(Noh* um_noh, int &quantidade);
    public:
        ABB();
        ~ABB();
        void Inserir(dado um_valor);
        Noh* Minimo();
        dado Busca(dado um_valor);
        void Remove_pos_ordem();
        void Remover_recursivamente(dado um_valor);
        void Calcula_no();
};

ABB::ABB(){
    raiz = NULL;
}

ABB::~ABB(){
    Remove_pos_ordem();
}

void ABB::Inserir(dado um_valor){
    raiz = Inserir_rec_aux(raiz, um_valor);
}

Noh* ABB::Inserir_rec_aux(Noh* um_noh, dado um_valor){
    if(um_noh == NULL){
        Noh* novo = new Noh(um_valor);
        return novo;
    }else{
        //não é folha nula, checa a inserção a direita ou a esquerda
        if(um_valor < um_noh->valor){
            um_noh->esquerdo = Inserir_rec_aux(um_noh->esquerdo, um_valor);
        }else{
            um_noh->direito = Inserir_rec_aux(um_noh->direito, um_valor);
        }
    }
    return um_noh;
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

void ABB::Calcula_no(){
    int quantidade_no = 0;
    int qt_sub_esq = 0;
    int qt_sub_dir = 0;

    quantidade_no = Percorre_em_ordem(raiz, quantidade_no);
    qt_sub_esq = Percorre_em_ordem(raiz->esquerdo, qt_sub_esq);
    qt_sub_dir = Percorre_em_ordem(raiz->direito, qt_sub_dir);
    
    cout << quantidade_no << " " << qt_sub_esq - qt_sub_dir << endl;
}

unsigned ABB::Percorre_em_ordem(Noh* um_noh, int &quantidade){
    if(um_noh != NULL){
        Percorre_em_ordem(um_noh->esquerdo, quantidade);
        quantidade++;
        Percorre_em_ordem(um_noh->direito, quantidade);
    }
    return quantidade;
}

int main(){
    ABB a1;
    int num;

    cin >> num;

    while(num != -1){
        a1.Inserir(num);
        cin >> num;
    }

    a1.Calcula_no();
}


