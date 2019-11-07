#include "Audio.h"


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


void Audio::play_tone(int bit) {
	try {
		data.bit = bit; // If bit is greater 1, will be treated as 1.
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
	outParam->nChannels = 1; // Mono, no reason for more channels

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
	data.cur = 0;
	data.wftable_0 = (float*)calloc(data.nFrame, sizeof(float));
	data.wftable_1 = (float*)calloc(data.nFrame, sizeof(float));

	for(unsigned int i = 0; i < data.nFrame; i++) {
		// y(t) = sin(2*pi*f*t)
		// t = i / sampling_rate
		data.wftable_0[i] = sin(M_PI * 2 * 440 * i / sampling_rate);
		data.wftable_1[i] = sin(M_PI * 2 * 6000 * i / sampling_rate);
	}
}


// TODO: for parameter userdata, the Callbackdata is already a private variable
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
			memcpy(buf, data->wftable_0+(data->cur), sz * sizeof(float));
			data->cur = (data->cur + sz) % data->nFrame;
			buf += sz;
			remainFrames -= sz;
		}
	} else {
		while (remainFrames > 0) {
			unsigned int sz = data->nFrame - data->cur;
			if (sz > remainFrames)
				sz = remainFrames;
			memcpy(buf, data->wftable_1+(data->cur), sz * sizeof(float));
			data->cur = (data->cur + sz) % data->nFrame;
			buf += sz;
			remainFrames -= sz;
		}
	}
	return 0;
}