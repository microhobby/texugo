#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <linux/errno.h>
#include <GpioLib.h>

int main(int argc, char *argv[])
{
	/* declare */
	GPIOLib * gpio;
	int pin;

	if (argc > 1) {
		pin = atoi(argv[1]);
		printf("We are try request pin %d\n", pin);
	} else {
		printf("No pin argument %d\n", - EINVAL);
		return - EINVAL;
	}

	/* instantiate */
	gpio = new GPIOLib(pin, GPIOLib::direction::OUTPUT, "test");

	/* blink forever */
	while (1) {
		gpio->setValue(1);
		sleep(1);
		gpio->setValue(0);
	}

	return 0;
}
