#include <WiFi.h>
#include "ELMduino.h"


const char* ssid = "WiFi_OBDII";
const char* password = "your-password";


//IP Adress of your ELM327 Dongle
IPAddress server(192, 168, 0, 10);
WiFiClient client;
ELM327 myELM327;


uint32_t rpm = 0;


void setup()
{
  Serial.begin(115200);

  // Connecting to ELM327 WiFi
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid);
  // WiFi.begin(ssid, password); //Use this line if your ELM327 has a password protected WiFi

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Connected to Wifi");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  if (client.connect(server, 35000))
    Serial.println("connected");
  else
  {
    Serial.println("connection failed");
    while(1);
  }

  myELM327.begin(client);
}


void loop()
{
  float tempRPM = myELM327.rpm();

  if (myELM327.status == ELM_SUCCESS)
  {
    rpm = (uint32_t)tempRPM;
    Serial.print("RPM: "); Serial.println(rpm);
  }
  else
  {
    Serial.print(F("\tERROR: "));
    Serial.println(myELM327.status);
    delay(100);
  }
}