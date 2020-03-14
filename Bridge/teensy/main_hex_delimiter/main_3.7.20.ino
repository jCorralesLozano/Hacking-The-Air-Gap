// Teensy Audio Library Documentation: https://www.pjrc.com/teensy/gui/index.html

#include <Audio.h>
#include <Wire.h>
#include "Frequency.h"

// Global Variables
bool same_freq        = true;   // For checking that the same frequency is just being detected more than once
byte data_byte        = 0;      // 16 frequencies represent hexadecimal. 2 Hex character = 1 byte. Used for combining two bytes before sending to Pi
bool wait_for_delimiter = true;
int hex_count = 0;

AudioInputI2S            audioInput;    // audio shield: mic  
AudioFilterStateVariable filter;        // High-pass filter
// TODO: Bandstop filter so that we could use both extreme ends of available frequencies 
AudioAnalyzeFFT1024      fft1024;

AudioConnection          patchCord1(audioInput, 0, filter, 0);
AudioConnection          patchCord2(filter, 2, fft1024, 0);

AudioControlSGTL5000     audioShield;     


int find_dominant_frequency_index() {
  float dominant_amp_value = 0;
  int dominant_freq_index = 0;

  for (int i = FREQ_0_INDEX; i <= FREQ_DELIMITER + 2; ++i) {
    float amp_value = fft1024.read(i);
    // amp_value >= 0.02 for checking that frequency is at least picked up by microphone
    // TODO: play around with constraint, 0.02 seems to be good for volume at 50% with audible freq setup
    if (amp_value >= 0.02 && amp_value > dominant_amp_value) {
      dominant_amp_value = amp_value;
      dominant_freq_index = i;
    }
  }
  
  return dominant_freq_index;
}


byte hz_to_binary(int freq_index) {
  switch (freq_index) {
    case FREQ_0_INDEX:
    case FREQ_0_INDEX + 1:
    case FREQ_0_INDEX + 2:
      return B00000000;
    case FREQ_1_INDEX:
    case FREQ_1_INDEX + 1:
    case FREQ_1_INDEX + 2:
      return B00000001;
    case FREQ_2_INDEX:
    case FREQ_2_INDEX + 1:
    case FREQ_2_INDEX + 2:
      return B00000010;
    case FREQ_3_INDEX:
    case FREQ_3_INDEX + 1:
    case FREQ_3_INDEX + 2:
      return B00000011;
    case FREQ_4_INDEX:
    case FREQ_4_INDEX + 1:
    case FREQ_4_INDEX + 2:
      return B00000100;
    case FREQ_5_INDEX:
    case FREQ_5_INDEX + 1:
    case FREQ_5_INDEX + 2:
      return B00000101;
    case FREQ_6_INDEX:
    case FREQ_6_INDEX + 1:
    case FREQ_6_INDEX + 2:
      return B00000110;
    case FREQ_7_INDEX:
    case FREQ_7_INDEX + 1:
    case FREQ_7_INDEX + 2:
      return B00000111;
    case FREQ_8_INDEX:
    case FREQ_8_INDEX + 1:
    case FREQ_8_INDEX + 2:
      return B00001000;
    case FREQ_9_INDEX:
    case FREQ_9_INDEX + 1:
    case FREQ_9_INDEX + 2:
      return B00001001;
    case FREQ_A_INDEX:
    case FREQ_A_INDEX + 1:
    case FREQ_A_INDEX + 2:
      return B00001010;
    case FREQ_B_INDEX:
    case FREQ_B_INDEX + 1:
    case FREQ_B_INDEX + 2:
      return B00001011;
    case FREQ_C_INDEX:
    case FREQ_C_INDEX + 1:
    case FREQ_C_INDEX + 2:
      return B00001100;
    case FREQ_D_INDEX:
    case FREQ_D_INDEX + 1:
    case FREQ_D_INDEX + 2:
      return B00001101;
    case FREQ_E_INDEX:
    case FREQ_E_INDEX + 1:
    case FREQ_E_INDEX + 2:
      return B00001110;
    case FREQ_F_INDEX:
    case FREQ_F_INDEX + 1:
    case FREQ_F_INDEX + 2:
      return B00001111;
    default:
      // It won't ever enter this condition
      return B00000000;
  }
}


void setup() {
  Serial1.begin(115200);
  
  // Audio connections require memory to work.
  AudioMemory(30);

  // Enable the audio shield and set the output volume.
  audioShield.enable();
  audioShield.inputSelect(AUDIO_INPUT_MIC);
  audioShield.volume(0.5);  // Max value is 0.8

  // Configure the window algorithm to use
  fft1024.windowFunction(AudioWindowHanning1024);
  //fft1024.windowFunction(NULL);
  // TODO: My understanding is that if exact multiple of 43 Hz, won't need window function.
  //       From what I notice though, windowFunction seems to better identify the frequency.

  // Filter out frequencies below 800 kHz
  // TOOD: Not necessary because when looking for dominant frequency, just looking at a particular range
  filter.frequency(900);
}


void loop() {
  int data_freq_index = 0;

  if (fft1024.available()) {
    // Compute the "main" frequency value
    data_freq_index = find_dominant_frequency_index();
    
    // Debugging Output
//    Serial.print((data_freq_index));
//    Serial.println();

    if (!wait_for_delimiter && (FREQ_0_INDEX <= data_freq_index && data_freq_index <= FREQ_F_INDEX + 2)) {
      byte half_byte = hz_to_binary(data_freq_index);

//      Serial.print(data_freq_index - FREQ_0_INDEX);
//      Serial.print(' ');

      // Send byte if two hex value have been received
      if (++hex_count == 2) {
        data_byte = data_byte | half_byte;
//        Serial.print(half_byte, BIN);
//        Serial.print((char)data_byte);
//        Serial.println();
        Serial1.write(data_byte);
        data_byte = 0;
        hex_count = 0;
      } else {
        data_byte = (half_byte << 4);
      }
      wait_for_delimiter = true;
    }
    else if (wait_for_delimiter && data_freq_index >= FREQ_DELIMITER) {
      wait_for_delimiter = false;
    }
  }
}
