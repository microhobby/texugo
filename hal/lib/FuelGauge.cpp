#include <FuelGauge.h>

FuelGauge::FuelGauge () 
{
	this->udev = udev_new();
	if (!this->udev)
		throw std::runtime_error("Cannot create udev context!");

	/* get device */
	this->dev = udev_device_new_from_syspath(udev, this->FUEL_GAUGE_SYSPATH);
}

FuelGauge::getStateOfCharge ()
{
	/* get capacity attr */
	this->soc = atoi(udev_device_get_sysattr_value(this->dev, "capacity"));
	return this->soc;
}

FuelGauge::getVoltageNow ()
{
	/* get voltage_now attr */
	this->voltage = 
		atoi(udev_device_get_sysattr_value(this->dev, "voltage_now"));

	return this->voltage / 100f;
}