
#include <GpioLib.h>

GPIOLib::GPIOLib (int gpiochip, int pin, GPIOLib::direction direction, const char* label) 
{
	/* open char device */
	char devchip[25];
	sprintf(devchip, "/dev/gpiochip%d", gpiochip);
	this->gpio_desc = open(devchip, 0);
	/* store pin line */
	this->gpio_pin = pin;
	this->gpio_direction = direction;
	this->gpio_label = (char*)label;

	/* request the pin*/
	this->buildRequestData();
}

void GPIOLib::buildRequestData () 
{
	/* build req data */
	gpio_req.lineoffsets[0] = this->gpio_pin;
	gpio_req.lines = 1;
	if (this->gpio_direction == GPIOLib::direction::OUTPUT)
		gpio_req.flags = GPIOHANDLE_REQUEST_OUTPUT;
	else
		gpio_req.flags = GPIOHANDLE_REQUEST_INPUT;
	strcpy(gpio_req.consumer_label, this->gpio_label);

	/* request and store */
	handle_desc = ioctl(this->gpio_desc, GPIO_GET_LINEHANDLE_IOCTL, &gpio_req);

	if (handle_desc == -1) {
		printf("Error trying to request pin %d err %s\n", gpio_pin, strerror(errno));
	}
}

int GPIOLib::getValue () 
{
	struct gpiohandle_data data;
	int ret;

	/* request value */
	ret = ioctl(gpio_req.fd, GPIOHANDLE_GET_LINE_VALUES_IOCTL, &data);

	if (ret == -1) {
		printf("Error trying to request pin %d err %s\n", 
			gpio_pin, strerror(errno));
	}

	return data.values[0];
}

void GPIOLib::setValue (int val)
{
	struct gpiohandle_data data;
	int ret;

	/* set value */
	data.values[0] = val;
	ret = ioctl(gpio_req.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);

	if (ret == -1) {
		printf("Error trying to request pin %d err %s\n", 
			gpio_pin, strerror(errno));
	}
}
