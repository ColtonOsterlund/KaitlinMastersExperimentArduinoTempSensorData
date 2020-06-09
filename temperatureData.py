import serial
import time
import csv
import schedule
from datetime import datetime
import os
import sys
 
# set up the serial line
ser = serial.Serial('COM3', 9600)
 
# Read and record the data
 
def printConsole():
	ser.write('1'.encode())
	b = ser.readline()         # read a byte string
	ser.flushInput()
	string_n = b.decode()  # decode byte string into Unicode  
	string = string_n.rstrip() # remove \n and \r
	data = string.split(",")
	print("Sensor 1: " + data[0])
	print("Sensor 2: " + data[1])
	print("Sensor 3: " + data[2])
	print("Sensor 4: " + data[3])
	print("Sensor 5: " + data[4])
	print("\n\n")
def printFile():
	file = open("MyFile.txt","a")
 
	# Read and record the data
 
	ser.write('1'.encode())
	b = ser.readline()         # read a byte string
	ser.flushInput()
	string_n = b.decode()  # decode byte string into Unicode  
	string = string_n.rstrip() # remove \n and \r
	now = datetime.now()
	# dd/mm/YY H:M:S
	dt_string = now.strftime("%d/%m/%Y %H:%M:%S")
	dataString = dt_string + "," + string
	print(dataString)
	file.write(dataString + "\n")
        
	file.close()

schedule.every(3600).seconds.do(printFile)
schedule.every(10).seconds.do(printConsole)
while True:
	try:
		schedule.run_pending()
		time.sleep(1)
	except Exception as e:
		print(e)
		print("\nexception - restarting\n")
		ser.close()
		os.system("python temperatureData.py")
		sys.exit()
	