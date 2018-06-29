#ifndef __HEADER_FUELGAUGE__
#define __HEADER_FUELGAUGE__

#include <stdio.h>
#include <libudev.h>
#include <stdexcept>

class FuelGauge {
	int soc;
	float voltage;
	static constexpr const char* FUEL_GAUGE_SYSPATH = 
		"/sys/class/power_supply/battery";
	struct udev *udev;
	struct udev_device *dev;
public:
	FuelGauge ();
	int getStateOfCharge ();
	int getVoltageNow ();
};

#endif