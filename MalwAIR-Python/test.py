#!/usr/bin/env python3
"""Play a sine signal."""
import sys

import numpy as np
import sounddevice as sd

start_idx = 0
samplerate = 44100

def callback(outdata, frames, time, status):
    if status:
        print(status, file=sys.stderr)
    global start_idx
    t = (start_idx + np.arange(frames)) / samplerate
    # t = t.reshape(-1, 1)
    outdata[:,0] = np.sin(2 * np.pi * 1000 * t)
    outdata[:,1] = np.sin(2 * np.pi * 1000 * t)
    start_idx += frames

output =  sd.OutputStream(channels=2, callback=callback,
                     samplerate=samplerate)
output.start()

while True:
    input()