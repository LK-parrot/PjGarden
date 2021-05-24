//arduino nano AtMega328p old bootloader

#include "Button.h"
#include "Valve.h"
#include "RTC.h"

//const byte smallPump = 7;
//const byte pump = 8;

short offSet = 0;
short choice = 0;

boolean OK;

struct valve valves_array[4];
struct valve *valves;

byte i, j;

void setup() {

  valves = valves_array;

  pinMode(13, OUTPUT); digitalWrite(13, 0);

  lcd.init();
  Wire.begin();
  RTC.begin();

  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  
  runRTC();

  printLcd("N. Valvole [1-4]", 0, 0);
  lcd.setCursor(0, 1);
  lcd.print("Value-> ");
  lcd.setCursor(8, 1);
  lcd.print(valves_number);

  setNumberValves();

  for (j = 0; j < valves_number; j++) { //Inizializzo valvola per valvola e le ciascune fasce

    initValve(valves, j);

    askBounds(valves, j); //chiedo quante fasce orarie creare

    for ( i = 0; i < valves->time_slots; i++) { //inizializzo le fasce interessate

      initBound(valves, i);

    }

    String sentence;

    for ( i = 0; i < valves->time_slots; i++) {

      //chiedo ed imposto gli orari delle fasce dichiarate iniziali

      sentence = "H iniz per V" + (String)j + " F" + (String)i;///impostare ore iniziali
      setHour(&(valves->bounds[i].fromH), sentence);

      sentence = "M iniz per V" + (String)j + " F" + (String)i;///impostare minuti iniziali
      setMinute(&(valves->bounds[i].fromM), sentence);

      //Setto gli orari finali

      sentence = "H fin per V" + (String)j + " F" + (String)i;///impostare ore finali
      setHour(&(valves->bounds[i].toH), sentence);


      sentence = "M fin per V" + (String)j + " F" + (String)i;///impostare minuti finali
      setMinute(&(valves->bounds[i].toM), sentence);

    }

    valves++;

  }

  //fine inizializzazione di ogni valvola

  for ( i = 0; i < valves_number; i++) { //riporto l'array delle valvole all'indice 0
    valves--;
  }

  //reinizializzato array valvole e pronto per essere riutilizzato
  lcd.clear();

}


//###################################################################################################################################################################


void loop() {
  OK = true;

  switch (choice) {

    case 0:

      printTime();

      for ( i = 0; i < valves_number; i++) {

        valves -> gate = false;
        valves++;

      }

      for ( i = 0; i < valves_number; i++) {

        valves--;

      }

      for ( i = 0; i < valves_number; i++) {

        for ( j = 0; j < valves->time_slots; j++) {

          if (difference(valves, j)) {

            valves->gate = true;

            lcd.setCursor(0, 0);
            lcd.print("RUNNING...");

          }

        }
        if (valves->gate) {
          if (!isOpen(valves)) {
            openValve(valves);
          }
        }
        else {
          if (isOpen(valves)) {
            closeValve(valves);
            lcd.clear();
          }
        }

        valves++;
      }
      for ( i = 0; i < valves_number; i++) {

        valves--;

      }

      break;

    case 1:

      printLcd("MENU", 0, 0);
      //inizio menu
      lcd.setCursor(0, 1);
      lcd.print("<--          -->");

      while (OK) {
        delay(300);
        if (buttonMenu()) {
          choice = 40;
          OK = false;
        }
        else if (buttonRight()) {
          choice = 10;
          OK = false;
        }
        else if (buttonLeft()) {
          choice = 40;
          OK = false;
        }
      }
      break;

    case 10:
      printLcd("MENU", 0, 0);
      //"Ora legale";
      lcd.setCursor(0, 1);
      lcd.print("                ");
      lcd.setCursor(0, 1);
      lcd.print("+- ora");
      while (OK) {
        if (buttonMenu()) {
          choice = 300;
          OK = false;
        }
        else if (buttonLeft()) {
          choice = 40;
          OK = false;
        }
        else if (buttonRight()) {
          choice = 20;
          OK = false;
        }
        delay(BUTTON_DELAY);
      }
      break;

    case 20:
      printLcd("MENU", 0, 0);
      //Mod. manuale?
      lcd.setCursor(0, 1);
      lcd.print("                ");
      lcd.setCursor(0, 1);
      lcd.print("Mod. manuale?");

      while (OK) {
        if (buttonMenu()) {
          choice = 200;
          OK = false;
        }
        else if (buttonLeft()) {
          choice = 10;
          OK = false;
        }
        else if (buttonRight()) {
          choice = 30;
          OK = false;
        }

        delay(250);

      }
      break;

    case 30:
      printLcd("MENU", 0, 0);
      //Mod. valv./fasc.
      lcd.setCursor(0, 1);
      lcd.print("                ");
      lcd.setCursor(0, 1);
      lcd.print("Mod. valv./fasc.");
      while (OK) {
        if (buttonMenu()) {
          setup();
          OK = false;
        }
        else if (buttonRight()) {
          choice = 40;
          OK = false;
        }
        else if (buttonLeft()) {
          choice = 20;
          OK = false;
        }
        delay(BUTTON_DELAY);
      }
      break;

    case 40:
      printLcd("MENU", 0, 0);
      //"EXIT"
      lcd.setCursor(0, 1);
      lcd.print("                ");
      lcd.setCursor(0, 1);
      lcd.print("OK per uscire");
      while (OK) {
        if (buttonMenu()) {
          choice = 0;
          OK = false;
        }
        else if (buttonRight()) {
          choice = 10;
          OK = false;
        }
        else if (buttonLeft()) {
          choice = 30;
          OK = false;
        }
        delay(250);
      }
      lcd.clear();
      break;

    case 200:

      currentValve = 0;

      lcd.setCursor(0, 1);
      lcd.print("                ");
      lcd.setCursor(0, 1);
      lcd.print("Valv. " + (String)currentValve);
      lcd.setCursor(8, 1);
      lcd.print("    ");
      lcd.setCursor(8, 1);
      if (isOpen(valves)) lcd.print(F("ON")); else lcd.print(F("OFF"));

      while (OK) {

        if (buttonRight() && (currentValve < (valves_number - 1))) {

          lcd.setCursor(6, 1);
          lcd.print((String)(++currentValve));
          lcd.setCursor(8, 1);
          lcd.print("    ");
          lcd.setCursor(8, 1);
          valves++;
          if (isOpen(valves)) lcd.print(F("ON")); else lcd.print(F("OFF"));
        }
        else if (buttonLeft() && (currentValve > 0)) {

          lcd.setCursor(6, 1);
          lcd.print((String)(--currentValve));
          lcd.setCursor(8, 1);
          lcd.print("    ");
          lcd.setCursor(8, 1);
          valves--;
          if (isOpen(valves)) lcd.print(F("ON")); else lcd.print(F("OFF"));
        }

        else if (buttonUp()) {
          lcd.setCursor(8, 1);
          openValve(valves);
          lcd.print("    ");
          lcd.setCursor(8, 1);
          if (isOpen(valves)) lcd.print(F("ON")); else lcd.print(F("OFF"));
        }
        else if (buttonDown()) {
          lcd.setCursor(8, 1);
          closeValve(valves);
          lcd.print("    ");
          lcd.setCursor(8, 1);
          if (isOpen(valves)) lcd.print(F("ON")); else lcd.print(F("OFF"));
        }
        else if (buttonMenu()) {
          OK = false;
          choice = 1;
          for (i = 0; i < currentValve; i++) {
            valves--;
          }
        }
        delay(250);
      }
      break;

    case 300:

      lcd.setCursor(0, 1);
      lcd.print("                ");
      lcd.setCursor(0, 1);
      lcd.print("Offset:" );
      lcd.setCursor(8, 1);
      lcd.print("    ");
      lcd.setCursor(8, 1);
      lcd.print((String)offSet);

      while (OK) {

        if (buttonUp() && (offSet < 3)) {
          lcd.setCursor(8, 1);
          lcd.print("    ");
          lcd.setCursor(8, 1);
          lcd.print((String)(++offSet));
        }
        else if (buttonDown() && (offSet > -3)) {
          lcd.setCursor(8, 1);
          lcd.print("    ");
          lcd.setCursor(8, 1);
          lcd.print((String)(--offSet));
        }
        else if (buttonMenu()) {
          OK = false;
          setTime(offSet);
          choice = 1;
        }
        delay(BUTTON_DELAY);
      }

      break;



  }//fine switch

  delay(BUTTON_DELAY);

  if (buttonMenu())
    choice = 1;

}
