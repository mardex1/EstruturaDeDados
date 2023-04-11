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
        void Percorre_em_ordem(Noh* um_noh);
    public:
        ABB();
        ~ABB();
        void Inserir(dado um_valor);
        Noh* Minimo();
        dado Busca(dado um_valor);
        void Remove_pos_ordem();
        void Remover_recursivamente(dado um_valor);
        void Imprime();
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

Noh* ABB::Minimo(){
    if(raiz == NULL){
        cerr << "erro, arvore vazia" << endl;
    }else{
        Noh* noh_minimo = Minimo_aux(raiz);
        return noh_minimo;
    }
}

Noh* ABB::Minimo_aux(Noh* raiz_subarvore){
    while(raiz_subarvore->esquerdo != NULL){
        raiz_subarvore = raiz_subarvore->esquerdo;
    }
    return raiz_subarvore;
}

Noh* ABB::Busca_aux(dado um_valor){
    Noh* atual = raiz;

    while(atual != NULL){
        if(atual->valor == um_valor){
            return atual;
        }else if(atual->valor > um_valor){
            atual = atual->esquerdo;
        }else{
            atual = atual->direito;
        }
    }
    return atual;
}

dado ABB::Busca(dado um_valor){
    Noh* noh_com_valor = Busca_aux(um_valor);

    if(noh_com_valor == NULL){
        cerr << "Valor não encontrado" << endl;
    }else{
        return noh_com_valor->valor;
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

void ABB::Remover_recursivamente(dado um_valor){
    raiz = Remover_rec_aux(raiz, um_valor);
}

Noh* ABB::Remover_rec_aux(Noh* um_noh, dado um_valor){
    if(um_noh == NULL){
        cerr << "Nó não encontrado" << endl;
    }else{
        Noh* nova_raiz_sub = um_noh;
        //Valor menor que o nó atual, vai para a sub esq
        if(um_valor < um_noh->valor){
            um_noh->esquerdo = Remover_rec_aux(um_noh->esquerdo, um_valor);
        //Valor maior que o nó atual, vai para a sub dir
        }else if(um_valor > um_noh->valor){
            um_noh->direito = Remover_rec_aux(um_noh->direito, um_valor);
        //Valor é igual ao que deve ser apagado
        }else{
            //Nó não tem filhos a esq
            if(um_noh->esquerdo == NULL){
                nova_raiz_sub = um_noh->direito;
            }
            //Nó não tem filhos a dir
            else if(um_noh->direito == NULL){
                nova_raiz_sub = um_noh->esquerdo;
            }
            //Nó tem dois filhos, pode-se trocar por antecessor ou sucessor
            else{
                //SUCESSOR
                nova_raiz_sub = Minimo_aux(um_noh->direito);
                //Troca o sucessor pelo seu filho a direita
                nova_raiz_sub->direito = Remove_menor(um_noh->direito);
                //Filho a esq de um noh torna-se filho a esquerda do sucessor
                nova_raiz_sub->esquerdo = um_noh->esquerdo;
            }

            delete um_noh;
        }
        return nova_raiz_sub;
    }
}

void ABB::Imprime(){
    Percorre_em_ordem(raiz);
    cout << endl;
}

void ABB::Percorre_em_ordem(Noh* um_noh){
    if(um_noh != NULL){
        Percorre_em_ordem(um_noh->esquerdo);
        cout << um_noh->valor << " ";
        Percorre_em_ordem(um_noh->direito);
    }
}

int main(){
    ABB arvore;
    
    int num;
    cin >> num;

    int n;

    for(int i = 0;i < num;i++){
        cin >> n;
        arvore.Inserir(n);
    }

    cin >> n;

    cout << arvore.Busca(n) << endl;

    cin >> n;
    
    arvore.Remover_recursivamente(n);

    arvore.Imprime();
}


