#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <poll.h>
#include <fcntl.h>
#include <getopt.h>
#include <sys/ioctl.h>
#include <linux/gpio.h>

int main(int argc, char *argv[])
{
	const char *device_name = NULL;
	int fd, handle_fd, pin, ret, i;
	struct gpiochip_info cinfo;

	/* open char device */
	fd = open("/dev/gpiochip6", 0);

	/* get info */
	ret = ioctl(fd, GPIO_GET_CHIPINFO_IOCTL, &cinfo);

	/* filter by name */
	for (i = 0; i < cinfo.lines; i++) {
		struct gpioline_info linfo;

		linfo.line_offset = i;
		/* get info from each line */
		ret = ioctl(fd, GPIO_GET_LINEINFO_IOCTL, &linfo);

		if (strcmp(linfo.name, argv[1]) == 0) {
			struct gpiohandle_request req;
			struct gpiohandle_data data;

			pin = i;
			
			/* we found it */
			/* build request */
			req.lineoffsets[0] = pin;
			req.lines = 1;
			req.flags = GPIOHANDLE_REQUEST_OUTPUT;
			strcpy(req.consumer_label, "consumer_test");

			handle_fd = ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &req);

			/* blink */
			while(1) {
				data.values[0] = 1;
				ret = ioctl(req.fd, 
					GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
				sleep(1);
				data.values[0] = 0;
				ret = ioctl(req.fd, 
					GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
				sleep(1);
			}
		}
	}
}
