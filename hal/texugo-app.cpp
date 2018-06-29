#include <stdio.h>
#include <FuelGauge.h>
#include <UdevListener.h>

int main(int argc, char *argv[])
{
	/* declare */
	char subsys[] = "power_supply";
	char dev_name[] = "BAT1";
	UdevListener* udev = new UdevListener();
	FuelGauge* gauge = new FuelGauge();

	/* initialize */
	udev->setSubSystem(subsys);
	gauge->setDeviceName(dev_name);

	while(1) {
		udev->startListening();
		printf("UEVENT has been received from %s!\n", 
			udev->getDeviceName());
		printf("Stage of Charge: %d%\n", gauge->getStateOfCharge());
	}

	return 0;
}