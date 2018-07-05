#include <main_defconfig.h>
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <UdevListener.h>

int main(int argc, char *argv[])
{
	/* declare */
	udev_device * dev;
	char wget_url[255];
	char subsys[] = PLATFORM_SUBSYS;
	char* dev_name = (char*) DEV_SOUND;
	UdevListener* udev = new UdevListener();

	/* initialize */
	udev->setSubSystem(subsys);

	while(1) {
		/* listening for uevents */
		dev = udev->startListening();

#ifdef DEBUG
		printf("UEVENT has been received from %s!\n",
			udev->getDeviceName());
#endif

		/* filter uevents */
		/* clap uevent */
		if (strcmp(udev->getDeviceName(), dev_name) == 0) {

#ifdef DEBUG
			printf("Sound Sensor Claped\n");
#endif

			/* send data for cloud */
			snprintf(wget_url, sizeof(wget_url),
			"wget -O/dev/null -q \"http://%s/iot/sound/\"",
			SERVER_IP, "bark.php");

#ifdef DEBUG
			printf("%s\n", wget_url);
#endif

			system(wget_url);
		}
	}

	return 0;
}
