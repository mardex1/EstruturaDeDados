#include <iostream>
#include <queue>
#include <stdexcept>

using namespace std;

typedef int Dado;

enum Posicao {DIR, ESQ};

class Noh {
    friend class ABB;
    public:
        Noh(Dado d);
    private:
        Dado valor;
        Noh* esquerdo;
        Noh* direito;
};

Noh::Noh(Dado d) {
    valor = d;
    esquerdo = NULL;
    direito = NULL;
}

class ABB {
    public:
        ABB();
        ~ABB();
        void Remove_pos_ordem();
        // Escreve uma Ã¡rvore nÃ­vel a nÃ­vel.
        // Pode ser Ãºtil para depurar o programa.
        void EscreverNivelANivel(std::ostream& saida);
        // Insere um dado na Ã¡rvore.
        void Inserir(Dado d);
        // Retorna o nro de folhas na Ã¡rvore.
        unsigned NroDeFolhas();
        unsigned Percorre_em_ordem(Noh* um_noh, unsigned &quantidade);
    private:
        Noh* raiz;
        void Remove_pos_ordem_aux(Noh* um_noh);
        Noh* Inserir_rec_aux(Noh* um_noh, Dado um_valor);
};

ABB::~ABB(){
    Remove_pos_ordem();
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

ABB::ABB(){
    raiz = NULL;
}

void ABB::Inserir(Dado d) {
    raiz = Inserir_rec_aux(raiz, d);
}

Noh* ABB::Inserir_rec_aux(Noh* um_noh, Dado um_valor){
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

unsigned ABB::NroDeFolhas(){
    unsigned folhas = 0;
    folhas = Percorre_em_ordem(raiz, folhas);
    return folhas;
}

unsigned ABB::Percorre_em_ordem(Noh* um_noh, unsigned &quantidade){
    if(um_noh != NULL){
        Percorre_em_ordem(um_noh->esquerdo, quantidade);
        if(um_noh->direito == NULL and um_noh->esquerdo == NULL){
            quantidade++;
        }
        Percorre_em_ordem(um_noh->direito, quantidade);
    }
    return quantidade;
}

void ABB::EscreverNivelANivel(ostream& saida) {
    queue<Noh*> filhos;
    Noh aux = Dado();
    Noh* fimDeNivel = &aux; // marcador especial para fim de nivel
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

int main() {
    unsigned qtde;
    cin >> qtde;
    ABB arvore;
    Dado valor;
    for (unsigned i = 0; i < qtde; ++i) {
        cin >> valor;
        arvore.Inserir(valor);
    }
    cout << arvore.NroDeFolhas() << endl;
    return 0;
}