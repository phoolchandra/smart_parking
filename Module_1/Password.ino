
/********* Functions For Password Managment *********/

//Generating Random password
void GenPassword() {
  
  ranpass=random(1000,9999);
  
  tempPassword= String(ranpass);

}

String firstpass;
//Setup new password
void newPassword() {
retype:
  tempPassword = "";
  changedPassword = false;
  i = 1;
  while (!storedPassword) {
    keypressed = myKeypad.getKey();   //Read pressed keys
    if (keypressed != NO_KEY) {
      tone(buzzer, 800, 200);
      if (keypressed == '0' || keypressed == '1' || keypressed == '2' || keypressed == '3' ||
          keypressed == '4' || keypressed == '5' || keypressed == '6' || keypressed == '7' ||
          keypressed == '8' || keypressed == '9' ) {
        tempPassword += keypressed;
        lcd.print("*");
        i++;
      }
      else if (keypressed == '#') {
        lcd.clear();
        delay(30);
        lcd.setCursor(0, 0);
        lcd.print("# - Clear Password  ");
        if (doublecheck == 0) lcd.print("SET NEW PASSWORD    ");
        if (doublecheck == 1) lcd.print("One more time...    ");
        lcd.print("* - Proceed/Enter   ");
        lcd.print(">>");
        delay(300);
        goto retype;
      }
      if (keypressed == 'C')
      {
        start();
        delay(300);

        break;
       }
      else if (keypressed == '*') {
        if (doublecheck == 0) {             // Re-enter password
          firstpass = tempPassword;
          doublecheck = 1;
          lcd.clear();
          delay(30);
          lcd.setCursor(0, 0);
          lcd.print("# - Clear Password  ");
          lcd.print("One more time...    ");
          lcd.print("* - Proceed/Enter   ");
          lcd.print(">>");
          delay(300);
          newPassword();
        }
        if (doublecheck == 1) {          
          doublecheck = 0;
          if (firstpass == tempPassword  || password == masterpassword) {
            i = 1;
            firstpass = "";
            password = tempPassword; // New password saved
            tempPassword = ""; //erase temp password
            lcd.clear();
            lcd.setCursor(0, 0);
            if(lockValue == true) lcd.print("PASSWORD CHANGED");
            lcd.setCursor(0, 1);
            lcd.print("----------------");
            storedPassword = true;
            tone(buzzer, 1000, 1000);
            delay(1000);
            lcd.clear();
            delay(30);
          }
          else {
            firstpass = "";
            lcd.clear();
            delay(30);
            lcd.setCursor(0, 0);
            lcd.print("# - Clear Password  ");
            lcd.print("SET NEW PASSWORD    ");
            lcd.print("* - Proceed/Enter   ");
            lcd.print(">>");
            delay(300);
            newPassword();
          }
        }
      }
    }
  }
}


/********************************FUNCTIONS*************************************/

//Change current password
void changePassword() {
retry: //label for goto

  tempPassword = "";
  i = 1;
  lcd.clear();
  delay(30);
  lcd.setCursor(0, 0);
  lcd.print("# - Clear Password  ");
  lcd.print("CURRENT PASSWORD    ");
  lcd.print("* - Proceed/Enter   ");
  lcd.print(">>");
  delay(300);
  while (!changedPassword) {      //Waiting for current password
    UltrasonicSensor();
    if (lockledPin == 1)
    {
      if (lockValue == true)
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
    delay(30);
    if (keypressed != NO_KEY) {
      tone(buzzer, 800, 200);
      if (keypressed == '0' || keypressed == '1' || keypressed == '2' || keypressed == '3' ||
          keypressed == '4' || keypressed == '5' || keypressed == '6' || keypressed == '7' ||
          keypressed == '8' || keypressed == '9' ) {
        tempPassword += keypressed;
        lcd.print("*");
        i++;
      }
      else if (keypressed == '#') {
        tempPassword = "";
        tone(buzzer, 500, 200);
        delay(300);
        goto retry;
      }
      if (keypressed == 'C')
      {
        start();
        delay(300);

        break;
      }
      else if (keypressed == '*') {
        i = 1;
        if (password == tempPassword) {
          storedPassword = false;
          tone(buzzer, 500, 200);
          lcd.clear();
          delay(30);
          lcd.setCursor(0, 0);
          lcd.print("# - Clear Password  ");
          lcd.print("SET NEW PASSWORD    ");
          lcd.print("* - Proceed/Enter   ");
          lcd.print(">>");
          delay(300);
          newPassword();          //Password is corrent, so call the newPassword function
          break;
        }
        else {              //Try again
          tempPassword = "";
          tone(buzzer, 500, 200);
          delay(300);
          goto retry;
        }
      }
    }
  }
}
