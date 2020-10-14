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
  testingSerialAdapter.writeInput("S0");
  ProtocolTest.handler();
  TEST_ASSERT_EQUAL(10E3, testingCANAdapter.getBaudrate());

  testingSerialAdapter.writeInput("S1");
  ProtocolTest.handler();
  TEST_ASSERT_EQUAL(20E3, testingCANAdapter.getBaudrate());

  testingSerialAdapter.writeInput("S2");
  ProtocolTest.handler();
  TEST_ASSERT_EQUAL(50E3, testingCANAdapter.getBaudrate());

  testingSerialAdapter.writeInput("S3");
  ProtocolTest.handler();
  TEST_ASSERT_EQUAL(100E3, testingCANAdapter.getBaudrate());

  testingSerialAdapter.writeInput("S4");
  ProtocolTest.handler();
  TEST_ASSERT_EQUAL(125E3, testingCANAdapter.getBaudrate());

  testingSerialAdapter.writeInput("S5");
  ProtocolTest.handler();
  TEST_ASSERT_EQUAL(250E3, testingCANAdapter.getBaudrate());

  testingSerialAdapter.writeInput("S6");
  ProtocolTest.handler();
  TEST_ASSERT_EQUAL(500E3, testingCANAdapter.getBaudrate());

  testingSerialAdapter.writeInput("S7");
  ProtocolTest.handler();
  TEST_ASSERT_EQUAL(800E3, testingCANAdapter.getBaudrate());

  testingSerialAdapter.writeInput("S8");
  ProtocolTest.handler();
  TEST_ASSERT_EQUAL(1000E3, testingCANAdapter.getBaudrate());
}

void test_can_btr(void)
{
  testingSerialAdapter.writeInput("s0000");
  TEST_ASSERT_TRUE(ProtocolTest.handler());
  TEST_ASSERT_EQUAL(0x00, testingCANAdapter.m_BTR0);
  TEST_ASSERT_EQUAL(0x00, testingCANAdapter.m_BTR1);

  testingSerialAdapter.writeInput("s031C");
  TEST_ASSERT_TRUE(ProtocolTest.handler());
  TEST_ASSERT_EQUAL(0x03, testingCANAdapter.m_BTR0);
  TEST_ASSERT_EQUAL(0x1C, testingCANAdapter.m_BTR1);

  testingSerialAdapter.writeInput("sFFFF");
  TEST_ASSERT_TRUE(ProtocolTest.handler());
  TEST_ASSERT_EQUAL(0xFF, testingCANAdapter.m_BTR0);
  TEST_ASSERT_EQUAL(0xFF, testingCANAdapter.m_BTR1);

  testingSerialAdapter.writeInput("s00000");
  TEST_ASSERT_FALSE(ProtocolTest.handler());

  testingSerialAdapter.writeInput("s000");
  TEST_ASSERT_FALSE(ProtocolTest.handler());
}

void test_can_open_normal(void)
{
  testingCANAdapter.m_currentstate = CANInterface::CLOSED;
  testingSerialAdapter.writeInput("O");
  TEST_ASSERT_TRUE(ProtocolTest.handler());
  TEST_ASSERT_EQUAL(1, testingCANAdapter.getChannelState());

  testingCANAdapter.m_currentstate = CANInterface::CLOSED;
  testingSerialAdapter.writeInput("O0");
  TEST_ASSERT_FALSE(ProtocolTest.handler());
  TEST_ASSERT_EQUAL(0, testingCANAdapter.getChannelState());

  testingCANAdapter.m_currentstate = CANInterface::NORMAL;
  testingSerialAdapter.writeInput("O");
  TEST_ASSERT_FALSE(ProtocolTest.handler());
  TEST_ASSERT_EQUAL(1, testingCANAdapter.getChannelState());

  testingCANAdapter.m_currentstate = CANInterface::LISTEN_ONLY;
  testingSerialAdapter.writeInput("O");
  TEST_ASSERT_FALSE(ProtocolTest.handler());
  TEST_ASSERT_EQUAL(2, testingCANAdapter.getChannelState());
}

void test_can_open_listen_only(void)
{
  testingCANAdapter.m_currentstate = CANInterface::CLOSED;
  testingSerialAdapter.writeInput("L");
  TEST_ASSERT_TRUE(ProtocolTest.handler());
  TEST_ASSERT_EQUAL(2, testingCANAdapter.getChannelState());

  testingCANAdapter.m_currentstate = CANInterface::CLOSED;
  testingSerialAdapter.writeInput("L0");
  TEST_ASSERT_FALSE(ProtocolTest.handler());
  TEST_ASSERT_EQUAL(0, testingCANAdapter.getChannelState());

  testingCANAdapter.m_currentstate = CANInterface::NORMAL;
  testingSerialAdapter.writeInput("L");
  TEST_ASSERT_FALSE(ProtocolTest.handler());
  TEST_ASSERT_EQUAL(1, testingCANAdapter.getChannelState());

  testingCANAdapter.m_currentstate = CANInterface::LISTEN_ONLY;
  testingSerialAdapter.writeInput("L");
  TEST_ASSERT_FALSE(ProtocolTest.handler());
  TEST_ASSERT_EQUAL(2, testingCANAdapter.getChannelState());
}

void test_can_close(void)
{
  testingCANAdapter.m_currentstate = CANInterface::NORMAL;
  testingSerialAdapter.writeInput("C");
  TEST_ASSERT_TRUE(ProtocolTest.handler());
  TEST_ASSERT_EQUAL(0, testingCANAdapter.getChannelState());

  testingCANAdapter.setState(CANInterface::LISTEN_ONLY);
  testingSerialAdapter.writeInput("C");
  TEST_ASSERT_TRUE(ProtocolTest.handler());
  TEST_ASSERT_EQUAL(0, testingCANAdapter.getChannelState());

  testingCANAdapter.m_currentstate = CANInterface::NORMAL;
  testingSerialAdapter.writeInput("C0");
  TEST_ASSERT_FALSE(ProtocolTest.handler());
  TEST_ASSERT_EQUAL(1, testingCANAdapter.getChannelState());

  testingCANAdapter.m_currentstate = CANInterface::LISTEN_ONLY;
  testingSerialAdapter.writeInput("L0");
  TEST_ASSERT_FALSE(ProtocolTest.handler());
  TEST_ASSERT_EQUAL(2, testingCANAdapter.getChannelState());
}

void test_tx_std(void)
{
  testingCANAdapter.clearOutputframe();
  testingCANAdapter.m_currentstate = CANInterface::NORMAL;
  testingSerialAdapter.writeInput("t0000");
  TEST_ASSERT_TRUE_MESSAGE(ProtocolTest.handler(), "Handler");
  TEST_ASSERT_EQUAL_UINT32_MESSAGE(0x000, testingCANAdapter.m_outputFrame.ID, "ID");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.DLC, "DLC");
  TEST_ASSERT_FALSE_MESSAGE(testingCANAdapter.m_outputFrame.Extended, "Extended");
  TEST_ASSERT_FALSE_MESSAGE(testingCANAdapter.m_outputFrame.RTR, "RTR");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[0], "DATA0");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[1], "DATA1");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[2], "DATA2");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[3], "DATA3");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[4], "DATA4");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[5], "DATA5");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[6], "DATA6");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[7], "DATA7");

  testingCANAdapter.clearOutputframe();
  testingCANAdapter.m_currentstate = CANInterface::NORMAL;
  testingSerialAdapter.writeInput("t1FF81122334455667788");
  TEST_ASSERT_TRUE_MESSAGE(ProtocolTest.handler(), "Handler");
  TEST_ASSERT_EQUAL_UINT32_MESSAGE(0x1FF, testingCANAdapter.m_outputFrame.ID, "ID");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(8, testingCANAdapter.m_outputFrame.DLC, "DLC");
  TEST_ASSERT_FALSE_MESSAGE(testingCANAdapter.m_outputFrame.Extended, "Extended");
  TEST_ASSERT_FALSE_MESSAGE(testingCANAdapter.m_outputFrame.RTR, "RTR");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0x11, testingCANAdapter.m_outputFrame.Data[0], "DATA0");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0x22, testingCANAdapter.m_outputFrame.Data[1], "DATA1");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0x33, testingCANAdapter.m_outputFrame.Data[2], "DATA2");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0x44, testingCANAdapter.m_outputFrame.Data[3], "DATA3");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0x55, testingCANAdapter.m_outputFrame.Data[4], "DATA4");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0x66, testingCANAdapter.m_outputFrame.Data[5], "DATA5");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0x77, testingCANAdapter.m_outputFrame.Data[6], "DATA6");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0x88, testingCANAdapter.m_outputFrame.Data[7], "DATA7");

  testingCANAdapter.clearOutputframe();
  testingCANAdapter.m_currentstate = CANInterface::NORMAL;
  testingSerialAdapter.writeInput("t1234AABBCCDD");
  TEST_ASSERT_TRUE_MESSAGE(ProtocolTest.handler(), "Handler");
  TEST_ASSERT_EQUAL_UINT32_MESSAGE(0x123, testingCANAdapter.m_outputFrame.ID, "ID");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(4, testingCANAdapter.m_outputFrame.DLC, "DLC");
  TEST_ASSERT_FALSE_MESSAGE(testingCANAdapter.m_outputFrame.Extended, "Extended");
  TEST_ASSERT_FALSE_MESSAGE(testingCANAdapter.m_outputFrame.RTR, "RTR");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0xAA, testingCANAdapter.m_outputFrame.Data[0], "DATA0");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0xBB, testingCANAdapter.m_outputFrame.Data[1], "DATA1");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0xCC, testingCANAdapter.m_outputFrame.Data[2], "DATA2");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0xDD, testingCANAdapter.m_outputFrame.Data[3], "DATA3");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[4], "DATA4");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[5], "DATA5");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[6], "DATA6");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[7], "DATA7");

  testingCANAdapter.clearOutputframe();
  testingCANAdapter.m_currentstate = CANInterface::CLOSED;
  testingSerialAdapter.writeInput("t1234AABBCCDD");
  TEST_ASSERT_FALSE_MESSAGE(ProtocolTest.handler(), "Handler");
  TEST_ASSERT_EQUAL_UINT32_MESSAGE(0x000, testingCANAdapter.m_outputFrame.ID, "ID");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.DLC, "DLC");
  TEST_ASSERT_FALSE_MESSAGE(testingCANAdapter.m_outputFrame.Extended, "Extended");
  TEST_ASSERT_FALSE_MESSAGE(testingCANAdapter.m_outputFrame.RTR, "RTR");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[0], "DATA0");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[1], "DATA1");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[2], "DATA2");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[3], "DATA3");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[4], "DATA4");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[5], "DATA5");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[6], "DATA6");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[7], "DATA7");

  testingCANAdapter.clearOutputframe();
  testingCANAdapter.m_currentstate = CANInterface::LISTEN_ONLY;
  testingSerialAdapter.writeInput("t1234AABBCCDD");
  TEST_ASSERT_FALSE_MESSAGE(ProtocolTest.handler(), "Handler");
  TEST_ASSERT_EQUAL_UINT32_MESSAGE(0x000, testingCANAdapter.m_outputFrame.ID, "ID");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.DLC, "DLC");
  TEST_ASSERT_FALSE_MESSAGE(testingCANAdapter.m_outputFrame.Extended, "Extended");
  TEST_ASSERT_FALSE_MESSAGE(testingCANAdapter.m_outputFrame.RTR, "RTR");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[0], "DATA0");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[1], "DATA1");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[2], "DATA2");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[3], "DATA3");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[4], "DATA4");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[5], "DATA5");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[6], "DATA6");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[7], "DATA7");
}

void test_tx_ext(void)
{
  testingCANAdapter.clearOutputframe();
  testingCANAdapter.m_currentstate = CANInterface::NORMAL;
  testingSerialAdapter.writeInput("T000000000");
  TEST_ASSERT_TRUE_MESSAGE(ProtocolTest.handler(), "Handler");
  TEST_ASSERT_EQUAL_UINT32_MESSAGE(0x0000000, testingCANAdapter.m_outputFrame.ID, "ID");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.DLC, "DLC");
  TEST_ASSERT_TRUE_MESSAGE(testingCANAdapter.m_outputFrame.Extended, "Extended");
  TEST_ASSERT_FALSE_MESSAGE(testingCANAdapter.m_outputFrame.RTR, "RTR");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[0], "DATA0");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[1], "DATA1");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[2], "DATA2");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[3], "DATA3");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[4], "DATA4");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[5], "DATA5");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[6], "DATA6");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[7], "DATA7");

  testingCANAdapter.clearOutputframe();
  testingCANAdapter.m_currentstate = CANInterface::NORMAL;
  testingSerialAdapter.writeInput("T1FFFFFFF81122334455667788");
  TEST_ASSERT_TRUE_MESSAGE(ProtocolTest.handler(), "Handler");
  TEST_ASSERT_EQUAL_UINT32_MESSAGE(0x1FFFFFFF, testingCANAdapter.m_outputFrame.ID, "ID");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(8, testingCANAdapter.m_outputFrame.DLC, "DLC");
  TEST_ASSERT_TRUE_MESSAGE(testingCANAdapter.m_outputFrame.Extended, "Extended");
  TEST_ASSERT_FALSE_MESSAGE(testingCANAdapter.m_outputFrame.RTR, "RTR");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0x11, testingCANAdapter.m_outputFrame.Data[0], "DATA0");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0x22, testingCANAdapter.m_outputFrame.Data[1], "DATA1");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0x33, testingCANAdapter.m_outputFrame.Data[2], "DATA2");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0x44, testingCANAdapter.m_outputFrame.Data[3], "DATA3");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0x55, testingCANAdapter.m_outputFrame.Data[4], "DATA4");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0x66, testingCANAdapter.m_outputFrame.Data[5], "DATA5");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0x77, testingCANAdapter.m_outputFrame.Data[6], "DATA6");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0x88, testingCANAdapter.m_outputFrame.Data[7], "DATA7");

  testingCANAdapter.clearOutputframe();
  testingCANAdapter.m_currentstate = CANInterface::NORMAL;
  testingSerialAdapter.writeInput("T0000ABCD411223344");
  TEST_ASSERT_TRUE_MESSAGE(ProtocolTest.handler(), "Handler");
  TEST_ASSERT_EQUAL_UINT32_MESSAGE(0x0000ABCD, testingCANAdapter.m_outputFrame.ID, "ID");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(4, testingCANAdapter.m_outputFrame.DLC, "DLC");
  TEST_ASSERT_TRUE_MESSAGE(testingCANAdapter.m_outputFrame.Extended, "Extended");
  TEST_ASSERT_FALSE_MESSAGE(testingCANAdapter.m_outputFrame.RTR, "RTR");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0x11, testingCANAdapter.m_outputFrame.Data[0], "DATA0");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0x22, testingCANAdapter.m_outputFrame.Data[1], "DATA1");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0x33, testingCANAdapter.m_outputFrame.Data[2], "DATA2");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0x44, testingCANAdapter.m_outputFrame.Data[3], "DATA3");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[4], "DATA4");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[5], "DATA5");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[6], "DATA6");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[7], "DATA7");

  testingCANAdapter.clearOutputframe();
  testingCANAdapter.m_currentstate = CANInterface::CLOSED;
  testingSerialAdapter.writeInput("T0000ABCD411223344");
  TEST_ASSERT_FALSE_MESSAGE(ProtocolTest.handler(), "Handler");
  TEST_ASSERT_EQUAL_UINT32_MESSAGE(0x00000000, testingCANAdapter.m_outputFrame.ID, "ID");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.DLC, "DLC");
  TEST_ASSERT_FALSE_MESSAGE(testingCANAdapter.m_outputFrame.Extended, "Extended");
  TEST_ASSERT_FALSE_MESSAGE(testingCANAdapter.m_outputFrame.RTR, "RTR");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[0], "DATA0");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[1], "DATA1");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[2], "DATA2");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[3], "DATA3");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[4], "DATA4");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[5], "DATA5");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[6], "DATA6");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[7], "DATA7");

  testingCANAdapter.clearOutputframe();
  testingCANAdapter.m_currentstate = CANInterface::LISTEN_ONLY;
  testingSerialAdapter.writeInput("T0000ABCD411223344");
  TEST_ASSERT_FALSE_MESSAGE(ProtocolTest.handler(), "Handler");
  TEST_ASSERT_EQUAL_UINT32_MESSAGE(0x00000000, testingCANAdapter.m_outputFrame.ID, "ID");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.DLC, "DLC");
  TEST_ASSERT_FALSE_MESSAGE(testingCANAdapter.m_outputFrame.Extended, "Extended");
  TEST_ASSERT_FALSE_MESSAGE(testingCANAdapter.m_outputFrame.RTR, "RTR");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[0], "DATA0");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[1], "DATA1");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[2], "DATA2");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[3], "DATA3");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[4], "DATA4");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[5], "DATA5");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[6], "DATA6");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[7], "DATA7");
}

void test_tx_std_rtr(void)
{
  testingCANAdapter.clearOutputframe();
  testingCANAdapter.m_currentstate = CANInterface::NORMAL;
  testingSerialAdapter.writeInput("r0000");
  TEST_ASSERT_TRUE_MESSAGE(ProtocolTest.handler(), "Handler");
  TEST_ASSERT_EQUAL_UINT32_MESSAGE(0x000, testingCANAdapter.m_outputFrame.ID, "ID");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.DLC, "DLC");
  TEST_ASSERT_FALSE_MESSAGE(testingCANAdapter.m_outputFrame.Extended, "Extended");
  TEST_ASSERT_TRUE_MESSAGE(testingCANAdapter.m_outputFrame.RTR, "RTR");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[0], "DATA0");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[1], "DATA1");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[2], "DATA2");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[3], "DATA3");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[4], "DATA4");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[5], "DATA5");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[6], "DATA6");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[7], "DATA7");

  testingCANAdapter.clearOutputframe();
  testingCANAdapter.m_currentstate = CANInterface::NORMAL;
  testingSerialAdapter.writeInput("r00081122334455667788");
  TEST_ASSERT_FALSE_MESSAGE(ProtocolTest.handler(), "Handler");
  TEST_ASSERT_EQUAL_UINT32_MESSAGE(0x000, testingCANAdapter.m_outputFrame.ID, "ID");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.DLC, "DLC");
  TEST_ASSERT_FALSE_MESSAGE(testingCANAdapter.m_outputFrame.Extended, "Extended");
  TEST_ASSERT_FALSE_MESSAGE(testingCANAdapter.m_outputFrame.RTR, "RTR");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[0], "DATA0");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[1], "DATA1");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[2], "DATA2");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[3], "DATA3");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[4], "DATA4");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[5], "DATA5");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[6], "DATA6");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[7], "DATA7");

  testingCANAdapter.clearOutputframe();
  testingCANAdapter.m_currentstate = CANInterface::NORMAL;
  testingSerialAdapter.writeInput("r1FF8");
  TEST_ASSERT_TRUE_MESSAGE(ProtocolTest.handler(), "Handler");
  TEST_ASSERT_EQUAL_UINT32_MESSAGE(0x1FF, testingCANAdapter.m_outputFrame.ID, "ID");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(8, testingCANAdapter.m_outputFrame.DLC, "DLC");
  TEST_ASSERT_FALSE_MESSAGE(testingCANAdapter.m_outputFrame.Extended, "Extended");
  TEST_ASSERT_TRUE_MESSAGE(testingCANAdapter.m_outputFrame.RTR, "RTR");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[0], "DATA0");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[1], "DATA1");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[2], "DATA2");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[3], "DATA3");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[4], "DATA4");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[5], "DATA5");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[6], "DATA6");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[7], "DATA7");

  testingCANAdapter.clearOutputframe();
  testingCANAdapter.m_currentstate = CANInterface::NORMAL;
  testingSerialAdapter.writeInput("r1234");
  TEST_ASSERT_TRUE_MESSAGE(ProtocolTest.handler(), "Handler");
  TEST_ASSERT_EQUAL_UINT32_MESSAGE(0x123, testingCANAdapter.m_outputFrame.ID, "ID");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(4, testingCANAdapter.m_outputFrame.DLC, "DLC");
  TEST_ASSERT_FALSE_MESSAGE(testingCANAdapter.m_outputFrame.Extended, "Extended");
  TEST_ASSERT_TRUE_MESSAGE(testingCANAdapter.m_outputFrame.RTR, "RTR");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[0], "DATA0");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[1], "DATA1");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[2], "DATA2");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[3], "DATA3");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[4], "DATA4");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[5], "DATA5");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[6], "DATA6");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[7], "DATA7");

  testingCANAdapter.clearOutputframe();
  testingCANAdapter.m_currentstate = CANInterface::CLOSED;
  testingSerialAdapter.writeInput("r1234AABBCCDD");
  TEST_ASSERT_FALSE_MESSAGE(ProtocolTest.handler(), "Handler");
  TEST_ASSERT_EQUAL_UINT32_MESSAGE(0x000, testingCANAdapter.m_outputFrame.ID, "ID");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.DLC, "DLC");
  TEST_ASSERT_FALSE_MESSAGE(testingCANAdapter.m_outputFrame.Extended, "Extended");
  TEST_ASSERT_FALSE_MESSAGE(testingCANAdapter.m_outputFrame.RTR, "RTR");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[0], "DATA0");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[1], "DATA1");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[2], "DATA2");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[3], "DATA3");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[4], "DATA4");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[5], "DATA5");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[6], "DATA6");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[7], "DATA7");

  testingCANAdapter.clearOutputframe();
  testingCANAdapter.m_currentstate = CANInterface::LISTEN_ONLY;
  testingSerialAdapter.writeInput("r1234AABBCCDD");
  TEST_ASSERT_FALSE_MESSAGE(ProtocolTest.handler(), "Handler");
  TEST_ASSERT_EQUAL_UINT32_MESSAGE(0x000, testingCANAdapter.m_outputFrame.ID, "ID");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.DLC, "DLC");
  TEST_ASSERT_FALSE_MESSAGE(testingCANAdapter.m_outputFrame.Extended, "Extended");
  TEST_ASSERT_FALSE_MESSAGE(testingCANAdapter.m_outputFrame.RTR, "RTR");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[0], "DATA0");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[1], "DATA1");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[2], "DATA2");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[3], "DATA3");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[4], "DATA4");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[5], "DATA5");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[6], "DATA6");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[7], "DATA7");
}

void test_tx_ext_rtr(void)
{
  testingCANAdapter.clearOutputframe();
  testingCANAdapter.m_currentstate = CANInterface::NORMAL;
  testingSerialAdapter.writeInput("R000000000");
  TEST_ASSERT_TRUE_MESSAGE(ProtocolTest.handler(), "Handler");
  TEST_ASSERT_EQUAL_UINT32_MESSAGE(0x0000000, testingCANAdapter.m_outputFrame.ID, "ID");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.DLC, "DLC");
  TEST_ASSERT_TRUE_MESSAGE(testingCANAdapter.m_outputFrame.Extended, "Extended");
  TEST_ASSERT_TRUE_MESSAGE(testingCANAdapter.m_outputFrame.RTR, "RTR");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[0], "DATA0");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[1], "DATA1");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[2], "DATA2");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[3], "DATA3");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[4], "DATA4");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[5], "DATA5");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[6], "DATA6");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[7], "DATA7");

  testingCANAdapter.clearOutputframe();
  testingCANAdapter.m_currentstate = CANInterface::NORMAL;
  testingSerialAdapter.writeInput("R1FFFFFFF8");
  TEST_ASSERT_TRUE_MESSAGE(ProtocolTest.handler(), "Handler");
  TEST_ASSERT_EQUAL_UINT32_MESSAGE(0x1FFFFFFF, testingCANAdapter.m_outputFrame.ID, "ID");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(8, testingCANAdapter.m_outputFrame.DLC, "DLC");
  TEST_ASSERT_TRUE_MESSAGE(testingCANAdapter.m_outputFrame.Extended, "Extended");
  TEST_ASSERT_TRUE_MESSAGE(testingCANAdapter.m_outputFrame.RTR, "RTR");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[0], "DATA0");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[1], "DATA1");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[2], "DATA2");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[3], "DATA3");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[4], "DATA4");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[5], "DATA5");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[6], "DATA6");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[7], "DATA7");

  testingCANAdapter.clearOutputframe();
  testingCANAdapter.m_currentstate = CANInterface::NORMAL;
  testingSerialAdapter.writeInput("R0000ABCD4");
  TEST_ASSERT_TRUE_MESSAGE(ProtocolTest.handler(), "Handler");
  TEST_ASSERT_EQUAL_UINT32_MESSAGE(0x0000ABCD, testingCANAdapter.m_outputFrame.ID, "ID");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(4, testingCANAdapter.m_outputFrame.DLC, "DLC");
  TEST_ASSERT_TRUE_MESSAGE(testingCANAdapter.m_outputFrame.Extended, "Extended");
  TEST_ASSERT_TRUE_MESSAGE(testingCANAdapter.m_outputFrame.RTR, "RTR");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[0], "DATA0");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[1], "DATA1");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[2], "DATA2");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[3], "DATA3");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[4], "DATA4");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[5], "DATA5");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[6], "DATA6");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[7], "DATA7");

  testingCANAdapter.clearOutputframe();
  testingCANAdapter.m_currentstate = CANInterface::NORMAL;
  testingSerialAdapter.writeInput("R0000ABCD412233187");
  TEST_ASSERT_FALSE_MESSAGE(ProtocolTest.handler(), "Handler");
  TEST_ASSERT_EQUAL_UINT32_MESSAGE(0x00000000, testingCANAdapter.m_outputFrame.ID, "ID");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.DLC, "DLC");
  TEST_ASSERT_FALSE_MESSAGE(testingCANAdapter.m_outputFrame.Extended, "Extended");
  TEST_ASSERT_FALSE_MESSAGE(testingCANAdapter.m_outputFrame.RTR, "RTR");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[0], "DATA0");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[1], "DATA1");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[2], "DATA2");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[3], "DATA3");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[4], "DATA4");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[5], "DATA5");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[6], "DATA6");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[7], "DATA7");

  testingCANAdapter.clearOutputframe();
  testingCANAdapter.m_currentstate = CANInterface::CLOSED;
  testingSerialAdapter.writeInput("R0000ABCD4");
  TEST_ASSERT_FALSE_MESSAGE(ProtocolTest.handler(), "Handler");
  TEST_ASSERT_EQUAL_UINT32_MESSAGE(0x00000000, testingCANAdapter.m_outputFrame.ID, "ID");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.DLC, "DLC");
  TEST_ASSERT_FALSE_MESSAGE(testingCANAdapter.m_outputFrame.Extended, "Extended");
  TEST_ASSERT_FALSE_MESSAGE(testingCANAdapter.m_outputFrame.RTR, "RTR");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[0], "DATA0");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[1], "DATA1");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[2], "DATA2");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[3], "DATA3");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[4], "DATA4");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[5], "DATA5");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[6], "DATA6");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[7], "DATA7");

  testingCANAdapter.clearOutputframe();
  testingCANAdapter.m_currentstate = CANInterface::LISTEN_ONLY;
  testingSerialAdapter.writeInput("R0000ABCD4");
  TEST_ASSERT_FALSE_MESSAGE(ProtocolTest.handler(), "Handler");
  TEST_ASSERT_EQUAL_UINT32_MESSAGE(0x00000000, testingCANAdapter.m_outputFrame.ID, "ID");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.DLC, "DLC");
  TEST_ASSERT_FALSE_MESSAGE(testingCANAdapter.m_outputFrame.Extended, "Extended");
  TEST_ASSERT_FALSE_MESSAGE(testingCANAdapter.m_outputFrame.RTR, "RTR");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[0], "DATA0");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[1], "DATA1");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[2], "DATA2");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[3], "DATA3");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[4], "DATA4");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[5], "DATA5");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[6], "DATA6");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_outputFrame.Data[7], "DATA7");
}

void test_filter_mode(void)
{
  testingCANAdapter.m_filtermode = false;
  testingSerialAdapter.writeInput("W0");
  TEST_ASSERT_TRUE_MESSAGE(ProtocolTest.handler(), "Handler");
  TEST_ASSERT_FALSE_MESSAGE(testingCANAdapter.m_filtermode,"FilterMode Dual");

  testingCANAdapter.m_filtermode = false;
  testingSerialAdapter.writeInput("W1");
  TEST_ASSERT_TRUE_MESSAGE(ProtocolTest.handler(), "Handler");
  TEST_ASSERT_TRUE_MESSAGE(testingCANAdapter.m_filtermode,"FilterMode Dual");

  testingCANAdapter.m_filtermode = false;
  testingSerialAdapter.writeInput("W");
  TEST_ASSERT_FALSE_MESSAGE(ProtocolTest.handler(), "Handler");
  TEST_ASSERT_FALSE_MESSAGE(testingCANAdapter.m_filtermode,"FilterMode Dual");

  testingCANAdapter.m_filtermode = false;
  testingSerialAdapter.writeInput("W2");
  TEST_ASSERT_FALSE_MESSAGE(ProtocolTest.handler(), "Handler");
  TEST_ASSERT_FALSE_MESSAGE(testingCANAdapter.m_filtermode,"FilterMode Dual");

  testingCANAdapter.m_filtermode = false;
  testingSerialAdapter.writeInput("W20");
  TEST_ASSERT_FALSE_MESSAGE(ProtocolTest.handler(), "Handler");
  TEST_ASSERT_FALSE_MESSAGE(testingCANAdapter.m_filtermode,"FilterMode Dual");

  testingCANAdapter.m_currentstate = CANInterface::NORMAL;
  testingCANAdapter.m_filtermode = false;
  testingSerialAdapter.writeInput("W0");
  TEST_ASSERT_FALSE_MESSAGE(ProtocolTest.handler(), "Handler");
  TEST_ASSERT_FALSE_MESSAGE(testingCANAdapter.m_filtermode,"FilterMode Dual");
}

void test_acn_register(void)
{
  for(int i = 0; i < 4; i++){
  testingCANAdapter.m_ACn[i] = 0;
  }
  testingCANAdapter.m_currentstate = CANInterface::CLOSED;
  testingSerialAdapter.writeInput("MFFFFFFFF");
  TEST_ASSERT_TRUE_MESSAGE(ProtocolTest.handler(), "Handler");
  for(int i = 0; i < 4; i++){
  TEST_ASSERT_EQUAL_UINT8(0xFF, testingCANAdapter.m_ACn[i]);   
  }

  for(int i = 0; i < 4; i++){
  testingCANAdapter.m_ACn[i] = 0;
  }
  testingCANAdapter.m_currentstate = CANInterface::CLOSED;
  testingSerialAdapter.writeInput("MABCDEF01");
  TEST_ASSERT_TRUE_MESSAGE(ProtocolTest.handler(), "Handler");  
  TEST_ASSERT_EQUAL_UINT8(0xAB, testingCANAdapter.m_ACn[0]);
  TEST_ASSERT_EQUAL_UINT8(0xCD, testingCANAdapter.m_ACn[1]); 
  TEST_ASSERT_EQUAL_UINT8(0xEF, testingCANAdapter.m_ACn[2]); 
  TEST_ASSERT_EQUAL_UINT8(0x01, testingCANAdapter.m_ACn[3]); 
}

void test_amn_register(void)
{
  for(int i = 0; i < 4; i++){
  testingCANAdapter.m_AMn[i] = 0;
  }
  testingCANAdapter.m_currentstate = CANInterface::CLOSED;
  testingSerialAdapter.writeInput("mFFFFFFFF");
  TEST_ASSERT_TRUE_MESSAGE(ProtocolTest.handler(), "Handler");
  for(int i = 0; i < 4; i++){
  TEST_ASSERT_EQUAL_UINT8(0xFF, testingCANAdapter.m_AMn[i]);   
  }

  for(int i = 0; i < 4; i++){
  testingCANAdapter.m_AMn[i] = 0;
  }
  testingCANAdapter.m_currentstate = CANInterface::CLOSED;
  testingSerialAdapter.writeInput("mABCDEF01");
  TEST_ASSERT_TRUE_MESSAGE(ProtocolTest.handler(), "Handler");  
  TEST_ASSERT_EQUAL_UINT8(0xAB, testingCANAdapter.m_AMn[0]);
  TEST_ASSERT_EQUAL_UINT8(0xCD, testingCANAdapter.m_AMn[1]); 
  TEST_ASSERT_EQUAL_UINT8(0xEF, testingCANAdapter.m_AMn[2]); 
  TEST_ASSERT_EQUAL_UINT8(0x01, testingCANAdapter.m_AMn[3]); 
}

void test_serial_baudrate(void)
{
  testingSerialAdapter.writeInput("U0");
  TEST_ASSERT_TRUE_MESSAGE(ProtocolTest.handler(), "Handler");
  TEST_ASSERT_EQUAL_UINT32(230400, testingSerialAdapter.m_baudrate);
  TEST_ASSERT_EQUAL_STRING("U0",testingNVMAdapter.m_outputString.c_str());

  testingSerialAdapter.m_baudrate =115200;
  testingSerialAdapter.writeInput("U1");
  TEST_ASSERT_TRUE_MESSAGE(ProtocolTest.handler(), "Handler");
  TEST_ASSERT_EQUAL_UINT32(115200, testingSerialAdapter.m_baudrate);
  TEST_ASSERT_EQUAL_STRING("U1",testingNVMAdapter.m_outputString.c_str());

  testingSerialAdapter.m_baudrate =115200;
  testingSerialAdapter.writeInput("U2");
  TEST_ASSERT_TRUE_MESSAGE(ProtocolTest.handler(), "Handler");
  TEST_ASSERT_EQUAL_UINT32(57600, testingSerialAdapter.m_baudrate);
  testingSerialAdapter.m_baudrate =115200;
  TEST_ASSERT_EQUAL_STRING("U2",testingNVMAdapter.m_outputString.c_str());

  testingSerialAdapter.writeInput("U3");
  TEST_ASSERT_TRUE_MESSAGE(ProtocolTest.handler(), "Handler");
  TEST_ASSERT_EQUAL_UINT32(38400, testingSerialAdapter.m_baudrate);
  testingSerialAdapter.m_baudrate =115200;
  TEST_ASSERT_EQUAL_STRING("U3",testingNVMAdapter.m_outputString.c_str());

  testingSerialAdapter.writeInput("U4");
  TEST_ASSERT_TRUE_MESSAGE(ProtocolTest.handler(), "Handler");
  TEST_ASSERT_EQUAL_UINT32(19200, testingSerialAdapter.m_baudrate);
  TEST_ASSERT_EQUAL_STRING("U4",testingNVMAdapter.m_outputString.c_str());

  testingSerialAdapter.writeInput("U");
  TEST_ASSERT_FALSE_MESSAGE(ProtocolTest.handler(), "Handler");
  TEST_ASSERT_EQUAL_UINT32(19200, testingSerialAdapter.m_baudrate);
  TEST_ASSERT_EQUAL_STRING("U4",testingNVMAdapter.m_outputString.c_str());

  testingSerialAdapter.writeInput("U54");
  TEST_ASSERT_FALSE_MESSAGE(ProtocolTest.handler(), "Handler");
  TEST_ASSERT_EQUAL_UINT32(19200, testingSerialAdapter.m_baudrate);
  TEST_ASSERT_EQUAL_STRING("U4",testingNVMAdapter.m_outputString.c_str());
}

void test_version(void)
{
  testingSerialAdapter.writeInput("V");
  TEST_ASSERT_TRUE_MESSAGE(ProtocolTest.handler(), "Handler");
  TEST_ASSERT_EQUAL_STRING("V0101\r",testingSerialAdapter.outputString.c_str());
}

void test_serialnumber(void)
{
  testingSerialAdapter.writeInput("N");
  TEST_ASSERT_TRUE_MESSAGE(ProtocolTest.handler(), "Handler");
  TEST_ASSERT_EQUAL_STRING("NNT32\r",testingSerialAdapter.outputString.c_str());
}

void test_timestamp(void)
{
  testingSerialAdapter.writeInput("Z0");
  TEST_ASSERT_TRUE_MESSAGE(ProtocolTest.handler(), "Handler");
  TEST_ASSERT_EQUAL_UINT32(0,testingNVMAdapter.m_outputInt);

  testingSerialAdapter.writeInput("Z1");
  TEST_ASSERT_TRUE_MESSAGE(ProtocolTest.handler(), "Handler");
  TEST_ASSERT_EQUAL_UINT32(1,testingNVMAdapter.m_outputInt);

  testingSerialAdapter.writeInput("Z2");
  TEST_ASSERT_FALSE_MESSAGE(ProtocolTest.handler(), "Handler");
  TEST_ASSERT_EQUAL_UINT32(1,testingNVMAdapter.m_outputInt);
}

void test_autostart(void)
{
  testingCANAdapter.m_currentstate = CANInterface::NORMAL;
  testingSerialAdapter.writeInput("Q0");
  TEST_ASSERT_TRUE_MESSAGE(ProtocolTest.handler(), "Handler");
  TEST_ASSERT_EQUAL_UINT32(0,testingNVMAdapter.m_outputInt);

  testingSerialAdapter.writeInput("Q1");
  TEST_ASSERT_TRUE_MESSAGE(ProtocolTest.handler(), "Handler");
  TEST_ASSERT_EQUAL_UINT32(1,testingNVMAdapter.m_outputInt);

  testingSerialAdapter.writeInput("Q2");
  TEST_ASSERT_TRUE_MESSAGE(ProtocolTest.handler(), "Handler");
  TEST_ASSERT_EQUAL_UINT32(2,testingNVMAdapter.m_outputInt);

  testingSerialAdapter.writeInput("Q3");
  TEST_ASSERT_FALSE_MESSAGE(ProtocolTest.handler(), "Handler");
  TEST_ASSERT_EQUAL_UINT32(2,testingNVMAdapter.m_outputInt);
}

int main(int argc, char **argv)
{

  UNITY_BEGIN();
  testingCANAdapter.m_inputFrame.ID = 0xFFF;
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