/*
Created on Sep 2018

@author: hufx

Strategy Engine
*/
#ifndef STRATEGY_ENGINE_H
#define STRATEGY_ENGINE_H

#include "MdEngine.h"
#include "TdEngine.h"
#include <cmath>
#include <iostream>
#include <iomanip>

class StrategyEngine
{
protected:
    const std::string name;
    bool stop;

public:
    virtual void init(const std::string& date) = 0;
    virtual void run(short source);
    virtual void on_market_data(const LFMarketDataField* curr_md, short source, long rcv_time) {};
    virtual void on_rsp_position(const LFRspPositionField* pos, int request_id, short source, long rcv_time);
    virtual void on_rtn_trade(const LFRtnTradeField* rtn_trade, int request_id, short source, long rcv_time) {};
    virtual void on_rtn_order(const LFRtnOrderField* rtn_order, int request_id, short source, long rcv_time) {};
    virtual void on_rsp_order_insert(const LFInputOrderField* order_insert, int request_id, short source, long rcv_time, short errorId=0, const char* errorMsg=nullptr) {};
    virtual void on_rsp_order_action(const LFOrderActionField* order_action, int request_id, short source, long rcv_time, short errorId=0, const char* errorMsg=nullptr) {};

public:
    int req_position(short source);
    int insert_limit_order(short source, std::string instrument_id, std::string exchange_id, double price, int volume, char direction, char offset);
    int cancel_order(short source, int order_id);

public:
    StrategyEngine(const std::string& name);
    ~StrategyEngine();
};

#endif