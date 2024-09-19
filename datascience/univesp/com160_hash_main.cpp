/*
    COM160: Estruturas de Dados

    Semana 4: Tabela Hash

            -: lógica (header): 
                L: classe Aluno: com160_aluno.h
                L: classe Hash: com160_hash.h
            -: implementação: 
                L: sem tratamento de colisões: com160_estruturas_dados_semana4_a.cpp
                L: com tratamento de colisões: com160_estruturas_dados_semana4_b.cpp
            -: execução: com160_hash_main.cpp


            -: comando de compilação (certificar-se de estar no folder)
                g++ com160_hash_main.cpp com160_estruturas_dados_semana4_a.cpp -o hash
                g++ com160_hash_main.cpp com160_estruturas_dados_semana4_b.cpp -o hash_com_tratamento
            -: execução após compilação
                .\hash
                .\hash_com_tratamento
*/
/*
    TABELA HASH
        -> Sinônimos: dicionário, mapa, array associativo
        -> Busca EFICIENTE em tempo constante (mantidas algumas condições restritivas)
            L: A tabela será organizada em memória como um VETOR (ou array)
        -> Estrutura de dados que mapeia CHAVES para VALORES
            L: CHAVE: qualquer tipo, identificador único -> mapeia para um endereço de memória
            L: VALOR: inteiro, para efetuar a busca no vetor -> índice do vetor
        
        -> Função de Espalhamento: f(chave) -> endereço
            L: vetor tamanho N, para valores bem distribuídos em um intervalo entre 0 e N-1
                L: necessário minimizar ocorrência de COLISÕES (2 chaves diferentes mapeadas para o mesmo endereço)
        
            ->> FUNÇÃO EXEMPLO 1:
                -: Mapear a somatória de inteiros de uma string,
                    de acordo com o valor de cada caractere na tabela ASCII, ao valor de um índice de vetor
                -: Tempo constante K: sendo K o limite de caracteres aceitos na chave
                -: PROBLEMA: chaves com os mesmos caracteres resultariam em um mesmo valor inteiro!
                    L: SOLUÇÃO: parametrizar um PESO para a POSIÇÃO dos caracteres na string
                        L: C0.a**(k-1) + C1.a**(k-2) + C2.a**(k-3)... + Ck-2.a**(1) + Ck-1
                        L: para a != 0 | 1
                        L: valor de a ALTO (>33, primos) tende a diminuir o nº de colisões
                            L: valor MUITO ALTO pode levar a overflow de inteiros
                            L: pode-se fazer uma compressão: i % N (N sendo o tamanho do vetor)
                            L: quanto maior N, menor o nº de colisões
                            L: escolher um valor PRIMO para N (diminui denominadores comuns)
            
        -> TRATAMENTO DE COLISÕES
            -: As colisões são inevitáveis e precisam ser tratadas em uma tabela hash.
                L: ocorrem quando a função de espalhamento aponta 2 (ou mais) chaves para o mesmo endereço
            
            -: TIPOS:
                L: ENCADEAMENTO SEPARADO: cada endereço A[i] é um ponteiro para uma LISTA ENCADEADA
                    que conterá todos os ELEMENTOS DE MESMO ÍNDICE (elementos que colidiram).
                    L: ao colocar N elementos em M endereços, espera-se N/M entradas por endereço
                    L: FATOR DE CARGA (N/M): o ideal é que seja limitado por uma constante, idealmente menor que 1
                        L: significa que, para um boa função de hash, existirão sempre endereços vazios
                
                L: TESTE LINEAR: colisões serão tratadas sem alocação de memória adicional, será utilizado o próprio vetor
                    L: ao colocar um item (k,v) em um endereço A[i] já ocupado com i=h(k), tenta-se em um novo endereço A[(i+1 mod M)]
                        L: as tentativas continuam até que um endereço vazio seja encontrado
                        L: problema de agrupamento: pesquisas podem se tornar lentas, devido à alocação em posições contíguas
                    L: SOLUÇÕES DE AGRUPAMENTO:
                        L: Teste Quadrático: testa em posições A[(i+f(j) mod M)] em que f(j) = j**2
                            L: evita o agrupamento sequencial mas cria novos padrões de agrupamento
                        L: Hashing Duplo: utiliza uma nova função g(k) para tratar colisões
                            L: A[(i+f(j)) mod M] sendo que f(j) = j*g(k)
                            L: a função de hashing secundária g(k) não pode resultar em 0
                            
            ->> FUNÇÃO EXEMPLO 2: Tratando colisões a partir da função 1 com Teste Linear
                L: a função para OBTER o item deverá examinar endereços consecutivos
                L: a função DELETE não poderá mais remover os itens, pois cada item é um "indício" das possíveis colisões consecutivas
                    L: a solução será substituir o item a ser removido por um MARCADOR "DISPONÍVEL" (-2)
                    L: a função OBTER poderá utilizar os endereços "disponíveis" para inserir entradas
*/         


#include <iostream>
#include "com160_hash.h" 

using namespace std;


// TESTES DAS TABELAS: COM E SEM TRATAMENTO DE COLISÕES
int main(){
    Hash alunosHash(10); // inicialização de uma tabela Hash com tamanho 10
    
    // FUNÇÃO 1: haverá colisão entre os RAs 12704, 1234 e 91234, todos possuem resto 4
    int   ras[7]   = {
        12704, 31300, 1234,
        49001, 52202, 65606,
        91234};
    string nomes[7] = {
        "Pedro", "Raul", "Paulo",
        "Carlos", "Lucas", "Maria",
        "Samanta"}; 
    
    // Loop de inserção dos vetores de RAs e Alunos na tabela
    // FUNÇÃO 1: os RAs colididos serão sobrescritos
    for (int i = 0; i < 7; i++) {
        Aluno aluno = Aluno(ras[i], nomes[i]);
        alunosHash.inserirAluno(aluno);
    }
    alunosHash.print();  
    cout << "--------APÓS INSERIR---------" <<  endl;
    
    Aluno aluno(12704,"");  
    bool     found = false;
    alunosHash.obterAluno(aluno, found);

    // FUNÇÃO 1: aluno não será encontrado, resultado == 0, pois houve colisão na inserção
    cout << aluno.getNome() << " Aluno RA 12704 encontrado? -> " << found << endl;
    
    cout << "--------APÓS REMOVER RA:12704---------" <<  endl;

    /*
        FUNÇÃO 1: remoção errada por conta da colisão, dado que o RA 12704 também mapeava para o 91234
                    L: o aluno deletado seria Pedro, mas Samanta foi removida
        FUNÇÃO 2: remoção correta, dado que o RA 12704 não mapeava para o 91234
            L: posição 4 do vetor será marcada como DISPONÍVEL após remoção, com -2
    */

    alunosHash.removerAluno(aluno);
    alunosHash.print();
    cout << "Fim" << endl;  
}