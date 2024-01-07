/*
Created on Sep 2018

@author: hufx

Transaction Cost
*/
#ifndef TRANSACTION_COST_H
#define TRANSACTION_COST_H

#include "Quotes.h"
#include "Constants.h"
#include "Calendars.h"
#include <iostream>

#define BROKER_FEE_MULTIPLIER   1.0

inline std::pair<double, bool> get_open_fee(const std::string& trading_day, const std::string& instrument_id)
{
    double fee;
    bool using_rate;
    std::string instrument_id_alp = get_instrument_id_alp(instrument_id);
    std::string instrument_id_mon = get_instrument_id_mon(instrument_id);
    /* SHFE */
    if (instrument_id_alp == "cu")
    {
        // since 199303
        // https://www.shfe.com.cn/news/notice/3084655.html since 20020401
        fee = 0.200 / 1000;
        // http://www.shfe.com.cn/news/notice/10252865.html 暂停执行所有品种6个月后期货合约手续费减半收取规定
        if (trading_day < "20101129" && trading_day < shift_trading_day_forward(shift_contract_month_backward(instrument_id_mon, 6, 15), 2, true))
            fee /= 2;
        // http://www.shfe.com.cn/news/notice/16264564.html
        if (trading_day >= "20110801")
            fee = 0.100 / 1000;
        // http://www.shfe.com.cn/news/notice/2327936.html
        if (trading_day >= "20120601")
            fee = 0.080 / 1000;
        // http://www.shfe.com.cn/news/notice/2726254.html
        if (trading_day >= "20120901")
            fee = 0.050 / 1000;
        // http://www.shfe.com.cn/news/notice/911321598.html
        if (trading_day >= "20141126" && trading_day <= "20150331")
            fee /= 2;
        // http://www.shfe.com.cn/news/notice/911322360.html
        if (trading_day >= "20150401" && trading_day <= "20150930")
            fee /= 2;
        using_rate = true;
    }
    else if (instrument_id_alp == "al")
    {
        // since 199311
        // https://www.shfe.com.cn/news/notice/3084655.html since 20020401
        fee = 0.200 / 1000;
        using_rate = true;
        // https://www.shfe.com.cn/news/notice/37263835.html
        // https://www.shfe.com.cn/news/notice/4535003.html
        if (trading_day >= "20030901")
        {
            fee = 2;
            using_rate = false;
        }
        // http://www.shfe.com.cn/news/notice/82285182.html
        if (trading_day >= "20080401")
            fee = 5;
        // http://www.shfe.com.cn/news/notice/10252865.html 暂停执行所有品种6个月后期货合约手续费减半收取规定
        if (trading_day < "20101129" && trading_day < shift_trading_day_forward(shift_contract_month_backward(instrument_id_mon, 6, 15), 2, true))
            fee /= 2;
        // http://www.shfe.com.cn/news/notice/2327936.html
        if (trading_day >= "20120601")
            fee = 4;
        // http://www.shfe.com.cn/news/notice/2726254.html
        if (trading_day >= "20120901")
            fee = 3;
        using_rate = false;
    }
    else if (instrument_id_alp == "zn")
    {
        // since 20070326; https://www.shfe.com.cn/news/notice/72227340.html; https://www.shfe.com.cn/news/notice/78275640.html; https://www.shfe.com.cn/news/notice/8228511.html
        fee = 15;
        // https://www.shfe.com.cn/news/notice/8754745.html
        if (trading_day >= "20080805")
            fee = 12;
        // https://www.shfe.com.cn/news/notice/89107451.html
        if (trading_day >= "20081010")
            fee = 10;
        // https://www.shfe.com.cn/news/notice/89211712.html; https://www.shfe.com.cn/news/notice/811305003.html; https://www.shfe.com.cn/news/notice/92186233.html
        if (trading_day >= "20081021")
            fee = 8;
        // http://www.shfe.com.cn/news/notice/10252865.html 暂停执行所有品种6个月后期货合约手续费减半收取规定
        if (trading_day < "20101129" && trading_day < shift_trading_day_forward(shift_contract_month_backward(instrument_id_mon, 6, 15), 2, true))
            fee /= 2;
        // http://www.shfe.com.cn/news/notice/2327936.html
        if (trading_day >= "20120601")
            fee = 4;
        // http://www.shfe.com.cn/news/notice/2726254.html
        if (trading_day >= "20120901")
            fee = 3;
        using_rate = false;
    }
    else if (instrument_id_alp == "pb")
    {
        // since 20110324; https://www.shfe.com.cn/news/notice/12185742.html
        fee = 0.100 / 1000;
        // http://www.shfe.com.cn/news/notice/2327936.html
        if (trading_day >= "20120601")
            fee = 0.050 / 1000;
        // http://www.shfe.com.cn/news/notice/2726254.html
        if (trading_day >= "20120901")
            fee = 0.040 / 1000;
        using_rate = true;
    }
    else if (instrument_id_alp == "ni")
    {
        // since 20150327; http://www.shfe.com.cn/news/notice/911322340.html
        fee = 6;
        // http://www.shfe.com.cn/news/notice/911328390.html
        if ((instrument_id_mon[2] != '0' || (instrument_id_mon[3] != '1' && instrument_id_mon[3] != '5' && instrument_id_mon[3] != '9')) && trading_day >= "20170907")
            fee = 1;
        // http://www.shfe.com.cn/news/notice/911330158.html
        if (instrument_id_mon == "1807" && trading_day >= "20180420")
            fee = 6;
        // http://www.shfe.com.cn/news/notice/911330961.html
        if (instrument_id_mon == "1811" && trading_day >= "20180803")
            fee = 6;
        // http://www.shfe.com.cn/news/notice/911334369.html
        if ((instrument_id_mon == "1908" || instrument_id_mon == "1910") && trading_day >= "20190730")
            fee = 6;
        // http://www.shfe.com.cn/news/notice/911335013.html
        if ((instrument_id_mon[2] != '0' || (instrument_id_mon[3] != '1' && instrument_id_mon[3] != '5' && instrument_id_mon[3] != '9')) && trading_day >= "20191014" && trading_day >= shift_trading_day_forward(shift_contract_month_backward(instrument_id_mon, 2), 10, true));
            fee = 6;
        // http://www.shfe.com.cn/news/notice/911339648.html
        if (trading_day >= "20210416")
            fee = 3;
        using_rate = false;
    }
    else if (instrument_id_alp == "sn")
    {
        // since 20150327; http://www.shfe.com.cn/news/notice/911322340.html
        fee = 3;
        // http://www.shfe.com.cn/news/notice/911328390.html
        // http://www.shfe.com.cn/news/notice/911339517.html
        if ((instrument_id_mon[2] != '0' || (instrument_id_mon[3] != '1' && instrument_id_mon[3] != '5' && instrument_id_mon[3] != '9')) && trading_day >= "20170907" && trading_day < "20210308")
            fee = 1;
        using_rate = false;
    }
    else if (instrument_id_alp == "au")
    {
        // since 20080109; http://www.shfe.com.cn/news/notice/8024962.html
        fee = 30;
        // http://www.shfe.com.cn/news/notice/10252865.html 暂停执行所有品种6个月后期货合约手续费减半收取规定
        if (trading_day < "20101129" && trading_day < shift_trading_day_forward(shift_contract_month_backward(instrument_id_mon, 6, 15), 2, true))
            fee /= 2;
        // http://www.shfe.com.cn/news/notice/2327936.html
        if (trading_day >= "20120601")
            fee = 20;
        // http://www.shfe.com.cn/news/notice/2726254.html
        if (trading_day >= "20120901")
            fee = 10;
        // http://www.shfe.com.cn/news/notice/911335013.html
        if (!((instrument_id_mon[2] == '0' && instrument_id_mon[3] == '6') || (instrument_id_mon[2] == '1' && instrument_id_mon[3] == '2')) && trading_day >= "20191014")
        {
            fee = 2;
            if (((instrument_id_mon[2] == '0' && (instrument_id_mon[3] == '2' || instrument_id_mon[3] == '4' || instrument_id_mon[3] == '8')) || (instrument_id_mon[2] == '1' && instrument_id_mon[3] == '0')) && trading_day >= shift_trading_day_forward(shift_contract_month_backward(instrument_id_mon, 2), 1, true))
                fee = 10;
        }
        using_rate = false;
    }
    else if (instrument_id_alp == "ag")
    {
        // since 20120510; http://www.shfe.com.cn/news/notice/2447617.html
        fee = 0.080 / 1000;
        // http://www.shfe.com.cn/news/notice/2726254.html
        if (trading_day >= "20120901")
            fee = 0.050 / 1000;
        // http://www.shfe.com.cn/news/notice/911335013.html
        if (!((instrument_id_mon[2] == '0' && instrument_id_mon[3] == '6') || (instrument_id_mon[2] == '1' && instrument_id_mon[3] == '2')) && trading_day >= "20191014" && trading_day < shift_trading_day_forward(shift_contract_month_backward(instrument_id_mon, 2), 1, true))
            fee = 0.010 / 1000;
        using_rate = true;
    }
    else if (instrument_id_alp == "rb")
    {
        // since 20090327; http://www.shfe.com.cn/news/notice/92235792.html
        fee = 0.100 / 1000;
        using_rate = true;
        // http://www.shfe.com.cn/news/notice/10252865.html 暂停执行所有品种6个月后期货合约手续费减半收取规定
        if (trading_day < "20101129" && trading_day < shift_trading_day_forward(shift_contract_month_backward(instrument_id_mon, 6, 15), 2, true))
            fee /= 2;
        // http://www.shfe.com.cn/news/notice/16264564.html
        if (trading_day >= "20110801")
            fee = 0.060 / 1000;
        // http://www.shfe.com.cn/news/notice/2327936.html
        if (trading_day >= "20120601")
            fee = 0.050 / 1000;
        // http://www.shfe.com.cn/news/notice/2726254.html
        if (trading_day >= "20120901")
            fee = 0.045 / 1000;
        // http://www.shfe.com.cn/news/notice/911324799.html
        if (trading_day >= "20160329")
            fee = 0.060 / 1000;
        // http://www.shfe.com.cn/news/notice/911324983.html
        if (trading_day >= "20160425")
            fee = 0.100 / 1000;
        // http://www.shfe.com.cn/news/notice/911401794.html
        // http://www.shfe.com.cn/news/notice/911402122.html
        if (instrument_id_mon == "2305" && trading_day >= "20220926" && trading_day < "20221201")
            fee = 0.200 / 1000;
        // http://www.shfe.com.cn/news/notice/911401900.html
        // http://www.shfe.com.cn/news/notice/911402689.html
        if (instrument_id_mon == "2310" && trading_day >= "20221107" && trading_day < "20230403")
            fee = 0.200 / 1000;
        // http://www.shfe.com.cn/news/notice/911402400.html
        // http://www.shfe.com.cn/news/notice/911402689.html
        // https://www.shfe.com.cn/news/notice/911403573.html
        if (instrument_id_mon == "2401" && trading_day < "20230907")
        {
            if (trading_day >= "20230403")
                fee = 0.300 / 1000;
            else if (trading_day >= "20230117")
                fee = 0.200 / 1000;
        }
        // http://www.shfe.com.cn/news/notice/911402939.html
        if (instrument_id_mon == "2405" && trading_day >= "20230524")
            fee = 0.300 / 1000;
    }
    else if (instrument_id_alp == "wr")
    {
        // since 20090327; http://www.shfe.com.cn/news/notice/92235792.html
        fee = 0.100 / 1000;
        // http://www.shfe.com.cn/news/notice/10252865.html 暂停执行所有品种6个月后期货合约手续费减半收取规定
        if (trading_day < "20101129" && trading_day < shift_trading_day_forward(shift_contract_month_backward(instrument_id_mon, 6, 15), 2, true))
            fee /= 2;
        // http://www.shfe.com.cn/news/notice/2327936.html
        if (trading_day >= "20120601")
            fee = 0.050 / 1000;
        // http://www.shfe.com.cn/news/notice/2726254.html
        // since 20181016; http://www.shfe.com.cn/news/notice/911331232.html
        if (trading_day >= "20120901")
            fee = 0.040 / 1000
        using_rate = true;
    }
    else if (instrument_id_alp == "hc")
    {
        // since 20140321; http://www.shfe.com.cn/news/notice/911319760.html
        fee = 0.080 / 1000;
        // http://www.shfe.com.cn/news/notice/911320975.html
        if (trading_day >= "20140825")
            fee = 0.040 / 1000;
        // http://www.shfe.com.cn/news/notice/911324983.html
        if (trading_day >= "20160425")
            fee = 0.100 / 1000;
        using_rate = true;
    }
    else if (instrument_id_alp == "fu")
    {
        // since 20040825; http://www.shfe.com.cn/news/notice/4742466.html
        fee = 2;
        using_rate = false;
        // http://www.shfe.com.cn/news/notice/10252865.html 暂停执行所有品种6个月后期货合约手续费减半收取规定
        if (trading_day < "20101129" && trading_day < shift_contract_month_backward(instrument_id_mon, 6))
            fee /= 2;
        // http://www.shfe.com.cn/news/notice/10149109.html
        if (trading_day >= "20110117")
        {
            fee = 0.050 / 1000;
            using_rate = true;
        }
        // http://www.shfe.com.cn/news/notice/2327936.html
        if (trading_day >= "20120601")
            fee = 0.035 / 1000;
        // http://www.shfe.com.cn/news/notice/2726254.html
        if (trading_day >= "20120901")
            fee = 0.020 / 1000;
        // http://www.shfe.com.cn/news/notice/911328200.html
        if (trading_day >= "20170901")
            fee = 2.000 / 1000;
        // http://www.shfe.com.cn/news/notice/911330669.html
        if (trading_day >= "20180716")
            fee = 0.050 / 1000;
        // http://www.shfe.com.cn/news/notice/911335013.html
        if ((instrument_id_mon[2] != '0' || (instrument_id_mon[3] != '1' && instrument_id_mon[3] != '5' && instrument_id_mon[3] != '9')) && trading_day >= "20191014" && trading_day < shift_trading_day_forward(shift_contract_month_backward(instrument_id_mon, 2), 10, true));
            fee = 0.010 / 1000;
        // http://www.shfe.com.cn/news/notice/911335385.html
        if (instrument_id_mon == "2001" && trading_day >= "20191122")
            fee = 0.200 / 1000;
    }
    else if (instrument_id_alp == "bu")
    {
        // since 20131009; http://www.shfe.com.cn/news/notice/38235956.html
        fee = 0.030 / 1000;
        // http://www.shfe.com.cn/news/notice/911323768.html
        if (trading_day >= "20151117")
            fee = 0.050 / 1000;
        // http://www.shfe.com.cn/news/notice/911323871.html
        if (trading_day >= "20151208")
            fee = 0.080 / 1000;
        // http://www.shfe.com.cn/news/notice/911324983.html
        if (trading_day >= "20160425")
            fee = 0.100 / 1000;
        using_rate = true;
    }
    else if (instrument_id_alp == "ru")
    {
        // since 199303
        // https://www.shfe.com.cn/news/notice/3084655.html since 20020401
        fee = 0.150 / 1000;
        using_rate = true;
        // https://www.shfe.com.cn/news/notice/3084222.html since at least 20021101
        if (trading_day >= "20021101")
        {
            fee = 5;
            using_rate = false;
        }
        // https://www.shfe.com.cn/news/notice/9226822.html
        if (trading_day >= "20101025")
        {
            fee = 0.100 / 1000;
            using_rate = true;
        }
        // https://www.shfe.com.cn/news/notice/9295130.html 天然橡胶期货6个月后合约手续费减半收取规定暂停执行
        // http://www.shfe.com.cn/news/notice/10252865.html 暂停执行所有品种6个月后期货合约手续费减半收取规定 since 20101129
        if (trading_day < "20101101" && trading_day < shift_trading_day_forward(shift_contract_month_backward(instrument_id_mon, 6, 15), 2, true))
            fee /= 2;
        // http://www.shfe.com.cn/news/notice/10252865.html
        if (trading_day >= "20101129")
            fee = 0.150 / 1000;
        // http://www.shfe.com.cn/news/notice/16269085.html
        if (instrument_id_mon >= "1208" && trading_day >= "20110816")
            fee = 0.100 / 1000;
        // http://www.shfe.com.cn/news/notice/2327936.html
        if (trading_day >= "20120601")
            fee = 0.050 / 1000;
        // http://www.shfe.com.cn/news/notice/2726254.html
        if (trading_day >= "20120901")
            fee = 0.045 / 1000;
        // http://www.shfe.com.cn/news/notice/911337331.html
        if (trading_day >= "20200707")
        {
            fee = 3;
            using_rate = false;
        }
    }
    else if (instrument_id_alp == "sp")
    {
        // since 20181127; http://www.shfe.com.cn/news/notice/911331902.html
        fee = 0.050 / 1000;
        using_rate = true;
    }
    else if (instrument_id_alp == "ss")
    {
        // since 20190925; http://www.shfe.com.cn/news/notice/911334944.html
        fee = 0.100 / 1000;
        using_rate = true;
        // http://www.shfe.com.cn/news/notice/911337331.html
        if (trading_day >= "20200707")
        {
            fee = 2;
            using_rate = false;
        }
    }
    else if (instrument_id_alp == "ao")
    {
        // since 20230619; http://www.shfe.com.cn/news/notice/911403031.html
        fee = 0.010 / 1000;
        using_rate = true;
        // https://www.shfe.com.cn/news/notice/911403576.html
        if (trading_day >= "20230908")
            fee = 0.100 / 1000;
    }
    else if (instrument_id_alp == "br")
    {
        // since 20230728; http://www.shfe.com.cn/news/notice/911403270.html
        fee = 0.010 / 1000;
        using_rate = true;
        // https://www.shfe.com.cn/news/notice/911403576.html
        if (trading_day >= "20230908")
            fee = 0.100 / 1000;
    }
    /* INE */
    else if (instrument_id_alp == "sc")
    {
        // since 20180326; http://www.shfe.com.cn/news/notice/911329893.html
        fee = 20;
        using_rate = false;
        // http://www.shfe.com.cn/news/notice/911330724.html
        if (instrument_id_mon == "1810" && trading_day < "20180901" && trading_day >= "20180705")
            fee = 5;
        if (instrument_id_mon == "1811" && trading_day < "20181001" && trading_day >= "20180705")
            fee = 10;
        // http://www.shfe.com.cn/news/notice/911330950.html
        if (instrument_id_mon == "1901" && trading_day < "20181201" && trading_day >= "20180803")
            fee = 5;
        if (instrument_id_mon == "1902" && trading_day < "20190101" && trading_day >= "20180803")
            fee = 5;
    }
    else if (instrument_id_alp == "nr")
    {
        // since 20190812; http://www.ine.cn/news/notice/1878.html
        fee = 10;
        using_rate = false;
        // http://www.shfe.com.cn/news/notice/911337330.html
        if (trading_day >= "20200707")
            fee = 3;
        // http://www.shfe.com.cn/news/notice/911339647.html
        if (trading_day >= "20210416")
        {
            fee = 0.020 / 1000;
            using_rate = true;
        }
    }
    else if (instrument_id_alp == "lu")
    {
        // since 20200622; http://www.shfe.com.cn/news/notice/911337187.html
        fee = 2;
        using_rate = false;
        // http://www.shfe.com.cn/news/notice/911339647.html
        if (trading_day >= "20210416")
        {
            fee = 0.010 / 1000;
            using_rate = true;
        }
    }
    else if (instrument_id_alp == "bc")
    {
        // since 20201119; http://www.shfe.com.cn/news/notice/911338406.html
        fee = 0.010 / 1000;
        using_rate = true;
    }
    else if (instrument_id_alp == "ec")
    {
        // since 20230818; http://www.shfe.com.cn/news/notice/911403434.html
        fee = 0.010 / 1000;
        using_rate = true;
    }
    /* DCE */
    else if (instrument_id_alp == "a")
    {
        // since 20020315; http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1986629/index.html
        fee = 4;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1987567/index.html
        if (trading_day >= "20120601")
            fee = 2;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6212400/index.html
        if (instrument_id_mon == "2005" && trading_day >= "20200402")
            fee = 6;
        using_rate = false;
    }
    else if (instrument_id_alp == "m")
    {
        // since 20000717; http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1987054/index.html; http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1986975/index.html
        fee = 0;
        using_rate = false;
        if (trading_day > "20000831")
            fee = 3;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1987567/index.html
        if (trading_day >= "20120601")
            fee = 2;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/5001374/index.html
        if (trading_day >= "20150309")
            fee = 1.5;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6074031/index.html
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6295503/index.html
        if ((instrument_id_mon[2] != '0' || (instrument_id_mon[3] != '1' && instrument_id_mon[3] != '5' && instrument_id_mon[3] != '9')) && trading_day < "20211102" && trading_day >= "20171201")
            fee = 0.2;
    }
    else if (instrument_id_alp == "c")
    {
        // since 20040922; http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1986787/index.html
        fee = 2;
        using_rate = false;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1987567/index.html
        if (trading_day >= "20120601")
            fee = 1.5;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1987954/index.html
        if (trading_day >= "20130909")
            fee = 1.2;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6074031/index.html
        if ((instrument_id_mon[2] != '0' || (instrument_id_mon[3] != '1' && instrument_id_mon[3] != '5' && instrument_id_mon[3] != '9')) && trading_day < "20211102" && trading_day >= "20171201")
            fee = 0.2;
    }
    else if (instrument_id_alp == "b")
    {
        // since 20041222; http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1986915/index.html
        fee = 4;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1987567/index.html
        if (trading_day >= "20120601")
            fee = 2;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6039650/index.html
        if (trading_day >= "20180501" || (trading_day >= "20170531" && instrument_id_mon >= "1805"))
            fee = 1;
        using_rate = false;
    }
    else if (instrument_id_alp == "y")
    {
        // since 20060109; http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/2045798/index.html
        fee = 6;
        using_rate = false;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1987141/index.html
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1987313/index.html
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1987299/index.html
        if (trading_day >= "20060807")
            fee = 4;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1987567/index.html
        if (trading_day >= "20120601")
            fee = 3.5;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1987606/index.html
        if (trading_day >= "20120901")
            fee = 2.5;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6192780/index.html
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6295503/index.html
        if ((instrument_id_mon[2] != '0' || (instrument_id_mon[3] != '1' && instrument_id_mon[3] != '5' && instrument_id_mon[3] != '9')) && trading_day < "20211102" && trading_day >= "20191101")
            fee = 0.2;
    }
    else if (instrument_id_alp == "l")
    {
        // since 20070731; http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/2046518/index.html
        fee = 8;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1987103/index.html
        if (trading_day >= "20080701")
            fee = 6;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1987567/index.html
        if (trading_day >= "20120601")
            fee = 3.5;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1987606/index.html
        if (trading_day >= "20120901")
            fee = 2.5;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/5001374/index.html
        if (trading_day >= "20150309")
            fee = 2;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6192780/index.html
        if ((instrument_id_mon[2] != '0' || (instrument_id_mon[3] != '1' && instrument_id_mon[3] != '5' && instrument_id_mon[3] != '9')) && trading_day >= "20191101")
            fee = 0.2;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6261878/index.html
        if (trading_day >= "20210104")
        {
            if (instrument_id_mon[2] == '0' && (instrument_id_mon[3] == '1' || instrument_id_mon[3] == '5' || instrument_id_mon[3] == '9'))
                fee = 1;
            else
                fee = 0.1;
        }
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6270769/index.html
        if ((instrument_id_mon[2] != '0' || (instrument_id_mon[3] != '1' && instrument_id_mon[3] != '5' && instrument_id_mon[3] != '9')) && trading_day >= "20210302")
            fee = 1;
        using_rate = false;
    }
    else if (instrument_id_alp == "p")
    {
        // since 20071029; http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/2046638/index.html
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1987103/index.html
        fee = 4;
        using_rate = false;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1987567/index.html
        if (trading_day >= "20120601")
            fee = 3.5;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1987606/index.html
        if (trading_day >= "20120901")
            fee = 2.5;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6192780/index.html
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6295503/index.html
        if ((instrument_id_mon[2] != '0' || (instrument_id_mon[3] != '1' && instrument_id_mon[3] != '5' && instrument_id_mon[3] != '9')) && trading_day < "20211102" && trading_day >= "20191101")
            fee = 0.2;
    }
    else if (instrument_id_alp == "v")
    {
        // since 20090525; http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/2046781/index.html
        fee = 6;
        using_rate = false;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1987567/index.html
        if (trading_day >= "20120601")
            fee = 3.5;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1987606/index.html
        if (trading_day >= "20120901")
            fee = 2.5;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1987954/index.html
        if (trading_day >= "20130909")
            fee = 2;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6192780/index.html
        if ((instrument_id_mon[2] != '0' || (instrument_id_mon[3] != '1' && instrument_id_mon[3] != '5' && instrument_id_mon[3] != '9')) && trading_day >= "20191101")
            fee = 0.2;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6261878/index.html
        if (trading_day >= "20210104")
        {
            if (instrument_id_mon[2] == '0' && (instrument_id_mon[3] == '1' || instrument_id_mon[3] == '5' || instrument_id_mon[3] == '9'))
                fee = 1;
            else
                fee = 0.1;
        }
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6270769/index.html
        if ((instrument_id_mon[2] != '0' || (instrument_id_mon[3] != '1' && instrument_id_mon[3] != '5' && instrument_id_mon[3] != '9')) && trading_day >= "20210302")
            fee = 1;
    }
    else if (instrument_id_alp == "j")
    {
        // since 20110415; http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/2048491/index.html
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1987591/index.html
        fee = 0.100 / 1000;
        using_rate = true;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1987567/index.html
        if (trading_day >= "20120601")
            fee = 0.080 / 1000;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/5001374/index.html
        if (trading_day >= "20150309")
            fee = 0.060 / 1000;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/5508883/index.html
        if (trading_day >= "20160426")
            fee = 0.180 / 1000;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/5500553/index.html
        if (trading_day >= "20160427")
            fee = 0.360 / 1000;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/5502298/index.html
        if (trading_day >= "20160428")
            fee = 0.720 / 1000;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/5513042/index.html 非日内交易手续费标准调整为成交金额的万分之0.6, 日内交易手续费标准维持不变
        if (trading_day >= "20160510")
            fee = 0.060 / 1000;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6001437/index.html 非日内交易手续费标准由成交金额的万分之0.6提高至万分之1.2, 日内交易手续费标准维持成交金额的万分之7.2不变
        if (trading_day >= "20161109")
            fee = 0.120 / 1000;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6034960/index.html 非日内交易手续费标准由成交金额的万分之1.2调整为成交金额的万分之0.6
        if (trading_day >= "20170417")
            fee = 0.060 / 1000;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6192780/index.html
        if ((instrument_id_mon[2] != '0' || (instrument_id_mon[3] != '1' && instrument_id_mon[3] != '5' && instrument_id_mon[3] != '9')) && trading_day >= "20191101")
            fee = 0.006 / 1000;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6278926/index.html
        if (instrument_id_mon[2] == '0' && (instrument_id_mon[3] == '1' || instrument_id_mon[3] == '5' || instrument_id_mon[3] == '9') && trading_day >= "20210518")
            fee = 0.070 / 1000;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6289003/index.html
        if (trading_day >= "20210824")
            fee = 0.100 / 1000;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6290677/index.html
        if ((instrument_id_mon == "2110" || instrument_id_mon == "2111" || instrument_id_mon == "2112" || instrument_id_mon == "2201") && trading_day >= "20210909")
            fee = 0.600 / 1000;
    }
    else if (instrument_id_alp == "jm")
    {
        // since 20130322; http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/2048401/index.html; http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1987494/index.html
        fee = 0.100 / 1000;
        using_rate = true;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/5001374/index.html
        if (trading_day >= "20150309")
            fee = 0.060 / 1000;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/5508883/index.html
        if (trading_day >= "20160426")
            fee = 0.180 / 1000;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/5500553/index.html
        if (trading_day >= "20160427")
            fee = 0.360 / 1000;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/5502298/index.html
        if (trading_day >= "20160428")
            fee = 0.720 / 1000;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/5513042/index.html 非日内交易手续费标准调整为成交金额的万分之0.6, 日内交易手续费标准维持不变
        if (trading_day >= "20160510")
            fee = 0.060 / 1000;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6001437/index.html 非日内交易手续费标准由成交金额的万分之0.6提高至万分之1.2, 日内交易手续费标准维持成交金额的万分之7.2不变
        if (trading_day >= "20161109")
            fee = 0.120 / 1000;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6034960/index.html 非日内交易手续费标准由成交金额的万分之1.2调整为成交金额的万分之0.6
        if (trading_day >= "20170417")
            fee = 0.060 / 1000;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6192780/index.html
        if ((instrument_id_mon[2] != '0' || (instrument_id_mon[3] != '1' && instrument_id_mon[3] != '5' && instrument_id_mon[3] != '9')) && trading_day >= "20191101")
            fee = 0.006 / 1000;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6278926/index.html
        if (instrument_id_mon[2] == '0' && (instrument_id_mon[3] == '1' || instrument_id_mon[3] == '5' || instrument_id_mon[3] == '9') && trading_day >= "20210518")
            fee = 0.070 / 1000;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6289003/index.html
        if (trading_day >= "20210824")
            fee = 0.100 / 1000;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6290677/index.html
        if ((instrument_id_mon == "2110" || instrument_id_mon == "2111" || instrument_id_mon == "2112" || instrument_id_mon == "2201") && trading_day >= "20210909")
            fee = 0.600 / 1000;
    }
    else if (instrument_id_alp == "i")
    {
        // since 20131018; http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/2048537/index.html
        fee = 0.080 / 1000;
        using_rate = true;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/5001374/index.html
        if (trading_day >= "20150309")
            fee = 0.060 / 1000;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/5510960/index.html
        if (trading_day >= "20160425")
            fee = 0.090 / 1000;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/5512822/index.html
        if (trading_day >= "20160426")
            fee = 0.180 / 1000;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/5500553/index.html
        if (trading_day >= "20160427")
            fee = 0.300 / 1000;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/5513042/index.html 非日内交易手续费标准调整为成交金额的万分之0.6, 日内交易手续费标准维持不变
        if (trading_day >= "20160510")
            fee = 0.060 / 1000;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6008823/index.html 非日内交易手续费标准由成交金额的万分之0.6调整为成交金额的万分之1.2, 日内交易手续费标准维持成交金额的万分之3不变
        if (trading_day >= "20161111")
            fee = 0.120 / 1000;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6034960/index.html 非日内交易手续费标准由成交金额的万分之1.2调整为成交金额的万分之0.6
        if (trading_day >= "20170417")
            fee = 0.060 / 1000;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6031349/index.html
        if (instrument_id_mon == "1707" && trading_day < "20170701" && trading_day >= "20170502")
            fee *= 0.1;
        if ((instrument_id_mon == "1708" || instrument_id_mon == "1710" || instrument_id_mon == "1711") && trading_day <= "20170731" && trading_day >= "20170502")
            fee *= 0.1;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6074031/index.html
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6164452/index.html
        if ((instrument_id_mon[2] != '0' || (instrument_id_mon[3] != '1' && instrument_id_mon[3] != '5' && instrument_id_mon[3] != '9')) && trading_day < "20190530" && trading_day >= "20171201")
            fee = 0.006 / 1000;
        if (instrument_id_mon == "1909" && trading_day >= "20190530")
            fee = 0.100 / 1000;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6172534/index.html
        if (trading_day >= "20190718")
            fee = 0.100 / 1000;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6192780/index.html
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6258635/index.html
        if ((instrument_id_mon[2] != '0' || (instrument_id_mon[3] != '1' && instrument_id_mon[3] != '5' && instrument_id_mon[3] != '9')) && trading_day < "20201222" && trading_day >= "20191101")
            fee = 0.010 / 1000;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6303974/index.html
        if ((instrument_id_mon == "2202" || instrument_id_mon == "2203" || instrument_id_mon == "2204" || instrument_id_mon == "2205") && trading_day >= "20220216")
            fee = 0.200 / 1000;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6307719/index.html
        if (instrument_id_mon == "2209" && trading_day >= "20220330")
            fee = 0.200 / 1000;
    }
    else if (instrument_id_alp == "jd")
    {
        // since 20131108; http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/2048617/index.html
        fee = 0.150 / 1000;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6208262/index.html
        if ((instrument_id_mon == "2004" || instrument_id_mon == "2005") && trading_day >= "20200309")
            fee = 0.300 / 1000;
        using_rate = true;
    }
    else if (instrument_id_alp == "fb")
    {
        // since 20131206; http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/2048823/index.html
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6191275/index.html
        fee = 0.100 / 1000;
        //
        fee = 0.050 / 1000;
        using_rate = true;
    }
    else if (instrument_id_alp == "bb")
    {
        // since 20131206; http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/2048823/index.html
        fee = 0.100 / 1000;
        //
        fee = 0.050 / 1000;
        using_rate = true;
    }
    else if (instrument_id_alp == "pp")
    {
        // since 20140228; http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/2048192/index.html
        fee = 0.050 / 1000;
        using_rate = true;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/5026889/index.html
        if (trading_day >= "20151230")
            fee = 0.070 / 1000;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/5510960/index.html
        if (trading_day >= "20160425")
            fee = 0.090 / 1000;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/5512822/index.html
        if (trading_day >= "20160426")
            fee = 0.180 / 1000;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/5500553/index.html
        if (trading_day >= "20160427")
            fee = 0.240 / 1000;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/5513042/index.html 非日内交易手续费标准调整为成交金额的万分之0.6, 日内交易手续费标准维持不变
        if (trading_day >= "20160510")
            fee = 0.060 / 1000;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6192780/index.html
        if ((instrument_id_mon[2] != '0' || (instrument_id_mon[3] != '1' && instrument_id_mon[3] != '5' && instrument_id_mon[3] != '9')) && trading_day >= "20191101")
            fee = 0.006 / 1000;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6261878/index.html
        if (trading_day >= "20210104")
        {
            if (instrument_id_mon[2] == '0' && (instrument_id_mon[3] == '1' || instrument_id_mon[3] == '5' || instrument_id_mon[3] == '9'))
                fee = 1;
            else
                fee = 0.1;
            using_rate = false;
        }
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6270769/index.html
        if ((instrument_id_mon[2] != '0' || (instrument_id_mon[3] != '1' && instrument_id_mon[3] != '5' && instrument_id_mon[3] != '9')) && trading_day >= "20210302")
            fee = 1;
    }
    else if (instrument_id_alp == "cs")
    {
        // since 20141219; http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/2285936/index.html
        fee = 1.5;
        using_rate = false;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6192780/index.html
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6295407/index.html
        if ((instrument_id_mon[2] != '0' || (instrument_id_mon[3] != '1' && instrument_id_mon[3] != '5' && instrument_id_mon[3] != '9')) && trading_day < "20211102" && trading_day >= "20191101")
            fee = 0.2;
    }
    else if (instrument_id_alp == "eg")
    {
        // since 20181210; http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6138990/index.html
        fee = 4;
        using_rate = false;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6192780/index.html
        if ((instrument_id_mon[2] != '0' || (instrument_id_mon[3] != '1' && instrument_id_mon[3] != '5' && instrument_id_mon[3] != '9')) && trading_day >= "20191101")
            fee = 0.4;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6229328/index.html
        if (trading_day >= "20200720")
        {
            if (instrument_id_mon[2] == '0' && (instrument_id_mon[3] == '1' || instrument_id_mon[3] == '5' || instrument_id_mon[3] == '9'))
                fee = 3;
            else
                fee = 0.2;
        }
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6270769/index.html
        if ((instrument_id_mon[2] != '0' || (instrument_id_mon[3] != '1' && instrument_id_mon[3] != '5' && instrument_id_mon[3] != '9')) && trading_day >= "20210302")
            fee = 3;
    }
    else if (instrument_id_alp == "rr")
    {
        // since 20190816; http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6177470/index.html
        fee = 4;
        using_rate = false;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6192780/index.html
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6225456/index.html
        if ((instrument_id_mon[2] != '0' || (instrument_id_mon[3] != '1' && instrument_id_mon[3] != '5' && instrument_id_mon[3] != '9'))
        {
            if (trading_day >= "20200701")
                fee = 0.2;
            else if (trading_day >= "20191101")
                fee = 0.4;
        }
        else
        {
            if (trading_day >= "20200701")
                fee = 1;
        }
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6295503/index.html
        if (trading_day >= "20211102")
            fee = 1;
    }
    else if (instrument_id_alp == "eb")
    {
        // since 20190926; http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6188157/index.html
        fee = 6;
        using_rate = false;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6225456/index.html
        if (trading_day >= "20200701")
        {
            if (instrument_id_mon[2] == '0' && (instrument_id_mon[3] == '1' || instrument_id_mon[3] == '5' || instrument_id_mon[3] == '9'))
                fee = 3;
            else
                fee = 0.3;
        }
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6270769/index.html
        if ((instrument_id_mon[2] != '0' || (instrument_id_mon[3] != '1' && instrument_id_mon[3] != '5' && instrument_id_mon[3] != '9')) && trading_day >= "20210302")
            fee = 3;
    }
    else if (instrument_id_alp == "pg")
    {
        // since 20200330; http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6210512/index.html
        fee = 6;
        using_rate = false;
    }
    else if (instrument_id_alp == "lh")
    {
        // since 20210108; http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6263003/index.html
        fee = 0.200 / 1000;
        using_rate = true;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/8544536/index.html
        if (trading_day >= "20230524")
            fee = 0.100 / 1000;
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
    else if (instrument_id_alp == "IM")
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
    else if (instrument_id_alp == "TL")
    {
        fee = 3;
        using_rate = false;
    }
    /* GFEX */
    else if (instrument_id_alp == "si")
    {
        fee = 0.100 / 1000;
        using_rate = true;
    }
    else if (instrument_id_alp == "lc")
    {
        fee = 0.080 / 1000;
        using_rate = true;
    }
    else
        std::cerr << parse_milliseconds(0) << " ERROR TdEngine %% - [transaction_cost] open fees haven't been defined for " << instrument_id_alp << std::endl;
    
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
    
    return std::make_pair(fee, using_rate);
}

inline double get_close_mpl(const std::string& trading_day, const std::string& instrument_id)
{
    double mpl;
    std::string instrument_id_alp = get_instrument_id_alp(instrument_id);
    std::string instrument_id_mon = get_instrument_id_mon(instrument_id);
    /* SHFE */
    if (instrument_id_alp == "cu")
    {
        mpl = 0;
        // http://www.shfe.com.cn/news/notice/10243056.html
        if (trading_day >= "20101129")
            mpl = 1;
        // http://www.shfe.com.cn/news/notice/16264564.html
        if (trading_day >= "20110801")
            mpl = 0;
        // http://www.shfe.com.cn/news/notice/911326216.html
        if ((instrument_id_mon == "1701" || instrument_id_mon == "1702") && trading_day >= "20161115")
            mpl = 2;
        // http://www.shfe.com.cn/news/notice/911339494.html
        if (trading_day >= "20210302")
            mpl = 1;
        // http://www.shfe.com.cn/news/notice/911339738.html
        if (trading_day >= "20210518")
            mpl = 2;
    }
    else if (instrument_id_alp == "al")
    {
        mpl = 0;
        // https://www.shfe.com.cn/news/notice/10243056.html
        if (trading_day >= "20101129")
            mpl = 1;
        // http://www.shfe.com.cn/news/notice/911319809.html
        if (trading_day >= "20140401")
            mpl = 0;
        // http://www.shfe.com.cn/news/notice/911339738.html
        if (trading_day >= "20210518")
            mpl = 1;
        // http://www.shfe.com.cn/news/notice/911340676.html
        if (instrument_id_mon == "2112" && trading_day >= "20211102")
            mpl = 5;
    }
    else if (instrument_id_alp == "zn")
    {
        // https://www.shfe.com.cn/news/notice/72227340.html
        mpl = 0;
        // https://www.shfe.com.cn/news/notice/6216207.html
        if (trading_day <= "20100827" && trading_day >= "20100802")
            mpl = 1;
        // http://www.shfe.com.cn/news/notice/10243056.html
        if (trading_day >= "20101129")
            mpl = 1;
        // http://www.shfe.com.cn/news/notice/911319809.html
        if (trading_day >= "20140401")
            mpl = 0;
        // http://www.shfe.com.cn/news/notice/911326216.html
        if ((instrument_id_mon == "1701" || instrument_id_mon == "1702") && trading_day >= "20161115")
            mpl = 2;
        // http://www.shfe.com.cn/news/notice/911328236.html
        if ((instrument_id_mon == "1710" || instrument_id_mon == "1711") && trading_day >= "20170823")
            mpl = 5;
        // http://www.shfe.com.cn/news/notice/911328648.html
        if (instrument_id_mon == "1712" && trading_day >= "20171018")
            mpl = 5;
        // http://www.shfe.com.cn/news/notice/911330875.html
        if (instrument_id_mon == "1809")
        {
            if (trading_day >= "20180816")
                mpl = 1;
            else if (trading_day >= "20180724")
                mpl = 5;
        }
        // http://www.shfe.com.cn/news/notice/911340676.html
        if (instrument_id_mon == "2112" && trading_day >= "20211102")
            mpl = 5;
        // http://www.shfe.com.cn/news/notice/911340977.html
        if ((instrument_id_mon == "2201" || instrument_id_mon == "2202") && trading_day >= "20211203")
            mpl = 1;
    }
    else if (instrument_id_alp == "pb")
    {
        // https://www.shfe.com.cn/news/notice/12185742.html
        mpl = 1;
        // http://www.shfe.com.cn/news/notice/911319809.html
        if (trading_day >= "20140401")
            mpl = 0;
        // http://www.shfe.com.cn/news/notice/911328542.html
        if (instrument_id_mon == "1711" && trading_day >= "20170926")
            mpl = 5;
        // http://www.shfe.com.cn/news/notice/911340644.html
        if ((instrument_id_mon == "2111" || instrument_id_mon == "2112") && trading_day >= "20211026")
            mpl = 1;
    }
    else if (instrument_id_alp == "ni")
    {
        // http://www.shfe.com.cn/news/notice/911322340.html
        mpl = 0;
        // http://www.shfe.com.cn/news/notice/911323534.html
        if (trading_day >= "20150922")
            mpl = 1;
        // http://www.shfe.com.cn/news/notice/911326216.html
        if ((instrument_id_mon == "1701" || instrument_id_mon == "1705") && trading_day >= "20161115")
            mpl = 2;
        // http://www.shfe.com.cn/news/notice/911328390.html
        if ((instrument_id_mon[2] != '0' || (instrument_id_mon[3] != '1' && instrument_id_mon[3] != '5' && instrument_id_mon[3] != '9')) && trading_day >= "20170907")
            mpl = 0;
        // http://www.shfe.com.cn/news/notice/911328523.html
        if (instrument_id_mon == "1801" && trading_day >= "20170922")
            mpl = 3;
        // http://www.shfe.com.cn/news/notice/911328534.html
        if (instrument_id_mon == "1801" && trading_day >= "20170925")
            mpl = 5;
        // http://www.shfe.com.cn/news/notice/911329729.html
        if (instrument_id_mon == "1805" && trading_day >= "20180212")
            mpl = 5;
        // http://www.shfe.com.cn/news/notice/911330158.html
        if ((instrument_id_mon == "1805" || instrument_id_mon == "1807") && trading_day >= "20180420")
            mpl = 1;
        // http://www.shfe.com.cn/news/notice/911330961.html
        if (instrument_id_mon == "1811" && trading_day >= "20180803")
            mpl = 1;
        // http://www.shfe.com.cn/news/notice/911334369.html
        if ((instrument_id_mon == "1908" || instrument_id_mon == "1910") && trading_day >= "20190730")
            mpl = 1;
        // http://www.shfe.com.cn/news/notice/911335013.html
        if ((instrument_id_mon[2] != '0' || (instrument_id_mon[3] != '1' && instrument_id_mon[3] != '5' && instrument_id_mon[3] != '9')) && trading_day >= "20191014" && trading_day >= shift_trading_day_forward(shift_contract_month_backward(instrument_id_mon, 2), 10, true));
            mpl = 1;
        // http://www.shfe.com.cn/news/notice/911339648.html
        if (trading_day >= "20210416")
            mpl = 0;
        // http://www.shfe.com.cn/news/notice/911339738.html
        if (trading_day >= "20210518")
            mpl = 1;
        // http://www.shfe.com.cn/news/notice/911339821.html
        if ((instrument_id_mon == "2107" || instrument_id_mon == "2108") && trading_day >= "20210603")
            mpl = 2;
        // http://www.shfe.com.cn/news/notice/911340644.html
        if ((instrument_id_mon == "2111" || instrument_id_mon == "2112") && trading_day >= "20211026")
            mpl = 2;
        // http://www.shfe.com.cn/news/notice/911340676.html
        if ((instrument_id_mon == "2111" || instrument_id_mon == "2112") && trading_day >= "20211102")
            mpl = 5;
        // http://www.shfe.com.cn/news/notice/911340692.html
        if ((instrument_id_mon == "2111" || instrument_id_mon == "2112" || instrument_id_mon == "2201") && trading_day >= "20211108")
            mpl = 15;
        // http://www.shfe.com.cn/news/notice/911340954.html
        if ((instrument_id_mon == "2202" || instrument_id_mon == "2203" || instrument_id_mon == "2204" || instrument_id_mon == "2205") && trading_day >= "20211201")
            mpl = 5;
        // http://www.shfe.com.cn/news/notice/911341243.html
        if ((instrument_id_mon == "2202" || instrument_id_mon == "2203") && trading_day >= "20220127")
            mpl = 15;
        // http://www.shfe.com.cn/news/notice/911341404.html
        if ((instrument_id_mon == "2204" || instrument_id_mon == "2205" || instrument_id_mon == "2206" || instrument_id_mon == "2207" || instrument_id_mon == "2208" || instrument_id_mon == "2209") && trading_day >= "20220310")
            mpl = 20;
        // http://www.shfe.com.cn/news/notice/911342054.html
        if ((instrument_id_mon == "2210" || instrument_id_mon == "2211" || instrument_id_mon == "2212" || instrument_id_mon == "2301") && trading_day >= "20220907")
            mpl = 20;
        // http://www.shfe.com.cn/news/notice/911402415.html
        if ((instrument_id_mon == "2302" || instrument_id_mon == "2303" || instrument_id_mon == "2304" || instrument_id_mon == "2305") && trading_day >= "20230119")
            mpl = 10;
        // http://www.shfe.com.cn/news/notice/911402954.html
        if ((instrument_id_mon == "2306" || instrument_id_mon == "2307" || instrument_id_mon == "2308" || instrument_id_mon == "2309") && trading_day >= "20230526")
            mpl = 6;
    }
    else if (instrument_id_alp == "sn")
    {
        // since 20150327; http://www.shfe.com.cn/news/notice/911322340.html
        mpl = 0;
        // http://www.shfe.com.cn/news/notice/911326192.html
        if (instrument_id_mon == "1701" && trading_day >= "20161111")
            mpl = 2;
        // http://www.shfe.com.cn/news/notice/911339494.html
        // http://www.shfe.com.cn/news/notice/911339517.html
        if (trading_day >= "20210302")
            mpl = 1;
        // http://www.shfe.com.cn/news/notice/911339821.html
        if ((instrument_id_mon == "2107" || instrument_id_mon == "2108") && trading_day >= "20210603")
            mpl = 2;
        // http://www.shfe.com.cn/news/notice/911340539.html
        if (instrument_id_mon == "2111" && trading_day >= "20211011")
            mpl = 8;
        // http://www.shfe.com.cn/news/notice/911340644.html
        if ((instrument_id_mon == "2111" || instrument_id_mon == "2112") && trading_day >= "20211026")
            mpl = 10;
        // http://www.shfe.com.cn/news/notice/911340660.html
        if ((instrument_id_mon == "2111" || instrument_id_mon == "2112") && trading_day >= "20211029")
            mpl = 15;
        // http://www.shfe.com.cn/news/notice/911340692.html
        if ((instrument_id_mon == "2111" || instrument_id_mon == "2112" || instrument_id_mon == "2201") && trading_day >= "20211108")
            mpl = 20;
        // http://www.shfe.com.cn/news/notice/911341189.html
        if (instrument_id_mon == "2202" && trading_day >= "20220117")
            mpl = 20;
        // http://www.shfe.com.cn/news/notice/911341243.html
        if (instrument_id_mon == "2203" && trading_day >= "20220127")
            mpl = 20;
        // http://www.shfe.com.cn/news/notice/911341404.html
        if ((instrument_id_mon == "2204" || instrument_id_mon == "2205" || instrument_id_mon == "2206" || instrument_id_mon == "2207") && trading_day >= "20220310")
            mpl = 20;
        // http://www.shfe.com.cn/news/notice/911341677.html
        if (instrument_id_mon == "2208" && trading_day >= "20220627")
            mpl = 20;
        // http://www.shfe.com.cn/news/notice/911341712.html
        if ((instrument_id_mon == "2207" || instrument_id_mon == "2208" || instrument_id_mon == "2209") && trading_day >= "20220701")
            mpl = 30;
        // http://www.shfe.com.cn/news/notice/911401786.html
        if ((instrument_id_mon == "2210" || instrument_id_mon == "2211") && trading_day >= "20220923")
            mpl = 20;
        // http://www.shfe.com.cn/news/notice/911401992.html
        if ((instrument_id_mon == "2212" || instrument_id_mon == "2301" || instrument_id_mon == "2302") && trading_day >= "20221115")
            mpl = 10;
        // http://www.shfe.com.cn/news/notice/911402513.html
        if ((instrument_id_mon == "2303" || instrument_id_mon == "2304" || instrument_id_mon == "2305") && trading_day >= "20230210")
            mpl = 6;
        // http://www.shfe.com.cn/news/notice/911402812.html
        if ((instrument_id_mon == "2306" || instrument_id_mon == "2307") && trading_day >= "20230427")
            mpl = 7;
        // http://www.shfe.com.cn/news/notice/911403348.html
        if ((instrument_id_mon == "2308" || instrument_id_mon == "2309") && trading_day >= "20230801")
            mpl = 7;
    }
    else if (instrument_id_alp == "au")
    {
        // http://www.shfe.com.cn/news/notice/8024962.html
        mpl = 0;
        // http://www.shfe.com.cn/news/notice/10243056.html
        if (trading_day >= "20101129")
            mpl = 1;
        // http://www.shfe.com.cn/news/notice/16264564.html
        if (trading_day >= "20110801")
            mpl = 0;
    }
    else if (instrument_id_alp == "ag")
    {
        // http://www.shfe.com.cn/news/notice/2447617.html
        mpl = 0;
        // http://www.shfe.com.cn/news/notice/911323534.html
        if (trading_day >= "20150922")
            mpl = 1;
        // http://www.shfe.com.cn/news/notice/911335013.html
        if (!((instrument_id_mon[2] == '0' && instrument_id_mon[3] == '6') || (instrument_id_mon[2] == '1' && instrument_id_mon[3] == '2')) && trading_day >= "20191014")
            mpl = 0;
        // http://www.shfe.com.cn/news/notice/911337770.html
        if (instrument_id_mon == "2012" && trading_day >= "20200828")
            mpl = 2;
        // http://www.shfe.com.cn/news/notice/911339738.html
        if (trading_day >= "20210518")
            mpl = 1;
    }
    else if (instrument_id_alp == "rb")
    {
        // http://www.shfe.com.cn/news/notice/92235792.html
        mpl = 0;
        // https://www.shfe.com.cn/news/notice/911117578.html
        if (trading_day <= "20091228" && trading_day >= "20091216")
            mpl = 1;
        // http://www.shfe.com.cn/news/notice/10243056.html
        if (trading_day >= "20101129")
            mpl = 1;
        // http://www.shfe.com.cn/news/notice/911319809.html
        if (trading_day >= "20140401")
            mpl = 0;
        // http://www.shfe.com.cn/news/notice/911324709.html
        if (trading_day >= "20160315")
            mpl = 1;
        // http://www.shfe.com.cn/news/notice/911326175.html
        if (instrument_id_mon == "1701" && trading_day >= "20161109")
            mpl = 2;
        // http://www.shfe.com.cn/news/notice/911326192.html
        if ((instrument_id_mon == "1701" || instrument_id_mon == "1705") && trading_day >= "20161111")
            mpl = 4;
        // http://www.shfe.com.cn/news/notice/911326216.html
        if ((instrument_id_mon == "1701" || instrument_id_mon == "1705") && trading_day >= "20161115")
            mpl = 5;
        // http://www.shfe.com.cn/news/notice/911328183.html
        if ((instrument_id_mon == "1710" || instrument_id_mon == "1801") && trading_day >= "20170815")
            mpl = 5;
        // http://www.shfe.com.cn/news/notice/911338606.html
        if (trading_day >= "20201204")
            mpl = 0;
        // http://www.shfe.com.cn/news/notice/911339718.html
        if (instrument_id_mon == "2110" && trading_day >= "20210512")
            mpl = 1;
        // http://www.shfe.com.cn/news/notice/911339738.html
        if (trading_day >= "20210518")
        {
            if (instrument_id_mon == "2110")
                mpl = 2;
            else
                mpl = 1;
        }
        // http://www.shfe.com.cn/news/notice/911339821.html
        if (instrument_id_mon == "2110" && trading_day >= "20210603")
            mpl = 3;
        // http://www.shfe.com.cn/news/notice/911340911.html
        if ((instrument_id_mon == "2201" || instrument_id_mon == "2205") && trading_day >= "20211126")
            mpl = 3;
    }
    else if (instrument_id_alp == "wr")
    {
        // http://www.shfe.com.cn/news/notice/92235792.html
        mpl = 0;
        // http://www.shfe.com.cn/news/notice/10243056.html
        if (trading_day >= "20101129")
            mpl = 1;
        // http://www.shfe.com.cn/news/notice/911331232.html
        if (trading_day >= "20181016")
            mpl = 0;
    }
    else if (instrument_id_alp == "hc")
    {
        // http://www.shfe.com.cn/news/notice/911319760.html
        mpl = 0;
        // http://www.shfe.com.cn/news/notice/911324983.html
        if (trading_day >= "20160425")
            mpl = 1;
        // http://www.shfe.com.cn/news/notice/911326381.html
        if (instrument_id_mon == "1705" && trading_day >= "20161213")
            mpl = 3;
        // http://www.shfe.com.cn/news/notice/911328269.html
        if ((instrument_id_mon == "1710" || instrument_id_mon == "1801") && trading_day >= "20170825")
            mpl = 5;
        // http://www.shfe.com.cn/news/notice/911338606.html
        if (trading_day >= "20201204")
            mpl = 0;
        // http://www.shfe.com.cn/news/notice/911339738.html
        if (trading_day >= "20210518")
            mpl = 1;
        // http://www.shfe.com.cn/news/notice/911339718.html
        // http://www.shfe.com.cn/news/notice/911339738.html
        // http://www.shfe.com.cn/news/notice/911339821.html
        if (instrument_id_mon == "2110")
        {
            if (trading_day >= "20210603")
                mpl = 3;
            else if (trading_day >= "20210518")
                mpl = 2;
            else if (trading_day >= "20210512")
                mpl = 1;
        }
        // http://www.shfe.com.cn/news/notice/911340911.html
        if ((instrument_id_mon == "2201" || instrument_id_mon == "2205") && trading_day >= "20211126")
            mpl = 3;
    }
    else if (instrument_id_alp == "fu")
    {
        // http://www.shfe.com.cn/news/notice/4742466.html
        mpl = 0;
        // http://www.shfe.com.cn/news/notice/10243056.html
        if (trading_day >= "20101129")
            mpl = 1;
        // http://www.shfe.com.cn/news/notice/911330669.html
        if (trading_day >= "20180716")
            mpl = 0;
        // http://www.shfe.com.cn/news/notice/911337117.html
        if (instrument_id_mon == "2009" && trading_day >= "20200609")
            mpl = 1;
        // http://www.shfe.com.cn/news/notice/911339821.html
        if (instrument_id_mon == "2109" && trading_day >= "20210603")
            mpl = 1;
        // http://www.shfe.com.cn/news/notice/911340676.html
        // http://www.shfe.com.cn/news/notice/911340692.html
        if (instrument_id_mon == "2201")
        {
            if (trading_day >= "20211108")
                mpl = 15;
            else if (trading_day >= "20211102")
                mpl = 5;
        }
        // http://www.shfe.com.cn/news/notice/911340977.html
        if (instrument_id_mon == "2205" && trading_day >= "20211203")
            mpl = 15;
        // http://www.shfe.com.cn/news/notice/911341527.html
        if (instrument_id_mon == "2209" && trading_day >= "20220429")
            mpl = 5;
        // http://www.shfe.com.cn/news/notice/911401786.html
        if (instrument_id_mon == "2301" && trading_day >= "20220923")
            mpl = 5;
        // http://www.shfe.com.cn/news/notice/911402632.html
        if (instrument_id_mon == "2305" && trading_day >= "20230322")
            mpl = 3;
        // http://www.shfe.com.cn/news/notice/911402937.html
        if (instrument_id_mon == "2309" && trading_day >= "20230523")
            mpl = 2;
    }
    else if (instrument_id_alp == "bu")
    {
        // http://www.shfe.com.cn/news/notice/38235956.html
        mpl = 0;
        // http://www.shfe.com.cn/news/notice/911323534.html
        if (trading_day >= "20150922")
            mpl = 1;
        // http://www.shfe.com.cn/news/notice/911326216.html
        if ((instrument_id_mon == "1612" || instrument_id_mon == "1706") && trading_day >= "20161115")
            mpl = 2;
        // http://www.shfe.com.cn/news/notice/911332153.html
        if (instrument_id_mon == "1906" && trading_day >= "20181203")
            mpl = 3;
    }
    else if (instrument_id_alp == "ru")
    {
        mpl = 0;
        // https://www.shfe.com.cn/news/notice/911117578.html
        if (trading_day <= "20091228" && trading_day >= "20091216")
            mpl = 1;
        // https://www.shfe.com.cn/news/notice/6216207.html
        if (trading_day <= "20100827" && trading_day >= "20100802")
            mpl = 1;
        // https://www.shfe.com.cn/news/notice/9226822.html
        // http://www.shfe.com.cn/news/notice/10243056.html since 20101129
        if (trading_day >= "20101025")
            mpl = 1;
        // http://www.shfe.com.cn/news/notice/911326175.html
        // http://www.shfe.com.cn/news/notice/911326192.html
        if (instrument_id_mon == "1701")
        {
            if (trading_day >= "20161111")
                mpl = 5;
            else if (trading_day >= "20161109")
                mpl = 0.100 / 0.045;
        }
        // http://www.shfe.com.cn/news/notice/911326192.html
        if (instrument_id_mon == "1705" && trading_day >= "20161111")
            mpl = 5;
        // http://www.shfe.com.cn/news/notice/911327702.html
        if (instrument_id_mon == "1709" && trading_day >= "20170526")
            mpl = 4;
        // http://www.shfe.com.cn/news/notice/911337331.html
        if (trading_day >= "20200707")
            mpl = 0;
        // http://www.shfe.com.cn/news/notice/911338346.html
        if (instrument_id_mon == "2101" && trading_day >= "20201111")
            mpl = 1;
        // http://www.shfe.com.cn/news/notice/911340676.html
        if (instrument_id_mon == "2201" && trading_day >= "20211102")
            mpl = 5;
        // http://www.shfe.com.cn/news/notice/911340954.html
        if (instrument_id_mon == "2205" && trading_day >= "20211201")
            mpl = 3;
    }
    else if (instrument_id_alp == "sp")
    {
        // http://www.shfe.com.cn/news/notice/911331902.html
        mpl = 0;
        // http://www.shfe.com.cn/news/notice/911340977.html
        // http://www.shfe.com.cn/news/notice/911341032.html
        if (instrument_id_mon == "2112" || instrument_id_mon == "2201" || instrument_id_mon == "2202" || instrument_id_mon == "2203")
        {
            if (trading_day >= "20211213")
                mpl = 5;
            else if (trading_day >= "20211203")
                mpl = 3;
        }
        // http://www.shfe.com.cn/news/notice/911341032.html
        if ((instrument_id_mon == "2204" || instrument_id_mon == "2205") && trading_day >= "20211213")
            mpl = 5;
    }
    else if (instrument_id_alp == "ss")
    {
        // http://www.shfe.com.cn/news/notice/911334944.html
        mpl = 1;
        // http://www.shfe.com.cn/news/notice/911337331.html
        if (trading_day >= "20200707")
            mpl = 0;
        // http://www.shfe.com.cn/news/notice/911340096.html
        if (instrument_id_mon == "2108" && trading_day >= "20210726")
            mpl = 1;
        // http://www.shfe.com.cn/news/notice/911340096.html
        // http://www.shfe.com.cn/news/notice/911340138.html
        // http://www.shfe.com.cn/news/notice/911340184.html
        if (instrument_id_mon == "2109")
        {
            if (trading_day >= "20210809")
                mpl = 6;
            else if (trading_day >= "20210803")
                mpl = 3;
            else if (trading_day >= "20210726")
                mpl = 1;
        }
        // http://www.shfe.com.cn/news/notice/911340138.html
        // http://www.shfe.com.cn/news/notice/911340184.html
        // http://www.shfe.com.cn/news/notice/911340421.html
        // http://www.shfe.com.cn/news/notice/911340430.html
        // http://www.shfe.com.cn/news/notice/911340458.html
        if (instrument_id_mon == "2110")
        {
            if (trading_day >= "20210930")
                mpl = 4;
            else if (trading_day >= "20210927")
                mpl = 2;
            else if (trading_day >= "20210923")
                mpl = 9;
            else if (trading_day >= "20210809")
                mpl = 6;
            else if (trading_day >= "20210803")
                mpl = 3;
        }
        // http://www.shfe.com.cn/news/notice/911340421.html
        // http://www.shfe.com.cn/news/notice/911340430.html
        // http://www.shfe.com.cn/news/notice/911340458.html
        if (instrument_id_mon == "2111")
        {
            if (trading_day >= "20210930")
                mpl = 4;
            else if (trading_day >= "20210927")
                mpl = 2;
            else if (trading_day >= "20210923")
                mpl = 9;
        }
        // http://www.shfe.com.cn/news/notice/911340660.html
        if (instrument_id_mon == "2112" && trading_day >= "20211029")
            mpl = 20;
        // http://www.shfe.com.cn/news/notice/911340911.html
        if (instrument_id_mon == "2201" && trading_day >= "20211126")
            mpl = 20;
        // http://www.shfe.com.cn/news/notice/911341032.html
        // http://www.shfe.com.cn/news/notice/911341243.html
        if (instrument_id_mon == "2202")
        {
            if (trading_day >= "20220127")
                mpl = 20;
            else if (trading_day >= "20211213")
                mpl = 5;
        }
        // http://www.shfe.com.cn/news/notice/911341243.html
        if (instrument_id_mon == "2203" && trading_day >= "20220127")
            mpl = 20;
        // http://www.shfe.com.cn/news/notice/911341404.html
        if ((instrument_id_mon == "2204" || instrument_id_mon == "2205" || instrument_id_mon == "2206" || instrument_id_mon == "2207") && trading_day >= "20220310")
            mpl = 20;
    }
    else if (instrument_id_alp == "ao")
    {
        // http://www.shfe.com.cn/news/notice/911403031.html
        mpl = 0;
        // https://www.shfe.com.cn/news/notice/911403576.html
        if (trading_day >= "20230908")
            mpl = 1;
    }
    else if (instrument_id_alp == "br")
    {
        // http://www.shfe.com.cn/news/notice/911403270.html
        mpl = 0;
        // https://www.shfe.com.cn/news/notice/911403576.html
        if (trading_day >= "20230908")
            mpl = 1;
    }
    /* INE */
    else if (instrument_id_alp == "sc")
    {
        // http://www.shfe.com.cn/news/notice/911329893.html
        mpl = 0;
    }
    else if (instrument_id_alp == "nr")
    {
        // http://www.ine.cn/news/notice/1878.html
        mpl = 1;
        // http://www.shfe.com.cn/news/notice/911337330.html
        if (trading_day >= "20200707")
            mpl = 0;
    }
    else if (instrument_id_alp == "lu")
        // http://www.shfe.com.cn/news/notice/911337187.html
        mpl = 1;
    else if (instrument_id_alp == "bc")
        // http://www.shfe.com.cn/news/notice/911338406.html
        mpl = 0;
    else if (instrument_id_alp == "ec")
        // http://www.shfe.com.cn/news/notice/911403434.html
        mpl = 0;
    /* DCE */
    else if (instrument_id_alp == "a")
    {
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1986629/index.html
        mpl = 1;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1986803/index.html
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1986772/index.html
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1986654/index.html
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1986662/index.html
        if (trading_day >= "20030616")
            mpl = 0;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1987748/index.html
        if (trading_day >= "20101129")
            mpl = 1;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/5001374/index.html
        if (trading_day >= "20150309")
            mpl = 0;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/5512822/index.html
        if (trading_day >= "20160426")
            mpl = 1;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6221291/index.html 仅调整日内
        if (instrument_id_mon == "2009" && trading_day >= "20200617")
            mpl = 5;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6304950/index.html
        if (instrument_id_mon == "2207" && trading_day >= "20220301")
            mpl = 3;
    }
    else if (instrument_id_alp == "m")
    {
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1987054/index.html; http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1986975/index.html
        mpl = 1;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1986818/index.html
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1986654/index.html
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1986662/index.html
        if (trading_day >= "20030101")
            mpl = 0;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1987748/index.html
        if (trading_day >= "20101129")
            mpl = 1;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1987842/index.html
        if (trading_day >= "20140415")
            mpl = 0;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/5505722/index.html
        if (trading_day >= "20160516")
            mpl = 1;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6117522/index.html 仅调整日内
        if (trading_day >= "20180822")
            mpl = 0;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6295503/index.html
        if (trading_day >= "20211102")
            mpl = 1;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6306522/index.html
        if (instrument_id_mon == "2205" && trading_day >= "20220315")
            mpl = 2.0*2/1.5 - 1;
    }
    else if (instrument_id_alp == "c")
    {
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1986787/index.html
        mpl = 0;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1987748/index.html
        if (trading_day >= "20101129")
            mpl = 1;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1987954/index.html
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6074031/index.html
        if (trading_day >= "20130909")
            mpl = 0;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6295503/index.html
        if (trading_day >= "20211102")
            mpl = 1;
    }
    else if (instrument_id_alp == "b")
    {
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1986915/index.html
        mpl = 0;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1987748/index.html
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6039650/index.html
        if (trading_day >= "20101129")
            mpl = 1;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6304950/index.html
        if ((instrument_id_mon == "2203" || instrument_id_mon == "2204" || instrument_id_mon == "2205") && trading_day >= "20220301")
            mpl = 3;
    }
    else if (instrument_id_alp == "y")
    {
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/2045798/index.html
        mpl = 0;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1987141/index.html
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1987313/index.html
        if (trading_day >= "20060807")
            mpl = -0.5;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1987095/index.html
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1987299/index.html
        if (trading_day >= "20080526")
            mpl = 0;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1987748/index.html
        if (trading_day >= "20101129")
            mpl = 1;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/5001374/index.html
        if (trading_day >= "20150309")
            mpl = 0;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/5505722/index.html
        if (trading_day >= "20160516")
            mpl = 1;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6117522/index.html 仅调整日内
        if (trading_day >= "20180822")
            mpl = 0;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6295503/index.html
        if (trading_day >= "20211102")
            mpl = 1;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6304950/index.html
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6306522/index.html
        if (instrument_id_mon == "2205")
        {
            if (trading_day >= "20220315")
                mpl = 5;
            else if (trading_day >= "20220301")
                mpl = 3;
        }
    }
    else if (instrument_id_alp == "l")
    {
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/2046518/index.html
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1987103/index.html
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1987299/index.html
        mpl = 0;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1987748/index.html
        if (trading_day >= "20101129")
            mpl = 1;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1987842/index.html
        if (trading_day >= "20140415")
            mpl = 0;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/5512822/index.html
        if (trading_day >= "20160426")
            mpl = 1;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6117522/index.html 仅调整日内
        if (trading_day >= "20180822")
            mpl = 0;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6261878/index.html
        if (trading_day >= "20210104")
            mpl = 1;
    }
    else if (instrument_id_alp == "p")
    {
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/2046638/index.html
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1987103/index.html
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1987299/index.html
        mpl = 0;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1987748/index.html
        if (trading_day >= "20101129")
            mpl = 1;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/5001374/index.html
        if (trading_day >= "20150309")
            mpl = 0;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/5505722/index.html
        if (trading_day >= "20160516")
            mpl = 1;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6117522/index.html 仅调整日内
        if (trading_day >= "20180822")
            mpl = 0;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6231912/index.html 仅调整日内
        if ((instrument_id_mon == "2009" || instrument_id_mon == "2101" || instrument_id_mon == "2105") && trading_day >= "20200803")
            mpl = 1;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6295503/index.html
        if (trading_day >= "20211102")
            mpl = 1;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6304950/index.html
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6306522/index.html
        if (instrument_id_mon == "2205")
        {
            if (trading_day >= "20220315")
                mpl = 7;
            else if(trading_day >= "20220301")
                mpl = 3;
        }
    }
    else if (instrument_id_alp == "v")
    {
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/2046781/index.html
        mpl = 0;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1987748/index.html
        if (trading_day >= "20101129")
            mpl = 1;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1987954/index.html
        if (trading_day >= "20130909")
            mpl = 0;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6261878/index.html
        if (trading_day >= "20210104")
            mpl = 1;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6296111/index.html
        if (instrument_id_mon == "2201" && trading_day >= "20211111")
            mpl = 9;
    }
    else if (instrument_id_alp == "j")
    {
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/2048491/index.html
        mpl = 1;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1987591/index.html
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1987567/index.html
        if (trading_day >= "20110919")
            mpl = 0;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/5503192/index.html
        if (trading_day >= "20160422")
            mpl = 1;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/5513042/index.html 非日内交易手续费标准调整为成交金额的万分之0.6, 日内交易手续费标准维持不变
        if (trading_day >= "20160510")
            mpl = 23;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6001437/index.html 非日内交易手续费标准由成交金额的万分之0.6提高至万分之1.2, 日内交易手续费标准维持成交金额的万分之7.2不变
        if (trading_day >= "20161109")
            mpl = 11;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6034960/index.html 非日内交易手续费标准由成交金额的万分之1.2调整为成交金额的万分之0.6
        if ((instrument_id_mon[2] != '0' || (instrument_id_mon[3] != '1' && instrument_id_mon[3] != '5' && instrument_id_mon[3] != '9')) && trading_day >= "20170417")
            mpl = 1;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6048629/index.html 仅调整日内
        if (instrument_id_mon[2] == '0' && (instrument_id_mon[3] == '1' || instrument_id_mon[3] == '5' || instrument_id_mon[3] == '9') && trading_day >= "20170801")
            mpl = 5;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6080548/index.html 仅调整日内
        if (instrument_id_mon == "1805" && trading_day >= "20171214")
            fee = 9;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6229328/index.html 仅调整日内
        if (instrument_id_mon[2] == '0' && (instrument_id_mon[3] == '1' || instrument_id_mon[3] == '5' || instrument_id_mon[3] == '9') && trading_day >= "20200720")
            mpl = 3;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6289003/index.html
        if (instrument_id_mon[2] == '0' && (instrument_id_mon[3] == '1' || instrument_id_mon[3] == '5' || instrument_id_mon[3] == '9') && trading_day >= "20210824")
            mpl = 1.8;
        if ((instrument_id_mon == "2109" || instrument_id_mon == "2201") && trading_day >= "20210824")
            mpl = 5;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6290677/index.html
        if ((instrument_id_mon == "2110" || instrument_id_mon == "2111" || instrument_id_mon == "2112" || instrument_id_mon == "2201") && trading_day >= "20210909")
            mpl = 1;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6304950/index.html
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6305419/index.html
        if (trading_day >= "20220301")
        {
            if (instrument_id_mon[2] != '0' || (instrument_id_mon[3] != '1' && instrument_id_mon[3] != '5' && instrument_id_mon[3] != '9'))
                mpl = 1.8;
            else if (instrument_id_mon == "2205")
            {
                if (trading_day < "20220308")
                    mpl = 3;
                else
                    mpl = 7;
            }
        }
    }
    else if (instrument_id_alp == "jm")
    {
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/1987494/index.html
        mpl = 0;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/5503192/index.html
        if (trading_day >= "20160422")
            mpl = 1;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/5513042/index.html 非日内交易手续费标准调整为成交金额的万分之0.6, 日内交易手续费标准维持不变
        if (trading_day >= "20160510")
            mpl = 23;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6001437/index.html 非日内交易手续费标准由成交金额的万分之0.6提高至万分之1.2, 日内交易手续费标准维持成交金额的万分之7.2不变
        if (trading_day >= "20161109")
            mpl = 11;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6034960/index.html 非日内交易手续费标准由成交金额的万分之1.2调整为成交金额的万分之0.6
        if ((instrument_id_mon[2] != '0' || (instrument_id_mon[3] != '1' && instrument_id_mon[3] != '5' && instrument_id_mon[3] != '9')) && trading_day >= "20170417")
            mpl = 1;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6048629/index.html 仅调整日内
        if (instrument_id_mon[2] == '0' && (instrument_id_mon[3] == '1' || instrument_id_mon[3] == '5' || instrument_id_mon[3] == '9') && trading_day >= "20170801")
            mpl = 5;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6080548/index.html 仅调整日内
        if (instrument_id_mon == "1805" && trading_day >= "20171214")
            fee = 9;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6229328/index.html 仅调整日内
        if (instrument_id_mon[2] == '0' && (instrument_id_mon[3] == '1' || instrument_id_mon[3] == '5' || instrument_id_mon[3] == '9') && trading_day >= "20200720")
            mpl = 3;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6289003/index.html
        if (instrument_id_mon[2] == '0' && (instrument_id_mon[3] == '1' || instrument_id_mon[3] == '5' || instrument_id_mon[3] == '9') && trading_day >= "20210824")
            mpl = 1.8;
        if ((instrument_id_mon == "2109" || instrument_id_mon == "2201") && trading_day >= "20210824")
            mpl = 5;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6290677/index.html
        if ((instrument_id_mon == "2110" || instrument_id_mon == "2111" || instrument_id_mon == "2112" || instrument_id_mon == "2201") && trading_day >= "20210909")
            mpl = 1;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6304950/index.html
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6305419/index.html
        if (trading_day >= "20220301")
        {
            if (instrument_id_mon[2] != '0' || (instrument_id_mon[3] != '1' && instrument_id_mon[3] != '5' && instrument_id_mon[3] != '9'))
                mpl = 1.8;
            else if (instrument_id_mon == "2205")
            {
                if (trading_day < "20220308")
                    mpl = 3;
                else
                    mpl = 7;
            }
        }
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/8541669/index.html
        if (trading_day >= "20230504")
            mpl = 5;
    }
    else if (instrument_id_alp == "i")
    {
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/2048537/index.html
        mpl = 0;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/5513867/index.html
        if (trading_day >= "20160314")
            mpl = 1;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/5513042/index.html 非日内交易手续费标准调整为成交金额的万分之0.6, 日内交易手续费标准维持不变
        if (trading_day >= "20160510")
            mpl = 9;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6008823/index.html 非日内交易手续费标准由成交金额的万分之0.6调整为成交金额的万分之1.2, 日内交易手续费标准维持成交金额的万分之3不变
        if (trading_day >= "20161111")
            mpl = 4;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6047171/index.html 仅调整日内
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6117522/index.html 仅调整日内
        if (trading_day >= "20170417")
        {
            if (instrument_id_mon[2] == '0' && (instrument_id_mon[3] == '1' || instrument_id_mon[3] == '5' || instrument_id_mon[3] == '9'))
            {
                if (trading_day < "20170725")
                    mpl = 7;
                else if (trading_day < "20180822")
                    mpl = 3;
                else
                    mpl = 1;
            }
            else
                mpl = 1;
        }
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6172534/index.html
        if (instrument_id_mon == "1909" && trading_day >= "20190718")
            mpl = 4;
        if (instrument_id_mon == "2001" && trading_day >= "20190718")
            mpl = 2;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6258635/index.html
        if ((instrument_id_mon == "2101" || instrument_id_mon == "2105" || instrument_id_mon == "2109") && trading_day >= "20201222")
            mpl = 7;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6305419/index.html
        if ((instrument_id_mon == "2203" || instrument_id_mon == "2204" || instrument_id_mon == "2205") && trading_day >= "20220308")
            mpl = 3;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6307719/index.html
        if (instrument_id_mon == "2209" && trading_day >= "20220330")
            mpl = 3;
    }
    else if (instrument_id_alp == "jd")
    {
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/2048617/index.html
        mpl = 1;
    }
    else if (instrument_id_alp == "fb")
    {
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/2048823/index.html
        mpl = 0;
    }
    else if (instrument_id_alp == "bb")
    {
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/2048823/index.html
        mpl = 0;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6295503/index.html
        if (trading_day >= "20211102")
            mpl = 1;
    }
    else if (instrument_id_alp == "pp")
    {
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/2048192/index.html
        mpl = 0;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/5031569/index.html
        if (trading_day >= "20151201")
            mpl = 1;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/5513042/index.html 非日内交易手续费标准调整为成交金额的万分之0.6, 日内交易手续费标准维持不变
        if (trading_day >= "20160510")
            mpl = 7;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6034960/index.html 仅调整日内
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6047171/index.html 仅调整日内
        if (trading_day >= "20170417")
        {
            if (instrument_id_mon[2] == '0' && (instrument_id_mon[3] == '1' || instrument_id_mon[3] == '5' || instrument_id_mon[3] == '9'))
            {
                if (trading_day < "20170725")
                    mpl = 3;
                else
                    mpl = 1;
            }
            else
                mpl = 1;
        }
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6117522/index.html 仅调整日内
        if (trading_day >= "20180822")
            mpl = 0;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6261878/index.html
        if (trading_day >= "20210104")
            mpl = 1;
    }
    else if (instrument_id_alp == "cs")
    {
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/2285936/index.html
        mpl = 0;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/5505722/index.html
        if (trading_day >= "20160516")
            mpl = 1;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6117522/index.html 仅调整日内
        if (trading_day >= "20180822")
            mpl = 0;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6295407/index.html
        if (trading_day >= "20211102")
            mpl = 1;
    }
    else if (instrument_id_alp == "eg")
    {
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6138990/index.html
        mpl = 0;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6295407/index.html
        if (trading_day >= "20211102")
            mpl = 1;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6296111/index.html
        if (instrument_id_mon == "2201" && trading_day >= "20211111")
            mpl = 2.0*8/3 - 1;
    }
    else if (instrument_id_alp == "rr")
    {
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6177470/index.html
        mpl = 1;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6225456/index.html
        if (trading_day >= "20200701")
            mpl = 0;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6295503/index.html
        if (trading_day >= "20211102")
            mpl = 1;
    }
    else if (instrument_id_alp == "eb")
    {
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6188157/index.html
        mpl = 1;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6251679/index.html
        if (instrument_id_mon == "2101" && trading_day >= "20201124")
            mpl = 3;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6265555/index.html 仅调整日内
        if (instrument_id_mon == "2102" && trading_day >= "20210115")
            mpl = 39;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6271459/index.html 仅调整日内
        if (instrument_id_mon == "2105" && trading_day >= "20210310")
            mpl = 3;
    }
    else if (instrument_id_alp == "pg")
    {
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6210512/index.html
        mpl = 1;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6295407/index.html
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6296111/index.html
        if (instrument_id_mon == "2201" && trading_day >= "20211102")
            mpl = 2.0*10/6 - 1;
        if (instrument_id_mon == "2112")
        {
            if (trading_day >= "20211111")
                mpl = 2.0*16/6 - 1;
            else if (trading_day >= "20211102")
                mpl = 2.0*10/6 - 1;
        }
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6302872/index.html
        if (instrument_id_mon == "2202" && trading_day >= "20220125")
            mpl = 2.0*10/6 - 1;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6305419/index.html
        if ((instrument_id_mon == "2203" || instrument_id_mon == "2204" || instrument_id_mon == "2205") && trading_day >= "20220308")
            mpl = 2.0*10/6 - 1;
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6306522/index.html
        if ((instrument_id_mon == "2204" || instrument_id_mon == "2205") && trading_day >= "20220315")
            mpl = 3;
    }
    else if (instrument_id_alp == "lh")
    {
        // http://www.dce.com.cn/dalianshangpin/ywfw/jystz/ywtz/6263003/index.html
        mpl = 3;
    }
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
    else if (instrument_id_alp == "IM")
        mpl = 15;
    else if (instrument_id_alp == "T")
        mpl = 0;
    else if (instrument_id_alp == "TF")
        mpl = 1;
    else if (instrument_id_alp == "TS")
        mpl = 0;
    else if (instrument_id_alp == "TL")
        mpl = 0;
    /* GFEX */
    else if (instrument_id_alp == "si")
        mpl = 1;
    else if (instrument_id_alp == "lc")
        mpl = 0;
    else
        std::cerr << parse_milliseconds(0) << " ERROR TdEngine %% - [transaction_cost] close fees haven't been defined for " << instrument_id_alp << std::endl;
    
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
    // http://www.cffex.com.cn/jystz/20230317/31868.html
    if (trading_day >= "20230320" && (instrument_id_alp == "IH" || instrument_id == "IF" || instrument_id == "IC" || instrument_id == "IM"))
        mpl = 10;

    // http://www.gfex.com.cn/gfex/tzts/202303/0aab06ca146d4c09b5b91eca0074f4f3.shtml
    if (trading_day >= "20230403" && instrument_id_alp == "si")
        mpl = 0;
    
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
