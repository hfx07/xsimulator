/*
Created on Sep 2018

@author: hufx

Tick size, Contract size, Exchange, Market
*/
#ifndef QUOTES_H
#define QUOTES_H

#include <cstring>
#include <cctype>
#include <string>

#define MARKET_CHINA_FUTURE_COMMODITY   "CHINA_FUTURE_COMMODITY"    //中国商品期货
#define MARKET_CHINA_FUTURE_INDEX       "CHINA_FUTURE_INDEX"        //中国股指期货
#define MARKET_CHINA_FUTURE_TREASURY    "CHINA_FUTURE_TREASURY"     //中国国债期货
#define MARKET_CHINA_STOCK              "CHINA_STOCK"               //中国股票

#ifndef EXCHANGE_SSE
#define EXCHANGE_SSE    "SSE"    //上海证券交易所
#endif
#ifndef EXCHANGE_SZE
#define EXCHANGE_SZE    "SZE"    //深圳证券交易所
#endif
#ifndef EXCHANGE_CFFEX
#define EXCHANGE_CFFEX  "CFFEX"  //中国金融期货交易所
#endif
#ifndef EXCHANGE_SHFE
#define EXCHANGE_SHFE   "SHFE"   //上海期货交易所
#endif
#ifndef EXCHANGE_DCE
#define EXCHANGE_DCE    "DCE"    //大连商品交易所
#endif
#ifndef EXCHANGE_CZCE
#define EXCHANGE_CZCE   "CZCE"   //郑州商品交易所
#endif

inline std::string get_instrument_id_alp(const std::string& instrument_id)
{
    std::string instrument_id_alp;
    for (char c: instrument_id)
    {
        if (isalpha(c))
            instrument_id_alp += c;
    }
    return instrument_id_alp;
}

inline int get_tick_size(const std::string& instrument_id, const std::string& trading_day = "NULL")
{
    double tick_size;
    std::string instrument_id_alp = get_instrument_id_alp(instrument_id);
    if (instrument_id_alp.length() == 0)
        tick_size = 0.01;
    /* SHFE */
    else if (instrument_id_alp.compare("cu") == 0)
        tick_size = 10;
    else if (instrument_id_alp.compare("al") == 0)
        tick_size = 5;
    else if (instrument_id_alp.compare("zn") == 0)
        tick_size = 5;
    else if (instrument_id_alp.compare("pb") == 0)
        tick_size = 5;
    else if (instrument_id_alp.compare("ni") == 0)
        tick_size = 10;
    else if (instrument_id_alp.compare("sn") == 0)
        tick_size = 10;
    else if (instrument_id_alp.compare("au") == 0)
        tick_size = 0.05;
    else if (instrument_id_alp.compare("ag") == 0)
        tick_size = 1;
    else if (instrument_id_alp.compare("rb") == 0)
        tick_size = 1;
    else if (instrument_id_alp.compare("wr") == 0)
        tick_size = 1;
    else if (instrument_id_alp.compare("hc") == 0)
        tick_size = 1;
    else if (instrument_id_alp.compare("fu") == 0)
        tick_size = 1;
    else if (instrument_id_alp.compare("bu") == 0)
        tick_size = 2;
    else if (instrument_id_alp.compare("ru") == 0)
        tick_size = 5;
    else if (instrument_id_alp.compare("sc") == 0)
        tick_size = 0.1;
    /* DCE */
    else if (instrument_id_alp.compare("c") == 0)
        tick_size = 1;
    else if (instrument_id_alp.compare("cs") == 0)
        tick_size = 1;
    else if (instrument_id_alp.compare("a") == 0)
        tick_size = 1;
    else if (instrument_id_alp.compare("b") == 0)
        tick_size = 1;
    else if (instrument_id_alp.compare("m") == 0)
        tick_size = 1;
    else if (instrument_id_alp.compare("y") == 0)
        tick_size = 2;
    else if (instrument_id_alp.compare("p") == 0)
        tick_size = 2;
    else if (instrument_id_alp.compare("fb") == 0)
        tick_size = 0.05;
    else if (instrument_id_alp.compare("bb") == 0)
        tick_size = 0.05;
    else if (instrument_id_alp.compare("jd") == 0)
        tick_size = 1;
    else if (instrument_id_alp.compare("l") == 0)
        tick_size = 5;
    else if (instrument_id_alp.compare("v") == 0)
        tick_size = 5;
    else if (instrument_id_alp.compare("pp") == 0)
        tick_size = 1;
    else if (instrument_id_alp.compare("j") == 0)
        tick_size = 0.5;
    else if (instrument_id_alp.compare("jm") == 0)
        tick_size = 0.5;
    else if (instrument_id_alp.compare("i") == 0)
        tick_size = 0.5;
    /* CZCE */
    else if (instrument_id_alp.compare("WH") == 0)
        tick_size = 1;
    else if (instrument_id_alp.compare("PM") == 0)
        tick_size = 1;
    else if (instrument_id_alp.compare("CF") == 0)
        tick_size = 5;
    else if (instrument_id_alp.compare("SR") == 0)
        tick_size = 1;
    else if (instrument_id_alp.compare("OI") == 0)
    {
        // http://www.czce.com.cn/cn/rootfiles/2018/05/07/1526089634152762-1526089634208871.pdf
        if (trading_day != "NULL" && trading_day < "20180516")
            tick_size = 2;
        else
            tick_size = 1;
    }
    else if (instrument_id_alp.compare("RI") == 0)
        tick_size = 1;
    else if (instrument_id_alp.compare("RS") == 0)
        tick_size = 1;
    else if (instrument_id_alp.compare("RM") == 0)
        tick_size = 1;
    else if (instrument_id_alp.compare("JR") == 0)
        tick_size = 1;
    else if (instrument_id_alp.compare("LR") == 0)
        tick_size = 1;
    else if (instrument_id_alp.compare("TA") == 0)
        tick_size = 2;
    else if (instrument_id_alp.compare("MA") == 0)
        tick_size = 1;
    else if (instrument_id_alp.compare("ME") == 0)
        tick_size = 1;
    else if (instrument_id_alp.compare("FG") == 0)
        tick_size = 1;
    else if (instrument_id_alp.compare("ZC") == 0)
        tick_size = 0.2;
    else if (instrument_id_alp.compare("SF") == 0)
        tick_size = 2;
    else if (instrument_id_alp.compare("SM") == 0)
        tick_size = 2;
    else if (instrument_id_alp.compare("CY") == 0)
        tick_size = 5;
    else if (instrument_id_alp.compare("AP") == 0)
        tick_size = 1;
    /* CFFEX */
    else if (instrument_id_alp.compare("IF") == 0)
        tick_size = 0.2;
    else if (instrument_id_alp.compare("IH") == 0)
        tick_size = 0.2;
    else if (instrument_id_alp.compare("IC") == 0)
        tick_size = 0.2;
    else if (instrument_id_alp.compare("TF") == 0)
        tick_size = 0.005;
    else if (instrument_id_alp.compare("T") == 0)
        tick_size = 0.005;
    else if (instrument_id_alp.compare("TS") == 0)
        tick_size = 0.005;
    return tick_size;
}

inline int get_contract_size(const std::string& instrument_id, const std::string& trading_day = "NULL")
{
    int contract_size;
    std::string instrument_id_alp = get_instrument_id_alp(instrument_id);
    if (instrument_id_alp.length() == 0)
        contract_size = 1;
    /* SHFE */
    else if (instrument_id_alp.compare("cu") == 0)
        contract_size = 5;
    else if (instrument_id_alp.compare("al") == 0)
        contract_size = 5;
    else if (instrument_id_alp.compare("zn") == 0)
        contract_size = 5;
    else if (instrument_id_alp.compare("pb") == 0)
        contract_size = 5;
    else if (instrument_id_alp.compare("ni") == 0)
        contract_size = 1;
    else if (instrument_id_alp.compare("sn") == 0)
        contract_size = 1;
    else if (instrument_id_alp.compare("au") == 0)
        contract_size = 1000;
    else if (instrument_id_alp.compare("ag") == 0)
        contract_size = 15;
    else if (instrument_id_alp.compare("rb") == 0)
        contract_size = 10;
    else if (instrument_id_alp.compare("wr") == 0)
        contract_size = 10;
    else if (instrument_id_alp.compare("hc") == 0)
        contract_size = 10;
    else if (instrument_id_alp.compare("fu") == 0)
    {
        // http://www.shfe.com.cn/news/notice/911330668.html
        if (trading_day != "NULL" && trading_day < "20180716")
            contract_size = 50;
        else
            contract_size = 10;
    }
    else if (instrument_id_alp.compare("bu") == 0)
        contract_size = 10;
    else if (instrument_id_alp.compare("ru") == 0)
        contract_size = 10;
    else if (instrument_id_alp.compare("sc") == 0)
        contract_size = 1000;
    /* DCE */
    else if (instrument_id_alp.compare("c") == 0)
        contract_size = 10;
    else if (instrument_id_alp.compare("cs") == 0)
        contract_size = 10;
    else if (instrument_id_alp.compare("a") == 0)
        contract_size = 10;
    else if (instrument_id_alp.compare("b") == 0)
        contract_size = 10;
    else if (instrument_id_alp.compare("m") == 0)
        contract_size = 10;
    else if (instrument_id_alp.compare("y") == 0)
        contract_size = 10;
    else if (instrument_id_alp.compare("p") == 0)
        contract_size = 10;
    else if (instrument_id_alp.compare("fb") == 0)
        contract_size = 500;
    else if (instrument_id_alp.compare("bb") == 0)
        contract_size = 500;
    else if (instrument_id_alp.compare("jd") == 0)
        contract_size = 10;
    else if (instrument_id_alp.compare("l") == 0)
        contract_size = 5;
    else if (instrument_id_alp.compare("v") == 0)
        contract_size = 5;
    else if (instrument_id_alp.compare("pp") == 0)
        contract_size = 5;
    else if (instrument_id_alp.compare("j") == 0)
        contract_size = 100;
    else if (instrument_id_alp.compare("jm") == 0)
        contract_size = 60;
    else if (instrument_id_alp.compare("i") == 0)
        contract_size = 100;
    /* CZCE */
    else if (instrument_id_alp.compare("WH") == 0)
        contract_size = 20;
    else if (instrument_id_alp.compare("PM") == 0)
        contract_size = 50;
    else if (instrument_id_alp.compare("CF") == 0)
        contract_size = 5;
    else if (instrument_id_alp.compare("SR") == 0)
        contract_size = 10;
    else if (instrument_id_alp.compare("OI") == 0)
        contract_size = 10;
    else if (instrument_id_alp.compare("RI") == 0)
        contract_size = 20;
    else if (instrument_id_alp.compare("RS") == 0)
        contract_size = 10;
    else if (instrument_id_alp.compare("RM") == 0)
        contract_size = 10;
    else if (instrument_id_alp.compare("JR") == 0)
        contract_size = 20;
    else if (instrument_id_alp.compare("LR") == 0)
        contract_size = 20;
    else if (instrument_id_alp.compare("TA") == 0)
        contract_size = 5;
    else if (instrument_id_alp.compare("MA") == 0)
        contract_size = 10;
    else if (instrument_id_alp.compare("ME") == 0)
        contract_size = 50;
    else if (instrument_id_alp.compare("FG") == 0)
        contract_size = 20;
    else if (instrument_id_alp.compare("ZC") == 0)
        contract_size = 100;
    else if (instrument_id_alp.compare("SF") == 0)
        contract_size = 5;
    else if (instrument_id_alp.compare("SM") == 0)
        contract_size = 5;
    else if (instrument_id_alp.compare("CY") == 0)
        contract_size = 5;
    else if (instrument_id_alp.compare("AP") == 0)
        contract_size = 10;
    /* CFFEX */
    else if (instrument_id_alp.compare("IF") == 0)
        contract_size = 300;
    else if (instrument_id_alp.compare("IH") == 0)
        contract_size = 300;
    else if (instrument_id_alp.compare("IC") == 0)
        contract_size = 200;
    else if (instrument_id_alp.compare("TF") == 0)
        contract_size = 10000;
    else if (instrument_id_alp.compare("T") == 0)
        contract_size = 10000;
    else if (instrument_id_alp.compare("TS") == 0)
        contract_size = 10000;
    return contract_size;
}

inline std::string get_exchange(const std::string& instrument_id)
{
    std::string exchange;
    std::string instrument_id_alp = get_instrument_id_alp(instrument_id);
    if (instrument_id_alp.length() == 0)
    {
        if ((instrument_id[0] == '6' && instrument_id[1] == '0') || instrument_id.compare("000300") == 0 || (instrument_id[0] == '9' && instrument_id[1] == '9') || instrument_id[0] == '5')
            exchange = EXCHANGE_SSE;
        else
            exchange = EXCHANGE_SZE;
    }
    else if (instrument_id_alp.compare("cu") == 0)
        exchange = EXCHANGE_SHFE;
    else if (instrument_id_alp.compare("al") == 0)
        exchange = EXCHANGE_SHFE;
    else if (instrument_id_alp.compare("zn") == 0)
        exchange = EXCHANGE_SHFE;
    else if (instrument_id_alp.compare("pb") == 0)
        exchange = EXCHANGE_SHFE;
    else if (instrument_id_alp.compare("ni") == 0)
        exchange = EXCHANGE_SHFE;
    else if (instrument_id_alp.compare("sn") == 0)
        exchange = EXCHANGE_SHFE;
    else if (instrument_id_alp.compare("au") == 0)
        exchange = EXCHANGE_SHFE;
    else if (instrument_id_alp.compare("ag") == 0)
        exchange = EXCHANGE_SHFE;
    else if (instrument_id_alp.compare("rb") == 0)
        exchange = EXCHANGE_SHFE;
    else if (instrument_id_alp.compare("wr") == 0)
        exchange = EXCHANGE_SHFE;
    else if (instrument_id_alp.compare("hc") == 0)
        exchange = EXCHANGE_SHFE;
    else if (instrument_id_alp.compare("fu") == 0)
        exchange = EXCHANGE_SHFE;
    else if (instrument_id_alp.compare("bu") == 0)
        exchange = EXCHANGE_SHFE;
    else if (instrument_id_alp.compare("ru") == 0)
        exchange = EXCHANGE_SHFE;
    else if (instrument_id_alp.compare("sc") == 0)
        exchange = EXCHANGE_SHFE;
    else if (instrument_id_alp.compare("c") == 0)
        exchange = EXCHANGE_DCE;
    else if (instrument_id_alp.compare("cs") == 0)
        exchange = EXCHANGE_DCE;
    else if (instrument_id_alp.compare("a") == 0)
        exchange = EXCHANGE_DCE;
    else if (instrument_id_alp.compare("b") == 0)
        exchange = EXCHANGE_DCE;
    else if (instrument_id_alp.compare("m") == 0)
        exchange = EXCHANGE_DCE;
    else if (instrument_id_alp.compare("y") == 0)
        exchange = EXCHANGE_DCE;
    else if (instrument_id_alp.compare("p") == 0)
        exchange = EXCHANGE_DCE;
    else if (instrument_id_alp.compare("fb") == 0)
        exchange = EXCHANGE_DCE;
    else if (instrument_id_alp.compare("bb") == 0)
        exchange = EXCHANGE_DCE;
    else if (instrument_id_alp.compare("jd") == 0)
        exchange = EXCHANGE_DCE;
    else if (instrument_id_alp.compare("l") == 0)
        exchange = EXCHANGE_DCE;
    else if (instrument_id_alp.compare("v") == 0)
        exchange = EXCHANGE_DCE;
    else if (instrument_id_alp.compare("pp") == 0)
        exchange = EXCHANGE_DCE;
    else if (instrument_id_alp.compare("j") == 0)
        exchange = EXCHANGE_DCE;
    else if (instrument_id_alp.compare("jm") == 0)
        exchange = EXCHANGE_DCE;
    else if (instrument_id_alp.compare("i") == 0)
        exchange = EXCHANGE_DCE;
    else if (instrument_id_alp.compare("WH") == 0)
        exchange = EXCHANGE_CZCE;
    else if (instrument_id_alp.compare("PM") == 0)
        exchange = EXCHANGE_CZCE;
    else if (instrument_id_alp.compare("CF") == 0)
        exchange = EXCHANGE_CZCE;
    else if (instrument_id_alp.compare("SR") == 0)
        exchange = EXCHANGE_CZCE;
    else if (instrument_id_alp.compare("OI") == 0)
        exchange = EXCHANGE_CZCE;
    else if (instrument_id_alp.compare("RI") == 0)
        exchange = EXCHANGE_CZCE;
    else if (instrument_id_alp.compare("RS") == 0)
        exchange = EXCHANGE_CZCE;
    else if (instrument_id_alp.compare("RM") == 0)
        exchange = EXCHANGE_CZCE;
    else if (instrument_id_alp.compare("JR") == 0)
        exchange = EXCHANGE_CZCE;
    else if (instrument_id_alp.compare("LR") == 0)
        exchange = EXCHANGE_CZCE;
    else if (instrument_id_alp.compare("TA") == 0)
        exchange = EXCHANGE_CZCE;
    else if (instrument_id_alp.compare("MA") == 0)
        exchange = EXCHANGE_CZCE;
    else if (instrument_id_alp.compare("ME") == 0)
        exchange = EXCHANGE_CZCE;
    else if (instrument_id_alp.compare("FG") == 0)
        exchange = EXCHANGE_CZCE;
    else if (instrument_id_alp.compare("ZC") == 0)
        exchange = EXCHANGE_CZCE;
    else if (instrument_id_alp.compare("SF") == 0)
        exchange = EXCHANGE_CZCE;
    else if (instrument_id_alp.compare("SM") == 0)
        exchange = EXCHANGE_CZCE;
    else if (instrument_id_alp.compare("CY") == 0)
        exchange = EXCHANGE_CZCE;
    else if (instrument_id_alp.compare("AP") == 0)
        exchange = EXCHANGE_CZCE;
    else if (instrument_id_alp.compare("IF") == 0)
        exchange = EXCHANGE_CFFEX;
    else if (instrument_id_alp.compare("IH") == 0)
        exchange = EXCHANGE_CFFEX;
    else if (instrument_id_alp.compare("IC") == 0)
        exchange = EXCHANGE_CFFEX;
    else if (instrument_id_alp.compare("TF") == 0)
        exchange = EXCHANGE_CFFEX;
    else if (instrument_id_alp.compare("T") == 0)
        exchange = EXCHANGE_CFFEX;
    else if (instrument_id_alp.compare("TS") == 0)
        exchange = EXCHANGE_CFFEX;
    return exchange;
}

inline std::string get_market(const std::string& instrument_id)
{
    std::string market;
    std::string instrument_id_alp = get_instrument_id_alp(instrument_id);
    std::string exchange = get_exchange(instrument_id);
    if (exchange.compare(EXCHANGE_SSE) == 0 || exchange.compare(EXCHANGE_SZE) == 0)
        market = MARKET_CHINA_STOCK;
    else if (exchange.compare(EXCHANGE_SHFE) == 0 || exchange.compare(EXCHANGE_DCE) == 0 || exchange.compare(EXCHANGE_CZCE) == 0)
        market = MARKET_CHINA_FUTURE_COMMODITY;
    else if (exchange.compare(EXCHANGE_CFFEX) == 0 && (instrument_id_alp.compare("IF") == 0 || instrument_id_alp.compare("IH") == 0 || instrument_id_alp.compare("IC") == 0))
        market = MARKET_CHINA_FUTURE_INDEX;
    else if (exchange.compare(EXCHANGE_CFFEX) == 0 && (instrument_id_alp.compare("TF") == 0 || instrument_id_alp.compare("T") == 0 || instrument_id_alp.compare("TS") == 0))
        market = MARKET_CHINA_FUTURE_TREASURY;
    return market;
}

#endif