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

String menu[10] = { "1. Tea", "2. Coffee", "3. Masala Dosa", "4. French Fries", "5. Veg. Burger", "6. Chicken Pizza", "7. Milk Shake", "8. Fruit Salad", "9. Diet Coke", "10. Fruit Juice" };
String order = "";

boolean flag = false;
int counter = 0;

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
  lcd.print("    Press 0    ");
  delay(3000);
  lcd.clear();
  delay(10);
}

void displayMenu() {
  for(int i = 0; i< 10; i += 2) {
  key = NO_KEY;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(menu[i]);
  lcd.setCursor(0,1);
  lcd.print(menu[i+1]);
  delay(100);
  while(key == NO_KEY)
    returnKey();
    
  if(key == '6') {
    if(i == 8 )
      i = -2;
    continue;
  }

  else if(key == '4') { 
    if(i == 0 || i == 8) {
       i = -2;
       continue;
    }
    else  {
      i -= 4;
      continue;
    }
  }

  else {
    errDisplay2();
    i -= 2;
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

  //Initializing the 16x2 LCD screen
  lcd.begin(16,2);

  intro();
}

void loop() {
  returnKey();
  if(key == NO_KEY) {
    //lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Instructions:");
    lcd.setCursor(0,1);
    lcd.print("    Press 1    ");
  }
   else {
    switch(key) {
      case '1':
        key = NO_KEY;
        instructions();
        break;
      
      case '*':
        key = NO_KEY;
        order += "*";
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

