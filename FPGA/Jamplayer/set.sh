#!/bin/bash
# Startup Script
#The script is used with cron, so save de script and makeit executable
#for adding to cron $ env EDITOR=nano crontab -e 
#in the opened file add_the_next_at_end_of_file:  @reboot /bin/bash /home/root/startup.sh


######## To power up the RedCape A0 trough PowerEnable in Pin P_42
#echo Starting PowerEnable V-A1 signal > /dev/kmsg
cd /sys/class/gpio/
##
#This is for RedCape VA0
#echo 7 > export
#This is for RedCape VA1
echo 115 > export
###
cd gpio115
echo "out" > direction
#echo 1 > value
#echo PowerEnable is up > /dev/kmsg

