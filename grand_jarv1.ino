// C++ code
//
#include <Adafruit_LiquidCrystal.h>

int Distancia1 = 0;

int Distancia2 = 0;

int vagasL = 0, vagasO = 0;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;

Adafruit_LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup()
{
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);
}

void loop()
{
  vagasL = 0;
  vagasO = 0;
  
  Distancia1 = 0.01723 * readUltrasonicDistance(6, 6);
  if (Distancia1 <= 200) {
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    vagasO = vagasO + 1;
  } else {
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    vagasL = vagasL + 1;
  }
  Distancia2 = 0.01723 * readUltrasonicDistance(7, 7);
  if (Distancia2 <= 200) {
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
        vagasO = vagasO + 1;
  } else {
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    vagasL = vagasL + 1;
  }
  lcd.setCursor(0,0);
  lcd.print("vagas livres");
  lcd.setCursor(15,0);
  lcd.print(vagasL);
  lcd.setCursor(0,1);
  lcd.print("vagas ocupadas");
  lcd.setCursor(15,1);
  lcd.print(vagasO);
  delay(100); // Delay a little bit to improve simulation performance
}