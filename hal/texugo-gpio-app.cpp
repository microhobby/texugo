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
	int pin, chip;

	if (argc > 2) {
		chip = atoi(argv[1]);
		pin = atoi(argv[2]);
		printf("We are try request pin gpiochip%d %d\n", chip, pin);
	} else {
		printf("No pin or gpiochip argument %d\n", - EINVAL);
		return - EINVAL;
	}

	/* instantiate */
	gpio = new GPIOLib(chip, pin, GPIOLib::direction::OUTPUT, "test");

	/* blink forever */
	while (1) {
		gpio->setValue(1);
		sleep(1);
		gpio->setValue(0);
		sleep(1);
	}

	return 0;
}
