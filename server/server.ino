#include<LiquidCrystal.h>

String order = "";
String sum = "";
char ch;
boolean orderAvailable = false;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //RS, E, DB4, DB5, DB6, DB7

void intro() {
  lcd.clear();
  
  lcd.setCursor(0,0);
  lcd.print("  Order Server  ");
  lcd.setCursor(0,1);
  lcd.print("  is now live.  ");
  delay(3000);
  lcd.clear();
  delay(10);
}

void waiting() {
  lcd.clear();
  
  lcd.setCursor(0,0);
  lcd.print("   Waiting...   ");
  lcd.setCursor(0,1);
  lcd.print("****************");
}

void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);

  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);

  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);

  intro();
}

void loop() {
  waiting();
  if(Serial.available() > 0) {
    order = "";
    while(Serial.available()) {
      ch = Serial.read();
      delay(5);
      if(ch == '#') {
        orderAvailable = true;
        break;
      }
      else {
        order += ch;
      }
      delay(5);
    }
    if(orderAvailable == true) {
      lcd.clear();
  
      lcd.setCursor(0,0);
      lcd.print("  Order Received  ");
      lcd.setCursor(0,1);
      lcd.print("****************");
      delay(3000);
      lcd.clear();
      delay(10);

      /*for(int i = 0; i < 11; i++) {
      }*/

      orderAvailable = false;
    }
  }
}
