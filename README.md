# STM32 Watch

## Summary

This project is a simplistic STM32L031K6-based hand watch. It uses two HP's HPDL1414 displays to display up to 6 alphanumeric signs (though only capital letters). For timekeeping I decided to go with DS3231MZ+ and the whole thing is programmed in C using STM32CubeIDE.

## Main functions

New, HCMS-2904 version:

Apart from keeping the time and date, the watch is capable of adjusting its brightness automatically and displaying battery voltage. It uses USB type C for convenient charging (not compatible with chargers that require device ID to be sent) and includes a LED to indicate charging status.

Old, HPDL-1414 version:
Apart from keeping the time and date, the watch is capable of displaying the current ambient temperature and pressure, courtesy of Bosch BMP280 (which can be hot-swapped for BME280 for additional humidity data) and battery voltage. The watch is also equipped with two user-programmable LEDs - green and red by default, one charging indicator LED - yellow and a vibration motor (also fully programmable). It uses USB type C for convenient charging, though it is not compatible with some of the USB-C chargers (those that require device ID to be sent).


## PCB design

The design is currently WIP as the first prototype using HPDL-1414 was produced and verified. The new design will include HCMS-2904 as a replacement and will drop some features and gain some new ones, streamlining the design.

## Case design

There is a simple WIP case design for the HPDL-1414 version, more will come once the new HCMS-2904 pcb is finished.
