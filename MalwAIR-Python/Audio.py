import numpy as np
import sounddevice as sd
import Macros

class Audio():

	def __init__(self):
		self.sample_rate = 44100
		self.frames_per_buffer = 512
		self.start_idx = 0 # Not sure what this is for
		self.frequency_channel_1 = 0
		self.frequency_channel_2 = 0

		# Stream Setup
		sd.default.samplerate = self.sample_rate
		sd.default.channels = 2, 2
		# TODO: Should put this in try and except
		self.output = sd.Stream(callback=self._callback)

		self.output.start()

	def __del__(self):
		self.output.stop()
		self.output.close()

	def play_tone(self, frequency_channel_1, frequency_channel_2 = 0):
		self.frequency_channel_1 = frequency_channel_1
		self.frequency_channel_2 = frequency_channel_2

	def _callback(self, indata, outdata, frames, time, status):
		# if status:
		# 	print(status)
		# TODO: Check out input underflow message

		t = (self.start_idx + np.arange(frames)) / self.sample_rate
		outdata[:,0] = np.sin(2 * np.pi * self.frequency_channel_1 * t)
		outdata[:,1] = np.sin(2 * np.pi * self.frequency_channel_2 * t)
		self.start_idx += frames