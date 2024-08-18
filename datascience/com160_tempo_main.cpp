/*
COM160: Estruturas de Dados

Semana 2: As visões das estruturas de dados
    -> Classes
        -: lógica (header): com160_tempo.h
        -: implementação: univesp_com160_estruturas_dados_semana2_a.cpp
        -: execução: com160_tempo_main.cpp

        !comando de compilação (certificar de estar no folder)
            ?g++ com160_tempo_main.cpp univesp_com160_estruturas_dados_semana2_a.cpp -o tempo
        !execução após compilação
            ?.\tempo
*/

#include <iostream>
#include "com160_tempo.h" //import da classe Tempo
using namespace std;


int main() {
  /*
    Neste primeiro objeto, passamos todos os parâmetros. Em outras
    palavras, nenhum valor padrão foi usado.
   */
  
  Tempo t1(23, 59, 59);   
  t1.print();       // 23:59:59
  t1.setHora(12);
  t1.setMinuto(30);
  t1.setSegundo(15);
  
  t1.print();       // 12:30:15
  cout << "Hora:    " << t1.getHora()   << endl;
  cout << "Minuto:  " << t1.getMinuto() << endl;
  cout << "Segundo:  " << t1.getSegundo() << endl;

  /*
    Nesta segunda instância, usamos o padrão apenas para minutos e
    segundos.
   */
  Tempo t2(12); 
  t2.print();  // 12:00:00

  Tempo t3(23, 59, 58);
  t3.print();  // 23:59:58
  t3.adicionaSegundo();
  t3.print();  // 23:59:59
  t3.adicionaSegundo();
  t3.print();  // 00:00:00
}