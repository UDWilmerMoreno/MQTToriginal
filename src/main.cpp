#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#define Rojo 16
#define Verde 5
#define Azul 4

const char *NombreDeRedWIFI = "familiamoreno";
const char *ClaveDeRedWIFI = "31502218";
const char *ServidorMQTT = "soldier.cloudmqtt.com";
const int PuertoDelServidorMQTT = 16409;
const char *Usuario = "ControlDeLuces";
const char *Contrasena = "0123456789";
const char *Topic = "Luces";
int Retardo = 2000;
char DatoMQTT;
int Caso;

WiFiClient espClient;
PubSubClient client(espClient);

void ColorNegro()
{
  digitalWrite(Rojo, LOW);
  digitalWrite(Verde, LOW);
  digitalWrite(Azul, LOW);
}
void ColorAzul()
{
  digitalWrite(Rojo, LOW);
  digitalWrite(Verde, LOW);
  digitalWrite(Azul, HIGH);
}
void ColorAguaMarina()
{
  digitalWrite(Rojo, LOW);
  digitalWrite(Verde, HIGH);
  digitalWrite(Azul, HIGH);
}
void ColorVerde()
{
  digitalWrite(Rojo, LOW);
  digitalWrite(Verde, HIGH);
  digitalWrite(Azul, LOW);
}
void ColorAmarillo()
{
  digitalWrite(Rojo, HIGH);
  digitalWrite(Verde, HIGH);
  digitalWrite(Azul, LOW);
}
void ColorRojo()
{
  digitalWrite(Rojo, HIGH);
  digitalWrite(Verde, LOW);
  digitalWrite(Azul, LOW);
}
void ColorMorado()
{
  digitalWrite(Rojo, HIGH);
  digitalWrite(Verde, LOW);
  digitalWrite(Azul, HIGH);
}
void ColorBlanco()
{
  digitalWrite(Rojo, HIGH);
  digitalWrite(Verde, HIGH);
  digitalWrite(Azul, HIGH);
}

void ConexionWifi()
{
  delay(10);
  Serial.println("");
  Serial.println("");
  Serial.print("Conectando a red Wifi...");
  WiFi.begin(NombreDeRedWIFI, ClaveDeRedWIFI);
  
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Dispositivo con conexión a internet");
}

void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Mensaje Recibido: [");
  Serial.print(topic);
  Serial.print("] ");

  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }

  Serial.println();
  DatoMQTT = payload[0];

  switch (DatoMQTT)
  {
  case '0':
    Caso = 0;
    break;
  case '1':
    Caso = 1;
    break;
  case '2':
    Caso = 2;
    break;
  case '3':
    Caso = 3;
    break;
  case '4':
    Caso = 4;
    break;
  case '5':
    Caso = 5;
    break;
  case '6':
    Caso = 6;
    break;
  case '7':
    Caso = 7;
    break;
  case 'q':
    Caso = 8;
    break;
  case 'w':
    Caso = 9;
    break;
  case 'e':
    Caso = 10;
    break;
  case 'r':
    Caso = 11;
    break;
  case 't':
    Caso = 12;
    break;
  case 'y':
    Caso = 13;
    break;
  case 'u':
    Caso = 14;
    break;
  case 'i':
    Caso = 15;
    break;
  default:
    Serial.println("Caracter no reconocido");
    break;
  }
}

void ConexionServidorMQTT()
{
  Serial.println("");
  Serial.print("Conectando al servidor MQTT...");
  while (!client.connected())
  {
    if (client.connect("", Usuario, Contrasena))
    {
      Serial.println("");
      Serial.println("Conexión exitosa al servidor MQTT");
      client.subscribe(Topic);
    }
    else
    {
      Serial.print(".");
      delay(5000);
    }
  }
}

void setup()
{
  pinMode(Rojo, OUTPUT);
  pinMode(Verde, OUTPUT);
  pinMode(Azul, OUTPUT);
  Serial.begin(115200);
  ConexionWifi();
  client.setServer(ServidorMQTT, PuertoDelServidorMQTT);
  client.setCallback(callback);
}

void loop()
{
  if (!client.connected())
  {
    ConexionServidorMQTT();
  }

  switch (Caso)
  {
  case 0:
    ColorNegro();
    delay(Retardo);
    Caso = 1;
    break;
  case 1:
    ColorAzul();
    delay(Retardo);
    Caso = 2;
    break;
  case 2:
    ColorAguaMarina();
    delay(Retardo);
    Caso = 3;
    break;
  case 3:
    ColorVerde();
    delay(Retardo);
    Caso = 4;
    break;
  case 4:
    ColorAmarillo();
    delay(Retardo);
    Caso = 5;
    break;
  case 5:
    ColorRojo();
    delay(Retardo);
    Caso = 6;
    break;
  case 6:
    ColorMorado();
    delay(Retardo);
    Caso = 7;
    break;
  case 7:
    ColorBlanco();
    delay(Retardo);
    Caso = 0;
    break;
  case 8:
    ColorNegro();
    break;
  case 9:
    ColorAzul();
    break;
  case 10:
    ColorAguaMarina();
    break;
  case 11:
    ColorVerde();
    break;
  case 12:
    ColorAmarillo();
    break;
  case 13:
    ColorRojo();
    break;
  case 14:
    ColorMorado();
    break;
  case 15:
    ColorBlanco();
    break;
  default:
    ColorNegro();
    Serial.println("No hay Caso");
    delay(Retardo);
    break;
  }
  
  client.loop();
}