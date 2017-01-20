#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

const char* ssid     =  "amp-modular-1";
const char* password =  "";

const char* host = "192.168.0.101";


void setup() {
  Serial.begin(115200);
  Serial.println();

  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid,password);
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");

  Serial.printf("Client started, IP is %s \n", WiFi.localIP().toString().c_str());
}

void loop() {
  delay(5000);

  Serial.print("connecting to ");
  Serial.println(host);

  //Use WiFiClient clalss to create TCP connections

  WiFiClient client;
  const int port = 8266;
  if(!client.connect(host,port)){
    Serial.println("connection failed");
    return;
  }
  String json;
  while(client.available()){
   json = client.readStringUntil('\n');
   Serial.println(json);
  }

  Serial.println("closing connection");
  client.stop();
  
  Serial.println(json);
  
}
