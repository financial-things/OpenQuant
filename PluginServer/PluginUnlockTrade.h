#pragma once
#include "Include/FTPluginCore.h"
#include "Include/FTPluginQuoteInterface.h"
#include "Include/FTPluginTradeInterface.h"
#include "Protocol/ProtoDataStruct_Trade.h"
#include "TimerWnd.h"
#include "MsgHandler.h"
#include "JsonCpp/json.h"

class CPluginHKTradeServer;

class CPluginUnlockTrade : public CTimerWndInterface, public CMsgHandlerEventInterface
{
public:
	CPluginUnlockTrade();
	virtual ~CPluginUnlockTrade();
	
	void Init(CPluginHKTradeServer* pTradeServer, ITrade_HK*  pTradeOp);
	void Uninit();	
	void SetTradeReqData(int nCmdID, const Json::Value &jsnVal, SOCKET sock);
	void NotifyOnUnlockTrade(UINT32 nCookie, Trade_SvrResult enSvrRet, UINT64 nErrCode);

protected:
	//CTimerWndInterface 
	virtual void OnTimeEvent(UINT nEventID);

	//CMsgHandlerEventInterface
	virtual void OnMsgEvent(int nEvent,WPARAM wParam,LPARAM lParam);

protected:
	//tomodify 1
	typedef UnlockTrade_Req	TradeReqType;
	typedef UnlockTrade_Ack	TradeAckType;

	struct	StockDataReq
	{
		SOCKET	sock;
		DWORD	dwReqTick;
		DWORD	dwLocalCookie;
		TradeReqType req;
	};
	
	typedef std::vector<StockDataReq*>		VT_REQ_TRADE_DATA;	
	

protected:	
	void HandleTimeoutReq();
	void HandleTradeAck(TradeAckType *pAck, SOCKET	sock);
	void SetTimerHandleTimeout(bool bStartOrStop);
	void ClearAllReqAckData();

private: 
	bool	DoDeleteReqData(StockDataReq* pReq); 

protected:
	CPluginHKTradeServer	*m_pTradeServer;
	ITrade_HK				*m_pTradeOp;	
	BOOL					m_bStartTimerHandleTimeout;
	
	CTimerMsgWndEx		m_TimerWnd;
	CMsgHandler			m_MsgHandler;

	VT_REQ_TRADE_DATA	m_vtReqData;
};