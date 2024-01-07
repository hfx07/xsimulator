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

static std::map<std::string, std::string> HOLIDAYS_CHINA {\
    {"20150903", "Victory Day of War of Resistance Against Japan"},\
    {"20150904", "Victory Day of War of Resistance Against Japan"},\

    {"20180101", "New Year"},\
    {"20180215", "Chinese New Year Eve"},\
    {"20180216", "Chinese New Year"},\
    {"20180219", "Chinese New Year"},\
    {"20180220", "Chinese New Year"},\
    {"20180221", "Chinese New Year"},\
    {"20180405", "Qingming Festival"},\
    {"20180406", "Qingming Festival"},\
    {"20180430", "Labor Day"},\
    {"20180501", "Labor Day"},\
    {"20180618", "Dragon Boat Festival"},\
    {"20180924", "Mid-Autumn Festival"},\
    {"20181001", "Chinese National Holiday"},\
    {"20181002", "Chinese National Holiday"},\
    {"20181003", "Chinese National Holiday"},\
    {"20181004", "Chinese National Holiday"},\
    {"20181005", "Chinese National Holiday"},\
    {"20181231", "New Year"},\
    
    {"20190101", "New Year"},\
    {"20190204", "Chinese New Year Eve"},\
    {"20190205", "Chinese New Year"},\
    {"20190206", "Chinese New Year"},\
    {"20190207", "Chinese New Year"},\
    {"20190208", "Chinese New Year"},\
    {"20190405", "Qingming Festival"},\
    {"20190501", "Labor Day"},\
    {"20190502", "Labor Day"},\
    {"20190503", "Labor Day"},\
    {"20190607", "Dragon Boat Festival"},\
    {"20190913", "Mid-Autumn Festival"},\
    {"20191001", "Chinese National Holiday"},\
    {"20191002", "Chinese National Holiday"},\
    {"20191003", "Chinese National Holiday"},\
    {"20191004", "Chinese National Holiday"},\
    {"20191007", "Chinese National Holiday"},\

    {"20200101", "New Year"},\
    {"20200124", "Chinese New Year Eve"},\
    {"20200127", "Chinese New Year"},\
    {"20200128", "Chinese New Year"},\
    {"20200129", "Chinese New Year"},\
    {"20200130", "Chinese New Year"},\
    {"20200131", "Chinese New Year"},\
    {"20200406", "Qingming Festival"},\
    {"20200501", "Labor Day"},\
    {"20200504", "Labor Day"},\
    {"20200505", "Labor Day"},\
    {"20200625", "Dragon Boat Festival"},\
    {"20200626", "Dragon Boat Festival"},\
    {"20201001", "Chinese National Holiday & Mid-Autumn Festival"},\
    {"20201002", "Chinese National Holiday"},\
    {"20201005", "Chinese National Holiday"},\
    {"20201006", "Chinese National Holiday"},\
    {"20201007", "Chinese National Holiday"},\
    {"20201008", "Chinese National Holiday"},\

    {"20210101", "New Year"},\
    {"20210211", "Chinese New Year Eve"},\
    {"20210212", "Chinese New Year"},\
    {"20210215", "Chinese New Year"},\
    {"20210216", "Chinese New Year"},\
    {"20210217", "Chinese New Year"},\
    {"20210405", "Qingming Festival"},\
    {"20210503", "Labor Day"},\
    {"20210504", "Labor Day"},\
    {"20210505", "Labor Day"},\
    {"20210614", "Dragon Boat Festival"},\
    {"20210920", "Mid-Autumn Festival"},\
    {"20210921", "Mid-Autumn Festival"},\
    {"20211001", "Chinese National Holiday"},\
    {"20211004", "Chinese National Holiday"},\
    {"20211005", "Chinese National Holiday"},\
    {"20211006", "Chinese National Holiday"},\
    {"20211007", "Chinese National Holiday"},\

    {"20220103", "New Year"},\
    {"20220131", "Chinese New Year Eve"},\
    {"20220201", "Chinese New Year"},\
    {"20220202", "Chinese New Year"},\
    {"20220203", "Chinese New Year"},\
    {"20220204", "Chinese New Year"},\
    {"20220404", "Qingming Festival"},\
    {"20220405", "Qingming Festival"},\
    {"20220502", "Labor Day"},\
    {"20220503", "Labor Day"},\
    {"20220504", "Labor Day"},\
    {"20220603", "Dragon Boat Festival"},\
    {"20220912", "Mid-Autumn Festival"},\
    {"20221003", "Chinese National Holiday"},\
    {"20221004", "Chinese National Holiday"},\
    {"20221005", "Chinese National Holiday"},\
    {"20221006", "Chinese National Holiday"},\
    {"20221007", "Chinese National Holiday"},\
    
    {"20230102", "New Year"},\
    {"20230123", "Chinese New Year"},\
    {"20230124", "Chinese New Year"},\
    {"20230125", "Chinese New Year"},\
    {"20230126", "Chinese New Year"},\
    {"20230127", "Chinese New Year"},\
    {"20230405", "Qingming Festival"},\
    {"20230501", "Labor Day"},\
    {"20230502", "Labor Day"},\
    {"20230503", "Labor Day"},\
    {"20230622", "Dragon Boat Festival"},\
    {"20230623", "Dragon Boat Festival"},\
    {"20230929", "Mid-Autumn Festival"},\
    {"20231002", "Chinese National Holiday"},\
    {"20231003", "Chinese National Holiday"},\
    {"20231004", "Chinese National Holiday"},\
    {"20231005", "Chinese National Holiday"},\
    {"20231006", "Chinese National Holiday"}
};

inline bool is_leap_year(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

inline std::string shift_contract_month_backward(const std::string& contract_month, unsigned int shift, unsigned int day = 1)
{

    struct tm _tm;
    char date[9];
    strptime(contract_month.c_str(), "%y%m", &_tm);
    while shift
    {
        if (_tm.tm_mon == 0)
        {
            _tm.tm_year -= 1;
            _tm.tm_mon = 11;
        }
        else
            _tm.tm_mon -= 1;
        shift--;
    }
    _tm.tm_mday = day;
    strftime(date, sizeof(date), "%Y%m%d", &_tm);
    return std::string(date)
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

inline void get_next_day(struct tm* _tm)
{
    switch (_tm->tm_mon)
    {
        case 0:
        case 2:
        case 4:
        case 6:
        case 7:
        case 9:
            if (_tm->tm_mday < 31)
                _tm->tm_mday += 1;
            else
            {
                _tm->tm_mon += 1;
                _tm->tm_mday = 1;
            }
            break;
        case 11:
            if (_tm->tm_mday < 31)
                _tm->tm_mday += 1;
            else
            {
                _tm->tm_year += 1;
                _tm->tm_mon = 1;
                _tm->tm_mday = 1;
            }
            break;
        case 1:
            if (_tm->tm_mday < 28 || (is_leap_year(_tm->tm_year) && _tm->tm_mday < 29))
                _tm->tm_mday += 1;
            else
            {
                _tm->tm_mon += 1;
                _tm->tm_mday = 1;
            }
            break;
        default:
            if (_tm->tm_mday < 30)
                _tm->tm_mday += 1;
            else
            {
                _tm->tm_mon += 1;
                _tm->tm_mday = 1;
            }
            break;
    }
}

inline void is_trading_day(const std::string& trading_day)
{
    struct tm _tm;
    int year, month, day, week;
    strptime(trading_day.c_str(), "%Y%m%d", &_tm);
    year = _tm.tm_year + 1900;
    month = _tm.tm_mon + 1;
    day = _tm.tm_mday;
    week = (day + 2 * month + 3 * (month + 1) / 5 + year + year / 4 - year / 100 + year / 400) % 7;
    return (week < 5 && HOLIDAYS_CHINA.find(trading_day) == HOLIDAYS_CHINA.end());
}

inline std::string get_previous_trading_day(const std::string& trading_day)
{
    return shift_trading_day_backward(trading_day, 1, false);
}

// Kim Larsson Formula
inline std::string shift_trading_day_backward(const std::string& trading_day, unsigned int shift, bool count_start_day)
{
    struct tm _tm;
    char date[9];
    int year, month, day, week = 7;
    strptime(trading_day.c_str(), "%Y%m%d", &_tm);
    if (count_start_day && is_trading_day(trading_day))
        shift--;
    strftime(date, sizeof(date), "%Y%m%d", &_tm);
    while shift
    {
        while (week > 4 || HOLIDAYS_CHINA.find(date) != HOLIDAYS_CHINA.end())
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
        shift--;
        week = 7;
    }
    return std::string(date);
}

inline std::string get_next_trading_day(const std::string& trading_day)
{
   return shift_trading_day_forward(trading_day, 1, false); 
}

// Kim Larsson Formula
inline std::string shift_trading_day_forward(const std::string& trading_day, unsigned int shift, bool count_start_day)
{
    struct tm _tm;
    char date[9];
    int year, month, day, week = 7;
    strptime(trading_day.c_str(), "%Y%m%d", &_tm);
    if (count_start_day && is_trading_day(trading_day))
        shift--;
    strftime(date, sizeof(date), "%Y%m%d", &_tm);
    while shift
    {
        while (week > 4 || HOLIDAYS_CHINA.find(date) != HOLIDAYS_CHINA.end())
        {
            get_next_day(&_tm);
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
        shift--;
        week = 7;
    }
    return std::string(date);
}

#endif
