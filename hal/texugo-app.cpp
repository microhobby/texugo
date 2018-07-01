#include <stdio.h>
#include <string.h>
#include <FuelGauge.h>
#include <UdevListener.h>

int main(int argc, char *argv[])
{
	/* declare */
	udev_device * dev;
	char subsys[] = "power_supply";
	char* dev_name = (char*)"battery";
	UdevListener* udev = new UdevListener();
	FuelGauge* gauge = new FuelGauge();

	/* if argument then is the device node name */
	if (argc >= 2) {
		dev_name = argv[1];
	}

	/* initialize */
	udev->setSubSystem(subsys);
	gauge->setDeviceName(dev_name);

	while(1) {
		dev = udev->startListening();
		printf("UEVENT has been received from %s!\n",
			udev->getDeviceName());

		if (strcmp(udev->getDeviceName(), dev_name) == 0) {
			gauge->setUdevDevice(dev);
			printf("State of Charge: %d%\n",
				gauge->getStateOfCharge());
		}
	}

	return 0;
}
