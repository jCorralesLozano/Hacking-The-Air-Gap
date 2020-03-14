import sys
import pygame as pg
import os
import time
import serial
import Macros

class ByteLayer():

	def __init__(self, sample_rate = 44100):
		# pg.mixer.init(freq, bitsize, channels, buffer)
		pg.mixer.init(sample_rate, -16, 2, 512)
		pg.mixer.music.set_volume(1) # Max volume
		self.ser = serial.Serial('/dev/ttyS0', 115200, timeout=0)

	# def __del__(self):
	# 	pg.mixer.music.fadeout(1000)
	# 	pg.mixer.music.stop()

	def send_command(self, command):
		'''
		stream music with mixer.music module in blocking manner
		this will stream the sound from disk while playing
		'''
		music_file = str()
		if (command == "ls"):
			music_file = "tone_2640_hz.wav"
		# elif (command == "cd"):
		# 	music_file = "tone_2640_hz.wav"

		clock = pg.time.Clock()
		try:
			pg.mixer.music.load(music_file)
		except pg.error:
			return

		pg.mixer.music.play()
		
		# check if playback has finished
		while pg.mixer.music.get_busy():
			clock.tick(30)

		pg.mixer.music.stop()

	def receive_byte(self):
		self.ser.flush()
		while True:
			if self.ser.in_waiting > 0:
				line = self.ser.readline().decode('utf-8', errors='ignore').rstrip()

				if (line == chr(Macros.STOP_BYTE)):
					print("Stop")
					return

				print(line)