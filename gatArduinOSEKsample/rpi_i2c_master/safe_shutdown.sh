#!/bin/bash
# /etc/init.d/safe_shutdown.sh

### BEGIN INIT INFO
# Provides:          safe_shutdown
# Required-Start:    $syslog
# Required-Stop:     $syslog
# Default-Start:     2 3 4 5
# Default-Stop:      0 1 6
# Short-Description: Example initscript
# Description:       This service is used to manage a safe shutdown of the RPi
### END INIT INFO


case "$1" in 
    start)
	echo $"@@@@@@@@ Informing Arduino RPi is alive  @@@@@@@@@"
	sh /home/pi/sketchbook/gatArduinOSEKsample/rpi_i2c_master/turnonrpi.sh &
        ;;
    stop)
        echo $"@@@@@@@@ Informing Arduino RPi is going to shutdown @@@@@@@@@"
	sh /home/pi/sketchbook/gatArduinOSEKsample/rpi_i2c_master/turnoffrpi.sh
        ;;
    *)
        echo "Usage: /etc/init.d/safe_shutdown start|stop"
        exit 1
        ;;
esac

exit 0
