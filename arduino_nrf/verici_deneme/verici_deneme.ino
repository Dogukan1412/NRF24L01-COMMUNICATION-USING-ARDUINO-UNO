
#include <SPI.h>
#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

RF24 transmitter(7,8); //CE,CSN pinleri secildi
const uint64_t channel = 0x000000000011;   // kanal sifreleme
int throttle = A0;   // analog girisler tanimlama
int yaw = A1;
int pitch = A2;
int roll = A3;
int stick1 = A4;
int stick2 = A5;
int message[5];   // degerlerin tutulacagı dizi

void setup() {
  Serial.begin(9600);  //9600 baudrate
  transmitter.begin();  // radyo baslatma
  transmitter.openWritingPipe(channel); // sifreli kanala yazma
  transmitter.setAutoAck(false);
  transmitter.setDataRate(RF24_250KBPS);
  transmitter.setPALevel(RF24_PA_HIGH);
  transmitter.stopListening(); // radyo'yu gönderici olarak baslat
}

void loop() {
  int throttle_value = analogRead(throttle);           // analog degerleri oku
  int throttle_value_map = map(throttle_value, 0, 1023, 0, 255);     // okunan degerlere aralık belirleme
  //int throttle_value_map = map(throttle_value, 0, 255, 1000, 3000);
  
  int yaw_value = analogRead(yaw);
  //int yaw_value_map = map(yaw_value, 0, 1023, 0, 255);
  int yaw_value_map = map(yaw_value, 0, 255, 1000, 1300);
  
  int pitch_value = analogRead(pitch);
  int pitch_value_map = map(pitch_value, 0, 1023, 1000, 1500);
  
  int roll_value = analogRead(roll);
  int roll_value_map = map(roll_value, 0, 1023, 0, 255);

  int stick1_value = analogRead(stick1);
  int stick1_value_map = map(stick1_value, 0, 1023, 0, 255);

  int stick2_value = analogRead(stick2);
  int stick2_value_map = map(stick2_value, 0, 1023, 0, 255);
  
  message[0] = throttle_value_map;  // degerleri diziye ata
  message[1] = yaw_value_map;
  message[2] = pitch_value_map;
  message[3] = roll_value_map;
  message[4] = stick1_value_map;
  message[5] = stick2_value_map;
  /*Serial.print(message[0]);
  Serial.print("\n");*/
  transmitter.write(message, sizeof(message));  // degerleri alıcıya yazdır
}
