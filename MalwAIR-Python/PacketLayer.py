from crc16 import crc16xmodem
import ByteLayer
import Macros

class PacketLayer():

	def __init__(self):
		self.byte_layer = ByteLayer.ByteLayer(self.check_if_packet)
		self.bytes_received = b''


	def send_packet(self, data: bytes) -> bool:
		length = len(data)

		# Check that data is less than or equal to 255 bytes
		if (length > 255):
			return False

		# Start byte
		self.byte_layer.send_byte(Macros.START_BYTE)

		# Length
		self.byte_layer.send_byte(length)

		# Data
		for b in data:
			self.byte_layer.send_byte(b)

		# Checksum
		crc = crc16xmodem(bytes([Macros.START_BYTE, length]) + data)
		crc_top = crc >> 8
		crc_bottom = crc & 0xFF
		self.byte_layer.send_byte(crc_top)
		self.byte_layer.send_byte(crc_bottom)

		# Stop byte
		self.byte_layer.send_byte(Macros.STOP_BYTE)

		return True


	def check_if_packet(byte: bytes):
		self.bytes_received.append(byte)

		for start_index in self._get_all_start_bytes():
			length = 0
			try:
				length = self.bytes_received[start_index+1]
				if (self.bytes_received[start_index+length+4] != Macros.STOP_BYTE):
					continue
			except IndexError:
				continue

			# Packet slice
			packet = self.bytes_received[start_index : start_index+4+length]

			# Get data
			data = packet[2 : length+2]

			# Get checksum
			checksum = packet[length+2] << 8
			checksum = checksum | packet[length+3]

			# Compare computed checksum with bytes_received
			if (crc16xmodem(packet[:length+2]) == checksum):
				print(data)
				self.bytes_received = b''

		# TODO: Make bytes_received a ring buffer


	def _get_all_start_bytes() -> list:
		return [i for i in range(len(self.bytes_received)) if self.bytes_received[i] == Macros.START_BYTE]

