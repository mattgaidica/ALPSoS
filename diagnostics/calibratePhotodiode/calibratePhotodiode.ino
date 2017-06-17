#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const int photoPort = A0; // A0
int photoVal;
long photoValAvg = 0;
int nSamplePhoto = 10;

#define OLED_RESET 4
Adafruit_SSD1306 oled(OLED_RESET);

void setup() {
  pinMode(photoPort, INPUT);
  oled.begin(SSD1306_SWITCHCAPVCC,0x3C);
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(WHITE);
}

void loop() {
  for(int ii=1;ii<=nSamplePhoto;ii++) {
    photoVal = analogRead(photoPort);
    photoValAvg = photoValAvg + photoVal;
    delay(100);
  }
  
  oled.clearDisplay();
  oled.setCursor(0,0);
  oled.println(photoValAvg/nSamplePhoto);
  oled.display();
  photoValAvg = 0;
}
