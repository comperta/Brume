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
      client.subscribe(BRUME_TOPIC);                        //Subscribe to BRUME topic 
      client.subscribe(LED_TOPIC);                          //Subscribe to LED topic 
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
  client.publish(BRUME_TOPIC, "off");                   // BRUME Off
  client.publish(LED_TOPIC, "off");                     // LED Off
}