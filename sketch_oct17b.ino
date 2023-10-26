/*
 *sketch para ESP32 que publica os dados de dois sensores de distância ultrassônicos para o Adafruit IO.
 */

#include <WiFi.h> //Biblioteca para se conectar a redes Wi-Fi
#include <WiFiClient.h> // Biblioteca para se comunicar com dispositivos TCP/UDP conectados a uma rede Wi-Fi
#include <PubSubClient.h> // Biblioteca para se comunicar com um broker MQTT


WiFiClient wifi_client;
PubSubClient mqtt_client(wifi_client);

const int trigPinS1 = 13; //pino digital que está conectado ao pino de gatilho do primeiro sensor de distância
const int echoPinS1 = 12; //pino digital que está conectado ao pino de eco do primeiro sensor de distância
const int trigPinS2 = 14; //pino digital que está conectado ao pino de gatilho do segundo sensor de distância
const int echoPinS2 = 27; //pino digital que está conectado ao pino de eco do segundo sensor de distância
#define SOUND_SPEED 0.034 //velocidade do som em metros por segundo


long duracaoS1; //duração do pulso em microssegundos emitido pelo primeiro sensor de distância
float distanciaCmS1; // distância em centímetros medida pelo primeiro sensor de distância
long duracaoS2;  //duração do pulso em microssegundos emitido pelo segundo sensor de distância
float distanciaCmS2; //distância em centímetros medida pelo segundo sensor de distância

const char* wifi_ssid = "XXXXXXXXX"; // SSID da sua rede Wi-Fi
const char* wifi_password = "XXXXXXXXXXX";  // Senha da sua rede Wi-Fi


const char* mqtt_broker = "io.adafruit.com"; //endereço do broker MQTT ao qual o ESP32 deve se conectar
const int mqtt_port = 1883; //porta na qual o broker MQTT está escutando
const char* mqtt_usernameAdafruitIO = "XXXXXXXXXX"; // usuário do Adafruit IO
const char* mqtt_keyAdafruitIO = "XXXXXXXXXXXXXX"; // chave de API do Adafruit IO

//chamada quando o ESP32 é iniciado. 
//Esta função configura os pinos digitais como pinos de saída e entrada, conecta-se à rede Wi-Fi e ao broker MQTT.
void setup() {
  pinMode(trigPinS1, OUTPUT);
  pinMode(echoPinS1, INPUT);
  pinMode(trigPinS2, OUTPUT);
  pinMode(echoPinS2, INPUT);
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(wifi_ssid, wifi_password);
  connectWiFi();
  mqtt_client.setServer(mqtt_broker, mqtt_port);
}


/*chamada repetidamente pelo ESP32. Esta função mede a distância com os dois sensores de distância, publica os dados dos 
 * sensores para o Adafruit IO e aguarda 10 segundos antes de repetir o ciclo.
*/
void loop() {
  if (!mqtt_client.connected()) {
    connectMQTT();
  }

  if (mqtt_client.connected()) {
    // Medir distância com sensor S1
    digitalWrite(trigPinS1, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPinS1, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinS1, LOW);
    duracaoS1 = pulseIn(echoPinS1, HIGH);
    distanciaCmS1 = duracaoS1 * SOUND_SPEED / 2;

    // Medir distância com sensor S2
    digitalWrite(trigPinS2, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPinS2, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinS2, LOW);
    duracaoS2 = pulseIn(echoPinS2, HIGH);
    distanciaCmS2 = duracaoS2 * SOUND_SPEED / 2;

    // Enviar leituras ao Adafruit IO
    mqtt_client.publish("alinnealess/feeds/sensorS1", String(distanciaCmS1).c_str());
    mqtt_client.publish("alinnealess/feeds/sensorS2", String(distanciaCmS2).c_str());


    mqtt_client.loop();
  }

  delay(10000); // Atraso entre as medições
}

  // Verificar a conexão com a Internet e atualizar o status do LED
  if (WiFi.status() == WL_CONNECTED) {
    digitalWrite(statusLedPin, HIGH); // Ligado quando conectado
  } else {
    digitalWrite(statusLedPin, LOW); // Desligado quando não conectado
  }
}

 // Conexão à rede Wi-Fi
void connectWiFi() {
  Serial.print("Conectando à rede WiFi .. ");
  unsigned long tempoInicial = millis();
  while (WiFi.status() != WL_CONNECTED && (millis() - tempoInicial < 10000)) {
    Serial.print(".");
    delay(100);
  }
  Serial.println();

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Conexão com WiFi falhou!");
  } else {
    Serial.print("Conectado com o IP: ");
    Serial.println(WiFi.localIP());
  }
}

// Conexão ao servidor MQTT
void connectMQTT() {
  unsigned long tempoInicial = millis();
  while (!mqtt_client.connected() && (millis() - tempoInicial < 10000)) {
    if (WiFi.status() != WL_CONNECTED) {
      connectWiFi();
    }
    Serial.print("Conectando ao MQTT Broker..");

    if (mqtt_client.connect("ESP32Client", mqtt_usernameAdafruitIO, mqtt_keyAdafruitIO)) {
      Serial.println();
      Serial.print("Conectado ao broker MQTT!");
    } else {
      Serial.println();
      Serial.print("Conexão com o broker MQTT falhou!");
      delay(500);
    }
  }
  Serial.println();
}
