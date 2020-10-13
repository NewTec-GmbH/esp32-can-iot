/***************************************************************************************************
  (c) NewTec GmbH 2020   -   www.newtec.de
  $URL: https://github.com/NewTec-GmbH/esp32-can-iot $
***************************************************************************************************/
/**
@addtogroup Testing
@{
@file       TestMain.h

Main Test entry point

* @}
***************************************************************************************************/
/* INCLUDES ***************************************************************************************/
#include <unity.h>
#include <stdio.h>
#include <stdlib.h>

#include <Lawicel.h>
#include <Arduino.h>
#include <Print.h>
#include <WString.h>
#include <math.h>
#include <cmath>

#include "test_serial_adapter.h"
#include "test_can_adapter.h"
#include "test_nvm_adapter.h"

testSerial testingSerialAdapter;
testCAN testingCANAdapter;
testNVM testingNVMAdapter;
Lawicel ProtocolTest(&testingSerialAdapter, &testingCANAdapter, &testingNVMAdapter);

void test_can_baudrate(void)
{
  testingSerialAdapter.writeInput("S6");
  ProtocolTest.handler();
  TEST_ASSERT_EQUAL(500E3,testingCANAdapter.getBaudrate());
}

void test_can_btr(void)
{
}

void test_can_open_normal(void)
{
}

void test_can_open_listen_only(void)
{
}

void test_can_close(void)
{
}

void test_tx_std(void)
{
}

void test_tx_ext(void)
{
}

void test_tx_std_rtr(void)
{
}

void test_tx_ext_rtr(void)
{
}

void test_filter_mode(void)
{
}

void test_acn_register(void)
{
}

void test_amn_register(void)
{
}

void test_serial_baudrate(void)
{
}

void test_version(void)
{
}

void test_serialnumber(void)
{
}

void test_timestamp(void)
{
}

void test_autostart(void)
{
}

int main(int argc, char **argv)
{
  

  UNITY_BEGIN();
  RUN_TEST(test_can_baudrate);
  RUN_TEST(test_can_btr);
  RUN_TEST(test_can_open_normal);
  RUN_TEST(test_can_open_listen_only);
  RUN_TEST(test_can_close);
  RUN_TEST(test_tx_std);
  RUN_TEST(test_tx_ext);
  RUN_TEST(test_tx_std_rtr);
  RUN_TEST(test_tx_ext_rtr);
  RUN_TEST(test_acn_register);
  RUN_TEST(test_amn_register);
  RUN_TEST(test_serial_baudrate);
  RUN_TEST(test_version);
  RUN_TEST(test_serialnumber);
  RUN_TEST(test_timestamp);
  RUN_TEST(test_autostart);
  return UNITY_END();
}