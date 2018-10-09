/*
Created on Sep 2018

@author: hufx

Td Engine
*/
#include "TdEngine.h"
#include "MarketTime.h"
#include "Constants.h"
#include "TransactionCost.h"
#include <iostream>
#include <iomanip>

TdEngine::TdEngine()
{
    tick_id = 0;
    last_tick_id = 0;
    
    order_opened.clear();
    order_closed.clear();
    order_traded.clear();
    
    pos.LongPosition = 0;
    pos.ShortPosition = 0;
    pos.LongBalance = 0.0;
    pos.ShortBalance = 0.0;
    pos.LongPnL = 0.0;
    pos.ShortPnL = 0.0;
    pos.Cost = 0.0;

    print_order = false;
}

TdEngine::~TdEngine()
{
    for (auto& order: order_opened)
        delete order.second;
    if (print_order)
        std::cout << "               StartTime" << "    StartFlag" << "    OrderType" << "    OrderId" << "    OrderPrc" << "    OrderVol" << "    AheadVol" << "    FillPrc" << "    FillVol" << "    OrderDur" << "    FillDur" << "    TxnCost" << "          PnL" << "    CloseOut" << "    EndFlag" << "                   EndTime" << std::endl;
    for (auto& order: order_closed)
    {
        if (print_order)
            std::cout << std::setw(24) << order.second->StartTime << std::setw(13) << order.second->StartFlag << std::setw(13) << order.second->OrderType << std::setw(11) << order.second->OrderId << std::setw(12) << order.second->OrderPrc << std::setw(12) << order.second->OrderVol << std::setw(12) << order.second->AheadVol << std::setw(11) << order.second->FillPrc << std::setw(11) << order.second->FillVol << std::setw(12) << order.second->OrderDur << std::setw(11) << order.second->FillDur << std::setw(11) << order.second->TxnCost << std::setw(13) << order.second->PnL << std::setw(12) << order.second->CloseOut << std::setw(11) << order.second->EndFlag << std::setw(26) << order.second->EndTime << std::endl;
        delete order.second;
    }
}

TdEngine td;

void TdEngine::init(const std::string& date, const std::string& period, const std::string& ticker, int latency_in_milliseconds, int hidden_queue_init_vol, double hidden_queue_add_rate, double hidden_queue_cxl_rate)
{
    rid = 8000000;
    
    std::string str;
    str = get_night_start_time(ticker);
    if (str.length() > 0)
        night_start_time = parse_date_time(date.c_str(), str.c_str());
    else
        night_start_time = 0;
    str = get_night_end_time(ticker);
    if (str.length() > 0)
    {
        night_end_time = parse_date_time(date.c_str(), str.c_str());
        if (night_end_time < night_start_time)
            night_end_time += 24 * 60 * 60 * 1000;
    }
    else
        night_end_time = 0;
    str = get_morning_start_time(ticker);
    if (str.length() > 0)
        morning_start_time = parse_date_time(date.c_str(), str.c_str());
    else
        morning_start_time = 0;
    str = get_break_start_time(ticker);
    if (str.length() > 0)
        break_start_time = parse_date_time(date.c_str(), str.c_str());
    else
        break_start_time = 0;
    str = get_break_end_time(ticker);
    if (str.length() > 0)
        break_end_time = parse_date_time(date.c_str(), str.c_str());
    else
        break_end_time = 0;
    str = get_morning_end_time(ticker);
    if (str.length() > 0)
        morning_end_time = parse_date_time(date.c_str(), str.c_str());
    else
        morning_end_time = 0;
    str = get_noon_start_time(ticker);
    if (str.length() > 0)
        noon_start_time = parse_date_time(date.c_str(), str.c_str());
    else
        noon_start_time = 0;
    str = get_noon_end_time(ticker);
    if (str.length() > 0)
        noon_end_time = parse_date_time(date.c_str(), str.c_str());
    else
        noon_end_time = 0;

    tick_period = period;

    latency = latency_in_milliseconds;
    tick_size = get_tick_size(ticker, date);
    contract_size = get_contract_size(ticker, date);

    mt.contract_size = contract_size;
    mt.tick_size = tick_size;
    mt.latency = latency_in_milliseconds;
    mt.milliseconds_per_tick = get_tick_milliseconds(ticker);
    mt.hidden_queue_init_vol = hidden_queue_init_vol;
    mt.hidden_queue_add_rate = hidden_queue_add_rate;
    mt.hidden_queue_cxl_rate = hidden_queue_cxl_rate;
    mt.has_buy_order_traded = false;
    mt.has_sell_order_traded = false;
    mt.volume_map.clear();
}

void TdEngine::receive_market_data(LFMarketDataField* data, long tick_time, long tick_time_prev)
{
    // update tick_str
    int action_day = atoi(data->ActionDay);
    char buffer[24];
    sprintf(buffer, "%04d-%02d-%02d %s.%03d", action_day / 10000, action_day % 10000 / 100, action_day % 100, data->UpdateTime, data->UpdateMillisec);
    tick_str = buffer;
    
    // update tick_id
    if (tick_period.compare("night") == 0)
    {
        if (tick_time <= night_start_time)
            tick_id = 0;
        else if (tick_time <= night_end_time)
            tick_id = (tick_time - night_start_time) / mt.milliseconds_per_tick;
        else
            tick_id = (night_end_time - night_start_time) / mt.milliseconds_per_tick;
    }
    else if (tick_period.compare("day") == 0)
    {
        if (tick_time <= morning_start_time)
            tick_id = 0;
        else if (tick_time <= break_start_time)
            tick_id = (tick_time - morning_start_time) / mt.milliseconds_per_tick;
        else if (tick_time <= break_end_time)
            tick_id = (break_start_time - morning_start_time) / mt.milliseconds_per_tick;
        else if (tick_time <= morning_end_time)
            tick_id = (tick_time - break_end_time) / mt.milliseconds_per_tick + (break_start_time - morning_start_time) / mt.milliseconds_per_tick;
        else if (tick_time <= noon_start_time)
            tick_id = (morning_end_time - break_end_time) / mt.milliseconds_per_tick + (break_start_time - morning_start_time) / mt.milliseconds_per_tick;
        else if (tick_time <= noon_end_time)
            tick_id = (tick_time - noon_start_time) / mt.milliseconds_per_tick + (morning_end_time - break_end_time) / mt.milliseconds_per_tick + (break_start_time - morning_start_time) / mt.milliseconds_per_tick;
        else
            tick_id = (noon_end_time - noon_start_time) / mt.milliseconds_per_tick + (morning_end_time - break_end_time) / mt.milliseconds_per_tick + (break_start_time - morning_start_time) / mt.milliseconds_per_tick;
    }

    // update match engine
    mt.match_market_data(data, tick_id, last_tick_id);

    int order_id;
    for (auto it_order = order_opened.begin(); it_order != order_opened.end();)
    {
        mt.execute_order(fill, it_order->second);
        if (fill.first > 0)
        {
            LFRtnTradeField* rtn_trade = new LFRtnTradeField;
            strcpy(rtn_trade->InstrumentID, data->InstrumentID);
            rtn_trade->Price = fill.second / fill.first;
            rtn_trade->Volume = fill.first;
            rtn_trade->Direction = (strcmp(it_order->second->OrderType, "Buy") == 0)? LF_CHAR_Buy : LF_CHAR_Sell;
            rtn_trade->OffsetFlag = (strcmp(it_order->second->StartFlag, "Entry") == 0) ? LF_CHAR_Open : LF_CHAR_CloseToday;
            order_traded[it_order->first] = rtn_trade;
        }
        it_order->second->FillPrc = (it_order->second->FillVol > 0) ? it_order->second->FillAmt / it_order->second->FillVol : 0.0;
        it_order->second->TxnCost += get_transaction_cost(data->TradingDay, data->InstrumentID, fill.first, fill.second, (strcmp(it_order->second->StartFlag, "Entry") == 0) ? LF_CHAR_Open : LF_CHAR_CloseToday);
        it_order->second->OrderDur += tick_id - last_tick_id;
        if (it_order->second->OrderVol == it_order->second->FillVol)
        {
            if (strcmp(it_order->second->StartFlag, "Exit") == 0)
            {
                auto it_last_open_order = --order_closed.end();
                while (strcmp(it_last_open_order->second->StartFlag, "Entry") != 0 || strcmp(it_last_open_order->second->EndFlag, "Fill") != 0)
                    --it_last_open_order;
                it_last_open_order->second->FillDur = tick_id - it_last_open_order->second->OrderId - it_last_open_order->second->OrderDur;
                if (strcmp(it_order->second->OrderType, "Buy") == 0)
                    it_order->second->PnL = (it_last_open_order->second->FillPrc - it_order->second->FillPrc) * it_order->second->FillVol * contract_size - it_order->second->TxnCost - it_last_open_order->second->TxnCost;
                else
                    it_order->second->PnL = (it_order->second->FillPrc - it_last_open_order->second->FillPrc) * it_order->second->FillVol * contract_size - it_order->second->TxnCost - it_last_open_order->second->TxnCost;
                it_last_open_order->second->CloseOut = it_order->second->OrderId;
            }
            strcpy(it_order->second->EndFlag, "Fill");
            strcpy(it_order->second->EndTime, tick_str.c_str());
            order_closed[it_order->first] = it_order->second;
            order_id = it_order->first;
            ++it_order;
            order_opened.erase(order_id);
        }
        else
            ++it_order;
    }

    // update last_tick_id
    last_tick_id = tick_id;
}