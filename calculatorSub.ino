#include <Keypad.h>
#include <Key.h>

#include <LiquidCrystal.h>
LiquidCrystal lcd(2, 3, A0, A1, A2, A3, A4);
const byte rows = 4;
const byte cols = 4;
char keys[rows][cols] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[rows] = {5, 6, 7, 8};
byte colPins[cols] = {9, 10, 11, 12};
char lastCorrect = 1;
char lastSign = '+';
Keypad bobokey = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);

int strike = 0;
int result;
int part1;
int part2;

void setup() {
  // put your setup code here, to run once:
  pinMode(A5, OUTPUT);
  digitalWrite(A5, HIGH);
  lcd.begin(16, 2);
  lcd.print("Hi! Who's there?");
  lcd.setCursor(0, 1);
  lcd.print("A>BoBo B>DD C>MM");
  char key = NO_KEY;
  while (key == NO_KEY) {
    char tempkey = bobokey.getKey();
    switch (tempkey) {
      case NO_KEY:
        break;
      case 'A':
        lcd.clear();
        lcd.home();
        lcd.print("Hello BoBo!");
        break;
      case 'B':
        lcd.clear();
        lcd.home();
        lcd.print("Hello BoBo!");
        break;
      case 'C':
        lcd.clear();
        lcd.home();
        lcd.print("Hello BoBo!");
        break;
    }
    randomSeed(millis());
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.clear();
  lcd.home();
  char type;
  if (lastCorrect) {
    type = char(random(0, 3));
  } else {
    type = 9;
  }

  if (type == 0) {
    part1 = int(random(2, 100));
    lcd.print(part1);
    lcd.print(" - ");
    lastSign = '-';
    part2 = int(random(1, part1));
    result = part1 - part2;
  } else if (type == 1) {
    part1 = int(random(1, 10));
    lcd.print(part1);
    lcd.print(" x ");
    lastSign = 'x';
    part2 = int(random(1, 10));
    result = part1 * part2;
  } else if (type == 2) {
    result = int(random(2, 100));
    part1 = int(random(1, result));
    lcd.print(part1);
    lcd.print(" + ");
    lastSign = '+';
    part2 = int(result - part1);
  } else {
    lcd.print(part1);
    lcd.print(' ');
    lcd.print(lastSign);
    lcd.print(' ');
  }



  lcd.print(part2);
  lcd.print(" =");
  lcd.setCursor(8, 1);
  unsigned long t0 = millis();
  int ans = 0;

  while ((millis() < t0 + 10000) && ((result >= 10 && ans < 10) || (result < 10 && ans == 0))) {
    char key = bobokey.getKey();
    switch (key) {
      case NO_KEY:
        break;
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
        lcd.print(key);
        ans = ans * 10 + key - 0x30;
        break;
    }
    if (ans == result) {
      lastCorrect = 1;
      strike += 1;
      delay(1000);
      lcd.clear();
      lcd.home();
      for (int i = 0; i < 2; i++) {
        lcd.print("YES!");
        delay(500);
        lcd.clear();
        lcd.home();
        delay(500);
      }

      if (strike >= 3) {
        lcd.clear();
        lcd.home();
        lcd.print(strike);
        lcd.print(" strike!");
        lcd.setCursor(0, 1);
        lcd.print(">>");
        bobokey.waitForKey();
      }
      break;
    }
  }

  if (ans != result) {
    lastCorrect = 0;
    strike = 0;
    delay(1000);
    lcd.clear();
    lcd.home();
    lcd.print("NOOOooo...");
    delay(2000);
  }

  //lcd.print(result);
  //delay(1000);


}
