#include <WiFi.h>
#include <ThingSpeak.h>
#include "DHTesp.h"
DHTesp dhtSensor;
TempAndHumidity data;
const int DHT_PIN = 15; //always use 15
char ssid[] = "Wokwi-GUEST";
char pass[] = "";
WiFiClient client;
unsigned long myChannelNumber = 2563486;
const char * myWriteAPIKey = "F1CCP406A87S49M5";
int statusCode;
void setup() {
Serial.begin(115200);
WiFi.mode(WIFI_STA);
ThingSpeak.begin(client);
dhtSensor.setup(DHT_PIN, DHTesp::DHT22);
}
void loop() {
data = dhtSensor.getTempAndHumidity();
if(WiFi.status() != WL_CONNECTED)
{
Serial.print("Attempting to connect");
while(WiFi.status() != WL_CONNECTED)
{
WiFi.begin(ssid, pass); // Connect to WPA/WPA2 network. Change
//this line if using open or WEP network
Serial.print(".");
delay(5000);
}
Serial.println("\nConnected.");
}
Serial.println("Humi: " + String(data.humidity, 1));
Serial.println("Temp: " + String(data.temperature, 2));
Serial.println("-----------");
ThingSpeak.setField(1, data.humidity);
ThingSpeak.setField(2, data.temperature);
statusCode = ThingSpeak.writeFields(myChannelNumber,myWriteAPIKey);
if(statusCode == 200) { //successful writing code
Serial.println("Channel update successful.");
}
else {
Serial.println("Problem Writing data. HTTP error code :" +
String(statusCode));
}
delay(15000); // data to be uploaded every 15secs
}
