#include "Statistic.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const bool dodebug = false;

const float alpsos_ver = 1.06;
const float photo_mWcm2_p1 = 0.00844;
const float photo_mWcm2_p2 = 0.14852;

#define VBATPIN A7

#define OLED_RESET 4
Adafruit_SSD1306 oled(OLED_RESET);
static const unsigned char PROGMEM alpsos_logo[] =
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x03, 0xfe, 0x01, 0xf8, 0x03, 0xff, 0x80, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x00, 0x00, 
0x03, 0xfe, 0x01, 0xf8, 0x03, 0xff, 0xe0, 0x1f, 0xf8, 0x00, 0x00, 0x00, 0x1f, 0xf8, 0x00, 0x00, 
0x03, 0xfe, 0x01, 0xf8, 0x03, 0xff, 0xe0, 0x3f, 0xfc, 0x00, 0x00, 0x00, 0x3f, 0xfc, 0x00, 0x00, 
0x03, 0xfe, 0x01, 0xf8, 0x03, 0xff, 0xf0, 0x7f, 0xfe, 0x00, 0x00, 0x00, 0x7f, 0xfe, 0x00, 0x00, 
0x07, 0xff, 0x01, 0xf8, 0x03, 0xf3, 0xf0, 0x7e, 0x7e, 0x00, 0x3f, 0x00, 0x7e, 0x7e, 0x00, 0x00, 
0x07, 0xdf, 0x01, 0xf8, 0x03, 0xf3, 0xf0, 0x7e, 0x7e, 0x00, 0xff, 0xc0, 0x7e, 0x7e, 0x00, 0x00, 
0x07, 0xdf, 0x01, 0xf8, 0x03, 0xf3, 0xf0, 0x7e, 0x7e, 0x01, 0xff, 0xe0, 0x7e, 0x7e, 0x00, 0x00, 
0x07, 0xdf, 0x01, 0xf8, 0x03, 0xf3, 0xf0, 0x7e, 0x7e, 0x01, 0xff, 0xe0, 0x7e, 0x7e, 0x00, 0x00, 
0x07, 0xdf, 0x01, 0xf8, 0x03, 0xf3, 0xf0, 0x7f, 0x80, 0x03, 0xf3, 0xf0, 0x7f, 0x80, 0x00, 0x00, 
0x07, 0xdf, 0x01, 0xf8, 0x03, 0xf3, 0xf0, 0x7f, 0xc0, 0x03, 0xf3, 0xf0, 0x7f, 0xc0, 0x00, 0x00, 
0x0f, 0xdf, 0x81, 0xf8, 0x03, 0xf3, 0xf0, 0x3f, 0xf0, 0x03, 0xf3, 0xf0, 0x3f, 0xf0, 0x00, 0x00, 
0x0f, 0x8f, 0x81, 0xf8, 0x03, 0xff, 0xf0, 0x1f, 0xf8, 0x03, 0xf3, 0xf0, 0x1f, 0xf8, 0x00, 0x00, 
0x0f, 0x8f, 0x81, 0xf8, 0x03, 0xff, 0xf0, 0x0f, 0xfc, 0x03, 0xd3, 0xf0, 0x0f, 0xfc, 0x00, 0x00, 
0x0f, 0x8f, 0x81, 0xf8, 0x03, 0xff, 0xe0, 0x07, 0xfe, 0x1f, 0xf3, 0xf0, 0x07, 0xfe, 0x00, 0x00, 
0x0f, 0x8f, 0x81, 0xf8, 0x03, 0xff, 0x80, 0x01, 0xff, 0x81, 0xfb, 0xf0, 0x01, 0xfe, 0x00, 0xf0, 
0x0f, 0x8f, 0x81, 0xf8, 0x03, 0xf0, 0x00, 0x00, 0xfe, 0x01, 0xfd, 0xf0, 0x00, 0xff, 0x07, 0xf8, 
0x1f, 0xff, 0xc1, 0xf8, 0x03, 0xf0, 0x00, 0x7e, 0x38, 0x00, 0xff, 0xf0, 0x7e, 0x3f, 0x1c, 0x7c, 
0x1f, 0xff, 0xc1, 0xf8, 0x03, 0xf0, 0x00, 0x7e, 0x20, 0x00, 0xff, 0xf0, 0x7e, 0x3e, 0x70, 0x3f, 
0x1f, 0xff, 0xc1, 0xf8, 0x03, 0xf0, 0x00, 0x7f, 0x80, 0x03, 0xfb, 0xfc, 0x7e, 0x3b, 0x81, 0xff, 
0x1f, 0xff, 0xc1, 0xf8, 0x03, 0xf0, 0x00, 0x7f, 0x00, 0x03, 0xf3, 0xfe, 0x7e, 0x2e, 0x03, 0xff, 
0x1f, 0x07, 0xc1, 0xff, 0x83, 0xf0, 0x00, 0x7c, 0x00, 0x00, 0x73, 0xff, 0xde, 0x38, 0x03, 0xff, 
0x1f, 0x07, 0xc1, 0xff, 0x83, 0xe0, 0x00, 0x30, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xe0, 0x03, 0xff, 
0x3f, 0x07, 0xe1, 0xff, 0x83, 0xdc, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x3f, 0xfc, 0x00, 0x01, 0xff, 
0x3f, 0x07, 0xe1, 0xff, 0x83, 0xbe, 0x07, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xf0, 0x00, 0x00, 0xff, 
0x3f, 0x07, 0xe1, 0xff, 0x82, 0xef, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x07, 0x7c, 0x00, 0x00, 0x7f, 
0x00, 0x00, 0x00, 0x00, 0x01, 0x83, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x03, 0xbf, 0x00, 0x00, 0x7f, 
0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc7, 0xe0, 0x00, 0x3f, 
0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x3f, 0x80, 0x00, 0x00, 0x00, 0x01, 0xe1, 0xf0, 0x00, 0x3f};

// global IO vars
const int photoPort = A0; // A0
const int flickrPort = 11;
const int indicatorPort = 13;
const int redBtnPort = 12; // has external pullup
const int greenBtnPort = 5;
int photoVal;

// global experimental vars
float startFreq = 25.0;
float endFreq = 60.0;
float freqInc = 0.25;

// startup loop
int updateBattery_ms = 1000; // 1 s
long updateBattery_ms_last = 0;
int readPhoto_ms = 250; // .25 s
long readPhoto_ms_last = 0;
int flickrFade_ms = 10; //
long flickrFade_ms_last = 0;
long changeMode_ms_last = 0;
bool fadeDir = true;
int count = 0; // *** rename

// modes
const int totalModes = 2;
const int defaultMode = 1;
int curMode = defaultMode;
char* modeNames[]={"Asc Desc", "Flickering?"};

void setup() {
  pinMode(photoPort, INPUT);
  pinMode(flickrPort, OUTPUT);
  pinMode(redBtnPort, INPUT_PULLUP);
  pinMode(greenBtnPort, INPUT_PULLUP);
  pinMode(VBATPIN, INPUT);
  
  analogWrite(flickrPort,255);
  
  oled.begin(SSD1306_SWITCHCAPVCC,0x3C);
  oled.clearDisplay();
  oled.drawBitmap(0,0,alpsos_logo,128,32,1);
  oled.display();
  delay(2000);
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(WHITE);
  oled.setCursor(0,0);
  oled.print("ALPSoS ver");
  oled.println(alpsos_ver);
  oled.println("Matt Gaidica");
  oled.println("matt@gaidi.ca");
  oled.println("Univ. of Michigan");
  oled.display();
  delay(2000);

  if(dodebug == true) {
    Serial.begin(19200);
    Serial.println("Initialized");
  }
}

void loop() {
  unsigned long cur_ms = millis();
  if (cur_ms - readPhoto_ms >= readPhoto_ms_last) {
    photoVal = analogRead(photoPort);
    readPhoto_ms_last = 0;
  }
  if (cur_ms - flickrFade_ms_last >= flickrFade_ms) {
    analogWrite(flickrPort,count);
    if (fadeDir) {
      count += 2;
    } else {
      count -= 2;
    }
    if (count > 254 || count < 1) {
      fadeDir = !fadeDir;
    }
    flickrFade_ms_last = cur_ms;
  }

  if (cur_ms - updateBattery_ms_last >= updateBattery_ms) {
    oled.clearDisplay();
    printBattery();
    oled.setCursor(0,0);
    print_mode(curMode);
    oled.println("GREEN => Start");
    oled.println("RED => Mode");
    print_photoVals();
    oled.display();
    updateBattery_ms_last = cur_ms;
  }

  if (!digitalRead(greenBtnPort)) {
    pinMode(flickrPort, OUTPUT);
    digitalWrite(flickrPort,LOW);
    switch (curMode) {
      case 1:
        ascDesc();
        break;
      case 2:
        isFlickering();
        break;
      default:
        break;
    }
    
  }
  if (!digitalRead(redBtnPort) && (cur_ms - changeMode_ms_last) > 300) {
    curMode++;
    if(curMode > totalModes) {
      curMode = 1;
    }
    updateBattery_ms_last = 0;
    changeMode_ms_last = cur_ms;;
  }
}

void print_mode(int modeNum) {
  oled.print("M");
  oled.print(modeNum);
  oled.print(". ");
  oled.println(modeNames[modeNum-1]); // zero-indexed
}

void print_photoVals() {
  oled.print("AD: ");
  oled.print(photoVal);
  oled.print(", mW/cm2:");
  oled.println(convert_photoVal(photoVal));
  return;
}

float convert_photoVal(float photoVal) {
  float photoVal_mWcm2 = photoVal * photo_mWcm2_p1 + photo_mWcm2_p2;
  return photoVal_mWcm2;
}

void printBattery() {
  float vbat = getBatteryVoltage();
  oled.setCursor(98,0);
  oled.print(vbat);
  oled.print("V");
  return;
}

float getBatteryVoltage() {
  float measuredvbat = analogRead(VBATPIN);
  measuredvbat *= 2;    // we divided by 2, so multiply back
  measuredvbat *= 3.3;  // Multiply by 3.3V, our reference voltage
  measuredvbat /= 1024; // convert to voltage
  return measuredvbat;
}

// Mode 1
void ascDesc() {
  digitalWrite(flickrPort,false);
  showStarting();
  bool runningExp = true;
  bool freqDir = true;
  bool ledState = true;
  int curSample = 0;
  
  // --- these must be the same size
  int requireSamples = 3;
  float ascFreqs[] = {0.0, 0.0, 0.0};
  float descFreqs[] = {0.0, 0.0, 0.0};
  // ---
  
  float curFreq = startFreq;
  int curDelay_ms = 1000 / curFreq;
  int incDelay_ms = 200;
  
  unsigned long lastFreqUpdate_ms = millis();
  unsigned long lastFlicker_ms = millis();
  oled.clearDisplay();
  oled.setCursor(0,0);
  oled.print("Trial ");
  oled.print(curSample+1);
  oled.print("/");
  oled.print(requireSamples);
  oled.print(", freq:");
  oled.println(curFreq);
  oled.println("Ascending Light");
  oled.println(">>press GREEN when");
  oled.println(">>light is constant.");
  oled.display();
  while(runningExp) {
    unsigned long cur_ms = millis();
    // make light flicker
    if (cur_ms - lastFlicker_ms >= curDelay_ms / 2) {
      if (ledState == true) {
        digitalWrite(flickrPort,HIGH);
        ledState = false;
      } else {
        digitalWrite(flickrPort,LOW);
        ledState = true;
      }
      lastFlicker_ms = cur_ms;
    }
    // handle inc/dec of freq
    if (cur_ms - lastFreqUpdate_ms >= incDelay_ms) {
      if (freqDir == true) {
        curFreq = curFreq + freqInc;
        if (curFreq > endFreq) {
          curFreq = startFreq;
          delay(1000);
        }
      } else {
        curFreq = curFreq - freqInc;
        if (curFreq < startFreq) {
          curFreq = endFreq;
          delay(1000);
        }
      }
      curDelay_ms = 1000 / curFreq;
      lastFreqUpdate_ms = cur_ms;
    }
    if (!digitalRead(greenBtnPort)) {
      digitalWrite(flickrPort,LOW);
      if (freqDir == true) {
        ascFreqs[curSample] = curFreq;
        if(dodebug == true) {
          Serial.print(curSample); Serial.print(": "); Serial.println(curFreq);
        }
        freqDir = false;
        oled.clearDisplay();
        oled.setCursor(0,0);
        oled.print("Trial ");
        oled.print(curSample+1);
        oled.print("/");
        oled.print(requireSamples);
        oled.print(", freq:");
        oled.println(curFreq);
        oled.println("Descending Light");
        oled.println(">>press GREEN when");
        oled.println(">>light is flickering");
        oled.display();
        curFreq = endFreq + freqInc;
      } else {
        descFreqs[curSample] = curFreq;
        if(dodebug == true) {
          Serial.print(curSample); Serial.print(": "); Serial.println(curFreq);
        }
        freqDir = true;
        curSample++;
        oled.clearDisplay();
        oled.setCursor(0,0);
        oled.print("Trial ");
        oled.print(curSample+1);
        oled.print("/");
        oled.print(requireSamples);
        oled.print(", freq:");
        oled.println(curFreq);
        oled.println("Ascending Light");
        oled.println(">>press GREEN when");
        oled.println(">>light is constant");
        oled.display();
        curFreq = startFreq - freqInc;
      }
      if (curSample == requireSamples) {
        runningExp = false;
      } else {
        delay(1000);
      }
    }
  }
  showResults(ascFreqs,descFreqs,requireSamples);
}

void showResults(float ascFreqs[],float descFreqs[],int n) {
  Statistic ascStats;
  ascStats.clear();
  for (int ii = 0; ii < n; ii++) {
    ascStats.add(ascFreqs[ii]);
    if(dodebug == true) {
      Serial.println(ascFreqs[ii]);
    }
  }
  oled.clearDisplay();
  oled.setCursor(0,0);
  oled.print("ASC: ");
  oled.print(ascStats.average());
  oled.print(" +/- ");
  oled.println(ascStats.pop_stdev());
  Serial.println("");
  Statistic descStats;
  descStats.clear();
  for (int ii = 0; ii < n; ii++) {
    descStats.add(descFreqs[ii]);
    if(dodebug == true) {
      Serial.println(descFreqs[ii]);
    }
  }
  oled.print("DES: ");
  oled.print(descStats.average());
  oled.print(" +/- ");
  oled.println(descStats.pop_stdev());

  Statistic allStats;
  allStats.clear();
  for (int ii = 0; ii < n; ii++) {
    allStats.add(ascFreqs[ii]);
  }
  for (int ii = 0; ii < n; ii++) {
    allStats.add(descFreqs[ii]);
  }
  oled.print("ALL: ");
  oled.print(allStats.average());
  oled.print(" +/- ");
  oled.println(allStats.pop_stdev());

  photoVal = analogRead(photoPort);
  print_photoVals();
  
  oled.display();

  bool doLoop = true;
  while (doLoop) {
    if (!digitalRead(redBtnPort)) {
      doLoop = false;
      showExiting();
    }
  }
}

// Mode 2
void isFlickering() {
  showStarting();

  bool runningExp = true;
  bool ledState = false;
  bool curState = true; // isFlickering?
  int requireSamples = 3;
  long lastFlicker_ms = 0;
  float curFreq = 0;
  int curSample = 0;
  int curDelay_ms = 0;
  
  if (random(0,1) == 0) {
    curFreq = random(startFreq*100,endFreq*100) / 100;
    curState = true;
  } else {
    curFreq = endFreq; // use end or force constant on?
    curState = false;
  }
  curDelay_ms = 1000 / curFreq;

  isFlickeringDisplay(curSample);
  while(runningExp) {
    unsigned long cur_ms = millis();
    // make light flicker
    if (cur_ms - lastFlicker_ms >= curDelay_ms / 2) {
      if (ledState == true) {
        digitalWrite(flickrPort,HIGH);
        ledState = false;
      } else {
        digitalWrite(flickrPort,LOW);
        ledState = true;
      }
      lastFlicker_ms = cur_ms;
    }
    if (!digitalRead(greenBtnPort)) {
      digitalWrite(flickrPort,LOW);
      curSample++;
      isFlickeringDisplay(curSample);
      if (random(0,1) == 0) {
        curFreq = random(startFreq*100,endFreq*100) / 100;
        curState = true;
      } else {
        curFreq = endFreq; // use end or force constant on?
        curState = false;
      }
      curDelay_ms = 1000 / curFreq;
      delay(1000);
    }
    if (!digitalRead(redBtnPort)) {
      runningExp = false;
    }
  }
  showExiting();
}

void isFlickeringDisplay(int curSample) {
  oled.clearDisplay();
  oled.setCursor(0,0);
  oled.println("Green => Flickering");
  oled.println("Red => Solid");
  oled.println(curSample);
  oled.display();
}

// Mode helpers
void showStarting() {
  for(int ii=3; ii > 0; ii--) {
    oled.clearDisplay();
    oled.setCursor(0,0);
    oled.print("Starting in ");
    oled.print(ii);
    oled.print("...");
    oled.display();
    delay(1000);
  }
}

void showExiting() {
  oled.clearDisplay();
  oled.setCursor(0,0);
  oled.print("Exiting...");
  oled.display();
  delay(1000);
  return;
}

