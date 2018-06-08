/**
 * \class ABTblutooth
 * \brief   Driver for bluetooth moudle.
 * @file    ABTblutooth.cpp
 * @author  ANTBOT
 * @version V1.0.1
 * @date    2018/2/24
 * @brief   Driver for bluetooth moudle. 
 */
#include <Arduino.h> 
#include <string.h>
#include "SoftwareSerial.h"
#include "ABTBlutooth.h"


SoftwareSerial ABTSerial(4,7);

ABTBlutooth::ABTBlutooth(unsigned char port):ABTPort(port)
{
  _SignalPin = port;
  //s1=pin1();
  //s2=pin2();
}
void ABTBlutooth::ABTINIT()
{
//328P
  ABTSerial =  SoftwareSerial(s2, s1);
	ABTSerial.begin(57600);	//用于和蓝牙模块通讯
	delay(200);

  sprintf( HEADFRAME,"ABT");
  
  frameCnt=0;
  rbytes = 0;
  speedL= speedR=80; 
  senCnt = 0;
}
int ABTBlutooth::ABTGetBleCmd()
{
	unsigned char aFlag=0;
	char rch;
//328P
	while(ABTSerial.available()>0)
  {
  	rch = ABTSerial.read();
    if(rch=='A'&&aFlag==0)//收到字符'A'开始认为是有效数据
  	{
  			aFlag=1;
  	}
  	if(aFlag)
    {
        readcmd[rbytes++]=rch;        
    }
        if(rbytes==4)//接到3个字节后判断帧头
        {
          if(readcmd[1]!='B'||readcmd[2]!='T')
          {
            aFlag=0;rbytes=0;//清除标志
          }          
        }  
    delay(1);
    if(rbytes==64)//最多读64个字节
    break; 
  }
  
	return rbytes;
}
void ABTBlutooth::ABTSendCMD(char *p)
{
	ABTSerial.println(p);	//用于和蓝牙模块通讯

}

void ABTBlutooth::ABTHandleBleCmd()
{
	int i,j;
  i=0;
  char cmdbuff[64];
  j=0;
  senCnt = 0;//计数清0
  for(i=0;i<64;i++)
  {
    if(readcmd[i]!=' ')//忽略空格
    cmdbuff[j++]=readcmd[i];
    if(readcmd[i]=='#')//帧结束标志
    {
      frameCnt++;      
      ABTExpCmd(cmdbuff);
      j=0;
      }    
    }
    memset(readcmd,0,64);//清空接收缓存
		rbytes=0;

		ABTSerial.flush();

}
void ABTBlutooth::ABTExpCmd(char *p)
{
	int i,j;
  char num[3];
  char cmd[32];
  char ctype,cRW;
  char headbuf[4];
  int param[2];//param[0]:管脚号/传感器模块编号 param[1]:值
  for(i=0;i<3;i++)//判断帧头
  {
    if(*p!=HEADFRAME[i])
    return;
    p++;
    }
   ctype= *p++;//命令类型：模拟量/数字量/传感器模块
   cRW  = *p++;//读写操作
  for(j=0;j<2;j++)
  {
    for(i=0;i<3;i++)
    {
      if(*p==','||*p=='#')
      break;      
      num[i]=*p;p++;
    }
    p++;
    param[j]=atoi(num);            
    memset(num,0,3);
  } 
  
  if(ctype=='A')//模拟量读写(PWM)
  {   
#ifdef ABT_WIFI
return;
#endif
       if(param[0]<2)//不控制0和1管脚
  			return;  
        if(cRW=='W')
        {
          sprintf( cmd,"analogWrite(%d,%d);",param[0],param[1]);
          pinMode(param[0],OUTPUT);
          analogWrite(param[0],param[1]);
          }else if(cRW=='R')
          {
            sprintf( cmd,"analogRead(%d,%d);",param[0],param[1]);
            pinMode(param[0],INPUT);
            sprintf(sendcmd,"ABTAR%d,%d#",param[0],analogRead(param[0]));
            ABTSendCMD(sendcmd);
            }
        
        }else if(ctype=='D') //数字量读写
        {
#ifdef ABT_WIFI
return;
#endif
        	if(param[0]<2)//不控制0和1管脚
  				return;  
            if(cRW=='W')
            {
              sprintf( cmd,"digitalWrite(%d,%d);",param[0],param[1]);
              pinMode(param[0],OUTPUT);
              digitalWrite(param[0],param[1]);
              }else if(cRW=='R')
              {
                sprintf( cmd,"digitalRead(%d,%d);",param[0],param[1]);
                pinMode(param[0],INPUT);
                sprintf(sendcmd,"ABTDR%d,%d#",param[0],digitalRead(param[0]));
            		ABTSendCMD(sendcmd); //              
                }
          }else //if(ctype=='S')//传感器操作  
          {
            //SnsrModel(cRW,param[0],param[1]);
            sprintf( cmd,"SensorOperate(%d,%d);",param[0],param[1]);
            ABTSensorFunc(cRW,param[0],param[1]);
            }
}

void ABTBlutooth::ABTSensorFunc(char cRW,int sID,int sVal)//传感器模块处理函数
{
	curInfo.cRW = cRW;
	curInfo.sID = sID;
	curInfo.sVal= sVal;
	if(senCnt==8)
		senCnt=0;
	senInfo[senCnt].cRW = cRW;
	senInfo[senCnt].sID = sID;
	senInfo[senCnt++].sVal = sVal;
	
}
