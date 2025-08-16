#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#define ESPALEXA_DEBUG
#include <Espalexa.h>

// WiFi credentials - CHANGE THESE
const char* ssid = "slow";
const char* password = "surfacepro";

// Device settings
String deviceName = "LED Lights"; // This is what you'll say to Alexa
int ledPin = D1; // PWM pin for MOSFET gate

// Espalexa instance
Espalexa espalexa;

// Custom web server for manual control
ESP8266WebServer controlServer(8080);

void setup() {
  Serial.begin(115200);
  delay(1000); // Give serial time to initialize
  
  Serial.println("\n=== D1 Mini Alexa LED Controller ===");
  Serial.println("Starting up...");
  
  // Initialize LED pin and built-in LED
  pinMode(ledPin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  analogWrite(ledPin, 0); // Start with lights off
  digitalWrite(LED_BUILTIN, HIGH); // Turn off built-in LED (HIGH = off on D1 Mini)
  Serial.println("LED pin initialized");
  
  // Connect to WiFi
  Serial.println("Attempting WiFi connection...");
  Serial.print("SSID: ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  Serial.print("Connecting");
  
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 30) {
    delay(500);
    Serial.print(".");
    attempts++;
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n*** WiFi Connected Successfully! ***");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    Serial.print("Network: ");
    Serial.println(WiFi.SSID());
    Serial.print("Signal Strength: ");
    Serial.print(WiFi.RSSI());
    Serial.println(" dBm");
  } else {
    Serial.println("\n*** WiFi Connection FAILED! ***");
    Serial.println("Check your SSID and password");
    return; // Don't continue if no WiFi
  }
  
  // Setup custom web server for manual control
  setupControlServer();
  
  // Add device to Espalexa
  Serial.println("Setting up Alexa device...");
  Serial.print("Device name: '");
  Serial.print(deviceName);
  Serial.println("'");
  
  // Add device - simple version that works with this library version
  espalexa.addDevice(deviceName, ledControl);
  espalexa.begin();
  
  Serial.println("*** Setup Complete! ***");
  Serial.println("Say 'Alexa, discover devices'");
  Serial.print("Espalexa Status: http://");
  Serial.print(WiFi.localIP());
  Serial.println("/espalexa");
  Serial.print("Manual Control: http://");
  Serial.print(WiFi.localIP());
  Serial.println(":8080");
}

void setupControlServer() {
  // Main control page
  controlServer.on("/", HTTP_GET, [](){
    String html = "<!DOCTYPE HTML><html><head><title>LED Strip Controller</title>";
    html += "<style>body{font-family:Arial; text-align:center; margin:50px;}";
    html += "button{font-size:24px; padding:15px 30px; margin:10px; border:none; border-radius:5px; cursor:pointer;}";
    html += ".on{background:#4CAF50; color:white;} .off{background:#f44336; color:white;}";
    html += ".dim{background:#2196F3; color:white;}</style></head><body>";
    html += "<h1>48V LED Strip Controller</h1>";
    html += "<h2>Manual Control Panel</h2>";
    html += "<p><a href='/on'><button class='on'>TURN ON (100%)</button></a></p>";
    html += "<p><a href='/off'><button class='off'>TURN OFF</button></a></p>";
    html += "<h3>Dimming Controls</h3>";
    html += "<p><a href='/dim25'><button class='dim'>25%</button></a> ";
    html += "<a href='/dim50'><button class='dim'>50%</button></a> ";
    html += "<a href='/dim75'><button class='dim'>75%</button></a></p>";
    
    // Show current status
    EspalexaDevice* device = espalexa.getDevice(0);
    if (device) {
      html += "<hr><h3>Current Status</h3>";
      html += "<p><strong>Brightness:</strong> " + String(device->getValue()) + "/255 (" + String(device->getPercent()) + "%)</p>";
    }
    
    html += "<hr><p><small>Refresh page to update status</small></p>";
    html += "</body></html>";
    
    controlServer.send(200, "text/html", html);
  });
  
  // Control endpoints
  controlServer.on("/on", HTTP_GET, [](){
    ledControl(255);
    Serial.println("Web: LED ON");
    controlServer.sendHeader("Location", "/");
    controlServer.send(302, "text/plain", "");
  });
  
  controlServer.on("/off", HTTP_GET, [](){
    ledControl(0);
    Serial.println("Web: LED OFF");
    controlServer.sendHeader("Location", "/");
    controlServer.send(302, "text/plain", "");
  });
  
  controlServer.on("/dim25", HTTP_GET, [](){
    ledControl(64);
    Serial.println("Web: LED 25%");
    controlServer.sendHeader("Location", "/");
    controlServer.send(302, "text/plain", "");
  });
  
  controlServer.on("/dim50", HTTP_GET, [](){
    ledControl(128);
    Serial.println("Web: LED 50%");
    controlServer.sendHeader("Location", "/");
    controlServer.send(302, "text/plain", "");
  });
  
  controlServer.on("/dim75", HTTP_GET, [](){
    ledControl(192);
    Serial.println("Web: LED 75%");
    controlServer.sendHeader("Location", "/");
    controlServer.send(302, "text/plain", "");
  });
  
  controlServer.begin();
  Serial.println("Control server started on port 8080");
}

void loop() {
  espalexa.loop();
  controlServer.handleClient();
  
  // Check for serial commands to test LED manually
  if (Serial.available()) {
    String command = Serial.readString();
    command.trim();
    
    if (command == "1" || command == "on") {
      Serial.println("Manual LED ON command");
      ledControl(255);
    } else if (command == "0" || command == "off") {
      Serial.println("Manual LED OFF command");
      ledControl(0);
    } else if (command.startsWith("dim")) {
      int brightness = command.substring(3).toInt();
      Serial.print("Manual LED DIM command: ");
      Serial.println(brightness);
      ledControl(brightness);
    } else if (command == "test") {
      Serial.println("Testing LED sequence...");
      ledControl(255); delay(1000);
      ledControl(128); delay(1000); 
      ledControl(0);   delay(1000);
    } else {
      Serial.println("Commands: 1/on, 0/off, dim128, test");
    }
  }
  
  // Add a heartbeat every 10 seconds
  static unsigned long lastHeartbeat = 0;
  if (millis() - lastHeartbeat > 10000) {
    Serial.print("Heartbeat - Uptime: ");
    Serial.print(millis() / 1000);
    Serial.println(" seconds");
    lastHeartbeat = millis();
  }
}

// Callback function when Alexa sends commands
void ledControl(uint8_t brightness) {
  Serial.println("=== LED Control Function Called ===");
  Serial.print("LED brightness set to: ");
  Serial.print(brightness);
  Serial.print(" (");
  Serial.print((brightness * 100) / 255);
  Serial.println("%)");
  
  // Flash the onboard LED to show command received
  digitalWrite(LED_BUILTIN, LOW);  // Turn on built-in LED
  delay(50);
  digitalWrite(LED_BUILTIN, HIGH); // Turn off built-in LED
  
  // Write PWM value (0-255 range)
  analogWrite(ledPin, brightness);
  
  // Update the Espalexa device state
  if (espalexa.getDevice(0)) {
    espalexa.getDevice(0)->setValue(brightness);
  }
  
  if (brightness > 0) {
    Serial.println("LED turned ON/DIM");
  } else {
    Serial.println("LED turned OFF");
  }
}