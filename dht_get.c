
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pi_2_mmio.h"
#include "pi_2_dht_read.h"


int main(int argc, char **argv) {
	//get specified pin from arguments
	int SIGNAL_PIN = -1;
	if(argc == 2) {
		char *end;
		SIGNAL_PIN = strtol(argv[1], &end, 10);
		if(strlen(end) != 0) {
			SIGNAL_PIN = -1;
		}
	}
	if(SIGNAL_PIN == -1) {
		printf("Please specify pin!\n");
		exit(-1);
	}

	//set up GPIO memory pointer for direct register access
	int r = pi_2_mmio_init();
	if(r != MMIO_SUCCESS) {
		printf("Error initiating Mem GPIO %d!\n", r);
		exit(-1);
	}

	pi_2_mmio_set_input(SIGNAL_PIN);

	volatile int t = 0;
	//signal pin on DHT should have a pullup, so on powerup, it should be high
	while(!pi_2_mmio_input(SIGNAL_PIN)) {
		t++;
		sleep_milliseconds(1);
		if(t > 3) {
			printf("Sensor was not detected!\n");
			exit(-1);
		}
	}

	//read data
	float humidity = 0, temperature = 0;
	int result = pi_2_dht_read(DHT22, SIGNAL_PIN, &humidity, &temperature);

	//out data
	printf("DHT out\tTemp:\t%f\tHumidity:\t%f\n", temperature, humidity);

	pi_2_mmio_set_low(SIGNAL_PIN);
	return 0;
}
