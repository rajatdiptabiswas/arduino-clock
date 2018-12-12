#include <Time.h>
#include <TimeLib.h>

#define DISPLAY_BRIGHTNESS   500

#define DIGIT_ON  HIGH
#define DIGIT_OFF LOW

#define SEGMENT_ON  LOW
#define SEGMENT_OFF HIGH

/*
 * display_1 = hour 10s place
 * display_2 = hour 1s place
 * display_3 = minute 10s place
 * display_4 = minute 1s place
 * 
 * switch_1 = push button for hour up
 * switch_2 = push button for hour down
 * switch_3 = push button for minute up
 * switch_4 = push button for minute down
 */

// Power for the displays
int display_1 = 10;
int display_2 = 11;
int display_3 = 12;
int display_4 = 13;

// Defining pins for the segments
int segment_a = 2;
int segment_b = 3;
int segment_c = 4;
int segment_d = 5;
int segment_e = 6;
int segment_f = 7;
int segment_g = 8;
int segment_dot = 9;

// Input pins for the push buttons
byte switch_1 = A0;
byte switch_2 = A1;
byte switch_3 = A2;
byte switch_4 = A3;

void setup()
{
  pinMode(segment_a, OUTPUT);
  pinMode(segment_b, OUTPUT);
  pinMode(segment_c, OUTPUT);
  pinMode(segment_d, OUTPUT);
  pinMode(segment_e, OUTPUT);
  pinMode(segment_f, OUTPUT);
  pinMode(segment_g, OUTPUT);
  pinMode(segment_dot, OUTPUT);

  pinMode(display_1, OUTPUT);
  pinMode(display_2, OUTPUT);
  pinMode(display_3, OUTPUT);
  pinMode(display_4, OUTPUT);

  Serial.begin(9600);

  pinMode(switch_1, INPUT);
  pinMode(switch_2, INPUT);
  pinMode(switch_3, INPUT);
  pinMode(switch_4, INPUT);

  digitalWrite(switch_1, LOW);
  digitalWrite(switch_2, LOW);
  digitalWrite(switch_3, LOW);
  digitalWrite(switch_4, LOW);
}

void loop()
{
  digitalWrite(segment_dot, HIGH);

  int hr = hour();
    int mn = minute();

    if (hr > 12)
      hr %= 12;

    if (mn > 60)
      mn %= 60;

  int time = hr*100 + mn;

  Serial.println(time);

  for (int i = 250; i > 0; i--)
  {
    if (time >= 1000)
    {
      displayNumber1(time);
    }
    else
    {
      displayNumber2(time);
    }
  }

  for (int i = 250; i > 0; i--)
  {
    if (time >= 1000)
    {
      displayNumber3(time);
    }
    else
    {
      displayNumber4(time);
    }
  }

  if (digitalRead(switch_1) == HIGH || digitalRead(switch_2) == HIGH)
    set_time_hour();

  if (digitalRead(switch_3) == HIGH || digitalRead(switch_4) == HIGH)
    set_time_minute();
}

void set_time_hour()
{
    int hours = hour();
    int minutes = minute();

    while (digitalRead(switch_1) == HIGH)
    {
      hours--;

      if (hours < 1)
      {
        hours = 12;
      }

      for (int i = 20; i > 0; i--)
      {
        int time = hours*100 + minutes;

        if (time >= 1000)
          displayNumber1(time);
        else
          displayNumber2(time);
      }

      delay(200);
    }

    while (digitalRead(switch_2))
    {
      hours++;

      if (hours > 12)
      {
        hours = 1;
      }

      for (int i = 20; i > 0; i--)
      {
        int time = hours*100 + minutes;

        if (time >= 1000)
          displayNumber1(time);
        else
          displayNumber2(time);
      }

      delay(200);
    }

    setTime(hours,minutes,0,0,0,0);
}

void set_time_minute()
{
  int hours = hour();
    int minutes = minute();

    while (digitalRead(switch_3))
    {
      minutes--;

      if (minutes < 0)
      {
        minutes = 59;
      }

      for (int i = 20; i > 0; i--)
      {
        int time = hours*100 + minutes;

        if (time > 1000)
          displayNumber1(time);
        else
          displayNumber2(time);
      }

      delay(200);
    }

    while (digitalRead(switch_4))
    {
      minutes++;

      if (minutes > 59)
      {
        minutes = 0;
      }

      for (int i = 20; i > 0; i--)
      {
        int time = hours*100 + minutes;

        if (time > 1000)
          displayNumber1(time);
        else
          displayNumber2(time);
      }

      delay(200);
    }

    setTime(hours,minutes,0,0,0,0);
}

void displayNumber1(int number)
{
  // Flash displays for a short amount of time
  for (int digit = 4; digit > 0; digit--)
  {
    switch (digit)
    {
      case 1:
        digitalWrite(display_1, DIGIT_ON);
        digitalWrite(segment_dot, LOW);
        break;

      case 2:
        digitalWrite(display_2, DIGIT_ON);
        digitalWrite(segment_dot, LOW);
        break;

      case 3:
        digitalWrite(display_3, DIGIT_ON);
        digitalWrite(segment_dot, LOW);
        break;

      case 4:
        digitalWrite(display_4, DIGIT_ON);
        digitalWrite(segment_dot, LOW);
        break;

    }

    lightNumber(number % 10);
    number /= 10;
    delayMicroseconds(DISPLAY_BRIGHTNESS);

    // Turn off all segments
    lightNumber(10);

    // Turn of all displays
    digitalWrite(display_1, DIGIT_OFF);
    digitalWrite(display_2, DIGIT_OFF);
    digitalWrite(display_3, DIGIT_OFF);
    digitalWrite(display_4, DIGIT_OFF);
  }
}

void displayNumber2(int number)
{
  // Flash displays for a short amount of time
  for (int digit = 4; digit > 0; digit--)
  {
    switch (digit)
    {
      case 1:
        lightNumber(10);
        digitalWrite(segment_dot, LOW);
        break;

      case 2:
        digitalWrite(display_2, DIGIT_ON);
        digitalWrite(segment_dot, LOW);
        break;

      case 3:
        digitalWrite(display_3, DIGIT_ON);
        digitalWrite(segment_dot, LOW);
        break;

      case 4:
        digitalWrite(display_4, DIGIT_ON);
        digitalWrite(segment_dot, LOW);
        break;

    }

    lightNumber(number % 10);
    number /= 10;
    delayMicroseconds(DISPLAY_BRIGHTNESS);

    // Turn off all segments
    lightNumber(10);

    // Turn of all displays
    digitalWrite(display_1, DIGIT_OFF);
    digitalWrite(display_2, DIGIT_OFF);
    digitalWrite(display_3, DIGIT_OFF);
    digitalWrite(display_4, DIGIT_OFF);
  }
}

void displayNumber3(int number)
{
  // Flash displays for a short amount of time
  for (int digit = 4; digit > 0; digit--)
  {
    switch (digit)
    {
      case 1:
        digitalWrite(display_1, DIGIT_ON);
        digitalWrite(segment_dot, HIGH);
        break;

      case 2:
        digitalWrite(display_2, DIGIT_ON);
        digitalWrite(segment_dot, HIGH);
        break;

      case 3:
        digitalWrite(display_3, DIGIT_ON);
        digitalWrite(segment_dot, HIGH);
        break;

      case 4:
        digitalWrite(display_4, DIGIT_ON);
        digitalWrite(segment_dot, HIGH);
        break;

    }

    lightNumber(number % 10);
    number /= 10;
    delayMicroseconds(DISPLAY_BRIGHTNESS);

    // Turn off all segments
    lightNumber(10);

    // Turn of all displays
    digitalWrite(display_1, DIGIT_OFF);
    digitalWrite(display_2, DIGIT_OFF);
    digitalWrite(display_3, DIGIT_OFF);
    digitalWrite(display_4, DIGIT_OFF);
  }
}

void displayNumber4(int number)
{
  // Flash displays for a short amount of time
  for (int digit = 4; digit > 0; digit--)
  {
    switch (digit)
    {
      case 1:
        lightNumber(10);
        digitalWrite(segment_dot, HIGH);
        break;

      case 2:
        digitalWrite(display_2, DIGIT_ON);
        digitalWrite(segment_dot, HIGH);
        break;

      case 3:
        digitalWrite(display_3, DIGIT_ON);
        digitalWrite(segment_dot, HIGH);
        break;

      case 4:
        digitalWrite(display_4, DIGIT_ON);
        digitalWrite(segment_dot, HIGH);
        break;

    }

    lightNumber(number % 10);
    number /= 10;
    delayMicroseconds(DISPLAY_BRIGHTNESS);

    // Turn off all segments
    lightNumber(10);

    // Turn of all displays
    digitalWrite(display_1, DIGIT_OFF);
    digitalWrite(display_2, DIGIT_OFF);
    digitalWrite(display_3, DIGIT_OFF);
    digitalWrite(display_4, DIGIT_OFF);
  }
}

void lightNumber(int number)
{
  switch (number)
  {
    case 0:
        digitalWrite(segment_a, SEGMENT_ON);
        digitalWrite(segment_b, SEGMENT_ON);
        digitalWrite(segment_c, SEGMENT_ON);
        digitalWrite(segment_d, SEGMENT_ON);
        digitalWrite(segment_e, SEGMENT_ON);
        digitalWrite(segment_f, SEGMENT_ON);
        digitalWrite(segment_g, SEGMENT_OFF);
        break;

      case 1:
        digitalWrite(segment_a, SEGMENT_OFF);
        digitalWrite(segment_b, SEGMENT_ON);
        digitalWrite(segment_c, SEGMENT_ON);
        digitalWrite(segment_d, SEGMENT_OFF);
        digitalWrite(segment_e, SEGMENT_OFF);
        digitalWrite(segment_f, SEGMENT_OFF);
        digitalWrite(segment_g, SEGMENT_OFF);
        break;

      case 2:
        digitalWrite(segment_a, SEGMENT_ON);
        digitalWrite(segment_b, SEGMENT_ON);
        digitalWrite(segment_c, SEGMENT_OFF);
        digitalWrite(segment_d, SEGMENT_ON);
        digitalWrite(segment_e, SEGMENT_ON);
        digitalWrite(segment_f, SEGMENT_OFF);
        digitalWrite(segment_g, SEGMENT_ON);
        break;

      case 3:
        digitalWrite(segment_a, SEGMENT_ON);
        digitalWrite(segment_b, SEGMENT_ON);
        digitalWrite(segment_c, SEGMENT_ON);
        digitalWrite(segment_d, SEGMENT_ON);
        digitalWrite(segment_e, SEGMENT_OFF);
        digitalWrite(segment_f, SEGMENT_OFF);
        digitalWrite(segment_g, SEGMENT_ON);
        break;

      case 4:
        digitalWrite(segment_a, SEGMENT_OFF);
        digitalWrite(segment_b, SEGMENT_ON);
        digitalWrite(segment_c, SEGMENT_ON);
        digitalWrite(segment_d, SEGMENT_OFF);
        digitalWrite(segment_e, SEGMENT_OFF);
        digitalWrite(segment_f, SEGMENT_ON);
        digitalWrite(segment_g, SEGMENT_ON);
        break;

      case 5:
        digitalWrite(segment_a, SEGMENT_ON);
        digitalWrite(segment_b, SEGMENT_OFF);
        digitalWrite(segment_c, SEGMENT_ON);
        digitalWrite(segment_d, SEGMENT_ON);
        digitalWrite(segment_e, SEGMENT_OFF);
        digitalWrite(segment_f, SEGMENT_ON);
        digitalWrite(segment_g, SEGMENT_ON);
        break;

      case 6:
        digitalWrite(segment_a, SEGMENT_ON);
        digitalWrite(segment_b, SEGMENT_OFF);
        digitalWrite(segment_c, SEGMENT_ON);
        digitalWrite(segment_d, SEGMENT_ON);
        digitalWrite(segment_e, SEGMENT_ON);
        digitalWrite(segment_f, SEGMENT_ON);
        digitalWrite(segment_g, SEGMENT_ON);
        break;

      case 7:
        digitalWrite(segment_a, SEGMENT_ON);
        digitalWrite(segment_b, SEGMENT_ON);
        digitalWrite(segment_c, SEGMENT_ON);
        digitalWrite(segment_d, SEGMENT_OFF);
        digitalWrite(segment_e, SEGMENT_OFF);
        digitalWrite(segment_f, SEGMENT_OFF);
        digitalWrite(segment_g, SEGMENT_OFF);
        break;

      case 8:
        digitalWrite(segment_a, SEGMENT_ON);
        digitalWrite(segment_b, SEGMENT_ON);
        digitalWrite(segment_c, SEGMENT_ON);
        digitalWrite(segment_d, SEGMENT_ON);
        digitalWrite(segment_e, SEGMENT_ON);
        digitalWrite(segment_f, SEGMENT_ON);
        digitalWrite(segment_g, SEGMENT_ON);
        break;

      case 9:
        digitalWrite(segment_a, SEGMENT_ON);
        digitalWrite(segment_b, SEGMENT_ON);
        digitalWrite(segment_c, SEGMENT_ON);
        digitalWrite(segment_d, SEGMENT_ON);
        digitalWrite(segment_e, SEGMENT_OFF);
        digitalWrite(segment_f, SEGMENT_ON);
        digitalWrite(segment_g, SEGMENT_ON);
        break;

      // all segment are ON
      case 10:
        digitalWrite(segment_a, SEGMENT_OFF);
        digitalWrite(segment_b, SEGMENT_OFF);
        digitalWrite(segment_c, SEGMENT_OFF);
        digitalWrite(segment_d, SEGMENT_OFF);
        digitalWrite(segment_e, SEGMENT_OFF);
        digitalWrite(segment_f, SEGMENT_OFF);
        digitalWrite(segment_g, SEGMENT_OFF);
        break;
  }
}