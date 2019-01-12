# Project Title : Smart praking

     this project give the solution how you can solve the parking problem eaily <br>
     Nowdays, we know that people have to face a lot of problem in big cities to park their<br>
     vehicles like first find the empty space for parking, security of vehicles and it consumes <br>
     a lot of time. Our project is a solution for parking.

## project vedio link for demo<br>
https://drive.google.com/file/d/1NBdoWs9Z9bVtt03Vy28Yc97eod0WfDYR/view?usp=sharing<br>

### Salient Features
1. We host the server using MQTT in which subscriber can see the empty<br>
   slots, damaged slots and occupied slots in parking area
   
2. It has automatic locking system. When you park your bycycle in empty slot the you have to create <br>
   new passowrd using the matrix keyborad which is above the slot.
   
3. all the required instructions are displayed in lcd display which is fixed beside the matrix keyboard.
4. If any slote will be damaged then a buzzer will inform the security gaurd and its information is also <br>
  published in mqtt hosted server.
  
5. If you have forgotten your password then there is master password facility also you can use it after <br>
   after showing you required proff that bycycle parked in slot is belonged from you.
6. there are separete slot of individual bycycles to avoid the falling of all bycycles in that row in which a bucycle<br>
  is fallen down at peak hour when there are overcrowding of bycycles.

#### Module_1- Folder Containing code for Lock system

Libaries to be included 

1.LiquidCrystal.h  - For LCD Display
2.Keypad.h         - For Keypad
3.LowPower.h        - For arduino sleep

# For Module_2 code - Containing street light control, Empty slot display 
1.Wire.h  <br>
2.Digital_Light_TSL2561.h  <br>



## Steps to be followed
-Copy whole foldor in your PC <br>
-Open Module_1/Module_1.ino in your arduino IDE  <br>
-Download above mentioned libraries  <br>
-Connect Arduino_1(The one for Smart lock mechanism)  <br>
-Upload the code in Arduino 1  <br>
-Open Module_2/Module_2.ino in your arduino IDE  <br>
-Download above mentioned libraries  <br>
-Connect Arduino_2(The one for street light control, Empty slot display)  <br>
-Upload the code in Arduino_2  <br>


#### For MQTT
- Copy Files in MQTT Module in your PC  <br>
-Publisher and Subscriber should be connected to same server  <br>
- To Publish data- Open Terminal  <br>
                   Execute file publisher.py  <br>
- To Subscribe for data - Open Terminal  <br>
                   Execute file subscriber.py  <br>
		   
