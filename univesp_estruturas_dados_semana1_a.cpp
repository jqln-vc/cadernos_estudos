/*
COM160: Estruturas de Dados

Semana 1: Introdução ao C++
    - comandos básicos
*/

#include <iostream>
using namespace std; // para não precisar escrever std::cout ou std::cin

// FUNÇÕES
    /*
        PARÂMETRO POR VALOR: recebe uma cópia da variável,
        não altera os valores originais

        PARÂMETRO POR REFERÊNCIA: recebe uma referência da variável,
        altera os valores originais
    */

// PARÂMETRO POR VALOR

void troca_por_valor(int a, int b){
    int temp;
    temp = a;
    a = b;
    b = temp;
}

// PARÂMETRO POR REFERÊNCIA

void troca_por_referencia(int &a, int &b){
    int temp;
    temp = a;
    a = b;
    b = temp;
}

int main() {
    cout << "Começando!" << "\n";
    
    // COMANDOS DE REPETIÇÃO
    // WHILE

    int digito;
    int contador = 0;
    int soma = 0;

    while (contador < 3) {
        cout << "Digite um número (" << contador << ")" << endl;
        cin >> digito;

        soma += digito;
        
        contador++;
    }
    cout << "A soma final é:" << soma << "." << endl;


    //FOR: séries

    int serie;

    for (int numero = 2; numero <= 10; numero += 2)
        serie += numero;

    cout << "A soma da série é" << serie << "." << endl;


    // DO WHILE
    float valor;
    soma = 0;
    contador = 0;

    do {
        cout << "Insira um valor para a média: " << endl;
        cin >> valor;

        soma += valor;
        contador++;
    } while (valor >= 0);

    
    float media = float(soma) /float((contador-1)); // subtrai-se 1 para não incluir no contador a entrada que encerra o loop
    cout << "A média é dos " << (contador-1) << "valores é : " << media << endl;
    
    // TESTE FUNÇÕES PARÂMETROS VALOR E REFERÊNCIA

    int a = 2, b = 10;
    cout << "Antes: a = " << a << "| b = " << b << endl;
    troca_por_valor(a,b);
    cout << "TROCA POR VALOR -> Depois: a = " << a << "| b = " << b << endl;

    cout << "Antes: a = " << a << "| b = " << b << endl;
    troca_por_referencia(a,b);
    cout << "TROCA POR REFERÊNCIA -> Depois: a = " << a << "| b = " << b << endl;

    return 0;
}


