#include <FuelGauge.h>

FuelGauge::FuelGauge () 
{
	this->udev = udev_new();
	if (!this->udev)
		throw std::runtime_error("Cannot create udev context!");

	this->setDeviceName((char*)"battery");
	/* get device */
	this->dev = udev_device_new_from_syspath(udev, deviceName);
}

FuelGauge::~FuelGauge () 
{
	udev_device_unref(dev);
	udev_unref(udev);
}

int FuelGauge::getStateOfCharge ()
{
	/* get capacity attr */
	this->soc = atoi(udev_device_get_sysattr_value(this->dev, "capacity"));
	return this->soc;
}

float FuelGauge::getVoltageNow ()
{
	/* get voltage_now attr */
	this->voltage = 
		atoi(udev_device_get_sysattr_value(this->dev, "voltage_now"));

	return this->voltage / 100.0f;
}

void FuelGauge::setUdevDevice (struct udev_device *device) 
{
	udev_device_unref(this->dev);
	this->dev = device;
	printf("I: DEVNODE=%s\n", udev_device_get_devnode(dev));
	printf("I: KERNEL=%s\n", udev_device_get_sysname(dev));
	printf("I: DEVPATH=%s\n", udev_device_get_devpath(dev));
	printf("I: DEVTYPE=%s\n", udev_device_get_devtype(dev));
}

void FuelGauge::setDeviceName (char* name)
{
	sprintf(deviceName, "%s%s/", this->FUEL_GAUGE_SYSPATH, name);
	printf("Dev fs: %s\n", this->deviceName);
	this->dev = udev_device_new_from_syspath(udev, deviceName);
}