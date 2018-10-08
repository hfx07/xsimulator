/*
Created on Sep 2018

@author: hufx

Td Engine
*/
#ifndef TD_ENGINE_H
#define TD_ENGINE_H

#include "DataStructs.h"
#include "MatchEngine.h"
#include <string>

class TdEngine
{
public:
    int rid;
    
    int contract_size;
    double tick_size;

    int tick_id, latency;
    std::string tick_str, tick_period;

    long night_start_time, night_end_time, morning_start_time, break_start_time, break_end_time, morning_end_time, noon_start_time, noon_end_time;
    
    LFRspPositionField pos;
    LFRtnOrderField rtn_order;
    LFOrderActionField order_action;
    LFInputOrderField order_insert;
    std::map<int, OrderField*> order_opened, order_closed;
    std::map<int, LFRtnTradeField*> order_traded;

protected:
    int last_tick_id;
    MatchEngine mt;
    std::pair<int, double> fill;

public:
    TdEngine();
    ~TdEngine();
    void init(const std::string& date, const std::string& period, const std::string& ticker, int latency_in_milliseconds, int hidden_queue_init_vol, double hidden_queue_add_rate, double hidden_queue_cxl_rate);
    void receive_market_data(LFMarketDataField* data, long tick_time, long tick_time_prev);
};

extern TdEngine td;

#endif