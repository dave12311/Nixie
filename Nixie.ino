#include "TimeLib.h"
#include "DS1302RTC.h"

DS1302RTC RTC(10,11,12);

TimeElements tm;

int b1, b2;

int timer;

#define wait 10

int Numbers[10][4] = 
{
  {1,0,0,0},  //0
  {0,0,0,0},  //1
  {1,0,0,1},  //2
  {0,0,0,1},  //3
  {1,1,1,0},  //4
  {0,1,1,0},  //5
  {1,0,1,0},  //6
  {0,0,1,0},  //7
  {1,1,0,0},  //8
  {0,1,0,0}   //9
};

void setup() {

  //Serial.begin(9600);

  setTime(12,0,0,8,2,2017);
  
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);

  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
}

void writeNumber(int num, int seg) {

  for(int i = 0;i < 4;i++) {
    digitalWrite(i, LOW);
  }

  delay(1);

  for(int i = 0;i < 4;i++) {
    if(Numbers[num][i] == 1) {
      digitalWrite(i+4, HIGH);
    } else {
      digitalWrite(i+4, LOW);
    }
  }

  delay(1);

  switch(seg) {
    case 1:
      digitalWrite(3, HIGH);
    break;

    case 2:
      digitalWrite(2, HIGH);
    break;

    case 3:
      digitalWrite(1, HIGH);
    break;

    case 4:
      digitalWrite(0, HIGH);
    break;
  }
 
}

void loop() {
  RTC.read(tm);
  
  b1 = digitalRead(8);
  b2 = digitalRead(9);
  
  if (b1 == LOW) {
    if(timer == 0) {
      if(tm.Minute < 60) {
        tm.Minute += 1;
      } else {
        tm.Minute = 0;
        tm.Hour += 1;
      }
      RTC.write(tm);
    }
    timer++;
  } else if (b2 == LOW) {
    if(timer == 0) {
      if(tm.Hour < 24) {
        tm.Hour += 1;
      } else {
        tm.Hour = 0;
      }
      RTC.write(tm);
    }
    timer++;
  } else {
    timer = 0;
  }

  if(timer>wait){timer=0;}

  if(tm.Hour/10 != 0 ) {
    writeNumber(tm.Hour/10,1);
  } else {
    writeNumber(0,0);
  }
  delay(1);
  writeNumber(tm.Hour%10,2);
  delay(1);
  writeNumber(tm.Minute/10,3);
  delay(1);
  writeNumber(tm.Minute%10,4);
  delay(1);
}



