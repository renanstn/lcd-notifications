#include "WifiCredentials.h"
#include <WiFi.h>
#include <LiquidCrystal_I2C.h>
#include <WebServer.h>

const int lcdColumns = 16;
const int lcdRows = 2;
String message = "";

LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);
WebServer server(80);
TaskHandle_t scrollTextHandle;


void setupLcd() {
  lcd.init();
  lcd.backlight();
}

void scrollText(void *arg) {
  const int delayTime = 300;
  for (int i=0; i < lcdColumns; i++) {
    message = " " + message;  
  } 
  message = message + " "; 
  for (int pos = 0; pos < message.length(); pos++) {
    lcd.setCursor(0, 1);
    lcd.print(message.substring(pos, pos + lcdColumns));
    delay(delayTime);
  }
  scrollText(NULL);
  // vTaskDelete(NULL);
}

void setupWifi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    lcd.setCursor(0, 0);
    lcd.print("Connecting to:");
    lcd.setCursor(0, 1);
    lcd.print(WIFI_SSID);
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Connected!");
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP());
}

void setupServer() {
  server.on("/", handle_OnConnect);
  server.on("/post", HTTP_POST, handle_notification);
  server.onNotFound(handle_NotFound);
  server.begin();
}

void handle_OnConnect() {
  server.send(200, "text/html", "hello from ESP32");
}

void handle_notification() {
  if (server.hasArg("notification")) {
    server.send(200, "text/html", "Received");
    message = server.arg("notification");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Notification:");
    if (message.length() > lcdColumns) {
      if (scrollTextHandle != NULL) {
        vTaskDelete(scrollTextHandle);
        scrollTextHandle = NULL;
      }
      xTaskCreatePinnedToCore(
        scrollText,         // function to run
        "scrollText",       // task name
        10000,              // stack size (bytes)
        NULL,               // params
        0,                  // priority 
        &scrollTextHandle,  // task handle
        1                   // core
      );
    } else {
      lcd.setCursor(0, 1);
      lcd.print(message);
    }
  } else {
    server.send(422, "text/html", "Missing 'notification'");
  }
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
