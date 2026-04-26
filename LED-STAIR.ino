#include <FastLED.h>

#define IR_PIN_UP    4
#define IR_PIN_DOWN  16
#define NUM_STRIPS   5
#define LEDS_PER_STRIP 3  // Chỉnh lại nếu strip có số LED khác

CRGB leds[NUM_STRIPS][LEDS_PER_STRIP];

// Màu vàng ấm — chỉnh số này nếu muốn vàng đậm/nhạt hơn
#define MAU_VANG CRGB(255, 180, 0)

void tatTatCa() {
  for (int i = 0; i < NUM_STRIPS; i++)
    fill_solid(leds[i], LEDS_PER_STRIP, CRGB::Black);
  FastLED.show();
}

void batStrip(int i) {
  fill_solid(leds[i], LEDS_PER_STRIP, MAU_VANG);
  FastLED.show();
}

void tatStrip(int i) {
  fill_solid(leds[i], LEDS_PER_STRIP, CRGB::Black);
  FastLED.show();
}

void setup() {
  Serial.begin(115200);
  pinMode(IR_PIN_UP,   INPUT);
  pinMode(IR_PIN_DOWN, INPUT);

  FastLED.addLeds<WS2812B, 13, GRB>(leds[0], LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 32, GRB>(leds[1], LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 14, GRB>(leds[2], LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 27, GRB>(leds[3], LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 26, GRB>(leds[4], LEDS_PER_STRIP);

  tatTatCa();
  Serial.println("Khoi dong xong.");
}

void loop() {
  int len   = digitalRead(IR_PIN_UP);
  int xuong = digitalRead(IR_PIN_DOWN);

  Serial.print("LEN: "); Serial.print(len);
  Serial.print(" | XUONG: "); Serial.println(xuong);

  // Đi LÊN: sáng 1→5 rồi tắt 1→5
  if (len == 0) {
    for (int i = 0; i < NUM_STRIPS; i++) {
      batStrip(i); delay(300);
    }
    delay(1000);
    for (int i = 0; i < NUM_STRIPS; i++) {
      tatStrip(i); delay(400);
    }
    delay(300);
  }

  // Đi XUỐNG: sáng 5→1 rồi tắt 5→1
  if (xuong == 0) {
    for (int i = NUM_STRIPS - 1; i >= 0; i--) {
      batStrip(i); delay(300);
    }
    delay(1000);
    for (int i = NUM_STRIPS - 1; i >= 0; i--) {
      tatStrip(i); delay(400);
    }
    delay(300);
  }

  else { tatTatCa(); }

  delay(100);
}