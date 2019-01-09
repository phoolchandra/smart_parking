Module_1- Folder Containing code for Lock system

Libaries to be included 

1.LiquidCrystal.h  - For LCD Display
2.Keypad.h         - For Keypad
3.LowPower.h        - For arduino sleep

For Module_2 code - Containing street light control, Empty slot display 
1.Wire.h
2.Digital_Light_TSL2561.h



Steps to be followed
-Copy whole foldor in your PC
-Open Module_1/Module_1.ino in your arduino IDE
-Download above mentioned libraries 
-Connect Arduino_1(The one for Smart lock mechanism)
-Upload the code in Arduino 1
-Open Module_2/Module_2.ino in your arduino IDE
-Download above mentioned libraries
-Connect Arduino_2(The one for street light control, Empty slot display)
-Upload the code in Arduino_2


For MQTT
- Copy Files in MQTT Module in your PC
-Publisher and Subscriber should be connected to same server
- To Publish data- Open Terminal
                   Execute file publisher.py
- To Subscribe for data - Open Terminal
                   Execute file subscriber.py
		   
