/*
Created on Sep 2018

@author: hufx

Data Structs
*/
#ifndef DATA_STRUCTS_H
#define DATA_STRUCTS_H

struct LFMarketDataField
{
    char  	    TradingDay[9];         //交易日
	char      	InstrumentID[10];      //合约代码
	char   	    ExchangeID[9];         //交易所代码
	char     	ExchangeInstID[10];    //合约在交易所的代码
	double   	LastPrice;             //最新价
	double   	PreSettlementPrice;    //上次结算价
	double   	PreClosePrice;         //昨收盘
	double   	PreOpenInterest;       //昨持仓量
	double   	OpenPrice;             //今开盘
	double   	HighestPrice;          //最高价
	double   	LowestPrice;           //最低价
	int      	Volume;                //数量
	double   	Turnover;              //成交金额
	double   	OpenInterest;          //持仓量
	double   	ClosePrice;            //今收盘
	double   	SettlementPrice;       //本次结算价
	double   	UpperLimitPrice;       //涨停板价
	double   	LowerLimitPrice;       //跌停板价
	double   	PreDelta;              //昨虚实度
	double   	CurrDelta;             //今虚实度
	char      	UpdateTime[9];         //最后修改时间
	int      	UpdateMillisec;        //最后修改毫秒
	double   	BidPrice1;             //申买价一
	int      	BidVolume1;            //申买量一
	double   	AskPrice1;             //申卖价一
	int      	AskVolume1;            //申卖量一
	double   	BidPrice2;             //申买价二
	int      	BidVolume2;            //申买量二
	double   	AskPrice2;             //申卖价二
	int      	AskVolume2;            //申卖量二
	double   	BidPrice3;             //申买价三
	int      	BidVolume3;            //申买量三
	double   	AskPrice3;             //申卖价三
	int      	AskVolume3;            //申卖量三
	double   	BidPrice4;             //申买价四
	int      	BidVolume4;            //申买量四
	double   	AskPrice4;             //申卖价四
	int      	AskVolume4;            //申卖量四
	double   	BidPrice5;             //申买价五
	int      	BidVolume5;            //申买量五
	double   	AskPrice5;             //申卖价五
	int      	AskVolume5;            //申卖量五
	double		AveragePrice;          //当日均价
	char      	ActionDay[9];          //业务日期
};

struct LFRspPositionField
{
	int 		LongPosition;
	int 		ShortPosition;
	double		LongBalance;
	double		ShortBalance;
	double		Cost;
	double		LongPnL;
	double		ShortPnL;
};

struct LFInputOrderField
{
	char        InstrumentID[10];      //合约代码
	double      LimitPrice;            //价格
	int         Volume;                //数量
	char        Direction;         	   //买卖方向
	char 		OffsetFlag;            //开平标志
};

struct LFOrderActionField
{
	char	  	InstrumentID[10];      //合约代码
	char     	ActionFlag;        	   //报单操作标志
	double   	LimitPrice;            //价格
	int      	VolumeChange;          //数量变化
	int      	RequestID;             //请求编号
};

struct LFRtnOrderField
{
	char        InstrumentID[10];      //合约代码
	double      LimitPrice;            //价格
	int         VolumeTraded;          //今成交数量
	int         VolumeTotal;           //剩余数量
	int         VolumeTotalOriginal;   //数量
	char      	Direction;         	   //买卖方向
	char       	OffsetFlag;        	   //开平标志
	char      	OrderStatus;           //报单状态
	int         RequestID;             //请求编号
};

struct LFRtnTradeField
{
	char        InstrumentID[10];      //合约代码
	double      Price;                 //价格
	int         Volume;                //数量
	char   		Direction;         	   //买卖方向
	char  		OffsetFlag;            //开平标志
};


struct OrderField
{
	char 		StartTime[24];
	char 		StartFlag[10];
	char 		OrderType[10];
	int			OrderId;
	double 		OrderPrc;
	int 		OrderVol;
	double 		AheadVol;
	double 		FillPrc;
	int 		FillVol;
	double 		FillAmt;
	int 		OrderDur;
	int 		FillDur;
	double 		TxnCost;
	double 		PnL;
	int 		CloseOut;
	char 		EndFlag[10];
	char 		EndTime[24];
};

struct FillField
{
	int 		BuyVol;
	int			SellVol;
	int 		AskVol;
	int 		BidVol;
	int 		PreAskVol;
	int 		PreBidVol;
};

#endif