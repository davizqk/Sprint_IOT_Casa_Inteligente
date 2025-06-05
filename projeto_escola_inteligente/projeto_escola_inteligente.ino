//Bibliotecas
#include <DHT11.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN A1      //Define qual será o pino para o sensor
#define DHTTYPE DHT11  // Variável od tipo DHT

DHT dht(DHTPIN, DHT11);  //Inicializa o objeto DHT com o pino e o tipo

//Variáveis Globias
const int PIR = 2;  //Pino digital que o PIR está plugado
int ledVermelho = 13;

//
const int MQ135 = A0;  //Pino Analogico do mq-135
const int buzzer = 12;

void LEDPorPresenca() {
  int estadoPIR = digitalRead(PIR);  //le o pino Digital 2

  //HIGH vale o valor de 1
  //LOW vale o valor 0
  if (estadoPIR == HIGH) {
    Serial.println("LED aceso");
    digitalWrite(ledVermelho, HIGH);

  } else {
    Serial.println("LED apagado");
    digitalWrite(ledVermelho, LOW);
  }


}  //fim da função

void alarme_dois_tons() {
  int freqAlta = 4000;
  int freqBaixa = 2000;
  int duracaoTom = 400;

  tone(buzzer, freqAlta, duracaoTom);
  delay(duracaoTom);
  tone(buzzer, freqBaixa, duracaoTom);
  delay(duracaoTom);
}

void sensorDeGas() {
  int estadoMQ135 = analogRead(MQ135);

  if (estadoMQ135 >= 300) {
    alarme_dois_tons();
  } else {
    noTone(buzzer);
  }

  Serial.println(estadoMQ135);
}

void temperaturaEUmidade() {
  float umidade = dht.readHumidity();         //le a umidade
  float temperatura = dht.readTemperature();  //le a temperatura em Celsius

  Serial.println("Umidade: " + String(umidade) + "%");
  Serial.println("Temperatura: " + String(temperatura) + "C");
  delay(5000);
}

void setup() {
  Serial.begin(9600);
  pinMode(ledVermelho, OUTPUT);
  pinMode(MQ135, INPUT);
  pinMode(buzzer, OUTPUT);

  //inicializa o sensor DHT
  dht.begin();

  Serial.println("Calibrando os sensores");
  delay(10000);
  Serial.println("Sensores calibrados parceiro(a), pode testar");
}  //fim do setup

void loop() {
  //As instruções no loop será somente chamada por funções

  //LEDPorPresenca();
  //sensorDeGas();
  temperaturaEUmidade();
}  //fim do loop
