#ifndef BYTELAYER_H
#define BYTELAYER_H

#include "Audio.h"

class ByteLayer() {
private:
	Audio audio_hack;

public:
	void send_byte(char c);
	char receive_byte();
};

#endif // BYTELAYER_H