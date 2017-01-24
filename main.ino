/*
 * - - - - - - - - - - - - - - - - - - - - - - - - -
 * ESP 8266 IoT Client
 * modulariot.xyz
 *
 * Contacts an IoT server to receive state changes.
 * - - - - - - - - - - - - - - - - - - - - - - - - -
 */

#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

const char* wifi_ssid = "amp-modular-1";
const char* wifi_password = "";
const char* server_address = "192.168.0.103";

// perform one-time setup of the ESP on boot
void setup()
{
    pinMode(5, OUTPUT);
    Serial.begin(115200);
    Serial.printf("Connecting to SSID %s.", wifi_ssid);
    WiFi.begin(wifi_ssid, wifi_password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
    }

    Serial.println("Connected to network.");
    Serial.printf("Client ready. DHCP IP is %s \n.", WiFi.localIP().toString().c_str());
}

// execute this loop continuously
void loop() {

    delay(100);
    Serial.printf("Connecting to remote host %s.\n", server_address);
    WiFiClient client;
    const int server_port = 8266;

    if (!client.connect(server_address, server_port))
    {
        Serial.println("\nConnection to remote host failed.");
        return;
    }

    String payload;

    payload = client.readStringUntil('\n');
    Serial.println("Payload received.");
    Serial.print("payload=\n");
    Serial.println(payload);

    if (payload[1] == 'N')
    {
        digitalWrite(5, HIGH);
    }
    if (payload[1] == 'F')
    {
        digitalWrite(5, LOW);
    }

    Serial.println("Closing connection to remote host.");
    client.stop();
}
