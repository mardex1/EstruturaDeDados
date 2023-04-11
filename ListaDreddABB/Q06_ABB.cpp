#include <iostream>

using namespace std;

typedef int dado;

struct Data{
    int nivel;
    unsigned quantidade;
    int conteudo;
};

class Noh{
    friend class ABB;
    private:
        Data valor;
        Noh* esquerdo;
        Noh* direito;
    public:
        Noh(dado um_valor, int nivel);
};

Noh::Noh(dado um_valor, int nivel){
    valor.conteudo = um_valor;
    valor.nivel = nivel;
    valor.quantidade = 1;
    esquerdo = NULL;
    direito = NULL;
}

class ABB{
    private:
        Noh* raiz;
        Noh* Minimo_aux(Noh* raiz_subarvore);
        Noh* Busca_aux(dado um_valor);
        void Remove_pos_ordem_aux(Noh* um_noh);
        Noh* Inserir_rec_aux(Noh* um_noh, dado um_valor, int &nivel);
        Noh* Remove_menor(Noh* raiz_sub);
        Noh* Remover_rec_aux(Noh* um_noh, dado um_valor);
        void Percorre_em_ordem(Noh* um_noh);
        void Nivela(Noh* um_noh);
        int Informar_altura(Noh* um_noh);
        int Maximo(int esq, int dir);
    public:
        ABB();
        ~ABB();
        void Inserir(dado um_valor);
        Noh* Minimo();
        dado Busca(dado um_valor);
        void Remove_pos_ordem();
        void Remover_recursivamente(dado um_valor);
        void Imprime();
        void Atualiza_altura(Noh* um_noh);
};

ABB::ABB(){
    raiz = NULL;
}

ABB::~ABB(){
    Remove_pos_ordem();
}

void ABB::Inserir(dado um_valor){
    int nivel = -1;
    raiz = Inserir_rec_aux(raiz, um_valor, nivel);
}

Noh* ABB::Inserir_rec_aux(Noh* um_noh, dado um_valor, int &nivel){
    nivel++;
    if(um_noh == NULL){
        Noh* novo = new Noh(um_valor, nivel);
        return novo;
    }else{
        //não é folha nula, checa a inserção a direita ou a esquerda
        if(um_valor == um_noh->valor.conteudo){
            um_noh->valor.quantidade++;
            return um_noh;
        }
        else if(um_valor < um_noh->valor.conteudo){
            um_noh->esquerdo = Inserir_rec_aux(um_noh->esquerdo, um_valor, nivel);
        }else if(um_valor > um_noh->valor.conteudo){
            um_noh->direito = Inserir_rec_aux(um_noh->direito, um_valor, nivel);
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

void ABB::Imprime(){
    Percorre_em_ordem(raiz);
    cout << endl;
}

void ABB::Percorre_em_ordem(Noh* um_noh){
    if(um_noh != NULL){
        cout << um_noh->valor.conteudo << "(" << um_noh->valor.quantidade << ")/" << um_noh->valor.nivel << " ";
        Percorre_em_ordem(um_noh->esquerdo);
        Percorre_em_ordem(um_noh->direito);
    }
}

Noh* ABB::Minimo_aux(Noh* raiz_subarvore){
    while(raiz_subarvore->esquerdo != NULL){
        raiz_subarvore = raiz_subarvore->esquerdo;
    }
    return raiz_subarvore;
}

Noh* ABB::Remove_menor(Noh* raiz_sub){
    if(raiz->esquerdo == NULL){
        return raiz_sub->direito;
    }else{
        raiz_sub->esquerdo = Remove_menor(raiz_sub->esquerdo);
        return raiz_sub;    
    }
}

void ABB::Remover_recursivamente(dado um_valor){
    raiz = Remover_rec_aux(raiz, um_valor);
}

Noh* ABB::Remover_rec_aux(Noh* um_noh, dado um_valor){
    if(um_noh == NULL){
        cerr << "Nó não encontrado" << endl;
    }else{
        Noh* nova_raiz_sub = um_noh;
        //Valor menor que o nó atual, vai para a sub esq
        if(um_valor < um_noh->valor.conteudo){
            um_noh->esquerdo = Remover_rec_aux(um_noh->esquerdo, um_valor);
        //Valor maior que o nó atual, vai para a sub dir
        }else if(um_valor > um_noh->valor.conteudo){
            um_noh->direito = Remover_rec_aux(um_noh->direito, um_valor);
        //Valor é igual ao que deve ser apagado
        }else{
            if(um_noh->valor.quantidade == 1){
                //Nó não tem filhos a esq
                if(um_noh->esquerdo == NULL){
                    nova_raiz_sub = um_noh->direito;
                    Atualiza_altura(um_noh);
                    
                }
                //Nó não tem filhos a dir
                else if(um_noh->direito == NULL){
                    nova_raiz_sub = um_noh->esquerdo;
                    Atualiza_altura(um_noh);
                }
                //Nó tem dois filhos, pode-se trocar por antecessor ou sucessor
                else{
                    //SUCESSOR
                    nova_raiz_sub = Minimo_aux(um_noh->direito);
                    //Troca o sucessor pelo seu filho a direita
                    nova_raiz_sub->direito = Remove_menor(um_noh->direito);
                    //Filho a esq de um noh torna-se filho a esquerda do sucessor
                    nova_raiz_sub->esquerdo = um_noh->esquerdo;
                    nova_raiz_sub->valor.nivel = um_noh->valor.nivel;
                }
                delete um_noh;
            }else{
                um_noh->valor.quantidade--;
                return nova_raiz_sub;
            }
        }
        return nova_raiz_sub;
    }
}

void ABB::Nivela(Noh* um_noh){
    if(um_noh != NULL){
        um_noh->valor.nivel--;
        Percorre_em_ordem(um_noh->esquerdo);
        Percorre_em_ordem(um_noh->direito);
    }
}

int ABB::Informar_altura(Noh* um_noh){
    if(um_noh == NULL){
        return 0;
    }else{
        return um_noh->valor.nivel;
    }
}

void ABB::Atualiza_altura(Noh* um_noh){
    int alt_arv_esq = Informar_altura(um_noh->esquerdo);
    int alt_arv_dir = Informar_altura(um_noh->direito);
    um_noh->valor.nivel = 1 + Maximo(alt_arv_esq, alt_arv_dir);
}

int ABB::Maximo(int esq, int dir){
    if(esq > dir){
        return esq;
    }else{
        return dir;
    }
}



int main(){
    ABB a1;
    int num;
    
    for(unsigned i = 0;i < 10;i++){
        cin >> num;
        a1.Inserir(num);
    }

    a1.Imprime();
    
    for(unsigned i = 0;i < 5;i++){
        cin >> num;
        a1.Remover_recursivamente(num);
    }

    a1.Imprime();
    
    for(unsigned i = 0;i < 10;i++){
        cin >> num;
        a1.Inserir(num);
    }

    a1.Imprime();

    for(unsigned i = 0;i < 5;i++){
        cin >> num;
        a1.Remover_recursivamente(num);
    }

    a1.Imprime();

    return 0;
}


