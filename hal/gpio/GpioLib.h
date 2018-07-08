#ifndef __HEADER_GPIOLIB__
#define __HEADER_GPIOLIB__

#include <linux/gpio.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>

class GPIOLib {
public:
	enum direction {
		INPUT,
		OUTPUT
	};

	GPIOLib (int pin, GPIOLib::direction direction, const char * label);
	int getValue ();
	void setValue (int val);
private:
	int gpio_desc;
	int gpio_pin;
	char * gpio_label;
	direction gpio_direction;
	void buildRequestData (struct gpiohandle_request *);
};

#endif