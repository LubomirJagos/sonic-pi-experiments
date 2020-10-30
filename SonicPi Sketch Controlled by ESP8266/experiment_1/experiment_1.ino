/***************************************************
This is a library for the Si1145 UV/IR/Visible Light Sensor

Designed specifically to work with the Si1145 sensor in the
adafruit shop
----> https://www.adafruit.com/products/1777 2

These sensors use I2C to communicate, 2 pins are required to
interface
Adafruit invests time and resources providing this open source code,
please support Adafruit and open-source hardware by purchasing
products from Adafruit!

Written by Limor Fried/Ladyada for Adafruit Industries.
BSD license, all text above must be included in any redistribution
****************************************************/
#if defined(ESP8266)
  #include <ESP8266WiFi.h>
#else
  #include <WiFi.h>
#endif
#include <WiFiUdp.h>
#include <OSCMessage.h>
#include <Wire.h>

char ssid[] = "____________"; // your network SSID (name)
char pass[] = "____________"; // your network password

WiFiUDP Udp; // A UDP instance to let us send and receive packets over UDP
const IPAddress outIp(192,168,0,113); // remote IP of your computer
const unsigned int outPort = 4560; // remote port to receive OSC
const unsigned int localPort = 8888; // local port to listen for OSC packets (actually not used for sending)


void setup() {
  Serial.begin(115200);
  
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println("");
  
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  Serial.println("Starting UDP");
  Udp.begin(localPort);
  Serial.print("Local port: ");

  #ifdef ESP32
    Serial.println(localPort);
  #else
    Serial.println(Udp.localPort());
  #endif
  
  Serial.println("OK!");
}

void loop() {
  String A = String(random(30,100));
  String B = String(random(70,120));
  String C = String(random(90,250));
  String msgStr = A + "," + B + "," + C;
  Serial.println(msgStr);

  unsigned int strArrayLength = msgStr.length() + 1;
  char msgArray[strArrayLength];
  msgStr.toCharArray(msgArray, strArrayLength);   // <--- CONVERT String into char[]

//  Serial.println("142");

  OSCMessage msg("/trigger/prophet");
  msg.add(msgArray);                   // <--- THIS IS IMPORTANT, NEED TO BE CHAR ARRAY, no String!!!
  //msg.add("120,130,150");
  //msg.add("142");
  Udp.beginPacket(outIp, outPort);
  msg.send(Udp);
  Udp.endPacket();
  msg.empty();
  delay(1000);
}
