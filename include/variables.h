#ifndef ARDUINO_CLOCK_VARIABLES_H
#define ARDUINO_CLOCK_VARIABLES_H

#include "../.pio/libdeps/uno/LiquidCrystal/src/LiquidCrystal.h"
#include "../.pio/libdeps/uno/DHT sensor library/DHT.h"
#include "enums.h"

extern Button buttonValue;

extern LiquidCrystal lcd;
extern DHT dht;

extern volatile int second;
extern volatile int minute;
extern volatile int hour;
extern volatile int day;
extern volatile int month;
extern volatile int year;
extern volatile int monthDays[];
extern bool hourFormat24;
extern bool dayTime;
extern const char *weekDays[];

extern EditMode editMode;
extern ViewMode viewMode;
extern AlarmEditMode alarmEditMode;

extern float humidity;
extern float temperature;

extern int alarmHour;
extern int alarmMinute;
extern bool alarmEnabled;
extern bool alarmTriggered;


#endif //ARDUINO_CLOCK_VARIABLES_H
