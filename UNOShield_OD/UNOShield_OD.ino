/***************************************************************************************
Exemplo de utilização da library AcquaShield com o Shield de OD, 
este exemplo mostra como realizar a leitura de OD e temperatura do Shield, 
realizar o procedimento de calbração do eletrodo de OD, 
fazer a leitura dos parâmetros de calibração e mostrar dados no display do Shield de OD.

******** Procedimento de calibração do eletrodo de OD: ********
** Abra o "Serial Monitor" do Arduino.
-> Envie o comando #ODCal#
** O Shield retornará "Procedimento de calibração iniciado...".
** O Shield começará a enviar as leituras de tensão do circuito.
** Retire o eletrodo de OD do conector do Shield e coloque um "Jumper" entre os terminais. 
-> Envie o comando #Cal,cc#
<- O Shield deve retornar *OK
** Este comando faz a correção da tensão de offset do circuito eletrônico.
** Retire o jumper do conector do Shield e conecte o eletrodo de OD.
** Separe a solução de calibração (0 mg/L).

** Coloque o eletrodo, inicialmente, na solução de calibração.
** O Shield começará a enviar as leituras de OD, aguarde até que a leitura de OD se estabilize.
-> Envie o comando #Cal,00#
<- O Shield deverá retornar *OK.
** Lave o eletrodo em águua corrente.
** Posteriormente, deixe o eletrodo em ar atmosférico e aguarde a leitura de OD, no terminal serial, se estabilizar.
-> Envie o comando #Cal,ar#
<- O Shield deve retornar *OK
** Ao finalizar os procedimentos de calibração...

-> Envie o comando F
** O Shield retornará "Rotina de calibração finalizada, reinicie o sistema..."
** Reinicie todo sistema (Arduino + Shield).
** Pronto, seu Shield de OD está calibrado.


** Firmware desenvolvido para Arduino UNO/Duemilanove **
** Leonardo Lopes de Albuquerque **
** 14/03/2024 **
***************************************************************************************************************************************************************************/

#include <Arduino.h>
#include "include/AcquaShield.h"

ODShield Shield_OD;

int relayPin = 13; // Usado para controlar aeradores. Quando HIGH irá ligar o aerador. Quando LOW desligará
float minOxygen = 5.0; // Quando estiver abaixo deste valor liga o aerador
float maxOxygen = 6.0; // Quando estiver acima deste valor desliga o aerador

void setup() {
    Serial.begin(9600);
    Shield_OD.init();

    pinMode( relayPin, OUTPUT );
}

void loop() {
    static char vetor_temp[6];              //Vetor para armazenar a string de temperatura do Shield de EC.
    static char vetor_OD[12];               //Vetor para armazenar a string de EC do Shield de EC.

    float od = 0.0;

    Shield_OD.DispBuffClear();      //Limpa o buffer do display do Shield de OD.
      
    // mg/l
    od = Shield_OD.OD();                       //Faz a leitura do valor de OD do Shield.

    if ( od <= minOxygen ) {
      digitalWrite( 13, HIGH );
    }
    
    if ( od >= maxOxygen ) {
      digitalWrite( 13, LOW );
    }

    dtostrf(od, 2, 1, vetor_OD);               //Faz a leitura do OD e converte a variável float "OD" em string.
    strcpy(vetor_OD, vetor_OD);                //Deixa a String no formato correto para ser mostrada no display do Shield de OD.     
    Shield_OD.DispWrite(2, 0, 9, vetor_OD);
    Shield_OD.DispWrite(2, 30, 9, "mg/L");

    // %
    od = Shield_OD.ODsat();  

    dtostrf(od, 3, 0, vetor_OD);               //Faz a leitura do OD e converte a variável float "OD" em string.
    strcpy(vetor_OD, vetor_OD);
    Shield_OD.DispWrite(2, 80, 9, vetor_OD);
    Shield_OD.DispWrite(2, 110, 9, "%");

    // Temp
    dtostrf(Shield_OD.temp(), 2, 1, vetor_temp);  //Faz a leitura da temperatura e converte a variável float "temp" em string.
    strcpy(vetor_temp, vetor_temp);               //Deixa a String no formato correto para ser mostrada no display do Shield de OD.
    Shield_OD.DispWrite(1, 0, 32, "Temp:");
    Shield_OD.DispWrite(1, 33, 32, vetor_temp);

    Shield_OD.DispShow();
    delay( 500 );
}
