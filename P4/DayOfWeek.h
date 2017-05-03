#ifndef DAYOFWEEK_H
#define DAYOFWEEK_H

class DayOfWeek
{
    char monthName[10];
    int month;
    int day;
    int year;
    char dayName[10];
public:
    void read(int month1, int day1, int year1);
    void print() const;
}; //DayOfWeek

#endif