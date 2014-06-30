This folder contains software to program a I2C master in a Raspberry Pi.
It is used to test & validate the Arduino I2C handler software.

i2cTest: Allows to send a list of commands.  Each command has three characters.

*.sh example scripts to perform common action sequences using i2cTest command.

Except:
- startup_mailer.sh: Sends an e-mail indicating current ip address on startup.  Must be called from /etc/rc.local. Password and emails settings are fake.
- safe_shutdown.sh: Sends the status of the raspberry pi to the Arduino when booting or shutting down.  Must be copied to /etc/init.d and configured to be executed on startup and shutdown.  


