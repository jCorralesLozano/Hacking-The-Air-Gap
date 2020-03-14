import PacketLayer

if __name__ == '__main__':
	packetLayer = PacketLayer.PacketLayer()
	cmd = str()

	while True:
		cmd = input ("Enter a command (pwd, ls, cd [dir], get [file path], quit): ")
		if (cmd == "quit"):
			print("Session End")
			break
		elif (cmd.split(" ")[0] in ["pwd", "ls", "cd", "get"]):
			print("Sending command: " + cmd)
			if (not byteLayer.send_packet(cmd)):
				# TODO: Allow commands with length over 255 characters
				print("Command needs to less than 255 characters")
			byteLayer.receive_packet()
		else:
			print("Command " + cmd + " not supported.")