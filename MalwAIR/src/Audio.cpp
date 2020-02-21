#include "include/Audio.h"


Audio::Audio() {
	// Construct a new RtAudio object. If no underlying audio API support 
	// is compiled, an exception will be thrown.
	try {
		adac = new RtAudio();
	} catch (RtAudioError& e) {
		throw CannotHackException("Audio: no underlying audio API support");
	}

	stream_setup();
	callback_data_setup();
	adac->startStream();
}


Audio::~Audio() {
	adac->stopStream();
	if (adac->isStreamOpen())
		adac->closeStream();

	delete adac;
	delete inParam;
	delete outParam;
}


void Audio::play_tone(int value) {
	try {
		data.bit = value; // 0-15 plays equivalent hexadecimal tone for second hex (4 LSBs)
						  // 16-31 plays equivalent hexadecimal tone for second hex (4 LSBs)
						  // 32 plays start
						  // 33 plays stop
		// adac->startStream();
	} catch (RtAudioError& e) {
		throw CannotHackException(e.what());
	}
}


void Audio::stream_setup() {
	inParam = new RtAudio::StreamParameters();
	outParam = new RtAudio::StreamParameters();

	inParam->deviceId = adac->getDefaultInputDevice();
	inParam->nChannels = 2; // Maybe one is all that is needed
	outParam->deviceId = adac->getDefaultOutputDevice();
	outParam->nChannels = 2; // Stereo, one channel for special frequency

	unsigned int bufferFrames = 256;

	try {
		adac->openStream(outParam, inParam, RTAUDIO_FLOAT32, sampling_rate,
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
	data.wftable_0_lsb = (float*)calloc(data.nFrame * data.nChannel, sizeof(float));
	data.wftable_1_lsb = (float*)calloc(data.nFrame * data.nChannel, sizeof(float));
	data.wftable_2_lsb = (float*)calloc(data.nFrame * data.nChannel, sizeof(float));
	data.wftable_3_lsb = (float*)calloc(data.nFrame * data.nChannel, sizeof(float));
	data.wftable_4_lsb = (float*)calloc(data.nFrame * data.nChannel, sizeof(float));
	data.wftable_5_lsb = (float*)calloc(data.nFrame * data.nChannel, sizeof(float));
	data.wftable_6_lsb = (float*)calloc(data.nFrame * data.nChannel, sizeof(float));
	data.wftable_7_lsb = (float*)calloc(data.nFrame * data.nChannel, sizeof(float));
	data.wftable_8_lsb = (float*)calloc(data.nFrame * data.nChannel, sizeof(float));
	data.wftable_9_lsb = (float*)calloc(data.nFrame * data.nChannel, sizeof(float));
	data.wftable_A_lsb = (float*)calloc(data.nFrame * data.nChannel, sizeof(float));
	data.wftable_B_lsb = (float*)calloc(data.nFrame * data.nChannel, sizeof(float));
	data.wftable_C_lsb = (float*)calloc(data.nFrame * data.nChannel, sizeof(float));
	data.wftable_D_lsb = (float*)calloc(data.nFrame * data.nChannel, sizeof(float));
	data.wftable_E_lsb = (float*)calloc(data.nFrame * data.nChannel, sizeof(float));
	data.wftable_F_lsb = (float*)calloc(data.nFrame * data.nChannel, sizeof(float));
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
		float freq_0_sample_val = sin(M_PI * 2 * FREQ_0 * i / sampling_rate);
		float freq_1_sample_val = sin(M_PI * 2 * FREQ_1 * i / sampling_rate);
		float freq_2_sample_val = sin(M_PI * 2 * FREQ_2 * i / sampling_rate);
		float freq_3_sample_val = sin(M_PI * 2 * FREQ_3 * i / sampling_rate);
		float freq_4_sample_val = sin(M_PI * 2 * FREQ_4 * i / sampling_rate);
		float freq_5_sample_val = sin(M_PI * 2 * FREQ_5 * i / sampling_rate);
		float freq_6_sample_val = sin(M_PI * 2 * FREQ_6 * i / sampling_rate);
		float freq_7_sample_val = sin(M_PI * 2 * FREQ_7 * i / sampling_rate);
		float freq_8_sample_val = sin(M_PI * 2 * FREQ_8 * i / sampling_rate);
		float freq_9_sample_val = sin(M_PI * 2 * FREQ_9 * i / sampling_rate);
		float freq_A_sample_val = sin(M_PI * 2 * FREQ_A * i / sampling_rate);
		float freq_B_sample_val = sin(M_PI * 2 * FREQ_B * i / sampling_rate);
		float freq_C_sample_val = sin(M_PI * 2 * FREQ_C * i / sampling_rate);
		float freq_D_sample_val = sin(M_PI * 2 * FREQ_D * i / sampling_rate);
		float freq_E_sample_val = sin(M_PI * 2 * FREQ_E * i / sampling_rate);
		float freq_F_sample_val = sin(M_PI * 2 * FREQ_F * i / sampling_rate);
		float freq_start_sample_val = sin(M_PI * 2 * FREQ_START * i / sampling_rate);
		float freq_stop_sample_val = sin(M_PI * 2 * FREQ_STOP * i / sampling_rate);
		float freq_special_sample_val = sin(M_PI * 2 * FREQ_SPECIAL * i / sampling_rate);

		// For the second hex values (the 4 least significant bits), start, and stop,
		// both channels will output the same tone
		for(unsigned int j = 0; j < data.nChannel; j++) {
			data.wftable_0_lsb[i*data.nChannel+j] = freq_0_sample_val;
			data.wftable_1_lsb[i*data.nChannel+j] = freq_1_sample_val;
			data.wftable_2_lsb[i*data.nChannel+j] = freq_2_sample_val;
			data.wftable_3_lsb[i*data.nChannel+j] = freq_3_sample_val;
			data.wftable_4_lsb[i*data.nChannel+j] = freq_4_sample_val;
			data.wftable_5_lsb[i*data.nChannel+j] = freq_5_sample_val;
			data.wftable_6_lsb[i*data.nChannel+j] = freq_6_sample_val;
			data.wftable_7_lsb[i*data.nChannel+j] = freq_7_sample_val;
			data.wftable_8_lsb[i*data.nChannel+j] = freq_8_sample_val;
			data.wftable_9_lsb[i*data.nChannel+j] = freq_9_sample_val;
			data.wftable_A_lsb[i*data.nChannel+j] = freq_A_sample_val;
			data.wftable_B_lsb[i*data.nChannel+j] = freq_B_sample_val;
			data.wftable_C_lsb[i*data.nChannel+j] = freq_C_sample_val;
			data.wftable_D_lsb[i*data.nChannel+j] = freq_D_sample_val;
			data.wftable_E_lsb[i*data.nChannel+j] = freq_E_sample_val;
			data.wftable_F_lsb[i*data.nChannel+j] = freq_F_sample_val;
			data.wftable_start[i*data.nChannel+j] = freq_start_sample_val;
			data.wftable_stop[i*data.nChannel+j] = freq_stop_sample_val;
		}

		// For the first hex values (the 4 most significant bits), channel 1 outputs hex tone,
		// ...
		data.wftable_0_msb[i*data.nChannel] = freq_0_sample_val;
		data.wftable_1_msb[i*data.nChannel] = freq_1_sample_val;
		data.wftable_2_msb[i*data.nChannel] = freq_2_sample_val;
		data.wftable_3_msb[i*data.nChannel] = freq_3_sample_val;
		data.wftable_4_msb[i*data.nChannel] = freq_4_sample_val;
		data.wftable_5_msb[i*data.nChannel] = freq_5_sample_val;
		data.wftable_6_msb[i*data.nChannel] = freq_6_sample_val;
		data.wftable_7_msb[i*data.nChannel] = freq_7_sample_val;
		data.wftable_8_msb[i*data.nChannel] = freq_8_sample_val;
		data.wftable_9_msb[i*data.nChannel] = freq_9_sample_val;
		data.wftable_A_msb[i*data.nChannel] = freq_A_sample_val;
		data.wftable_B_msb[i*data.nChannel] = freq_B_sample_val;
		data.wftable_C_msb[i*data.nChannel] = freq_C_sample_val;
		data.wftable_D_msb[i*data.nChannel] = freq_D_sample_val;
		data.wftable_E_msb[i*data.nChannel] = freq_E_sample_val;
		data.wftable_F_msb[i*data.nChannel] = freq_F_sample_val;

		// ...
		// but channel 2 outputs special tone, denoting that it is the first hex value
		data.wftable_0_msb[i*data.nChannel+1] = freq_special_sample_val;
		data.wftable_1_msb[i*data.nChannel+1] = freq_special_sample_val;
		data.wftable_2_msb[i*data.nChannel+1] = freq_special_sample_val;
		data.wftable_3_msb[i*data.nChannel+1] = freq_special_sample_val;
		data.wftable_4_msb[i*data.nChannel+1] = freq_special_sample_val;
		data.wftable_5_msb[i*data.nChannel+1] = freq_special_sample_val;
		data.wftable_6_msb[i*data.nChannel+1] = freq_special_sample_val;
		data.wftable_7_msb[i*data.nChannel+1] = freq_special_sample_val;
		data.wftable_8_msb[i*data.nChannel+1] = freq_special_sample_val;
		data.wftable_9_msb[i*data.nChannel+1] = freq_special_sample_val;
		data.wftable_A_msb[i*data.nChannel+1] = freq_special_sample_val;
		data.wftable_B_msb[i*data.nChannel+1] = freq_special_sample_val;
		data.wftable_C_msb[i*data.nChannel+1] = freq_special_sample_val;
		data.wftable_D_msb[i*data.nChannel+1] = freq_special_sample_val;
		data.wftable_E_msb[i*data.nChannel+1] = freq_special_sample_val;
		data.wftable_F_msb[i*data.nChannel+1] = freq_special_sample_val;
	}
}


int Audio::rtaudio_callback(void* outbuf, void* inbuf, unsigned int nFrames, 
	double streamtime, RtAudioStreamStatus status, void* userdata)
{
	// TODO: Throw an exception?
	// if (status)
	// 	std::cout << "Stream over/underflow detected!" << std::endl;

	// Output audio
	float* buf = (float*)outbuf;
	CallbackData* data = (CallbackData*)userdata;
	unsigned int remainFrames = nFrames;

	while (remainFrames > 0) {
		unsigned int sz = data->nFrame - data->cur;
		if (sz > remainFrames)
			sz = remainFrames;

		switch (data->bit) {
			case 0:
				memcpy(buf, data->wftable_0_lsb + (data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
				break;
			case 1:
				memcpy(buf, data->wftable_1_lsb + (data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
				break;
			case 2:
				memcpy(buf, data->wftable_2_lsb + (data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
				break;
			case 3:
				memcpy(buf, data->wftable_3_lsb + (data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
				break;
			case 4:
				memcpy(buf, data->wftable_4_lsb + (data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
				break;
			case 5:
				memcpy(buf, data->wftable_5_lsb + (data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
				break;
			case 6:
				memcpy(buf, data->wftable_6_lsb + (data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
				break;
			case 7:
				memcpy(buf, data->wftable_7_lsb + (data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
				break;
			case 8:
				memcpy(buf, data->wftable_8_lsb + (data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
				break;
			case 9:
				memcpy(buf, data->wftable_9_lsb + (data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
				break;
			case 10:
				memcpy(buf, data->wftable_A_lsb + (data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
				break;
			case 11:
				memcpy(buf, data->wftable_B_lsb + (data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
				break;
			case 12:
				memcpy(buf, data->wftable_C_lsb + (data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
				break;
			case 13:
				memcpy(buf, data->wftable_D_lsb + (data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
				break;
			case 14:
				memcpy(buf, data->wftable_E_lsb + (data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
				break;
			case 15:
				memcpy(buf, data->wftable_F_lsb + (data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
				break;
			case 16:
				memcpy(buf, data->wftable_0_msb + (data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
				break;
			case 17:
				memcpy(buf, data->wftable_1_msb + (data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
				break;
			case 18:
				memcpy(buf, data->wftable_2_msb + (data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
				break;
			case 19:
				memcpy(buf, data->wftable_3_msb + (data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
				break;
			case 20:
				memcpy(buf, data->wftable_4_msb + (data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
				break;
			case 21:
				memcpy(buf, data->wftable_5_msb + (data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
				break;
			case 22:
				memcpy(buf, data->wftable_6_msb + (data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
				break;
			case 23:
				memcpy(buf, data->wftable_7_msb + (data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
				break;
			case 24:
				memcpy(buf, data->wftable_8_msb + (data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
				break;
			case 25:
				memcpy(buf, data->wftable_9_msb + (data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
				break;
			case 26:
				memcpy(buf, data->wftable_A_msb + (data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
				break;
			case 27:
				memcpy(buf, data->wftable_B_msb + (data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
				break;
			case 28:
				memcpy(buf, data->wftable_C_msb + (data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
				break;
			case 29:
				memcpy(buf, data->wftable_D_msb + (data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
				break;
			case 30:
				memcpy(buf, data->wftable_E_msb + (data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
				break;
			case 31:
				memcpy(buf, data->wftable_F_msb + (data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
				break;
			case 32:
				memcpy(buf, data->wftable_start + (data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
				break;
			case 33:
				memcpy(buf, data->wftable_stop + (data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
				break;
			default: // TODO: Maybe throw an exception here, or leave it up to user to avoid ending up here
				memcpy(buf, data->wftable_stop + (data->cur*data->nChannel), sz * data->nChannel * sizeof(float));
				break;
		}

		data->cur = (data->cur + sz) % data->nFrame;
		buf += sz * data->nChannel;
		remainFrames -= sz;
	}

	// Process audio input
	// cout << 

	return 0;
}