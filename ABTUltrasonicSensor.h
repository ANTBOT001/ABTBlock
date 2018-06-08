/** 
 * \brief   Driver for ultrasonic sensor device.
 * @file    ABTUltrasonicSensor.h
 * @author  ANTBOT
 * @version V1.0.0
 * @date    2017/09/10
 * @brief   Header for for ABTUltrasonicSensor.cpp module 
 */
#ifndef ABTUltrasonicSensor_H
#define ABTUltrasonicSensor_H


#include <Arduino.h>
#include "ABTPort.h"



class ABTUltrasonicSensor : public ABTPort
{
public:

  ABTUltrasonicSensor(unsigned char port);
  double distanceCm(int MAXcm = 400);
  long measure(unsigned long timeout = 30000);
private:
  unsigned char  _SignalPin;
};

#endif 

