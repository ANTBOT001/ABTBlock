/** 
 * \brief   Driver for BaseBoard.
 * \file    ABTBase.h
 * @author  ANTBOT
 * @version V1.0.0
 * @date    2017/09/10
 * @brief   Driver for BaseBoard. 
 */
#ifndef ABTBase_H
#define ABTBase_H

#include <Arduino.h>
#include "ABTPort.h"
#include "ABTUltrasonicSensor.h"

ABTPorts _abtPort[6] =
{
    {3, 2}, {9, 8}, {11, 0}, {6, 5}, {A3, A2}, {A1, A0}
};


#endif // ABTBase_H

