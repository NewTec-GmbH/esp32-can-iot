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
#include <Lawicel.h>
#include <SerialAdapter.h>
#include <CANAdapter.h>
#include <NVMAdapter.h>
#include <ESP_Server.h>
#include <Settings.h>
#include <io.h>
#include <Board.h>

/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/

/* VARIABLES **************************************************************************************/
SerialAdapter serialAdapter;
CANAdapter sja1000Adapter;
NVMAdapter flashAdapter;
Lawicel protocolLawicel(serialAdapter, sja1000Adapter, flashAdapter);

/* PUBLIC METHODES ********************************************************************************/
void restart();

void setup()
{
  Board::init();
  if (!protocolLawicel.begin())
  {
    restart();
  }
  else if (!ESPServer::begin())
  {
    restart();
  }
}

void loop()
{
  protocolLawicel.executeCycle();
  if (ESPServer::handleNextRequest())
  {
    restart();
  }
}

/* PROTECTED METHODES *****************************************************************************/

/* PRIVATE METHODES *******************************************************************************/

/* EXTERNAL FUNCTIONS *****************************************************************************/

/* INTERNAL FUNCTIONS *****************************************************************************/

void restart()
{
  protocolLawicel.end();
  ESPServer::end();
  Board::reset();
}