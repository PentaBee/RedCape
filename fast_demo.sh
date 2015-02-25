#!/bin/bash
#This script is a fast demo to see the leds flashing on the RedCape VA2
cd FPGA/Jrunner/
##
chmod +x jrunner
./jrunner redcapea2_demo.cdf
cd ~
echo Flashing LEDs DEMO - Use the PushButtons to control the DEMO
