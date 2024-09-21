/*
    COM160: Estruturas de Dados

    Semana 6: Árvores AVL e Grafos
        -> Estrutura da Tabela Hash
            -: lógica (header): 
                L: classe Aluno: com160_aluno.h
                L: classe Hash: com160_hash.h
            -: implementação: com160_estruturas_dados_semana6.cpp
            -: execução: com160_hash_main.cpp


            -: comando de compilação (certificar-se de estar no folder)
                g++ com160_hash_main.cpp com160_estruturas_dados_semana4_a.cpp -o hash
            -: execução após compilação
                .\hash
*/
/*
    ÁRVORES AVL
        -> A busca em árvore é EFICIENTE em ÁRVORES BALANCEADAS.
            -: O número de COMPARAÇÕES é proporcional à ALTURA DA ÁRVORE
        
        -> FATOR DE BALANCEAMENTO: diferença de altura entre as subárvores da esquerda e da direita
            -: Em árvores AVL, deve ficar no intervalo [-1,1]
            -: Caso, após inserção ou remoção, algum nó violar o fato de balanceamento
                uma ROTAÇÃO deve ser feita.


*/
