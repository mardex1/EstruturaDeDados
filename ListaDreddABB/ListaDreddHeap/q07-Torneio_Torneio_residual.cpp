#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

struct num{
    int num_base;
    int num_relativo;
};

typedef num dado;
const int INVALIDO = -1;

class Torneio{
    private:
        dado *mheap;
        int mcapacidade;
        int mtamanho;
        int InicioDados;
        inline int esquerdo(int i){return 2*i+1;}
        inline int direito(int i){return 2*i+2;}
        void Arruma();
        void Copia_maior(int i);
        void Copia_menor(int i);
        void Copia_subindo(int i);
    public:
        Torneio(dado vet[], int tam);
        ~Torneio();
        void Imprime();
        int Espia_raiz();
};

Torneio::Torneio(dado vet[], int tam){
    mcapacidade = 1;
    while(mcapacidade < tam){
        mcapacidade *= 2;
    }
    //Potencia de 2 - 1 + o tamanho do vetor
    mcapacidade = mcapacidade - 1 + tam;
    
    mheap = new dado[mcapacidade];
    InicioDados = mcapacidade - tam;

    for(int i = 0;i < mcapacidade;i++){
        mheap[i].num_base = -1;
        mheap[i].num_relativo = -1;
    }

    memcpy(&mheap[InicioDados], vet, tam*sizeof(dado));
    mtamanho = tam;
    Arruma();
}

Torneio::~Torneio(){
    delete [] mheap;
}

void Torneio::Arruma(){
    for(int i = InicioDados-1; i>=0; i--){
        Copia_maior(i);
    }
}

void Torneio::Copia_maior(int i){
    int esq = esquerdo(i);
    int dir = direito(i);
    if(mheap[esq].num_base == INVALIDO){
        mheap[i].num_relativo = mheap[dir].num_relativo;
    }else if(mheap[dir].num_base == INVALIDO){
        mheap[i].num_relativo = mheap[esq].num_relativo;
    }else if(esq < mcapacidade){
        if((dir < mcapacidade) && (mheap[dir].num_base > mheap[esq].num_base)){
            mheap[i].num_relativo = mheap[dir].num_relativo - mheap[esq].num_relativo; 
            mheap[i].num_base = mheap[dir].num_base;
        }else if(mheap[esq].num_base > mheap[dir].num_base){
            mheap[i].num_relativo = mheap[esq].num_relativo - mheap[dir].num_relativo; 
            mheap[i].num_base = mheap[esq].num_base; 
        }
    }else{
        mheap[i].num_base = INVALIDO;
        mheap[i].num_relativo = INVALIDO;
    }
}


void Torneio::Imprime(){
    for(int i = 0;i < mcapacidade;i++){
        cout << mheap[i].num_relativo << " ";
    }cout << endl;
    for(int i = 0;i < mcapacidade;i++){
        cout << mheap[i].num_base << " ";
    }cout << endl;
}

int Torneio::Espia_raiz(){
    return mheap[0].num_base;
}

int main(){
    int quantidade_participantes;

    cin >> quantidade_participantes;

    dado identificacao[quantidade_participantes];

    for(int i = 0;i < quantidade_participantes;i++){
        cin >> identificacao[i].num_base;
        identificacao[i].num_relativo = identificacao[i].num_base;
    }

    Torneio *h = new Torneio(identificacao, quantidade_participantes);
    
    h->Imprime();

    return 0;
}