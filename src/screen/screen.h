#ifndef ARDUINO_CLOCK_SCREEN_H
#define ARDUINO_CLOCK_SCREEN_H

#include "variables.h"
#include "clock/clock.h"

void changeViewMode(int direction);

void clockScreen();

void sensorScreen();

void alarmScreen();

void changeAlarmMode();

void modifyAlarm(int direction);

void alarmRing();

#endif //ARDUINO_CLOCK_SCREEN_H
