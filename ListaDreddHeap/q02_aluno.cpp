#include <iostream>   
#include <string>
#include <algorithm>
#include <stdexcept>

struct Atividade {
        int nota;
        int tentativas;
};

class Aluno {
    public:
        Aluno();
        Aluno(unsigned matr, const std::string& n, unsigned capAtiv);
        Aluno(const Aluno& umAluno); // construtor de cópia para evitar problemas
                                     // com atributos dinâmicos
        ~Aluno();
        void InserirAtividade(const Atividade& a);
        std::string Nome() const { return nome; }
        unsigned Matricula() { return matricula; }
        float Media() const;
        int Tentativas() const;
        Aluno& operator=(const Aluno& umAluno); // sobrecarga do operador de atribuição
                                                // para evitar problemas com atributos dinâmicos
    private:
        unsigned matricula;
        std::string nome;
        unsigned capAtividades;
        Atividade* vetAtividades;
        unsigned nroAtividades;
};

Aluno::Aluno()
    : matricula(0), nome(""), capAtividades(0), nroAtividades(0) {
    vetAtividades = NULL;
}

Aluno::Aluno(unsigned matr, const std::string& n, unsigned capAtiv) 
    : matricula(matr), nome(n), capAtividades(capAtiv), nroAtividades(0) {
    vetAtividades = new Atividade[capAtiv];
}

Aluno::Aluno(const Aluno& umAluno) {
    matricula = umAluno.matricula;
    nome = umAluno.nome;
    capAtividades = umAluno.capAtividades;
    nroAtividades = umAluno.nroAtividades;
    vetAtividades = new Atividade[capAtividades];
    std::copy(umAluno.vetAtividades, umAluno.vetAtividades + capAtividades, vetAtividades);
}

Aluno::~Aluno() {
    delete[] vetAtividades;
}

Aluno& Aluno::operator=(const Aluno& umAluno) {
    matricula = umAluno.matricula;
    nome = umAluno.nome;
    capAtividades = umAluno.capAtividades;
    nroAtividades = umAluno.nroAtividades;
    delete[] vetAtividades;
    vetAtividades = new Atividade[capAtividades];
    std::copy(umAluno.vetAtividades, umAluno.vetAtividades + capAtividades, vetAtividades);
    return *this;
}

void Aluno::InserirAtividade(const Atividade& a) {
    vetAtividades[nroAtividades] = a;
    nroAtividades++;
}

float Aluno::Media() const {
    float soma = 0.0f;
    for (unsigned i = 0; i < nroAtividades; i++)       
        soma += float(vetAtividades[i].nota);  
    return soma / float(nroAtividades);
}

int Aluno::Tentativas() const {
    int tentativas = 0;
    for (unsigned i = 0; i < nroAtividades; i++)
        tentativas += vetAtividades[i].tentativas;
    return tentativas;
}

bool operator>(const Aluno& a1, const Aluno& a2) {
}

typedef Aluno TDado;

class Heap {
    // classe Heap (max-heap, o maior fica na raiz/inicio)
    public:
        // Criar heap sem dados e com capacidade informada
        Heap(int cap);
        // Destruttor
        ~Heap();
        // Inserir um dado na heap
        void Inserir(const TDado& d);
        // Consulta a raiz
        TDado Raiz();
        // Retira e retorna a raiz
        TDado Retirar();
        // Verifica se a heap está vazia
        bool Vazia();
    protected:
        void ArrumarDescendo(int i);
        void ArrumarSubindo(int i);
        inline int Direito(int i);
        inline int Esquerdo(int i);
        inline int Pai(int i);
        int mCapacidade;
        int mTamanho;
        TDado* mVetDados;
};

using namespace std;

Heap::Heap(int cap) {
}

Heap::~Heap() {
}

void Heap::ArrumarDescendo(int i) {
    // Arruma as posicoes de i para baixo.
}

void Heap::ArrumarSubindo(int i) {
    // Arruma as posicoes de i para cima.
}

int Heap::Pai(int i) {
}

int Heap::Esquerdo(int i) {
}

int Heap::Direito(int i) {
}

TDado Heap::Raiz() {
    if (mTamanho == 0) 
        throw runtime_error("Heap vazia nao tem raiz");

    // completar
}

TDado Heap::Retirar() {
    if (mTamanho == 0) 
        throw runtime_error("Heap vazia nao tem raiz");

    // completar
}

bool Heap::Vazia() {
}

void Heap::Inserir(const TDado& d){
if (mTamanho == mCapacidade) 
        throw runtime_error("Impossivel inserir em heap cheio.");

    // completar
}

int main() {
    unsigned qtdeAlunos;
    cin >> qtdeAlunos;
    unsigned qtdeAtividades;
    cin >> qtdeAtividades;
    Heap heap(qtdeAlunos);
    Atividade atividade;
    string nome;
    unsigned matricula;
    for (unsigned i = 0; i < qtdeAlunos; i++) {
        cin >> matricula >> nome;
        Aluno aluno(matricula, nome, qtdeAtividades);
        for (unsigned i = 0; i < qtdeAtividades; i++) {
            cin >> atividade.nota >> atividade.tentativas;
            aluno.InserirAtividade(atividade);
        }
        heap.Inserir(aluno);
    }
    Aluno alunoDestaque(heap.Retirar());
    cout << '[' << alunoDestaque.Matricula() << "] " << alunoDestaque.Nome() << endl;
    return 0;
}
