import PacketLayer

if __name__ == "__main__":
	packet_layer = PacketLayer.PacketLayer()

	with open("../MalwAIR/input/hello.txt", "rb") as f:
		data = f.read(255)
		while data:
			packet_layer.send_packet(data)
			print("Packet sent")
			data = f.read(255)
	input()


	# for i in range(10):
	# 	audio_hack.send_byte(bytes('a', 'ascii'))
	# 			byte_int = int.from_bytes(byte, byteorder='big')