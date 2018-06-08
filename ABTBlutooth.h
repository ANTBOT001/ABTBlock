/**
 * \class ABTblutooth
 * \brief   Driver for bluetooth moudle.
 * @file    ABTblutooth.h
 * @author  ANTBOT
 * @version V1.0.1
 * @date    2018/2/24
 * @brief   Driver for bluetooth moudle. 
 */
#ifndef ABTBLUTOOTH_H
#define ABTBLUTOOTH_H


#include <Arduino.h>
#include "ABTPort.h"

struct infoFrmBle{
	char cRW;
	int sID;
	int sVal;
	};


class ABTBlutooth : public ABTPort
{
public:

  ABTBlutooth(uint8_t port);  
	void ABTINIT();
		int ABTGetBleCmd();//接收蓝牙指令
		void ABTHandleBleCmd();//处理蓝牙指令
	  void ABTSendCMD(char *p);//向蓝牙发送指令
	  void ABTSimple();//透传测试
	  
	  void ABTPrint();
	  
	  void ABTSensorFunc(char cRW,int sID,int sVal);//传感器模块处理函数
public:
		char readcmd[64];//接收到的蓝牙数据缓存
		char sendcmd[32];//发送缓存
		int  speedL;
		int  speedR;
		infoFrmBle curInfo;		
		infoFrmBle senInfo[8];//传感器指令缓存
		unsigned char senCnt;	
	private:
		void ABTExpCmd(char * p);//解析单条帧命令
		void ABTSprint(char *p);//调试接口
		
	private:	
		
		char HEADFRAME[4];//帧头
		int frameCnt;//接收帧计数
		int rbytes;	
private:
  unsigned char  _SignalPin;
};

#endif 

