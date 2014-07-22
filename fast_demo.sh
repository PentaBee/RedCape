#!/bin/bash
#This script is a fast demo to see the leds flashing on the RedCape VA1
cd /DEMO/jrunner/
##
chmod +x jrunner
./jrunner redcape1_test.cdf
cd ~
echo Flashing LEDs DEMO
