#ifndef __HEADER_GPIOLIB__
#define __HEADER_GPIOLIB__

#include <linux/gpio.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>

class GPIOLib {
public:
	enum direction {
		INPUT,
		OUTPUT
	};

	GPIOLib (int gpiochip, int pin, GPIOLib::direction direction, const char * label);
	int getValue ();
	void setValue (int val);
private:
	int gpio_desc;
	int gpio_pin;
	char * gpio_label;
	struct gpiohandle_request gpio_req;
	int handle_desc;
	direction gpio_direction;
	void buildRequestData ();
};

#endif
