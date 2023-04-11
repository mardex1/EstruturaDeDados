#include <iostream>
#include <cstdlib>

using namespace std;

typedef int dado;

class Noh{
    friend class Lista;
    private:   
        const dado mdado;
        Noh *mproximo;
    public:
        Noh(dado d = 0);
};

Noh::Noh(dado d) : mdado(d){
    mproximo = NULL;
} 

class Lista{
    private:
        Noh *minicio;
        Noh *mfim;
        int mtamanho;
        void Remove_todos();
        void Imprime_reverso_aux(Noh *umnoh);
    public:
        Lista();
        Lista(const Lista& umalista);
        ~Lista();
        Lista& operator=(const Lista& umalista);
        inline void Insere(dado d);
        void Insere_no_fim(dado d);
        void Insere_no_inicio(dado d);
        void Insere_na_posicao(int posicao, dado d);
        int Procura(dado valor);//Retorna a posição
        void Imprime();
        void Imprime_Reverso();
        inline bool Vazia();
        int Remove_no_fim();
        int Remove_no_inicio();
        void Soma(Lista& l2, int tamanho1, int tamanho2);
};

Lista::Lista(){
    mtamanho = 0;
    minicio = NULL;
    mfim = NULL;
}

Lista::Lista(const Lista& umalista){
    mtamanho = 0;
    minicio = NULL;
    mfim = NULL;

    Noh *aux = umalista.minicio;

    while(aux != NULL){
        Insere_no_fim(aux->mdado);
        aux = aux->mproximo;
    }
}

Lista::~Lista(){
    Remove_todos();
}

void Lista::Remove_todos(){
    Noh *aux = minicio;
    Noh *temp;

    while(aux != NULL){
        temp = aux;
        aux = aux->mproximo;
        delete temp;
    }

    mtamanho = 0;
    minicio = NULL;
    mfim =  NULL;
}

Lista& Lista::operator=(const Lista& umalista){
    // Limpa a lista atual
    Remove_todos();
    // Percorre a lista recebida como parametro, copiando os dados
    Noh *aux = umalista.minicio;

    while(aux != NULL){
        Insere_no_fim(aux->mdado);
        aux = aux->mproximo; 
    }

    return *this;
}
//Como é uma função pequena, foi declarada com inline
void Lista::Insere(dado d){
    Insere_no_fim(d);
}

void Lista::Insere_no_fim(dado d){
    Noh *novo = new Noh(d);

    if(Vazia()){
        minicio = novo;
        mfim = novo;
    }else{
        mfim->mproximo = novo;
        mfim = novo;
    }
    mtamanho++;
}

void Lista::Insere_no_inicio(dado d){
    Noh *novo = new Noh(d);

    if(Vazia()){
        minicio = novo;
        mfim = novo;
    }else{
        novo->mproximo = minicio;
        minicio = novo;
    }
    mtamanho++;
}

void Lista::Insere_na_posicao(int posicao, dado d){
    Noh *novo = new Noh (d);

    if((posicao <= mtamanho) and (posicao >= 0)){
        if(Vazia()){
            minicio = novo;
            mfim = novo;
        }else if(posicao == 0){
            novo->mproximo = minicio;
            minicio = novo;
        }else if(posicao == mtamanho){
            mfim->mproximo = novo;
            mfim = novo;
        }else{//insere no meio
            Noh *aux = minicio;
            int pos_aux = 0;

            //Chegando na posicao da lista
            while(pos_aux < (posicao - 1)){
                aux = aux->mproximo;
                pos_aux++;
            }
            novo->mproximo = aux->mproximo;
            aux->mproximo = novo;
        }
        mtamanho++;

    }else{
        cerr << "Posicao Inexistente!" << endl;
        exit(EXIT_FAILURE);
    }
}

int Lista::Procura(dado valor){
    Noh *aux = minicio;
    int pos_aux = 0;

    while((aux != NULL) and (aux->mdado != valor)){
        pos_aux++;
        aux = aux->mproximo;
    }

    if(aux == NULL){
        pos_aux = -1;
    }

    return pos_aux;
}

void Lista::Imprime(){
    Noh *aux = minicio;

    while(aux != NULL){
        cout << aux->mdado << " ";
        aux = aux->mproximo;
    }
    cout << endl;
}

void Lista::Imprime_Reverso(){
    Imprime_reverso_aux(minicio);
    cout << endl;
}

void Lista::Imprime_reverso_aux(Noh *umnoh){
    if(umnoh != NULL){
        Imprime_reverso_aux(umnoh->mproximo);
        cout << umnoh->mdado << " ";
    }
}

inline bool Lista::Vazia(){
    return (minicio == NULL);
}

int Lista::Remove_no_fim(){
    if(Vazia()){
        cerr << "Remoção de lista vazia!" << endl;
        exit(EXIT_FAILURE);
    }
    Noh *aux = minicio;
    Noh *anterior = NULL;

    while(aux->mproximo != NULL){
        anterior = aux;
        aux = aux->mproximo;
    }
    int temp = mfim->mdado;
    //Parei no penultimo
    if(anterior == NULL)
        minicio = NULL;
    else
        anterior->mproximo = NULL;
    
    delete mfim;
    mfim = anterior;
    mtamanho--;

    return temp;
}   

int Lista::Remove_no_inicio(){
    if(Vazia()){
        cerr << "Remoção de lista vazia!" << endl;
        exit(EXIT_FAILURE);
    }
    Noh* aux = minicio;
    int temp = aux->mdado;
    minicio = aux->mproximo;
    delete aux;

    mtamanho--;
    if(Vazia()){
        mfim = NULL;
    }

    return temp; 
}

void Lista::Soma(Lista& l2, int tamanho1, int tamanho2){
    Lista l3;
    int soma = 0;
    int armazena = 0;
    int v1;
    int v2;
    if(tamanho1 > tamanho2){
        while(tamanho2 > 0){
            v1 = Remove_no_inicio();
            v2 = l2.Remove_no_inicio();
            soma = v1 + v2 + armazena;
            armazena = 0;
            if(soma > 9){
                armazena = soma/10;
                l3.Insere_no_fim(soma % 10);
            }else{
                l3.Insere_no_fim(soma);
            }
            tamanho2--;
            tamanho1--;
            l3.Imprime();
        }
            //l3.Insere_no_fim(Remove_no_inicio() + armazena);
        
    }else{
        while(tamanho1 > 0){
            v1 = Remove_no_inicio();
            v2 = l2.Remove_no_inicio();
            soma = v1 + v2 + armazena;
            armazena = 0;
            if(soma > 9){
                armazena = soma/10;
                l3.Insere_no_fim(soma % 10);
            }else{
                l3.Insere_no_fim(soma);
            }
            tamanho1--;
            tamanho2--;
            l3.Imprime();
        }
    }
    l3.Imprime();
}

int main(){
    Lista l1;
    Lista l2;
    int num;
    int tamanho1;
    int tamanho2;

    while(cin >> num && num != -1){
        l1.Insere(num);
        tamanho1++;
    }

    while(cin >> num && num != -1){
        l2.Insere(num);
        tamanho2++;
    }

    l1.Soma(l2, tamanho1, tamanho2);

    return 0;
}