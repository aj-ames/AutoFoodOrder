String order = "";
String sum = "";
char ch;
boolean orderAvailable = false;

void setup() {
  Serial.begin(9600);
}

void loop() {
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
      Serial.println(order);
      Serial.flush();
    }
  }
}
