CXXFLAGS = -Wall -std=c++11 -L/usr/local/lib -lrtaudio -I/usr/local/include/rtaudio
FILES = src/main.cpp src/Audio.cpp

malwAIR:
	g++ $(CXXFLAGS) $(FILES) -o build/malwAIR

clean:
	cd build && rm -f malwAIR

run:
	cd build && ./malwAIR