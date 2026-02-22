# RP2040 DC motor speed controller

### Description
RP2040 DC motor speed controller targetting DRV-family motor drivers and supporting pid speed correction with an encoder. I²C can be used to set the desired speed.  

This was just quickly made to allow me to control the RPM of a little N20 metal gear motor with built-in encoder via I²C. It is by no means perfect but it works, see cfg.h for pin allocations and various settings. 

### Working setups
Tested on Waveshare RP2040-zero with DRV8833 and a 1:10 gear ratio N20 metal gear motor. 
