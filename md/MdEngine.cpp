/*
Created on Sep 2018

@author: hufx

Md Engine
*/
#include "MdEngine.h"
#include "MarketTime.h"
#include <iostream>
#include <fstream>
#include <bzlib.h>

#define BUF_SIZE    200

MdEngine::MdEngine()
{
    tick_time = 0;
    tick_time_prev = 0;
}

MdEngine::~MdEngine()
{
    for (auto& tick: md_tick)
        delete tick;
}

MdEngine md;

#define GET_TICK_RECORD(line, pos, pos_next, md_tick) \
    tick_record = new LFMarketDataField;\
    pos = 0;\
    pos_next = line.find(',', pos);\
    strcpy(tick_record->TradingDay, line.substr(pos, pos_next - pos).c_str());\
    pos = pos_next + 1;\
    pos_next = line.find(',', pos);\
    strcpy(tick_record->InstrumentID, line.substr(pos, pos_next - pos).c_str());\
    pos = pos_next + 1;\
    pos_next = line.find(',', pos);\
    strcpy(tick_record->ExchangeID, line.substr(pos, pos_next - pos).c_str());\
    pos = pos_next + 1;\
    pos_next = line.find(',', pos);\
    strcpy(tick_record->ExchangeInstID, line.substr(pos, pos_next - pos).c_str());\
    pos = pos_next + 1;\
    pos_next = line.find(',', pos);\
    tick_record->LastPrice = atof(line.substr(pos, pos_next - pos).c_str());\
    pos = pos_next + 1;\
    pos_next = line.find(',', pos);\
    tick_record->PreSettlementPrice = atof(line.substr(pos, pos_next - pos).c_str());\
    pos = pos_next + 1;\
    pos_next = line.find(',', pos);\
    tick_record->PreClosePrice = atof(line.substr(pos, pos_next - pos).c_str());\
    pos = pos_next + 1;\
    pos_next = line.find(',', pos);\
    tick_record->PreOpenInterest = atof(line.substr(pos, pos_next - pos).c_str());\
    pos = pos_next + 1;\
    pos_next = line.find(',', pos);\
	tick_record->OpenPrice = atof(line.substr(pos, pos_next - pos).c_str());\
    pos = pos_next + 1;\
    pos_next = line.find(',', pos);\
	tick_record->HighestPrice = atof(line.substr(pos, pos_next - pos).c_str());\
    pos = pos_next + 1;\
    pos_next = line.find(',', pos);\
	tick_record->LowestPrice = atof(line.substr(pos, pos_next - pos).c_str());\
    pos = pos_next + 1;\
    pos_next = line.find(',', pos);\
	tick_record->Volume = atoi(line.substr(pos, pos_next - pos).c_str());\
    pos = pos_next + 1;\
    pos_next = line.find(',', pos);\
	tick_record->Turnover = atof(line.substr(pos, pos_next - pos).c_str());\
    pos = pos_next + 1;\
    pos_next = line.find(',', pos);\
	tick_record->OpenInterest = atof(line.substr(pos, pos_next - pos).c_str());\
    pos = pos_next + 1;\
    pos_next = line.find(',', pos);\
	tick_record->ClosePrice = atof(line.substr(pos, pos_next - pos).c_str());\
    pos = pos_next + 1;\
    pos_next = line.find(',', pos);\
	tick_record->SettlementPrice = atof(line.substr(pos, pos_next - pos).c_str());\
    pos = pos_next + 1;\
    pos_next = line.find(',', pos);\
	tick_record->UpperLimitPrice = atof(line.substr(pos, pos_next - pos).c_str());\
    pos = pos_next + 1;\
    pos_next = line.find(',', pos);\
	tick_record->LowerLimitPrice = atof(line.substr(pos, pos_next - pos).c_str());\
    pos = pos_next + 1;\
    pos_next = line.find(',', pos);\
	tick_record->PreDelta = atof(line.substr(pos, pos_next - pos).c_str());\
    pos = pos_next + 1;\
    pos_next = line.find(',', pos);\
	tick_record->CurrDelta = atof(line.substr(pos, pos_next - pos).c_str());\
    pos = pos_next + 1;\
    pos_next = line.find(',', pos);\
	strcpy(tick_record->UpdateTime, line.substr(pos, pos_next - pos).c_str());\
    pos = pos_next + 1;\
    pos_next = line.find(',', pos);\
	tick_record->UpdateMillisec = atoi(line.substr(pos, pos_next - pos).c_str());\
    pos = pos_next + 1;\
    pos_next = line.find(',', pos);\
	tick_record->BidPrice1 = atof(line.substr(pos, pos_next - pos).c_str());\
    pos = pos_next + 1;\
    pos_next = line.find(',', pos);\
	tick_record->BidVolume1 = atoi(line.substr(pos, pos_next - pos).c_str());\
    pos = pos_next + 1;\
    pos_next = line.find(',', pos);\
	tick_record->AskPrice1 = atof(line.substr(pos, pos_next - pos).c_str());\
    pos = pos_next + 1;\
    pos_next = line.find(',', pos);\
	tick_record->AskVolume1 = atoi(line.substr(pos, pos_next - pos).c_str());\
    pos = pos_next + 1;\
    pos_next = line.find(',', pos);\
	tick_record->BidPrice2 = atof(line.substr(pos, pos_next - pos).c_str());\
    pos = pos_next + 1;\
    pos_next = line.find(',', pos);\
	tick_record->BidVolume2 = atoi(line.substr(pos, pos_next - pos).c_str());\
    pos = pos_next + 1;\
    pos_next = line.find(',', pos);\
	tick_record->AskPrice2 = atof(line.substr(pos, pos_next - pos).c_str());\
    pos = pos_next + 1;\
    pos_next = line.find(',', pos);\
	tick_record->AskVolume2 = atoi(line.substr(pos, pos_next - pos).c_str());\
    pos = pos_next + 1;\
    pos_next = line.find(',', pos);\
	tick_record->BidPrice3 = atof(line.substr(pos, pos_next - pos).c_str());\
    pos = pos_next + 1;\
    pos_next = line.find(',', pos);\
	tick_record->BidVolume3 = atoi(line.substr(pos, pos_next - pos).c_str());\
    pos = pos_next + 1;\
    pos_next = line.find(',', pos);\
	tick_record->AskPrice3 = atof(line.substr(pos, pos_next - pos).c_str());\
    pos = pos_next + 1;\
    pos_next = line.find(',', pos);\
	tick_record->AskVolume3 = atoi(line.substr(pos, pos_next - pos).c_str());\
    pos = pos_next + 1;\
    pos_next = line.find(',', pos);\
	tick_record->BidPrice4 = atof(line.substr(pos, pos_next - pos).c_str());\
    pos = pos_next + 1;\
    pos_next = line.find(',', pos);\
	tick_record->BidVolume4 = atoi(line.substr(pos, pos_next - pos).c_str());\
    pos = pos_next + 1;\
    pos_next = line.find(',', pos);\
	tick_record->AskPrice4 = atof(line.substr(pos, pos_next - pos).c_str());\
    pos = pos_next + 1;\
    pos_next = line.find(',', pos);\
	tick_record->AskVolume4 = atoi(line.substr(pos, pos_next - pos).c_str());\
    pos = pos_next + 1;\
    pos_next = line.find(',', pos);\
	tick_record->BidPrice5 = atof(line.substr(pos, pos_next - pos).c_str());\
    pos = pos_next + 1;\
    pos_next = line.find(',', pos);\
	tick_record->BidVolume5 = atoi(line.substr(pos, pos_next - pos).c_str());\
    pos = pos_next + 1;\
    pos_next = line.find(',', pos);\
	tick_record->AskPrice5 = atof(line.substr(pos, pos_next - pos).c_str());\
    pos = pos_next + 1;\
    pos_next = line.find(',', pos);\
	tick_record->AskVolume5 = atoi(line.substr(pos, pos_next - pos).c_str());\
    pos = pos_next + 1;\
    pos_next = line.find(',', pos);\
	tick_record->AveragePrice = atof(line.substr(pos, pos_next - pos).c_str());\
    pos = pos_next + 1;\
    pos_next = line.find(',', pos);\
	strcpy(tick_record->ActionDay, line.substr(pos, pos_next - pos).c_str());\
    md_tick.push_back(tick_record);

void MdEngine::init(const std::string& date, const std::string& period, const std::string& ticker, const std::string& source)
{
    std::string exchange_id = get_exchange(ticker);
    std::string filename (std::string("/home/hufx/store/md_csv/") + source + "/future/tick/" + exchange_id + "/" + date + "/" + ticker + ".csv.bz2");

    int pos = filename.rfind('.');
    if (filename.substr(pos + 1) != "bz2")
    {
        std::ifstream file;
        int pos_next;
        file.open(filename.c_str(), std::ifstream::in);
        std::getline(file, line); // header
        std::getline(file, line);
        while (file.good())
        {
            GET_TICK_RECORD(line, pos, pos_next, md_tick);
            std::getline(file, line);
        }
        file.close();
    }
    else
    {
        FILE* file;
        BZFILE* bzfile;
        char buf[BUF_SIZE];
        int bzerror;
        std::string line, str;
        int pos_nextline, pos_next, linecout = 0;

        file = fopen(filename.c_str(), "r");
        if (!file)
            std::cerr << parse_milliseconds(tick_time) << " ERROR MdEngine %% - [init_market_data] file can not be opened" << std::endl;
        bzfile = BZ2_bzReadOpen(&bzerror, file, 0, 0, NULL, 0);
        if (bzerror != BZ_OK)
        {
            BZ2_bzReadClose(&bzerror, bzfile);
            std::cerr << parse_milliseconds(tick_time) << " ERROR MdEngine %% - [init_market_data] file can not be read" << std::endl;
        }
        bzerror = BZ_OK;
        while (bzerror == BZ_OK)
        {
            BZ2_bzRead(&bzerror, bzfile, buf, BUF_SIZE);
            if (bzerror == BZ_OK)
            {
                str = std::string(buf);
                pos_nextline = str.find('\n');
                if (pos_nextline != std::string::npos)
                {
                    line += str.substr(0, pos_nextline);
                    linecout += 1;
                    if (linecout > 1) // header
                    {
                        GET_TICK_RECORD(line, pos, pos_next, md_tick);
                    }
                    line = str.substr(pos_nextline + 1, std::string::npos);
                }
                else
                    line += str;
            }
        }
        if (bzerror != BZ_STREAM_END)
        {
            BZ2_bzReadClose(&bzerror, bzfile);
            std::cerr << parse_milliseconds(tick_time) << " ERROR MdEngine %% - [init_market_data] file read is unfinished" << std::endl;
        }
        else
        {
            str = std::string(buf);
            pos_nextline = str.find('\n');
            if (pos_nextline != std::string::npos)
            {
                line += str.substr(0, pos_nextline);
                linecout += 1;
                if (linecout > 1) // header
                {
                    GET_TICK_RECORD(line, pos, pos_next, md_tick);
                }
            }
            else
                std::cerr << parse_milliseconds(tick_time) << " ERROR MdEngine %% - [init_market_data] last tick record can not be read" << std::endl;
            BZ2_bzReadClose(&bzerror, bzfile);
        }
        if (fclose(file))
            std::cerr << parse_milliseconds(tick_time) << " ERROR MdEngine %% - [init_market_data] file can not be closed" << std::endl;
    }

    instrument_id = tick_record->InstrumentID;
    it_tick = md_tick.begin();
}

bool MdEngine::send_market_data()
{
    tick_record = *it_tick;
    ++it_tick;
    tick_time = parse_date_time(tick_record->ActionDay, tick_record->UpdateTime, tick_record->UpdateMillisec);
    return it_tick != md_tick.end();
}