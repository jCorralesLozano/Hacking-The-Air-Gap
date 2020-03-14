import ByteLayer

if __name__ == '__main__':
	byteLayer = ByteLayer.ByteLayer()
	cmd = str()

	while True:
		cmd = input ("Enter a command (ls, quit): ")
		if (cmd == "quit"):
			print("Session End")
			break
		elif (cmd == "ls"):
			print("Sending command " + cmd + ".")
			byteLayer.send_command(cmd)
			byteLayer.receive_byte()
		else:
			print("Command " + cmd + " not supported.")