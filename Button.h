#ifndef BUTTON_H
#define BUTTON_H
#define BUTTONS_PIN A0


const int BUTTON_DELAY = 200;

boolean buttonMenu() {
  if ((analogRead(BUTTONS_PIN) <= (553 + 10)) && (analogRead(BUTTONS_PIN) >= (553 - 10)))
    return true;
  else
    return false;
}

boolean buttonUp() {
  if ((analogRead(BUTTONS_PIN) <= (243 + 10)) && (analogRead(BUTTONS_PIN) >= (243 - 10)))
    return true;
  else
    return false;
}

boolean buttonDown() {
  if ((analogRead(BUTTONS_PIN) <= (347 + 10)) && (analogRead(BUTTONS_PIN) >= (347 - 10)))
    return true;
  else
    return false;
}

boolean buttonLeft() {
  if ((analogRead(BUTTONS_PIN) <= (111 + 10)) && (analogRead(BUTTONS_PIN) >= (111 - 10)))
    return true;
  else
    return false;
}

boolean buttonRight() {
  if ((analogRead(BUTTONS_PIN) <= (174 + 10)) && (analogRead(BUTTONS_PIN) >= (174 - 10)))
    return true;
  else
    return false;
}

#endif
