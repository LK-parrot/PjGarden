#include "Bounds.h"
#include "Button.h"
#include "LCD.h"
#include "RTC.h"
#ifndef VALVE_H
#define VALVE_H

const byte MAX_VALVE = 4;
const byte MAX_BOUNDS = 3;

struct valve {
  byte pin;
  boolean isOpened;
  boolean gate;
  byte time_slots;
  struct bound bounds[3];
};

byte valves_number = 1;
byte currentValve;

void initBound(struct valve *valves, byte index) {

  valves->bounds[index].fromH = 0;
  valves->bounds[index].fromM = 0;
  valves->bounds[index].toH = 0;
  valves->bounds[index].toM = 0;

}

void askBounds(struct valve *valve, byte number) {
  valve -> time_slots = 1;
  String frase = "Orari V" + (String)number + " [1-3]";
  printLcd(frase, 0, 0);
  lcd.setCursor(0, 1);
  lcd.print("Value-> ");
  lcd.setCursor(8, 1);
  lcd.print(valve->time_slots);

  while (!buttonMenu()) {

    lcd.setCursor(8, 1);
    if (buttonUp()) {
      if ((valve->time_slots + 1) > MAX_BOUNDS)
        lcd.print(MAX_BOUNDS);
      else
        lcd.print(++(valve->time_slots));
    }
    else if (buttonDown()) {
      if ((valve->time_slots - 1) < 1)
        lcd.print(1);
      else
        lcd.print(--(valve->time_slots));
    }

    delay(BUTTON_DELAY);
  }
  delay(BUTTON_DELAY);
}

void setNumberValves() {
  while (!buttonMenu()) {
    lcd.setCursor(8, 1);
    if (buttonUp()) {
      if ((valves_number + 1) > MAX_VALVE)
        lcd.print(MAX_VALVE);
      else
        lcd.print(++valves_number);
    }
    else if (buttonDown()) {
      if ((valves_number - 1) < 1)
        lcd.print(1);
      else
        lcd.print(--valves_number);
    }
    delay(BUTTON_DELAY);
  }

  delay(BUTTON_DELAY);
}



void closeValve(struct valve *valve) {
  digitalWrite(valve-> pin, 1);
  valve->isOpened = false;
}
void openValve(struct valve *valve) {
  digitalWrite(valve-> pin, 0);
  valve->isOpened = true;
}

boolean isOpen(struct valve *valve) {
  return valve -> isOpened;
}

void initValve(struct valve *valve, byte slot) {
  valve -> pin = slot + 5;//setto pin della valvola(v0 corrisponde al pin 5)
  pinMode(valve->pin, OUTPUT);//inizializzo la valvola
  closeValve(valve);//chiudo la valvola e setto lo stato a chiuso
}

boolean difference(struct valve *valve, byte j) {

  now = RTC.now();

  from1 = toSec(valve->bounds[j].fromH, valve->bounds[j].fromM);
  now1 = toSec((byte)(now.hour()), (byte)now.minute());
  to1 = toSec(valve->bounds[j].toH, valve->bounds[j].toM);

  difference1 = (from1 - now1);
  difference2 = (now1 - to1);

  return (difference1 <= 0) && (difference2 < 0);

}

setHour(byte *hour, String text) {

  printLcd(text, 0, 0);
  lcd.setCursor(0, 1);
  lcd.print("Value-> ");
  lcd.setCursor(8, 1);
  lcd.print((String)(*hour));

  while (!buttonMenu()) {
    lcd.setCursor(8, 1);
    if (buttonUp()) {
      if ((*hour + 1) > 23) {
        lcd.print(23);
        *hour = 23;
      }
      else {
        ++(*hour);
        if (*hour < 10) {
          lcd.print("0" + (String)(*hour));
        }
        else {
          lcd.print((String)(*hour));
        }
      }
    }
    else if (buttonDown()) {
      if ((*hour - 1) < 0) {
        lcd.print(0);
        *hour = 0;
      }
      else {
        --(*hour);
        if (*hour < 10) {
          lcd.print("0" + (String)(*hour));
        }
        else {
          lcd.print((String)(*hour));
        }
      }
    }
    else if (buttonRight()) {
      if ((*hour - 1) > 13) {
        lcd.print("00");
        *hour = 0;
      }
      else {
        *hour += 10;
        if (*hour < 10) {
          lcd.print("0" + (String)(*hour));
        }
        else {
          lcd.print((String)(*hour));
        }
      }
    }
    else if (buttonLeft()) {
      if ((*hour - 1) < 10) {
        lcd.print("00");
        *hour = 0;
      }
      else {
        *hour -= 10;
        if (*hour < 10) {
          lcd.print("0" + (String)(*hour));
        }
        else {
          lcd.print((String)(*hour));
        }
      }
    }
    delay(BUTTON_DELAY);
  }
  delay(BUTTON_DELAY);

}

setMinute(byte *minute, String text) {
  printLcd(text, 0, 0);
  lcd.setCursor(0, 1);
  lcd.print("Value-> ");
  lcd.setCursor(8, 1);
  lcd.print(*minute);

  while (!buttonMenu()) {
    lcd.setCursor(8, 1);
    if (buttonUp()) {
      if ((*minute + 1) > 59) {
        lcd.print(59);
      }
      else {
        ++(*minute);
        if (*minute < 10) {
          lcd.print("0" + (String)(*minute));
        }
        else {
          lcd.print((String)(*minute));
        }
      }
    }
    else if (buttonDown()) {
      if ((*minute - 1) < 0) {
        lcd.print(0);
      }
      else {
        --(*minute);
        if (*minute < 10) {
          lcd.print("0" + (String)(*minute));
        }
        else {
          lcd.print((String)(*minute));
        }
      }
    }
    else if (buttonRight()) {
      if ((*minute - 1) > 48) {
        lcd.print("00");
        *minute = 0;
      }
      else {
        *minute += 10;
        if (*minute < 10) {
          lcd.print("0" + (String)(*minute));
        }
        else {
          lcd.print((String)(*minute));
        }
      }
    }
    else if (buttonLeft()) {
      if ((*minute - 1) < 10) {
        lcd.print("00");
        *minute = 0;
      }
      else {
        *minute -= 10;
        if (*minute < 10) {
          lcd.print("0" + (String)(*minute));
        }
        else {
          lcd.print((String)(*minute));
        }
      }
    }
    delay(BUTTON_DELAY);
  }
  delay(BUTTON_DELAY);
}

#endif
