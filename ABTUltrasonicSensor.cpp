/**
 * \class ABTUltrasonicSensor
 * \brief   Driver for ultrasonic sensor device.
 * @file    ABTUltrasonicSensor.cpp
 * @author  ANTBOT
 * @version V1.0.1
 * @date    2017/9/10
 * @brief   Driver for Me ultrasonic sensor device. 
 */
#include "ABTUltrasonicSensor.h"


ABTUltrasonicSensor::ABTUltrasonicSensor(unsigned char port):ABTPort(port)
{
  _SignalPin = port;
  //s1=pin1();
  //s2=pin2();
}
double ABTUltrasonicSensor::distanceCm(int MAXcm)
{
  long distance = measure(MAXcm * 55 + 200);
  return( (double)distance / 58.0);
}

long ABTUltrasonicSensor::measure(unsigned long timeout)
{
  long duration;
  ABTPort::dWrite1(LOW);
  delayMicroseconds(2);
  ABTPort::dWrite1(HIGH);
  delayMicroseconds(10);
  ABTPort::dWrite1(LOW);
  pinMode(s2, INPUT);
  duration = pulseIn(s2, HIGH, timeout);
  delayMicroseconds(200);
  return(duration);
}

