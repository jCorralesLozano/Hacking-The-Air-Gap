import pyaudio
import numpy as np
import matplotlib.pyplot as plt
from scipy.fftpack import fft
import time
import csv

CHUNK = 4096  # number of data points to read at a time
RATE = 44100  # time resolution of the recording device (Hz)
FREQUENCY = 4000  # target frequency
BANDWIDTH = 100  # boundary from the target frequency
LOWER = FREQUENCY - BANDWIDTH  # lower frequency bound
UPPER = FREQUENCY + BANDWIDTH  # upper frequency bound

p = pyaudio.PyAudio()  # start the PyAudio class
stream = p.open(format=pyaudio.paInt16, channels=1, rate=RATE, input=True,
                frames_per_buffer=CHUNK)  #uses default input device

# open csv file for writing
csvfile = open('frequency.csv', 'w')

# create the file writer object
filewriter = csv.writer(csvfile, delimiter=',',
                        quotechar='|', quoting=csv.QUOTE_MINIMAL)
filewriter.writerow(['Peak Amplitude', 'Frequency (Hz)', 'Time (s)'])

# start the timer
startTime = time.time()

# store frequency and time data
freqYAxis = []
timeXAxis = []

# create a numpy array holding a single read of audio data
for i in range(100):  # to it a few times just to see
    data = np.fromstring(stream.read(CHUNK),dtype=np.int16)
    data = fft(data)  # compute the fft (complex numbers list)
    d = len(data) / 2  # you only need half of the fft list (real signal symmetry)

    # end timer
    endTime = time.time()

    # freq = index
    # magnitude = value
    peak = np.max(abs(data))
    for freq, magnitude in enumerate(data):
        mag = abs(magnitude)
        if peak == mag and LOWER <= freq <= UPPER:
            print(f"Peak Amplitude: {peak}, Magnitude: {abs(magnitude)}, freq: {freq}")
            filewriter.writerow([peak, freq, endTime - startTime])
            freqYAxis.append(freq)
            timeXAxis.append(endTime - startTime)
        elif peak == mag:
            print(f"peak: {peak}, freq: {freq}")
            freqYAxis.append(freq)
            timeXAxis.append(endTime - startTime)
            filewriter.writerow([peak, freq, endTime - startTime])

# plot frequency vs time
plt.plot(timeXAxis, freqYAxis, 'r')
plt.xlabel('Time (seconds)')
plt.ylabel('Frequency (Hertz)')
plt.savefig('freq_v_time.png')  # savefig must be called before show
                                # because show() erases the plot afterwards
plt.show()
plt.close()

# close the csv file
csvfile.close()

# close the stream gracefully
stream.stop_stream()
stream.close()
p.terminate()
