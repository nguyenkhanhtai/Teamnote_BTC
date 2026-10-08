#include <bits/stdc++.h>
  // Use: int weekday = day_of_week(2026,10,8);

// Valid Gregorian date, year >= 1. Returns Sunday=0, ..., Saturday=6.
int day_of_week(int year, int month, int day) {
    if (month < 3) { month += 12; --year; }
    int y = year % 100, century = year / 100;
    int h = (day + 13 * (month + 1) / 5 + y + y / 4 +
             century / 4 + 5 * century) % 7;
    return (h + 6) % 7;
}
