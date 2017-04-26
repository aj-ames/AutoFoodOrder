#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 10, 9, 8, 7); //RS, E, DB4, DB5, DB6, DB7

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
  pinMode(12,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(7,OUTPUT);

  //Initializing the 16x2 LCD screen
  lcd.begin(16,2);
}

void loop() {
  char key=kpd.getKey(); //storing pressed value in key variable
  if(key != NO_KEY) {
    Serial.println(key);
  }
}

