#include <main_defconfig.h>
#include <stdio.h>
#include <string.h>
#include <UdevListener.h>

int main(int argc, char *argv[])
{
	/* declare */
	udev_device * dev;
	char subsys[] = "power_supply";
	char* dev_name = (char*) DEV_BATTERY;
	UdevListener* udev = new UdevListener();

	/* initialize */
	udev->setSubSystem(subsys);

	while(1) {
		/* listening for uevents */
		dev = udev->startListening();
		printf("UEVENT has been received from %s!\n",
			udev->getDeviceName());

		/* filter uevents */
		/* clap uevent */
		if (strcmp(udev->getDeviceName(), dev_name) == 0) {
			
		}
	}

	return 0;
}
