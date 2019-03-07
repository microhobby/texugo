#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/gpio.h>
#include <sys/ioctl.h>

int main (int argc, char *argv[]) 
{
	struct gpiohandle_request req;
	struct gpiohandle_data data;
	int fd, handle_fd, pin, ret;

	/* get pin argument */
	pin = atoi(argv[1]);

	/* open char device */
	fd = open("/dev/gpiochip6", 0);
	
	/* build request */
	req.lineoffsets[0] = pin;
	req.lines = 1;
	req.flags = GPIOHANDLE_REQUEST_OUTPUT;
	strcpy(req.consumer_label, "test");

	/* request by ioctl */
	handle_fd = ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &req);
	printf("Handle request :: %d\n", handle_fd);

	if (handle_fd == -1) {
		printf("ioctl failed and returned errno %s \n", 
			strerror(errno));
		
		exit errno;
	}

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
