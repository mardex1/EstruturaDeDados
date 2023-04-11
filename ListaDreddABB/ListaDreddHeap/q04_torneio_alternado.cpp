#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

typedef int dado;
const int INVALIDO = -1;

class Torneio{
    private:
        dado *mheap;
        int mcapacidade;
        int mtamanho;
        int InicioDados;
        inline int pai(int i){return (i-1)/2;}
        inline int esquerdo(int i){return 2*i+1;}
        inline int direito(int i){return 2*i+2;}
        void Arruma();
        void Copia_maior(int i);
        void Copia_menor(int i);
    public:
        Torneio(dado vet[], int tam);
        ~Torneio();
        void Imprime();
        int Retorna_campeao();
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

    memcpy(&mheap[InicioDados], vet, tam*sizeof(dado));

    mtamanho = tam;

    Arruma();
}

Torneio::~Torneio(){
    delete [] mheap;
}

void Torneio::Arruma(){
    int aux = 1;
    //Se etapa for true, Max heap
    //Se etapa for false, Min heap 
    bool etapa = false;
    int cont = 0;
    while(aux < mtamanho){
        aux *= 2;
    }
    while(aux > 0){
        if(etapa == true)
            etapa = false;
        else if(etapa == false)
            etapa = true;
        if(etapa == true){
            while(cont < aux/2){
                Copia_maior(InicioDados-1);
                InicioDados--;
                cont++;
            }
            cont = 0;
        }else{
            while(cont < aux/2){
                Copia_menor(InicioDados-1);
                InicioDados--;
                cont++;
            }
            cont = 0;
        }
        aux = aux/2;
    }
}

void Torneio::Copia_maior(int i){
    int esq = esquerdo(i);
    int dir = direito(i);

    int maior = INVALIDO;

    if(esq < mcapacidade){
        if(dir < mcapacidade && mheap[dir] > mheap[esq]){
            maior = dir;
        }else{
            maior = esq; 
        }
        mheap[i] = mheap[maior];
    }else{
        mheap[i] = INVALIDO;
    }
}

void Torneio::Copia_menor(int i){
    int esq = esquerdo(i);
    int dir = direito(i);

    int menor = INVALIDO;
    if(mheap[esq] == INVALIDO){
        mheap[i] = mheap[dir];
    }else if(mheap[dir] == INVALIDO){
        mheap[i] = mheap[esq];
    }else if(esq < mcapacidade){
        if(dir < mcapacidade && mheap[dir] < mheap[esq]){
            menor = dir;
        }else{
            menor = esq; 
        }
        mheap[i] = mheap[menor];
    }else{
        mheap[i] = INVALIDO;
    }
}

void Torneio::Imprime(){
    for(int i = 0;i < mcapacidade;i++){
        cout << mheap[i] << " ";
    }cout << endl;
}

int Torneio::Retorna_campeao(){
    return mheap[0];
}

int main(){
    int quantidade_participantes;
    cin >> quantidade_participantes;

    int identificacao[quantidade_participantes];

    for(int i = 0;i < quantidade_participantes;i++){
        cin >> identificacao[i];
    }

    Torneio *h = new Torneio(identificacao, quantidade_participantes);

    cout << h->Retorna_campeao() << endl;

    return 0;
}