import serial
import csv
import datetime
from datetime import timedelta

def millis():
   dt = datetime.datetime.now() - start_time
   ms = (dt.days * 24 * 60 * 60 + dt.seconds) * 1000 + dt.microseconds / 1000.0
   return ms

ser_obj=serial.Serial('/dev/ttyACM0', 9600, timeout=1)

start_time = datetime.datetime.now()

with open('Data3/test6.csv', 'wb') as csvfile:
	spamwriter = csv.writer(csvfile, delimiter=',', quotechar='|', quoting=csv.QUOTE_MINIMAL)

	while True:	
		message=ser_obj.readline()
		result=message.strip().split(',')

		if len(result)==1:

			
			try:

				print float(result[0])

				spamwriter.writerow([millis(), float(result[0])])

			except:
				pass
