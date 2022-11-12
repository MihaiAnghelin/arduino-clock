#include "enums.h"
#include "LiquidCrystal.h"
#include "DHT.h"
#include "macros.h"

Button buttonValue = Button::notPressed;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);
DHT dht(DHT_PIN, DHT_TYPE);

EditMode editMode = Normal;
ViewMode viewMode = ClockView;
AlarmEditMode alarmEditMode = AlarmNormal;

volatile int second = 0;
volatile int minute = 0;
volatile int hour = 0;
volatile int day = 9;
volatile int month = 11;
volatile int year = 2022;
volatile int monthDays[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
bool hourFormat24 = true;
bool dayTime = true;
const char *weekDays[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

float humidity = 0;
float temperature = 0;

int alarmHour = 0;
int alarmMinute = 0;
bool alarmEnabled = false;
bool alarmTriggered = false;

