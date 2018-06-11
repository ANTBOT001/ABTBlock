#include <SoftwareSerial.h>
#include "U8glib.h"
#include <dht11.h>
#define DHT11PIN 9
dht11 DHT11;
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE); 
SoftwareSerial mySerial(8,7);
int oldVal=0;
int cnt=0;
const   uint8_t bitmap_s []   U8G_PROGMEM  ={0x00,0x00,0x00,0x00,0xFD,0xFC,0x04,0x84,0x44,0x84,0x44,0x84,0x28,0x88,0x28,0x88,
0x10,0x50,0x10,0x50,0x28,0x20,0x28,0x20,0x44,0x50,0x44,0x88,0x81,0x04,0x02,0x02};/*"双",0*/

const   uint8_t bitmap_y []   U8G_PROGMEM  ={0x00,0x00,0x27,0xFE,0x14,0x20,0x14,0x40,0x85,0xFC,0x45,0x04,0x45,0xFC,0x15,0x04,
0x15,0xFC,0x25,0x24,0xE4,0x20,0x24,0xA8,0x29,0x24,0x2A,0x22,0x30,0xA0,0x00,0x40};/*"源",1*/

const   uint8_t bitmap_d []   U8G_PROGMEM  ={0x01,0x00,0x01,0x00,0x01,0x00,0x3F,0xF8,0x21,0x08,0x21,0x08,0x21,0x08,0x3F,0xF8,
0x21,0x08,0x21,0x08,0x21,0x08,0x3F,0xF8,0x21,0x0A,0x01,0x02,0x01,0x02,0x00,0xFE};/*"电",2*/

const   uint8_t bitmap_z[]    U8G_PROGMEM  ={0x00,0x00,0x7F,0xF8,0x00,0x10,0x00,0x20,0x00,0x40,0x01,0x80,0x01,0x00,0xFF,0xFE,
0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x05,0x00,0x02,0x00};/*"子",3*/
void draw(void) {
  u8g.setFont(u8g_font_unifont);
  // graphic commands to redraw the complete screen should be placed here  
 u8g.drawBitmapP ( 32 , 0 , 2 , 16 , bitmap_s); 
 u8g.drawBitmapP ( 49 , 0 , 2 , 16 , bitmap_y );
 u8g.drawBitmapP ( 66 , 0 , 2 , 16 , bitmap_d); 
 u8g.drawBitmapP ( 83 , 0 , 2 , 16 , bitmap_z );
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(2400);
  mySerial.begin(2400);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  delay(200);
}

void loop() {
  // put your main code here, to run repeatedly:
  char str1[32];
  char str2[32];
  float val_pm25;
  int chk;
  cnt++;
  if(cnt==20)
  cnt=0;
  if(cnt<=10)
  {
    val_pm25 = calcPM25();//夏普PM2.5传感器
  //Serial.println(val_pm25);
    if(val_pm25>0)
        oldVal=(int)val_pm25;
    if(oldVal>999)
        oldVal=999;
    sprintf(str1,"PM2.5:%03d",oldVal);    
    //////////////////////////////////////
    if(oldVal<150)//空气良好：绿色
  {
    digitalWrite(10,1);
    digitalWrite(11,0);
    }else if(oldVal<300)//空气一般：黄色
    {
      analogWrite(10,200);
      analogWrite(11,50);
      }else{//空气差：红色
        digitalWrite(10,0);
        digitalWrite(11,1);
      }    
    //////////////////////////////////////
     u8g.firstPage();  
  do {       
      draw();    
      u8g.setFont(u8g_font_fub17);  
      u8g.drawStr(6, 58,str1);      
      //u8g.drawStr(0, 40,str1);      
  } while( u8g.nextPage() );
    
    }else{
      chk = DHT11.read(DHT11PIN);
      delay(200);
  if(chk==DHTLIB_OK)
  {
    sprintf(str1,"Humi:%d (%%)     ",(int)DHT11.humidity);
    sprintf(str2,"Temp:%d (oC)    ",(int)DHT11.temperature);
    u8g.firstPage();  
  do {       
      draw();      
      u8g.drawStr(0, 56,str1);
      u8g.drawStr(0, 36,str2);
  } while( u8g.nextPage() );
  }
  
     }
  delay(500);
}
float calcPM25()//计算均值，采集5个点，去掉最大最小值，然后求平均数
{
  float val[5],vpm;
  float vmax,vmin,vsum;
  int i,j;
  vsum = 0.0;
  for(i=0;i<5;i++)
  {
    j=0;
    while(1)
    {
      vpm = GetPM25Data_sharp();
      if(vpm>1.0)
      break;
      j++;
      if(j==5)
      return 0.0;
      }
      val[i] = vpm;
      vsum+=vpm;
    }
    vmax = val[0];
    vmin = val[0];
    for(i=0;i<4;i++)
    {
      if(vmax<val[i+1])
      vmax = val[i+1];
      if(vmin>val[i+1])
      vmin = val[i+1];
      }
     vsum-=vmax;
     vsum-=vmin;
     return vsum/3.0; 
 }
float GetPM25Data_sharp()//读取PM2.5传感器,波特率：2400； 校验位：无； 停止位：1 位； 数据位：8；数据包长度为7字节
{
  int cnt,pmval,readcmd[7];
  unsigned char gdata,eFlag,rbytes=0;
  float pm25;
  cnt=0;
   eFlag =0;
  while(mySerial.available()>0)
  //while(Serial.available()>0)
  {
    gdata = mySerial.read();//保存接收字符 
    //gdata = Serial.read();//保存接收字符 
    if(gdata==0xAA&&eFlag==0)
     {
        eFlag=1;        
    }
    if(eFlag==1)
    {
        readcmd[rbytes++]=gdata;
    }    
    delay(2);
    cnt++;
    if(cnt>100)
    return 0;
    if(rbytes==7)//完整帧
    {
      break;
      }   
    }
    if(rbytes==0)
     return 0;
    //if(readcmd[6]!=0xFF)
    // return 0;
  pmval = readcmd[1];
  pmval<<=8;
  pmval+=readcmd[2];
  pm25 = pmval*5.0/1024.0;//计算PM2.5值
  pm25*=800.0;
  if(pm25>999)
  pm25=0;
  return pm25;
}
