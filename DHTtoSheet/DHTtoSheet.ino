#include "ESP8266WiFi.h"
#include "DHT.h"
#define DHTPIN D4    // what digital pin we're connected to
#define DHTTYPE DHT22  // DHT 11

DHT dht(DHTPIN,DHTTYPE);


const char WEBSITE[] = "api.pushingbox.com";
const String devid = "v3903EF84D404A47"; 
const char* MY_SSID = "Cisco06394";
const char* MY_PWD =  "ontani209";


void setup()
{
  Serial.begin(115200);
  dht.begin();
  Serial.print("Connecting to "+*MY_SSID);
  WiFi.begin(MY_SSID, MY_PWD);
  Serial.println("going into wl connect");

  while (WiFi.status() != WL_CONNECTED) //not connected,..waiting to connect
    {
      delay(1000);
      Serial.print(".");
    }
  Serial.println("wl connected");
  Serial.println("");
  Serial.println("Credentials accepted! Connected to wifi\n ");
  Serial.println("");
}


void loop()
{
  delay(15000);

  float humidityData = dht.readHumidity();
  float celData = dht.readTemperature();
  float fehrData = dht.readTemperature(true);
  
  if (isnan(humidityData) || isnan(celData) || isnan(fehrData))
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  float hicData = dht.computeHeatIndex(celData, humidityData, false);
  Serial.print("Humidity: ");
  Serial.print(humidityData);
  Serial.print(" %\t");
  Serial.print("Temperature in Cel: ");
  Serial.print(celData);
  Serial.print(" *C ");
  Serial.println("");
    
  WiFiClient client; 
if (client.connect(WEBSITE, 80))
      { 
         client.print("GET /pushingbox?devid=" + devid
       + "&humidityData=" + (String) humidityData
       + "&celData="      + (String) celData
         );

      client.println(" HTTP/1.1"); 
      client.print("Host: ");
      client.println(WEBSITE);
      client.println("User-Agent: ESP8266/1.0");
      client.println("Connection: close");
      client.println();
      }
}
