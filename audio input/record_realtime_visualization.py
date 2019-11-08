import pyaudio
import numpy as np
import matplotlib.pyplot as plt
from scipy.fftpack import fft, fftfreq
import time
import csv

CHUNK = 4096  # number of data points to read at a time
RATE = 44100  # time resolution of the recording device (Hz)
LOWER = 440  # lower frequency bound
UPPER = 6000  # upper frequency bound
BANDWIDTH = 50  # boundary from the target frequency
FRATE = 44100  # frame rate

p = pyaudio.PyAudio()  # start the PyAudio class
stream = p.open(format=pyaudio.paInt16, channels=1, rate=RATE, input=True,
                frames_per_buffer=CHUNK)  #uses default input device

# open csv file for writing
csvfile = open('frequency.csv', 'w')

# create the file writer object
filewriter = csv.writer(csvfile, delimiter=',',
                        quotechar='|', quoting=csv.QUOTE_MINIMAL)
filewriter.writerow(['Frequency (Hz)', 'Time (s)'])

# start the timer
startTime = time.time()

# store frequency and time data
freqYAxis = []
timeXAxis = []

# create a numpy array holding a single read of audio data
for i in range(100):  # to it a few times just to see
    data = np.fromstring(stream.read(CHUNK), dtype=np.int16)
    data = fft(data)  # compute the fft (complex numbers list)
    # print out the frequencies found
    freqs = fftfreq(len(data))
    # print(freqs.min(), freqs.max())

    # Find the peak in the coefficients
    idx = np.argmax(np.abs(data))
    freq = freqs[idx]
    freq_in_hertz = abs(freq * FRATE)
    print(freq_in_hertz)
    # end timer
    endTime = time.time()

    # check if the frequency is near the UPPER or LOWER boundary
    if UPPER - BANDWIDTH <= freq_in_hertz <= UPPER + BANDWIDTH:
        filewriter.writerow([freq, endTime - startTime])
        freqYAxis.append(freq_in_hertz)
        timeXAxis.append(endTime - startTime)
    elif LOWER - BANDWIDTH <= freq_in_hertz <= LOWER + BANDWIDTH:
        freqYAxis.append(freq_in_hertz)
        timeXAxis.append(endTime - startTime)
        filewriter.writerow([freq, endTime - startTime])
    else:
        freqYAxis.append(0)  # record 0 Hz frequency
        timeXAxis.append(endTime - startTime)
        filewriter.writerow([freq, endTime - startTime])

# close the csv file
csvfile.close()

# plot frequency vs time
plt.plot(timeXAxis, freqYAxis, 'r')
plt.xlabel('Time (seconds)')
plt.ylabel('Frequency (Hertz)')
plt.savefig('freq_v_time.png')  # savefig must be called before show
                                # because show() erases the plot afterwards
plt.show()
plt.close()

# close the stream gracefully
stream.stop_stream()
stream.close()
p.terminate()
