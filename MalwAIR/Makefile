CXXFLAGS = -Wall -std=c++14 -L/usr/local/lib -lrtaudio -I/usr/local/include/rtaudio
FILES = src/main.cpp src/Audio.cpp

malwAIR:
	g++  -o build/malwAIR $(FILES) $(CXXFLAGS)

clean:
	cd build && rm -f malwAIR

run:
	cd build && ./malwAIR ../input/hello.txt