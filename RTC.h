#ifndef RTC_H
#define RTC_H
#include "RTClib.h"
RTC_DS1307 RTC;

long from1 = 0L;
long to1 = 0L;
long now1 = 0L;

long difference1;
long difference2;

void runRTC() {
  if (! RTC.isrunning()) {
    // following line sets the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
}

DateTime now;

void setTime(short offSet) {

  RTC.adjust(DateTime(now.year(), now.month(), now.day(), (now.hour() + offSet), now.minute(), now.second()));

}

void printTime() {

  now = RTC.now();
  lcd.setCursor(11, 0);

  if ((now.hour()) < 10) {
    lcd.print("0" + (String)(now.hour()));
  }
  else {
    lcd.print((String)(now.hour()));
  }

  lcd.print(":");

  if ((now.minute()) < 10) {
    lcd.print("0" + (String)now.minute());
  }
  else {
    lcd.print((String)now.minute());
  }
}

long toSec(byte FROM_H, byte FROM_M) {

  long a = (long)(FROM_M * 60L + FROM_H * 3600L + 0L);
  return (long)a;
}

#endif
