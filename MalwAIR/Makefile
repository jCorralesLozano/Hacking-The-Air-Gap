CXXFLAGS = -Wall -std=c++14 -L/usr/local/lib -lrtaudio -I/usr/local/include/rtaudio
FILES = src/main.cpp src/Audio.cpp

MalwAIR:
	g++  -o build/MalwAIR $(FILES) $(CXXFLAGS)

clean:
	cd build && rm -f MalwAIR

run:
	cd build && ./MalwAIR ../input/hello.txt