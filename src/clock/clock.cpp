#include "clock.h"

void changeEditMode()
{
	editMode = (EditMode) ((int) editMode + 1);
	if (hourFormat24 && editMode == DayTime)
	{
		editMode = (EditMode) ((int) editMode + 1);
	}

	if (editMode == NoMode)
	{
		editMode = Normal;
		lcd.noBlink();
		lcd.noCursor();
		lcd.clear();
	}
	_delay_ms(100);
}

void modifyDate(int direction)
{
	switch (editMode)
	{
		case Day:
			day += direction;
			if (day == monthDays[month - 1] + 1)
			{
				day = 1;
			}

			if (day == 0)
			{
				day = monthDays[month - 1];
			}
			break;
		case Month:
			month += direction;
			if (month == 13)
			{
				month = 1;
			}

			if (month == 0)
			{
				month = 12;
			}

			if (day > monthDays[month - 1])
			{
				day = monthDays[month - 1];
			}
			break;
		case Year:
			year += direction;
			if (year == 2100)
			{
				year = 2001;
			}

			if (year == 2000)
			{
				year = 2099;
			}

			if (year % 4 == 0)
			{
				monthDays[1] = 29;
			}
			else
			{
				monthDays[1] = 28;
			}
			if (day > monthDays[month - 1])
			{
				day = monthDays[month - 1];
			}
			break;
		case Hour:
			hour += direction;
			if (hour == 24)
			{
				hour = 0;
			}

			if (hour == -1)
			{
				hour = 23;
			}
			break;
		case Minute:
			minute += direction;
			if (minute > 59)
			{
				minute = 0;
			}

			if (minute < 0)
			{
				minute = 59;
			}
			break;
		case Second:
			second += direction;
			if (second == 60)
			{
				second = 0;
			}

			if (second == -1)
			{
				second = 59;
			}
			break;
		case HourFormat:
			hourFormat24 = !hourFormat24;
//				lcd.clear();
			break;
		case DayTime:
			dayTime = !dayTime;
			break;

	}
	_delay_ms(100);
}

const char *getWeekDay()
{
	int yy = year % 100;
	int yearCode = (yy + yy / 4) % 7;

	const char *monthCodes = "033614625035";
	int monthCode = monthCodes[month - 1] - '0';

	int centuryCode = 6;

	int leapYear = year % 4 == 0;

	if (leapYear && month < 3)
	{
		leapYear = 1;
	}
	else
	{
		leapYear = 0;
	}

	int weekDayCode = yearCode + monthCode + centuryCode + day - leapYear;

	return weekDays[weekDayCode % 7];
}