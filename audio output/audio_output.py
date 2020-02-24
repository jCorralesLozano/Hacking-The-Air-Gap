#EECS 159
#Mohammed Haque
#11/21/19
#!/usr/bin/python

import sys
import pygame as pg
import numpy as np
import pygame.sndarray
import os
import time

freq = 44100    # audio CD quality
bitsize = -16   # unsigned 16 bit
channels = 1    # 1 is mono, 2 is stereo
buffer = 4096   # number of samples (experiment to get right sound)
# 44.1kHz, 16-bit signed, mono
pg.mixer.pre_init(freq, bitsize, channels) 
pg.init()
# buffer : the peak ; volume ; loudness
# 440 : the frequency in hz
# if astype int16 not specified sound will get very noisy, because we have defined it as 16 bit mixer at mixer.pre_init()
# ( probably due to int overflow resulting in non continuous sound data)
arr = np.array([buffer * np.sin(2.0 * np.pi * 5000 * x / freq) for x in range(0, freq)]).astype(np.int16)
sound = pg.sndarray.make_sound(arr)

try:
    while True:
        # -1 means loop unlimited times
        sound.play(-1)
        # determines length of sound
        pg.time.delay(1000)
        sound.stop()
        time.sleep(0)
except KeyboardInterrupt:
    # if user hits Ctrl/C then exit
    # (works only in console mode)
    sound.stop()
    raise SystemExit
