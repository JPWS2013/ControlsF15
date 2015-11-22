import serial
import csv
import time

ser_obj=serial.Serial('/dev/ttyACM0', 115200, timeout=10)

with open('Data2/RPMData5.csv', 'wb') as csvfile:
	data_writer = csv.writer(csvfile, delimiter=',', quotechar='|', quoting=csv.QUOTE_MINIMAL)

	starttime=time.time()

	while True:	
		message=ser_obj.readline()
		rpm_raw=message.strip()
		rpm=int(rpm_raw)

		elapsed=time.time()-starttime

		print rpm, elapsed

		data_writer.writerow([rpm, elapsed])
