import pygame, pygame.sndarray
import numpy
import scipy.signal

class ToneGenerator:

	def __init__(self, sample_rate = 44100):
		self.sample_rate = sample_rate
		# pygame.mixer.init(freq, bitsize, channels, buffer)
		pygame.mixer.init(44100, -16, 1, 512)
		pygame.mixer.music.set_volume(1) # Max volume


	def play_tone(self, frequency, ms = 1000, peak = 4096):
		"""Play the given NumPy array, as a sound, for ms milliseconds."""
		sound = pygame.sndarray.make_sound(self._sine_wave(frequency, peak))
		sound.play(-1)
		pygame.time.delay(ms)
		sound.stop()


	def _sine_wave(self, hz, peak):
		"""Compute N samples of a sine wave with given frequency and peak amplitude.
		   Defaults to one second.
		"""
		length = self.sample_rate / float(hz)
		omega = numpy.pi * 2 / length
		xvalues = numpy.arange(int(length)) * omega
		onecycle = peak * numpy.sin(xvalues)
		return numpy.resize(onecycle, (self.sample_rate,)).astype(numpy.int16)