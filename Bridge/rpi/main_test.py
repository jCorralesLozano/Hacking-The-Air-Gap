import ToneGenerator

if __name__ == '__main__':
	tg = ToneGenerator.ToneGenerator()
	hz = str()

	while True:
		hz = input ("Enter a frequency: ")
		tg.play_tone(hz)