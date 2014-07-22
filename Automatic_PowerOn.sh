#!/bin/bash
#This script is for Automaticly turning ON  RedCapeA1 and loading Device Tree
#Adding Init to Cron
(crontab -l 2>/dev/null; echo "@reboot /bin/bash /home/root/InitRCA1.sh") | crontab -
##Compiling the device tree overlay object
cd /home/root/DeviceTree
dtc -O dtb -o BB-RedCape-00A0.dtbo -b 0 -@ BB-RedCape-00A0.dts
#Move the object to where it will be looked for 
mv BB-RedCape-00A0.dtbo /lib/firmware/


echo Added Automatic Init at startup to crontab
