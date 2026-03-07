// Receiver (принимает любые сообщения)
#include <SPI.h>
#include <LoRa.h>

const long frequency = 433E6; // та же частота
const int ssPin = 10;   // NSS/CS
const int resetPin = 9; // RST
const int dio0 = 2;     // DIO0 (IRQ)

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("LoRa Receiver");

  LoRa.setPins(ssPin, resetPin, dio0);
  if (!LoRa.begin(frequency)) {
    Serial.println("Ошибка запуска LoRa. Проверьте подключение и питание (3.3V).");
    while (1);
  }

  Serial.println("LoRa начат, ожидаю сообщения...");
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // получили пакет
    String incoming = "";
    while (LoRa.available()) {
      incoming += (char)LoRa.read();
    }

    Serial.print("Получен пакет: ");
    Serial.print(incoming);
    Serial.print("  | RSSI: ");
    Serial.println(LoRa.packetRssi());
  }

  // небольшой сон, чтобы не забивать CPU
  delay(10);
}