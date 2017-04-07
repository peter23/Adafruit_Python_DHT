
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


	pi_2_mmio_set_output(SIGNAL_PIN);
	pi_2_mmio_set_high(SIGNAL_PIN);


	return 0;
}
