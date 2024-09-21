/*
    COM160: Estruturas de Dados

    Semana 6: Árvores AVL e Grafos

            -: lógica (header): 
                L: classe Aluno: com160_aluno.h
                L: classe Árvore AVL: com160_arvore_avl.h
            -: implementação: com160_estruturas_dados_semana6.cpp
            -: execução: com160_arvore_avl_main.cpp


            -: comando de compilação (certificar-se de estar no folder)
                g++ com160_arvore_avl_main.cpp com160_estruturas_dados_semana6.cpp -o arvore_avl
            -: execução após compilação
                .\arvore_avl
*/
/*
    ÁRVORES AVL
        -> A busca em árvore é EFICIENTE em ÁRVORES BALANCEADAS.
            -: O número de COMPARAÇÕES é proporcional à ALTURA DA ÁRVORE
        
        -> FATOR DE BALANCEAMENTO: diferença de altura entre as subárvores da esquerda e da direita
            -: Em árvores AVL, deve ficar no intervalo [-1,1]
            -: Caso, após inserção ou remoção, algum nó violar o fato de balanceamento
                uma ROTAÇÃO deve ser feita.
            
        -> REGRAS DE ROTAÇÕES
            | nó desbalanceado | filho do nó desb. | tipo de rotação
            |        +2        |         +1        |  simples-esquerda
            |        +2        |          0        |  simples-esquerda
            |        +2        |         -1        |  dupla-filho-direita-pai-esquerda
            |        -2        |         +1        |  dupla-filho-esquerda-pai-direita
            |        -2        |          0        |  simples-direita
            |        -2        |         -1        |  simples-direita

    
    
*/


#include "com160_arvore_avl.h"

// retorna True se raiz é igual a NULL
bool arvoreBuscaAVL::vazia() const {
  return raiz == NULL;
}

/*
    -> faz uma alocação teste, se for possível, retorna False (a alocação é desalocada com delete)
    -> se retornar um erro de alocação (bad_alloc), faz a captura com catch e retorna True
*/
 
bool arvoreBuscaAVL::cheia() const {
  NodeType* alocacao;
  try {
      alocacao = new NodeType;
      delete alocacao;
      return false;
}
  catch(std::bad_alloc exception) {
      return true;
}
}

void arvoreBuscaAVL::destruirArvore(NodeType*& arvore)
{
  if (arvore != NULL)
    {
      // desaloca subarvores e arvore
      destruirArvore(arvore -> esquerda);
      destruirArvore(arvore -> direita);
      delete arvore;
    }
}


void arvoreBuscaAVL::obterAluno(NodeType* arvore, Aluno& aluno, bool& encontrado) const {
  
  // se a árvore estiver vazia, retorna False
  if (arvore == NULL)
    encontrado = false;

  // busca recursivamente os nós, se menor (subárvore esquerda) ou maior (subárvore direita)
  else if (aluno.getRa() < arvore -> aluno.getRa())
    obterAluno(arvore->esquerda, aluno, encontrado);
  else if (aluno.getRa() > arvore -> aluno.getRa())
    obterAluno(arvore -> direita, aluno, encontrado);
  
  // quando encontrado, passa o valor para a variável aluno e retorna True
  else {
    aluno = arvore -> aluno;
    encontrado = true;
  }
}

/*
    inserirAluno()
      -> Folhas têm fator de balanceamento 0
        -: se a árvore estiver vazia (NULL), inserimos um novo nó com o valor de aluno
        -: maisAlta = True: pois inserimos um novo nó
      

*/
void arvoreBuscaAVL::inserirAluno(NodeType*& arvore, Aluno aluno, bool& maisAlta) { 
  if (arvore == NULL) {
      arvore = new NodeType;
      arvore->direita  = NULL;
      arvore->esquerda = NULL;
      arvore->aluno  = aluno;
      arvore->fatorBalanceamento  = 0; // Acabamos de inserir uma folha
      maisAlta = true;
      return;
  }  

  // se o RA inserido for menor que o atual, inserirAluno é executado recursivamente na subárvore esquerda
  // se maisAlta for True, como estamos na subárvore esquerda, o fator de Balanceamento é decrementado em 1
  if (aluno.getRa() < arvore -> aluno.getRa()) {
    inserirAluno(arvore -> esquerda, aluno, maisAlta);
    if (maisAlta)
      arvore -> fatorBalanceamento = arvore -> fatorBalanceamento - 1;    
  } 
  // se o RA inserido for maior que o atual, inserirAluno é executado recursivamente na subárvore direita
  // se maisAlta for True, como estamos na subárvore direita, o fator de Balanceamento é incrementado em 1
  else { 
    inserirAluno(arvore -> direita, aluno, maisAlta);
    if (maisAlta)
      arvore -> fatorBalanceamento = arvore -> fatorBalanceamento + 1;    
  }
  // Ajustamos o fator de balanceamento se necessário
  rotacionar(arvore);
  
  /*

  */
  if (maisAlta && arvore -> fatorBalanceamento == 0) {
      maisAlta = false;
   }
}

void arvoreBuscaAVL::removerAluno(NodeType*& arvore, int aluno, bool& maisBaixa) {
  if (aluno < arvore -> aluno.getRa()) {
    removerAluno(arvore->esquerda, aluno, maisBaixa);
    if (maisBaixa)
      arvore->fatorBalanceamento = arvore->fatorBalanceamento + 1;     
  } else if (aluno > arvore->aluno.getRa()) {
    removerAluno(arvore->direita, aluno, maisBaixa);
    if (maisBaixa)
      arvore->fatorBalanceamento = arvore->fatorBalanceamento - 1;
  } else if (aluno == arvore->aluno.getRa()) {
    removerNo(arvore, maisBaixa);
  }  
  if (arvore != NULL) {
    rotacionar(arvore);  
    if (maisBaixa && arvore->fatorBalanceamento != 0){
      maisBaixa = false;
    }
  }
}

void arvoreBuscaAVL::removerNo(NodeType*& arvore, bool& maisBaixa) {
  Aluno data;
  NodeType* ponteiroTemporario;
  ponteiroTemporario = arvore;
  if (arvore->esquerda == NULL) {
    arvore = arvore->direita;
    maisBaixa = true;
    delete ponteiroTemporario; 
  } else if (arvore->direita == NULL) {
    arvore = arvore->esquerda; 
    maisBaixa = true;
    delete ponteiroTemporario;
  } else {
    getSucessor(arvore, data);
    arvore->aluno = data;
    removerAluno(arvore->direita, data.getRa(), maisBaixa);
    if (maisBaixa)
      arvore->fatorBalanceamento = arvore->fatorBalanceamento - 1;
  }
}

void arvoreBuscaAVL::getSucessor(NodeType* arvore, Aluno& data) {
  arvore = arvore->direita;
  while (arvore->esquerda != NULL)
    arvore = arvore->esquerda;
  data = arvore->aluno;
}

void arvoreBuscaAVL::printPreOrdem(NodeType* arvore) const {
  if (arvore != NULL)  {
      std::cout << arvore->aluno.getNome() << "[" << arvore->fatorBalanceamento << "] ";
      printPreOrdem(arvore->esquerda);
      printPreOrdem(arvore->direita);
    }
}

void arvoreBuscaAVL::printInOrdem(NodeType* arvore) const {
  if (arvore != NULL) {
    printInOrdem(arvore->esquerda);
    std::cout << arvore->aluno.getNome() << "[" << arvore->fatorBalanceamento << "] ";
    printInOrdem(arvore->direita);
  }
}

void arvoreBuscaAVL::printPosOrdem(NodeType* arvore) const {
  if (arvore != NULL) {
	printPosOrdem(arvore->esquerda);
	printPosOrdem(arvore->direita);
	std::cout << arvore->aluno.getNome() << "[" << arvore->fatorBalanceamento << "] ";
    }
}

void arvoreBuscaAVL::rotacaoEsquerda(NodeType*& arvore) const {
  NodeType* p = arvore->direita;
  arvore->direita = p->esquerda; 
  p->esquerda   = arvore; 
  arvore          = p;    
}

void arvoreBuscaAVL::rotacaoDireita (NodeType*& arvore) const {
  NodeType* ponteiro = arvore -> esquerda;
  arvore -> esquerda = ponteiro -> direita;
  ponteiro -> direita     = arvore;
  arvore = ponteiro;  
}

void arvoreBuscaAVL::rotacaoEsquerdaDireita(
					 NodeType*& arvore    
					 ) const{
  NodeType* child = arvore->esquerda;
  rotacaoEsquerda(child);
  arvore->esquerda = child;
  rotacaoDireita(arvore);
}

void arvoreBuscaAVL::rotacaoDireitaEsquerda(
					 NodeType*& arvore
					 ) const{
  NodeType* child = arvore->direita;
  rotacaoDireita(child);
  arvore->direita = child;
  rotacaoEsquerda (arvore);
}

void arvoreBuscaAVL::rotacionar(NodeType*& arvore) const {      
  NodeType* child;
  NodeType* grandChild; // Usado em rotacao dupla
  
  // Rotacionar para a direita 
  if (arvore->fatorBalanceamento == -2) {
    child = arvore->esquerda;

    switch (child->fatorBalanceamento) {
    case -1 : // Simples para a direita: Caso 1
      arvore->fatorBalanceamento = 0;
      child ->fatorBalanceamento = 0;
      rotacaoDireita(arvore);
      break;      
    case 0 : // Simples para a direita: Caso 2 -> Remoções
      arvore->fatorBalanceamento = -1;
      child ->fatorBalanceamento = +1;
      rotacaoDireita(arvore);
      break;      
    case 1 :  // Rotacao dupla
      grandChild = child->direita;

      switch(grandChild->fatorBalanceamento){
      case -1 :
	arvore ->fatorBalanceamento = +1;
	child->fatorBalanceamento =  0;      
	break;
      case 0 :
	arvore ->fatorBalanceamento = 0;
	child->fatorBalanceamento = 0;
	break;
      case +1 :
	arvore ->fatorBalanceamento =  0;
	child->fatorBalanceamento = -1;
	break;
      }
      grandChild->fatorBalanceamento = 0; 
      rotacaoEsquerdaDireita(arvore);
    }
  }  
  // Vamos rotacionar para a esquerda
  else if (arvore->fatorBalanceamento == +2) {
    child = arvore->direita;
    
    switch (child->fatorBalanceamento) {
    case  1 : // Simples para a esquerda: Caso 1
      arvore ->fatorBalanceamento = 0;
      child->fatorBalanceamento = 0;
      rotacaoEsquerda(arvore);
      break;      
    case 0 : // Simples para a esquerda: Caso 2
      arvore ->fatorBalanceamento = +1;
      child->fatorBalanceamento = -1;
      rotacaoEsquerda(arvore);
      break;      
    case -1 : // Rotacao dupla
      grandChild = child->esquerda;
      
      switch(grandChild->fatorBalanceamento){
      case -1 :
	arvore ->fatorBalanceamento =  0;
	child->fatorBalanceamento = +1;      
	break;
      case 0 :
	arvore ->fatorBalanceamento = 0;
	child->fatorBalanceamento = 0;
	break;
      case +1 :
	arvore ->fatorBalanceamento = -1;
	child->fatorBalanceamento =  0;
	break;
      }
      grandChild->fatorBalanceamento = 0; 
      rotacaoDireitaEsquerda(arvore);
    }
  }          
}