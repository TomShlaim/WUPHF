#define BLYNK_TEMPLATE_ID "YOUR_BLYNK_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "YOUR_BLYNK_TEMPLATE_NAME"
#define BLYNK_AUTH_TOKEN "YOUR_BLYNK_AUTH_TOKEN"
#define BLYNK_PRINT SerialUSB
#define PIN 8
#define NUM_OF_PIXELS 10
#define EspSerial Serial1
#define ESP8266_BAUD 115200

#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_CircuitPlayground.h>
#include <Keyboard.h>
#include <Mouse.h>

char ssid[] = "YOUR_WIFI_SSID";
char pass[] = "YOUR_WIFI_PASSWORD";
char osLogo = KEY_LEFT_GUI;
char enterKey = KEY_RETURN;

ESP8266 wifi( & EspSerial);
Adafruit_NeoPixel neoPixels(NUM_OF_PIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  SerialUSB.begin(115200);

  EspSerial.begin(ESP8266_BAUD);
  delay(10);

  Blynk.begin(BLYNK_AUTH_TOKEN, wifi, ssid, pass);

  neoPixels.begin();
}

void loop() {
  neoPixels.clear();

  Blynk.run();
}
BLYNK_WRITE(V1) {
  int pinValue = param.asInt();

  updateNeoPixels(pinValue);
}
BLYNK_WRITE(V2) {
  int pinValue = param.asInt();

  if (pinValue == 1) {
    wuphfTrigger();
  }
}
void updateNeoPixels(int pinValue) {
  Serial.println("Updated neo pixels amount : ");
  Serial.println(pinValue);

  for (int i = 0; i < pinValue; i++) {
    neoPixels.setPixelColor(i, neoPixels.Color(242, 140, 40));
    neoPixels.show();
    delay(100);
  }

  Serial.println("Resetting the rest of the pixels");
  Serial.println(pinValue);

  for (int i = pinValue; i < NUM_OF_PIXELS; i++) {
    neoPixels.setPixelColor(i, 0);
    neoPixels.show();
    delay(100);
  }
}
void wuphfTrigger() {
  openURL("https://google.com");
  neoPixels.clear();
}
void openURL(char url[]) {
  Serial.println("Opening URL");
  openNewChromeTab();
  insertURL(url);
  Keyboard.press(enterKey);
  Keyboard.releaseAll();
}
void insertURL(char url[]) {
  int i = 0;

  while (url[i] != '\0') {
    char currentChar = url[i];
    Keyboard.write(currentChar);
    ++i;
  }
}
void openNewChromeTab() {
  Keyboard.press(osLogo);
  Keyboard.press('t');
  Keyboard.releaseAll();
}
