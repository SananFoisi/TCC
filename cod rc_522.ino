#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  // Inicializa o sensor RC522
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.begin(9600);
  Serial.println("Aproxime o cartão do leitor...");
  
  // Inicializa os relés, sensor de chuva e Ethernet como antes
  ...
}

void loop() {
  // Código de leitura RFID
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    Serial.print("UID tag: ");
    String content = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""));
      content.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    content.toUpperCase();
    
    if (content.substring(0) == "YOUR_CARD_UID") {  // Substitua YOUR_CARD_UID pelo UID do cartão
      digitalWrite(relayPins[0], HIGH); // Aciona o relé 1
      delay(500); // Atraso para evitar múltiplas leituras
    }
    mfrc522.PICC_HaltA();
  }

  // Código de controle dos relés, leitura de sensores e resposta ao cliente
  ...
}
