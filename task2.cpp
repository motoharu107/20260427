#include <Adafruit_NeoPixel.h>

const int LED_PIN = 2; // M5Stamp C3Uの内蔵NeoPixel LEDはGPIO2に接続されています
const int GPIO7_PIN = 7; // GPIO 7番ピン
const int NUM_LEDS = 1; // 内蔵LEDの数

Adafruit_NeoPixel pixels(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

unsigned long lastToggleTime = 0; // GPIO 7 最後の切り替え時刻
bool gpio7State = false; // GPIO 7 の状態

void setup() {
  Serial.begin(115200); // シリアル通信を初期化
  pinMode(GPIO7_PIN, OUTPUT); // GPIO 7を出力ピンに設定
  digitalWrite(GPIO7_PIN, LOW); // 初期状態を LOW に設定
  pixels.begin(); // NeoPixelを初期化
  pixels.setBrightness(100); // 明るさを100に設定 (眩しさを抑える)
  pixels.setPixelColor(0, pixels.Color(0, 0, 255)); // 初期状態を青に設定（GPIO7がLOWのため）
  pixels.show(); // 初期状態を表示
}

void loop() {
  unsigned long currentTime = millis();

  // GPIO 7 を1秒間隔で HIGH/LOW に切り替え
  if (currentTime - lastToggleTime >= 1000) {
    gpio7State = !gpio7State;
    digitalWrite(GPIO7_PIN, gpio7State ? HIGH : LOW);
    
    // GPIO 7 の状態に応じて LED の色を更新
    if (gpio7State) {
      // GPIO 7 が HIGH の時は赤
      pixels.setPixelColor(0, pixels.Color(255, 0, 0));
      Serial.println("BUTTON ON"); // シリアル通信で "BUTTON ON" を表示
    } else {
      // GPIO 7 が LOW の時は青
      pixels.setPixelColor(0, pixels.Color(0, 0, 255));
      Serial.println("BUTTON OFF"); // シリアル通信で "BUTTON OFF" を表示
    }
    pixels.show();
    
    lastToggleTime = currentTime;
  }
}
