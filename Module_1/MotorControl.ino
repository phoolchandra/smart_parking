

/********* Functions For Motor Control *********/

uint8_t measure_distance()
{
  // Duration will be the input pulse width and distance will be the distance to the obstacle in centimeters
  int duration;
  uint8_t distance;
  // Output pulse with 1ms width on trigPin
  digitalWrite(trigPinM, HIGH);
  delay(1);
  digitalWrite(trigPinM, LOW);
  // Measure the pulse input in echo pin
  duration = pulseIn(echoPinM, HIGH);
  // Distance is half the duration devided by 29.1 (from datasheet)
  distance = (duration / 2) / 29.1;

  return distance;
}

void Lock()
{
  uint8_t r = 0;
  digitalWrite(RELAY1, HIGH);          // Turns ON Relays 1
  digitalWrite(RELAY2, LOW);
  delay(2000);
  // Wait 2 seconds
  j = 0;
  pre = 0;
  curr = measure_distance();
  Serial.println("\n Motor Distance:");
  Serial.println(curr);
  bool stopped=false;
  

  while(curr < 9)        //check for distance <9
  {
    
    UltrasonicSensor();
    if ((curr != pre && lockledPin==0) || curr == 6 )
    {
      pre = curr;
      delay(5000);
      curr = measure_distance();
      delay(1000);
      Serial.println("\n Motor Distance:");
      Serial.println(curr);

    }
    else 
    {
      stopped=true;
      break;
    }   
  }

  digitalWrite(RELAY1, HIGH);         // Turns Relay Off
  digitalWrite(RELAY2, HIGH);
  delay(1000);

  if (stopped == true && curr < 9)
  {
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Lock Unsuccessful");

    digitalWrite(RELAY1, LOW);          // Turns ON Relays 2
    digitalWrite(RELAY2, HIGH);
    while ( curr > 4 )
    {
      delay(3000);
      curr=measure_distance();
      Serial.println("\n Motor Distance:");
      Serial.println(curr);
    }

    delay(1000);
    digitalWrite(RELAY1, HIGH);         // Turns Relay Off
    digitalWrite(RELAY2, HIGH); // Wait 2 seconds
    delay(20);
    j = 0;
    lcd.clear();
    start();
  }
}

void Unlock()
{
  delay(1000);

  digitalWrite(RELAY1, LOW);          // Turns ON Relays 2
  digitalWrite(RELAY2, HIGH);
  uint8_t dist=measure_distance();

  while (dist > 4)
  {
    dist=measure_distance();
    Serial.print(dist);
    delay(1000);

  }

  delay(2000);
  digitalWrite(RELAY1, HIGH);         // Turns Relay Off
  digitalWrite(RELAY2, HIGH); // Wait 2 seconds
  delay(2000);
}
