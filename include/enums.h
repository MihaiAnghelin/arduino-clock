//
// Created by mihui on 11/10/22.
//

#ifndef ARDUINO_CLOCK_ENUMS_H
#define ARDUINO_CLOCK_ENUMS_H

enum Button
{
	top = 143,
	bottom = 328,
	left = 503,
	right = 0,
	select = 741,
	notPressed = 1023
};

enum EditMode
{
	Normal = 0,
	Day = 1,
	Month = 2,
	Year = 3,
	HourFormat = 4,
	Hour = 5,
	Minute = 6,
	Second = 7,
	DayTime = 8,
	NoMode = 9,
};

enum ViewMode
{
	NoneFirst = 0,
	ClockView = 1,
	SensorView = 2,
	AlarmView = 3,
	NoneLast = 4,
};

enum AlarmEditMode
{
	AlarmNormal = 0,
	AlarmHour = 1,
	AlarmMinute = 2,
	AlarmDayTime = 3,
	AlarmNoMode = 4,
};

#endif //ARDUINO_CLOCK_ENUMS_H
