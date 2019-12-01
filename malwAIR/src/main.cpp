#include "include/Audio.h"
#include <fstream>
#include <iostream>
#include <unistd.h>

int main(int argc, char** argv) {

	// // Section for debugging.
	// audio_hack.play_tone(0);
	// char input;
	// std::cout << "\nPress <enter> to quit.\n";
	// std::cin.get(input);
	// audio_hack.stop_tone();


	// If no file is given as input argument, exit
	if (argc < 2) {
		std::cout << "No file argument." << std::endl;
		return 0;
	}
	
	Audio audio_hack;
	std::ifstream in_file;

	// Open file to read in binary mode
	in_file.open(argv[1], std::ifstream::in | std::ifstream::binary);
	char c;

	// Smallest reading size is 1 byte at a time
	while (in_file.get(c)) {
		// Deconstruct the byte read into bits
		for (int i = 7; i >= 0; --i) {
			// Output a tone for each bit with a .5 second pause in-between each
			std::cout << ((c >> i) & 1);
			audio_hack.play_tone((c >> i) & 1);
			usleep(75000);
			audio_hack.stop_tone();
			audio_hack.play_tone(2);
			usleep(75000);
			audio_hack.stop_tone();
		}
		std::cout << std::endl;
	}

	in_file.close();
	return 0;
}