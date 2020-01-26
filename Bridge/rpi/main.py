import serial

if __name__ == '__main__':
	display = False;
	ser = serial.Serial('/dev/ttyS0', 115200, timeout=0)
	ser.flush()
	while True:
		if ser.in_waiting > 0:
			line = ser.readline().decode('utf-8', errors='ignore').rstrip()

			# if (line == "Start"):
			# 	print("Start")
			# 	display = True
			# elif (line == "Stop"):
			# 	display = False;
			# 	print("Stop")
			# elif (display):
			# 	print(line)

			print(line)