#!/bin/bash

echo "WELCOME TO TEXUGO"
echo ""

echo "MOUNT DISTRO"
mount -t proc proc proc/
mount -t sysfs sys sys/
mount -o bind /dev dev/
echo ""

echo "TMPFS" 
/bin/./systemd-tmpfiles --prefix=/dev --create --boot &
echo ""

echo "FSCK"
/lib/systemd/./systemd-fsck &

echo "LOAD DRIVERS" 
/lib/systemd/./systemd-modules-load
echo ""

echo "REMOUNT" 
/lib/systemd/./systemd-remount-fs
echo ""

echo "SEED" 
/lib/systemd/./systemd-random-seed load
echo ""

echo "UDEV CONTROLL" 
/lib/systemd/./systemd-udevd &
echo ""

echo "TRIGOR UDEV" 
/bin/./udevadm trigger --type=subsystems --action=add &
/bin/./udevadm trigger --type=devices --action=add &
echo ""

echo "VOLATILE FS"
/bin/./systemd-tmpfiles --create --remove --boot --exclude-prefix=/dev
echo ""

echo "WPA"
/sbin/wpa_supplicant -u -s -O /run/wpa_supplicant
echo ""

echo "RAISE NET" 
/sbin/./ifup -a
echo ""

echo "AVAHI" 
/usr/sbin/./avahi-daemon -s &
echo ""

echo "DHCP" 
/usr/lib/dhcpcd5/./dhcpcd -q -b
echo ""

echo "LIST NET"
ls /sys/class/net
echo ""

echo "IFCONFIG" 
/sbin/./ifconfig wlan0 up
echo ""

echo "IFCONFIG" 
/sbin/./ifconfig
echo ""

echo "RF"
/usr/sbin/./rfkill list
echo ""

echo "TEXUGO IS ALIVE?"

sleep 30s
/usr/bin/./wget www.google.com.br -P /texugo/texugo/

while :
do
    echo "IFCONFIG" 
    /sbin/./ifconfig
    echo ""
    
    echo "TEXUGO IS SLEEPING"
    sleep 10m
done