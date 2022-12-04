//Mardem Arantes de Castro
//Dia 08/11/2022
//Matricula = 202210086
#include <iostream>
using namespace std;

int condicional(int matriz[8][7], int posicao_atual){
  if((matriz[posicao_atual][0] == 1)and(matriz[posicao_atual][2] == 0)){
    return 0;
  }else{
    return 1;
  }
}

int bicondicional(int matriz[8][7], int posicao_atual){
  if((matriz[posicao_atual][4] == matriz[posicao_atual][2])){
    return 1;
  }else{
    return 0;
  }
}

int main (){
  int p, q, r;
  int matriz_verdade[8][7];  
  int coluna1[8] = {1,1,1,1,0,0,0,0};
  int coluna2[8] = {1,1,0,0,1,1,0,0};
  int coluna3[8] = {1,0,0,1,1,0,1,0};

  //Preenche as colunas p, q, r
  for(int i = 0;i < 8;i++){
    matriz_verdade[i][0] = coluna1[i];
    matriz_verdade[i][1] = coluna2[i];
    matriz_verdade[i][2] = coluna3[i];
  }

  //Condicional
  for(int i = 0;i < 8;i++){
    matriz_verdade[i][3] = condicional(matriz_verdade, i);
  }

  //Disjunção
  for(int i = 0;i < 8;i++){
    if((matriz_verdade[i][0] == 1) or (matriz_verdade[i][2] == 1)){
      matriz_verdade[i][4] = 1;
    }else{
      matriz_verdade[i][4] = 0;
    }
  }

  //bicondicional
  for(int i = 0;i < 8;i++){
    matriz_verdade[i][5] = bicondicional(matriz_verdade, i);
  }

  //Conjunção
  for(int i = 0;i < 8;i++){
    if((matriz_verdade[i][3] == 1) and (matriz_verdade[i][5] == 1)){
      matriz_verdade[i][6] = 1;
    }else{
      matriz_verdade[i][6] = 0;
    }
  }

  //Imprime o cabeçalho
  cout << "p          q          r        p->r        p||q      r<->p||q  (p->r)&&(r<->p||q)" << endl;

  //Imprime a matriz verdade inteira
  for(int i = 0;i < 8;i++){
    for(int j = 0;j < 7;j++){
      cout << matriz_verdade[i][j] << "          ";
    }
    cout << endl;
  }

}