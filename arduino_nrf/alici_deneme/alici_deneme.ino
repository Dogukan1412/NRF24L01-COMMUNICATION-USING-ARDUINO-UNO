
#include <SPI.h>
#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

RF24 receiver(7,8); //CE,CSN pinleri secildi
const uint64_t channel = 0x000000000011;  // kanal sifreleme
int message[5];  // alinan degerleri diziye ata

void setup() {
  Serial.begin(9600);  // 9600 baudrate
  receiver.begin();   // radyo baslatma
  receiver.openReadingPipe(1,channel);   //sifreli kanaldan okuma
  receiver.setAutoAck(false);
  receiver.setDataRate(RF24_250KBPS);
  receiver.setPALevel(RF24_PA_HIGH);
  receiver.startListening(); // radyo'yu alici olarak baslat
}

void loop() {
  if (receiver.available())  // radyo musait
  {
    receiver.read(message, sizeof(message));  // gelen degerleri oku
    analogWrite(3, message[0]);  // gelen degerleri pinlere yazdır
    analogWrite(5, message[1]);
    analogWrite(6, message[2]);
    analogWrite(9, message[3]);
    analogWrite(10, message[4]);
    analogWrite(4, message[5]);
  }
}
