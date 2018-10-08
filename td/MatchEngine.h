/*
Created on Sep 2018

@author: hufx

Match Engine
*/
#ifndef MATCH_ENGINE_H
#define MATCH_ENGINE_H

#include "DataStructs.h"
#include <map>
#include <utility>

class MatchEngine
{
protected:
    LFMarketDataField last_md, curr_md;
    FillField fill;
    std::map<double, int> trade_map;
    std::map<double, int> ask_quote;
    std::map<double, int> bid_quote;

public:
    int contract_size;
    double tick_size;

    int latency;
    int milliseconds_per_tick;

    int hidden_queue_init_vol;
    double hidden_queue_add_rate;
    double hidden_queue_cxl_rate;

    std::map<double, std::pair<int, int>> volume_map;

    bool has_buy_order_traded, has_sell_order_traded;
    
    void match_market_data(LFMarketDataField* data, int tick_id, int last_tick_id);
    void execute_order(std::pair<int, double>& result, OrderField* order);
};

#endif