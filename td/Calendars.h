/*
Created on Sep 2018

@author: hufx

Calendars
*/
#ifndef CALENDARS_H
#define CALENDARS_H

#include <map>
#include <string>
#include <cstdlib>

static std::map<std::string, std::string> HOLIDAYS {\
    {"20180924", "Mid-autumn Festival"},\
    {"20181001", "Chinese National Holiday"},\
    {"20181002", "Chinese National Holiday"},\
    {"20181003", "Chinese National Holiday"},\
    {"20181004", "Chinese National Holiday"},\
    {"20181005", "Chinese National Holiday"}
};

inline bool is_leap_year(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

inline void get_previous_day(struct tm* _tm)
{
    if (_tm->tm_mday == 1)
    {
        if (_tm->tm_mon == 0)
        {
            _tm->tm_year -= 1;
            _tm->tm_mon = 11;
            _tm->tm_mday = 31;
        }
        else
        {
            _tm->tm_mon -= 1;
            switch (_tm->tm_mon)
            {
                case 0:
                case 2:
                case 4:
                case 6:
                case 7:
                case 9:
                case 11:
                    _tm->tm_mday = 31;
                    break;
                case 1:
                    if (is_leap_year(_tm->tm_year))
                        _tm->tm_mday = 29;
                    else
                        _tm->tm_mday = 28;
                    break;
                default:
                    _tm->tm_mday = 30;
                    break;
            }
        }
    }
    else
        _tm->tm_mday -= 1;
}

// Kim Larsson Formula
inline std::string get_previous_trading_day(const std::string& trading_day)
{
    struct tm _tm;
    char date[9];
    int year, month, day, week = 7;
    strptime(trading_day.c_str(), "%Y%m%d", &_tm);
    while (week > 4 || HOLIDAYS.find(date) != HOLIDAYS.end())
    {
        get_previous_day(&_tm);
        strftime(date, sizeof(date), "%Y%m%d", &_tm);
        year = _tm.tm_year + 1900;
        month = _tm.tm_mon + 1;
        day = _tm.tm_mday;
        if (month == 1 || month == 2)
        {
            month += 12;
            --year;
        }
        week = (day + 2 * month + 3 * (month + 1) / 5 + year + year / 4 - year / 100 + year / 400) % 7;
    }
    return std::string(date);
}

#endif