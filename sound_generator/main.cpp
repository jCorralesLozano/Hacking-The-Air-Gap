#include "Audio.h"
#include <iostream>

int main() {
	
	Audio audio_hack;

	audio_hack.play_tone(0);
	char input;
	std::cout << "\nPlaying 0 press <enter> to quit.\n";
	std::cin.get(input);
	audio_hack.stop_tone();

	audio_hack.play_tone(1);
	std::cout << "\nPlaying 1 press <enter> to quit.\n";
	std::cin.get(input);
	audio_hack.stop_tone();

	audio_hack.play_tone(0);
	std::cout << "\nPlaying 0 press <enter> to quit.\n";
	std::cin.get(input);
	audio_hack.stop_tone();

	audio_hack.play_tone(1);
	std::cout << "\nPlaying 1 press <enter> to quit.\n";
	std::cin.get(input);
	audio_hack.stop_tone();

	return 0;
}