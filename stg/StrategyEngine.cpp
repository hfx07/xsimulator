/*
Created on Sep 2018

@author: hufx

Strategy Engine
*/
#include "StrategyEngine.h"
#include "MarketTime.h"
#include "Constants.h"
#include "TransactionCost.h"

StrategyEngine::StrategyEngine(const std::string& name): name(name)
{
    stop = false;
}

StrategyEngine::~StrategyEngine() {}

void StrategyEngine::run(short source)
{
    req_position(source);
    while(md.send_market_data() && !stop)
    {
        //md.send_market_data();
        if (td.tick_period.compare("day") == 0 && md.tick_time < td.night_end_time - 24 * 60 * 60 * 1000)
            continue;
        if (td.tick_period.compare("night") == 0 && md.tick_time >= td.morning_start_time + 24 * 60 * 60 * 1000)
            continue;
        if (md.tick_record->LastPrice > md.tick_record->UpperLimitPrice || md.tick_record->LastPrice < md.tick_record->LowerLimitPrice)
            continue;
        
        // when upperlimit or lowerlimit is reached
        if (md.tick_record->AskVolume1 == 0)
            md.tick_record->AskPrice1 = md.tick_record->UpperLimitPrice;
        if (md.tick_record->BidVolume1 == 0)
            md.tick_record->BidPrice1 = md.tick_record->LowerLimitPrice;
        
        td.receive_market_data(md.tick_record, md.tick_time, md.tick_time_prev);
        for(auto& order: td.order_traded)
        {
            td.pos.Cost += get_transaction_cost(md.tick_record->TradingDay, md.tick_record->InstrumentID, order.second->Volume, order.second->Price * order.second->Volume, order.second->OffsetFlag);
            if (order.second->Direction == LF_CHAR_Buy)
            {
                if (order.second->OffsetFlag == LF_CHAR_Open)
                {
                    td.pos.LongPosition += order.second->Volume;
                    td.pos.LongBalance += order.second->Price * order.second->Volume * td.contract_size;
                }
                else
                {
                    td.pos.ShortPosition -= order.second->Volume;
                    td.pos.ShortBalance -= order.second->Price * order.second->Volume * td.contract_size;
                    if (td.pos.ShortPosition == 0)
                        td.pos.ShortPnL = td.pos.ShortBalance;
                }
            }
            else if (order.second->Direction == LF_CHAR_Sell)
            {
                if (order.second->OffsetFlag == LF_CHAR_Open)
                {
                    td.pos.ShortPosition += order.second->Volume;
                    td.pos.ShortBalance += order.second->Price * order.second->Volume * td.contract_size;
                }
                else
                {
                    td.pos.LongPosition -= order.second->Volume;
                    td.pos.LongBalance -= order.second->Price * order.second->Volume * td.contract_size;
                    if (td.pos.LongPosition == 0)
                        td.pos.LongPnL = -td.pos.LongBalance;
                }
            }
            on_rtn_trade(order.second, order.first, source, md.tick_time + td.latency);
            delete order.second;
        }
        td.order_traded.clear();

        on_market_data(md.tick_record, source, md.tick_time + td.latency);
        md.tick_time_prev = md.tick_time;
    }
}

int StrategyEngine::req_position(short source)
{
    if (td.tick_period.compare("day") == 0)
    {
        long time = std::max(td.morning_start_time, md.tick_time);
        std::cout << parse_milliseconds(time + td.latency) << " DEBUG " << name << " %% - [req_position] (source)" << source << std::endl;
        on_rsp_position(&td.pos, (md.tick_time > 0) ? 0 : -1, source, time + 3 * td.latency);
    }
    else if (td.tick_period.compare("night") == 0)
    {
        long time = std::max(td.night_start_time, md.tick_time);
        std::cout << parse_milliseconds(time + td.latency) << " DEBUG " << name << " %% - [req_position] (source)" << source << std::endl;
        on_rsp_position(&td.pos, (md.tick_time > 0) ? 0 : -1, source, time + 3 * td.latency);
    }
    else
    {
        std::cout << parse_milliseconds(md.tick_time) << " ERROR " << name << " %% - [req_position] (source)" << source << " (errMsg)交易时段必须为day、night或both" << std::endl;
        stop = true;
    }
    return -1;
}

void StrategyEngine::on_rsp_position(const LFRspPositionField* pos, int request_id, short source, long rcv_time)
{
    if (pos->LongPosition == pos->ShortPosition)
        std::cout << parse_milliseconds(rcv_time) << " DEBUG " << name << " %% - [rsp_position] (source)" << source << " (rid)" << request_id << " (pos)long " << pos->LongPosition << " short " << pos->ShortPosition << " (cost)" << pos->Cost << " (pnl)" << pos->LongPnL + pos->ShortPnL - pos->Cost << std::endl;
    else
        std::cout << parse_milliseconds(rcv_time) << " DEBUG " << name << " %% - [rsp_position] (source)" << source << " (rid)" << request_id << " (pos)long " << pos->LongPosition << " short " << pos->ShortPosition << " (cost)" << pos->Cost << std::endl;
}

int StrategyEngine::insert_limit_order(short source, std::string instrument_id, std::string exchange_id, double price, int volume, char direction, char offset)
{
    td.rid++;
    int request_id = td.rid;

    OrderField* order = new OrderField;
    strcpy(order->StartTime, td.tick_str.c_str());
    if (offset == LF_CHAR_Open)
        strcpy(order->StartFlag, "Entry");
    else if (offset == LF_CHAR_CloseToday)
        strcpy(order->StartFlag, "Exit");
    if (direction == LF_CHAR_Buy)
        strcpy(order->OrderType, "Buy");
    else if (direction == LF_CHAR_Sell)
        strcpy(order->OrderType, "Sell");
    order->OrderId = td.tick_id;
    order->OrderPrc = price;
    order->OrderVol = volume;
    order->AheadVol = 0.0;
    order->FillVol = 0;
    order->FillAmt = 0;
    order->OrderDur = 0;
    order->FillDur = 0;
    order->TxnCost = 0.0;
    order->PnL = 0.0;
    order->CloseOut = 0;
    td.order_opened[request_id] = order;
    std::cout << parse_milliseconds(md.tick_time + td.latency) << " DEBUG " << name << " %% - [insert_limit_order] (source)" << source << " (rid)" << request_id << " (ticker)" << instrument_id << " (exchange)" << exchange_id << " (p)" << price << " (v)" << volume << " (direction)" << direction << " (offset)" << offset << std::endl;
    
    strcpy(td.rtn_order.InstrumentID, instrument_id.c_str());
    td.rtn_order.LimitPrice = price;
    td.rtn_order.VolumeTraded = 0;
    td.rtn_order.VolumeTotal = volume;
    td.rtn_order.VolumeTotalOriginal = volume;
    td.rtn_order.Direction = direction;
    td.rtn_order.OffsetFlag = offset;
    td.rtn_order.OrderStatus = LF_CHAR_NoTradeQueueing;
    td.rtn_order.RequestID = request_id;
    on_rtn_order(&td.rtn_order, request_id, source, md.tick_time + 3 * td.latency);
    return request_id;
}

int StrategyEngine::cancel_order(short source, int order_id)
{
    td.rid++;
    int request_id = td.rid;
    std::cout << parse_milliseconds(md.tick_time + td.latency) << " DEBUG " << name << " %% - [cancel_order] (source)" << source << " (rid)" << request_id << " (order_id)" << order_id << std::endl;

    auto it = td.order_opened.find(order_id);
    if (it == td.order_opened.end())
    {
        strcpy(td.order_action.InstrumentID, md.instrument_id.c_str());
        td.order_action.ActionFlag = LF_CHAR_AF_Delete;
        td.order_action.LimitPrice = 0;
        td.order_action.VolumeChange = 0;
        td.order_action.RequestID = request_id;
        on_rsp_order_action(&td.order_action, order_id, source, md.tick_time + 3 * td.latency, 26, "CTP:报单已全成交或已撤销，不能再撤");
    }
    else
    {
        strcpy(it->second->EndFlag, "Cancel");
        strcpy(it->second->EndTime, td.tick_str.c_str());

        strcpy(td.rtn_order.InstrumentID, md.instrument_id.c_str());
        td.rtn_order.LimitPrice = it->second->OrderPrc;
        td.rtn_order.VolumeTraded = it->second->FillVol;
        td.rtn_order.VolumeTotal = it->second->OrderVol - it->second->FillVol;
        td.rtn_order.VolumeTotalOriginal = it->second->OrderVol;
        if (strcmp(it->second->OrderType, "Buy") == 0)
            td.rtn_order.Direction = LF_CHAR_Buy;
        else if (strcmp(it->second->OrderType, "Sell") == 0)
            td.rtn_order.Direction = LF_CHAR_Sell;
        if (strcmp(it->second->StartFlag, "Entry") == 0)
            td.rtn_order.OffsetFlag = LF_CHAR_Open;
        else if (strcmp(it->second->StartFlag, "Exit") == 0)
            td.rtn_order.OffsetFlag = LF_CHAR_CloseToday;
        td.rtn_order.OrderStatus = LF_CHAR_Canceled;
        td.rtn_order.RequestID = it->first;
        on_rtn_order(&td.rtn_order, it->first, source, md.tick_time + 3 * td.latency);
        
        td.order_closed[it->first] = it->second;
        td.order_opened.erase(it->first);
    }
    return request_id;
}