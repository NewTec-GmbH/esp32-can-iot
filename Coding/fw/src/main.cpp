/***************************************************************************************************
  (c) NewTec GmbH 2020   -   www.newtec.de
  $URL: https://github.com/NewTec-GmbH/esp32-can-iot $
***************************************************************************************************/
/**
@addtogroup Application
@{
@file       main.cpp

Main Application

* @}
***************************************************************************************************/
/* INCLUDES ***************************************************************************************/
#include <Arduino.h>
#include "Lawicel.h"
#include "SerialAdapter.h"
#include "CANAdapter.h"
#include "NVMAdapter.h"
#include "WSAdapter.h"
#include "Board.h"
#include "WLAN.h"

/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/

/* VARIABLES **************************************************************************************/
SerialAdapter serialAdapter;
CANAdapter sja1000Adapter;
NVMAdapter flashAdapter;
WSAdapter websocketadapter;
//Lawicel protocolLawicel(serialAdapter, sja1000Adapter, flashAdapter);
Lawicel protocolLawicel(websocketadapter, sja1000Adapter, flashAdapter);

/* PUBLIC METHODES ********************************************************************************/
void setup()
{
  Board::init();
  if (!protocolLawicel.begin())
  {
    Board::haltSystem();
  }
  else
  {
    Serial.println(wlan::getIPAddress());
  }
}

void loop()
{
  if (!protocolLawicel.executeCycle())
  {
    Board::blinkError(250);
  }
  if (!wlan::checkConnection())
  {
    Board::haltSystem();
  }
  if (ESPServer::isRestartRequested())
  {
    Board::reset();
  }
}

/* PROTECTED METHODES *****************************************************************************/

/* PRIVATE METHODES *******************************************************************************/

/* EXTERNAL FUNCTIONS *****************************************************************************/

/* INTERNAL FUNCTIONS *****************************************************************************/
