#include <LiquidCrystal.h>

// Konfigurasi pin LCD: (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Struktur data untuk lirik
struct Lyric {
  const char* text;
  unsigned long startDelay; // dalam ms
  unsigned long charDelay;  // delay per karakter (ms)
};

// Lirik lagu "Tante..."
Lyric lyrics[] = {
  {"tante...",                 300,   80},
  {"sudah terbiasa terjadi tante", 2500, 90},
  {"teman datang ketika lagi butuh saja", 5800, 80},
  {"coba kalau lagi susah",   9500,  150},
  {"mereka semua menghilaaaaang", 13500, 150}
};

const int totalLyrics = sizeof(lyrics) / sizeof(lyrics[0]);

void typeText(const char* text, unsigned long charDelay) {
  lcd.clear();
  lcd.setCursor(0, 0);
  int col = 0;
  int row = 0;

  for (int i = 0; text[i] != '\0'; i++) {
    lcd.print(text[i]);
    col++;
    // Pindah ke baris kedua jika penuh baris pertama
    if (col >= 16) {
      col = 0;
      row++;
      if (row > 1) break; // LCD 16x2, jadi maksimal 2 baris
      lcd.setCursor(col, row);
    }
    delay(charDelay);
  }
}

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Mulai nyanyi...");
  delay(2000);
  lcd.clear();

  unsigned long lastTime = millis();

  for (int i = 0; i < totalLyrics; i++) {
    unsigned long currentTime = millis();
    unsigned long targetTime = lastTime + lyrics[i].startDelay;

    // Tunggu hingga waktu startDelay tercapai
    while (millis() < targetTime) {
      // tidak melakukan apa-apa, menunggu
    }

    typeText(lyrics[i].text, lyrics[i].charDelay);
    lastTime = targetTime;
  }

  lcd.clear();
  lcd.print("Selesai 🎶");
}

void loop() {
  // Tidak perlu loop lagi, cukup sekali
}
