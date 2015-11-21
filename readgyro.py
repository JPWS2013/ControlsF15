import serial
import csv
import datetime

ser_obj=serial.Serial('/dev/ttyACM0', 9600, timeout=1)

with open('Data/test.csv', 'wb') as csvfile:
	spamwriter = csv.writer(csvfile, delimiter=',', quotechar='|', quoting=csv.QUOTE_MINIMAL)

	while True:	
		message=ser_obj.readline()
		result=message.strip().split(',')

		if len(result)==7:

			lin_accel_x=float(result[0])
			lin_accel_y=float(result[1])
			lin_accel_z=float(result[2])

			ang_vel_x=float(result[3])
			ang_vel_y=float(result[4])
			ang_vel_z=float(result[5])

			d=datetime.datetime.now()
			dt_str=d.strftime("%d/%m/%Y %H:%M:%S")


			spamwriter.writerow([dt_str, lin_accel_x, lin_accel_y, lin_accel_z, ang_vel_x, ang_vel_y, ang_vel_z])

			print"Data:"
			print dt_str
			print lin_accel_x, lin_accel_y, lin_accel_z
			print ang_vel_x, ang_vel_y, ang_vel_z
			print " "