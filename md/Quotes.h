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
#ifndef EXCHANGE_INE
#define EXCHANGE_INE   "INE"   //上海国际能源交易中心
#endif
#ifndef EXCHANGE_DCE
#define EXCHANGE_DCE    "DCE"    //大连商品交易所
#endif
#ifndef EXCHANGE_CZCE
#define EXCHANGE_CZCE   "CZCE"   //郑州商品交易所
#endif
#ifndef EXCHANGE_GFEX
#define EXCHANGE_GFEX    "GFEX"   //广州期货交易所
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

inline std::string get_instrument_id_mon(const std::string& instrument_id)
{
    std::string instrument_id_mon;
    for (char c: instrument_id)
    {
        if !isalpha(c)
            instrument_id_mon += c;
    }
    return instrument_id_mon;
}

inline int get_tick_size(const std::string& instrument_id, const std::string& trading_day = "NULL")
{
    double tick_size;
    std::string instrument_id_alp = get_instrument_id_alp(instrument_id);
    std::string instrument_id_mon = get_instrument_id_mon(instrument_id);
    if (instrument_id_alp.length() == 0)
        tick_size = 0.01;
    /* SHFE */
    else if (instrument_id_alp.compare("cu") == 0)
        tick_size = 10;
    else if (instrument_id_alp.compare("al") == 0)
    {
        // https://www.shfe.com.cn/news/notice/3617075.html
        if (trading_day < "20080501" && instrument_id_mon < "0805")
            tick_size = 10;
        // https://www.shfe.com.cn/news/notice/73243296.html
        else
            tick_size = 5;
    }
    else if (instrument_id_alp.compare("zn") == 0) // https://www.shfe.com.cn/news/notice/72228525.html
        tick_size = 5;
    else if (instrument_id_alp.compare("pb") == 0)
        tick_size = 5;
    else if (instrument_id_alp.compare("ni") == 0)
        tick_size = 10;
    else if (instrument_id_alp.compare("sn") == 0)
        tick_size = 10;
    else if (instrument_id_alp.compare("au") == 0)
    {
        // http://www.shfe.com.cn/news/notice/3544645.html
        if (trading_day != "NULL" && trading_day < "20130625")
            tick_size = 0.01;
        // http://www.shfe.com.cn/news/notice/911335477.html
        else if (trading_day != "NULL" && trading_day < "20191210")
            tick_size = 0.05;
        else
            tick_size = 0.02;
    }
    else if (instrument_id_alp.compare("ag") == 0)
        tick_size = 1;
    else if (instrument_id_alp.compare("rb") == 0)
        tick_size = 1;
    else if (instrument_id_alp.compare("wr") == 0)
        tick_size = 1;
    else if (instrument_id_alp.compare("hc") == 0)
    {
        // http://www.shfe.com.cn/news/notice/911322663.html
        if (trading_day != "NULL" && trading_day < "20150428")
            tick_size = 2;
        else
            tick_size = 1;
    }
    else if (instrument_id_alp.compare("fu") == 0)
        tick_size = 1;
    else if (instrument_id_alp.compare("bu") == 0)
    {
        // http://www.shfe.com.cn/news/notice/911340717.html
        if (trading_day != "NULL" && trading_day < "20220316")
            tick_size = 2;
        else
            tick_size = 1;
    }
    else if (instrument_id_alp.compare("ru") == 0)
        tick_size = 5;
    else if (instrument_id_alp.compare("sp") == 0)
        tick_size = 2;
    else if (instrument_id_alp.compare("ss") == 0)
        tick_size = 5;
    else if (instrument_id_alp.compare("ao") == 0)
        tick_size = 1;
    else if (instrument_id_alp.compare("br") == 0)
        tick_size = 5;
    /* INE */
    else if (instrument_id_alp.compare("sc") == 0)
        tick_size = 0.1;
    else if (instrument_id_alp.compare("nr") == 0)
        tick_size = 5;
    else if (instrument_id_alp.compare("lu") == 0)
        tick_size = 1;
    else if (instrument_id_alp.compare("bc") == 0)
        tick_size = 10;
    else if (instrument_id_alp.compare("ec") == 0)
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
    {
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6191275/index.html
        if (trading_day != "NULL" && trading_day < "20191015")
            tick_size = 0.05;
        else
            tick_size = 0.5;
    }
    else if (instrument_id_alp.compare("bb") == 0)
        tick_size = 0.05;
    else if (instrument_id_alp.compare("jd") == 0)
        tick_size = 1;
    else if (instrument_id_alp.compare("l") == 0)
    {
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6295000/index.html; http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6293982/index.html
        if (trading_day != "NULL" && trading_day < "20211101")
            tick_size = 5;
        else
            tick_size = 1;
    }
    else if (instrument_id_alp.compare("v") == 0)
    {
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6295000/index.html; http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6293982/index.html
        if (trading_day != "NULL" && trading_day < "20211101")
            tick_size = 5;
        else
            tick_size = 1;
    }
    else if (instrument_id_alp.compare("pp") == 0)
        tick_size = 1;
    else if (instrument_id_alp.compare("j") == 0)
    {
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/5000074/index.html
        if (trading_day != "NULL" && trading_day < "20150418")
            tick_size = 1;
        else
            tick_size = 0.5;
    }
    else if (instrument_id_alp.compare("jm") == 0)
    {
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/5000074/index.html
        if (trading_day != "NULL" && trading_day < "20150418")
            tick_size = 1;
        else
            tick_size = 0.5;
    }
    else if (instrument_id_alp.compare("i") == 0)
    {
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/5000074/index.html
        if (trading_day != "NULL" && trading_day < "20150418")
            tick_size = 1;
        else
            tick_size = 0.5;
    }
    else if (instrument_id_alp.compare("eg") == 0)
        tick_size = 1;
    else if (instrument_id_alp.compare("rr") == 0)
        tick_size = 1;
    else if (instrument_id_alp.compare("eb") == 0)
        tick_size = 1;
    else if (instrument_id_alp.compare("pg") == 0)
        tick_size = 1;
    else if (instrument_id_alp.compare("lh") == 0)
        tick_size = 5;
    /* CZCE */
    else if (instrument_id_alp.compare("WS") == 0) /* eliminated now */
        tick_size = 1;
    // http://www.czce.com.cn/cn/sspz/pm/pzjs/qh/webinfo/2012/01/1325851217868694.htm
    else if (instrument_id_alp.compare("QM") == 0) /* eliminated now */
        tick_size = 1;
    // http://www.czce.com.cn/cn/rootfiles/2012/07/11/1340962525895641-1340962526154737.pdf
    else if (instrument_id_alp.compare("WH") == 0)
        tick_size = 1;
    else if (instrument_id_alp.compare("WT") == 0) /* eliminated now */
        tick_size = 1;
    // http://www.czce.com.cn/cn/sspz/pm/pzjs/qh/webinfo/2012/01/1325851217868694.htm
    else if (instrument_id_alp.compare("PM") == 0)
        tick_size = 1;
    else if (instrument_id_alp.compare("CF") == 0)
        tick_size = 5;
    else if (instrument_id_alp.compare("SR") == 0)
        tick_size = 1;
    else if (instrument_id_alp.compare("RO") == 0) /* eliminated now */
        tick_size = 2;
    // http://www.czce.com.cn/cn/rootfiles/2012/07/11/1340962525895641-1340962526154737.pdf
    else if (instrument_id_alp.compare("OI") == 0)
    {
        // http://www.czce.com.cn/cn/rootfiles/2018/05/07/1526089634152762-1526089634208871.pdf
        if (trading_day != "NULL" && trading_day < "20180516")
            tick_size = 2;
        else
            tick_size = 1;
    }
    else if (instrument_id_alp.compare("ER") == 0) /* eliminated now */
        tick_size = 1;
    // http://www.czce.com.cn/cn/rootfiles/2012/07/11/1340962525895641-1340962526154737.pdf
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
    else if (instrument_id_alp.compare("ME") == 0) /* eliminated now */
        tick_size = 1;
    // http://www.czce.com.cn/cn/rootfiles/2014/06/13/1402482218812025-1402482218815763.pdf
    else if (instrument_id_alp.compare("MA") == 0)
        tick_size = 1;
    else if (instrument_id_alp.compare("FG") == 0)
        tick_size = 1;
    else if (instrument_id_alp.compare("TC") == 0) /* eliminated now */
        tick_size = 0.2;
    // http://www.czce.com.cn/cn/rootfiles/2015/05/08/1425547808690959-1425547808761440.pdf
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
    else if (instrument_id_alp.compare("CJ") == 0)
        tick_size = 5;
    else if (instrument_id_alp.compare("UR") == 0)
        tick_size = 1;
    else if (instrument_id_alp.compare("SA") == 0)
        tick_size = 1;
    else if (instrument_id_alp.compare("PF") == 0)
        tick_size = 2;
    else if (instrument_id_alp.compare("PK") == 0)
        tick_size = 2;
    /* CFFEX */
    else if (instrument_id_alp.compare("IF") == 0)
        tick_size = 0.2;
    else if (instrument_id_alp.compare("IH") == 0)
        tick_size = 0.2;
    else if (instrument_id_alp.compare("IC") == 0)
        tick_size = 0.2;
    else if (instrument_id_alp.compare("IM") == 0)
        tick_size = 0.2;
    else if (instrument_id_alp.compare("TF") == 0)
    {
        if (trading_day != "NULL" && trading_day < "20150317")
            tick_size = 0.002;
        else
            tick_size = 0.005;
    }
    else if (instrument_id_alp.compare("T") == 0)
        tick_size = 0.005;
    else if (instrument_id_alp.compare("TS") == 0)
        tick_size = 0.005;
    else if (instrument_id_alp.compare("TL") == 0)
        tick_size = 0.01;
    /* GFEX */
    else if (instrument_id_alp.compare("si") == 0)
        tick_size = 5;
    else if (instrument_id_alp.compare("lc") == 0)
        tick_size = 50;
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
    else if (instrument_id_alp.compare("zn") == 0) // https://www.shfe.com.cn/news/notice/72228525.html
        contract_size = 5;
    else if (instrument_id_alp.compare("pb") == 0)
    {
        // http://www.shfe.com.cn/news/notice/3782977.html
        if (trading_day != "NULL" && trading_day < "20130902")
            contract_size = 25;
        else
            contract_size = 5;
    }
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
        // http://www.shfe.com.cn/news/notice/10141355.html
        // http://www.shfe.com.cn/news/notice/911330668.html
        std::string instrument_id_mon = get_instrument_id_mon(instrument_id);
        if (trading_day != "NULL" && trading_day < "20180716" && (trading_day >= "20120201" || (trading_day >= "20110117" && instrument_id_mon >= "1202")))
            contract_size = 50;
        else
            contract_size = 10;
    }
    else if (instrument_id_alp.compare("bu") == 0)
        contract_size = 10;
    else if (instrument_id_alp.compare("ru") == 0)
    {
        //  http://www.shfe.com.cn/news/notice/16268174.html
        std::string instrument_id_mon = get_instrument_id_mon(instrument_id);
        if (trading_day != "NULL" && (trading_day < "20110726" || (trading_day < "20120801" && instrument_id_mon < "1208")))
            contract_size = 5;
        else
            contract_size = 10;
    }
    else if (instrument_id_alp.compare("sp") == 0)
        contract_size = 10;
    else if (instrument_id_alp.compare("ss") == 0)
        contract_size = 5;
    else if (instrument_id_alp.compare("ao") == 0)
        contract_size = 20;
    else if (instrument_id_alp.compare("br") == 0)
        contract_size = 5;
    /* INE */
    else if (instrument_id_alp.compare("sc") == 0)
        contract_size = 1000;
    else if (instrument_id_alp.compare("nr") == 0)
        contract_size = 10;
    else if (instrument_id_alp.compare("lu") == 0)
        contract_size = 10;
    else if (instrument_id_alp.compare("bc") == 0)
        contract_size = 5;
    else if (instrument_id_alp.compare("ec") == 0)
        contract_size = 50;
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
    {
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6191275/index.html
        if (trading_day != "NULL" && trading_day < "20191015")
            contract_size = 500;
        else
            contract_size = 10;
    }
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
    else if (instrument_id_alp.compare("eg") == 0)
        contract_size = 10;
    else if (instrument_id_alp.compare("rr") == 0)
        contract_size = 10;
    else if (instrument_id_alp.compare("eb") == 0)
        contract_size = 5;
    else if (instrument_id_alp.compare("pg") == 0)
        contract_size = 20;
    else if (instrument_id_alp.compare("lh") == 0)
        contract_size = 16;
    /* CZCE */
    else if (instrument_id_alp.compare("WS") == 0) /* eliminated now */
        contract_size = 10;
    // http://www.czce.com.cn/cn/sspz/pm/pzjs/qh/webinfo/2012/01/1325851217868694.htm
    else if (instrument_id_alp.compare("QM") == 0) /* eliminated now */
        contract_size = 50;
    // http://www.czce.com.cn/cn/rootfiles/2012/07/11/1340962525895641-1340962526154737.pdf
    else if (instrument_id_alp.compare("WH") == 0)
        contract_size = 20;
    else if (instrument_id_alp.compare("WT") == 0) /* eliminated now */
        contract_size = 10;
    // http://www.czce.com.cn/cn/sspz/pm/pzjs/qh/webinfo/2012/01/1325851217868694.htm
    else if (instrument_id_alp.compare("PM") == 0)
        contract_size = 50;
    else if (instrument_id_alp.compare("CF") == 0)
        contract_size = 5;
    else if (instrument_id_alp.compare("SR") == 0)
        contract_size = 10;
    else if (instrument_id_alp.compare("RO") == 0) /* eliminated now */
        contract_size = 5;
    // http://www.czce.com.cn/cn/rootfiles/2012/07/11/1340962525895641-1340962526154737.pdf
    else if (instrument_id_alp.compare("OI") == 0)
        contract_size = 10;
    else if (instrument_id_alp.compare("ER") == 0) /* eliminated now */
        contract_size = 10;
    // http://www.czce.com.cn/cn/rootfiles/2012/07/11/1340962525895641-1340962526154737.pdf
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
    else if (instrument_id_alp.compare("ME") == 0) /* eliminated now */
        contract_size = 50;
    // http://www.czce.com.cn/cn/rootfiles/2014/06/13/1402482218812025-1402482218815763.pdf
    else if (instrument_id_alp.compare("MA") == 0)
        contract_size = 10;
    else if (instrument_id_alp.compare("FG") == 0)
        contract_size = 20;
    else if (instrument_id_alp.compare("TC") == 0) /* eliminated now */
        contract_size = 200;
    // http://www.czce.com.cn/cn/rootfiles/2015/05/08/1425547808690959-1425547808761440.pdf
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
    else if (instrument_id_alp.compare("CJ") == 0)
        contract_size = 5;
    else if (instrument_id_alp.compare("UR") == 0)
        contract_size = 20;
    else if (instrument_id_alp.compare("SA") == 0)
        contract_size = 20;
    else if (instrument_id_alp.compare("PF") == 0)
        contract_size = 5;
    else if (instrument_id_alp.compare("PK") == 0)
        contract_size = 5;
    /* CFFEX */
    else if (instrument_id_alp.compare("IF") == 0)
        contract_size = 300;
    else if (instrument_id_alp.compare("IH") == 0)
        contract_size = 300;
    else if (instrument_id_alp.compare("IC") == 0)
        contract_size = 200;
    else if (instrument_id_alp.compare("IM") == 0)
        contract_size = 200;
    else if (instrument_id_alp.compare("TF") == 0)
        contract_size = 10000;
    else if (instrument_id_alp.compare("T") == 0)
        contract_size = 10000;
    else if (instrument_id_alp.compare("TS") == 0)
        contract_size = 20000;
    else if (instrument_id_alp.compare("TL") == 0)
        contract_size = 10000;
    /* GFEX */
    else if (instrument_id_alp.compare("si") == 0)
        contract_size = 5;
    else if (instrument_id_alp.compare("lc") == 0)
        contract_size = 1;
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
    else if (instrument_id_alp.compare("sp") == 0)
        exchange = EXCHANGE_SHFE;
    else if (instrument_id_alp.compare("ss") == 0)
        exchange = EXCHANGE_SHFE;
    else if (instrument_id_alp.compare("ao") == 0)
        exchange = EXCHANGE_SHFE;
    else if (instrument_id_alp.compare("br") == 0)
        exchange = EXCHANGE_SHFE;
    else if (instrument_id_alp.compare("sc") == 0)
        exchange = EXCHANGE_INE;
    else if (instrument_id_alp.compare("nr") == 0)
        exchange = EXCHANGE_INE;
    else if (instrument_id_alp.compare("lu") == 0)
        exchange = EXCHANGE_INE;
    else if (instrument_id_alp.compare("bc") == 0)
        exchange = EXCHANGE_INE;
    else if (instrument_id_alp.compare("ec") == 0)
        exchange = EXCHANGE_INE;
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
    else if (instrument_id_alp.compare("eg") == 0)
        exchange = EXCHANGE_DCE;
    else if (instrument_id_alp.compare("rr") == 0)
        exchange = EXCHANGE_DCE;
    else if (instrument_id_alp.compare("eb") == 0)
        exchange = EXCHANGE_DCE;
    else if (instrument_id_alp.compare("pg") == 0)
        exchange = EXCHANGE_DCE;
    else if (instrument_id_alp.compare("lh") == 0)
        exchange = EXCHANGE_DCE;
    else if (instrument_id_alp.compare("WS") == 0) /* eliminated now */
        exchange = EXCHANGE_CZCE;
    else if (instrument_id_alp.compare("QM") == 0) /* eliminated now */
        exchange = EXCHANGE_CZCE;
    else if (instrument_id_alp.compare("WH") == 0)
        exchange = EXCHANGE_CZCE;
    else if (instrument_id_alp.compare("WT") == 0) /* eliminated now */
        exchange = EXCHANGE_CZCE;
    else if (instrument_id_alp.compare("PM") == 0)
        exchange = EXCHANGE_CZCE;
    else if (instrument_id_alp.compare("CF") == 0)
        exchange = EXCHANGE_CZCE;
    else if (instrument_id_alp.compare("SR") == 0)
        exchange = EXCHANGE_CZCE;
    else if (instrument_id_alp.compare("RO") == 0) /* eliminated now */
        exchange = EXCHANGE_CZCE;
    else if (instrument_id_alp.compare("OI") == 0)
        exchange = EXCHANGE_CZCE;
    else if (instrument_id_alp.compare("ER") == 0) /* eliminated now */
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
    else if (instrument_id_alp.compare("ME") == 0) /* eliminated now */
        exchange = EXCHANGE_CZCE;
    else if (instrument_id_alp.compare("MA") == 0)
        exchange = EXCHANGE_CZCE;
    else if (instrument_id_alp.compare("FG") == 0)
        exchange = EXCHANGE_CZCE;
    else if (instrument_id_alp.compare("TC") == 0) /* eliminated now */
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
    else if (instrument_id_alp.compare("CJ") == 0)
        exchange = EXCHANGE_CZCE;
    else if (instrument_id_alp.compare("UR") == 0)
        exchange = EXCHANGE_CZCE;
    else if (instrument_id_alp.compare("SA") == 0)
        exchange = EXCHANGE_CZCE;
    else if (instrument_id_alp.compare("PF") == 0)
        exchange = EXCHANGE_CZCE;
    else if (instrument_id_alp.compare("PK") == 0)
        exchange = EXCHANGE_CZCE;
    else if (instrument_id_alp.compare("IF") == 0)
        exchange = EXCHANGE_CFFEX;
    else if (instrument_id_alp.compare("IH") == 0)
        exchange = EXCHANGE_CFFEX;
    else if (instrument_id_alp.compare("IC") == 0)
        exchange = EXCHANGE_CFFEX;
    else if (instrument_id_alp.compare("IM") == 0)
        exchange = EXCHANGE_CFFEX;
    else if (instrument_id_alp.compare("TF") == 0)
        exchange = EXCHANGE_CFFEX;
    else if (instrument_id_alp.compare("T") == 0)
        exchange = EXCHANGE_CFFEX;
    else if (instrument_id_alp.compare("TS") == 0)
        exchange = EXCHANGE_CFFEX;
    else if (instrument_id_alp.compare("TL") == 0)
        exchange = EXCHANGE_CFFEX;
    else if (instrument_id_alp.compare("si") == 0)
        exchange = EXCHANGE_GFEX;
    else if (instrument_id_alp.compare("lc") == 0)
        exchange = EXCHANGE_GFEX;
    return exchange;
}

inline std::string get_market(const std::string& instrument_id)
{
    std::string market;
    std::string instrument_id_alp = get_instrument_id_alp(instrument_id);
    std::string exchange = get_exchange(instrument_id);
    if (exchange.compare(EXCHANGE_SSE) == 0 || exchange.compare(EXCHANGE_SZE) == 0)
        market = MARKET_CHINA_STOCK;
    else if (exchange.compare(EXCHANGE_SHFE) == 0 || exchange.compare(EXCHANGE_INE) == 0 || exchange.compare(EXCHANGE_DCE) == 0 || exchange.compare(EXCHANGE_CZCE) == 0 || exchange.compare(EXCHANGE_GFEX) == 0)
        market = MARKET_CHINA_FUTURE_COMMODITY;
    else if (exchange.compare(EXCHANGE_CFFEX) == 0 && (instrument_id_alp.compare("IF") == 0 || instrument_id_alp.compare("IH") == 0 || instrument_id_alp.compare("IC") == 0 || instrument_id_alp.compare("IM") == 0))
        market = MARKET_CHINA_FUTURE_INDEX;
    else if (exchange.compare(EXCHANGE_CFFEX) == 0 && (instrument_id_alp.compare("TF") == 0 || instrument_id_alp.compare("T") == 0 || instrument_id_alp.compare("TS") == 0 || instrument_id_alp.compare("TL") == 0))
        market = MARKET_CHINA_FUTURE_TREASURY;
    return market;
}

#endif
