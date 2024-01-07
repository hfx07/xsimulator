/*
Created on Oct 2018

@author: hufx

strategy demo
*/
#include "StrategyEngine.h"
#include "MarketTime.h"
#include "Constants.h"
#include <deque>
#include <vector>
#include <iostream>

#define SOURCE_INDEX SOURCE_CTP
#define TRADED_VOLUME_LIMIT 500

/* these 3 parameters are assumed and used in match engine and should be calibrated for a specific ticker */
#define HIDDEN_QUEUE_INIT_VOL 130 // init bid/ask volume at a hidden level (e.g. bid/ask 2/3/4/5... for level 1 market data)
#define HIDDEN_QUEUE_ADD_RATE 0.5 // limit order add rate at a hidden level
#define HIDDEN_QUEUE_CXL_RATE 0.5 // limit order cancel rate at a hidden level

struct Signal
{
    std::string name;
    int look_back;
    int param1;
    int param2;
    int trade_size;
    std::deque<double> TickPrice;
    bool has_open_position;
    bool has_open_long_position;
    bool has_open_short_position;
};

class Strategy: public StrategyEngine
{
protected:
    bool td_connected;
    bool trade_completed;
    int rid;
    int md_num;
    int traded_volume;
    std::string exchange;
    Signal signal;
public:
    virtual void init(const std::string& date, bool print_log);
    virtual void on_market_data(const LFMarketDataField* data, short source, long rcv_time);
    virtual void on_rsp_position(const LFRspPositionField* pos, int request_id, short source, long rcv_time);
    virtual void on_rtn_trade(const LFRtnTradeField* data, int request_id, short source, long rcv_time);
    virtual void on_rsp_order_insert(const LFInputOrderField* data, int request_id, short source, long rcv_time, short errorId=0, const char* errorMsg=nullptr);

public:
    std::string ticker;
    Strategy(const std::string& name);
};

Strategy::Strategy(const std::string& name): StrategyEngine(name)
{
    stop = false;
}

void Strategy::init(const std::string& date, bool print_log)
{
    // necessary initialization of internal fields
    td_connected = false;
    log = print_log;
    trade_completed = true;
    md_num = 0;
    traded_volume = 0;
    exchange = get_exchange(ticker);

    // ========= bind and initialize a signal ========
    signal.name = "sample_signal";
    signal.look_back = 1000;
    signal.param1 = 200;
    signal.param2 = 50;
    signal.TickPrice.clear();
    signal.has_open_position = false;
    signal.has_open_long_position = false;
    signal.has_open_short_position = false;
    signal.trade_size = 1;
}

void Strategy::on_rsp_position(const LFRspPositionField* pos, int request_id, short source, long rcv_time)
{
    if (request_id == -1 && source == SOURCE_INDEX)
    {
        td_connected = true;
        if (log)
            std::cout << parse_milliseconds(rcv_time) << " DEBUG " << name << " %% - [rsp_position] (source)" << source << " (rid)" << request_id << " (td)connected" << std::endl;
    }
    else
    {
        if (log)
            std::cout << parse_milliseconds(rcv_time) << " DEBUG " << name << " %% - [rsp_position] (source)" << source << " (rid)" << request_id << " (pos)long " << pos->LongPosition << " short " << pos->ShortPosition << " (cost)" << pos->Cost << " (pnl)" << pos->LongPnL + pos->ShortPnL - pos->Cost << std::endl;
    }
}

void Strategy::on_market_data(const LFMarketDataField* curr_md, short source, long rcv_time)
{
    if (strcmp(ticker.c_str(), curr_md->InstrumentID) == 0 && td_connected)
    {
        signal.TickPrice.push_back(curr_md->LastPrice);
        if (signal.TickPrice.size() > signal.look_back)
            signal.TickPrice.pop_front();
        md_num += 1;
        if (md_num < signal.look_back + 2)
            return;
        
        // ============ prepare data ============
        double rolling_min = 9999999;
        double rolling_max = 0;
        for (int i = 0; i < signal.param1; i++)
        {
            int idx = signal.look_back - 1 - signal.param2 - i; // delay
            double curPrice = signal.TickPrice[idx];
            rolling_max = (curPrice > rolling_max) ? curPrice: rolling_max;
            rolling_min = (curPrice < rolling_min) ? curPrice: rolling_min;
        }
        bool long_entry_condition = rolling_max <= curr_md->LastPrice;
        bool short_entry_condition = rolling_min >= curr_md->LastPrice;
        bool exit_condition = rolling_max > curr_md->LastPrice && rolling_min < curr_md->LastPrice;
        if (trade_completed)
        {
            if (long_entry_condition && !signal.has_open_position)
            {
                rid = insert_limit_order(SOURCE_INDEX, ticker.c_str(), exchange.c_str(),
                                         curr_md->UpperLimitPrice, signal.trade_size,
                                         LF_CHAR_Buy, LF_CHAR_Open);
                if (rid > 0)
                    trade_completed = false;
            }
            if (short_entry_condition && !signal.has_open_position)
            {
                rid = insert_limit_order(SOURCE_INDEX, ticker.c_str(), exchange.c_str(),
                                         curr_md->LowerLimitPrice, signal.trade_size,
                                         LF_CHAR_Sell, LF_CHAR_Open);
                if (rid > 0)
                    trade_completed = false;
            }
            if (exit_condition && signal.has_open_position)
            {
                if (signal.has_open_long_position)
                {
                    rid = insert_limit_order(SOURCE_INDEX, ticker.c_str(), exchange.c_str(),
                                             curr_md->LowerLimitPrice, signal.trade_size,
                                             LF_CHAR_Sell, LF_CHAR_CloseToday);
                    if (rid > 0)
                        trade_completed = false;
                }
                if (signal.has_open_short_position)
                {
                    rid = insert_limit_order(SOURCE_INDEX, ticker.c_str(), exchange.c_str(),
                                             curr_md->UpperLimitPrice, signal.trade_size,
                                             LF_CHAR_Buy, LF_CHAR_CloseToday);
                    if (rid > 0)
                        trade_completed = false;
                }
            }
        }
    }
}

void Strategy::on_rtn_trade(const LFRtnTradeField* rtn_trade, int request_id, short source, long rcv_time)
{
    if (log)
        std::cout << parse_milliseconds(rcv_time) << " DEBUG " << name << " %% - [rtn_trade] (source)" << source << " (rid)" << request_id << " (ticker)" << rtn_trade->InstrumentID << " (p)" << rtn_trade->Price << " (v)" << rtn_trade->Volume << " (direction)" << rtn_trade->Direction << " (offset)" << rtn_trade->OffsetFlag << " (pos)long " << td.pos.LongPosition << " short " << td.pos.ShortPosition << " (cost)" << td.pos.Cost << " (pnl)" << td.pos.LongPnL + td.pos.ShortPnL - td.pos.Cost << std::endl;
    traded_volume += rtn_trade->Volume;
    if (rid == request_id)
    {
        trade_completed = true;
        if (rtn_trade->OffsetFlag == LF_CHAR_Open)
        {
            signal.has_open_position = true;
            if (rtn_trade->Direction == LF_CHAR_Buy)
            {
                signal.has_open_long_position = true;
                signal.has_open_short_position = false;
            }
            else if (rtn_trade->Direction == LF_CHAR_Sell)
            {
                signal.has_open_short_position = true;
                signal.has_open_long_position = false;
            }
        }
        else if (rtn_trade->OffsetFlag == LF_CHAR_CloseToday)
        {
            signal.has_open_position = false;
            signal.has_open_short_position = false;
            signal.has_open_long_position = false;
        }
    }
    if (traded_volume >= TRADED_VOLUME_LIMIT)
    {
        if (log)
            std::cout << parse_milliseconds(rcv_time) << " DEBUG " << name << " %% - [finish] stop trading due to traded volume limit (v_trd)" << traded_volume << " (v_trd_limit)" << TRADED_VOLUME_LIMIT << std::endl;
        stop = true;
    }
}

void Strategy::on_rsp_order_insert(const LFInputOrderField* order_insert, int request_id, short source, long rcv_time, short errorId, const char* errorMsg)
{
    std::cout << parse_milliseconds(rcv_time) << " DEBUG " << name << " %% - [rsp_order_insert] (source)" << source << " (rid)" << request_id << " (ticker)" << order_insert->InstrumentID << " (p)" << order_insert->LimitPrice << " (v)" << order_insert->Volume << " (direction)" << order_insert->Direction << " (offset)" << order_insert->OffsetFlag << " (errId)" << errorId << " (errMsg)" << errorMsg << std::endl;
}

int main(int argc, const char* argv[])
{
    Strategy stg(std::string("strategy_demo"));
    std::vector<std::string> args;
    std::string period = "day";
    bool print_log = false;
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
        {
            std::cout << "Usage: " << argv[0] << " DATE INSTRUMENT_ID SOURCE LATENCY [-p, --period PERIOD] [-o, --order] [-l, --log] [-h, --help]" << std::endl;
            return 0;
        }
        else if (strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--period") == 0)
        {
            if (i + 1 < argc)
                period = argv[++i];
            else
            {
                std::cerr << "-p, --period option requires one argument." << std::endl;
                return 1;
            }
        }
        else if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--order") == 0)
            td.print_order = true;
        else if (strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "--log") == 0)
            print_log = true;
        else
            args.push_back(argv[i]);
    }
    if (args.size() != 4)
    {
        std::cerr << "Usage: " << argv[0] << " DATE INSTRUMENT_ID SOURCE LATENCY [-p, --period PERIOD] [-o, --order] [-l, --log] [-h, --help]" << std::endl;
        return 1;
    }
    md.init(args[0], period, args[1], args[2]);
    td.init(args[0], period, md.instrument_id, atoi(args[3].c_str()), HIDDEN_QUEUE_INIT_VOL, HIDDEN_QUEUE_ADD_RATE, HIDDEN_QUEUE_CXL_RATE);
    stg.ticker = md.instrument_id;
    stg.init(args[0], print_log);
    stg.run(SOURCE_INDEX);
    return 0;
}
