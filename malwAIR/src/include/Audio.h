#ifndef AUDIO_H
#define AUDIO_H

#include "CannotHackException.h"
#include "RtAudio.h"
#include <math.h>
#include <cstring>


class Audio {
public:
	Audio();
	~Audio();
	void play_tone(int bit);
	void stop_tone();

private:
	void output_stream_setup();
	void callback_data_setup();	// Tone for bit 0 (440Hz) and 1 (6000Hz) created here
	static int rtaudio_callback(void *outbuf, void *inbuf, unsigned int nFrames,
		 double streamtime, RtAudioStreamStatus status, void *userdata);

	typedef struct {
		unsigned int bit;		// 0 or 1, play a different tone for each
		unsigned int nFrame;	// Frame Number of Wave Table
		float *wftable_0;		// Wave Form Table(interleaved) for bit 0
		float *wftable_1;		// Wave Form Table(interleaved) for bit 1
		unsigned int cur;		// current index of WaveFormTable(in Frame)
	} CallbackData;

	// TODO: Can I just hardcode this common sampling rate?
	unsigned int sampling_rate = 44100;
	CallbackData data;
	RtAudio* dac;
	RtAudio::StreamParameters* outParam;

};

#endif // AUDIO_H