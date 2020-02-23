import math
import numpy as np
import sounddevice as sd
import time
import Macros

class ByteLayer():

	def __init__(self, callback_packet_layer, sample_rate = 44100, tone_period = 0.05):
		self.sample_rate = 44100
		self.tone_period = tone_period	# Time to play a tone for, in seconds
		self.callback_packet_layer = callback_packet_layer
		self.start_idx = 0 # TODO: Not sure what this is for
		self.frequency_channel_1 = 0
		self.frequency_channel_2 = 0

		self.byte_to_freq = {
			0: Macros.FREQ_0, 1: Macros.FREQ_1, 2: Macros.FREQ_2, 3: Macros.FREQ_3, 
			4: Macros.FREQ_4, 5: Macros.FREQ_5, 6: Macros.FREQ_6, 7: Macros.FREQ_7, 
			8: Macros.FREQ_8, 9: Macros.FREQ_9, 10: Macros.FREQ_A, 11: Macros.FREQ_B, 
			12: Macros.FREQ_C, 13: Macros.FREQ_D, 14: Macros.FREQ_E, 15: Macros.FREQ_F
		}

		self.freq_to_byte = dict((y,x) for x,y in self.byte_to_freq.items())

		# Stream Setup
		sd.default.samplerate = self.sample_rate
		sd.default.channels = 1, 2	# Number of input/output channels
		# TODO: Should put this in try and except
		self.stream = sd.Stream(callback=self._callback)

		self.stream.start()


	def __del__(self):
		self.stream.stop()
		self.stream.close()


	def send_byte(self, byte):
		first, second = self._deconstruct_byte_into_two_freq(byte)

		# Output first tone, one channel is "data tone", and other is "MSBs tone"
		self.frequency_channel_1 = first
		self.frequency_channel_2 = Macros.FREQ_SPECIAL
		time.sleep(self.tone_period)

		# Output second tone, both channels same
		self.frequency_channel_1 = second
		self.frequency_channel_2 = second
		time.sleep(self.tone_period)

		self.frequency_channel_1 = 0
		self.frequency_channel_2 = 0


	def _callback(self, indata, outdata, frames, time, status):
		# if status:
		# 	print(status)
		# TODO: Check out input underflow message

		t = (self.start_idx + np.arange(frames)) / self.sample_rate
		outdata[:,0] = np.sin(2 * np.pi * self.frequency_channel_1 * t)
		outdata[:,1] = np.sin(2 * np.pi * self.frequency_channel_2 * t)
		self.start_idx += frames

		if any(indata):
			# TODO: Better Peak Detection Algorithm
			# https://stackoverflow.com/questions/22583391/peak-signal-detection-in-realtime-timeseries-data/56451135#56451135
			dominant_amp_value = 0
			dominant_freq_index = 0

			fft_output = np.abs(np.fft.rfft(indata[:, 0], n = 1024))
			for i in range(len(fft_output)):
				if (dominant_amp_value < fft_output[i]):
					dominant_amp_value = fft_output[i]
					dominant_freq_index = i
			print("Dominant Freq: " + str(dominant_freq_index*43) + " Amp: " + str(dominant_amp_value) + " Special: " + str(fft_output[40]))

	def _deconstruct_byte_into_two_freq(self, byte):
		first = byte >> 4
		second = byte & 0b00001111
		print(byte)
		print(first)
		print(second)
		return (self.byte_to_freq[first], self.byte_to_freq[second])