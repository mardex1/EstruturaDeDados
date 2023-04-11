/* avl - Árvore Binária de Busca com Balanceamento AVL
 *
 * by Joukim, Outubro de 2019 - Estrutura de Dados (GCC216)
 * Caracteristicas de implementação outubro de 2019:
 * -> tratamento de exceção
 * -> usa pokemon na forma id/valor
 * -> uso de métodos recursivos
 * -> sem duplo encadeamento
 * -> invés de transplanta, usa removeMenor
 */

#include <iostream>
#include <stdexcept>

using namespace std;

typedef unsigned tipoChave;

struct pokemon {
    unsigned id;
    string nome;
    string tipo;
    int nivel;
};

ostream& operator<<(ostream& saida, const pokemon& e) {
    saida << "(" << e.id << "," << e.nome << "," << e.tipo << "," << e.nivel << ")";
    return saida;
}

istream& operator>>(istream& entrada, pokemon& e) {
    entrada >> e.id >> e.nome >> e.tipo >> e.nivel;
    return entrada;
}

class noh {
    friend class avl;
    private:
        pokemon elemento;
        noh* esq;
        noh* dir;
        unsigned altura;
    public:
        noh(const pokemon& umPokemon):
            elemento(umPokemon),  esq(NULL), dir(NULL), altura(1) { }
        ~noh() { }
        int fatorBalanceamento(noh* umNoh);
        int Informar_altura(noh* umNoh);
        void Atualiza_altura(noh* umNoh);
        int Maximo(int alt_arv_esq, int alt_arv_dir);
};

int noh::fatorBalanceamento(noh* umNoh) {
    int alt_arv_esq = Informar_altura(umNoh->esq);
    int alt_arv_dir = Informar_altura(umNoh->dir);
    int fator_bal = alt_arv_esq - alt_arv_dir;
    return fator_bal;
}

void noh::Atualiza_altura(noh* umNoh){
    int alt_arv_esq = Informar_altura(umNoh->esq);
    int alt_arv_dir = Informar_altura(umNoh->dir);   
    umNoh->altura = 1 + Maximo(alt_arv_esq, alt_arv_dir);
}

int noh::Maximo(int alt_arv_esq, int alt_arv_dir){
    if(alt_arv_dir > alt_arv_esq){
        return alt_arv_dir;
    }else{
        return alt_arv_esq;
    }
}

int noh::Informar_altura(noh* umNoh){
    if(umNoh == NULL){
        return 0;
    }else{
        return umNoh->altura;
    }
}

class avl {
    friend ostream& operator<<(ostream& output, avl& arvore);
    private:
        noh* raiz;
        // funções auxiliares para remoção
        noh* encontraMenor(noh* raizSub);
        noh* removeMenor(noh* raizSub);
        // funções auxiliares para inserção e remoção usando método recursivo
        // retorna o nó para ajustar o pai ou o raiz
        noh* insereAux(noh* umNoh, const pokemon& umPokemon);
        noh* removeAux(noh* umNoh, tipoChave id);
        // métodos para manutenção do balanceamento
        noh* rotacaoEsquerda(noh* umNoh);
        noh* rotacaoDireita(noh* umNoh);
        noh* arrumaBalanceamento(noh* umNoh);
        // busca, método iterativo
        noh* buscaAux(tipoChave id);
        // função auxiliar do destrutor, usa percorrimento pós-ordem
        void destruirRecursivamente(noh* umNoh);
        void imprimirDir(const std::string& prefixo, const noh* meuNoh);
        void imprimirEsq(const std::string& prefixo, const noh* meuNoh, bool temIrmao);
        void levantamentoAux(noh* umNoh, string tipo, int nivel, int& qtd);
    public:
        avl() { raiz = NULL; }
        ~avl();
        void imprimir();
        // inserção e remoção são recursivos
        void insere(const pokemon& umPokemon);
        void remove(tipoChave id);
        // inserção e remoção, métodos recursivos
        // busca retorna uma cópia do objeto armazenado
        pokemon busca(tipoChave id);
        // efetua levantamento de quantos pokemons existem de um dado tipo e nível
        int levantamento(string tipo, int nivel);
};

// destrutor
avl::~avl() {
    destruirRecursivamente(raiz);
}

// destrutor é recursivo, fazendo percorrimento pós-ordem
void avl::destruirRecursivamente(noh* umNoh) {
    if(umNoh != NULL){
        destruirRecursivamente(umNoh->esq);
        destruirRecursivamente(umNoh->dir);
        delete umNoh;
    }
}

void avl::insere(const pokemon& umDado) {
    raiz = insereAux(raiz, umDado);
}

// inserção recursiva, devolve nó para atribuição de pai ou raiz
noh* avl::insereAux(noh* umNoh, const pokemon& umDado) {
    if(umNoh == NULL){
        noh* novo = new noh(umDado);
        return novo;
    }else{
        //Não é folha nula, checa a inserção a direita ou a esquerda
        if(umDado.id > umNoh->elemento.id){
            umNoh->dir = insereAux(umNoh->dir,umDado);
        }else if(umDado.id < umNoh->elemento.id){
            umNoh->esq = insereAux(umNoh->esq,umDado);
        }else if(umDado.id < umNoh->elemento.id){
            throw runtime_error("Erro na inserção: chave já existente!");
            
        }
    }
    return arrumaBalanceamento(umNoh);
}

// checa e arruma, se necessário, o balanceamento em umNoh,
// fazendo as rotações e ajustes necessários
noh* avl::arrumaBalanceamento(noh* umNoh) {
    
    if(umNoh == NULL){
        return umNoh;
    }
    //inicialmente atualiza a altura de umNoh
    umNoh->Atualiza_altura(umNoh);
    //Checa o balanceamento no nó 
    int fator_bal = umNoh->fatorBalanceamento(umNoh);
    //Retorna o no acima da arvore, caso esteja balanceado
    if((fator_bal >= -1) and (fator_bal <= 1)) {
        return umNoh;
    }
    //Caso 1: Desbalanceamento esquerda esquerda
    else if((fator_bal > 1) and (umNoh->fatorBalanceamento(umNoh->esq)) >= 0) {
        return rotacaoDireita(umNoh);
    }
    //Caso 2: Desbalanceamento esquerda direita
    else if((fator_bal > 1) and (umNoh->fatorBalanceamento(umNoh->esq) < 0)){
        umNoh->esq = rotacaoEsquerda(umNoh->esq);
        return rotacaoDireita(umNoh);
    }
    //Caso 3: Desbalanceamento direita direita
    else if((fator_bal < -1) and (umNoh->fatorBalanceamento(umNoh->dir) <= 0)){
        return rotacaoEsquerda(umNoh);
    }
    else if((fator_bal < -1) and(umNoh->fatorBalanceamento(umNoh->dir) > 0)){
        umNoh->dir = rotacaoDireita(umNoh->dir);
        return rotacaoEsquerda(umNoh);
    }
    return umNoh;
}


// rotação à esquerda na subárvore com raiz em umNoh
// retorna o novo pai da subárvore
noh* avl::rotacaoEsquerda(noh* umNoh) {
    //Acha o filho a direita da raiz da subarvore
    noh* Noh_aux = umNoh->dir;
    // armazena subárvore à esquerda do nó auxiliar 
    // à direita da raiz atual
    umNoh->dir = Noh_aux->esq;
    // Posiciona umNoh como filho a esquerda de aux
    Noh_aux->esq = umNoh;
    //Atualiza alturas
    umNoh->Atualiza_altura(umNoh);
    Noh_aux->Atualiza_altura(Noh_aux);   
    
    //Atualiza a nova raiz da subarvore
    return Noh_aux;
    }


// rotação à direita na subárvore com raiz em umNoh
// retorna o novo pai da subárvore
noh* avl::rotacaoDireita(noh* umNoh) {
    //Acha filho a esquerda da raiz da subarvore
    noh* noh_aux = umNoh->esq;
    //Armazena a subarvore a direita de noh aux à esquerda da raiz atual
    umNoh->esq = noh_aux->dir;
    //Posiciona um noh como filho à direita de noh aux
    noh_aux->dir = umNoh;

    umNoh->Atualiza_altura(umNoh);
    noh_aux->Atualiza_altura(noh_aux);
    
    return noh_aux;
}


// método de busca auxiliar (retorna o nó), iterativo
noh* avl::buscaAux(tipoChave chave) {
    noh* atual = raiz;

    while(atual != NULL){
        if(atual->elemento.id == chave){
            return atual;
        }else if(atual->elemento.id > chave){
            atual = atual->esq;
        }else{
            atual = atual->dir;
        }
    }
    return atual;
}

// busca elemento com uma dada chave na árvore e retorna o registro completo
pokemon avl::busca(tipoChave chave) {
    noh* resultado = buscaAux(chave);
    if (resultado != NULL)
        return resultado->elemento;
    else
        throw runtime_error("Erro na busca: elemento não encontrado!");
}

// nó mínimo (sucessor) de subárvore com raiz em raizSub (folha mais à esquerda)
noh* avl::encontraMenor(noh* raizSub) {
    while(raizSub->esq != NULL){
        raizSub = raizSub->esq;
    }
    return raizSub;
}

// procedimento auxiliar para remover o sucessor substituíndo-o pelo
// seu filho à direita
noh* avl::removeMenor(noh* raizSub) {
    if(raizSub->esq == NULL){
        return raizSub->dir;
    }else{
        raizSub->esq = removeMenor(raizSub->esq);
        return arrumaBalanceamento(raizSub);
    }
}

// remoção recursiva
void avl::remove(tipoChave chave) {
    raiz = removeAux(raiz, chave);
}

noh* avl::removeAux(noh* umNoh, tipoChave chave) {
    if(umNoh == NULL){
        throw runtime_error("Erro na remoção: chave não encontrada!");
    }
    noh* nova_raiz_suba = umNoh;
    // Valor é menor que nó atual, vai para subárvore esquerda
    if(chave < umNoh->elemento.id){
        umNoh->esq = removeAux(umNoh->esq, chave);
    }
    //Valor é maior que nó atual, vai pra subárvore direita
    else if(chave > umNoh->elemento.id){
        umNoh->dir = removeAux(umNoh->dir, chave);
    }
    //Valor igual ao no atual, que deve ser apagado
    else{
        //nó não tem filhos a esquerda
        if(umNoh->esq == NULL){
            nova_raiz_suba = umNoh->dir;
        //Nó não tem filhos a direita
        }else if(umNoh->dir == NULL){
            nova_raiz_suba = umNoh->esq;
        //nó tem dois filhos
        }else{
            //Trocando pelo sucessor
            nova_raiz_suba = encontraMenor(umNoh->dir);
            //Onde antes estava o sucessor fica agora seu filho à direita
            nova_raiz_suba->dir = removeMenor(umNoh->dir);  
            //Filho à esquerda de umNoh torna-se filho à esquerda do sucessor
            nova_raiz_suba->esq = umNoh->esq;
        }
        delete umNoh;
    }
    return arrumaBalanceamento(nova_raiz_suba);
}

int avl::levantamento(string tipo, int nivel){
    int qtd = 0;
    levantamentoAux(raiz, tipo, nivel, qtd);
    return qtd;
}

void avl::levantamentoAux(noh* umNoh, string tipo, int nivel, int &qtd){
    if(umNoh != NULL){
        if((umNoh->elemento.tipo == tipo) and (umNoh->elemento.nivel == nivel)){
            qtd++;
        }
        levantamentoAux(umNoh->esq, tipo, nivel, qtd);
        levantamentoAux(umNoh->dir, tipo, nivel, qtd);
    }
}

ostream& operator<<(ostream& output, avl& arvore) {
    arvore.imprimir();
    return output;
}

// imprime formatado seguindo o padrao tree as subarvores direitas de uma avl
void avl::imprimirDir(const std::string& prefixo, const noh* meuNoh)
{
    if( meuNoh != nullptr )
    {
        std::cout << prefixo
                  << "└d─"
                  << "(" << meuNoh->elemento.id << "," << meuNoh->elemento.nome << ")"
                  << std::endl;

        // Repassa o prefixo para manter o historico de como deve ser a formatacao e chama no filho direito e esquerdo
        imprimirEsq( prefixo + "    " , meuNoh->esq , meuNoh->dir==nullptr );
        imprimirDir( prefixo + "    " , meuNoh->dir );
    }
}

// imprime formatado seguindo o padrao tree as subarvores direitas de uma avl
void avl::imprimirEsq(const std::string& prefixo, const noh* meuNoh, bool temIrmao)
{
    if( meuNoh != nullptr )
    {
        std::cout << prefixo ;

        // A impressao da arvore esquerda depende da indicacao se existe o irmao a direita
        if (temIrmao)
            std::cout << "└e─" ;
        else
            std::cout << "├e─";

        std::cout << "(" << meuNoh->elemento.id << "," << meuNoh->elemento.nome << ")"
                  << std::endl;

        // Repassa o prefixo para manter o historico de como deve ser a formatacao e chama no filho direito e esquerdo
        imprimirEsq( prefixo + "│   " , meuNoh->esq, meuNoh->dir==nullptr );
        imprimirDir( prefixo + "│   " , meuNoh->dir );
    }
}

// imprime formatado seguindo o padrao tree uma avl
void avl::imprimir()
{
    if( this->raiz != nullptr )
    {
        std::cout << "(" << this->raiz->elemento.id << "," << this->raiz->elemento.nome << ")" << std::endl;
        // apos imprimir a raiz, chama os respectivos metodos de impressao nas subarvore esquerda e direita
        // a chamada para a impressao da subarvore esquerda depende da existencia da subarvore direita
        imprimirEsq( " " , this->raiz->esq, this->raiz->dir==nullptr );
        imprimirDir( " " , this->raiz->dir );
    } else
        std::cout << "*arvore vazia*" << std::endl;
}

int main() {
    avl arvore;
    tipoChave id;
    pokemon umPokemon;
    string tipo;
    int nivel;
    int quantidade;

    char operacao;

    do {
        try {
            cin >> operacao;
            switch (operacao) {
                case 'i': // Inserir recursivamente
                    // objeto recebe id, nome, tipo e nível
                    cin >> umPokemon;
                    arvore.insere(umPokemon);
                    break;
                case 'r': // Remover recursivamente
                    cin >> id;
                    arvore.remove(id);
                    break;
                case 'b': // Buscar
                    cin >> id; // ler o id
                    umPokemon = arvore.busca(id); // escrever dados do pokemon
                    cout << "Elemento buscado: " << umPokemon << endl;
                    break;
                case 'l': // Levantamento por tipo e nível
                    cin >> tipo >> nivel;
                    quantidade = arvore.levantamento(tipo, nivel);
                    cout << "Levantamento de pokemons tipo " << tipo
                         << " e nível " << nivel << ": " << quantidade << endl;
                    break;
                case 'e': // Escrever tudo (em ordem)
                    cout << arvore;
                    break;
                case 'f': // Finalizar execução
                    break;
                default:
                    cout << "Comando invalido!\n";
            }
        } catch (runtime_error& e) {
            cout << e.what() << endl;
        }
    } while (operacao != 'f');

    return 0;
}