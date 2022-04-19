#include "WifiCredentials.h"
#include <WiFi.h>
#include <LiquidCrystal_I2C.h>
#include <WebServer.h>

const int SERIAL_SPEED = 115200;
const int lcdColumns = 16;
const int lcdRows = 2;

IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);
WebServer server(80);


void setupLcd() {
  lcd.init();
  lcd.backlight();
}

void setupWifi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    lcd.setCursor(0, 0);
    lcd.print("Connecting to WiFi:");
    lcd.setCursor(0, 1);
    lcd.print(WIFI_SSID);
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Connected to the WiFi network");
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP());
}

void setupServer() {
  server.on("/", handle_OnConnect);
  server.on("/notification", handle_notification);
  server.onNotFound(handle_NotFound);
  server.begin();
}

void handle_OnConnect() {
  server.send(200, "text/html", "hello from ESP32");
}

void handle_notification() {

}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

void setup() {
  setupLcd();
  setupWifi();
  setupServer();
}

void loop() {
  server.handleClient();
}
