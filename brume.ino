#include <ESP8266WiFi.h>
#include <PubSubClient.h> // for MQTT
#include "config.h" //Config file for credentials


//#define LED ESP

#define LED_ESP D4        // on various NODEMCU boards the LED Pin is different.....
#define LED D8            // Pin D8 for Relay 1
#define BRUME D7          // Pin D7 for Relay 2


///////////***********MQTT*************////////
WiFiClient espClient;
PubSubClient client(espClient);
///////////***********MQTT*************////////

int connectionDelay = 5000; // try to reconnect every 5 seconds
int etat_brume = 0;
int etat_led = 0;

void setup()
{

  #ifdef DEBUG
    Serial.begin(9600);
    Serial.println();
    Serial.println("debug mode on");
    Serial.println("Setting up NODEMCU........");
    Serial.println("");
  #endif
  digitalWrite(LED_ESP, HIGH);                          // Turn off LED_ESP Light
  WIFI_Connect();                                   // Connect to the WIFI
  pinMode(LED_ESP, OUTPUT);
  pinMode(BRUME, OUTPUT);
  pinMode(LED, OUTPUT);
  digitalWrite(BRUME, HIGH);
  digitalWrite(LED, HIGH);

}



//Functions
//***********************************


void WIFI_Connect() 
{
      // We start by connecting to a WiFi network
      #ifdef DEBUG
        Serial.println();
        Serial.print("Connecting to ");
        Serial.println(SSID);
      #endif
      WiFi.begin(SSID, PASSWORD);

      while (WiFi.status() != WL_CONNECTED) {
        delay(connectionDelay);
        #ifdef DEBUG
          Serial.printl(".");
        #endif
      }

      #ifdef DEBUG
        Serial.println("");
        Serial.println("WiFi connected");
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
      #endif
      client.setServer(MQTT_SERVER, 1883);                // Set MQTT server and port number
      client.setCallback(callback);
     
}

void loop()  {

    if (!client.connected()) {
         digitalWrite(LED_ESP, HIGH);
        #ifdef DEBUG
          Serial.println("------------------------");
          Serial.println("NODEMCU MQTT Disconnected");
          Serial.println("Reconnecting ... ");
        #endif
        reconnect();
        Clear_MQTT();
      }
    else {
      client.loop();
      digitalWrite(LED_ESP, LOW);         //LED_ESP is inverted on a MODEMCU...
      Update_MQTT_With_Status();
      }

}
