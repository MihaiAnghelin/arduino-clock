#include "screen.h"
#include "macros.h"
#include "avdweb_VirtualDelay.h"
#include "variables.h"

void changeViewMode(int direction)
{
	viewMode = (ViewMode) ((int) viewMode + direction);
	if (viewMode == NoneFirst)
	{
		viewMode = AlarmView;
	}
	else if (viewMode == NoneLast)
	{
		viewMode = ClockView;
	}
	_delay_ms(100);
}

void clockScreen()
{
	lcd.setCursor(0, 0);
	if (day < 10)
	{
		lcd.print("0");
	}
	lcd.print(day);

	lcd.setCursor(2, 0);
	lcd.print("/");
	if (month < 10)
	{
		lcd.print("0");
	}
	lcd.print(month);

	lcd.setCursor(5, 0);
	lcd.print("/");
	lcd.print(year);

	if (editMode == Normal)
	{
		lcd.print(" ");
		lcd.print(getWeekDay());
	}

	lcd.setCursor(0, 1);
	int hourToPrint = hour;
	if (!hourFormat24)
	{
		hourToPrint %= 12;
		if (hourToPrint == 0)
		{
			hourToPrint = 12;
		}
	}

	if (hourToPrint < 10)
	{
		lcd.print("0");
	}

	lcd.print(hourToPrint);

//	lcd.print(hourFormat24 ? hour : (hour % 12));

	lcd.setCursor(2, 1);
	lcd.print(":");
	if (minute < 10)
	{
		lcd.print("0");
	}
	lcd.print(minute);

	lcd.setCursor(5, 1);
	lcd.print(":");
	if (second < 10)
	{
		lcd.print("0");
	}
	lcd.print(second);

	if (!hourFormat24)
	{
		lcd.print(dayTime ? "AM" : "PM");
	}

	if (editMode != Normal)
	{
		lcd.setCursor(11, 0);
		lcd.print("HF");
		lcd.print(hourFormat24 ? "24" : "12");

		lcd.setCursor(11, 1);
		lcd.print("SET ");
		switch (editMode)
		{
			case Day:
				lcd.print("D");
				lcd.setCursor(1, 0);
				break;
			case Month:
				lcd.print("M");
				lcd.setCursor(4, 0);
				break;
			case Year:
				lcd.print("Y");
				lcd.setCursor(9, 0);
				break;
			case HourFormat:
				lcd.print("F");
				lcd.setCursor(13, 0);
				break;
			case Hour:
				lcd.print("h");
				lcd.setCursor(1, 1);
				break;
			case Minute:
				lcd.print("m");
				lcd.setCursor(4, 1);
				break;
			case Second:
				lcd.print("s");
				lcd.setCursor(7, 1);
				break;
			case DayTime:
				lcd.print("F");
				lcd.setCursor(9, 1);
				break;
		}

		lcd.cursor();
	}
}

void sensorScreen()
{
	static VirtualDelay alarmDelay;
	alarmDelay.start(2000);

	if (alarmDelay.elapsed())
	{
		humidity = dht.readHumidity();
		temperature = dht.readTemperature();
	}

	if (isnan(humidity))
	{
		lcd.clear();
		lcd.setCursor(0, 0);
		lcd.print("Failed Humidity!");
	}

	if (isnan(temperature))
	{
		lcd.clear();
		lcd.setCursor(0, 1);
		lcd.print("Failed Temp!");
	}

	if (isnan(humidity) || isnan(temperature))
	{
		return;
	}

	lcd.setCursor(0, 0);
	lcd.print("Humidity: ");
	lcd.print(humidity);

	lcd.setCursor(0, 1);
	lcd.print("Temp: ");
	lcd.print(temperature);
	lcd.print((char) 223);
	lcd.print("C");
}

void alarmScreen()
{
	lcd.setCursor(0, 0);
	lcd.print("Alarm: ");
	lcd.print(alarmEnabled ? "ON" : "OFF");

	lcd.setCursor(0, 1);
	int hourToPrint = alarmHour;
	if (!hourFormat24)
	{
		hourToPrint %= 12;
		if (hourToPrint == 0)
		{
			hourToPrint = 12;
		}
	}

	if (hourToPrint < 10)
	{
		lcd.print("0");
	}

	lcd.print(hourToPrint);

	lcd.print(":");
	if (alarmMinute < 10)
	{
		lcd.print("0");
	}
	lcd.print(alarmMinute);

	if (!hourFormat24)
	{
		lcd.print(dayTime ? "AM" : "PM");
	}

	if (alarmEditMode != AlarmNormal)
	{
		lcd.setCursor(11, 1);
		lcd.print("SET ");
		switch (alarmEditMode)
		{
			case AlarmHour:
				lcd.print("h");
				lcd.setCursor(1, 1);
				break;
			case AlarmMinute:
				lcd.print("m");
				lcd.setCursor(4, 1);
				break;
			case AlarmDayTime:
				lcd.print("F");
				lcd.setCursor(5, 1);
				break;
		}

		lcd.cursor();
	}
}

void alarmRing()
{
	static VirtualDelay alarmDelay;

	alarmDelay.start(1000);

	if (alarmDelay.elapsed())
	{
		noTone(BUZZER_PIN);
	}
	else
	{
		tone(BUZZER_PIN, 1000, 1000);
	}
}

void changeAlarmMode()
{
	alarmEditMode = (AlarmEditMode) (alarmEditMode + 1);
	if (alarmEditMode == AlarmNoMode)
	{
		alarmEditMode = AlarmNormal;
		lcd.noBlink();
		lcd.noCursor();
	}

	if (alarmEditMode == AlarmDayTime && hourFormat24)
	{
		alarmEditMode = AlarmNormal;
		lcd.noBlink();
		lcd.noCursor();
	}

	_delay_ms(100);
}

void modifyAlarm(int direction)
{
	switch (alarmEditMode)
	{
		case AlarmHour:
			alarmHour += direction;
			if (alarmHour < 0)
			{
				alarmHour = 23;
			}
			else if (alarmHour > 23)
			{
				alarmHour = 0;
			}
			break;
		case AlarmMinute:
			alarmMinute += direction;
			if (alarmMinute < 0)
			{
				alarmMinute = 59;
			}
			else if (alarmMinute > 59)
			{
				alarmMinute = 0;
			}
			break;
		case AlarmDayTime:
			dayTime = !dayTime;
			break;
		default:
			break;
	}

//	_delay_ms(100);
}