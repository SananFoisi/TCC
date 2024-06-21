#include <SPI.h>
#include <Ethernet.h>

// Configurações da Ethernet
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 177);
EthernetServer server(80);

// Pinos dos relés
const int relayPins[] = { 2, 3, 4, 5, 6 };
const int numRelays = 5;

// Pinos dos sensores LDR
const int ldrPins[] = { A0, A1, A2 };
const int numLDRs = 3;

// Pino do sensor de temperatura LM35
const int lm35Pin = A3;

// Pino do sensor de chuva FD10
const int rainSensorPin = 7;

void setup() {
  // Inicializa os relés
  for (int i = 0; i < numRelays; i++) {
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], LOW);  // Desliga todos os relés inicialmente
  }

  // Inicializa o sensor de chuva
  pinMode(rainSensorPin, INPUT);

  // Inicializa a Ethernet
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.begin(9600);
  Serial.println("Server is at ");
  Serial.println(Ethernet.localIP());
}

void loop() {
  EthernetClient client = server.available();
  if (client) {
    String request = client.readStringUntil('\r');
    client.flush();

    // Verifica qual relé deve ser controlado
    for (int i = 0; i < numRelays; i++) {
      if (request.indexOf("/relay" + String(i + 1) + "/on") != -1) {
        digitalWrite(relayPins[i], HIGH);
      } 
      else if (request.indexOf("/relay" + String(i + 1) + "/off") != -1) {
        digitalWrite(relayPins[i], LOW);
      }
    }

    // Leitura dos sensores LDR
    float ldrPercentage[numLDRs];
    for (int i = 0; i < numLDRs; i++) {
      ldrPercentage[i] = (analogRead(ldrPins[i]) / 1023.0) * 100.0;
    }

    // Leitura do sensor LM35 e conversão para temperatura
    float voltage = (analogRead(lm35Pin) * 5.0) / 1023.0;
    float temperatureC = voltage * 100.0; // Fator de 10 mV por grau Celsius

    // Leitura do sensor de chuva
    int rainState = digitalRead(rainSensorPin);
    String rainStatus = (rainState == HIGH) ? "Chovendo" : "Não chovendo";

    // Responde ao cliente com a página HTML/CSS
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html; charset=UTF-8");
    client.println();
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println("<head>");
    client.println("<style>");
    client.println("body { font-family: Arial, sans-serif; margin: 0; padding: 0; display: flex; justify-content: center; align-items: center; height: 100vh; background-color: #f0f0f0; }");
    client.println(".container { text-align: center; background: #fff; padding: 20px; border-radius: 8px; box-shadow: 0 0 10px rgba(0, 0, 0, 0.1); }");
    client.println("h1 { margin-bottom: 20px; color: #333; }");
    client.println(".button { display: inline-block; padding: 10px 20px; margin: 10px; font-size: 16px; color: #fff; background-color: #007bff; border: none; border-radius: 4px; text-decoration: none; cursor: pointer; transition: background-color 0.3s; }");
    client.println(".button:hover { background-color: #0056b3; }");
    client.println("</style>");
    client.println("</head>");
    client.println("<body>");
    client.println("<div class=\"container\">");
    client.println("<h1>Controle de Relés</h1>");

    // Adiciona botões de controle dos relés
    for (int i = 0; i < numRelays; i++) {
      client.print("<a href=\"/relay");
      client.print(i + 1);
      client.print("/on\" class=\"button\">Relé ");
      client.print(i + 1);
      client.println(" ON</a>");
      client.print("<a href=\"/relay");
      client.print(i + 1);
      client.print("/off\" class=\"button\">Relé ");
      client.print(i + 1);
      client.println(" OFF</a>");
    }

    // Exibe a temperatura
    client.print("<h1>Temperatura: ");
    client.print(temperatureC);
    client.println("°C</h1>");

    // Exibe a porcentagem de luminosidade dos sensores LDR
    client.println("<h1>Sensores LDR</h1>");
    for (int i = 0; i < numLDRs; i++) {
      client.print("<p>Sensor LDR ");
      client.print(i + 1);
      client.print(": ");
      client.print(ldrPercentage[i]);
      client.println("%</p>");
    }

    // Exibe o status da chuva
    client.print("<h1>Status da Chuva: ");
    client.print(rainStatus);
    client.println("</h1>");

    client.println("</div>");
    client.println("</body>");
    client.println("</html>");

    delay(1);
    client.stop();
  }
}
