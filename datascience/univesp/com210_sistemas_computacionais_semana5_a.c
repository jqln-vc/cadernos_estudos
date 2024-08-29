/*
    COM210: Sistemas Computacionais

    Semana 5: Linguagem C: Ponteiro, Endereço e Memória
        -> Simulação de Paginação


        -> MEMÓRIA FÍSICA / MEMÓRIA PRINCIPAL: armazena os dados e programas que estão sendo usados ativamente pelo sistema
            -: capacidade limitada: todos os processos em execução precisam compartilhar esse recurso limitado
        -> MEMÓRIA VIRTUAL: permite que programas grandes sejam executados em sistemas com memória física limitada
            -: espaço de endereçamento virtual que pode ser maior que a memória física, mapeado para o DISCO
        -> PAGINAÇÃO: gerenciamento de memória
            -: MEMÓRIA VIRTUAL: dividida em unidades de tamanho fixo chamadas de PÁGINAS
            -: MEMÓRIA FÍSICA: memória física é dividida em blocos de tamanho fixo chamados de FRAMES
            -: PÁGINA (memória virtual)
            -: FRAMES (memória física): correspondem ao tamanho de uma PÁGINA (memória virtual)
            -: PROCESSO: cada um tem sua TABELA DE PÁGINAS
            -: TABELA DE PÁGINAS: Cada processo tem uma tabela de páginas que mapeia páginas virtuais para frames físicos
                l: se a PÁGINA desejada não estiver na MEMÓRIA FÍSICA (um evento conhecido como page fault), o sistema operacional a carrega do DISCO para um FRAME livre na MEMÓRIA FÍSICA
        -> PAGE FAULT: quando um processo tenta acessar uma página que não está atualmente na memória física
            -: o sistema operacional precisa carregar a página do disco rígido para a memória física, o que pode causar uma desaceleração significativa, pois o acesso ao disco é muito mais lento do que o acesso à RAM
        
        -> Implementação no HARDWARE
            -: normalmente, por unidades dedicadas de hardware integradas nos processadores
            -: feita pelo MMU (Memory Management Unit)
        
        
        
        -> NO DISCO, cada PÁGINA tem:
            -: Bit de validade (bv=1 -> pv na RAM)
                L: indica se a pv está carregada (1) ou não (0) na memória principal (RAM)
            -: Ponteiro para página virtual (pv)
            -: Deslocamento (dv)
        
        -> NA RAM, cada FRAME tem:
            -: Número da página física (pf)
            -: Deslocamento (df)
            -: Conteúdo
            
*/

#include <stdio.h>

// memória física (RAM)
typedef struct frames {
    int bv; // bit de validade
    char conteudoRAM;
} frame;


typedef struct paginas {
    int bv; // bit de validade
    char conteudoDISCO;
    frame *pv; // ponteiro página virtual
} pagina;

pagina DISCO[20];
frame RAM[2];
int i, j;

int main() {

    // SIMULAÇÃO DE PAGINAÇÃO SIMPLES

    // INICIALIZANDO DA RAM
    for (i = 0; i < 2; i++)
        RAM[i].bv = 0; // bit de validade inicializado em 0

    // PAGINAÇÃO
    for (i = 0; i < 20; i++) {
        DISCO[i].conteudoDISCO = 'a' + i;
        DISCO[i].bv = 1; // bit de validade inicializado em 1, pois está sendo inserido conteúdo no disco
        DISCO[i].pv = NULL; // ainda não carregado na MEMÓRIA PRINCIPAL (RAM)

        // SIMULAÇÃO QUE A 5ª E A 10ª PÁGINAS SÃO MAIS USADAS, SENDO SUBIDAS NA RAM
        if ((DISCO[i].conteudoDISCO == 'e') || (DISCO[i].conteudoDISCO == 'j'))
            for (j = 0; j < 2; j++)
                if (RAM[j].bv == 0) { // verificar se a MEMÓRIA RAM está livre
                    RAM[j].bv = 1;
                    DISCO[i].pv = &RAM[j]; // ponteiro do DISCO aponta para o endereço na RAM, que guarda a PÁGINA
                    RAM[j].conteudoRAM = DISCO[i].conteudoDISCO; // sobe o conteúdo para a RAM
                    j = 2;
                }
    }
    printf("VISUALIZACAO DISCO\n");
    for (i = 0; i < 20; i++) {
        printf("%d pagina [conteudo: %c", i + 1, DISCO[i].conteudoDISCO);
        printf(" BV: %d", DISCO[i].bv);
        printf(" RAM: %d]\n", DISCO[i].pv); // ponteiro para MEMÓRIA VIRTUAL (PÁGINA)
    }
    printf("VISUALIZACAO RAM\n");
    for (j = 0; j < 2; j++) {
        printf("%d frame [conteudo: %c", j + 1, RAM[j].conteudoRAM);
        printf(" BV: %d]\n", RAM[j].bv);
    }
    return(0);
}
