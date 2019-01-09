
/********* Functions For Checking Cycle distance in slot *********/

void UltrasonicSensor()
{
  
    Serial.println(analogRead(wakeUpPin));
    delay(30);
    if (analogRead(wakeUpPin) <292 )
    {
      lockledPin = 0;
    }
    else if (analogRead(wakeUpPin) >=292)
    {
      lockledPin = 1;
    }
  
  delay(10);
}
