#include <iostream>
#include <queue>

typedef int dado;

enum Posicao {DIR, ESQ};

class Noh {
    friend class ABB;
    public:
        Noh (dado d);
    private:
        dado valor;
        Noh* esquerdo;
        Noh* direito;
};

Noh::Noh(dado um_valor){
    valor = um_valor;
    esquerdo = NULL;
    direito = NULL;
}

class ABB{
    private:
        Noh* raiz;
        void Remove_pos_ordem_aux(Noh* um_noh);
        Noh* Inserir_rec_aux(Noh* um_noh, dado um_valor);
        void Percorre_em_ordem(Noh* um_noh, dado &um_valor);
    public:
        ABB();
        ~ABB();
        void Inserir(dado um_valor);
        void Remove_pos_ordem();
        void EscreverNivelANivel(std::ostream& saida);
        void Sucessor(dado &um_valor);
};


using namespace std;


void ABB::EscreverNivelANivel(ostream& saida) {
    queue<Noh*> filhos;
    Noh noh = dado();
    Noh* fimDeNivel = &noh; // noh especial para fim de nivel
    filhos.push(raiz);
    filhos.push(fimDeNivel);
    while (not filhos.empty()) {
        Noh* ptNoh = filhos.front();
        filhos.pop();
        if (ptNoh == fimDeNivel) {
            saida << "\n";
            if (not filhos.empty())
                filhos.push(fimDeNivel);
        }
        else {
            saida << '[';
            if (ptNoh != NULL) {
                saida << ptNoh->valor;
                filhos.push(ptNoh->esquerdo);
                filhos.push(ptNoh->direito);
            }
            saida << ']';
        }
    }
}

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

void ABB::Sucessor(dado &um_valor){
    Percorre_em_ordem(raiz, um_valor);
    cout << endl;
}

void ABB::Percorre_em_ordem(Noh* um_noh, dado &um_valor){
    if(um_noh != NULL){
        Percorre_em_ordem(um_noh->esquerdo, um_valor);
        if(um_noh->valor > um_valor){
            cout << um_noh->valor << " ";
        }
        Percorre_em_ordem(um_noh->direito, um_valor);
    }
}

// === Programa ================================================================
int main() {
    ABB arvore;
    dado chave;
    char operacao;
    do {
        cin >> operacao;
        switch (operacao) {
            case 'i': // Inserir
                cin >> chave;
                arvore.Inserir(chave);
                break;
            case 'e': // Escrever
                arvore.EscreverNivelANivel(cout);
                break;
            case 's': { // Sucessor
                cin >> chave;
                arvore.Sucessor(chave);
                break;
            }
        }
    } while (operacao != 'f');
    return 0;
}
