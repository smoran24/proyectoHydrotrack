#include <ESP8266WiFi.h>
#include <WebSocketsClient.h>

const char* ssid = "Floresta";          // nombre de tu red Wi-Fi
const char* password = "45203070";      // contraseña de tu red Wi-Fi
const char* serverIP = "192.168.100.27"; // dirección IP de tu servidor Node.js local
//const char* serverIP = "192.168.100.15";
const int serverPort = 8080;            // puerto del servidor WebSocket
//const int serverPort = 3000;
WebSocketsClient webSocket;

volatile int pulseCount = 0;
int PinSensor = D2;                 // Sensor conectado al pin D2 (GPIO4)
float factor_conversion = 7.11;     // Factor de conversión para convertir de frecuencia a caudal
float volume = 0;
long t0 = 0;                        // millis() del ciclo anterior

void ICACHE_RAM_ATTR pulseCounter() {
  pulseCount++;
}

void setup() {
  Serial.begin(9600);
  connectToWiFi();
  webSocket.begin(serverIP, serverPort, "/");
  webSocket.onEvent(webSocketEvent);
  pinMode(PinSensor, INPUT);
  attachInterrupt(digitalPinToInterrupt(PinSensor), pulseCounter, RISING);
  t0 = millis();
}

void loop() {
  webSocket.loop();
  if (webSocket.isConnected()) {
    float flow_L_m = pulseCount / factor_conversion; // Calcula el flujo en L/m
    pulseCount = 0; // Reinicia el contador de pulsos
    long dt = millis() - t0; // Calcula la variación de tiempo
    t0 = millis();
    volume = volume + (flow_L_m / 60) * (dt / 1000); // Volumen (L) = Flujo (L/s) * Tiempo (s)
  
    // Envía los datos al servidor WebSocket
    String dataToSend = "Flow: " + String(flow_L_m, 3) + " L/min, Volume: " + String(volume, 3) + " L";
    webSocket.sendTXT(dataToSend);
  
    // Muestra los datos en el monitor serie
    Serial.println(dataToSend);
    // Agrega un retraso de 1 segundo (1000 milisegundos)
    delay(1000);
  }
}


void connectToWiFi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }
  Serial.println("Conexión WiFi establecida");
  Serial.print("Dirección IP asignada: ");
  Serial.println(WiFi.localIP());
}

void webSocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch(type) {
    case WStype_DISCONNECTED:
      Serial.println("Websocket Disconnected.");
      break;
    case WStype_CONNECTED:
      Serial.println("Websocket Connected.");
      break;
    case WStype_TEXT:
      Serial.print("Received data: ");
      Serial.println((char*)payload);
      break;
    case WStype_BIN:
      Serial.println("Received binary data.");
      break;
  }
}
