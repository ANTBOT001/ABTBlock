/**
 * \class ABTButton
 * \brief   Driver for ultrasonic sensor device.
 * @file    ABTButton.cpp
 * @author  ANTBOT
 * @version V1.0.1
 * @date    2017/9/10
 * @brief   Driver for Me ultrasonic sensor device. 
 */
#include "ABTButton.h"


ABTButton::ABTButton(unsigned char port):ABTPort(port)
{
  _SignalPin = port;
  //s1=pin1();
  //s2=pin2();
}
unsigned char ABTButton::GetButton1()
{
  pinMode(s1, INPUT);
  return digitalRead(s1);
}
unsigned char ABTButton::GetButton2()
{
  pinMode(s2, INPUT);
  return digitalRead(s2);
}

