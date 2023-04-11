/* avl - Árvore Binária de Busca com Balanceamento AVL
 *
 * by Joukim, Outubro de 2020 - Estrutura de Dados (GCC216)
 * Caracteristicas de implementação outubro de 2019:
 * -> tratamento de exceção
 * -> usa dado na forma chave/valor
 * -> uso de métodos recursivos
 * -> sem duplo encadeamento
 * -> invés de transplanta, usa removeMenor
 */

#include <iostream>
#include <stdexcept>

using namespace std;
#include <stdexcept>

struct dado {
    unsigned ano; // ano é a chave para ordenação na AVL
    string cidadeRealizacao;
    unsigned qtdadeFilmesApresentados;   
};

ostream& operator<<(ostream& saida, const dado& e) {
    saida << "(" << e.ano << "," << e.cidadeRealizacao << "," << e.qtdadeFilmesApresentados << ")";
    return saida;
}

istream& operator>>(istream& entrada, dado& e) {
    entrada >> e.ano >> e.cidadeRealizacao >> e.qtdadeFilmesApresentados;
    return entrada;
}
typedef unsigned tipoChave;

class noh {
    friend class avl;
    private:
        dado elemento;
        noh* esq;
        noh* dir;
        unsigned altura;
    public:
        noh(const dado& umDado):
            elemento(umDado),  esq(NULL), dir(NULL), altura(1) { }
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
        noh* insereAux(noh* umNoh, const dado& umDado);
        noh* removeAux(noh* umNoh, tipoChave chave);
        // métodos para manutenção do balanceamento
        noh* rotacaoEsquerda(noh* umNoh);
        noh* rotacaoDireita(noh* umNoh);
        noh* arrumaBalanceamento(noh* umNoh);
        // busca, método iterativo
        noh* buscaAux(tipoChave chave);
        // função auxiliar do destrutor, usa percorrimento pós-ordem
        void destruirRecursivamente(noh* umNoh);
        void imprimirDir(const std::string& prefixo, const noh* meuNoh);
        void imprimirEsq(const std::string& prefixo, const noh* meuNoh, bool temIrmao);
        void levantamentoAux(noh* umNoh, unsigned& qt_filmes_maior, dado &desempate, int& ano_maior);
    public:
        avl() { raiz = NULL; }
        ~avl();
        void imprimir();
        // inserção e remoção são recursivos
        void insere(const dado& umDado);
        void remove(tipoChave chave);
        // inserção e remoção, métodos recursivos
        // busca retorna uma cópia do objeto armazenado
        dado busca(tipoChave chave);
        // efetua levantamento do ano com maior número de filmes apresentados
        int levantamento();
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

void avl::insere(const dado& umDado) {
    raiz = insereAux(raiz, umDado);
}

// inserção recursiva, devolve nó para atribuição de pai ou raiz
noh* avl::insereAux(noh* umNoh, const dado& umDado) {
    if(umNoh == NULL){
        noh* novo = new noh(umDado);
        return novo;
    }else{
        //Não é folha nula, checa a inserção a direita ou a esquerda
        if(umDado.ano > umNoh->elemento.ano){
            umNoh->dir = insereAux(umNoh->dir,umDado);
        }else if(umDado.ano < umNoh->elemento.ano){
            umNoh->esq = insereAux(umNoh->esq,umDado);
        }else if(umDado.ano == umNoh->elemento.ano){
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
        if(atual->elemento.ano == chave){
            return atual;
        }else if(atual->elemento.ano > chave){
            atual = atual->esq;
        }else{
            atual = atual->dir;
        }
    }
    return atual;
}

// busca elemento com uma dada chave na árvore e retorna o registro completo
dado avl::busca(tipoChave chave) {
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
    if(chave < umNoh->elemento.ano){
        umNoh->esq = removeAux(umNoh->esq, chave);
    }
    //Valor é maior que nó atual, vai pra subárvore direita
    else if(chave > umNoh->elemento.ano){
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

int avl::levantamento( ){
    if(raiz == NULL){
        throw runtime_error("Erro no levantamento: árvore Vazia!");
    }else{
        unsigned qt_filmes_maior = 0;
        int ano_maior = 0;
        dado dado_desempate;
        levantamentoAux(raiz, qt_filmes_maior, dado_desempate, ano_maior);
        return ano_maior;
    }
}

void avl::levantamentoAux(noh* umNoh, unsigned& qt_filmes_maior, dado &dado_desempate, int& ano_maior){
    if(umNoh != NULL){
        levantamentoAux(umNoh->esq, qt_filmes_maior, dado_desempate, ano_maior);
        if((umNoh->elemento.qtdadeFilmesApresentados > qt_filmes_maior)){
            ano_maior = umNoh->elemento.ano;
            qt_filmes_maior = umNoh->elemento.qtdadeFilmesApresentados;
            dado_desempate = umNoh->elemento;
        }else if(umNoh->elemento.qtdadeFilmesApresentados == dado_desempate.qtdadeFilmesApresentados){
            if(umNoh->elemento.ano < dado_desempate.ano){
                ano_maior = umNoh->elemento.ano;
            }else{
                ano_maior = dado_desempate.ano;
            }
        }
        levantamentoAux(umNoh->dir, qt_filmes_maior, dado_desempate, ano_maior);
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
                  << "(" << meuNoh->elemento.ano << "," << meuNoh->elemento.cidadeRealizacao << ")"
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

        std::cout << "(" << meuNoh->elemento.ano << "," << meuNoh->elemento.cidadeRealizacao << ")"
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
        std::cout << "(" << this->raiz->elemento.ano << "," << this->raiz->elemento.cidadeRealizacao << ")" << std::endl;
        // apos imprimir a raiz, chama os respectivos metodos de impressao nas subarvore esquerda e direita
        // a chamada para a impressao da subarvore esquerda depende da existencia da subarvore direita
        imprimirEsq( " " , this->raiz->esq, this->raiz->dir==nullptr );
        imprimirDir( " " , this->raiz->dir );
    } else
        std::cout << "*arvore vazia*" << std::endl;
}

int main() {
    avl arvore;
    tipoChave chave;
    dado umDado;
    unsigned ano;

    char operacao;

    do {
        try {
            cin >> operacao;
            switch (operacao) {
                case 'i': // Inserir recursivamente
                    // objeto recebe nome, cidade e quantidade de filmes apresentados
                    cin >> umDado;
                    arvore.insere(umDado);
                    break;
                case 'r': // Remover recursivamente
                    cin >> chave;
                    arvore.remove(chave);
                    break;
                case 'b': // Buscar
                    cin >> chave; // ler a chave
                    umDado = arvore.busca(chave); // escrever os dados do festival
                    cout << "Elemento buscado: " << umDado << endl;
                    break;
                case 'l': // Levantamento pelo ano com maior número de filmes apresentados
                    ano = arvore.levantamento( );
                    cout << "Edição com maior quantidade de filmes apresentados: " << ano << endl;
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
