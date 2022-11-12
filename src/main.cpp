#include <util/delay.h>
#include <Arduino.h>
#include "variables.h"
#include "clock/clock.h"
#include "screen/screen.h"
#include "macros.h"

void setup()
{
	TIMSK1 = (1 << TOIE1); // activare timer overflow
	TCNT1 = 0x0BDC;
	TCCR1A = 0;
	TCCR1B = (1 << CS12); // timer start



	lcd.begin(16, 2);
	lcd.clear();

	dht.begin();

	pinMode(BUTTON_PIN, INPUT);
	pinMode(BUZZER_PIN, OUTPUT);
}

void loop()
{
	buttonValue = (Button) analogRead(BUTTON_PIN);

	switch (buttonValue)
	{
		case top:
			if (viewMode == ClockView && editMode != Normal)
			{
				modifyDate(BACK);
			}

			if (viewMode == AlarmView && alarmEditMode != AlarmNormal)
			{
				modifyAlarm(BACK);
			}

			if (viewMode == AlarmView && alarmEditMode == AlarmNormal)
			{
				alarmEnabled = !alarmEnabled;
				_delay_ms(100);
			}

			if (viewMode == ClockView && alarmTriggered)
			{
				alarmTriggered = false;
			}
			break;
		case bottom:
			if (viewMode == ClockView && editMode != Normal)
			{
				modifyDate(NEXT);
			}

			if (viewMode == AlarmView && alarmEditMode != AlarmNormal)
			{
				modifyAlarm(NEXT);
			}

			if (viewMode == AlarmView && alarmEditMode == AlarmNormal)
			{
				alarmEnabled = !alarmEnabled;
				_delay_ms(100);
			}

			if (viewMode == ClockView && alarmTriggered)
			{
				alarmTriggered = false;
			}
			break;
		case left:
			if (editMode == Normal && alarmEditMode == AlarmNormal)
			{
				changeViewMode(BACK);
			}
			break;
		case right:
			if (editMode == Normal && alarmEditMode == AlarmNormal)
			{
				changeViewMode(NEXT);
			}
			break;
		case select:
			if (viewMode == ClockView)
			{
				changeEditMode();
			}

			if (viewMode == AlarmView)
			{
				changeAlarmMode();
			}
			break;
		case notPressed:
			break;
	}

	switch (viewMode)
	{
		case ClockView:
			clockScreen();
			break;
		case SensorView:
			sensorScreen();
			break;
		case AlarmView:
			alarmScreen();
			break;
	}

	if (alarmTriggered)
	{
		alarmRing();
	}

	_delay_ms(100);
	lcd.clear();
}

ISR(TIMER1_OVF_vect)
{
	if (editMode != 0)
	{
		return;
	}

	if (alarmHour == hour && alarmMinute == minute && second == 0 && alarmEnabled)
	{
		alarmTriggered = true;
	}

	TCNT1 = 0x0BDC;

	second++;
	if (second != 60)
	{
		return;
	}
	second = 0;

	minute++;
	if (minute < 60)
	{
		return;
	}

	minute = 0;
	hour++;
	if (hour < 24)
	{
		return;
	}
	hour = 0;
	day++;
	if (day <= monthDays[month - 1])
	{
		return;
	}

	day = 1;
	month++;
	if (month <= 12)
	{
		return;
	}

	month = 1;
	year++;

	if (year % 4 == 0)
	{
		monthDays[1] = 29;
	}
	else
	{
		monthDays[1] = 28;
	}
}

