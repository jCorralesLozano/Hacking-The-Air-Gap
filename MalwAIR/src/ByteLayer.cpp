#include "ByteLayer.h"

#define PERIOD 300

void ByteLayer::send_byte(char c) {
	int first = c >> 4;
	int second = c & 0b00001111; // Binary literal is a C++14 thing

	audio_hack.play_tone(first + 16)
	Sleep(PERIOD);
	audio_hack.stop_tone();

	audio_hack.play_tone(second);
	Sleep(PERIOD);
	audio_hack.stop_tone();
}


char ByteLayer::receive_byte() {
	
}