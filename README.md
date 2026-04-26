# 🪜 ESP32 Stair Chase LED System · Hệ Thống Đèn LED Đuổi Cầu Thang ESP32

<div align="center">

![Platform](https://img.shields.io/badge/Platform-ESP32-blue?logo=espressif&logoColor=white)
![Library](https://img.shields.io/badge/Library-FastLED-ff6600?logo=arduino&logoColor=white)
![Language](https://img.shields.io/badge/Language-Arduino%20C%2B%2B-teal?logo=cplusplus&logoColor=white)
![License](https://img.shields.io/badge/License-MIT-green)
![Status](https://img.shields.io/badge/Status-Working%20✅-brightgreen)
![LED](https://img.shields.io/badge/LED-WS2812B-yellow)
![Sensor](https://img.shields.io/badge/Sensor-IR%20MH--B-red)

</div>

---

> 🇹🇼 **繁體中文（台灣）版本** 見下方 Part 1
>
> 🇻🇳 **Tiếng Việt** xem phần Part 2 bên dưới

---

<br>

# 🇹🇼 PART 1 — 繁體中文（台灣）

---

# 基於ESP32之紅外線感測樓梯追逐燈控制系統

> 💡 當有人走上樓梯，燈條一條一條地依序點亮，像是在為你照路；走過之後，再一條一條地優雅熄滅。這個專題用最簡單的元件，實現了讓家裡充滿科技感的自動感應樓梯燈。

<div align="center">

```
┌─────────────────────────────────────────────────────────┐
│           🪜 樓梯追逐燈示意圖                             │
│                                                         │
│  👤 人從下往上走           👤 人從上往下走               │
│                                                         │
│   ━━━━━━  ← 燈條5 💡       ━━━━━━  ← 燈條5 💡          │
│   ━━━━━━  ← 燈條4 💡       ━━━━━━  ← 燈條4              │
│   ━━━━━━  ← 燈條3 💡       ━━━━━━  ← 燈條3              │
│   ━━━━━━  ← 燈條2           ━━━━━━  ← 燈條2              │
│   ━━━━━━  ← 燈條1 ←感測器1 ━━━━━━  ← 燈條1              │
│                              感測器2↑                   │
│   上行：1→2→3→4→5 點亮      下行：5→4→3→2→1 點亮        │
│         1→2→3→4→5 熄滅            5→4→3→2→1 熄滅        │
└─────────────────────────────────────────────────────────┘
```

</div>

## 📸 實物照片

> 📷 **建議拍攝角度：** 樓梯側拍（能看到燈條位置）、ESP32接線特寫、感測器安裝位置

```
[ 此處放入你的實物照片 ]
建議：上傳到 GitHub 後，用以下語法插入：
![實物照片](images/stair_led_real.jpg)
```

## 🎬 影片示範

> 🎥 **影片連結（請自行填入）：**

```
[![Demo影片](https://img.youtube.com/vi/YOUR_VIDEO_ID/0.jpg)](https://youtu.be/YOUR_VIDEO_ID)
```

---

## 📋 目錄

- [專案簡介](#-專案簡介)
- [硬體清單](#-硬體清單)
- [電路接線](#-電路接線)
- [安裝步驟](#-安裝步驟)
- [程式碼說明](#-程式碼說明)
- [GPIO腳位表](#-gpio腳位表)
- [⚠️ 重要警告](#️-重要警告)
- [自訂設定](#-自訂設定)
- [常見問題排查](#-常見問題排查)
- [開發歷程](#-開發歷程)
- [如何貢獻](#-如何貢獻)
- [授權](#-授權)
- [致謝](#-致謝)

---

## 🔍 專案簡介

這是一個以 **ESP32** 為核心，搭配 **WS2812B RGB LED燈條** 和 **紅外線感測器（MH-B）** 所實現的樓梯自動追逐燈系統。

### ✨ 功能特色

- 🔼 **上行模式**：當感測器1偵測到人時，5條燈條由下往上依序點亮（間隔300ms），等待1秒後依序熄滅
- 🔽 **下行模式**：當感測器2偵測到人時，5條燈條由上往下依序點亮（間隔300ms），等待1秒後依序熄滅
- 🌙 **待機模式**：無人時全部熄滅，節省電力
- 🟡 **暖黃色光**：`CRGB(255, 180, 0)` — 溫馨、不刺眼，適合夜間通行

### 🧠 技術核心

| 項目 | 說明 |
|------|------|
| 主控板 | ESP32（雙核 240MHz，內建 Wi-Fi/BT，雖本專案未使用） |
| LED 驅動 | FastLED 函式庫 — 精確控制 WS2812B 的時序訊號 |
| 感測原理 | 紅外線反射式避障感測，MH-B 模組輸出 LOW（0）表示偵測到障礙物 |
| 電源架構 | 雙電源：18650 3S 電池組（12V）供 LED，ESP32 另外以 USB/5V 供電 |

---

## 🛒 硬體清單

| 數量 | 元件 | 規格 | 建議購買 |
|------|------|------|----------|
| 1x | ESP32 開發板（標準版） | 38腳位，3.3V系統 | [蝦皮搜尋 "ESP32 開發板"](https://shopee.tw) |
| 5x | WS2812B RGB LED 燈條 | 每條3顆LED，12V供電 | [蝦皮搜尋 "WS2812B 燈條"](https://shopee.tw) |
| 2x | 紅外線避障感測模組 | 優信電子 MH-B（附LM358），距離可調 | [蝦皮搜尋 "MH-B 紅外線避障"](https://shopee.tw) |
| 3x | 18650 鋰電池 | 保護板版本，容量 2500mAh+ | [蝦皮搜尋 "18650 鋰電池"](https://shopee.tw) |
| 1x | 18650 3S 電池盒 | 含保護板，串聯輸出 ~11.1V | [蝦皮搜尋 "18650 3S 電池盒"](https://shopee.tw) |
| 1個 | 100µF/25V 電解電容 | 用於穩定 12V 電源雜訊 | 任何電子材料行 |
| 若干 | 杜邦線/排線 | 公母、母母各備一些 | 任何電子材料行 |
| 1個 | 麵包板（選用） | 方便測試接線 | 任何電子材料行 |

> 💡 **購買提示：** WS2812B 燈條請確認是 **12V供電版本**，不要買 5V版本。購買時詢問商家即可。

---

## 🔌 電路接線

### ⚡ 電源架構（非常重要，請務必理解）

```
┌───────────────────────────────────────────────────────┐
│                    電源架構圖                          │
│                                                       │
│  18650 x3 串聯 (12V)                                  │
│    ┌───────┐                                          │
│    │ + 12V │──────┬──── WS2812B 燈條1 (12V / VCC)    │
│    │       │      ├──── WS2812B 燈條2 (12V / VCC)    │
│    │       │      ├──── WS2812B 燈條3 (12V / VCC)    │
│    │       │      ├──── WS2812B 燈條4 (12V / VCC)    │
│    │       │      └──── WS2812B 燈條5 (12V / VCC)    │
│    │  GND  │──────┬──── WS2812B 所有燈條 GND         │
│    └───────┘      └──── ESP32 GND  ← 共地！           │
│                                                       │
│  USB / 5V 電源                                        │
│    ┌───────┐                                          │
│    │ + 5V  │──── ESP32 5V腳位 或 USB供電              │
│    │  GND  │──── ESP32 GND（已與12V共地）             │
│    └───────┘                                          │
│                                                       │
│  ⚠️ 12V 與 5V 電源的 GND 必須連在一起（共地）！        │
└───────────────────────────────────────────────────────┘
```

### 📊 詳細接線表

#### ESP32 → WS2812B 燈條（訊號線 Din）

| ESP32 GPIO | 連接至 | 說明 |
|-----------|--------|------|
| GPIO 13 | 燈條1 Din | 最底階燈條 |
| GPIO 32 | 燈條2 Din | 第2階 |
| GPIO 14 | 燈條3 Din | 第3階（中間） |
| GPIO 27 | 燈條4 Din | 第4階 |
| GPIO 26 | 燈條5 Din | 最頂階燈條 |
| GND | 所有燈條 GND | ⚠️ 必須共地 |

#### ESP32 → MH-B 紅外線感測器

| ESP32 | MH-B 模組 | 說明 |
|-------|-----------|------|
| **3.3V** | VCC | ⚠️ 一定是3.3V，絕對不能接5V！ |
| GND | GND | 接地 |
| **GPIO 4** | OUT | 感測器1（上行，裝在樓梯底部） |
| **GPIO 16** | OUT | 感測器2（下行，裝在樓梯頂部） |

#### WS2812B 燈條電源

| 12V電源 | WS2812B 燈條 |
|---------|-------------|
| + 12V | VCC（紅線）|
| GND | GND（白/黑線）|

> 💡 **Din資料線** 連接 ESP32 GPIO，VCC/GND 連接 12V 電源，三條線各接不同地方。

---

## 🛠 安裝步驟

> 這個部分寫給**完全沒有使用過 Arduino 的新手**。已經熟悉 Arduino IDE 的人可以跳到步驟3。

### 步驟 1：下載並安裝 Arduino IDE

1. 前往 [https://www.arduino.cc/en/software](https://www.arduino.cc/en/software)
2. 點選你的作業系統版本（Windows / macOS / Linux）
3. 下載並按照安裝精靈完成安裝
4. 開啟 Arduino IDE，確認軟體可以正常啟動

### 步驟 2：在 Arduino IDE 加入 ESP32 開發板支援

ESP32 不是 Arduino 原廠開發板，需要手動加入支援套件。

1. 開啟 Arduino IDE
2. 點選上方選單 **檔案（File）** → **偏好設定（Preferences）**
3. 在「**額外的開發板管理員網址（Additional boards manager URLs）**」欄位貼上：
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_espressif_index.json
   ```
4. 按 **OK** 儲存
5. 點選上方選單 **工具（Tools）** → **開發板（Board）** → **開發板管理員（Boards Manager）**
6. 在搜尋框輸入 `esp32`
7. 找到 **esp32 by Espressif Systems**，點選 **安裝（Install）**
8. 等待安裝完成（約需下載幾分鐘，請耐心等候）
9. 安裝完成後，選擇 **工具 → 開發板 → ESP32 Arduino → ESP32 Dev Module**

### 步驟 3：安裝 FastLED 函式庫

WS2812B 需要精確的時序訊號，必須使用 FastLED 函式庫，不能用普通的 `digitalWrite()`。

1. 在 Arduino IDE 點選 **草稿碼（Sketch）** → **Include Library** → **Manage Libraries...**
2. 在搜尋框輸入 `FastLED`
3. 找到 **FastLED by Daniel Garcia**
4. 點選 **Install**，等待安裝完成

### 步驟 4：依照接線表完成硬體連接

按照上面的「詳細接線表」，把每一條線接好：

- ✅ ESP32 的 GPIO 13, 32, 14, 27, 26 分別接到 5 條燈條的 Din
- ✅ 感測器1的 OUT 接 GPIO 4，感測器2的 OUT 接 GPIO 16
- ✅ **感測器 VCC 接 ESP32 的 3.3V**（不是5V！）
- ✅ 12V 電池接燈條的 VCC 和 GND
- ✅ 所有 GND 共地

### 步驟 5：開啟並修改程式碼

1. 下載本專案的 `LED-STAIR.ino` 檔案
2. 用 Arduino IDE 開啟
3. 找到這一行：
   ```cpp
   #define LEDS_PER_STRIP 3  // 每條燈條的LED數量
   ```
4. 把 `3` 改成你實際的每條燈條 LED 數量（如果你的燈條每條有5顆，就改成5）

### 步驟 6：選擇正確的序列埠

1. 用 USB 線把 ESP32 連接到電腦
2. 點選 **工具（Tools）** → **序列埠（Port）**
3. 選擇出現的 COM 埠（Windows 會顯示 COMx，Mac/Linux 會顯示 /dev/tty...）

> 💡 如果沒有出現 COM 埠，可能需要安裝 CH340 驅動程式：[下載連結](https://www.wch.cn/download/CH341SER_EXE.html)

### 步驟 7：上傳程式碼

1. 確認上方顯示的開發板是 **ESP32 Dev Module**
2. 點選左上角的 **上傳（→）** 按鈕
3. 等待下方出現「**上傳完成（Upload complete）**」

### 步驟 8：用 Serial Monitor 確認運作

1. 點選 **工具 → Serial Monitor**
2. 右下角確認 Baud Rate 設定為 **115200**
3. 你應該會看到像這樣的輸出：
   ```
   Khoi dong xong.
   LEN: 1 | XUONG: 1
   LEN: 1 | XUONG: 1
   ...
   ```
4. 當 `LEN` 顯示 `0` 時，代表上行感測器偵測到物體
5. 當 `XUONG` 顯示 `0` 時，代表下行感測器偵測到物體

### 步驟 9：測試功能

1. 用手在 **感測器1** 前方約 5-15 cm 處遮擋 → 燈條應從下往上依序點亮
2. 用手在 **感測器2** 前方約 5-15 cm 處遮擋 → 燈條應從上往下依序點亮
3. 如果感測器沒有反應，調整模組上的 **距離調整旋鈕**（小型藍色可變電阻）

---

## 💻 程式碼說明

以下是完整程式碼，並附上逐段說明：

```cpp
#include <FastLED.h>

// ============================================================
// 腳位定義
// ============================================================
#define IR_PIN_UP    4    // 感測器1（上行）— 接 GPIO 4
#define IR_PIN_DOWN  16   // 感測器2（下行）— 接 GPIO 16
#define NUM_STRIPS   5    // 共有幾條燈條
#define LEDS_PER_STRIP 3  // 每條燈條有幾顆 LED（依實際修改）

// ============================================================
// LED 陣列宣告
// 二維陣列：leds[條索引][顆索引]
// ============================================================
CRGB leds[NUM_STRIPS][LEDS_PER_STRIP];

// 暖黃色定義 — R:255, G:180, B:0
// 想要更亮白可以調高 G 值，想要更橘可以降低 G 值
#define MAU_VANG CRGB(255, 180, 0)

// ============================================================
// 輔助函式：熄滅全部燈條
// ============================================================
void tatTatCa() {
  for (int i = 0; i < NUM_STRIPS; i++)
    fill_solid(leds[i], LEDS_PER_STRIP, CRGB::Black); // Black = 熄滅
  FastLED.show(); // 必須呼叫 show() 才會實際更新 LED
}

// ============================================================
// 輔助函式：點亮第 i 條燈條
// ============================================================
void batStrip(int i) {
  fill_solid(leds[i], LEDS_PER_STRIP, MAU_VANG);
  FastLED.show();
}

// ============================================================
// 輔助函式：熄滅第 i 條燈條
// ============================================================
void tatStrip(int i) {
  fill_solid(leds[i], LEDS_PER_STRIP, CRGB::Black);
  FastLED.show();
}

// ============================================================
// setup() — 開機初始化，只執行一次
// ============================================================
void setup() {
  Serial.begin(115200); // 啟動序列通訊，用來偵錯
  
  pinMode(IR_PIN_UP,   INPUT); // 感測器腳位設為輸入
  pinMode(IR_PIN_DOWN, INPUT);

  // 向 FastLED 登記每條燈條：LED型號、GPIO腳位、顏色順序(GRB)、LED陣列、顆數
  FastLED.addLeds<WS2812B, 13, GRB>(leds[0], LEDS_PER_STRIP); // 燈條1
  FastLED.addLeds<WS2812B, 32, GRB>(leds[1], LEDS_PER_STRIP); // 燈條2
  FastLED.addLeds<WS2812B, 14, GRB>(leds[2], LEDS_PER_STRIP); // 燈條3
  FastLED.addLeds<WS2812B, 27, GRB>(leds[3], LEDS_PER_STRIP); // 燈條4
  FastLED.addLeds<WS2812B, 26, GRB>(leds[4], LEDS_PER_STRIP); // 燈條5

  tatTatCa(); // 確保開機時所有燈都是熄滅狀態
  Serial.println("Khoi dong xong."); // 輸出啟動完成訊息
}

// ============================================================
// loop() — 主程式迴圈，不斷重複執行
// ============================================================
void loop() {
  int len   = digitalRead(IR_PIN_UP);   // 讀取上行感測器
  int xuong = digitalRead(IR_PIN_DOWN); // 讀取下行感測器

  // 輸出感測器狀態到 Serial Monitor（方便偵錯）
  Serial.print("LEN: "); Serial.print(len);
  Serial.print(" | XUONG: "); Serial.println(xuong);

  // ── 上行觸發（感測器1偵測到人，輸出 LOW = 0）──
  if (len == 0) {
    for (int i = 0; i < NUM_STRIPS; i++) {
      batStrip(i); // 依序點亮：燈條1, 2, 3, 4, 5
      delay(300);  // 每條間隔 300ms
    }
    delay(1000); // 全亮後等待 1 秒
    for (int i = 0; i < NUM_STRIPS; i++) {
      tatStrip(i); // 依序熄滅：燈條1, 2, 3, 4, 5
      delay(400);  // 每條間隔 400ms（比點亮慢一些，更優雅）
    }
    delay(300); // 全熄後緩衝 300ms
  }

  // ── 下行觸發（感測器2偵測到人，輸出 LOW = 0）──
  if (xuong == 0) {
    for (int i = NUM_STRIPS - 1; i >= 0; i--) {
      batStrip(i); // 依序點亮：燈條5, 4, 3, 2, 1
      delay(300);
    }
    delay(1000);
    for (int i = NUM_STRIPS - 1; i >= 0; i--) {
      tatStrip(i); // 依序熄滅：燈條5, 4, 3, 2, 1
      delay(400);
    }
    delay(300);
  }

  else { tatTatCa(); } // 沒有任何感測器觸發時，確保全部熄滅

  delay(100); // 主迴圈每次等待 100ms，避免 CPU 過熱
}
```

### 🔍 關鍵程式概念說明

#### 1. 為什麼感測器的「偵測到」是 0 而不是 1？

MH-B 模組使用的是「**低電位觸發（Active Low）**」邏輯。沒有障礙物時，OUT腳位輸出高電位（1）；偵測到障礙物時，輸出低電位（0）。這是紅外線感測器的常見設計，使用前必須了解。

#### 2. 為什麼必須用 FastLED 而不是 digitalWrite？

WS2812B 是智慧型 LED，需要透過精確的**單線序列通訊協定**（約 800Kbps）來傳遞每顆 LED 的 R、G、B 值。FastLED 在背後處理了所有複雜的時序控制。如果用 digitalWrite，根本無法正確驅動 WS2812B。

#### 3. 為什麼顏色順序是 GRB 而不是 RGB？

WS2812B 的 LED 晶片內部接線順序是 **G（綠）→ R（紅）→ B（藍）**，這與一般人直覺的 RGB 順序相反。FastLED 在 `addLeds` 時需要指定 `GRB`，這樣傳入 `CRGB(255, 0, 0)` 才能正確顯示紅色。

---

## 📍 GPIO 腳位表

| 功能 | GPIO 腳位 | 備注 |
|------|-----------|------|
| 上行感測器 | GPIO 4 | 感測器1 OUT |
| 下行感測器 | GPIO 16 | 感測器2 OUT |
| 燈條1 Din | GPIO 13 | 最底階 |
| 燈條2 Din | GPIO 32 | 第2階 |
| 燈條3 Din | GPIO 14 | 第3階 |
| 燈條4 Din | GPIO 27 | 第4階 |
| 燈條5 Din | GPIO 26 | 最頂階 |
| 感測器 VCC | 3.3V | ⚠️ 絕對不是5V！ |
| 共地 | GND | 與12V電源共地 |

### 🗺️ ESP32 安全可用腳位（參考）

```
ESP32 可安全使用的 GPIO（本專案已選用）：
  ✅ GPIO 4, 13, 14, 16, 17, 18, 19, 21, 22, 23, 25, 26, 27, 32, 33, 34, 35

🚫 絕對禁止使用（連接 Flash）：
  GPIO 6, 7, 8, 9, 10, 11

⚠️ 謹慎使用（Strapping Pin，開機時影響系統）：
  GPIO 0, 2, 5, 12, 15
```

---

## ⚠️ 重要警告

> 以下內容都是**真實踩坑血淚教訓**，在製作過程中確實發生過以下問題，請務必仔細閱讀！

---

### 🔴 警告 1：ESP32 的 GPIO 6-11 絕對禁止使用！

```
⛔ GPIO 6, 7, 8, 9, 10, 11 — 嚴禁接任何外部元件！
```

這 6 個腳位在 ESP32 內部連接著**快閃記憶體（SPI Flash）**，是 ESP32 儲存程式碼的地方。一旦你把外部訊號接到這些腳位，**輕則程式無法上傳，重則直接燒毀 ESP32**。這個錯誤不會有任何警告，只會讓你的 ESP32 突然死掉。

---

### 🟠 警告 2：GPIO 12 和 GPIO 5 是 Strapping Pin

```
⚠️ GPIO 0, 2, 5, 12, 15 — Strapping Pin，開機時行為特殊！
```

ESP32 在**開機（Reset/上電）的瞬間**，會讀取這些腳位的電壓來決定系統啟動模式。如果你的外部電路讓這些腳位在開機時呈現異常電壓，**ESP32 會進入下載模式（無法正常運行）或啟動失敗**。本專案刻意避開這些腳位。

---

### 🔴 警告 3：感測器 VCC 只能接 3.3V！

```
⛔ MH-B 感測器 VCC → 接 ESP32 的 3.3V，絕對不能接 5V！
```

**原因：** ESP32 的 GPIO 腳位是 **3.3V 系統**，能承受的最高輸入電壓為 3.3V。MH-B 模組在 3.3V 供電時，OUT 腳位輸出的電壓也是 3.3V，完全安全。但如果你把 VCC 接到 5V，模組的 OUT 腳位輸出的就是 5V 訊號，這個電壓**超出 ESP32 GPIO 的承受範圍，會立刻燒毀 GPIO**。

> 💀 **真實案例：** 本專案開發過程中，曾因為把感測器接到5V導致 GPIO 16 損壞，ESP32 無法偵測下行感測器。後來必須改用 GPIO 17，並重新整理 `#define` 的腳位設定。

---

### 🟠 警告 4：WS2812B 不能用 digitalWrite 控制！

```
⚠️ WS2812B 必須使用 FastLED 函式庫，不能用 digitalWrite()！
```

WS2812B 需要精確的時序訊號（NZR 協定），普通的 `digitalWrite()` 無法達到所需的時序精度。只要使用 `FastLED.addLeds<WS2812B, PIN, GRB>()` 正確登記，FastLED 會在背後全部處理好。

---

### 🟡 警告 5：12V 與 3.3V 電源必須共地！

```
⚠️ 兩個電源系統的 GND 必須連在一起（共地）！
```

ESP32 的 GPIO 訊號線（Din）是以 **ESP32 的 GND 為參考電位**，而 WS2812B 的資料接收是以 **12V 電源的 GND 為參考電位**。如果這兩個 GND 沒有接在一起，Din 線上的訊號電壓對 WS2812B 而言是「不確定的」，燈條可能亂閃、不亮、或只有部分正常。

---

### 🟡 警告 6：WS2812B 對電源雜訊很敏感

```
💡 建議在 12V 電源端並聯一個 100µF / 25V 電解電容
```

WS2812B 在高頻切換時，電流瞬間需求很大。如果電源線較長或電池老化，電壓可能瞬間下降，造成 LED 閃爍或顏色不正確。在電源 VCC 和 GND 之間並聯一個大電容，可以有效吸收這種瞬間雜訊。

---

## 🎨 自訂設定

### 修改 LED 顏色

找到程式碼中的這一行：
```cpp
#define MAU_VANG CRGB(255, 180, 0)
```

修改三個數字（範圍 0-255）：

| 顏色效果 | CRGB 數值 |
|---------|-----------|
| 暖黃色（原版） | `CRGB(255, 180, 0)` |
| 純白色 | `CRGB(255, 255, 255)` |
| 冷白色 | `CRGB(180, 180, 255)` |
| 橘紅色 | `CRGB(255, 80, 0)` |
| 藍色 | `CRGB(0, 0, 255)` |
| 降低亮度（暗暖黃） | `CRGB(128, 90, 0)` |

### 修改追逐速度

```cpp
// 點亮間隔（數字越小越快）
batStrip(i); delay(300);  // 改小→更快，改大→更慢

// 熄滅間隔
tatStrip(i); delay(400);  // 同上

// 全亮後的停留時間
delay(1000);  // 單位：毫秒，1000 = 1 秒
```

### 增加燈條數量

1. 修改 `#define NUM_STRIPS 5` 為新的數量（例如 `7`）
2. 在 `setup()` 中新增對應的 `FastLED.addLeds<>` 行，指定新的 GPIO 和陣列索引
3. 確認新的 GPIO 是安全可用的

### 修改每條 LED 數量

```cpp
#define LEDS_PER_STRIP 3  // 改成你的燈條實際 LED 數量
```

---

## 🔧 常見問題排查

### ❌ 問題：LED 完全不亮

**可能原因與解法：**
1. **12V 電源沒有通電** → 檢查電池電壓，確認開關打開
2. **GND 沒有共地** → 用三用電錶量測 ESP32 GND 和 12V 電池負極之間的電壓，應該是 0V
3. **Din 接線錯誤** → 確認 Din 線接到正確的 GPIO，而不是 VCC 或 GND
4. **FastLED 沒有正確安裝** → 重新安裝 FastLED 函式庫

### ❌ 問題：LED 亮起但顏色不對（應該黃色卻是藍色或其他顏色）

**原因：** 你的燈條顏色順序可能是 RGB 而不是 GRB。

**解法：** 把 `GRB` 改成 `RGB`：
```cpp
FastLED.addLeds<WS2812B, 13, RGB>(leds[0], LEDS_PER_STRIP); // 改 GRB → RGB
```

### ❌ 問題：感測器偵測到人但燈不亮（Serial Monitor 顯示 LEN 沒有變成 0）

**可能原因與解法：**
1. **感測器距離太遠** → 用螺絲起子順時針轉動模組上的小藍色可變電阻，縮短感測距離
2. **VCC 接錯了（接了5V）** → 改接 3.3V。如果已接5V，GPIO 可能已損壞，需換一個 GPIO 腳位
3. **模組本身壞了** → 換一個新的 MH-B 模組測試

### ❌ 問題：LED 隨機亂閃或顏色不穩定

**可能原因與解法：**
1. **電源電壓不穩** → 加裝 100µF 電容在電源端
2. **連接線太長** → 縮短 Din 線長度，或在 Din 線上串聯一個 300-500Ω 電阻（在 ESP32 側）
3. **電池電量不足** → 充電或換新電池

### ❌ 問題：程式上傳失敗（找不到 ESP32 或上傳超時）

**可能原因與解法：**
1. **沒有安裝 CH340 驅動** → 下載安裝 CH340 驅動程式
2. **GPIO 0 被拉低** → 確認 GPIO 0 沒有外部電路干擾（這是下載模式觸發腳位）
3. **USB 線只有充電功能** → 換一條有資料傳輸功能的 USB 線
4. **序列埠選錯了** → 在 Arduino IDE 重新選擇正確的 COM 埠

### ❌ 問題：上傳成功但 Serial Monitor 顯示亂碼

**原因：** Baud Rate 設定不正確。

**解法：** Serial Monitor 右下角的 Baud Rate 選擇 **115200**（與程式碼中的 `Serial.begin(115200)` 一致）。

---

## 📖 開發歷程

> 這個專案不是一開始就成功的。以下是從零開始，踩過的每一個坑的完整記錄，希望你能避開這些錯誤。

### 第一版：Arduino Uno + 普通 LED 燈泡

**起點：** 最初的構想很簡單 — 用幾顆 LED 搭配感測器，讓樓梯燈自動亮。使用的是 Arduino Uno 和普通 5mm LED。

**遇到的問題：**
- Arduino Uno 的 I/O 腳位數量不夠（只有 14 個數位腳位），要控制 5 條各自獨立的燈條，腳位很快就不夠用
- 普通 LED 只有開/關，無法調色或調亮度

**結論：** 硬體選型錯誤，需要升級。

### 第二版：Arduino Uno + WS2812B + digitalWrite（失敗）

**嘗試：** 換用 WS2812B 可定址 LED，試著用 `digitalWrite()` 直接控制。

**遇到的問題：**
- `digitalWrite()` 的時序完全無法滿足 WS2812B 的 NZR 通訊協定需求
- LED 要麼完全不亮，要麼隨機閃爍亂色
- 完全無法穩定控制

**學到的教訓：** WS2812B **必須**使用專用函式庫（FastLED 或 NeoPixel）。

### 第三版：Arduino Uno + WS2812B + FastLED（可以動但有限制）

**進展：** 改用 FastLED 後，LED 終於可以穩定控制了！顏色正確，追逐效果也能實現。

**但遇到了新問題：**
- Arduino Uno 的記憶體（SRAM 只有 2KB）在處理多條燈條的陣列時，偶爾會發生記憶體不足崩潰
- Arduino Uno 的腳位電壓是 5V，而某些模組是 3.3V 系統，需要電壓轉換

### 第四版：ESP32 + WS2812B + FastLED（接線錯誤版）

**升級：** 換用 ESP32，記憶體（520KB SRAM）和腳位數量問題全部解決！

**但這次犯了新的致命錯誤：**

1. **燒毀 GPIO 16：** 把感測器 VCC 接到了 5V，導致 OUT 腳位輸出 5V 訊號，超過 ESP32 的 3.3V 容忍範圍，GPIO 16 直接損壞。

2. **使用了 Strapping Pin：** 測試過程中，曾把一條燈條的 Din 接到 GPIO 12。結果 ESP32 在電池供電模式下不斷重啟，找不到原因，後來才查資料發現 GPIO 12 是 Flash 電壓選擇的 Strapping Pin。

3. **嘗試使用 GPIO 6：** 因為不知道 ESP32 的限制，曾試著接 GPIO 6，結果 ESP32 直接無法上傳程式，一度以為 ESP32 壞了。

**每個錯誤都花了大量時間排查和確認。**

### 第五版（現在的版本）：謹慎選腳位，穩定運行 ✅

**最終解法：**
- 仔細研究 ESP32 的 GPIO 限制，選用安全腳位（13, 14, 16, 26, 27, 32）
- 感測器 VCC 改接 3.3V
- 完整共地處理
- 加裝 100µF 電容穩定電源

**結果：** 系統穩定運行，追逐燈效果完美，感測器靈敏度良好。

---

## 🤝 如何貢獻

歡迎所有人提交 Pull Request 或 Issue！

1. Fork 本專案
2. 建立你的功能分支：`git checkout -b feature/你的功能名稱`
3. 提交你的修改：`git commit -m '加入新功能：某某某'`
4. 推送到分支：`git push origin feature/你的功能名稱`
5. 開啟 Pull Request

### 💡 歡迎的貢獻方向

- [ ] 加入亮度調節功能
- [ ] 加入不同顏色模式（彩虹追逐等）
- [ ] Wi-Fi/藍牙遠端控制
- [ ] 感測器偵測範圍自動校準
- [ ] 更優雅的熄滅效果（漸暗）
- [ ] 支援更多 LED 型號

---

## 📄 授權

本專案採用 **MIT License** 授權。

你可以自由使用、修改、散布本專案，包含商業用途，唯需保留原始授權聲明。

詳見 [LICENSE](LICENSE) 檔案。

---

## 🙏 致謝

- **FastLED 團隊** — 提供了穩定且強大的 LED 控制函式庫，使本專案得以實現
- **Espressif Systems** — ESP32 這塊強大的晶片讓 Maker 的可能性大幅擴展
- **Arduino 社群** — 豐富的教學資源讓初學者也能快速入門
- **優信電子** — MH-B 感測器模組品質穩定，價格實惠
- 所有在 Stack Overflow 和 Arduino Forum 上分享 ESP32 GPIO 限制知識的開發者們——正是你們的分享，避免了更多人踩相同的坑

---

<br>
<br>
<br>

---

# 🇻🇳 PART 2 — TIẾNG VIỆT

---

# Hệ Thống Đèn LED Đuổi Cầu Thang Dùng ESP32 & Cảm Biến Hồng Ngoại

> 💡 Khi có người bước lên cầu thang, từng thanh đèn sáng lên theo thứ tự như đang dẫn đường; sau khi đi qua, chúng lại tắt đi từng cái một một cách duyên dáng. Dự án này dùng những linh kiện đơn giản nhất để tạo ra hệ thống đèn cầu thang tự động cảm ứng đầy công nghệ cho ngôi nhà của bạn.

<div align="center">

```
┌─────────────────────────────────────────────────────────┐
│         🪜 Sơ đồ hệ thống đèn đuổi cầu thang            │
│                                                         │
│  👤 Người đi LÊN              👤 Người đi XUỐNG         │
│                                                         │
│   ━━━━━━  ← Đèn 5 💡          ━━━━━━  ← Đèn 5 💡       │
│   ━━━━━━  ← Đèn 4 💡          ━━━━━━  ← Đèn 4           │
│   ━━━━━━  ← Đèn 3 💡          ━━━━━━  ← Đèn 3           │
│   ━━━━━━  ← Đèn 2              ━━━━━━  ← Đèn 2           │
│   ━━━━━━  ← Đèn 1 ←Cảm biến1  ━━━━━━  ← Đèn 1          │
│                               Cảm biến 2↑              │
│   Lên: sáng 1→2→3→4→5         Xuống: sáng 5→4→3→2→1   │
│         tắt 1→2→3→4→5                 tắt 5→4→3→2→1    │
└─────────────────────────────────────────────────────────┘
```

</div>

## 📸 Hình ảnh thực tế

> 📷 **Góc chụp gợi ý:** Chụp nghiêng cầu thang (thấy được vị trí đèn), cận cảnh dây nối ESP32, vị trí lắp cảm biến

```
[ Đặt ảnh thực tế của bạn vào đây ]
Gợi ý: Upload lên GitHub rồi chèn bằng cú pháp:
![Ảnh thực tế](images/stair_led_real.jpg)
```

## 🎬 Video Demo

> 🎥 **Link video (điền vào sau khi quay):**

```
[![Video Demo](https://img.youtube.com/vi/YOUR_VIDEO_ID/0.jpg)](https://youtu.be/YOUR_VIDEO_ID)
```

---

## 📋 Mục lục

- [Giới thiệu dự án](#-giới-thiệu-dự-án)
- [Danh sách linh kiện](#-danh-sách-linh-kiện)
- [Sơ đồ đấu dây](#-sơ-đồ-đấu-dây)
- [Hướng dẫn cài đặt](#-hướng-dẫn-cài-đặt)
- [Giải thích code](#-giải-thích-code)
- [Bảng GPIO](#-bảng-gpio)
- [⚠️ Cảnh báo quan trọng](#️-cảnh-báo-quan-trọng)
- [Tùy chỉnh](#-tùy-chỉnh)
- [Xử lý lỗi thường gặp](#-xử-lý-lỗi-thường-gặp)
- [Lịch sử phát triển](#-lịch-sử-phát-triển)
- [Đóng góp](#-đóng-góp)
- [Giấy phép](#-giấy-phép)
- [Lời cảm ơn](#-lời-cảm-ơn)

---

## 🔍 Giới thiệu dự án

Đây là hệ thống đèn cầu thang tự động sử dụng **ESP32** làm bộ điều khiển trung tâm, kết hợp với **5 thanh đèn LED WS2812B RGB** và **2 cảm biến hồng ngoại (module MH-B)** để tạo hiệu ứng đèn "đuổi" theo người đi.

### ✨ Tính năng chính

- 🔼 **Chế độ đi lên:** Khi cảm biến 1 phát hiện người, 5 thanh đèn sáng lần lượt từ dưới lên (cách nhau 300ms), giữ sáng 1 giây, rồi tắt lần lượt
- 🔽 **Chế độ đi xuống:** Khi cảm biến 2 phát hiện người, 5 thanh đèn sáng lần lượt từ trên xuống (cách nhau 300ms), giữ sáng 1 giây, rồi tắt lần lượt
- 🌙 **Chế độ chờ:** Khi không có người, tất cả đèn tắt để tiết kiệm điện
- 🟡 **Màu vàng ấm:** `CRGB(255, 180, 0)` — ấm áp, không chói, phù hợp đi đêm

### 🧠 Nền tảng kỹ thuật

| Thành phần | Chi tiết |
|-----------|----------|
| Vi điều khiển | ESP32 (2 lõi 240MHz, tích hợp Wi-Fi/BT — dự án này chưa dùng) |
| Điều khiển LED | Thư viện FastLED — kiểm soát chính xác tín hiệu thời gian cho WS2812B |
| Nguyên lý cảm biến | Phản xạ hồng ngoại, module MH-B xuất LOW (0) khi phát hiện vật cản |
| Kiến trúc nguồn điện | Nguồn kép: pin 18650 3S (12V) cho đèn LED, ESP32 cấp nguồn qua USB/5V riêng |

---

## 🛒 Danh sách linh kiện

| Số lượng | Linh kiện | Thông số | Mua ở đâu |
|---------|-----------|----------|-----------|
| 1x | Mạch ESP32 (bản tiêu chuẩn) | 38 chân, hệ thống 3.3V | [Shopee: "ESP32 development board"](https://shopee.vn) |
| 5x | Thanh đèn WS2812B RGB | Mỗi thanh 3 LED, nguồn 12V | [Shopee: "WS2812B LED strip"](https://shopee.vn) |
| 2x | Module cảm biến tránh vật cản hồng ngoại | Ưu Tín MH-B (có LM358), điều chỉnh được khoảng cách | [Shopee: "MH-B IR obstacle avoidance"](https://shopee.vn) |
| 3x | Pin 18650 Lithium | Loại có mạch bảo vệ, ≥2500mAh | [Shopee: "18650 lithium battery"](https://shopee.vn) |
| 1x | Hộp pin 18650 3S | Có mạch bảo vệ, nối tiếp, đầu ra ~11.1V | [Shopee: "18650 3S battery holder"](https://shopee.vn) |
| 1 cái | Tụ điện điện phân 100µF/25V | Lọc nhiễu nguồn 12V | Cửa hàng linh kiện điện tử |
| Vài sợi | Dây cắm (jumper wire) | Đực-cái, cái-cái, mỗi loại chuẩn bị sẵn | Cửa hàng linh kiện điện tử |
| 1 cái | Breadboard (tuỳ chọn) | Tiện cho việc test | Cửa hàng linh kiện điện tử |

> 💡 **Lưu ý khi mua:** Thanh đèn WS2812B phải là loại **nguồn 12V**, không phải 5V. Hỏi người bán trước khi mua.

---

## 🔌 Sơ đồ đấu dây

### ⚡ Kiến trúc nguồn điện (rất quan trọng, phải hiểu rõ)

```
┌───────────────────────────────────────────────────────┐
│                 Sơ đồ nguồn điện                       │
│                                                       │
│  3 pin 18650 nối tiếp (12V)                           │
│    ┌───────┐                                          │
│    │ + 12V │──────┬──── WS2812B Đèn 1 (12V / VCC)    │
│    │       │      ├──── WS2812B Đèn 2 (12V / VCC)    │
│    │       │      ├──── WS2812B Đèn 3 (12V / VCC)    │
│    │       │      ├──── WS2812B Đèn 4 (12V / VCC)    │
│    │       │      └──── WS2812B Đèn 5 (12V / VCC)    │
│    │  GND  │──────┬──── GND tất cả các thanh đèn      │
│    └───────┘      └──── ESP32 GND  ← Phải chung mass! │
│                                                       │
│  USB / 5V (nguồn cho ESP32)                           │
│    ┌───────┐                                          │
│    │ + 5V  │──── Chân 5V trên ESP32 hoặc cổng USB    │
│    │  GND  │──── ESP32 GND (đã chung với 12V rồi)    │
│    └───────┘                                          │
│                                                       │
│  ⚠️ GND của nguồn 12V và 5V phải được nối chung!      │
└───────────────────────────────────────────────────────┘
```

### 📊 Bảng đấu dây chi tiết

#### ESP32 → WS2812B (dây tín hiệu Din)

| GPIO trên ESP32 | Nối tới | Ghi chú |
|----------------|---------|---------|
| GPIO 13 | Đèn 1 Din | Thanh thấp nhất |
| GPIO 32 | Đèn 2 Din | Bậc thứ 2 |
| GPIO 14 | Đèn 3 Din | Bậc giữa |
| GPIO 27 | Đèn 4 Din | Bậc thứ 4 |
| GPIO 26 | Đèn 5 Din | Thanh cao nhất |
| GND | GND tất cả đèn | ⚠️ Phải chung mass |

#### ESP32 → Cảm biến hồng ngoại MH-B

| Chân ESP32 | Chân module MH-B | Ghi chú |
|-----------|-----------------|---------|
| **3.3V** | VCC | ⚠️ Phải là 3.3V, tuyệt đối không cắm 5V! |
| GND | GND | Nối đất |
| **GPIO 4** | OUT | Cảm biến 1 (đi lên, đặt ở chân cầu thang) |
| **GPIO 16** | OUT | Cảm biến 2 (đi xuống, đặt ở đỉnh cầu thang) |

#### Nguồn điện cho thanh đèn WS2812B

| Nguồn 12V | WS2812B |
|-----------|---------|
| + 12V | VCC (dây đỏ) |
| GND | GND (dây trắng/đen) |

> 💡 **Lưu ý:** Dây **Din** nối vào GPIO của ESP32; dây **VCC và GND** nối vào nguồn 12V. Ba dây, ba nơi khác nhau!

---

## 🛠 Hướng dẫn cài đặt

> Phần này viết dành cho người **hoàn toàn chưa dùng Arduino bao giờ**. Ai đã biết Arduino IDE có thể bỏ qua bước 1-2.

### Bước 1: Tải và cài Arduino IDE

1. Vào [https://www.arduino.cc/en/software](https://www.arduino.cc/en/software)
2. Chọn phiên bản theo hệ điều hành của bạn (Windows / macOS / Linux)
3. Tải về và cài đặt theo hướng dẫn
4. Mở Arduino IDE, kiểm tra phần mềm chạy được bình thường

### Bước 2: Thêm hỗ trợ board ESP32 vào Arduino IDE

ESP32 không phải board gốc của Arduino, cần thêm thủ công.

1. Mở Arduino IDE
2. Chọn menu **File** → **Preferences**
3. Tìm ô **"Additional boards manager URLs"**, dán vào:
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_espressif_index.json
   ```
4. Nhấn **OK** để lưu
5. Vào **Tools** → **Board** → **Boards Manager**
6. Gõ `esp32` vào ô tìm kiếm
7. Tìm **esp32 by Espressif Systems**, nhấn **Install**
8. Chờ cài đặt xong (cần tải xuống vài phút, hãy kiên nhẫn)
9. Sau khi xong, chọn **Tools → Board → ESP32 Arduino → ESP32 Dev Module**

### Bước 3: Cài thư viện FastLED

WS2812B cần tín hiệu thời gian chính xác, bắt buộc dùng FastLED, không thể dùng `digitalWrite()` thông thường.

1. Trong Arduino IDE, vào **Sketch** → **Include Library** → **Manage Libraries...**
2. Gõ `FastLED` vào ô tìm kiếm
3. Tìm **FastLED by Daniel Garcia**
4. Nhấn **Install**, chờ cài đặt hoàn tất

### Bước 4: Đấu dây phần cứng

Theo bảng đấu dây ở phần trên, nối từng dây một:

- ✅ GPIO 13, 32, 14, 27, 26 của ESP32 nối vào Din của 5 thanh đèn
- ✅ OUT cảm biến 1 → GPIO 4, OUT cảm biến 2 → GPIO 16
- ✅ **VCC cảm biến → chân 3.3V của ESP32** (không phải 5V!)
- ✅ Pin 12V → VCC và GND của các thanh đèn
- ✅ Tất cả GND nối chung (chung mass)

### Bước 5: Mở và chỉnh sửa code

1. Tải file `LED-STAIR.ino` từ dự án này
2. Mở bằng Arduino IDE
3. Tìm dòng này:
   ```cpp
   #define LEDS_PER_STRIP 3  // số LED mỗi thanh đèn
   ```
4. Đổi `3` thành số LED thực tế của thanh đèn bạn dùng (ví dụ 5 thì đổi thành 5)

### Bước 6: Chọn cổng COM đúng

1. Cắm ESP32 vào máy tính bằng dây USB
2. Vào **Tools** → **Port**
3. Chọn cổng COM xuất hiện (Windows: COMx, Mac/Linux: /dev/tty...)

> 💡 Nếu không thấy cổng COM, cần cài driver CH340: [Link tải](https://www.wch.cn/download/CH341SER_EXE.html)

### Bước 7: Nạp code

1. Xác nhận board đang chọn là **ESP32 Dev Module**
2. Nhấn nút **Upload (→)** ở góc trái trên
3. Chờ thấy dòng **"Upload complete"** ở dưới cùng

### Bước 8: Kiểm tra qua Serial Monitor

1. Vào **Tools → Serial Monitor**
2. Đặt Baud Rate ở góc dưới phải thành **115200**
3. Bạn sẽ thấy màn hình hiển thị như sau:
   ```
   Khoi dong xong.
   LEN: 1 | XUONG: 1
   LEN: 1 | XUONG: 1
   ...
   ```
4. Khi `LEN` hiển thị `0` → cảm biến 1 đang phát hiện vật
5. Khi `XUONG` hiển thị `0` → cảm biến 2 đang phát hiện vật

### Bước 9: Test chức năng

1. Dùng tay che trước **cảm biến 1** cách khoảng 5-15cm → đèn sáng dần từ dưới lên
2. Dùng tay che trước **cảm biến 2** → đèn sáng dần từ trên xuống
3. Nếu cảm biến không phản ứng, vặn vít điều chỉnh trên module (biến trở xanh nhỏ) để tăng độ nhạy

---

## 💻 Giải thích code

Đây là code hoàn chỉnh với chú thích chi tiết:

```cpp
#include <FastLED.h>

// ============================================================
// Định nghĩa chân GPIO
// ============================================================
#define IR_PIN_UP    4    // Cảm biến 1 (đi lên) — nối GPIO 4
#define IR_PIN_DOWN  16   // Cảm biến 2 (đi xuống) — nối GPIO 16
#define NUM_STRIPS   5    // Tổng số thanh đèn
#define LEDS_PER_STRIP 3  // Số LED mỗi thanh (chỉnh theo thực tế)

// ============================================================
// Khai báo mảng LED
// Mảng 2 chiều: leds[chỉ số thanh][chỉ số LED]
// ============================================================
CRGB leds[NUM_STRIPS][LEDS_PER_STRIP];

// Màu vàng ấm — R:255, G:180, B:0
// Muốn trắng hơn: tăng G; muốn cam hơn: giảm G
#define MAU_VANG CRGB(255, 180, 0)

// ============================================================
// Hàm phụ: tắt tất cả thanh đèn
// ============================================================
void tatTatCa() {
  for (int i = 0; i < NUM_STRIPS; i++)
    fill_solid(leds[i], LEDS_PER_STRIP, CRGB::Black); // Black = tắt
  FastLED.show(); // Bắt buộc phải gọi show() để cập nhật LED thực
}

// ============================================================
// Hàm phụ: bật thanh đèn thứ i
// ============================================================
void batStrip(int i) {
  fill_solid(leds[i], LEDS_PER_STRIP, MAU_VANG);
  FastLED.show();
}

// ============================================================
// Hàm phụ: tắt thanh đèn thứ i
// ============================================================
void tatStrip(int i) {
  fill_solid(leds[i], LEDS_PER_STRIP, CRGB::Black);
  FastLED.show();
}

// ============================================================
// setup() — khởi tạo, chạy 1 lần khi mới bật
// ============================================================
void setup() {
  Serial.begin(115200); // Khởi động Serial để debug
  
  pinMode(IR_PIN_UP,   INPUT); // Cấu hình chân cảm biến là INPUT
  pinMode(IR_PIN_DOWN, INPUT);

  // Đăng ký từng thanh đèn với FastLED: loại LED, GPIO, thứ tự màu GRB
  FastLED.addLeds<WS2812B, 13, GRB>(leds[0], LEDS_PER_STRIP); // Đèn 1
  FastLED.addLeds<WS2812B, 32, GRB>(leds[1], LEDS_PER_STRIP); // Đèn 2
  FastLED.addLeds<WS2812B, 14, GRB>(leds[2], LEDS_PER_STRIP); // Đèn 3
  FastLED.addLeds<WS2812B, 27, GRB>(leds[3], LEDS_PER_STRIP); // Đèn 4
  FastLED.addLeds<WS2812B, 26, GRB>(leds[4], LEDS_PER_STRIP); // Đèn 5

  tatTatCa(); // Đảm bảo lúc khởi động tất cả đèn đều tắt
  Serial.println("Khoi dong xong."); // Thông báo khởi động xong
}

// ============================================================
// loop() — vòng lặp chính, chạy liên tục
// ============================================================
void loop() {
  int len   = digitalRead(IR_PIN_UP);   // Đọc cảm biến 1
  int xuong = digitalRead(IR_PIN_DOWN); // Đọc cảm biến 2

  // In trạng thái cảm biến ra Serial Monitor để debug
  Serial.print("LEN: "); Serial.print(len);
  Serial.print(" | XUONG: "); Serial.println(xuong);

  // ── Kích hoạt đi LÊN (cảm biến 1 phát hiện người, xuất LOW = 0) ──
  if (len == 0) {
    for (int i = 0; i < NUM_STRIPS; i++) {
      batStrip(i); // Bật lần lượt: đèn 1, 2, 3, 4, 5
      delay(300);  // Cách nhau 300ms
    }
    delay(1000); // Giữ sáng 1 giây
    for (int i = 0; i < NUM_STRIPS; i++) {
      tatStrip(i); // Tắt lần lượt: đèn 1, 2, 3, 4, 5
      delay(400);  // Cách nhau 400ms (chậm hơn bật, mềm mại hơn)
    }
    delay(300); // Đợi thêm 300ms trước khi vòng lặp tiếp
  }

  // ── Kích hoạt đi XUỐNG (cảm biến 2 phát hiện người, xuất LOW = 0) ──
  if (xuong == 0) {
    for (int i = NUM_STRIPS - 1; i >= 0; i--) {
      batStrip(i); // Bật lần lượt: đèn 5, 4, 3, 2, 1
      delay(300);
    }
    delay(1000);
    for (int i = NUM_STRIPS - 1; i >= 0; i--) {
      tatStrip(i); // Tắt lần lượt: đèn 5, 4, 3, 2, 1
      delay(400);
    }
    delay(300);
  }

  else { tatTatCa(); } // Không cảm biến nào kích hoạt → tắt hết

  delay(100); // Vòng lặp nghỉ 100ms để tránh quá tải CPU
}
```

### 🔍 Giải thích các khái niệm quan trọng

#### 1. Tại sao "phát hiện được" lại bằng 0 chứ không phải 1?

Module MH-B sử dụng logic **kích hoạt mức thấp (Active Low)**. Khi không có vật cản, chân OUT xuất mức cao (1). Khi phát hiện vật cản, chân OUT xuất mức thấp (0). Đây là thiết kế phổ biến của cảm biến hồng ngoại, cần nắm rõ trước khi dùng.

#### 2. Tại sao phải dùng FastLED chứ không dùng digitalWrite?

WS2812B là LED thông minh, cần giao tiếp nối tiếp một dây chính xác với tốc độ ~800Kbps để truyền giá trị R, G, B cho từng LED. FastLED xử lý toàn bộ timing phức tạp phía sau. Nếu dùng `digitalWrite`, không thể điều khiển WS2812B đúng cách.

#### 3. Tại sao thứ tự màu là GRB chứ không phải RGB?

Chip LED bên trong WS2812B có thứ tự nối dây là **G (xanh lá) → R (đỏ) → B (xanh dương)**, ngược với RGB thông thường. FastLED cần chỉ định `GRB` khi `addLeds`, nhờ đó khi bạn viết `CRGB(255, 0, 0)`, màu đỏ hiển thị đúng.

---

## 📍 Bảng GPIO

| Chức năng | GPIO | Ghi chú |
|-----------|------|---------|
| Cảm biến 1 (đi lên) | GPIO 4 | OUT cảm biến 1 |
| Cảm biến 2 (đi xuống) | GPIO 16 | OUT cảm biến 2 |
| Din Đèn 1 | GPIO 13 | Bậc thấp nhất |
| Din Đèn 2 | GPIO 32 | Bậc 2 |
| Din Đèn 3 | GPIO 14 | Bậc giữa |
| Din Đèn 4 | GPIO 27 | Bậc 4 |
| Din Đèn 5 | GPIO 26 | Bậc cao nhất |
| VCC cảm biến | 3.3V | ⚠️ Không phải 5V! |
| GND chung | GND | Chung mass với nguồn 12V |

### 🗺️ Các GPIO an toàn có thể dùng trên ESP32

```
✅ GPIO an toàn dùng cho dự án này:
  GPIO 4, 13, 14, 16, 17, 18, 19, 21, 22, 23, 25, 26, 27, 32, 33, 34, 35

🚫 TUYỆT ĐỐI KHÔNG dùng (nối với Flash nội bộ):
  GPIO 6, 7, 8, 9, 10, 11

⚠️ Cẩn thận (Strapping Pin, ảnh hưởng lúc khởi động):
  GPIO 0, 2, 5, 12, 15
```

---

## ⚠️ Cảnh báo quan trọng

> Đây đều là **kinh nghiệm thực tế đau thương** — những lỗi này đã thực sự xảy ra trong quá trình làm dự án. Hãy đọc kỹ để tránh!

---

### 🔴 Cảnh báo 1: GPIO 6-11 của ESP32 TUYỆT ĐỐI KHÔNG ĐƯỢC DÙNG!

```
⛔ GPIO 6, 7, 8, 9, 10, 11 — Cấm kết nối bất kỳ linh kiện ngoài nào!
```

6 chân này bên trong ESP32 được kết nối với **Flash SPI** — bộ nhớ lưu chương trình của ESP32. Nếu bạn nối tín hiệu ngoài vào đây, **nhẹ thì không nạp được code, nặng thì cháy ESP32 ngay lập tức**. Lỗi này không có cảnh báo, ESP32 của bạn sẽ "chết" đột ngột mà không hiểu vì sao.

---

### 🟠 Cảnh báo 2: GPIO 12 và GPIO 5 là Strapping Pin

```
⚠️ GPIO 0, 2, 5, 12, 15 — Strapping Pin, hành vi đặc biệt lúc khởi động!
```

ESP32 đọc điện áp các chân này **ngay lúc bật nguồn/Reset** để quyết định chế độ khởi động. Nếu mạch ngoài làm điện áp các chân này bất thường lúc bật nguồn, **ESP32 sẽ vào chế độ download (không chạy code được) hoặc không khởi động được**. Dự án này chủ động tránh các chân đó.

---

### 🔴 Cảnh báo 3: VCC cảm biến chỉ được cắm vào 3.3V!

```
⛔ VCC module MH-B → cắm vào chân 3.3V của ESP32, TUYỆT ĐỐI không cắm 5V!
```

**Lý do:** Hệ thống GPIO của ESP32 chạy ở **3.3V**. Module MH-B ở 3.3V sẽ xuất tín hiệu OUT mức 3.3V — hoàn toàn an toàn. Nhưng nếu cắm VCC vào 5V, OUT sẽ xuất 5V. Điện áp này **vượt ngưỡng chịu đựng của GPIO ESP32, sẽ cháy GPIO ngay lập tức**.

> 💀 **Sự cố thực tế:** Trong quá trình làm dự án, đã từng cắm cảm biến vào 5V làm cháy GPIO 16. ESP32 không còn đọc được cảm biến xuống nữa. Phải chuyển sang dùng GPIO 17 và cập nhật lại `#define` trong code.

---

### 🟠 Cảnh báo 4: WS2812B không thể điều khiển bằng digitalWrite!

```
⚠️ WS2812B bắt buộc phải dùng thư viện FastLED, không được dùng digitalWrite()!
```

WS2812B cần tín hiệu thời gian chính xác (giao thức NZR), `digitalWrite()` thông thường không đủ độ chính xác thời gian. Chỉ cần dùng `FastLED.addLeds<WS2812B, PIN, GRB>()` đúng cách, FastLED sẽ xử lý tất cả phía sau.

---

### 🟡 Cảnh báo 5: GND nguồn 12V và 3.3V phải nối chung!

```
⚠️ GND của hai hệ thống nguồn phải nối chung (common ground)!
```

Tín hiệu GPIO của ESP32 (dây Din) lấy GND của ESP32 làm điện áp tham chiếu, trong khi WS2812B lấy GND của nguồn 12V làm tham chiếu. Nếu hai GND này không nối chung, tín hiệu trên dây Din sẽ "không xác định" với WS2812B — đèn có thể nháy loạn, không sáng, hoặc chỉ một phần hoạt động.

---

### 🟡 Cảnh báo 6: WS2812B rất nhạy với nhiễu nguồn

```
💡 Khuyến nghị: gắn tụ điện 100µF / 25V song song với nguồn 12V
```

WS2812B khi chuyển đổi nhanh sẽ kéo dòng điện đột ngột rất lớn. Nếu dây nguồn dài hoặc pin xuống, điện áp có thể tụt đột ngột, gây nháy đèn hoặc màu sắc sai. Gắn tụ lớn giữa VCC và GND sẽ hấp thụ nhiễu này hiệu quả.

---

## 🎨 Tùy chỉnh

### Thay đổi màu sắc LED

Tìm dòng này trong code:
```cpp
#define MAU_VANG CRGB(255, 180, 0)
```

Thay đổi ba số (từ 0 đến 255):

| Màu sắc | Giá trị CRGB |
|---------|-------------|
| Vàng ấm (bản gốc) | `CRGB(255, 180, 0)` |
| Trắng thuần | `CRGB(255, 255, 255)` |
| Trắng lạnh | `CRGB(180, 180, 255)` |
| Cam đỏ | `CRGB(255, 80, 0)` |
| Xanh dương | `CRGB(0, 0, 255)` |
| Vàng ấm tối hơn | `CRGB(128, 90, 0)` |

### Thay đổi tốc độ hiệu ứng

```cpp
// Khoảng cách giữa mỗi lần bật (số nhỏ = nhanh hơn)
batStrip(i); delay(300);  // Giảm số → nhanh hơn, tăng → chậm hơn

// Khoảng cách giữa mỗi lần tắt
tatStrip(i); delay(400);  // Tương tự

// Thời gian giữ sáng
delay(1000);  // Đơn vị: millisecond, 1000 = 1 giây
```

### Thêm bớt số thanh đèn

1. Đổi `#define NUM_STRIPS 5` thành số mới (ví dụ `7`)
2. Trong `setup()`, thêm dòng `FastLED.addLeds<>` tương ứng, chỉ định GPIO và chỉ số mảng mới
3. Kiểm tra GPIO mới là GPIO an toàn

### Đổi số LED mỗi thanh

```cpp
#define LEDS_PER_STRIP 3  // Đổi thành số LED thực tế của thanh đèn bạn
```

---

## 🔧 Xử lý lỗi thường gặp

### ❌ Lỗi: Đèn hoàn toàn không sáng

**Nguyên nhân có thể và cách sửa:**
1. **Nguồn 12V chưa có điện** → Kiểm tra điện áp pin, đảm bảo công tắc đang bật
2. **GND không chung mass** → Dùng đồng hồ đo điện trở giữa GND ESP32 và cực âm pin 12V, phải là ~0Ω
3. **Nối sai dây Din** → Xác nhận dây Din đang nối đúng GPIO, không phải VCC hay GND
4. **FastLED chưa cài đúng** → Cài lại thư viện FastLED

### ❌ Lỗi: Đèn sáng nhưng sai màu (hanh vàng nhưng ra xanh hoặc màu khác)

**Nguyên nhân:** Thanh đèn của bạn có thứ tự màu RGB thay vì GRB.

**Cách sửa:** Đổi `GRB` thành `RGB`:
```cpp
FastLED.addLeds<WS2812B, 13, RGB>(leds[0], LEDS_PER_STRIP); // Đổi GRB → RGB
```

### ❌ Lỗi: Cảm biến không phát hiện được người (Serial Monitor không thấy LEN = 0)

**Nguyên nhân có thể và cách sửa:**
1. **Khoảng cách quá xa** → Dùng tua vít vặn biến trở xanh theo chiều kim đồng hồ để giảm khoảng cách cảm biến
2. **VCC đã cắm nhầm 5V** → Chuyển về 3.3V. Nếu đã cắm 5V, GPIO có thể đã hỏng, cần đổi sang chân GPIO khác
3. **Module bị hỏng** → Thử module MH-B khác

### ❌ Lỗi: Đèn nháy loạn hoặc màu không ổn định

**Nguyên nhân có thể và cách sửa:**
1. **Nguồn không ổn định** → Gắn thêm tụ 100µF vào nguồn
2. **Dây quá dài** → Rút ngắn dây Din, hoặc nối tiếp điện trở 300-500Ω vào dây Din (phía ESP32)
3. **Pin yếu** → Sạc hoặc thay pin mới

### ❌ Lỗi: Nạp code thất bại (không tìm thấy ESP32 hoặc timeout)

**Nguyên nhân có thể và cách sửa:**
1. **Chưa cài driver CH340** → Tải và cài driver CH340
2. **GPIO 0 bị kéo xuống** → Kiểm tra không có mạch ngoài nào tác động vào GPIO 0
3. **Dây USB không truyền dữ liệu được** → Đổi dây USB khác có chức năng truyền dữ liệu
4. **Chọn sai cổng COM** → Chọn lại đúng cổng trong Arduino IDE

### ❌ Lỗi: Nạp code xong nhưng Serial Monitor hiển thị ký tự lạ

**Nguyên nhân:** Baud Rate sai.

**Cách sửa:** Góc dưới phải Serial Monitor, chọn **115200** (phải khớp với `Serial.begin(115200)` trong code).

---

## 📖 Lịch sử phát triển

> Dự án này không thành công ngay từ đầu. Đây là toàn bộ hành trình, bao gồm mọi lỗi đã gặp, để bạn có thể tránh đi vào vết xe đổ.

### Phiên bản 1: Arduino Uno + LED thông thường

**Khởi đầu:** Ý tưởng ban đầu rất đơn giản — vài LED thường + cảm biến = đèn cầu thang tự động. Dùng Arduino Uno và LED 5mm thông thường.

**Vấn đề gặp phải:**
- Arduino Uno chỉ có 14 chân digital, kiểm soát 5 dải đèn độc lập tốn hết chân ngay
- LED thường chỉ có bật/tắt, không điều chỉnh màu hay độ sáng được

**Kết luận:** Chọn sai phần cứng, cần nâng cấp.

### Phiên bản 2: Arduino Uno + WS2812B + digitalWrite (thất bại)

**Thử nghiệm:** Chuyển sang WS2812B, thử điều khiển bằng `digitalWrite()` trực tiếp.

**Vấn đề gặp phải:**
- `digitalWrite()` không đủ tốc độ và độ chính xác thời gian cho giao thức NZR của WS2812B
- LED hoặc hoàn toàn không sáng, hoặc nháy loạn sắc màu ngẫu nhiên
- Không thể kiểm soát ổn định được

**Bài học:** WS2812B **bắt buộc** phải dùng thư viện chuyên dụng (FastLED hoặc NeoPixel).

### Phiên bản 3: Arduino Uno + WS2812B + FastLED (hoạt động nhưng có giới hạn)

**Tiến bộ:** Sau khi dùng FastLED, LED cuối cùng điều khiển được ổn định! Màu sắc đúng, hiệu ứng đuổi cũng làm được.

**Vấn đề mới xuất hiện:**
- Bộ nhớ Arduino Uno (SRAM chỉ 2KB) không đủ khi xử lý mảng nhiều thanh đèn, thỉnh thoảng bị crash do tràn bộ nhớ
- Arduino Uno là hệ 5V, một số module cần 3.3V, phải có mạch chuyển đổi điện áp

### Phiên bản 4: ESP32 + WS2812B + FastLED (đấu dây sai — có sự cố nghiêm trọng)

**Nâng cấp:** Chuyển sang ESP32 — bộ nhớ (520KB SRAM) và số lượng chân đã không còn là vấn đề nữa!

**Nhưng lần này mắc các lỗi chết người mới:**

1. **Cháy GPIO 16:** Cắm VCC cảm biến vào 5V, OUT cảm biến xuất 5V vào GPIO ESP32, GPIO 16 bị cháy ngay. ESP32 không còn đọc được cảm biến đi xuống.

2. **Dùng Strapping Pin:** Khi test, đã nối một thanh đèn vào GPIO 12. Kết quả: ESP32 liên tục khởi động lại khi dùng pin, không biết lý do. Mãi sau mới tra tài liệu ra GPIO 12 là Strapping Pin chọn điện áp Flash.

3. **Dùng nhầm GPIO 6:** Do không biết giới hạn của ESP32, đã thử nối vào GPIO 6. Kết quả: ESP32 không nạp được code nữa, tưởng ESP32 đã chết.

**Mỗi lỗi tốn rất nhiều thời gian để tìm ra và xác nhận nguyên nhân.**

### Phiên bản 5 — Phiên bản hiện tại: Chọn GPIO an toàn, chạy ổn định ✅

**Giải pháp cuối cùng:**
- Nghiên cứu kỹ giới hạn GPIO của ESP32, chọn các chân an toàn (13, 14, 16, 26, 27, 32)
- VCC cảm biến chuyển về 3.3V
- Đấu dây GND đầy đủ, chung mass
- Gắn tụ 100µF ổn định nguồn

**Kết quả:** Hệ thống chạy ổn định, hiệu ứng đèn đuổi đẹp, cảm biến nhạy và đáng tin cậy.

---

## 🤝 Đóng góp

Chào mừng tất cả mọi người gửi Pull Request hoặc mở Issue!

1. Fork dự án này
2. Tạo nhánh tính năng: `git checkout -b feature/ten-tinh-nang`
3. Commit thay đổi: `git commit -m 'Thêm tính năng: ...'`
4. Push lên nhánh: `git push origin feature/ten-tinh-nang`
5. Mở Pull Request

### 💡 Hướng đóng góp được chào đón

- [ ] Thêm chức năng điều chỉnh độ sáng
- [ ] Thêm các chế độ màu sắc khác (đuổi cầu vồng, v.v.)
- [ ] Điều khiển từ xa qua Wi-Fi hoặc Bluetooth
- [ ] Tự động hiệu chỉnh phạm vi cảm biến
- [ ] Hiệu ứng tắt mờ dần (fade out)
- [ ] Hỗ trợ thêm nhiều loại LED khác

---

## 📄 Giấy phép

Dự án này sử dụng **MIT License**.

Bạn được tự do sử dụng, sửa đổi, phân phối dự án này, bao gồm mục đích thương mại, với điều kiện giữ lại thông báo giấy phép gốc.

Xem chi tiết tại file [LICENSE](LICENSE).

---

## 🙏 Lời cảm ơn

- **Team FastLED** — Cung cấp thư viện điều khiển LED ổn định và mạnh mẽ, nền tảng của dự án này
- **Espressif Systems** — ESP32 là con chip tuyệt vời, mở rộng vô số khả năng cho người làm đồ tự chế
- **Cộng đồng Arduino** — Tài nguyên hướng dẫn phong phú giúp người mới bắt đầu nhanh chóng
- **Ưu Tín Electronics** — Module cảm biến MH-B chất lượng ổn định, giá cả phải chăng
- Tất cả các lập trình viên trên Stack Overflow và Arduino Forum đã chia sẻ kiến thức về giới hạn GPIO của ESP32 — nhờ các bạn, nhiều người đã tránh được những lỗi tương tự

---

<div align="center">

**⭐ Nếu dự án này có ích cho bạn, hãy để lại một Star trên GitHub nhé! ⭐**

**⭐ 如果這個專題對你有幫助，歡迎給個 Star！⭐**

Made with ❤️ by a hobbyist who burned one too many GPIO pins

</div>
