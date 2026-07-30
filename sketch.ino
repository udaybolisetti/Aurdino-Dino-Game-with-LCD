#include <LiquidCrystal.h>

LiquidCrystal lcd(12,11,5,4,3,2);

const int buttonPin = 7;

int dinoRow = 1;
int obstaclePos = 15;

bool jumping = false;
unsigned long jumpTime = 0;

int score = 0;

void setup() {
  pinMode(buttonPin, INPUT);

  lcd.begin(16,2);

  // Custom dino character
  byte dino[8] = {
    B00100,
    B01110,
    B10101,
    B00100,
    B01110,
    B10101,
    B00100,
    B00000
  };

  lcd.createChar(0,dino);

  lcd.clear();
}

void loop() {

  // Button pressed → jump
  if(digitalRead(buttonPin)==HIGH && !jumping){
      jumping=true;
      dinoRow=0;
      jumpTime=millis();
  }

  // Jump duration
  if(jumping && millis()-jumpTime>500){
      jumping=false;
      dinoRow=1;
  }

  lcd.clear();

  // Display Dino
  lcd.setCursor(1,dinoRow);
  lcd.write(byte(0));

  // Display obstacle
  lcd.setCursor(obstaclePos,1);
  lcd.print("|");

  // Collision check
  if(obstaclePos==1 && dinoRow==1){
      lcd.clear();
      lcd.setCursor(3,0);
      lcd.print("GAME OVER");

      lcd.setCursor(4,1);
      lcd.print("Score:");
      lcd.print(score);

      while(true);
  }

  obstaclePos--;

  if(obstaclePos<0){
      obstaclePos=15;
      score++;
  }

  lcd.setCursor(10,0);
  lcd.print(score);

  delay(150);
}