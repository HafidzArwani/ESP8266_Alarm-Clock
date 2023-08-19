#include <ESP8266WiFi.h>
#include <LCD_I2C.h>

#include "AudioFileSourceSPIFFS.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2SNoDAC.h"

#define NTP_SERVER     "ntp.bsn.go.id"
#define UTC_OFFSET     25200
#define UTC_OFFSET_DST 0

LCD_I2C lcd(0x27, 16, 2);
AudioGeneratorMP3 *mp3 = NULL;
AudioFileSourceSPIFFS *file = NULL;
AudioOutputI2SNoDAC *out = NULL;

bool alarm = false;
const char* sound = "";

void disp() {
  struct tm *timeinfo;
  time_t      rawtime;
  time     (&rawtime);
  timeinfo = localtime(&rawtime);

  static uint8_t menits;
  //  uint8_t hari  = timeinfo->tm_wday;
  uint8_t jam   = timeinfo->tm_hour;
  uint8_t menit = timeinfo->tm_min;

  char buffer[20];
  char date[20];

  if (timeinfo->tm_year == 70) return;
  if (menits == menit) return;

  strftime(buffer, 20, "  %I:%M %p  ", timeinfo);
  strftime(date, 20, "%a, %e %b %g", timeinfo);

  lcd.setCursor(0, 0);
  lcd.print("\x2d\x7e");
  lcd.print(buffer);
  lcd.print("\x7f\x2d");
  lcd.setCursor(1, 1);
  lcd.print(date);

  menits = menit;

  if (jam == 13 && menit == 40)
  alarm = true;
}

void spinner() {
  static int8_t counter = 0;
  const char* glyphs = "\xa1\xa5\xdf";
  lcd.setCursor(15, 1);
  lcd.write(glyphs[counter++]);
  if (counter == strlen(glyphs)) {
    counter = 0;
  }
}

void setup() {
  Serial.begin(115200);
  SPIFFS.begin();
  WiFi.begin("Kos Rendang", "assalamualaikum");

  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Connecting to ");
  lcd.setCursor(0, 1);
  lcd.print("WiFi ");

  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    spinner();
  }
  lcd.clear();
  configTime(UTC_OFFSET, UTC_OFFSET_DST, NTP_SERVER);

  audioLogger = &Serial;
  file = new AudioFileSourceSPIFFS("/tangi.mp3");
  out = new AudioOutputI2SNoDAC();
  mp3 = new AudioGeneratorMP3();
}

void loop() {
  disp();
  if (alarm)
    mp3->begin(file, out);

  stopPlay();
}

void stopPlay() {
  if (mp3->isRunning())
    if (!mp3->loop())
      mp3->stop();
  alarm = false;
}
