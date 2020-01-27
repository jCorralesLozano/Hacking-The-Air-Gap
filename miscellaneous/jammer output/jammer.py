#EECS 159A
#Mohammed Haque
#11/21/19
''' pg_midi_sound101.py
play midi music files (also mp3 files) using pygame
tested with Python273/331 and pygame192 by vegaseat
'''
#code modified from here: https://www.daniweb.com/programming/software-development/code/454835/let-pygame-play-your-midi-or-mp3-files


#!/usr/bin/python

import sys
import pygame as pg
import os
import time


def play_music(music_file):
    '''
    stream music with mixer.music module in blocking manner
    this will stream the sound from disk while playing
    '''
    clock = pg.time.Clock()
    try:
        pg.mixer.music.load(music_file)
        print("Music file {} loaded!".format(music_file))
    except pygame.error:
        print("File {} not found! {}".format(music_file, pg.get_error()))
        return

    pg.mixer.music.play()
    
    # for x in range(0,100):
    #     pg.mixer.music.set_volume(float(x)/100.0)
    #     time.sleep(.0075)
    # # check if playback has finished
    while pg.mixer.music.get_busy():
        clock.tick(30)


freq = 44100    # audio CD quality
bitsize = -16   # unsigned 16 bit
channels = 2    # 1 is mono, 2 is stereo
buffer = 2048   # number of samples (experiment to get right sound)
pg.mixer.init(freq, bitsize, channels, buffer)
# optional volume 0 to 1.0
pg.mixer.music.set_volume(1.0)


##if len(sys.argv) > 1:
##
##    try: 
##        user_volume = float(sys.argv[1])
##    except ValueError:
##        print ("Volume argument invalid. Please use a float (0.0 - 1.0)")
##        pg.mixer.music.fadeout(1000)
##        pg.mixer.music.stop()
##        raise SystemExit
##
##    print("Playing at volume: " + str(user_volume)+ "\n")
##    pg.mixer.music.set_volume(user_volume)
mp3s = []
for file in os.listdir("."):
    if file.endswith(".wav"):
        mp3s.append(file)

print (mp3s)

try:
    while True:
        for x in mp3s: 
            play_music(x)
            time.sleep(0)
except KeyboardInterrupt:
    # if user hits Ctrl/C then exit
    # (works only in console mode)
    pg.mixer.music.fadeout(1000)
    pg.mixer.music.stop()
    raise SystemExit
##else:
##    print("Please specify volume as a float! (0.0 - 1.0)")
