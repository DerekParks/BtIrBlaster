#!/bin/bash

#http://wiki.pinguino.cc/index.php/Interfacing_with_Bluetooth_JY-MCU
#https://github.com/GuyCarver/MicroPython/blob/master/Lib/JYMCU.py

BT_DEV=/dev/rfcomm0
DEV_ID=00:12:03:09:75:32

if [ "$EUID" -ne 0 ]
	then echo "Please run as root"
	exit
fi

if [ ! -e $BT_DEV ] ; then
	echo $BT_DEV "not found"
	if echo -e "info 00:12:03:09:75:32\nquit\n" | bluetoothctl | grep -q "not available"
	then
		echo "Device not paired"
	else
		echo "Device is paried"
	fi
	rfcomm connect $BT_DEV $DEV_ID 1 > 2&>1 /dev/null &
	echo "BT is connected"
fi
