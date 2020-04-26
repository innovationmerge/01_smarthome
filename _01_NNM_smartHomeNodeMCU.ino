#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
 
// Replace with your network credentials
const char* ssid = "iNNovationMerge";
const char* password = "123456789";
 
ESP8266WebServer server(8082);   //instantiate server at port 8082 (http port)
 
String page = "";
int FANPin = D0;

void setup(void){
  //the HTML of the web page
  page = "<h1>iNNovationMerge <br> Home Automation using IoT</h1>\
  <p>FAN:&nbsp;<a href=\"FANOn\"><button>ON</button></a>&nbsp;<a href=\"FANOff\"><button>OFF</button></a></p>";
  //make the LED pin output and initially turned off
  pinMode(FANPin, OUTPUT);
  digitalWrite(FANPin, LOW);
  delay(1000);
  Serial.begin(115200);
  
  WiFi.softAP(ssid, password); //begin WiFi access point
  Serial.println("");;
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP()); 

  //Render Page with buttons once the URL is given 
  server.on("/", [](){
    server.send(200, "text/html", page);
  });.
  
  //Url to turn ON LED - Given as href to ON button
 server.on("/FANOn", [](){
  server.send(200, "text/html", page);
  digitalWrite(FANPin, LOW);
  delay(1000);
  });
  
  //Url to turn OFF LED - Given as href to OFF button
  server.on("/FANOff", [](){
    server.send(200, "text/html", page);
    digitalWrite(FANPin, HIGH);
    delay(1000); 
  });

  //Start the server 
  server.begin();
  Serial.println("Web server started!");
}
 
void loop(void){
  server.handleClient();
}
