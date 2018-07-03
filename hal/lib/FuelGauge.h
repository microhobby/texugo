#ifndef __HEADER_FUELGAUGE__
#define __HEADER_FUELGAUGE__

#include <main_defconfig.h>
#include <stdio.h>
#include <libudev.h>
#include <stdexcept>

class FuelGauge {
	int soc;
	float voltage;
	char deviceName[120];
	static constexpr const char* FUEL_GAUGE_SYSPATH = 
		"/sys/class/power_supply/";
	struct udev *udev;
	struct udev_device *dev;
public:
	FuelGauge ();
	~FuelGauge ();
	int getStateOfCharge ();
	float getVoltageNow ();
	void setUdevDevice (struct udev_device *);
	void setDeviceName (char* name);
};

#endif