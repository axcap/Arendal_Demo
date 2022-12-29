#define ESP32

#include <WiFi.h>
#include <HTTPClient.h>
#include <Update.h>
#include <WiFiManager.h>
#include <ota.h>

// This string should correspond to github tag used for Releasing (via. Github Actions)
#define VERSION "0.0.2"

// Replace your_username/your_repo with your values (ex. axcap/Esp-GitHub-OTA)
// This is a link to repo where your firmware updates will be pulled from
#define RELEASE_URL "https://api.github.com/repos/axcap/Arendal_Demo/releases/latest"

#define DELAY_MS 1000

#define HOSTNAME "ESP32 OTA"
#define LED_BUILTIN 12

void setup()
{
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  setup_wifi();
  init_ota(VERSION);
}

void loop()
{
  handle_ota(RELEASE_URL);

  // Your code goes here
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(DELAY_MS);                  // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  delay(DELAY_MS);                  // wait for a second
}

void setup_wifi(){
  WiFiManager wm;
  // wm.resetSettings();
  wm.setHostname(HOSTNAME);
  auto res = wm.autoConnect("Fallback ESP AP"); // password protected ap

  if(!res) {
      Serial.println("Failed to connect");
      ESP.restart();
  }

  Serial.println("\nWiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}