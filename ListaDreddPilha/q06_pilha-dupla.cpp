/* Classe pilha dupla, duas pilhas usando um armazenamento 
 * compartilhado em um vetor com 50 posições
 *
 * by Joukim, 2019, Estruturas de Dados
 *
 */

#include <iostream>

using namespace std;

// pilha dupla em vetor de 50 elementos
// não é permitido alterar a estrutura da classe
// inserindo ou retirando métodos
// classe não precisa de destrutor, já que não 
// aloca dados dinamicamente
class pilhaDupla {
private:
    int topo1;
    int topo2;
    int tamanho1;
    int tamanho2;
    int dados[50];
public:
    pilhaDupla();
    // escolha é um inteiro para indicar qual pilha sendo usada:
    // 1 -> pilha 1 (início do arranjo)
    // 2 -> pilha 2 (final do arranjo)
    void empilha(int escolha, int valor); // empilha valor na pilha escolhida
    int desempilha(int escolha); // retorna o topo da pilha escolhida
    bool vazia(int escolha); // verifica se pilha escolhida é vazia
};


pilhaDupla::pilhaDupla() {
    tamanho1 = 0;
    topo1 = -1;
    tamanho2 = 0;
    topo2 = 50; 
}

void pilhaDupla::empilha(int escolha, int valor) {
    if(tamanho1+tamanho2 > 50){
        cout << "INVALIDO" << endl;
    }else{
        if(escolha == 1){
            topo1++;
            tamanho1++;
            dados[topo1] = valor;
        }else if(escolha == 2){
            topo2--;
            tamanho2++;
            dados[topo2] = valor;
        }
    }
}

int pilhaDupla::desempilha(int escolha) {
    if(escolha == 1){
        topo1--;
        tamanho1--;
        return dados[topo1+1];
    }else if(escolha == 2){
        topo2++;
        tamanho2--;
        return dados[topo2-1];
    }
}

bool pilhaDupla::vazia(int escolha) {
    if (escolha == 1) 
        return (tamanho1 == 0);
    else if (escolha == 2)
        return (tamanho2 == 0);
    return true;
}

int main() {
    pilhaDupla PP;
    char opcao;
    int escolha;
    int valor;
    
    do {
        cin >> opcao;
        switch (opcao) {
        case 'E': 
            cin >> escolha >> valor;
            PP.empilha(escolha,valor);  
            break;      
        case 'D':
            cin >> escolha;
            if ( PP.vazia(escolha) ) cout << "VAZIA" << endl;
            else cout << PP.desempilha(escolha) << " ";
            break;      
        }
        
    } while (opcao != 'T');

    return 0;
}