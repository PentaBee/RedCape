#!/bin/bash
#This script is for turning ON  RedCapeA1
######## To power down the RedCape A0 trough PowerEnable in Pin P_42
cd /sys/class/gpio/
##
#This is for RedCape VA0
#echo 7 > export
#This is for RedCape VA1
echo 48 > export
###
cd gpio48
echo "out" > direction
echo 1 > value
echo RedCape is ON > /dev/kmsg
echo RedCape is ON
