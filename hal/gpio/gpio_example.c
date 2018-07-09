#include <stdio.h>
#include <string.h>
#include <linux/gpio.h>
#include <sys/ioctl.h>

int main (int argc, char *argv[]) 
{
	struct gpiohandle_request req;
	struct gpiohandle_data data;
	int fd, handle_fd, pin;

	/* get pin argument */
	pin = atoi(argv[1]);

	/* open char device */
	fd = open("/dev/gpiochip0", 0);
	
	/* build request */
	req.lineoffsets[0] = pin;
	req.lines = 1;
	req.flags = GPIOHANDLE_REQUEST_OUTPUT;
	strcpy(req.consumer_label, "test");

	/* request by ioctl */
	handle_fd = ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &req);

	/* blink forever */
	while (1) {
		data.values[0] = 1;
		ret = ioctl(req.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
		sleep(1);
		data.values[0] = 0;
		ret = ioctl(req.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
		sleep(1);
	}

	return 0;
}

