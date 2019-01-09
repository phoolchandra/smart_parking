import serial
import paho.mqtt.publish as publish      #importing required libraries
 

MQTT_SERVER = "localhost"   #server name 
MQTT_PATH = "available_slots"    #MQTT_PATH name descrided as topic name for easily understanding 
ser = serial.Serial('/dev/ttyACM0',9600)  #serialy reading from port ttyACMO whose baud rate is 9600

while True:
	read_serial=ser.readline()
	print read_serial   # printing the obtained information in publisher screen
	publish.single(MQTT_PATH,read_serial, hostname=MQTT_SERVER)  #sending information in sever 
