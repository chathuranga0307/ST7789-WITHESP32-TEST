#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>

#include <TFT_eSPI.h>
#include "image2.h"

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);

int imageW = 240;
int imageH = 240;

int screenW = 240;
int screenH =  228;//135;
int m = imageW;

int start = 1;
unsigned short imageS[54720] = {0}; // edit this screenW * screen H

int pos = 0;
int x = 0;
int y = 0;
int changeX = 1;
int changeY = 1;

// Variables for test data
int int_value;
float float_value;
bool bool_value = true;

// MAC Address of responder - edit as required
uint8_t broadcastAddress[] = {0x24, 0x6F, 0x28, 0x7A, 0xAE, 0x7C};

// Define a data structure
typedef struct struct_message {
  char a[32];
  int b;
  float c;
  bool d;
} struct_message;
// Create a structured object
struct_message myData;

// Peer info
esp_now_peer_info_t peerInfo;

// Callback function called when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
void setup() {
  Serial.begin(115200);

  //_______________________________

  tft.init();
  tft.setRotation(1);
  tft.setSwapBytes(true);
  tft.fillScreen(TFT_BLACK);

  pos = x + imageW * y;
  start = pos;
  m = screenW + pos;
  for (int i = 0; i < screenW * screenH; i++)
  {
    if (start % m == 0)
    {
      start = start + (imageW - screenW);
      m = m + imageW;
    }
    imageS[i] = Prof_pic[start];
    start++;
  }
  x = x + changeX;
  if (x == imageW - screenW - 1 || x < 0)
    changeX = changeX * -1;

  y = y + changeY;
  if (y == imageH - screenH - 1 || y < 0)
    changeY = changeY * -1;

  tft.pushImage(0, 0, screenW, screenH, imageS);

  //WiFi.mode(WIFI_STA);

}


void loop() {

}
