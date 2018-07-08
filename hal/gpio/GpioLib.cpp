
#include <GpioLib.h>

GPIOLib::GPIOLib (int pin, GPIOLib::direction direction, const char* label) 
{
	/* open char device */
	this->gpio_desc = open("/dev/gpiochip0", 0);
	/* store pin line */
	this->gpio_pin = pin;
	this->gpio_direction = direction;
	this->gpio_label = (char*)label;
}

void GPIOLib::buildRequestData (struct gpiohandle_request * req) 
{
	/* build req data */
	req->lineoffsets[0] = this->gpio_pin;
	req->lines = 1;
	if (this->gpio_direction == GPIOLib::direction::OUTPUT)
		req->flags = GPIOHANDLE_REQUEST_OUTPUT;
	else
		req->flags = GPIOHANDLE_REQUEST_INPUT;
	strcpy(req->consumer_label, this->gpio_label);
}

int GPIOLib::getValue () 
{
	struct gpiohandle_data data;
	struct gpiohandle_request req;
	int handle_desc, ret;

	/* build req data */
	this->buildRequestData(&req);

	/* request value */
	handle_desc = ioctl(this->gpio_desc, GPIO_GET_LINEHANDLE_IOCTL, &req);
	ret = ioctl(req.fd, GPIOHANDLE_GET_LINE_VALUES_IOCTL, &data);

	if (ret) {
		printf("Error trying to request pin %d err %d\n", gpio_pin, ret);
	}

	return data.values[0];
}

void GPIOLib::setValue (int val)
{
	struct gpiohandle_data data;
	struct gpiohandle_request req;
	int handle_desc, ret;

	/* build req data */
	this->buildRequestData(&req);

	/* set value */
	handle_desc = ioctl(this->gpio_desc, GPIO_GET_LINEHANDLE_IOCTL, &req);
	data.values[0] = val;
	ret = ioctl(req.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);

	if (ret) {
		printf("Error trying to request pin %d err %d\n", gpio_pin, ret);
	}
}