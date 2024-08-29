/*
    COM210: Sistemas Computacionais

    Semana 5: Linguagem C: Ponteiro, Endereço e Memória
        -> Particionamento fixo

        -> MONOPROGRAMAÇÃO: único processo executado por vez no processador
        -> MULTIPROGRAMAÇÃO: vários processos compartilhando o processador
            -: Particionamento fixo e tamanho igual
            -: Particionamento fixo e tamanho variável
            -: Particionamento variável ou dinâmico
            
*/

#include <stdio.h>

// PARTICIONAMENTO FIXO COM TAMANHO FIXO

typedef struct {
    unsigned int bv; // 0 = partição vazia, 1 = processo na memória
    char processo[5]; // vetor de processos
} particao; particao RAM[10]; // vetor de partições

int main() {
    int i;

    // INICIALIZAÇÃO DA RAM
    for (i = 0; i < 10; i++)
        RAM[i].bv = 0;

    // ALOCAÇÃO DE PROCESSOS NA RAM
    for (i = 0; i < 10; i++)
        if (RAM[i].bv == 0) {
            printf("Insira um processo: ");
            RAM[i].bv = 1;
            scanf("%s", &RAM[i].processo);
        }

    // SIMULAÇÃO DO PROCESSADOR ENCERRANDO EXECUÇÃO DE PROCESSO
        strcpy(RAM[2].processo, "");
        RAM[2].bv = 0;
        printf("\n Processo n.3 finalizado\n");
        
        strcpy(RAM[8].processo, "");
        RAM[8].bv = 0;
        printf("\n Processo n.9 finalizado\n");

    // VISUALIZAÇÃO DA RAM SIMULADA
    printf("\n Status da RAM\n");
    for (i = 0; i < 10; i++)
        printf("%da Particao da RAM: [%d | %s]\n", i + 1, RAM[i].bv, RAM[i].processo);
    
    // NOVA ALOCAÇÃO DE PROCESSO
    for (i = 0; i < 10; i++)
        if (RAM[i].bv == 0) {
            printf("Insira um processo: ");
            RAM[i].bv = 1;
            scanf("%s", &RAM[i].processo);
        }

    // VISUALIZAÇÃO DA RAM SIMULADA
    printf("\n Status da RAM\n");
    for (i = 0; i < 10; i++)
        printf("%da Particao da RAM: [%d | %s]\n", i + 1, RAM[i].bv, RAM[i].processo);
}