// Transmitter (отправляет "1" каждые 5 секунд)
#include <SPI.h>
#include <LoRa.h>

const long frequency = 433E6; // частота 433 MHz (проверьте местные ПРАВИЛА)
const int ssPin = 10;   // NSS/CS
const int resetPin = 9; // RST
const int dio0 = 2;     // DIO0 (IRQ)

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("LoRa Transmitter");

  LoRa.setPins(ssPin, resetPin, dio0);
  if (!LoRa.begin(frequency)) {
    Serial.println("Ошибка запуска LoRa. Проверьте подключение и питание (3.3V).");
    while (1);
  }

  Serial.println("LoRa начат");
}

void loop() {
  Serial.println("Отправляю: 1");
  LoRa.beginPacket();
  LoRa.print("1");
  LoRa.endPacket(); // неблокирующая отправка

  delay(5000); // 5 секунд
}