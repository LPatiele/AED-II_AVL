#include <iostream>
#include <string>

using namespace std;

class Pessoa{

  public:
    string nome;
    int idade;
    int direita;
    int esquerda;
    Pessoa* filhoEsquerda;
    Pessoa* filhoDireita;
    Pessoa* pai;

    Pessoa(){
      nome = "";
      idade = 0;
      filhoDireita = NULL;
      filhoEsquerda = NULL;
      pai = NULL;
      direita = 0;
      esquerda = 0;
    };

    Pessoa( string n, int id){
      nome = n;
      idade = id;
      filhoDireita = NULL;
      filhoEsquerda = NULL;
      pai = NULL;
    };

    ~Pessoa(){};

    void setNome(string n){  nome = n;    };

    string getNome(){      return nome;    };

    void setIdade(int id){      idade = id;    };

    int getIdade(){      return idade;    };

    void inserirPessoa(Pessoa *nova, Pessoa** raiz){
        if(nova->idade <= this->idade){
          if(filhoEsquerda == NULL){
              this->filhoEsquerda = nova;
              nova->pai = this;
              atualizarBalanco(nova, true);
              (*raiz)->verificaBalanceamento(raiz);
          }else{ filhoEsquerda->inserirPessoa(nova, raiz);  }
        }else{
          if(filhoDireita == NULL){
              this->filhoDireita = nova;
              nova->pai = this;
              atualizarBalanco(nova, true);
              (*raiz)->verificaBalanceamento(raiz);
          }else{  filhoDireita->inserirPessoa(nova, raiz);  }
        }
    };

    void deletarSemFilho(Pessoa* pessoa){
      if(pessoa->pai->filhoEsquerda == pessoa){
         // Remove a esquerda.
         cout << endl << "Removendo filho a esquerda" << endl;
         pessoa->pai->filhoEsquerda = NULL;
         delete pessoa;
       }else{
         // Remove a direita.
         cout << endl << "Removendo filho a direita" << endl;
         pessoa->pai->filhoDireita = NULL;
         delete pessoa;
       }
    };

    void deletarUmFilho(Pessoa* pessoa){
      // Verifica qual o lado esta.
      if(pessoa->pai->filhoEsquerda == pessoa){
        if(pessoa->filhoEsquerda != NULL){
        // Remove filho a esquerda.
          pessoa->filhoEsquerda->pai = pessoa->pai;
          pessoa->pai->filhoEsquerda = pessoa->filhoEsquerda;
          delete pessoa;
        }else{
        // Remove filho a direita.
          pessoa->filhoDireita->pai = pessoa->pai;
          pessoa->pai->filhoEsquerda = pessoa->filhoDireita;
          delete pessoa;
        }
      }else{
        if(pessoa->filhoEsquerda != NULL){
          // Remove filho a esquerda.
          pessoa->filhoEsquerda->pai = pessoa->pai;
          pessoa->pai->filhoDireita = pessoa->filhoEsquerda;
          delete pessoa;
        }else{
          // Remove filho a direita.
          pessoa->filhoDireita->pai = pessoa->pai;
          pessoa->pai->filhoDireita = pessoa->filhoDireita;
          delete pessoa;
        }
      }
    };

    void deletarDoisFilhos(Pessoa* pessoa){
        //Verificar de qual lado esta. 0 = esquerdo e 1 = direito.
        int binario;
        if(pessoa->pai->filhoEsquerda == pessoa){ binario = 0; }
        else{ binario = 1;}
        // Verifica se o filho a direita tem um filho a esquerda.
        if(pessoa->filhoDireita->filhoEsquerda == NULL){
          // Atualiza balanceamento.
          atualizarBalanco(pessoa->filhoDireita, false);
          pessoa->filhoDireita->direita = pessoa->direita;
          pessoa->filhoDireita->esquerda = pessoa->esquerda;
          if(binario == 0){ pessoa->pai->filhoEsquerda = pessoa->filhoDireita; }
          else{ pessoa->pai->filhoDireita = pessoa->filhoDireita; }
          pessoa->filhoDireita->filhoEsquerda = pessoa->filhoEsquerda;
          pessoa->filhoDireita->pai = pessoa->pai;
          pessoa->filhoEsquerda->pai = pessoa->filhoDireita;
          delete pessoa;
        }else{
          Pessoa* aux = pessoa->filhoDireita;
          while(aux->filhoEsquerda != NULL){
            aux = aux->filhoEsquerda;
          }
          //Atualiza balanceamento.
          atualizarBalanco(aux, false);
          aux->direita = pessoa->direita;
          aux->esquerda = pessoa->esquerda;
          // Verifica se aux tem filho a direita.
          if(aux->filhoDireita != NULL){ aux->filhoDireita->pai = aux->pai; }
          aux->pai->filhoEsquerda = aux->filhoDireita;
          if(binario == 0){ pessoa->pai->filhoEsquerda = aux; }
          else{ pessoa->pai->filhoDireita = aux; }
          aux->pai = pessoa->pai;
          aux->filhoEsquerda = pessoa->filhoEsquerda;
          aux->filhoDireita = pessoa->filhoDireita;
          aux->filhoEsquerda->pai = aux;
          aux->filhoDireita->pai = aux;
          delete pessoa;
        }
    };


    void deletarRaizDoisFilhos(Pessoa* pessoa, Pessoa** raiz){
      // Verifica de qual lado esta.
        if(pessoa->filhoDireita->filhoEsquerda == NULL){
          // Sem filho a esquerda.
          atualizarBalanco(pessoa->filhoDireita, false);
          // Atualiza balanceamento.
          pessoa->filhoDireita->direita = pessoa->direita;
          pessoa->filhoDireita->esquerda = pessoa->esquerda;
          pessoa->filhoDireita->filhoEsquerda = pessoa->filhoEsquerda;
          pessoa->filhoDireita->pai = NULL;
          (*raiz) = pessoa->filhoDireita;
          pessoa->filhoEsquerda->pai = (*raiz);
          delete pessoa;
        }else{
          // Com filho a esquerda.
          Pessoa* aux = pessoa->filhoDireita;
          while(aux->filhoEsquerda != NULL){
            aux = aux->filhoEsquerda;
          }
          atualizarBalanco(aux, false);
          // Verifica se aux tem filho a direita.
          if(aux->filhoDireita != NULL){ aux->filhoDireita->pai = aux->pai;  }
          aux->pai->filhoEsquerda = aux->filhoDireita;
          aux->pai = NULL;
          // Atualiza balanceamento
          aux->direita = pessoa->direita;
          aux->esquerda = pessoa->esquerda;
          // Atualiza ponteiros
          aux->filhoEsquerda = pessoa->filhoEsquerda;
          aux->filhoDireita = pessoa->filhoDireita;
          aux->filhoEsquerda->pai = aux;
          aux->filhoDireita->pai = aux;
          (*raiz) = aux;
          delete pessoa;
        }
    };

    void deletarElemento(int chave, Pessoa ** raiz){
      Pessoa* aux = this->buscar(chave);
      if(aux != NULL){
        if(aux->filhoEsquerda == NULL && aux->filhoDireita == NULL){
            if(aux->pai == NULL){
               delete aux;
               (*raiz) = NULL;
            }else{
              atualizarBalanco(aux, false);
              deletarSemFilho(aux);
            }
        }else{
          if(aux->filhoEsquerda == NULL || aux->filhoDireita == NULL){
              if(aux->pai == NULL){
                if(aux->filhoEsquerda != NULL){
                  aux->filhoEsquerda->pai = NULL;
                  (*raiz) = aux->filhoEsquerda;
                }else{
                  aux->filhoDireita->pai=NULL;
                  (*raiz) = aux->filhoDireita;
                }
                delete aux;
              }else{
                  atualizarBalanco(aux, false);
                  deletarUmFilho(aux);
              }
          }else{
              if(aux->pai == NULL){ deletarRaizDoisFilhos(aux, raiz); }
              else{ deletarDoisFilhos(aux); }
          }
        }
        (*raiz)->verificaBalanceamento(raiz);
      }else{   cout << "Pessoa Não Encontrada" << endl;  }
    };

    Pessoa* buscar(int chave){
      if(chave != this->idade){
        if(chave < this->idade){
          if(filhoEsquerda!=NULL){ this->filhoEsquerda->buscar(chave); }
          else{ return NULL;  }
        }else{
          if(filhoDireita != NULL){ this->filhoDireita->buscar(chave); }
          else{ return NULL; }
        }
      }else{
        return this;
      }
    };

    void apagarTudo(){
     if(this->filhoEsquerda != NULL) this->filhoEsquerda->apagarTudo();
     if(this->filhoDireita != NULL) this->filhoDireita->apagarTudo();
       delete this;
    };

    void mostrarPre(){
        int balanceia = this->direita-this->esquerda;
        cout << this->nome << ":" << this->idade <<endl;
        cout<< " Valor de balanceamento : "<< balanceia << endl;
        if(filhoEsquerda != NULL) this->filhoEsquerda->mostrarPre();
        if(filhoDireita != NULL) this->filhoDireita->mostrarPre();
    };

    void mostrarOrdem(){
      if(filhoEsquerda != NULL) this->filhoEsquerda->mostrarOrdem();
      cout << this->nome << ":" << this->idade << endl;
      if(filhoDireita != NULL) this->filhoDireita->mostrarOrdem();
    };

    void mostrarPos(){
      if(filhoEsquerda != NULL) this->filhoEsquerda->mostrarPos();
      if(filhoDireita != NULL) this->filhoDireita->mostrarPos();
      cout << this->nome << ":" << this->idade << endl;
    };

    void atualizarBalanco(Pessoa* pessoa, bool opcao){
        Pessoa* aux = pessoa;
        Pessoa* auxPai = pessoa->pai;
        bool segundoFilho;
        if(auxPai->filhoEsquerda!=NULL && auxPai->filhoDireita!=NULL){ segundoFilho = true;  }
        else{  segundoFilho = false;        }
        while(aux->pai != NULL){
            if(auxPai->filhoEsquerda == aux){
              if(opcao){ auxPai->esquerda++; }
              else{ auxPai->esquerda--; }
            }else{
              if(opcao){ auxPai->direita++; }
              else{ auxPai->direita--; }
            }
            if(segundoFilho){ return; }
            aux=aux->pai;
            auxPai=aux->pai;
          }
    };

    int balancoNos(){
        esquerda = 0;
        direita = 0;
        if (filhoEsquerda != NULL) {  esquerda = filhoEsquerda->balancoNos()+1;   }
        if (filhoDireita != NULL) {  direita = filhoDireita->balancoNos()+1;   }
        return (esquerda > direita) ? esquerda : direita;
    };

    void verificaBalanceamento(Pessoa** raiz){
        int b;
        b = this->direita - this->esquerda;
        if(b < -1 || b > 1){
          cout << "Árvore Desbalanceada em: " << this->idade << endl;
          this->mostrarPre();
          balancear(b, this, raiz);
          return;
        }
        if(filhoEsquerda != NULL){
          this->filhoEsquerda->verificaBalanceamento(raiz);
        }
        if(filhoDireita != NULL){
          this->filhoDireita->verificaBalanceamento(raiz);
        }
    };

    void balancear(int tipo, Pessoa *pessoa, Pessoa** raiz){
        int tipofilho;
        if(tipo < 0){
        tipofilho = pessoa->filhoEsquerda->direita - pessoa->filhoEsquerda->esquerda;
        if(tipofilho <= 0){
          // Rotação simples pela direita.
          cout << "Rotação simples pela direita" << endl;
          simplesDireita(pessoa, raiz);
        }else{
          // Rotação dupla pela direita.
          cout << "Rotação dupla pela direita" << endl;
          duplaEsquerda(pessoa, raiz);
        }
      }else{
        tipofilho = pessoa->filhoDireita->direita - pessoa->filhoDireita->esquerda;
        if(tipofilho >= 0){
          // Rotação simples pela esquerda.
          cout << "Rotação simples pela esquerda" << endl;
          simplesEsquerda(pessoa, raiz);
        }else{
          // Rotação dupla pela esquerda.
          cout << "Rotação dupla pela esquerda" << endl;
          duplaDireita(pessoa, raiz);
        }
      }
      (*raiz)->balancoNos();
    };

    void simplesDireita(Pessoa* pessoa, Pessoa** raiz){
      if(pessoa->pai == NULL){
        // Balanceia a raiz.
        (*raiz) = pessoa->filhoEsquerda;
        pessoa->filhoEsquerda = (*raiz)->filhoDireita;
        (*raiz)->filhoDireita = pessoa;
        (*raiz)->pai = NULL;
        pessoa->pai = (*raiz);
        if(pessoa->filhoEsquerda != NULL)  pessoa->filhoEsquerda->pai = pessoa;
      }else{
        Pessoa* ppai = pessoa->pai;
        Pessoa* aux = pessoa->filhoEsquerda;
        if(pai->filhoEsquerda == pessoa){ ppai->filhoEsquerda = aux; }
        else{ ppai->filhoDireita = aux; }
        aux->pai = ppai;
        pessoa->filhoEsquerda = aux->filhoDireita;
        aux->filhoDireita = pessoa;
        pessoa->pai = aux;
        if(pessoa->filhoEsquerda != NULL)  pessoa->filhoEsquerda->pai = pessoa;
      }
    };

    void simplesEsquerda(Pessoa* pessoa, Pessoa** raiz){
      if(pessoa->pai == NULL){
        // Balanceia a raiz.
        (*raiz) = pessoa->filhoDireita;
        pessoa->filhoDireita = (*raiz)->filhoEsquerda;
        (*raiz)->filhoEsquerda = pessoa;
        (*raiz)->pai = NULL;
        pessoa->pai = (*raiz);
        if(pessoa->filhoDireita != NULL){
          pessoa->filhoDireita->pai = pessoa;
        }
      }else{
        Pessoa* ppai = pessoa->pai;
        Pessoa* aux = pessoa->filhoDireita;;
        if(ppai->filhoEsquerda == pessoa){ ppai->filhoEsquerda = aux; }
        else{ ppai->filhoDireita = aux; }
        aux->pai = ppai;
        pessoa->filhoDireita = aux->filhoEsquerda;
        aux->filhoEsquerda = pessoa;
        pessoa->pai = aux;
        if(pessoa->filhoDireita != NULL){
          pessoa->filhoDireita->pai = pessoa;
        }
      }
    };

    void duplaDireita(Pessoa* pessoa, Pessoa** raiz){
        Pessoa* meio = pessoa->filhoDireita;
        Pessoa* folha = meio->filhoEsquerda;
        pessoa->filhoDireita = folha;
        folha->pai = pessoa;
        meio->filhoEsquerda = NULL;
        folha->filhoDireita = meio;
        meio->pai = folha;
        simplesEsquerda(pessoa, raiz);
    };

    void duplaEsquerda(Pessoa* pessoa, Pessoa** raiz){
      Pessoa* meio = pessoa->filhoEsquerda;
      Pessoa* folha = meio->filhoDireita;
      pessoa->filhoEsquerda = folha;
      folha->pai = pessoa;
      meio->filhoDireita = NULL;
      folha->filhoEsquerda = meio;
      meio->pai = folha;
      simplesDireita(pessoa, raiz);
    };


};
