CXXFLAGS = -ggdb -std=c++11 -L/usr/local/lib -lrtaudio -I/usr/local/include/rtaudio

danny: main.o Audio.o
	g++ $(CXXFLAGS) main.o Audio.o -o danny

main.o: main.cpp
	g++ $(CXXFLAGS) -c main.cpp

Audio.o: Audio.cpp
	g++ $(CXXFLAGS) -c Audio.cpp

clean:
	rm *.o danny