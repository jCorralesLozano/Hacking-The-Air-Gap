import serial
import Macros
import ToneGenerator

class ByteLayer():

	def __init__(self, sample_rate = 44100):
		self.tone = ToneGenerator()
		self.ser = serial.Serial('/dev/ttyS0', 115200, timeout=0)

		# Conversion dictionaries
		self.byte_to_freq = {
			0: Macros.FREQ_0, 1: Macros.FREQ_1, 2: Macros.FREQ_2, 3: Macros.FREQ_3, 
			4: Macros.FREQ_4, 5: Macros.FREQ_5, 6: Macros.FREQ_6, 7: Macros.FREQ_7, 
			8: Macros.FREQ_8, 9: Macros.FREQ_9, 10: Macros.FREQ_A, 11: Macros.FREQ_B, 
			12: Macros.FREQ_C, 13: Macros.FREQ_D, 14: Macros.FREQ_E, 15: Macros.FREQ_F
		}
		self.freq_to_byte = dict((y,x) for x,y in self.byte_to_freq.items())

	# def __del__(self):
	# 	pg.mixer.music.fadeout(1000)
	# 	pg.mixer.music.stop()


	def send_byte(self, byte: int):
		first, second = self._deconstruct_byte_into_two_freq(byte)

		# Output delimiter tone
		self.tone.play_tone(FREQ_DELIMITER)

		# Output first hex data tone
		self.tone.play_tone(first)

		# Output delimiter tone
		self.tone.play_tone(FREQ_DELIMITER)

		# Output second hex data tone
		self.tone.play_tone(second)


	def _deconstruct_byte_into_two_freq(self, byte: int):
		first = byte >> 4
		second = byte & 0b00001111
		print(byte)
		print('\t', first)
		print('\t', second)
		return (self.byte_to_freq[first], self.byte_to_freq[second])