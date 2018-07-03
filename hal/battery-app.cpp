#include <main_defconfig.h>
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <FuelGauge.h>
#include <UdevListener.h>

int main(int argc, char *argv[])
{
	/* declare */
	udev_device * dev;
	char wget_url[255];
	char subsys[] = POWER_SUPPLY_SUBSYS;
	char* dev_name = (char*) DEV_BATTERY;
	UdevListener* udev = new UdevListener();
	FuelGauge* gauge = new FuelGauge();

	/* initialize */
	udev->setSubSystem(subsys);
	gauge->setDeviceName(dev_name);

	while(1) {
		/* listening for uevents */
		dev = udev->startListening();
		printf("UEVENT has been received from %s!\n",
			udev->getDeviceName());

		/* filter uevents */
		/* battery uevent */
		if (strcmp(udev->getDeviceName(), dev_name) == 0) {
			/* set uevent object */
			gauge->setUdevDevice(dev);

			/* print battery level and voltage now */
			printf("State of Charge: %d%\n",
				gauge->getStateOfCharge());
			printf("Battery Voltage: %f\n", 
				gauge->getVoltageNow());

			/* send data for cloud */
			snprintf(wget_url, sizeof(wget_url),
			"wget -O/dev/null -q \"http://%s/iot/battery/%sSOC=%d&Volt=%f\"",
			SERVER_IP, "set.php?", 
				gauge->getStateOfCharge(),
				gauge->getVoltageNow());
			printf("%s\n", wget_url);
			system(wget_url);
		}
	}

	return 0;
}
