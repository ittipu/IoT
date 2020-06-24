#include<ESP8266WiFi.h>
WiFiClient WIFI_CLIENT;



#include <PubSubClient.h>
PubSubClient MQTT_CLIENT;


#define sensor A0

void setup(){
  Serial.begin(115200);
  pinMode(sensor,INPUT);

  WiFi.begin("Tipu","tipu1234");
  while(WiFi.status()!=WL_CONNECTED){
    delay(500);
  }
  Serial.println("IP Address: ");
  Serial.println(WiFi.localIP());

  
}

void reconnect(){
  MQTT_CLIENT.setServer("192.168.0.103",1883);
  MQTT_CLIENT.setClient(WIFI_CLIENT);
  while(!MQTT_CLIENT.connected()){
    Serial.println("Attempt to connect to MQTT broker");
    MQTT_CLIENT.connect("tipu");
    delay(3000);
  }
  Serial.println("MQTT connected");
}

void loop(){
  if(!MQTT_CLIENT.connected()){
    reconnect();
  }
  int value=analogRead(sensor);
  MQTT_CLIENT.publish("tipu/GassSensor",String(value).c_str());
  delay(1000);
}
