/**
 * \class ABTPort
 * \brief   Port Mapping for RJ25
 * @file    ABTPort.h
 * @author  ANTBOT
 * @version V1.0.1
 * @date    2017/09/10
 * @brief   Header for ABTPort.cpp module 
 */
#ifndef ABTPORT_H_
#define ABTPORT_H_

#include <Arduino.h>
/**
 * A structure to represent MePort Signal.
 */
typedef struct
{
  uint8_t s1;
  uint8_t s2;
} ABTPorts;

extern ABTPorts _abtPort[6];  // 
#define PORT_1  (0x00)
#define PORT_2  (0x01)
#define PORT_3  (0x02)
#define PORT_4  (0x03)
#define PORT_5  (0x04)
#define PORT_6  (0x05)

#define FALSE   (0)
#define TRUE    (1)


class ABTPort
{
public:

  ABTPort(void);

  ABTPort(unsigned char port);

  bool dRead1(void);

  bool dRead2(void);
  
  void dWrite1(bool value);

  void dWrite2(bool value);

  int aRead1(void);

  int aRead2(void);

  void aWrite1(int value);

  void aWrite2(int value);

  unsigned char pin1(void);
  unsigned char pin2(void);

protected:


  unsigned char s1;

  unsigned char s2;

  unsigned char _port;

};
#endif 

