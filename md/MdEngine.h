/*
Created on Sep 2018

@author: hufx

Md Engine
*/
#ifndef MD_ENGINE_H
#define MD_ENGINE_H

#include "DataStructs.h"
#include <vector>
#include <string>

class MdEngine
{
public:
    std::vector<LFMarketDataField*> md_tick;
    LFMarketDataField* tick_record;
    long tick_time, tick_time_prev;
    std::string instrument_id;

protected:
    std::string line;
    std::vector<LFMarketDataField*>::iterator it_tick;

public:
    MdEngine();
    ~MdEngine();
    void init(const std::string& date, const std::string& period, const std::string& ticker, const std::string& source);
    bool send_market_data();
};

extern MdEngine md;

#endif