#include <ESP8266WebServer.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <FirebaseArduino.h>

const int oneWireBus = 4;     
OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);
#define FIREBASE_HOST "https://velha-guarda.firebaseio.com/"
#define FIREBASE_AUTH "SB4ahzKIDOhbPgTtKp7PMQGH10r11"

float tempSensor1;

uint8_t sensor1[8] = { 0x28, 0xEE, 0xD5, 0x64, 0x1A, 0x16, 0x02, 0xEC  };
/*Put your SSID & Password*/
const char* ssid = "Net Virtua 67";  // Enter SSID here
const char* password = "3511598700";  //Enter Password here

ESP8266WebServer server(80);  

void setup() {
  // Start the Serial Monitor
  Serial.begin(115200);
  // Start the DS18B20 sensor
  sensors.begin();
  
  Serial.println("Connecting to ");
  Serial.println(ssid);

  //connect to your local wi-fi network
  WiFi.begin(ssid, password);

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());

  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
  sensors.requestTemperatures(); 
  float temperatureC = sensors.getTempCByIndex(0);
  Serial.print(temperatureC);
  Serial.println("ºC");
  delay(5000);
}

void handle_OnConnect() {
  sensors.requestTemperatures();
  tempSensor1 = sensors.getTempCByIndex(0); // Gets the values of the temperature
  server.send(200, "text/html", SendHTML(tempSensor1)); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String SendHTML(float tempSensor1){
  String ptr = "<!DOCTYPE html>";
  ptr +="<html>";
  ptr +="<head>";
  ptr +="<title>Monitor de temperatura</title>";
  ptr +="<meta charset='UTF-8'/>";
  ptr +="<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  ptr +="<link href='https://fonts.googleapis.com/css?family=Open+Sans:300,400,600' rel='stylesheet'>";
  ptr +="<link rel='icon' href='favicon.ico' type='image/x-icon'>";
  ptr +="<style>";
  ptr +="html { font-family: 'Open Sans', sans-serif; display: block; margin: 0px auto; text-align: center;color: #444444;}";
  ptr +="body{margin-top: 50px;} ";
  ptr +="h1 {margin: 50px auto 30px;} ";
  ptr +=".side-by-side{display: table-cell;vertical-align: middle;position: relative;}";
  ptr +=".text{font-weight: 600;font-size: 19px;width: 200px;}";
  ptr +=".temperature{font-weight: 300;font-size: 50px;padding-right: 15px;}";
  ptr +=".living-room .temperature{color: #F29C1F;}";
  ptr +=".superscript{font-size: 17px;font-weight: 600;position: absolute;right: -5px;top: 15px;}";
  ptr +=".data{padding: 10px;}";
  ptr +=".container{display: table;margin: 0 auto;}";
  ptr +=".icon{width:82px}";
  ptr +="</style>";
  ptr +="</head>";
  ptr +="<body>";
  ptr +="<h1>Monitor de temperatura</h1>";
  ptr +="<div class='container'>";
  ptr +="<div class='data living-room'>";
  ptr +="<div class='side-by-side icon'>";
  ptr +="<svg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 297 297'>";
  ptr +="<circle cx='148.5' cy='148.5' r='148.5' fill='#c63c22'/>";
  ptr +="<path d='M296.703 139.216l-96.66-96.678-104.931 199.82 54.626 54.626C231.181 296.318 297 230.1 297 148.5c0-3.119-.108-6.212-.297-9.284z' fill='#9e231d'/>";
  ptr +="<path d='M207.444 99.107c9.143 0 16.556-7.412 16.556-16.556s-7.412-16.556-16.556-16.556c-.233 0-.459.025-.689.035.446-1.863.689-3.805.689-5.805 0-13.715-11.118-24.833-24.833-24.833-8.456 0-15.919 4.23-20.404 10.685-2.92-2.582-6.747-4.163-10.951-4.163a16.462 16.462 0 00-9.793 3.228c-4.538-5.926-11.683-9.751-19.724-9.751-10.476 0-19.43 6.491-23.079 15.667a16.457 16.457 0 00-7.106-1.62C82.412 49.44 75 56.852 75 65.996s7.412 16.556 16.556 16.556l115.888 16.555z' fill='#fff'/>";
  ptr +="<path d='M207.444 65.996c-.233 0-.459.025-.689.035.446-1.863.689-3.805.689-5.804 0-13.715-11.118-24.833-24.833-24.833-8.455 0-15.919 4.23-20.404 10.685-2.92-2.583-6.747-4.163-10.951-4.163-.882 0-1.745.073-2.589.208V90.71l58.777 8.397c9.143 0 16.556-7.412 16.556-16.556s-7.412-16.555-16.556-16.555z' fill='#d0d5d9'/><path d='M238.282 115.5H206.25v-33H90.75v148.792c0 8.952 7.257 16.208 16.208 16.208h83.083c8.952 0 16.208-7.257 16.208-16.208V198h32.032a9.218 9.218 0 009.218-9.218v-64.064a9.216 9.216 0 00-9.217-9.218zm-2.429 61.532a6.718 6.718 0 01-6.718 6.718h-19.488v-54h19.488a6.718 6.718 0 016.718 6.718v40.564z' fill='#f0deb4'/>";
  ptr +="<path d='M238.282 115.5H206.25v-33h-57.583v165h41.375c8.952 0 16.208-7.257 16.208-16.208V198h32.032a9.218 9.218 0 009.218-9.218v-64.064a9.218 9.218 0 00-9.218-9.218zm-2.429 61.532a6.718 6.718 0 01-6.718 6.718h-19.488v-54h19.488a6.718 6.718 0 016.718 6.718v40.564z' fill='#d8c49c'/><path d='M111.814 237.857h73.372c7.905 0 14.314-6.409 14.314-14.314v-92.4h-102v92.4c0 7.906 6.409 14.314 14.314 14.314z' fill='#ffa800'/>";
  ptr +="<path d='M148.667 131.143v106.714h36.519c7.905 0 14.314-6.409 14.314-14.314v-92.4h-50.833z' fill='#c63c22'/></svg>";
  ptr +="</div>";
  ptr +="<div class='side-by-side text'>Rampas de temperatura</div>";
  ptr +="<div class='side-by-side temperature'>";
  ptr +=(int)tempSensor1;
  ptr += "<meta http-equiv='refresh' content='2'>";
  ptr +="<span class='superscript'>&deg;C</span></div>";
  ptr +="</div>";
  ptr +="</div>";
  ptr +="</body>";
  ptr +="</html>";
  return ptr;
}
