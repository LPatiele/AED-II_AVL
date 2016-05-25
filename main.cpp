#include <iostream>
#include <string>
#include "pessoas.hpp"


int main(int argc, char const *argv[]) {
  Pessoa* pessoa;
  Pessoa* raiz = NULL;

  string nome;
  int idade;
  int insere = 0;
  int chave;

  while(insere < 6){
    //cout << "Informe o nome:" << endl;
    //cin >> nome;
    cout << "Informe a idade:" << endl;
    cin >> idade;
    nome = "____";
    pessoa = new Pessoa(nome, idade);

    if(raiz == NULL){ raiz = pessoa; }
    else{ raiz->inserirPessoa(pessoa, &raiz); }

    insere++;
  }

  // cout << endl << "Pré-Ordem" << endl;
  // raiz->mostrarPre();
  //
  // cout << endl << "Ordem" << endl;
  // raiz->mostrarOrdem();
  //
  // cout << endl << "Pós-Ordem" << endl;
  // raiz->mostrarPos();

  //  insere = 0;
  //  while(insere < 3){
  //    cout << endl << "Informe a idade para deletar: ";
  //    cin >> chave;
  //    insere++;
  //    raiz->deletarElemento(chave, &raiz);
  //    raiz->mostrarPre();
  //  }
   raiz->mostrarPre();

  return 0;
}
