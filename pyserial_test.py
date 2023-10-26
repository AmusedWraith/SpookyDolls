
#def write_read(x):
#    arduino.write(bytes(x,   'utf-8'))
#    time.sleep(0.05)
#    data = arduino.readline()
#    return   data


#while True:
#    num = input("Enter a number: ")
#    value   = write_read(num)
#    print(value)

import serial
import time

arduino = serial.Serial(port='/dev/ttyUSB0',   baudrate=9600, timeout=.1)
time.sleep(.1)

while True:

	print ("Enter Command")

	var = str(input())
	print ("You Entered :", var)

	arduino.write(str.encode(var))