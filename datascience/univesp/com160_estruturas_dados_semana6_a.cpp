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
      // desaloca subárvores e, só depois, a árvore
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
    Checamos se o ajuste de balanceamento foi ajustado quando a árvore aumentou de tamanho (maisAlta == true)
      -> Se sim, maisAlta é false, pois o fator de balanceamento já foi ajustado
      -> Esse passo é crucial para a eficiência da árvore, pois garante que só percorremos a altura da árvore
        para ajustar o balanceamento quando for necessário
  */
  if (maisAlta && arvore -> fatorBalanceamento == 0) {
      maisAlta = false;
   }
}
/*
  removerAluno():
    -> Função recursiva, ao achar o Aluno chama a função removerNó()
      -: ao retornar nas chamadas pendentes, checa se a árvore está maisBaixa

*/
void arvoreBuscaAVL::removerAluno(NodeType*& arvore, int aluno, bool& maisBaixa) {
  if (aluno < arvore -> aluno.getRa()) {
    removerAluno(arvore -> esquerda, aluno, maisBaixa);
    
    // se a árvore estiver mais baixa no lado esquerdo, após a remoção, incrementamos o fator de balanceamento em 1
    if (maisBaixa)
      arvore -> fatorBalanceamento = arvore -> fatorBalanceamento + 1;     
  } else if (aluno > arvore -> aluno.getRa()) {
    removerAluno(arvore -> direita, aluno, maisBaixa);
    
    // se a árvore estiver mais baixa no lado direito, após a remoção, decrementamos o fator de balanceamento em 1
    if (maisBaixa)
      arvore -> fatorBalanceamento = arvore -> fatorBalanceamento - 1;
  } else if (aluno == arvore -> aluno.getRa()) {
    removerNo(arvore, maisBaixa); // ao encontrar o aluno, removemos o nó
  }  

/*
  Checamos se o ajuste de balanceamento foi ajustado após as rotações necessárias
      -> Se sim, o fator de balanceamento já foi ajustado, setamos maisBaixa para False
      -> Esse passo é crucial para a eficiência da árvore, pois garante que só percorremos a altura da árvore
        para ajustar o balanceamento quando for necessário
*/  
  if (arvore != NULL) {
    rotacionar(arvore);  
    if (maisBaixa && arvore -> fatorBalanceamento != 0){
      maisBaixa = false;
    }
  }
}

/*
  removerNó():
    -> Função auxiliar de removerAluno()
      -: utiliza um ponteiroTemporário que aponta para o nó a ser removido
      -: checa a árvore esquerda, se estiver NULL, o nó da direita irá substituir a posição do nó a ser removido
        -: senão, faz o mesmo com a subárvore direita, substituindo o valor do nó a ser removido pelo nó da esquerda
        -: remove o ponteiroTemporario, que apontava para o nó a ser removido
        -: atualiza maisBaixa como True
      -: se o nó tiver 2 filhos (direita e esquerda), substitui o valor do nó a ser removido pelo sucessor
        -: sucessor é obtido pela função getSucessor()
          -: o sucessor é removido recursivamente (removerAluno->removerNó)
*/
void arvoreBuscaAVL::removerNo(NodeType*& arvore, bool& maisBaixa) {
    Aluno data;
    NodeType* ponteiroTemporario;
    ponteiroTemporario = arvore;
    if (arvore -> esquerda == NULL) {
        arvore = arvore -> direita;
        maisBaixa = true;
        delete ponteiroTemporario; 
    } else if (arvore -> direita == NULL) {
        arvore = arvore -> esquerda; 
        maisBaixa = true;
        delete ponteiroTemporario;
    } 
    /*  
      No caso de o Nó possuir 2 filhos (direita e esquerda)
        -> percorremos a subárvore direita, com getSucessor, até o sucessor imediato (nó mais à esquerda)
        -> o valor do nó a ser removido é substituído pelo sucessor
          -: o sucessor é removido recursivamente (removerAluno->removerNó)
          -: se maisBaixa após a remoção, por estarmos na subárvore direita, o fator é decrementado em 1
    */
    else {
        getSucessor(arvore, data);
        arvore -> aluno = data;
        removerAluno(arvore -> direita, data.getRa(), maisBaixa);
        if (maisBaixa)
          arvore -> fatorBalanceamento = arvore -> fatorBalanceamento - 1;
    }
}

/*
  getSucessor(): função auxiliar de removerNó()
    -> Chamada no caso de o nó a ser removido possuir 2 filhos (esquerdo e direito)
    -> Percorre todos os nós mais à esquerda da subárvore da direita
    -> Substitui o valor do nó a ser removido pelo sucessor
      -: Após a troca, remove recursivamente o sucessor imediato (na subárvore direita)
      -: Como estamos na subárvore direita, se ela fica maisBaixa, o fator de balanceamento é decrementado em 1
*/
void arvoreBuscaAVL::getSucessor(NodeType* arvore, Aluno& data) {
    arvore = arvore -> direita;
    while (arvore -> esquerda != NULL)
      arvore = arvore -> esquerda;
    data = arvore -> aluno;
}

void arvoreBuscaAVL::printPreOrdem(NodeType* arvore) const {
  if (arvore != NULL)  {
      std::cout << arvore -> aluno.getNome() << "[" << arvore -> fatorBalanceamento << "] ";
      printPreOrdem(arvore -> esquerda);
      printPreOrdem(arvore -> direita);
    }
}

void arvoreBuscaAVL::printInOrdem(NodeType* arvore) const {
  if (arvore != NULL) {
    printInOrdem(arvore -> esquerda);
    std::cout << arvore -> aluno.getNome() << "[" << arvore -> fatorBalanceamento << "] ";
    printInOrdem(arvore -> direita);
  }
}

void arvoreBuscaAVL::printPosOrdem(NodeType* arvore) const {
  if (arvore != NULL) {
	printPosOrdem(arvore -> esquerda);
	printPosOrdem(arvore -> direita);
	std::cout << arvore -> aluno.getNome() << "[" << arvore -> fatorBalanceamento << "] ";
    }
}

// nó: +2, filho: +1,0
    // Antes da rotação:
    //       A
    //        \
    //         B
    //        / \
    //       C   D
    //
    // Depois da rotação:
    //       B
    //      / \
    //     A   D
    //      \
    //       C
// Em momento algum, precisamos mexer em (D)
void arvoreBuscaAVL::rotacaoEsquerda(NodeType*& arvore) const {
    NodeType* ponteiroTemporario = arvore -> direita; // filho direito (B), será o novo nó raíz
    arvore -> direita = ponteiroTemporario -> esquerda; // filho direito da raíz (A), recebe o filho esquerdo do nó temporário (C) A -> C
    ponteiroTemporario -> esquerda = arvore; // filho esquerdo do nó temporário (B), recebe a raíz (A) A <- B -> D
    arvore = ponteiroTemporario; // (B) é alocado como nova raíz da árvore
}

// nó: -2, filho: -1,0
// Antes da rotação:
//       A
//      /
//     B
//    / \
//   C   D
//
// Depois da rotação:
//       B
//      / \
//     C   A
//        /  
//       D    
// Em momento algum, precisamos mexer em (C)
void arvoreBuscaAVL::rotacaoDireita (NodeType*& arvore) const {
  NodeType* ponteiroTemporario = arvore -> esquerda; // filho esquerdo (B), será o novo nó raíz (nó temporário)
  arvore -> esquerda = ponteiroTemporario -> direita; // filho esquerdo da raíz (A), recebe o filho direito (D) do nó temporário (B) D <- A
  ponteiroTemporario -> direita = arvore; // filho direito do nó temporário (B), recebe a raíz (A) B -> A
  arvore = ponteiroTemporario;  // (B) é alocado como nova raíz da árvore
}

// nó: -2, filho: +1
void arvoreBuscaAVL::rotacaoEsquerdaDireita(NodeType*& arvore) const {
  NodeType* filho = arvore -> esquerda;
  rotacaoEsquerda(filho);
  arvore -> esquerda = filho;
  rotacaoDireita(arvore);
}
// nó: +2, filho: -1
void arvoreBuscaAVL::rotacaoDireitaEsquerda(NodeType*& arvore) const {
  NodeType* filho = arvore -> direita;
  rotacaoDireita(filho);
  arvore -> direita = filho;
  rotacaoEsquerda (arvore);
}

void arvoreBuscaAVL::rotacionar(NodeType*& arvore) const {      
  NodeType* filho;
  NodeType* neto; // Usado em rotacao dupla
  
  // Rotacionar para a direita 
  if (arvore -> fatorBalanceamento == -2) {
    filho = arvore -> esquerda; // nó a ser rotacionado

    switch (filho -> fatorBalanceamento) {
    case -1 : // Simples para a direita: caso -2, -1
      arvore -> fatorBalanceamento = 0;
      filho -> fatorBalanceamento = 0;
      rotacaoDireita(arvore);
      break;      
    case 0 : // Simples para a direita: caso -2, 0
      arvore -> fatorBalanceamento = -1;
      filho -> fatorBalanceamento = +1;
      rotacaoDireita(arvore);
      break;      
    case 1 :  // Rotacao dupla: caso -2, +1
      neto = filho -> direita;

      switch(neto -> fatorBalanceamento){
      case -1 :
        arvore -> fatorBalanceamento = +1;
        filho -> fatorBalanceamento =  0;      
        break;
      case 0 :
        arvore -> fatorBalanceamento = 0;
        filho -> fatorBalanceamento = 0;
        break;
      case +1 :
        arvore -> fatorBalanceamento =  0;
        filho -> fatorBalanceamento = -1;
        break;
      }
      neto -> fatorBalanceamento = 0; 
      rotacaoEsquerdaDireita(arvore);
    }
  }  
  // Vamos rotacionar para a esquerda
  else if (arvore -> fatorBalanceamento == +2) {
    filho = arvore -> direita;
    
    switch (filho -> fatorBalanceamento) {
    case  1 : // Simples para a esquerda: caso +2, +1
      arvore -> fatorBalanceamento = 0;
      filho -> fatorBalanceamento = 0;
      rotacaoEsquerda(arvore);
      break;      
    case 0 : // Simples para a esquerda: caso +2, 0
      arvore -> fatorBalanceamento = +1;
      filho -> fatorBalanceamento = -1;
      rotacaoEsquerda(arvore);
      break;      
    case -1 : // Rotacao dupla: caso +2, -1
      neto = filho -> esquerda;
      
      switch(neto -> fatorBalanceamento){
      case -1 :
        arvore -> fatorBalanceamento =  0;
        filho -> fatorBalanceamento = +1;      
        break;
      case 0 :
        arvore -> fatorBalanceamento = 0;
        filho -> fatorBalanceamento = 0;
        break;
      case +1 :
        arvore -> fatorBalanceamento = -1;
        filho -> fatorBalanceamento =  0;
        break;
    }
      neto -> fatorBalanceamento = 0; 
      rotacaoDireitaEsquerda(arvore);
    }
  }          
}