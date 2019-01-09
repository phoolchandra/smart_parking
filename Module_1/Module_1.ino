
//Libraries
#include <LiquidCrystal.h>
#include <Keypad.h>


/*-------------------------------POWERCONSUMPTION---------------------------------------*/
#include "LowPower.h"

// Use pin 2 as wake up pin
const uint8_t wakeUpPin = 2;


/*-------------------------------KEYPAD---------------------------------------*/
const byte numRows = 4; //number of rows on the keypad
const byte numCols = 4; //number of columns on the keypad
char keypressed;
char keymap[numRows][numCols] =
{
  {
    '1', '2', '3', 'A'  }
  ,
  {
    '4', '5', '6', 'B'  }
  ,
  {
    '7', '8', '9', 'C'  }
  ,
  {
    '*', '0', '#', 'D'  }
};
//Code that shows the the keypad connections to the arduino terminals
byte rowPins[numRows] = {
  51, 49, 47, 45}; //Rows 0 to 3
byte colPins[numCols] = {
  43, 41, 39, 37}; //Columns 0 to 3
//initializes an instance of the Keypad class
Keypad myKeypad = Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);

/*-------------------------------CONSTANTS------------------------------------*/
LiquidCrystal lcd(13, 12, 5, 4, 3, 7); //LCD
const uint8_t buzzer = A14;        //Buzzer/small speaker
const uint8_t lock = 9;       //Electric door opener


/*-------------------------------VARIABLES------------------------------------*/
String password;
String masterpassword="10516263";
int ranpass;//Variable to store the current password
String tempPassword = ""; //Variable to store the input password
bool doublecheck;    //Check twice the new passoword
boolean armed = false;  //Variable for system state (armed:true / unarmed:false)
boolean input_pass;   //Variable for input password (correct:true / wrong:false)
boolean storedPassword = false;
boolean changedPassword = false;
boolean checkPassword = false;
boolean lockValue = false;
uint8_t i = 1; //variable to index an array
/*----------------------------------------------------------------------------*/

uint8_t const trigPin = 9;
uint8_t const echoPin = 8;
uint8_t  lockledPin = 1;
uint8_t vPin = 2;

uint8_t const trigPinl = 9;
uint8_t const echoPinl = 8;
uint8_t  lockledPinl = 1;
/*----------------------------------------------------------------------------*/

uint8_t resetpass = 36;
uint8_t resetall = 38;
uint8_t const resetPin = 40;

/*---------------------------------------------------------------------------*/

#define RELAY2  22                        
#define RELAY1  24
uint8_t const trigPinM = 11;
uint8_t const echoPinM = 10;
uint8_t const buzzPinM = 25;
uint8_t pre = -1;
uint8_t curr = 0; 
uint8_t j;

/*--------------------------------------------------------------------------*/

void setup() {

  // Configure wake up pin as input.
  // This will consumes few uA of current.
  pinMode(wakeUpPin, INPUT);
  pinMode(vPin, OUTPUT); 
  digitalWrite(vPin,HIGH);

  digitalWrite(resetPin, HIGH);
  delay(200);
  // initialize the digital pin as an output.
  pinMode(resetPin, OUTPUT);
  pinMode(resetall, INPUT);
  pinMode(resetpass, INPUT);

  pinMode(RELAY1, OUTPUT);       
  pinMode(RELAY2, OUTPUT);
  pinMode(trigPinM, OUTPUT); // trig pin will have pulses output
  pinMode(echoPinM, INPUT);

  Serial.begin(9600);//initialize Serial Port

  pinMode(lock, OUTPUT);
  analogWrite(6, 60);
  lcd.begin(20, 4); //Setup the LCD's number of columns and rows
  //Print welcome message...
  pinMode(trigPin, OUTPUT); // trig pin will have pulses output
  pinMode(echoPin, INPUT); // echo pin should be input to get pulse width
  pinMode(trigPinl, OUTPUT); // trig pin will have pulses output
  pinMode(echoPinl, INPUT); // echo pin should be input to get pulse width
  pinMode(buzzer, OUTPUT);
}

void wakeUp()
{
  // Just a handler for the pin interrupt.

}

void loop() { //Main loop

    // Allow wake up pin to trigger interrupt on low.
  attachInterrupt(0, wakeUp, LOW);

  // Enter power down state with ADC and BOD module disabled.
  // Wake up when wake up pin is low.
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF); 

  // Disable external pin interrupt on wake up pin.

  detachInterrupt(0);

  // Do something here
  // Example: Read sensor, data logging, data transmission.
  lcd.clear();
  delay(30);
  lcd.setCursor(0, 0);
  lcd.print("Arduino Security");
  lcd.setCursor(0, 1);
  lcd.print("Automatic lock  ");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" opener system  ");
  lcd.setCursor(0, 1);
  lcd.print(" with password  ");
  delay(2000);
  unlockTheDoor();

}

// Function for Initialisation of system

void start() { //Main loop
  // Allow wake up pin to trigger interrupt on low.
  attachInterrupt(0, wakeUp, LOW);

  // Enter power down state with ADC and BOD module disabled.
  // Wake up when wake up pin is low.
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF); 

  // Disable external pin interrupt on wake up pin.

  detachInterrupt(0);
  // Do something here
  // Example: Read sensor, data logging, data transmission.
  lcd.clear();
  delay(30);
  lcd.setCursor(0, 0);
  lcd.print("Arduino Security");
  lcd.setCursor(0, 1);
  lcd.print("Automatic lock  ");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" opener system  ");
  lcd.setCursor(0, 1);
  lcd.print(" with password  ");
  delay(2000);
  unlockTheDoor();
}
/********************************FUNCTIONS*************************************/


// Function for Locking and Unlocking

void unlockTheDoor() {


lockAgain:       //goto label
  delay(3000);

  UltrasonicSensor();
  delay(300);
  while (lockledPin != 0)
  {
    if (lockValue == true)               //Buzzer for cycle theft
    {
      tone(buzzer, 1000, 1000);
      delay(300);
      start();
    }
    else
    {
      tone(buzzer, 1000, 1000);
      delay(1000);
      Serial.println("this never happensSSS");
      start();

    }
    UltrasonicSensor();
  }

  tempPassword = "";
  lcd.clear();
  delay(300);

  UltrasonicSensor();
  delay(300);
  if (lockledPin == 0 && lockValue == false)   // Check for cycle in range
  {                                          // and lockvalue then lock cycle
    lcd.clear();
    delay(30);
    lcd.setCursor(0, 0);
    lcd.print("Lock Being Applied");
    Lock();
    lockValue=true;
    delay(1000);
    lcd.setCursor(0, 0);
    lcd.print("Your Password is :");
    GenPassword();
    lcd.setCursor(0, 1);
    lcd.print(ranpass);
    lcd.setCursor(0, 2);
    lcd.print("Press '*' To Proceed");
    lcd.setCursor(0, 3);
    lcd.print("Press A to Change");

  }
  else if (lockledPin == 0 && storedPassword == false)          // Condition for re-initialisation
  {
    delay(1000);
    lcd.setCursor(0, 0);
    lcd.print("Your Password is :");
    GenPassword();
    lcd.setCursor(0, 1);
    lcd.print(ranpass);
    lcd.setCursor(0, 2);
    lcd.print("Press '*' To Proceed");
    lcd.setCursor(0, 3);
    lcd.print("Press A to Change");

  }
  else
  {
    lcd.setCursor(0, 0);
    lcd.print("A-Change Password");
    lcd.setCursor(10, 1);
    lcd.print("or");
    lcd.setCursor(0, 2);
    lcd.print("B-To Unlock");

  }

  while (true) {
    UltrasonicSensor();
    delay(300);
    if (lockledPin != 0)
    {
      if (lockValue == true)
      {
        tone(buzzer, 1000, 1000);                  //Buzzer for cycle theft
        delay(300);
        start();
      }
      else
      {
        tone(buzzer, 1000, 1000);
        delay(1000);
        Serial.println("this never happens");
        start();
      }
    }


    keypressed = myKeypad.getKey();
    delay(300);
    if (keypressed != NO_KEY)
    {
      tone(buzzer, 800, 200);
      Serial.println(keypressed);
      delay(300);
      break;
    }

  }
  while (true) {
    UltrasonicSensor();
    if (lockledPin == 1)
    {
      if (lockValue == true)
      {
        tone(buzzer, 1000, 1000);                   //Buzzer for cycle theft
        delay(300);
        start();
      }
      else
      {
        tone(buzzer, 1000, 1000);
        delay(1000);
        start();
      }
    }

    if (keypressed == '*' && storedPassword == false )          // To confirm Random password
    {        
      password=tempPassword;
      storedPassword = true;
      tone(buzzer, 1000, 1000);
      delay(1000);
      lcd.clear();
      delay(30);

      lockValue=true;
      goto lockAgain;

    } 

    if (keypressed == 'A' && storedPassword == false)            // TO Create own password
    {

      lcd.clear();
      delay(30);
      lcd.setCursor(0, 0);
      lcd.print("# - Clear Password  ");
      lcd.print("SET NEW PASSWORD    ");
      lcd.print("* - Proceed/Enter   ");
      lcd.print(">>");
      delay(300);
      newPassword();
      goto lockAgain;

    }

    else if (keypressed == 'A' && storedPassword == true)       // Change password
    {
      changePassword();
      goto lockAgain;
    }

    if (keypressed == 'B' && lockValue==true)              // To unlock the cycle
    {
      lcd.clear();
      delay(30);
      lcd.setCursor(0, 0);
      lcd.print("# - Clear Password  ");
      lcd.print("Type Your Password  ");
      lcd.print("* - Proceed/Enter   ");
      lcd.print(">>");
      delay(300);

      break;
    }
    if (keypressed == 'C')                         //To cancel
    {
      start();
      delay(300);

      break;
    }

    keypressed = myKeypad.getKey();
    if (keypressed != NO_KEY)
    {
      tone(buzzer, 800, 200);
      Serial.println(keypressed);
      delay(30);
    }

  }

  i = 6;
  noTone(buzzer);
  digitalWrite(lock, LOW);
pass:
  while (!checkPassword) {
    UltrasonicSensor();
    if (lockledPin == 1)
    {
      if (lockValue == true)                             //Buzzer for cycle theft
      {
        tone(buzzer, 1000, 1000);
        delay(300);   // change this to switch
        start();
      }
      else
      {
        tone(buzzer, 1000, 1000);
        delay(1000);
        start();
      }
    }
    keypressed = myKeypad.getKey();   //Read pressed keys
    if (keypressed != NO_KEY) {   //Accept only numbers and * from keypad
      tone(buzzer, 800, 200);    //Button tone
      if (keypressed == '0' || keypressed == '1' || keypressed == '2' || keypressed == '3' ||
        keypressed == '4' || keypressed == '5' || keypressed == '6' || keypressed == '7' ||
        keypressed == '8' || keypressed == '9' ) {
        tempPassword += keypressed;
        lcd.print("*");       //Put * on lcd
        i++;
      }
      else if (keypressed == 'A' && lockValue == false) {
        storedPassword = false;
        lcd.clear();
        delay(30);
        lcd.setCursor(0, 0);
        lcd.print("# - Clear Password  ");
        lcd.print("SET NEW PASSWORD    ");
        lcd.print("* - Proceed/Enter   ");
        lcd.print(">>");
        delay(300);
        newPassword();
        lockValue=true;
        goto lockAgain;
      }
      else if (keypressed == 'A' && lockValue == true) {
        changePassword();
        goto lockAgain;
      }
      else if (keypressed == '#') {
        tempPassword = "";
        lcd.clear();
        delay(30);
        lcd.setCursor(0, 0);
        lcd.print("# - Clear Password  ");
        lcd.print("Type Your Password  ");
        lcd.print("* - Proceed/Enter   ");
        lcd.print(">>");
        goto pass;
      }
      if (keypressed == 'C')
      {
        start();
        delay(300);

        break;
      }
      else if (keypressed == '*') { //Check for password
        if (password == tempPassword || tempPassword == masterpassword) { //If it's correct...
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Correct password");
          lcd.setCursor(0, 1);

          UltrasonicSensor();
          if (lockledPin == 1)
          {
            if (lockValue == true)
            {
              tone(buzzer, 1000,1000);
              delay(300);
              start();
            }
            goto lockAgain;
          }

          lcd.print("lock being unlocked");
          Unlock();
          delay(2000);
          lcd.clear();
          delay(30);
          lcd.setCursor(0, 0);
          lcd.print("Lock Unlocked");
          while(true ) {
            Serial.println(analogRead(wakeUpPin));
            delay(3000);
            if(analogRead(wakeUpPin) >302) break;
          }
          lockValue = false;
          storedPassword == false;
          lcd.clear();


          tone(buzzer, 1000, 1000);  //Play a tone while door is unlocked
          digitalWrite(lock, HIGH);//unlock the door for 5 seconds
          delay(1000);
          start();
        }
        else {          //if it's false, retry
          tempPassword = "";
          lcd.clear();
          delay(30);
          lcd.setCursor(0, 0);
          lcd.print("# - Clear Password  ");
          lcd.print("Type Your Password  ");
          lcd.print("* - Proceed/Enter   ");
          lcd.print(">>");
          tone(buzzer, 500, 200);
          delay(300);
          goto pass;
        }
      }
    }
  }
}

