/*
Created on Sep 2018

@author: hufx

Transaction Cost
*/
#ifndef TRANSACTION_COST_H
#define TRANSACTION_COST_H

#include "Quotes.h"
#include "Constants.h"
#include <iostream>

#define BROKER_FEE_MULTIPLIER   1.0

inline std::pair<double, bool> get_open_fee(const std::string& trading_day, const std::string& instrument_id)
{
    double fee;
    bool using_rate;
    std::string instrument_id_alp = get_instrument_id_alp(instrument_id);
    if (trading_day.substr(0, 4) == "2018")
    {
        /* SHFE */
        if (instrument_id_alp == "cu")
        {
            fee = 0.050 / 1000;
            using_rate = true;
        }
        else if (instrument_id_alp == "al")
        {
            fee = 3;
            using_rate = false;
        }
        else if (instrument_id_alp == "zn")
        {
            fee = 3;
            using_rate = false;
        }
        else if (instrument_id_alp == "pb")
        {
            fee = 0.040 / 1000;
            using_rate = true;
        }
        else if (instrument_id_alp == "ni")
        {
            // http://www.shfe.com.cn/news/notice/911328390.html
            if (instrument_id[instrument_id.size() - 2] == '0' && (instrument_id[instrument_id.size() - 1] == '1' || instrument_id[instrument_id.size() - 1] == '5' || instrument_id[instrument_id.size() - 1] == '9'))
                fee = 6;
            else
                fee = 1;
            using_rate = false;
        }
        else if (instrument_id_alp == "sn")
        {
            // http://www.shfe.com.cn/news/notice/911328390.html
            if (instrument_id[instrument_id.size() - 2] == '0' && (instrument_id[instrument_id.size() - 1] == '1' || instrument_id[instrument_id.size() - 1] == '5' || instrument_id[instrument_id.size() - 1] == '9'))
                fee = 3;
            else
                fee = 1;
            using_rate = false;
        }
        else if (instrument_id_alp == "au")
        {
            fee = 10;
            using_rate = false;
        }
        else if (instrument_id_alp == "ag")
        {
            fee = 0.050 / 1000;
            using_rate = true;
        }
        else if (instrument_id_alp == "rb")
        {
            fee = 0.100 / 1000;
            using_rate = true;
        }
        else if (instrument_id_alp == "wr")
        {
            fee = 0.040 / 1000;
            using_rate = true;
        }
        else if (instrument_id_alp == "hc")
        {
            fee = 0.100 / 1000;
            using_rate = true;
        }
        else if (instrument_id_alp == "fu")
        {
            fee = 2.000 / 1000;
            using_rate = true;
        }
        else if (instrument_id_alp == "bu")
        {
            fee = 0.100 / 1000;
            using_rate = true;
        }
        else if (instrument_id_alp == "ru")
        {
            fee = 0.045 / 1000;
            using_rate = true;
        }
        /* INE */
        else if (instrument_id_alp == "sc")
        {
            fee = 20;
            using_rate = false;
        }
        /* DCE */
        else if (instrument_id_alp == "a")
        {
            fee = 2;
            using_rate = false;
        }
        else if (instrument_id_alp == "b")
        {
            if (instrument_id == "b1801" || instrument_id == "b1803")
                fee = 2;
            else
                fee = 1;
            using_rate = false;
        }
        else if (instrument_id_alp == "bb")
        {
            fee = 0.050 / 1000;
            using_rate = true;
        }
        else if (instrument_id_alp == "c")
        {
            if (instrument_id[instrument_id.size() - 2] == '0' && (instrument_id[instrument_id.size() - 1] == '1' || instrument_id[instrument_id.size() - 1] == '5' || instrument_id[instrument_id.size() - 1] == '9'))
                fee = 0.6;
            else
                fee = 0.1;
            using_rate = false;
        }
        else if (instrument_id_alp == "cs")
        {
            fee = 1.5;
            using_rate = false;
        }
        else if (instrument_id_alp == "fb")
        {
            fee = 0.050 / 1000;
            using_rate = true;
        }
        else if (instrument_id_alp == "i")
        {
            if (instrument_id[instrument_id.size() - 2] == '0' && (instrument_id[instrument_id.size() - 1] == '1' || instrument_id[instrument_id.size() - 1] == '5' || instrument_id[instrument_id.size() - 1] == '9'))
                fee = 0.120 / 1000;
            else
                fee = 0.006 / 1000;
            using_rate = true;
        }
        else if (instrument_id_alp == "j")
        {
            if (instrument_id[instrument_id.size() - 2] == '0' && (instrument_id[instrument_id.size() - 1] == '1' || instrument_id[instrument_id.size() - 1] == '5' || instrument_id[instrument_id.size() - 1] == '9'))
                fee = 0.180 / 1000;
            else
                fee = 0.060 / 1000;
            // http://www.dce.com.cn/dalianshangpin/yw/fw/jystz/ywtz/6080548/index.html
            if (instrument_id == "j1805")
                fee = 0.300 / 1000;
            using_rate = true;
        }
        else if (instrument_id_alp == "jd")
        {
            fee = 0.150 / 1000;
            using_rate = true;
        }
        else if (instrument_id_alp == "jm")
        {
            if (instrument_id[instrument_id.size() - 2] == '0' && (instrument_id[instrument_id.size() - 1] == '1' || instrument_id[instrument_id.size() - 1] == '5' || instrument_id[instrument_id.size() - 1] == '9'))
                fee = 0.180 / 1000;
            else
                fee = 0.060 / 1000;
            // http://www.dce.com.cn/dalianshangpin/yw/fw/jystz/ywtz/6080548/index.html
            if (instrument_id == "jm1805")
                fee = 0.300 / 1000;
            using_rate = true;
        }
        else if (instrument_id_alp == "l")
        {
            fee = 2;
            using_rate = false;
        }
        else if (instrument_id_alp == "m")
        {
            if (instrument_id[instrument_id.size() - 2] == '0' && (instrument_id[instrument_id.size() - 1] == '1' || instrument_id[instrument_id.size() - 1] == '5' || instrument_id[instrument_id.size() - 1] == '9'))
                fee = 1.5;
            else
                fee = 0.2;
            using_rate = false;
        }
        else if (instrument_id_alp == "p")
        {
            fee = 2.5;
            using_rate = false;
        }
        else if (instrument_id_alp == "pp")
        {
            fee = 0.060 / 1000;
            using_rate = true;
        }
        else if (instrument_id_alp == "v")
        {
            fee = 1;
            using_rate = false;
        }
        else if (instrument_id_alp == "y")
        {
            fee = 2.5;
            using_rate = false;
        }
        /* CZCE */
        else if (instrument_id_alp == "AP")
        {
            fee = 0.5;
            using_rate = false;
        }
        else if (instrument_id_alp == "CF")
        {
            fee = 4.3;
            using_rate = false;
        }
        else if (instrument_id_alp == "CY")
        {
            fee = 4;
            using_rate = false;
        }
        else if (instrument_id_alp == "FG")
        {
            fee = 3;
            using_rate = false;
        }
        else if (instrument_id_alp == "JR")
        {
            fee = 3;
            using_rate = false;
        }
        else if (instrument_id_alp == "LR")
        {
            fee = 3;
            using_rate = false;
        }
        else if (instrument_id_alp == "MA")
        {
            fee = 2;
            using_rate = false;
        }
        else if (instrument_id_alp == "OI")
        {
            fee = 2.5;
            using_rate = false;
        }
        else if (instrument_id_alp == "PM")
        {
            fee = 5;
            using_rate = false;
        }
        else if (instrument_id_alp == "RI")
        {
            fee = 2.5;
            using_rate = false;
        }
        else if (instrument_id_alp == "RM")
        {
            fee = 1.5;
            using_rate = false;
        }
        else if (instrument_id_alp == "RS")
        {
            fee = 2;
            using_rate = false;
        }
        else if (instrument_id_alp == "SF")
        {
            fee = 3;
            using_rate = false;
        }
        else if (instrument_id_alp == "SM")
        {
            fee = 3;
            using_rate = false;
        }
        else if (instrument_id_alp == "SR")
        {
            fee = 3;
            using_rate = false;
        }
        else if (instrument_id_alp == "TA")
        {
            fee = 3;
            using_rate = false;
        }
        else if (instrument_id_alp == "WH")
        {
            fee = 2.5;
            using_rate = false;
        }
        else if (instrument_id_alp == "ZC")
        {
            fee = 4;
            using_rate = false;
        }
        /* CFFEX */
        else if (instrument_id_alp == "IC")
        {
            fee = 0.023 / 1000;
            using_rate = true;
        }
        else if (instrument_id_alp == "IF")
        {
            fee = 0.023 / 1000;
            using_rate = true;
        }
        else if (instrument_id_alp == "IH")
        {
            fee = 0.023 / 1000;
            using_rate = true;
        }
        else if (instrument_id_alp == "T")
        {
            fee = 3;
            using_rate = false;
        }
        else if (instrument_id_alp == "TF")
        {
            fee = 3;
            using_rate = false;
        }
        else if (instrument_id_alp == "TS")
        {
            fee = 3;
            using_rate = false;
        }
        
        // http://www.shfe.com.cn/news/notice/911330158.html
        if (trading_day >= "20180420" && instrument_id == "ni1807")
            fee = 6;
        // http://www.shfe.com.cn/news/notice/911330669.html
        if (trading_day >= "20180716" && instrument_id_alp == "fu")
            fee = 0.050 / 1000;
        // http://www.shfe.com.cn/news/notice/911330961.html
        if (trading_day >= "20180803" && instrument_id == "ni1811")
            fee = 6;
        
        // http://www.ine.cn/news/notice/578.html
        if (trading_day >= "20180705" && trading_day < "20180901" && instrument_id == "sc1810")
            fee = 5;
        if (trading_day >= "20180705" && trading_day < "20181001" && instrument_id == "sc1811")
            fee = 10;
        // http://www.ine.cn/news/notice/845.html
        if (trading_day >= "20180803" && trading_day < "20181201" && instrument_id == "sc1901")
            fee = 5;
        if (trading_day >= "20180803" && trading_day < "20190101" && instrument_id == "sc1902")
            fee = 5;
        
        // http://www.dce.com.cn/dalianshangpin/yw/fw/jystz/ywtz/6117522/index.html
        if (trading_day >= "20180822")
        {
            if (instrument_id_alp == "p" || instrument_id == "y")
                fee = 1.25;
            if (instrument_id_alp == "cs")
                fee = 0.75;
            if (instrument_id_alp == "l")
                fee = 1;
            if (instrument_id_alp == "pp")
                fee = 0.030 / 1000;
            if (instrument_id_alp == "i" && instrument_id[instrument_id.size() - 2] == '0' && (instrument_id[instrument_id.size() - 1] == '1' || instrument_id[instrument_id.size() - 1] == '5' || instrument_id[instrument_id.size() - 1] == '9'))
                fee = 0.060 / 1000;
            if (instrument_id_alp == "m")
            {
                if (instrument_id[instrument_id.size() - 2] == '0' && (instrument_id[instrument_id.size() - 1] == '1' || instrument_id[instrument_id.size() - 1] == '5' || instrument_id[instrument_id.size() - 1] == '9'))
                    fee = 0.75;
                else
                    fee = 0.1;
            }
        }

        // http://www.czce.com.cn/cn/rootfiles/2018/05/07/1526089634085979-1526089634138361.pdf
        if (trading_day > "20180102" && instrument_id_alp == "OI")
            fee = 2;
        // http://www.czce.com.cn/cn/rootfiles/2018/05/07/1526089634797462-1526089634846913.pdf
        if (trading_day > "20180122" && (instrument_id_alp == "TA" || instrument_id_alp == "ZC" || instrument_id_alp == "MA") && ((instrument_id[instrument_id.size() - 2] == '0' && (instrument_id[instrument_id.size() - 1] == '3' || instrument_id[instrument_id.size() - 1] == '7')) || (instrument_id[instrument_id.size() - 2] == '1' && instrument_id[instrument_id.size() - 1] == '1')))
            fee = 0.5;
        // http://www.czce.com.cn/cn/rootfiles/2018/06/13/1527574139659870-1527574139676711.pdf
        if (trading_day >= "20180614" && instrument_id_alp == "AP")
            fee = 10;
        // http://www.czce.com.cn/cn/rootfiles/2018/06/20/1527574746050105-1527574746063024.pdf
        if (trading_day >= "20180621" && instrument_id_alp == "AP")
            fee = 20;
        // http://www.czce.com.cn/cn/rootfiles/2018/08/06/1533010573842086-1533010573859399.pdf
        if (trading_day > "20180807" && (instrument_id == "MA809" || instrument_id == "TA809"))
            fee = 6;
        // http://www.czce.com.cn/cn/rootfiles/2018/08/16/1533011447479860-1533011447613907.pdf
        if (trading_day > "20180817" && (instrument_id == "TA811" || instrument_id == "TA901"))
            fee = 6;
    }
    else
        std::cout << parse_milliseconds(0) << " ERROR TdEngine %% - [transaction_cost] open fees haven't been defined on " << trading_day << std::endl;
    return std::make_pair(fee, using_rate);
}

inline double get_close_mpl(const std::string& trading_day, const std::string& instrument_id)
{
    double mpl;
    std::string instrument_id_alp = get_instrument_id_alp(instrument_id);
    if (trading_day.substr(0, 4) == "2018")
    {
        /* SHFE */
        if (instrument_id_alp == "cu")
            mpl = 0;
        else if (instrument_id_alp == "al")
            mpl = 0;
        else if (instrument_id_alp == "zn")
            mpl = 0;
        else if (instrument_id_alp == "pb")
            mpl = 0;
        else if (instrument_id_alp == "ni")
        {
            // http://www.shfe.com.cn/news/notice/911328390.html
            if (instrument_id[instrument_id.size() - 2] == '0' && (instrument_id[instrument_id.size() - 1] == '1' || instrument_id[instrument_id.size() - 1] == '5' || instrument_id[instrument_id.size() - 1] == '9'))
                mpl = 1;
            else
                mpl = 0;
            // http://www.shfe.com.cn/news/notice/911328534.html
            if (instrument_id == "ni1801")
                mpl = 5;
        }
        else if (instrument_id_alp == "sn")
            mpl = 0;
        else if (instrument_id_alp == "au")
            mpl = 0;
        else if (instrument_id_alp == "ag")
            mpl = 1;
        else if (instrument_id_alp == "rb")
        {
            if (instrument_id == "rb1801")
                mpl = 5;
            else
                mpl = 1;
        }
        else if (instrument_id_alp == "wr")
            mpl = 1;
        else if (instrument_id_alp == "hc")
        {
            if (instrument_id == "hc1801")
                mpl = 5;
            else
                mpl = 1;
        }
        else if (instrument_id_alp == "fu")
            mpl = 1;
        else if (instrument_id_alp == "bu")
            mpl = 1;
        else if (instrument_id_alp == "ru")
            mpl = 1;
        /* INE */
        else if (instrument_id_alp == "sc")
            mpl = 0;
        /* DCE */
        else if (instrument_id_alp == "a")
            mpl = 1;
        else if (instrument_id_alp == "b")
            mpl = 1;
        else if (instrument_id_alp == "bb")
            mpl = 1;
        else if (instrument_id_alp == "c")
            mpl = 1;
        else if (instrument_id_alp == "cs")
            mpl = 1;
        else if (instrument_id_alp == "fb")
            mpl = 1;
        else if (instrument_id_alp == "i")
            mpl = 1;
        else if (instrument_id_alp == "j")
            mpl = 1;
        else if (instrument_id_alp == "jd")
            mpl = 1;
        else if (instrument_id_alp == "jm")
            mpl = 1;
        else if (instrument_id_alp == "l")
            mpl = 1;
        else if (instrument_id_alp == "m")
            mpl = 1;
        else if (instrument_id_alp == "p")
            mpl = 1;
        else if (instrument_id_alp == "pp")
            mpl = 1;
        else if (instrument_id_alp == "v")
            mpl = 1;
        else if (instrument_id_alp == "y")
            mpl = 1;
        /* CZCE */
        else if (instrument_id_alp == "AP")
            mpl = 0;
        else if (instrument_id_alp == "CF")
            mpl = 0;
        else if (instrument_id_alp == "CY")
            mpl = 0;
        else if (instrument_id_alp == "FG")
            mpl = 8;
        else if (instrument_id_alp == "JR")
            mpl = 1;
        else if (instrument_id_alp == "LR")
            mpl = 1;
        else if (instrument_id_alp == "MA")
            mpl = 3;
        else if (instrument_id_alp == "OI")
            mpl = 0;
        else if (instrument_id_alp == "PM")
            mpl = 1;
        else if (instrument_id_alp == "RI")
            mpl = 1;
        else if (instrument_id_alp == "RM")
            mpl = 0;
        else if (instrument_id_alp == "RS")
            mpl = 1;
        else if (instrument_id_alp == "SF")
            mpl = 3;
        else if (instrument_id_alp == "SM")
            mpl = 2;
        else if (instrument_id_alp == "SR")
            mpl = 0;
        else if (instrument_id_alp == "TA")
            mpl = 0;
        else if (instrument_id_alp == "WH")
            mpl = 0;
        else if (instrument_id_alp == "ZC")
            mpl = 2;
        /* CFFEX */
        else if (instrument_id_alp == "IC")
            mpl = 30;
        else if (instrument_id_alp == "IF")
            mpl = 30;
        else if (instrument_id_alp == "IH")
            mpl = 30;
        else if (instrument_id_alp == "T")
            mpl = 0;
        else if (instrument_id_alp == "TF")
            mpl = 1;
        else if (instrument_id_alp == "TS")
            mpl = 0;
        
        // http://www.shfe.com.cn/news/notice/911329729.html
        if (trading_day >= "20180212" && instrument_id == "ni1805")
            mpl = 5;
        // http://www.shfe.com.cn/news/notice/911330158.html
        if (trading_day >= "20180420" && (instrument_id == "ni1805" || instrument_id == "ni1807"))
            mpl = 1;
        // http://www.shfe.com.cn/news/notice/911330669.html
        if (trading_day >= "20180716" && instrument_id_alp == "fu")
            mpl = 0;
        // http://www.shfe.com.cn/news/notice/911330875.html
        if (trading_day >= "20180724" && instrument_id == "zn1809")
        {
            mpl = 5;
            if (trading_day >= "20180816")
                mpl = 1;
        }
        // http://www.shfe.com.cn/news/notice/911330961.html
        if (trading_day >= "20180803" && instrument_id == "ni1811")
            mpl = 1;
        // http://www.shfe.com.cn/news/notice/911331232.html
        if (trading_day >= "20181016" && instrument_id_alp == "wr")
            mpl = 0;
        
        // http://www.czce.com.cn/cn/rootfiles/2018/05/07/1526089634666124-1526089634720927.pdf
        if (trading_day > "20180112" && instrument_id_alp == "ZC")
            mpl = 1;
        // http://www.czce.com.cn/cn/rootfiles/2018/05/07/1526089634797462-1526089634846913.pdf
        if (trading_day > "20180122" && (instrument_id_alp == "TA" || instrument_id_alp == "ZC" || instrument_id_alp == "MA") && ((instrument_id[instrument_id.size() - 2] == '0' && (instrument_id[instrument_id.size() - 1] == '3' || instrument_id[instrument_id.size() - 1] == '7')) || (instrument_id[instrument_id.size() - 2] == '1' && instrument_id[instrument_id.size() - 1] == '1')))
            mpl = 1;
        // http://www.czce.com.cn/cn/rootfiles/2018/03/12/1517180623673436-1517180623691194.pdf
        if (trading_day >= "20180315" && instrument_id_alp == "AP")
            mpl = 2;
        // http://www.czce.com.cn/cn/rootfiles/2018/05/16/1527571716248278-1527571716267681.pdf
        if (trading_day >= "20180517" && (instrument_id == "AP807" || instrument_id == "AP810" || instrument_id == "AP811" || instrument_id == "AP812" || instrument_id == "AP901" || instrument_id == "AP903" || instrument_id == "AP905"))
            mpl = 6;
        // http://www.czce.com.cn/cn/rootfiles/2018/05/19/1527571955091368-1527571955108631.pdf
        if (trading_day >= "20180522" && (instrument_id == "AP807" || instrument_id == "AP810" || instrument_id == "AP811" || instrument_id == "AP812" || instrument_id == "AP901" || instrument_id == "AP903" || instrument_id == "AP905"))
            mpl = 40;
        // http://www.czce.com.cn/cn/rootfiles/2018/05/24/1527572423628969-1527572423645598.pdf
        if (trading_day > "20180525" && (instrument_id == "CF809" || instrument_id == "CF901"))
            mpl = 1;
        // http://www.czce.com.cn/cn/rootfiles/2018/06/07/1527573618945332-1527573618964465.pdf
        if (trading_day > "20180611" && (instrument_id == "CF809" || instrument_id == "CF901"))
            mpl = 10 / 4.3;
        // http://www.czce.com.cn/cn/rootfiles/2018/06/13/1527574139659870-1527574139676711.pdf
        if (trading_day >= "20180614" && instrument_id_alp == "AP")
            mpl = 2;
        // http://www.czce.com.cn/cn/rootfiles/2018/06/20/1527574746050105-1527574746063024.pdf
        if (trading_day >= "20180621" && instrument_id_alp == "AP")
            mpl = 1;
        // http://www.czce.com.cn/cn/rootfiles/2018/06/22/1531035551736278-1531035551769551.pdf
        if (trading_day > "20180625" && instrument_id_alp == "FG")
            mpl = 2;
        // http://www.czce.com.cn/cn/rootfiles/2018/08/06/1533010573842086-1533010573859399.pdf
        if (trading_day > "20180807" && (instrument_id == "MA809" || instrument_id == "TA809"))
            mpl = 1;
        // http://www.czce.com.cn/cn/rootfiles/2018/08/16/1533011447479860-1533011447613907.pdf
        if (trading_day > "20180817" && (instrument_id == "TA811" || instrument_id == "TA901"))
            mpl = 1;
        // http://www.czce.com.cn/cn/rootfiles/2018/08/22/1533011950316693-1533011950331077.pdf
        if (trading_day > "20180823" && (instrument_id == "TA811" || instrument_id == "TA901"))
            mpl = 2;
        
        // http://www.cffex.com.cn/jysgg/20180202/21451.html
        if (trading_day >= "20180205" && instrument_id_alp == "TF")
            mpl = 0;
    }
    else
        std::cout << parse_milliseconds(0) << " ERROR TdEngine %% - [transaction_cost] close fees haven't been defined on " << trading_day << std::endl;
    return mpl;
}

inline double get_transaction_cost(const std::string& trading_day, const std::string& instrument_id, int volume, double amout, char offset)
{
    double fee = 0.0;
    auto res = get_open_fee(trading_day, instrument_id);
    if (res.second)
        fee = res.first * amout * get_contract_size(instrument_id, trading_day);
    else
        fee = res.first * volume;
    if (offset == LF_CHAR_CloseToday)
        fee = fee * get_close_mpl(trading_day, instrument_id);
    return fee * BROKER_FEE_MULTIPLIER;
}

#endif