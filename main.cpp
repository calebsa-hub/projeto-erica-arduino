/*
Código do projeto de apresentação de modelos atomicos para Deficientes Visuais
Autor: Caleb F. Sá
Responsável: Érica Sabrina
jan-2024 
*/

#include <SoftwareSerial.h>

// Definindo os pinos RX e TX para a comunicação com o módulo Bluetooth HC-05
const int rxPin = 2; // RX do HC-05 conectado ao pino digital 2 do Arduino
const int txPin = 3; // TX do HC-05 conectado ao pino digital 3 do Arduino
const int buttonPins[] = {4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
const int numButtons = 10;
// Inicializando o objeto SoftwareSerial para comunicar com o módulo Bluetooth
SoftwareSerial bluetooth(rxPin, txPin); // RX, TX

void setup() {
  // Iniciando a comunicação serial com o computador
  Serial.begin(9600);
  //Serial.println("Digite AT para configurar o módulo Bluetooth.");

  // Iniciando a comunicação serial com o módulo Bluetooth
  bluetooth.begin(9600);

  for (int i = 0; i < numButtons; ++i) {
    pinMode(buttonPins[i], INPUT);
    digitalWrite(buttonPins[i], HIGH);
  }
}

void loop() {
  if (bluetooth.available()) {
    // Se houver dados disponíveis para leitura do módulo Bluetooth
    char receivedChar = bluetooth.read();
    Serial.print(receivedChar); // Imprime os dados recebidos no Monitor Serial
  }

  if (Serial.available()) {
    // Se houver dados disponíveis para leitura do Monitor Serial
    char sendChar = Serial.read();
    bluetooth.print(sendChar); // Envia os dados do Monitor Serial para o módulo Bluetooth
  }

  if (Serial.available()) {
    for(int i = 0; i < numButtons; ++i){
      if(digitalRead(buttonPins[i]) == LOW) {
        //botao pressionado
        bluetooth.print('');
        delay(1000);
      }
    }
  }
}
