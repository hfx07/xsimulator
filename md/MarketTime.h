/*
Created on Sep 2018

@author: hufx

Market Time
*/
#ifndef MARKET_TIME_H
#define MARKET_TIME_H

#include "Quotes.h"
#include <ctime>
#include <cstdio>
#include <cstdlib>

inline long parse_date_time(const char* date, const char* time, int ms = 0)
{
    struct tm _tm;
    char buffer[18];
    sprintf(buffer, "%s %s", date, time);
    strptime(buffer, "%Y%m%d %H:%M:%S", &_tm);
    return timelocal(&_tm) * 1000 + ms;
}

inline std::string parse_milliseconds(long milli)
{
    if (milli < 0)
        return std::string("NULL");
    long sec = milli / 1000;
    struct tm * dt;
    char buffer [24];
    dt = localtime(&sec);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", dt);
    char ms[5];
    sprintf(ms, ".%03ld", milli % 1000);
    strcat(buffer, ms);
    return std::string(buffer);
}

inline int get_tick_milliseconds(const std::string& instrument_id)
{
    int tick_time;
    std::string market = get_market(instrument_id);
    if (market.compare(MARKET_CHINA_FUTURE_COMMODITY) == 0 || market.compare(MARKET_CHINA_FUTURE_INDEX) == 0 || market.compare(MARKET_CHINA_FUTURE_TREASURY) == 0)
        tick_time = 500;
    else if (market.compare(MARKET_CHINA_STOCK) == 0)
        tick_time = 3000;
    return tick_time;
}

inline std::string get_night_start_time(const std::string& instrument_id)
{
    std::string night_start_time;
    std::string market = get_market(instrument_id);
    // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1987872/index.html DCE: p,j since 20140704
    // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/2285993/index.html DCE: m,y,a,b,jm,i since 20141226
    // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6156940/index.html DCE: l,v,pp,eg,c,cs since 20190329
    // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6202113/index.html DCE: 21:00:00->22:30:00 on 20191225 only
    // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6204446/index.html DCE: cancel since 20200203
    // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6215428/index.html DCE: restart, pg since 20200506
    if (market.compare(MARKET_CHINA_FUTURE_COMMODITY) == 0)
        night_start_time = "21:00:00";
    else
        night_start_time = "";
    return night_start_time;
}

inline std::string get_night_end_time(const std::string& instrument_id)
{
    std::string night_end_time;
    std::string exchange = get_exchange(instrument_id);
    std::string instrument_id_alp = get_instrument_id_alp(instrument_id);
    if (exchange.compare(EXCHANGE_SHFE) == 0)
    {
        if (instrument_id_alp.compare("au") == 0 || instrument_id_alp.compare("ag") == 0)
            night_end_time = "02:30:00";
        else if (instrument_id_alp.compare("cu") == 0 || instrument_id_alp.compare("al") == 0 || instrument_id_alp.compare("zn") == 0 || instrument_id_alp.compare("pb") == 0 || instrument_id_alp.compare("ni") == 0 || instrument_id_alp.compare("sn") == 0)
            night_end_time = "01:00:00";
        else
            night_end_time = "23:00:00";
    }
    // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/5000381/index.html DCE: 02:30:00->23:30:00 since 20150508
    // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6156940/index.html DCE: 23:30:00->23:00:00 since 20190329
    // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6204446/index.html DCE: cancel since 20200203
    // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6215428/index.html DCE: restart since 20200506
    else if (exchange.compare(EXCHANGE_DCE) == 0 || exchange.compare(EXCHANGE_CZCE) == 0)
        night_end_time = "23:30:00";
    else
        night_end_time = "";
    return night_end_time;
}

inline std::string get_morning_start_time(const std::string& instrument_id)
{
    std::string morning_start_time;
    std::string market = get_market(instrument_id);
    if (market.compare(MARKET_CHINA_FUTURE_COMMODITY) == 0)
        morning_start_time = "09:00:00";
    else if (market.compare(MARKET_CHINA_FUTURE_INDEX) == 0 || market.compare(MARKET_CHINA_STOCK) == 0)
        morning_start_time = "09:30:00";
    else if (market.compare(MARKET_CHINA_FUTURE_TREASURY) == 0)
        // morning_start_time = "09:15:00";
        // http://www.cffex.com.cn/jystz/20200612/24518.html
        morning_start_time = "09:30:00"; // since 20200720
    else
        morning_start_time = "";
    return morning_start_time;
}

inline std::string get_break_start_time(const std::string& instrument_id)
{
    std::string break_start_time;
    std::string market = get_market(instrument_id);
    if (market.compare(MARKET_CHINA_FUTURE_COMMODITY) == 0)
        break_start_time = "10:15:00";
    else
        break_start_time = "";
    return break_start_time;
}

inline std::string get_break_end_time(const std::string& instrument_id)
{
    std::string break_end_time;
    std::string market = get_market(instrument_id);
    if (market.compare(MARKET_CHINA_FUTURE_COMMODITY) == 0)
        break_end_time = "10:30:00";
    else
        break_end_time = "";
    return break_end_time;
}

inline std::string get_morning_end_time(const std::string& instrument_id)
{
    std::string morning_end_time;
    std::string market = get_market(instrument_id);
    if (market.compare(MARKET_CHINA_FUTURE_COMMODITY) == 0 || market.compare(MARKET_CHINA_FUTURE_INDEX) == 0 || market.compare(MARKET_CHINA_FUTURE_TREASURY) == 0 || market.compare(MARKET_CHINA_STOCK) == 0)
        morning_end_time = "11:30:00";
    else
        morning_end_time = "";
    return morning_end_time;
}

// since 20100628; https://www.shfe.com.cn/news/notice/5227967.html

inline std::string get_noon_start_time(const std::string& instrument_id)
{
    std::string noon_start_time;
    std::string market = get_market(instrument_id);
    if (market.compare(MARKET_CHINA_FUTURE_COMMODITY) == 0)
        noon_start_time = "13:30:00";
    else if (market.compare(MARKET_CHINA_FUTURE_INDEX) == 0 || market.compare(MARKET_CHINA_FUTURE_TREASURY) == 0 || market.compare(MARKET_CHINA_STOCK) == 0)
        noon_start_time = "13:00:00";
    else
        noon_start_time = "";
    return noon_start_time;
}

inline std::string get_noon_end_time(const std::string& instrument_id)
{
    std::string noon_end_time;
    std::string market = get_market(instrument_id);
    if (market.compare(MARKET_CHINA_FUTURE_COMMODITY) == 0 || market.compare(MARKET_CHINA_FUTURE_INDEX) == 0 || market.compare(MARKET_CHINA_STOCK) == 0)
        noon_end_time = "15:00:00";
    else if (market.compare(MARKET_CHINA_FUTURE_TREASURY) == 0)
        noon_end_time = "15:15:00";
    else
        noon_end_time = "";
    return noon_end_time;
}

#endif
