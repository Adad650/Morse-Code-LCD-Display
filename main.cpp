#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

const int button = 6;
int buttonState = 0;
int lastButtonState = 0;
unsigned long pressTime = 0;
unsigned long releaseTime = 0;
int cursorPosition = 0; 

void setup() {
  pinMode(button, INPUT_PULLUP); 
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Morse Code Display");
  delay(2000);
  lcd.clear();
  Serial.begin(115200);
}

void loop() {
  buttonState = digitalRead(button);


  if (buttonState == LOW && lastButtonState == HIGH) {
    pressTime = millis(); 
  }


  if (buttonState == HIGH && lastButtonState == LOW) {
    releaseTime = millis(); 
    unsigned long duration = releaseTime - pressTime;

   
    if (duration <= 250) {
      lcd.setCursor(cursorPosition, 0); 
      lcd.print("."); 
      Serial.println("Dot");
    } else {
      lcd.setCursor(cursorPosition, 0); 
      lcd.print("-"); 
      Serial.println("Dash");
    }


    cursorPosition++;
    if (cursorPosition >= 16) { 
      cursorPosition = 0;
      lcd.clear(); 
    }
    delay(10);
  }


  lastButtonState = buttonState;
}