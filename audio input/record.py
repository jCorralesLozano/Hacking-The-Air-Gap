import sounddevice as sd
from scipy.io.wavfile import write

fs = 44100  # Sample rate
seconds = 3  # Duration of recording

print(f"Recording for {seconds} seconds")

myrecording = sd.rec(int(seconds * fs), samplerate=fs, channels=2)
sd.wait()  # Wait until recording is finished
write('200.wav', fs, myrecording)  # Save as WAV file 

print("Finished recording")