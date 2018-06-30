#include <WiFiEsp.h>
#include <WiFiEspUdp.h>
#include "SoftwareSerial.h"


SoftwareSerial ESP8266(6, 7); // RX, TX
WiFiEspUDP UDP;

const int left_door_pin = 2;
const int right_door_pin = 3;
const int LDR_pin = A0;

String stats_message;
char stat_packet[28];

String left_door_name = "ldoor:";
String right_door_name = "rdoor:";
String door_type = "|g";

String LDR_name = "ldr:";  // Light Dependent Resistor
String LDR_type = "|g";

String new_line = "\n";

char ssid[] = "somessid";
char password[] = "somepass";
int radio_status = WL_IDLE_STATUS;
unsigned int listen_port = 10002;  // might not need this
char stats_server_ip[] = "192.168.1.150";
int stats_server_port = 1060;


void setup() {
    pinMode(left_door_pin, INPUT);
    pinMode(right_door_pin, INPUT);
    pinMode(LDR_pin, INPUT);

    Serial.begin(115200);  // Debug
    ESP8266.begin(9600);
    WiFi.init(&ESP8266);

    if (WiFi.status() == WL_NO_SHIELD) {
        Serial.println("WiFi shield not present");
        // don't continue:
        while (true);
    }

    while (radio_status != WL_CONNECTED) {
        Serial.print("Attempting to connect to WPA SSID: ");
        Serial.println(ssid);
        // Connect to WPA/WPA2 network
        radio_status = WiFi.begin(ssid, password);
    }

    Serial.println("Connected to wifi");
    printWifiStatus();

    Serial.println("\nStarting UDP module");
    UDP.begin(listen_port);
}

void loop() {

    Serial.print("Left door is: ");
    Serial.println(digitalRead(left_door_pin));

    Serial.print("Right door is: ");
    Serial.println(digitalRead(right_door_pin));

    stats_message = left_door_name + digitalRead(left_door_pin);
    stats_message += door_type + new_line;
    stats_message += right_door_name + digitalRead(right_door_pin);
    stats_message += door_type + new_line;
    stats_message += LDR_name;

    if (analogRead(LDR_pin) > 500) {
        stats_message += 1;
    } else {
        stats_message += 0;
    }

    stats_message += LDR_type;

    Serial.println("Sending packet");
    stats_message.toCharArray(stat_packet, 28);

    UDP.beginPacket(stats_server_ip, stats_server_port);
    UDP.write(stat_packet);
    UDP.endPacket();

    Serial.println("Sleeping for 10");
    delay(10000);
}

void printWifiStatus() {
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());

    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);

    long rssi = WiFi.RSSI();
    Serial.print("signal strength (RSSI):");
    Serial.print(rssi);
    Serial.println(" dBm");
}