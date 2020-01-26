#ifndef AUDIO_H
#define AUDIO_H

#include "CannotHackException.h"
#include "RtAudio.h"
#define _USE_MATH_DEFINES
#include <cmath>
// #include <math.h>
#include <cstring>


class Audio {
public:
	Audio();
	~Audio();
	void play_tone(int value);
	void stop_tone();

private:
	void output_stream_setup();
	void callback_data_setup();	// Tone for bit 0 (440Hz) and 1 (6000Hz) created here
	static int rtaudio_callback(void *outbuf, void *inbuf, unsigned int nFrames,
		 double streamtime, RtAudioStreamStatus status, void *userdata);

	typedef struct {
		// TODO: change name of var bit
		unsigned int bit;		// 0 or 1, play a different tone for each
		unsigned int nFrame;	// Frame Number of Wave Table
		float *wftable_start;	// Wave Form Table(interleaved) for Start Tone
		float *wftable_stop;	// Wave Form Table(interleaved) for Stop Tone
		float *wftable_0; 		// Wave Form Table(interleaved) for 0x0
		float *wftable_1; 		// Wave Form Table(interleaved) for 0x1
		float *wftable_2; 		// Wave Form Table(interleaved) for 0x2
		float *wftable_3; 		// Wave Form Table(interleaved) for 0x3
		float *wftable_4; 		// Wave Form Table(interleaved) for 0x4
		float *wftable_5; 		// Wave Form Table(interleaved) for 0x5
		float *wftable_6; 		// Wave Form Table(interleaved) for 0x6
		float *wftable_7; 		// Wave Form Table(interleaved) for 0x7
		float *wftable_8; 		// Wave Form Table(interleaved) for 0x8
		float *wftable_9; 		// Wave Form Table(interleaved) for 0x9
		float *wftable_A; 		// Wave Form Table(interleaved) for 0xA
		float *wftable_B; 		// Wave Form Table(interleaved) for 0xB
		float *wftable_C; 		// Wave Form Table(interleaved) for 0xC
		float *wftable_D; 		// Wave Form Table(interleaved) for 0xD
		float *wftable_E; 		// Wave Form Table(interleaved) for 0xE
		float *wftable_F; 		// Wave Form Table(interleaved) for 0xF
		float *wftable_0_msb; 	// Wave Form Table(interleaved) for 0x0
		float *wftable_1_msb; 	// Wave Form Table(interleaved) for 0x1 (first half)
		float *wftable_2_msb; 	// Wave Form Table(interleaved) for 0x2 (first half)
		float *wftable_3_msb; 	// Wave Form Table(interleaved) for 0x3 (first half)
		float *wftable_4_msb; 	// Wave Form Table(interleaved) for 0x4 (first half)
		float *wftable_5_msb; 	// Wave Form Table(interleaved) for 0x5 (first half)
		float *wftable_6_msb; 	// Wave Form Table(interleaved) for 0x6 (first half)
		float *wftable_7_msb; 	// Wave Form Table(interleaved) for 0x7 (first half)
		float *wftable_8_msb; 	// Wave Form Table(interleaved) for 0x8 (first half)
		float *wftable_9_msb; 	// Wave Form Table(interleaved) for 0x9 (first half)
		float *wftable_A_msb; 	// Wave Form Table(interleaved) for 0xA (first half)
		float *wftable_B_msb; 	// Wave Form Table(interleaved) for 0xB (first half)
		float *wftable_C_msb; 	// Wave Form Table(interleaved) for 0xC (first half)
		float *wftable_D_msb; 	// Wave Form Table(interleaved) for 0xD (first half)
		float *wftable_E_msb; 	// Wave Form Table(interleaved) for 0xE (first half)
		float *wftable_F_msb; 	// Wave Form Table(interleaved) for 0xF (first half)
		unsigned int cur;		// current index of WaveFormTable(in Frame)
	} CallbackData;

	// TODO: Can I just hardcode this common sampling rate?
	unsigned int sampling_rate = 44100;
	CallbackData data;
	RtAudio* dac;
	RtAudio::StreamParameters* outParam;

};

#endif // AUDIO_H