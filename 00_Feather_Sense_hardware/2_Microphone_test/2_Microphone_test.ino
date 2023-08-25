/*
 * ©️2023 Interaction Magic - George Cave
 * Workshop: Prototyping with hardware and the web
 * https://interactionmagic.com
 */

// PDM = Pulse Density Modulation microphone
// More info here: https://en.wikipedia.org/wiki/Pulse-density_modulation
#include <PDM.h>

// Buffer to read samples into, each sample is 16-bits
short sample_buffer[256];

// Number of samples read since we last checked
volatile int samples_read;

void setup() {
	Serial.begin(9600);

	// When PDM configure the data receive callback
	PDM.onReceive(onPDMdata);
	PDM.begin(1, 16000);

	// Optionally set the gain, defaults to 20
	// PDM.setGain(30);
}

void loop() {

	long volume = getVolume();
	Serial.println(volume);
	delay(10);

}

// Returns approximation of the volume (loudness) detected, based on last 500 samples
int32_t getVolume(){

	int sample_to_collect = 500; 

	int min_volume = 30000;
	int max_volume = -30000;
	int count = 0; 

	while (count < sample_to_collect) {
		if (!samples_read) {
			yield();
			continue;
		}
		for (int i = 0; i < samples_read; i++) {
			min_volume = min(sample_buffer[i], min_volume);
			max_volume = max(sample_buffer[i], max_volume);
			count++;
		}
		// clear the read count
		samples_read = 0;
	}

	return max_volume - min_volume;
}

// Continually reads data from microphone and saves it into the sample_buffer
void onPDMdata() {
	// query the number of bytes available
	int bytes_available = PDM.available();

	// read into the sample buffer
	PDM.read(sample_buffer, bytes_available);

	// Save number of samples read 16-bit, 2 bytes per sample
	samples_read = bytes_available / 2;
}
