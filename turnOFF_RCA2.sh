#!/bin/bash
#This script is for turning OFF  RedCapeA2, given that is already ON
######## To power down the RedCape A0 trough PowerEnable in Pin P_42
cd /sys/class/gpio/
##
#This is for RedCape VA0
#echo 7 > export
#This is for RedCape VA1 & VA2
#echo 48 > export
###
cd gpio48
#echo "out" > direction
echo 0 > value
echo RedCape is OFF > /dev/kmsg
echo RedCape is OFF
