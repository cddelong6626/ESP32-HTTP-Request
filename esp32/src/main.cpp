#include <Arduino.h>
#include <WiFi.h>

const char* ssid = ""; // WiFi SSID
const char* password = ""; // WiFi password

const char* host =  "172.20.10.3";
const uint16_t port = 5000;

void setup() 
{
  // initialize serial comms
  Serial.begin(9600);
  while (!Serial) {delay(100);} {}

  // initialize WiFi
  Serial.println("\nInitializing WiFi...");
  WiFi.mode(WIFI_STA);
  WiFi.begin();
  Serial.println("WiFi initialized.");

  // connect to hotspot
  Serial.print("Connecting to ");
  Serial.print(ssid);
  Serial.println("...");

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {}

  Serial.println("WiFi connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // connect to the server
  Serial.print("Connecting to host: ");
  Serial.print(host);
  Serial.print(":");
  Serial.print(port);
  Serial.println("...");

  WiFiClient client;
  while (!client.connect(host, port)) {}
  Serial.println("Client connected.");

  // Make GET request  
  String request = "GET / HTTP/1.1\r\nHost: 172.20.10.3\r\nAccept: */*\r\n\r\n";
  Serial.println("\nMaking request:\n");
  Serial.println(request);

  client.print(request);

  // wait until GET request is responded to
  Serial.println("Response:\n");
  unsigned long timeout = millis();
  while(client.available() == 0) {}

  // read the response of server and print it to serial
  while(client.available()) 
  {
    String line = client.readString();
    Serial.print(line);
  }

  // close connection
  Serial.println("\nDisconnecting from server.");
  client.stop();
}

void loop() {}
