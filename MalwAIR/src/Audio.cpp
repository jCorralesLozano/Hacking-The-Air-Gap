#include "include/Audio.h"


Audio::Audio() {
	// Construct a new RtAudio object. If no underlying audio API support 
	// is compiled, an exception will be thrown.
	try {
		dac = new RtAudio();
	} catch (RtAudioError& e) {
		throw CannotHackException("Audio: no underlying audio API support");
	}

	output_stream_setup();
	callback_data_setup();
}


Audio::~Audio() {
	if (dac->isStreamOpen())
		dac->closeStream();

	delete dac;
	delete outParam;
}


void Audio::play_tone(int value) {
	try {
		data.bit = value; // 0-15 plays equivalent hexadecimal tone
						  // 16 - start, 17 - stop, 18 - special
		dac->startStream();
	} catch (RtAudioError& e) {
		throw CannotHackException(e.what());
	}
}

void Audio::stop_tone() {
	try {
		dac->stopStream();
	} catch (RtAudioError& e) {
		throw CannotHackException(e.what());
	}
}


void Audio::output_stream_setup() {
	outParam = new RtAudio::StreamParameters();
	outParam->deviceId = dac->getDefaultOutputDevice(); // Get the default audio device
	outParam->nChannels = 2; // Stereo, one channel for special frequency

	// Specify number of sample frames that will be written to device per write operation
	unsigned int bufferFrames = 256;

	try {
		dac->openStream(outParam, NULL, RTAUDIO_FLOAT32, sampling_rate,
						&bufferFrames, rtaudio_callback, &data);
	} catch (RtAudioError& e) {
		throw CannotHackException(e.what());
	}
}


void Audio::callback_data_setup() {
	// Create Wave Form Table
	data.bit = 0;
	data.nFrame = sampling_rate; // Frame Number Sampling Rate (44100Hz)
	data.nChannel = outParam->nChannels;
	data.cur = 0;
	data.wftable_0 = (float*)calloc(data.nFrame * data.nChannel, sizeof(float));
	data.wftable_1 = (float*)calloc(data.nFrame * data.nChannel, sizeof(float));
	data.wftable_2 = (float*)calloc(data.nFrame * data.nChannel, sizeof(float));
	data.wftable_3 = (float*)calloc(data.nFrame * data.nChannel, sizeof(float));
	data.wftable_4 = (float*)calloc(data.nFrame * data.nChannel, sizeof(float));
	data.wftable_5 = (float*)calloc(data.nFrame * data.nChannel, sizeof(float));
	data.wftable_6 = (float*)calloc(data.nFrame * data.nChannel, sizeof(float));
	data.wftable_7 = (float*)calloc(data.nFrame * data.nChannel, sizeof(float));
	data.wftable_8 = (float*)calloc(data.nFrame * data.nChannel, sizeof(float));
	data.wftable_9 = (float*)calloc(data.nFrame * data.nChannel, sizeof(float));
	data.wftable_A = (float*)calloc(data.nFrame * data.nChannel, sizeof(float));
	data.wftable_B = (float*)calloc(data.nFrame * data.nChannel, sizeof(float));
	data.wftable_C = (float*)calloc(data.nFrame * data.nChannel, sizeof(float));
	data.wftable_D = (float*)calloc(data.nFrame * data.nChannel, sizeof(float));
	data.wftable_E = (float*)calloc(data.nFrame * data.nChannel, sizeof(float));
	data.wftable_F = (float*)calloc(data.nFrame * data.nChannel, sizeof(float));
	data.wftable_0_msb = (float*)calloc(data.nFrame * data.nChannel, sizeof(float));
	data.wftable_1_msb = (float*)calloc(data.nFrame * data.nChannel, sizeof(float));
	data.wftable_2_msb = (float*)calloc(data.nFrame * data.nChannel, sizeof(float));
	data.wftable_3_msb = (float*)calloc(data.nFrame * data.nChannel, sizeof(float));
	data.wftable_4_msb = (float*)calloc(data.nFrame * data.nChannel, sizeof(float));
	data.wftable_5_msb = (float*)calloc(data.nFrame * data.nChannel, sizeof(float));
	data.wftable_6_msb = (float*)calloc(data.nFrame * data.nChannel, sizeof(float));
	data.wftable_7_msb = (float*)calloc(data.nFrame * data.nChannel, sizeof(float));
	data.wftable_8_msb = (float*)calloc(data.nFrame * data.nChannel, sizeof(float));
	data.wftable_9_msb = (float*)calloc(data.nFrame * data.nChannel, sizeof(float));
	data.wftable_A_msb = (float*)calloc(data.nFrame * data.nChannel, sizeof(float));
	data.wftable_B_msb = (float*)calloc(data.nFrame * data.nChannel, sizeof(float));
	data.wftable_C_msb = (float*)calloc(data.nFrame * data.nChannel, sizeof(float));
	data.wftable_D_msb = (float*)calloc(data.nFrame * data.nChannel, sizeof(float));
	data.wftable_E_msb = (float*)calloc(data.nFrame * data.nChannel, sizeof(float));
	data.wftable_F_msb = (float*)calloc(data.nFrame * data.nChannel, sizeof(float));
	data.wftable_start = (float*)calloc(data.nFrame * data.nChannel, sizeof(float));
	data.wftable_stop = (float*)calloc(data.nFrame * data.nChannel, sizeof(float));

	// TODO: If failure to allocate memory, throw an exception
	// if (!data.wftable)
	// {
	// 	delete audio;
	// 	fprintf(stderr, "fail to allocate memory¥n");
	// 	return 1;
	// }

	for(unsigned int i = 0; i < data.nFrame; ++i) {
		// y(t) = sin(2*pi*f*t)
		// t = i / sampling_rate
		// Ultrasound binary with extra bit for distinguishing next bit
		// data.wftable_0[i] = sin(M_PI * 2 * 20000 * i / sampling_rate);
		// data.wftable_1[i] = sin(M_PI * 2 * 20100 * i / sampling_rate);
		// data.wftable_extra[i] = sin(M_PI * 2 * 20200 * i / sampling_rate);
		// Ultrasound hex protocol
		float val_20038 = sin(M_PI * 2 * 20038 * i / sampling_rate);
		float val_20081 = sin(M_PI * 2 * 20081 * i / sampling_rate);
		float val_20124 = sin(M_PI * 2 * 20124 * i / sampling_rate);
		float val_20167 = sin(M_PI * 2 * 20167 * i / sampling_rate);
		float val_20210 = sin(M_PI * 2 * 20210 * i / sampling_rate);
		float val_20253 = sin(M_PI * 2 * 20253 * i / sampling_rate);
		float val_20296 = sin(M_PI * 2 * 20296 * i / sampling_rate);
		float val_20339 = sin(M_PI * 2 * 20339 * i / sampling_rate);
		float val_20382 = sin(M_PI * 2 * 20382 * i / sampling_rate);
		float val_20425 = sin(M_PI * 2 * 20425 * i / sampling_rate);
		float val_20468 = sin(M_PI * 2 * 20468 * i / sampling_rate);
		float val_20511 = sin(M_PI * 2 * 20511 * i / sampling_rate);
		float val_20554 = sin(M_PI * 2 * 20554 * i / sampling_rate);
		float val_20597 = sin(M_PI * 2 * 20597 * i / sampling_rate);
		float val_20640 = sin(M_PI * 2 * 20640 * i / sampling_rate);
		float val_20683 = sin(M_PI * 2 * 20683 * i / sampling_rate);
		float val_20726 = sin(M_PI * 2 * 20726 * i / sampling_rate);
		float val_20769 = sin(M_PI * 2 * 20769 * i / sampling_rate);
		float val_20812 = sin(M_PI * 2 * 20812 * i / sampling_rate);

		for(unsigned int j = 0; j < data.nChannel; j++) {
			data.wftable_0[i*data.nChannel+j] = val_20038;
			data.wftable_1[i*data.nChannel+j] = val_20081;
			data.wftable_2[i*data.nChannel+j] = val_20124;
			data.wftable_3[i*data.nChannel+j] = val_20167;
			data.wftable_4[i*data.nChannel+j] = val_20210;
			data.wftable_5[i*data.nChannel+j] = val_20253;
			data.wftable_6[i*data.nChannel+j] = val_20296;
			data.wftable_7[i*data.nChannel+j] = val_20339;
			data.wftable_8[i*data.nChannel+j] = val_20382;
			data.wftable_9[i*data.nChannel+j] = val_20425;
			data.wftable_A[i*data.nChannel+j] = val_20468;
			data.wftable_B[i*data.nChannel+j] = val_20511;
			data.wftable_C[i*data.nChannel+j] = val_20554;
			data.wftable_D[i*data.nChannel+j] = val_20597;
			data.wftable_E[i*data.nChannel+j] = val_20640;
			data.wftable_F[i*data.nChannel+j] = val_20683;
			data.wftable_start[i*data.nChannel+j] = val_20726;
			data.wftable_stop[i*data.nChannel+j] = val_20769;
		}

		data.wftable_0_msb[i*data.nChannel] = val_20038;
		data.wftable_1_msb[i*data.nChannel] = val_20081;
		data.wftable_2_msb[i*data.nChannel] = val_20124;
		data.wftable_3_msb[i*data.nChannel] = val_20167;
		data.wftable_4_msb[i*data.nChannel] = val_20210;
		data.wftable_5_msb[i*data.nChannel] = val_20253;
		data.wftable_6_msb[i*data.nChannel] = val_20296;
		data.wftable_7_msb[i*data.nChannel] = val_20339;
		data.wftable_8_msb[i*data.nChannel] = val_20382;
		data.wftable_9_msb[i*data.nChannel] = val_20425;
		data.wftable_A_msb[i*data.nChannel] = val_20468;
		data.wftable_B_msb[i*data.nChannel] = val_20511;
		data.wftable_C_msb[i*data.nChannel] = val_20554;
		data.wftable_D_msb[i*data.nChannel] = val_20597;
		data.wftable_E_msb[i*data.nChannel] = val_20640;
		data.wftable_F_msb[i*data.nChannel] = val_20683;

		data.wftable_0_msb[i*data.nChannel+1] = val_20812;
		data.wftable_1_msb[i*data.nChannel+1] = val_20812;
		data.wftable_2_msb[i*data.nChannel+1] = val_20812;
		data.wftable_3_msb[i*data.nChannel+1] = val_20812;
		data.wftable_4_msb[i*data.nChannel+1] = val_20812;
		data.wftable_5_msb[i*data.nChannel+1] = val_20812;
		data.wftable_6_msb[i*data.nChannel+1] = val_20812;
		data.wftable_7_msb[i*data.nChannel+1] = val_20812;
		data.wftable_8_msb[i*data.nChannel+1] = val_20812;
		data.wftable_9_msb[i*data.nChannel+1] = val_20812;
		data.wftable_A_msb[i*data.nChannel+1] = val_20812;
		data.wftable_B_msb[i*data.nChannel+1] = val_20812;
		data.wftable_C_msb[i*data.nChannel+1] = val_20812;
		data.wftable_D_msb[i*data.nChannel+1] = val_20812;
		data.wftable_E_msb[i*data.nChannel+1] = val_20812;
		data.wftable_F_msb[i*data.nChannel+1] = val_20812;
	}
}


// TODO: for parameter userdata, the Callbackdata is already a private variable
// TODO: a lot of copy and paste, can we shrink it some
int Audio::rtaudio_callback(void* outbuf, void* inbuf, unsigned int nFrames, 
	double streamtime, RtAudioStreamStatus status, void *userdata)
{
	float* buf = (float*)outbuf;
	CallbackData* data = (CallbackData*)userdata;
	unsigned int remainFrames = nFrames;

	if (data->bit == 0) {
		while (remainFrames > 0) {
			unsigned int sz = data->nFrame - data->cur;
			if (sz > remainFrames)
				sz = remainFrames;
			memcpy(buf, data->wftable_0+(data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
			data->cur = (data->cur + sz) % data->nFrame;
			buf += sz * data->nChannel;
			remainFrames -= sz;
		}
	} else if (data->bit == 1) {
		while (remainFrames > 0) {
			unsigned int sz = data->nFrame - data->cur;
			if (sz > remainFrames)
				sz = remainFrames;
			memcpy(buf, data->wftable_1+(data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
			data->cur = (data->cur + sz) % data->nFrame;
			buf += sz * data->nChannel;
			remainFrames -= sz;
		}
	} else if (data->bit == 2) {
		while (remainFrames > 0) {
			unsigned int sz = data->nFrame - data->cur;
			if (sz > remainFrames)
				sz = remainFrames;
			memcpy(buf, data->wftable_2+(data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
			data->cur = (data->cur + sz) % data->nFrame;
			buf += sz * data->nChannel;
			remainFrames -= sz;
		}
	} else if (data->bit == 3) {
		while (remainFrames > 0) {
			unsigned int sz = data->nFrame - data->cur;
			if (sz > remainFrames)
				sz = remainFrames;
			memcpy(buf, data->wftable_3+(data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
			data->cur = (data->cur + sz) % data->nFrame;
			buf += sz * data->nChannel;
			remainFrames -= sz;
		}
	} else if (data->bit == 4) {
		while (remainFrames > 0) {
			unsigned int sz = data->nFrame - data->cur;
			if (sz > remainFrames)
				sz = remainFrames;
			memcpy(buf, data->wftable_4+(data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
			data->cur = (data->cur + sz) % data->nFrame;
			buf += sz * data->nChannel;
			remainFrames -= sz;
		}
	} else if (data->bit == 5) {
		while (remainFrames > 0) {
			unsigned int sz = data->nFrame - data->cur;
			if (sz > remainFrames)
				sz = remainFrames;
			memcpy(buf, data->wftable_5+(data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
			data->cur = (data->cur + sz) % data->nFrame;
			buf += sz * data->nChannel;
			remainFrames -= sz;
		}
	} else if (data->bit == 6) {
		while (remainFrames > 0) {
			unsigned int sz = data->nFrame - data->cur;
			if (sz > remainFrames)
				sz = remainFrames;
			memcpy(buf, data->wftable_6+(data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
			data->cur = (data->cur + sz) % data->nFrame;
			buf += sz * data->nChannel;
			remainFrames -= sz;
		}
	} else if (data->bit == 7) {
		while (remainFrames > 0) {
			unsigned int sz = data->nFrame - data->cur;
			if (sz > remainFrames)
				sz = remainFrames;
			memcpy(buf, data->wftable_7+(data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
			data->cur = (data->cur + sz) % data->nFrame;
			buf += sz * data->nChannel;
			remainFrames -= sz;
		}
	} else if (data->bit == 8) {
		while (remainFrames > 0) {
			unsigned int sz = data->nFrame - data->cur;
			if (sz > remainFrames)
				sz = remainFrames;
			memcpy(buf, data->wftable_8+(data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
			data->cur = (data->cur + sz) % data->nFrame;
			buf += sz * data->nChannel;
			remainFrames -= sz;
		}
	} else if (data->bit == 9) {
		while (remainFrames > 0) {
			unsigned int sz = data->nFrame - data->cur;
			if (sz > remainFrames)
				sz = remainFrames;
			memcpy(buf, data->wftable_9+(data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
			data->cur = (data->cur + sz) % data->nFrame;
			buf += sz * data->nChannel;
			remainFrames -= sz;
		}
	} else if (data->bit == 10) {
		while (remainFrames > 0) {
			unsigned int sz = data->nFrame - data->cur;
			if (sz > remainFrames)
				sz = remainFrames;
			memcpy(buf, data->wftable_A+(data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
			data->cur = (data->cur + sz) % data->nFrame;
			buf += sz * data->nChannel;
			remainFrames -= sz;
		}
	} else if (data->bit == 11) {
		while (remainFrames > 0) {
			unsigned int sz = data->nFrame - data->cur;
			if (sz > remainFrames)
				sz = remainFrames;
			memcpy(buf, data->wftable_B+(data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
			data->cur = (data->cur + sz) % data->nFrame;
			buf += sz * data->nChannel;
			remainFrames -= sz;
		}
	} else if (data->bit == 12) {
		while (remainFrames > 0) {
			unsigned int sz = data->nFrame - data->cur;
			if (sz > remainFrames)
				sz = remainFrames;
			memcpy(buf, data->wftable_C+(data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
			data->cur = (data->cur + sz) % data->nFrame;
			buf += sz * data->nChannel;
			remainFrames -= sz;
		}
	} else if (data->bit == 13) {
		while (remainFrames > 0) {
			unsigned int sz = data->nFrame - data->cur;
			if (sz > remainFrames)
				sz = remainFrames;
			memcpy(buf, data->wftable_D+(data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
			data->cur = (data->cur + sz) % data->nFrame;
			buf += sz * data->nChannel;
			remainFrames -= sz;
		}
	} else if (data->bit == 14) {
		while (remainFrames > 0) {
			unsigned int sz = data->nFrame - data->cur;
			if (sz > remainFrames)
				sz = remainFrames;
			memcpy(buf, data->wftable_E+(data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
			data->cur = (data->cur + sz) % data->nFrame;
			buf += sz * data->nChannel;
			remainFrames -= sz;
		}
	} else if (data->bit == 15) {
		while (remainFrames > 0) {
			unsigned int sz = data->nFrame - data->cur;
			if (sz > remainFrames)
				sz = remainFrames;
			memcpy(buf, data->wftable_F+(data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
			data->cur = (data->cur + sz) % data->nFrame;
			buf += sz * data->nChannel;
			remainFrames -= sz;
		}
	} else if (data->bit == 16) {	// Start tone
		while (remainFrames > 0) {
			unsigned int sz = data->nFrame - data->cur;
			if (sz > remainFrames)
				sz = remainFrames;
			memcpy(buf, data->wftable_start+(data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
			data->cur = (data->cur + sz) % data->nFrame;
			buf += sz * data->nChannel;
			remainFrames -= sz;
		}
	} else if (data->bit == 17) {	// Stop tone
		while (remainFrames > 0) {
			unsigned int sz = data->nFrame - data->cur;
			if (sz > remainFrames)
				sz = remainFrames;
			memcpy(buf, data->wftable_stop+(data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
			data->cur = (data->cur + sz) % data->nFrame;
			buf += sz * data->nChannel;
			remainFrames -= sz;
		}
	} else if (data->bit == 18) {
		while (remainFrames > 0) {
			unsigned int sz = data->nFrame - data->cur;
			if (sz > remainFrames)
				sz = remainFrames;
			memcpy(buf, data->wftable_0_msb+(data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
			data->cur = (data->cur + sz) % data->nFrame;
			buf += sz * data->nChannel;
			remainFrames -= sz;
		}
	} else if (data->bit == 19) {
		while (remainFrames > 0) {
			unsigned int sz = data->nFrame - data->cur;
			if (sz > remainFrames)
				sz = remainFrames;
			memcpy(buf, data->wftable_1_msb+(data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
			data->cur = (data->cur + sz) % data->nFrame;
			buf += sz * data->nChannel;
			remainFrames -= sz;
		}
	} else if (data->bit == 20) {
		while (remainFrames > 0) {
			unsigned int sz = data->nFrame - data->cur;
			if (sz > remainFrames)
				sz = remainFrames;
			memcpy(buf, data->wftable_2_msb+(data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
			data->cur = (data->cur + sz) % data->nFrame;
			buf += sz * data->nChannel;
			remainFrames -= sz;
		}
	} else if (data->bit == 21) {
		while (remainFrames > 0) {
			unsigned int sz = data->nFrame - data->cur;
			if (sz > remainFrames)
				sz = remainFrames;
			memcpy(buf, data->wftable_3_msb+(data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
			data->cur = (data->cur + sz) % data->nFrame;
			buf += sz * data->nChannel;
			remainFrames -= sz;
		}
	} else if (data->bit == 22) {
		while (remainFrames > 0) {
			unsigned int sz = data->nFrame - data->cur;
			if (sz > remainFrames)
				sz = remainFrames;
			memcpy(buf, data->wftable_4_msb+(data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
			data->cur = (data->cur + sz) % data->nFrame;
			buf += sz * data->nChannel;
			remainFrames -= sz;
		}
	} else if (data->bit == 23) {
		while (remainFrames > 0) {
			unsigned int sz = data->nFrame - data->cur;
			if (sz > remainFrames)
				sz = remainFrames;
			memcpy(buf, data->wftable_5_msb+(data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
			data->cur = (data->cur + sz) % data->nFrame;
			buf += sz * data->nChannel;
			remainFrames -= sz;
		}
	} else if (data->bit == 24) {
		while (remainFrames > 0) {
			unsigned int sz = data->nFrame - data->cur;
			if (sz > remainFrames)
				sz = remainFrames;
			memcpy(buf, data->wftable_6_msb+(data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
			data->cur = (data->cur + sz) % data->nFrame;
			buf += sz * data->nChannel;
			remainFrames -= sz;
		}
	} else if (data->bit == 25) {
		while (remainFrames > 0) {
			unsigned int sz = data->nFrame - data->cur;
			if (sz > remainFrames)
				sz = remainFrames;
			memcpy(buf, data->wftable_7_msb+(data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
			data->cur = (data->cur + sz) % data->nFrame;
			buf += sz * data->nChannel;
			remainFrames -= sz;
		}
	} else if (data->bit == 26) {
		while (remainFrames > 0) {
			unsigned int sz = data->nFrame - data->cur;
			if (sz > remainFrames)
				sz = remainFrames;
			memcpy(buf, data->wftable_8_msb+(data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
			data->cur = (data->cur + sz) % data->nFrame;
			buf += sz * data->nChannel;
			remainFrames -= sz;
		}
	} else if (data->bit == 27) {
		while (remainFrames > 0) {
			unsigned int sz = data->nFrame - data->cur;
			if (sz > remainFrames)
				sz = remainFrames;
			memcpy(buf, data->wftable_9_msb+(data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
			data->cur = (data->cur + sz) % data->nFrame;
			buf += sz * data->nChannel;
			remainFrames -= sz;
		}
	} else if (data->bit == 28) {
		while (remainFrames > 0) {
			unsigned int sz = data->nFrame - data->cur;
			if (sz > remainFrames)
				sz = remainFrames;
			memcpy(buf, data->wftable_A_msb+(data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
			data->cur = (data->cur + sz) % data->nFrame;
			buf += sz * data->nChannel;
			remainFrames -= sz;
		}
	} else if (data->bit == 29) {
		while (remainFrames > 0) {
			unsigned int sz = data->nFrame - data->cur;
			if (sz > remainFrames)
				sz = remainFrames;
			memcpy(buf, data->wftable_B_msb+(data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
			data->cur = (data->cur + sz) % data->nFrame;
			buf += sz * data->nChannel;
			remainFrames -= sz;
		}
	} else if (data->bit == 30) {
		while (remainFrames > 0) {
			unsigned int sz = data->nFrame - data->cur;
			if (sz > remainFrames)
				sz = remainFrames;
			memcpy(buf, data->wftable_C_msb+(data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
			data->cur = (data->cur + sz) % data->nFrame;
			buf += sz * data->nChannel;
			remainFrames -= sz;
		}
	} else if (data->bit == 31) {
		while (remainFrames > 0) {
			unsigned int sz = data->nFrame - data->cur;
			if (sz > remainFrames)
				sz = remainFrames;
			memcpy(buf, data->wftable_D_msb+(data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
			data->cur = (data->cur + sz) % data->nFrame;
			buf += sz * data->nChannel;
			remainFrames -= sz;
		}
	} else if (data->bit == 32) {
		while (remainFrames > 0) {
			unsigned int sz = data->nFrame - data->cur;
			if (sz > remainFrames)
				sz = remainFrames;
			memcpy(buf, data->wftable_E_msb+(data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
			data->cur = (data->cur + sz) % data->nFrame;
			buf += sz * data->nChannel;
			remainFrames -= sz;
		}
	} else if (data->bit == 33) {
		while (remainFrames > 0) {
			unsigned int sz = data->nFrame - data->cur;
			if (sz > remainFrames)
				sz = remainFrames;
			memcpy(buf, data->wftable_F_msb+(data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
			data->cur = (data->cur + sz) % data->nFrame;
			buf += sz * data->nChannel;
			remainFrames -= sz;
		}
	}

	// TODO: Shouldn't need an else, throw an exception though if it enters it.

	return 0;
}