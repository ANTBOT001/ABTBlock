/**
 * \class ABTPort
 * \brief   Port Mapping for RJ25
 * @file    ABTPort.cpp
 * @author  ANTBOT
 * @version V1.0.1
 * @date    2017/09/10
 * @brief   Port Mapping for RJ25 
 */
#include "ABTPort.h"


ABTPort::ABTPort(void)
{
  s1 = _abtPort[0].s1;
  s2 = _abtPort[0].s2;
  _port = 0;
}

ABTPort::ABTPort(uint8_t port)
{
  s1 = _abtPort[port].s1;
  s2 = _abtPort[port].s2;
  _port = port;
}

bool ABTPort::dRead1(void)
{
  bool val;
  pinMode(s1, INPUT);
  val = digitalRead(s1);
  return(val);
}
bool ABTPort::dRead2(void)
{
  bool val;
  pinMode(s2, INPUT);
  val = digitalRead(s2);
  return(val);
}
void ABTPort::dWrite1(bool value)
{
  pinMode(s1, OUTPUT);
  digitalWrite(s1, value);
}

void ABTPort::dWrite2(bool value)
{
  pinMode(s2, OUTPUT);
  digitalWrite(s2, value);
}

int ABTPort::aRead1(void)
{
  int val;
  pinMode(s1, INPUT);
  val = analogRead(s1);
  return(val);
}

int ABTPort::aRead2(void)
{
  int16_t val;
  pinMode(s2, INPUT);
  val = analogRead(s2);
  return(val);
}

void ABTPort::aWrite1(int value)
{
  analogWrite(s1, value);
}

void ABTPort::aWrite2(int value)
{
  analogWrite(s2, value);
}

unsigned char ABTPort::pin1(void)
{
  return(s1);
}

unsigned char ABTPort::pin2(void)
{
  return(s2);
}
