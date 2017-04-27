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

char key;
char ch = ' ';
String sum = "";

String menu[11] = { "1.Tea  Rs. 10", "2.Coffee Rs. 25", "3.Dosa  Rs. 50", "4.Fries Rs. 100", "5.Burger  Rs. 125", "6.Pizza  Rs. 175", "7.Softie Rs. 75", "8.Salad  Rs. 35", "9.Coke  Rs. 30", "10.Juice  Rs. 20", "Escape: 0" };
String order = "*";

boolean flag = false;
//int counter = 0;

// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = { 2,3,4,5 };

// Connect keypad COL0, COL1 and COL2 to these Arduino pins.
byte colPins[COLS] = { 6,7,8 };

//  Create the Keypad
Keypad kpd = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS );


void intro() {
  lcd.clear();
  
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

void instructions() {
  lcd.clear();
  
  lcd.setCursor(0,0);
  lcd.print("To start order:");
  lcd.setCursor(0,1);
  lcd.print("    Press *    ");
  delay(3000);
  lcd.clear();
  delay(10);
  
  lcd.setCursor(0,0);
  lcd.print("To select item:");
  lcd.setCursor(0,1);
  lcd.print("    Press 5    ");
  delay(3000);
  lcd.clear();
  delay(10);

  lcd.setCursor(0,0);
  lcd.print("To see next:");
  lcd.setCursor(0,1);
  lcd.print("    Press 6    ");
  delay(3000);
  lcd.clear();
  delay(10);

  lcd.setCursor(0,0);
  lcd.print("To see previous:");
  lcd.setCursor(0,1);
  lcd.print("    Press 4    ");
  delay(3000);
  lcd.clear();
  delay(10);

  lcd.setCursor(0,0);
  lcd.print("To confirm order:");
  lcd.setCursor(0,1);
  lcd.print("    Press #    ");
  delay(3000);
  lcd.clear();
  delay(10);

  lcd.setCursor(0,0);
  lcd.print("To delete order:");
  lcd.setCursor(0,1);
  lcd.print("    Press 8    ");
  delay(3000);
  lcd.clear();
  delay(10);
}

void displayMenu() {
  for(int i = 0; i< 11; i++) {
  key = NO_KEY;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(menu[i]);
  lcd.setCursor(0,1);
  lcd.print("Next: 6|Prev: 4");
  delay(100);
  while(key == NO_KEY)
    returnKey();
    
  if(key == '6') {
    if(i == 10 ) 
      i = -1;
    continue;
  }

  else if(key == '4') { 
    if(i == 0) {
       i = -1;
       continue;
    }
    else  {
      i -= 2;
      continue;
    }
  }

  else if(key == '5') {
    int temp=i+1;
    if(temp<10) {
      order += "0";
      order += temp;
    }
    else
      order += temp;
    order += "*";
    Serial.println(order);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(menu[i]);
    lcd.setCursor(0,1);
    lcd.print("Entered!");
    delay(1000);
    lcd.clear();
    delay(10);
    i -= 1;
    continue;
  }

  else if(key == '#') {
    order += "#";
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Order Accepted!");
    lcd.setCursor(0,1);
    lcd.print("****************");
    delay(2000);
    lcd.clear();
    delay(10);
    Serial1.println(order);
    Serial.flush();
    order = "*";
    while(Serial1.available()) {
      while(ch != '#') {
        ch = Serial1.read();
        sum += ch;
      }
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("   Total Cost:   ");
      lcd.setCursor(0,1);
      lcd.print(sum);
      delay(3000);
      lcd.clear();
      delay(10);
      flag = true;
    }
    if(flag == true) {
      flag = false;
      break;
    }
    break;
  }

  else if(key == '0') 
    break;

  else if(key == '8') {
    order = "*";
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(" Order Cleared! ");
    lcd.setCursor(0,1);
    lcd.print("****************");
    delay(3000);
    lcd.clear();
    delay(10);
    break;
  }
    
  else {
    errDisplay2();
    i -= 1;
    continue;
  }
  lcd.clear();
  delay(10);
  }
}

void errDisplay() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Oops! Begin Your");
  lcd.setCursor(0,1);
  lcd.print("  Order First!  ");
  delay(3000);
  lcd.clear();
  delay(10);
}

void errDisplay2() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Oops!");
  lcd.setCursor(0,1);
  lcd.print("Bad Choice!");
  delay(3000);
  lcd.setCursor(0,0);
  lcd.print("   Try Again!   ");
  lcd.setCursor(0,1);
  lcd.print("****************");
  delay(3000);
  lcd.clear();
  delay(10);
}

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
  pinMode(53,OUTPUT);
  digitalWrite(53,HIGH);

  //Initializing the 16x2 LCD screen
  lcd.begin(16,2);

  intro();
}//End of setup()

void loop() {
  returnKey();
  if(key == NO_KEY) {
    //lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Instructions: 1");
    lcd.setCursor(0,1);
    lcd.print(" Start Order: * ");
  }
   else {
    switch(key) {
      case '1':
        key = NO_KEY;
        instructions();
        break;
      
      case '*':
        key = NO_KEY;
        displayMenu();
        break;

      case '#':
        key = NO_KEY;
        errDisplay();
        break;

      case '4':
        key = NO_KEY;
        errDisplay();
        break;

      case '6':
        key = NO_KEY;
        errDisplay();
        break;

      case '5':
        key = NO_KEY;
        errDisplay();
        break;

      case '0':
        key = NO_KEY;
        errDisplay();
        break;
       
      default:
        key = NO_KEY;
        errDisplay2();
    }//End of switch construct
    
   }//End of else condition
   
}

char returnKey() {
  key=kpd.getKey(); //storing pressed value in key variable
  return key;
  }

