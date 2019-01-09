
// Libraries
#include <Wire.h>
#include <Digital_Light_TSL2561.h>

uint8_t n = 1;
uint8_t m = n;

//**************** Pins assignments **************//

uint8_t const trigPin[1] = {11}; 
uint8_t const echoPin[1] = {12};
uint8_t const lockledPin = 8;
uint8_t const redled = 26;
uint8_t const slotpin = 28;

uint8_t ledPin = 13;                // choose the pin for the LED
#define pirPin 4
uint8_t calibrationTime = 30;
long unsigned int lowIn;
long unsigned int pause = 5000;
boolean lockLow = true;
boolean takeLowTime;
uint8_t PIRValue = 0;

#include<LiquidCrystal.h>
LiquidCrystal lcd(10, 9, 42, 44, 46, 48);

void setup()
{
  Wire.begin();
  Serial.begin(9600);

  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);      // declare LED as output

  pinMode(trigPin[0], OUTPUT); // trig pin will have pulses output
  pinMode(echoPin[0], INPUT); // echo pin should be input to get pulse width
  pinMode(lockledPin, OUTPUT);
  pinMode(redled, INPUT);
  pinMode(slotpin, OUTPUT);

  digitalWrite(slotpin, HIGH);

  digitalWrite(lockledPin, HIGH);

  analogWrite(6, 60);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Number of empty slot");
  lcd.setCursor(0, 1);
  lcd.print(m, DEC);

  TSL2561.init();
}

void loop()
{

  Serial.print("The Light value is: ");
  Serial.println(TSL2561.readVisibleLux());
  if (TSL2561.readVisibleLux() == 0) {
    PIRSensor();
  }
  Serial.print("The ledpin is: ");
  Serial.println(digitalRead(ledPin));
  

  for (uint8_t i = 0; i < 1; i++)
    UltrasonicSensor(i);          //Check for cycle in range 

  delay(1000);
}

void PIRSensor() {
  if (digitalRead(pirPin) == HIGH) {        //Check for motion
    if (lockLow) {
      PIRValue = 1;
      lockLow = false;
      Serial.println("Motion detected.");
      digitalWrite(ledPin, HIGH);  // turn LED ON
      delay(50);
    }
    takeLowTime = true;
  }
  if (digitalRead(pirPin) == LOW) {          //Check for no motion
    if (takeLowTime) {
      lowIn = millis(); takeLowTime = false;
    }
    if (!lockLow && millis() - lowIn > pause) {
      PIRValue = 0;
      lockLow = true;
      Serial.println("Motion ended.");
      digitalWrite(ledPin, LOW);  // turn LED OFF
      delay(50);
    }
  }
}

void UltrasonicSensor(uint8_t i)
{
  // Duration will be the input pulse width and distance will be the distance to the obstacle in centimeters

  int duration;
  uint8_t distance;
  // Output pulse with 1ms width on trigPin
  digitalWrite(trigPin[i], HIGH);
  delay(1);
  digitalWrite(trigPin[i], LOW);
  // Measure the pulse input in echo pin
  duration = pulseIn(echoPin[0], HIGH);
  // Distance is half the duration devided by 29.1 (from datasheet)
  distance = (duration / 2) / 29.1;
  // if distance less than 0.5 meter and more than 0 (0 or less means over range)
  if (distance <= 15 && distance >= 0 )
  {
    // Buzz
    digitalWrite(lockledPin, LOW);           //For waking up arduino 2
    digitalWrite(slotpin, LOW);              // For showing slot LED
    m = 0;
    lcd.setCursor(0, 1);
    lcd.print(m, DEC);
  }
  else if ((distance > 15 || distance < 0)) {
    digitalWrite(lockledPin, HIGH);
    digitalWrite(slotpin, HIGH);
    m = 1;
    lcd.setCursor(0, 1);
    lcd.print(m, DEC);
  }
  Serial.println("\nDistance:");
  Serial.println(distance);

  // Waiting 60 ms won't hurt any one
  delay(500);
}
