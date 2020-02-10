#include "include/Audio.h"
#include <fstream>
#include <iostream>
// #include <unistd.h>
#include <windows.h>

int main(int argc, char** argv) {

	// Section for debugging
	Audio audio_hack;
	for (int i = 0; i < 34; ++i) {
		audio_hack.play_tone(i);
		char input;
		std::cout << "\nPlaying tone: " << i << " Hz. Press <enter> to go to next tone.\n";
		std::cin.get(input);
		audio_hack.stop_tone();
	}

	// // If no file is given as input argument, exit
	// if (argc < 2) {
	// 	std::cout << "No file argument." << std::endl;
	// 	return 0;
	// }
	
	// Audio audio_hack;
	// std::ifstream in_file;

	// // Open file to read in binary mode
	// in_file.open(argv[1], std::ifstream::in | std::ifstream::binary);
	// char c;

	// // Start Bridge to retrieve data
	// audio_hack.play_tone(16);
	// // usleep(1000000);
	// Sleep(300);
	// audio_hack.stop_tone();

	// // Read one byte at a time
	// while (in_file.get(c)) {
	// 	// Deconstruct the byte to two hexadecimal value
	// 	int first = c >> 4;
	// 	int second = c & 0b00001111; // Binary literal is a C++14 thing

	// 	audio_hack.play_tone(first + 18);	// Offset by 18 to play designated freq tone + the special tone
	// 	// usleep(1000000);
	// 	Sleep(300);
	// 	audio_hack.stop_tone();

	// 	audio_hack.play_tone(second);
	// 	// usleep(1000000);
	// 	Sleep(300);
	// 	audio_hack.stop_tone();
	// }

	// in_file.close();

	// // Stop Bridge from waiting for data
	// audio_hack.play_tone(17);
	// // usleep(1000000);
	// Sleep(300);
	// audio_hack.stop_tone();

	return 0;
}