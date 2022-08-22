# STM32 Watch

## Summary

This project is a simplistic STM32L031K6-based hand watch. It uses two HP's HPDL1414 displays to display up to 6 alphanumeric signs (though only capital letters). For timekeeping I decided to go with DS3231MZ+ and the whole thing is programmed in C using STM32CubeIDE.

## Main functions

Apart from keeping the time and date, the watch is capable of displaying the current ambient temperature and pressure, courtesy of Bosch BMP280 (which can be hot-swapped for BME280 for additional humidity data) and battery voltage.

## PCB design

TODO

## Case design

TODO
