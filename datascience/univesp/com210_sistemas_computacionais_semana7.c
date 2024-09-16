/*
    COM210: Sistemas Computacionais

    Semana 7: Linguagem Assembly

    -> Linguagem de Montagem:
        -: Linguagem de programação de baixo nível
        -: Projetada para ser diretamente interpretada pelo processador
        -: Cada instrução é uma mnemônica que representa uma operação específica
        -: As instruções são escritas em um formato que pode ser diretamente entendido pelo processador
        -: Cada instrução tem um formato específico que inclui o opcode (código da operação) e um ou mais operandos
        -: As instruções são traduzidas para o formato de código de máquina que o processador pode executar
        -: As instruções são mais rápidas de executar do que as instruções em linguagem de alto nível, mas são mais difíceis de escrever e depurar


    -> Estrutura da sentença: () opcionais
        (rótulo): mnemônico operando(s) (comentário)
    
    -> Mnemônicos ou opcodes (pode variar entre arquiteturas):
        -: MOV: Move o valor de um operando para outro operando
        -: ADD: Adiciona o valor de um operando em outro operando
        -: SUB: Subtrai o valor de um operando de outro operando
        -: MUL: Multiplica o valor de um operando em outro operando
        -: DIV: Divide o valor de um operando em outro operando
        -: JMP: Checa a condição do operando, se 0, pula para um rótulo específico, no operando
        -: NZ: Condição para pular se o operando não for zero
        -: Z: Condição para pular se o operando for zero

    -> REGISTRADORES:
        -: Uso geral: podem ser usados para qualquer fim, porém geralmente algumas funções são reservadas para determinados registradores
            L: EAX: acumulador | devolve resultado de operações | indica interrupção e chamada de sistema
            L: EBX: endereços de base | ponteiro de dados
            L: ECX: contador | usado para loops
            L: EDX: dados | guardar dados de instruções
        -: Segmento: apontam para segmentos de memória
            L: CS: segmento de código
            L: DS: segmento de dados (variáveis, etc) | usado em instruções de manuseio de bloco
        -: Ponteiro:
            L: BP: apontador de base | endereço base da pilha
            L: SP: apontador de pilha | endereço topo da pilha
        -: Estado / Flags: cada bit significa um estado do processador
            L: C: carry | deslocamento de bits em operações aritméticas
            L: P: parity | se resultado tem paridade de 1s
            L: A: aux carry | deslocamento de bits em operações aritméticas
            L: Z: zero | se resultado da soma é zero
            L: S: sinal | se resultado é negativo
            L: T: trap
            L: I: interrupção
            L: O: overflow

            
        
        

    -> ASM Inline:
        -: Técnica de programação que permite a execução de código assembly diretamente em um programa escrito em linguagem de alto nível, como C/C++.
        -: Utilizar a diretiva __asm__() ou asm()
        -: As instruções assembly são escritas dentro de uma string
        -: Quebras de linha são permitidas, porém sintaxes podem variar entre montadores
        

        -> Estrutura estendida:
            __asm__(
                "código assembly"
                : "operandos de saída" (opcional)
                : "operandos de entrada" (opcional)
                : "registradores ou clobber list" (opcional)
            );

        
*/

#include <stdio.h>

/*
    ASSEMBLY INLINE:SOMA DE DOIS NÚMEROS

    ->  Operandos de saída:
        -: "=a" (resultado)
        -: "=r" (resultado2)
    ->  Operandos de entrada:
        -: "a" (x)
        -: "b" (y)

*/
int main(){
    // inicialização de variáveis
    int resultado = 0, resultado2 = 0, x = 3, y = 5;

    // código assembly inline (1)
    __asm__ (
        "movl %1, %%eax;" // move o valor de x para o registrador eax
        "movl %2, %%ebx;" // move o valor de y para o registrador ebx
        "addl %%ebx, %%eax;" // adiciona o valor de ebx ao eax, e armazena o resultado em eax
        :"=a" (resultado) // a soma de x e y (em eax) é armazenada em resultado
        :"a" (x), "b" (y) // instrui o compilador a passar os valores de x e y para eax e ebx
    );

    // código assembly inline alternativo (2)
    __asm__ (
        "addl %%ebx, %%eax;" // adiciona o valor de ebx ao eax, e armazena o resultado em eax
        :"=r" (resultado2) // o resultado da soma (em eax) é armazenado em resultado2
        :"a" (x), "b" (y) // instrui o compilador a passar os valores de x e y para eax e ebx
    );

    printf("resultado = %d\n", resultado);
    printf("resultado2 = %d\n", resultado2);

    return 0;

    /*
        NOTAS SOBRE O CÓDIGO (2):
            -> Diferentemente do código (1), que armazena explicitamente as variáveis x e y nos registradores eax e ebx, 
            o código (2) não especifica os registradores que armazenarão os valores de x e y.
            -> O código presume que os valores de interesse estarão disponíveis nos registradores eax e ebx.
                -: Pode resultar em valores indesejados no tempo de execução se os valores de x e y não estão disponíveis nesses registradores.    
    */ 
}
