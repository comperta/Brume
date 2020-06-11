void callback(char* topic, byte* payload, unsigned int length) {
  if (strcmp(topic, BRUME_TOPIC) == 0) {
    digitalWrite(BRUME, LOW);
    delay(3000);
    digitalWrite(BRUME, HIGH);
    delay(3000);
  }
  if (strcmp(topic, LED_TOPIC) == 0) {
    digitalWrite(BRUME, LOW);
    delay(3000);
    digitalWrite(BRUME, HIGH);
    delay(3000);
  }
}




void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    #ifdef DEBUG
      Serial.print("Attempting MQTT connection...");
    #endif
    // Attempt to connect
    if (client.connect("ESP8266Client", mqtt_username, mqtt_password)) {
      #ifdef DEBUG
        Serial.println("");
        Serial.println("connected");
      #endif
      client.publish(AVAILABILITY_TOPIC, "online");         // Once connected, publish online to the availability topic
      client.subscribe(TARE_TOPIC);       //Subscribe to tare topic for remote tare
      client.subscribe(CALIBRATION_TOPIC);       //Subscribe to Calibration topic for remote tare
      client.subscribe(PAUSESTOP_TOPIC);                    //Subscribe to pausestop topic
      client.subscribe(EXITDOCK_TOPIC);                     //Subscribe to exit dock topic 
      client.subscribe(QUICKSTART_TOPIC);                   //Subscribe to quick start topic
      client.subscribe(GODOCK_TOPIC);                       //Subscribe to go to dock topic
    } else {
      #ifdef DEBUG
        Serial.print("failed, rc=");
        Serial.print(client.state());
        Serial.println(" try again in 5 seconds");
      #endif
      // Wait 5 seconds before retrying
      delay(connectionDelay);
    }
  }
}
void Clear_MQTT() {
  #ifdef DEBUG
    Serial.println("Clear MQTT");
  #endif
  client.publish(AVAILABILITY_TOPIC, "online");         // Once connected, publish online to the availability topic
  client.publish(MOVE_TOPIC, "off");                    // Mow LED
  client.publish(DOCKED_TOPIC, "off");                  // Dock LED Off
  client.publish(TRACKING_TOPIC, "off");                // Tracking LED OFF
  client.publish(PARKED_TOPIC, "off");                  // Parked LED OFF
  client.publish(CHARGING_TOPIC, "off");                // Charging LED OFF  
}