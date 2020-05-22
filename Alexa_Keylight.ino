#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Espalexa.h>

// Keylight settings
const String keylight_ip = "192.168.1.xxx";
const uint16_t keylight_port = 9123;
const uint8_t keylight_number_of_lights = 1;

// Wi-Fi settings
const char* wifi_ssid = "YOUR_SSID_HERE";
const char* wifi_password = "YOUR_PASSWORD_HERE";

Espalexa espalexa;
EspalexaDevice* elgatoKeylight;

HTTPClient http;

String url;

void setup() {
  Serial.begin(115200);
  while(!connectWifi()) {
    Serial.println("Retrying in 5 seconds...");
    delay(5000);
  }

  elgatoKeylight = new EspalexaDevice("Elgato Keylight", keyligtCallback);

  espalexa.addDevice(elgatoKeylight);

  espalexa.begin();
  url = "http://" + keylight_ip + ":" + keylight_port + "/elgato/lights";
}

String command = "";
void loop() {
  if(WiFi.status() != WL_CONNECTED) {
    Serial.println("Wi-Fi got disconnected!");
    while(!connectWifi()) {
      Serial.println("Retrying in 5 seconds...");
      delay(5000);
    }
  }
  
  espalexa.loop();

  if(command != "") {
    if(!http.begin(url)) {
      Serial.println("Couldn't connect to Elgato Keylight");
      return;  
    }
  
    http.addHeader("Content-Type", "application/json");
    Serial.println(url + " - " + http.PUT(command));
    Serial.println("Response: " + http.getString());
    http.end();
    
    Serial.println(command);
    command = "";
  }
  delay(1);
}

void keyligtCallback(uint8_t brightness) {
  String setting = "";

  String to_add = "";
  if(brightness == 0) {
    to_add = "{\"on\": 0}";
  } else {
    to_add = "{\"on\": 1, \"brightness\":" + String(map(brightness, 0, 255, 0, 100)) + "}";
  }
    
  for(int i = 0; i < keylight_number_of_lights; i++) {
    if(i != 0) {
      setting += ",";
    }
    
    setting = setting + to_add;
  }
  
  command = "{\"lights\":[" + setting + "],\"numberOfLights\":" + keylight_number_of_lights + "}";
}

boolean connectWifi(){
  WiFi.mode(WIFI_STA);
  WiFi.begin(wifi_ssid, wifi_password);

  // Wait for connection
  Serial.println("Connecting...");
  
  for(int i = 0; i < 20; i++) {
    if(WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(500);
    }
  }
  
  Serial.println("");
  
  if (WiFi.status() == WL_CONNECTED){
    Serial.print("Connected to ");
    Serial.println(wifi_ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    return true;
  }
  
  Serial.println("Connection failed");
  return false;
}
