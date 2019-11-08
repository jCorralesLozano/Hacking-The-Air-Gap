import matplotlib.pyplot as plt
from scipy.fftpack import fft, fftfreq
from scipy.io import wavfile # get the api
import numpy as np

fs, data = wavfile.read('1000.wav') # load the data
a = data.T[0] # this is a two channel soundtrack, I get the first track
b=[ele for ele in a] # this is 8-bit track, b is now normalized on [-1,1)
c = fft(b) # calculate fourier transform (complex numbers list)
d = len(c)/2  # you only need half of the fft list (real signal symmetry)

# print out the frequencies found
freqs = fftfreq(len(c))
print(freqs.min(), freqs.max())

# Find the peak in the coefficients
frate = 44100
idx = np.argmax(np.abs(c))
freq = freqs[idx]
freq_in_hertz = abs(freq*frate)
print(freq_in_hertz)

plt.plot(abs(c[:round(d-1)]),'r') 
plt.show()