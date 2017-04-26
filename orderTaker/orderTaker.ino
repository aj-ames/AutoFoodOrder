#include <LiquidCrystal.h>
#include <Keypad.h>
LiquidCrystal lcd(32, 33, 34, 35, 36, 37); //RS, E, DB4, DB5, DB6, DB7

const byte ROWS = 4; // Four rows
const byte COLS = 3; // Three columns

// Define the Keymap
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = { 2,3,4,5 };

// Connect keypad COL0, COL1 and COL2 to these Arduino pins.
byte colPins[COLS] = { 6,7,8 };

//  Create the Keypad
Keypad kpd = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
  //Serial for Serial Monitor
  Serial.begin(9600);
  //Serial for Bluetooth
  Serial1.begin(9600);

  //Pins of LCD Screen
  pinMode(32,OUTPUT);
  pinMode(33,OUTPUT);
  pinMode(34,OUTPUT);
  pinMode(35,OUTPUT);
  pinMode(36,OUTPUT);
  pinMode(37,OUTPUT);
  pinMode(52,OUTPUT);
  digitalWrite(52,HIGH);

  //Initializing the 16x2 LCD screen
  lcd.begin(16,2);

  lcd.setCursor(0,0);
  lcd.print("Auto Order Taker");
  lcd.setCursor(0,1);
  lcd.print("will take order!");
  delay(3000);
  lcd.clear();
  delay(10);
  lcd.setCursor(0,0);
  lcd.print(" Choose wisely!");
  lcd.setCursor(0,1);
  lcd.print(" Don't be shy!");
  delay(3000);
  lcd.clear();
  delay(10);
}

void loop() {
  char key=kpd.getKey(); //storing pressed value in key variable
  if(key != NO_KEY) {
    Serial.println(key);
    Serial.flush();
  }
}

