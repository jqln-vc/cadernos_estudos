/*
    COM160: Estruturas de Dados

    Semana 5: Árvores Binárias de Busca
        -> 
            -: lógica (header): 
                L: classe Aluno: com160_aluno.h
                L: struct No: com160_arvore_busca.h
                L: classe ArvoreBusca: com160_arvore_busca.h
                
            -: implementação: 
                L: classe Aluno: com160_estruturas_dadoss_semana5.cpp
                L: árvore de busca: com160_estruturas_dados_semana5.cpp
            -: execução: com160_arvore_busca_main.cpp


            !comando de compilação (certificar de estar no folder)
                g++ com160_estruturas_dados_semana5.cpp com160_arvore_busca_main.cpp -o arvore_busca
            !execução após compilação
                .\arvore_busca
*/
/*
            ******** ESTRUTURA INICIAL DA ÁRVORE ********


                                PEDRO-20
                               /        \
                       RAUL-18        PAULO-58
                       /       \       /      
                CARLOS-7  LUCAS-19  MARIA-26  
                                    /     \                   
                                SARA-25    ULISSES-30

            ******** PERCURSO PRÉ-ORDEM ********

                                   *1*
                                PEDRO-20
                         *2*  /      \  *5*
                       RAUL-18        PAULO-58
                  *3*   /  *4*\       /  *6*    
                CARLOS-7  LUCAS-19  MARIA-26  
                                  *7* /     \  *8*                 
                                SARA-25    ULISSES-30

            ******** PERCURSO IN-ORDEM ********

                                   *4*
                                PEDRO-20
                         *2*  /      \  *8*
                       RAUL-18        PAULO-58
                  *1*   /  *3*\       /  *6*    
                CARLOS-7  LUCAS-19  MARIA-26  
                                  *5* /     \  *7*                 
                                SARA-25    ULISSES-30

            ******** PERCURSO PÓS-ORDEM ********

                                   *8*
                                PEDRO-20
                         *3*  /      \  *7*
                       RAUL-18        PAULO-58
                  *1*   /  *2*\       /  *6*    
                CARLOS-7  LUCAS-19  MARIA-26  
                                  *4* /     \  *5*                 
                                SARA-25    ULISSES-30
*/


#include "com160_arvore_busca.h"
using namespace std;

const int NUM_ALUNOS = 8; // número máximo de nós

int main() {
    ArvoreBusca arvoreBusca;

    int ras[NUM_ALUNOS] = {20, 18, 58, 7, 19, 26, 25, 30};     
    string nomes[NUM_ALUNOS] = {
        "Pedro", "Raul", "Paulo",
        "Carlos", "Lucas", "Maria",
        "Sara", "Ulisses"};
    Aluno alunos[NUM_ALUNOS];

    for (int i = 0; i < NUM_ALUNOS; i++){
        Aluno aluno = Aluno(ras[i], nomes[i]);
        alunos[i] = aluno;
        arvoreBusca.inserirAluno(aluno);
    }

    cout << "Pre:  ";
    arvoreBusca.printPreOrdem();
    cout << endl;
    cout << "In:   ";
    arvoreBusca.printInOrdem();
    cout << endl;
    cout << "Pos: ";
    arvoreBusca.printPosOrdem();
    cout << endl;

    // Removendo aluno na raiz e verificando nova estrutura com os 3 tipos de percurso
    arvoreBusca.removerAluno(alunos[0].getRa());
/*    
                ******** PERCURSO PRÉ-ORDEM ********

                                   *1*
                                SARA-25
                         *2*  /      \  *5*
                       RAUL-18        PAULO-58
                  *3*   /  *4*\       /  *6*    
                CARLOS-7  LUCAS-19  MARIA-26  
                                            \  *7*                 
                                        ULISSES-30
 
                ******** PERCURSO IN-ORDEM ********

                                   *4*
                                SARA-25
                         *2*  /      \  *7*
                       RAUL-18        PAULO-58
                  *1*   /  *3*\       /  *5*    
                CARLOS-7  LUCAS-19  MARIA-26  
                                            \  *6*                 
                                        ULISSES-30

                ******** PERCURSO PÓS-ORDEM ********

                                   *7*
                                SARA-25
                         *3*  /      \  *6*
                       RAUL-18        PAULO-58
                  *1*   /  *2*\       /  *5*    
                CARLOS-7  LUCAS-19  MARIA-26  
                                            \  *4*                 
                                        ULISSES-30
*/


    cout << "********" << endl;
    cout << "Pre:  ";
    arvoreBusca.printPreOrdem();
    cout << endl;
    cout << "In:   ";
    arvoreBusca.printInOrdem();
    cout << endl;
    cout << "Pos: ";
    arvoreBusca.printPosOrdem();
    cout << endl;
}