/** 
 * \brief   Driver for Button module.
 * @file    ABTButton.h
 * @author  ANTBOT
 * @version V1.0.0
 * @date    2017/09/10
 * @brief   Header for for ABTButton.cpp module 
 */
#ifndef ABTBUTTON_H
#define ABTBUTTON_H


#include <Arduino.h>
#include "ABTPort.h"



class ABTButton : public ABTPort
{
public:

  ABTButton(uint8_t port);
  unsigned char GetButton1();
  unsigned char GetButton2();
private:
  unsigned char  _SignalPin;
};

#endif 

