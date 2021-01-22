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

/* System Includes */
#include <unity.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cmath>

/* Custom Arduino Includes for Compatibility. Located in lib/Test */
#include "Lawicel.h"
#include "Arduino.h"
#include "Print.h"
#include "WString.h"

/* Test Adapters for Lawicel Protocol */
#include "test_serial_adapter.h"
#include "test_can_adapter.h"
#include "test_nvm_adapter.h"

/* CONSTANTS **************************************************************************************/

TestSerialAdapter testingSerialAdapter;                                           /**< Serial Adapter */
TestCANAdapter testingCANAdapter;                                                 /**< CAN Adapter */
TestNVMAdapter testingNVMAdapter;                                                 /**< NVM Adapter */
Lawicel ProtocolTest(testingSerialAdapter, testingCANAdapter, testingNVMAdapter); /**< Lawicel Protocol Instance */

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/

void runProtocolExecute(uint8_t cycles); /**< Runs Lawicel Cycle the amount of times specified */
void test_can_baudrate(void);            /**< Test set CAN Baudrate */
void test_can_btr(void);                 /**< Test set CAN BTR Registers */
void test_can_open_normal(void);         /**< Test Open Normal CAN Channel */
void test_can_open_listen_only(void);    /**< Test Open Listen Only CAN Channel */
void test_can_close(void);               /**< Test Close CAN Channel */
void test_tx_std(void);                  /**< Test Send STD Frame */
void test_tx_ext(void);                  /**< Test Send EXT Frame */
void test_tx_std_rtr(void);              /**< Test Send STD RTR Frame */
void test_tx_ext_rtr(void);              /**< Test Send EXT RTR Frame */
void test_filter_mode(void);             /**< Test set Filter Mode */
void test_acn_register(void);            /**< Test set ACRn */
void test_amn_register(void);            /**< Test set AMRn */
void test_serial_baudrate(void);         /**< Test set Serial Baudrate */
void test_version(void);                 /**< Test get Version */
void test_serialnumber(void);            /**< Test get Serial number */
void test_timestamp(void);               /**< Test set Timestamp mode */
void test_autostart(void);               /**< Test set Autostart Mode */

/* VARIABLES **************************************************************************************/

/* PUBLIC METHODES ********************************************************************************/

/**************************************************************************************************/

/**
*   Main Testing Programm. Runs the Different Unity Tests
*/
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
    RUN_TEST(test_filter_mode);
    RUN_TEST(test_acn_register);
    RUN_TEST(test_amn_register);
    RUN_TEST(test_serial_baudrate);
    RUN_TEST(test_version);
    RUN_TEST(test_serialnumber);
    RUN_TEST(test_timestamp);
    RUN_TEST(test_autostart);
    return UNITY_END();
}

/* PROTECTED METHODES *****************************************************************************/

/* PRIVATE METHODES *******************************************************************************/

/**************************************************************************************************/

/**
*   Test set CAN Baudrate
*/
void test_can_baudrate(void)
{
    testingCANAdapter.m_currentState = CANInterface::CLOSED;
    testingCANAdapter.m_baudRate = 0;

    runProtocolExecute(testingSerialAdapter.writeInput("S0"));
    TEST_ASSERT_EQUAL(10E3, testingCANAdapter.m_baudRate);

    runProtocolExecute(testingSerialAdapter.writeInput("S1"));
    TEST_ASSERT_EQUAL(20E3, testingCANAdapter.m_baudRate);

    runProtocolExecute(testingSerialAdapter.writeInput("S2"));
    TEST_ASSERT_EQUAL(50E3, testingCANAdapter.m_baudRate);

    runProtocolExecute(testingSerialAdapter.writeInput("S3"));
    TEST_ASSERT_EQUAL(100E3, testingCANAdapter.m_baudRate);

    runProtocolExecute(testingSerialAdapter.writeInput("S4"));
    TEST_ASSERT_EQUAL(125E3, testingCANAdapter.m_baudRate);

    runProtocolExecute(testingSerialAdapter.writeInput("S5"));
    TEST_ASSERT_EQUAL(250E3, testingCANAdapter.m_baudRate);

    runProtocolExecute(testingSerialAdapter.writeInput("S6"));
    TEST_ASSERT_EQUAL(500E3, testingCANAdapter.m_baudRate);

    runProtocolExecute(testingSerialAdapter.writeInput("S7"));
    TEST_ASSERT_EQUAL(800E3, testingCANAdapter.m_baudRate);

    runProtocolExecute(testingSerialAdapter.writeInput("S8"));
    TEST_ASSERT_EQUAL(1000E3, testingCANAdapter.m_baudRate);
}

/**************************************************************************************************/

/**
*   Test set CAN BTR Registers
*/
void test_can_btr(void)
{
    runProtocolExecute(testingSerialAdapter.writeInput("s0000"));
    TEST_ASSERT_EQUAL(0x00, testingCANAdapter.m_btr0);
    TEST_ASSERT_EQUAL(0x00, testingCANAdapter.m_btr1);

    runProtocolExecute(testingSerialAdapter.writeInput("s031C"));
    TEST_ASSERT_EQUAL(0x03, testingCANAdapter.m_btr0);
    TEST_ASSERT_EQUAL(0x1C, testingCANAdapter.m_btr1);

    runProtocolExecute(testingSerialAdapter.writeInput("sFFFF"));
    TEST_ASSERT_EQUAL(0xFF, testingCANAdapter.m_btr0);
    TEST_ASSERT_EQUAL(0xFF, testingCANAdapter.m_btr1);
}

/**************************************************************************************************/

/**
*   Test Open Normal CAN Channel
*/
void test_can_open_normal(void)
{
    testingCANAdapter.m_currentState = CANInterface::CLOSED;
    runProtocolExecute(testingSerialAdapter.writeInput("O"));
    TEST_ASSERT_EQUAL(1, testingCANAdapter.getChannelState());

    testingCANAdapter.m_currentState = CANInterface::NORMAL;
    runProtocolExecute(testingSerialAdapter.writeInput("O"));
    TEST_ASSERT_EQUAL(1, testingCANAdapter.getChannelState());

    testingCANAdapter.m_currentState = CANInterface::LISTEN_ONLY;
    runProtocolExecute(testingSerialAdapter.writeInput("O"));
    TEST_ASSERT_EQUAL(2, testingCANAdapter.getChannelState());
}

/**************************************************************************************************/

/**
*   Test Open Listen Only CAN Channel
*/
void test_can_open_listen_only(void)
{
    testingCANAdapter.m_currentState = CANInterface::CLOSED;
    runProtocolExecute(testingSerialAdapter.writeInput("L"));
    TEST_ASSERT_EQUAL(2, testingCANAdapter.getChannelState());

    testingCANAdapter.m_currentState = CANInterface::CLOSED;
    runProtocolExecute(testingSerialAdapter.writeInput("L0"));
    TEST_ASSERT_EQUAL(0, testingCANAdapter.getChannelState());

    testingCANAdapter.m_currentState = CANInterface::NORMAL;
    runProtocolExecute(testingSerialAdapter.writeInput("L"));
    TEST_ASSERT_EQUAL(1, testingCANAdapter.getChannelState());

    testingCANAdapter.m_currentState = CANInterface::LISTEN_ONLY;
    runProtocolExecute(testingSerialAdapter.writeInput("L"));
    TEST_ASSERT_EQUAL(2, testingCANAdapter.getChannelState());
}

/**************************************************************************************************/

/**
*   Test Close CAN Channel
*/
void test_can_close(void)
{
    testingCANAdapter.setState(CANInterface::NORMAL);
    runProtocolExecute(testingSerialAdapter.writeInput("C"));
    TEST_ASSERT_EQUAL(0, testingCANAdapter.getChannelState());

    testingCANAdapter.setState(CANInterface::LISTEN_ONLY);
    runProtocolExecute(testingSerialAdapter.writeInput("C"));
    TEST_ASSERT_EQUAL(0, testingCANAdapter.getChannelState());
}

/**************************************************************************************************/

/**
*   Test Send STD Frame
*/
void test_tx_std(void)
{
    testingCANAdapter.setState(CANInterface::NORMAL);
    testingCANAdapter.setBaudrate(500E3);

    testingCANAdapter.clearOutputFrame();
    runProtocolExecute(testingSerialAdapter.writeInput("t0010"));
    testingCANAdapter.enterInputFrame(0x001, false, false, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    TEST_ASSERT_TRUE_MESSAGE(testingCANAdapter.compareFrames(testingCANAdapter.m_inputFrame, 
                                                            testingCANAdapter.m_outputFrame), 
                                                            "Frame Compare");

    testingCANAdapter.clearOutputFrame();
    runProtocolExecute(testingSerialAdapter.writeInput("t1FF81122334455667788"));
    testingCANAdapter.enterInputFrame(0x1FF, false, false, 8, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88);
    TEST_ASSERT_TRUE_MESSAGE(testingCANAdapter.compareFrames(testingCANAdapter.m_inputFrame, 
                                                            testingCANAdapter.m_outputFrame), 
                                                            "Frame Compare");

    testingCANAdapter.clearOutputFrame();
    runProtocolExecute(testingSerialAdapter.writeInput("t1234AABBCCDD"));
    testingCANAdapter.enterInputFrame(0x123, false, false, 4, 0xAA, 0xBB, 0xCC, 0xDD, 0, 0, 0, 0);
    TEST_ASSERT_TRUE_MESSAGE(testingCANAdapter.compareFrames(testingCANAdapter.m_inputFrame, 
                                                            testingCANAdapter.m_outputFrame), 
                                                            "Frame Compare");

    testingCANAdapter.clearOutputFrame();
    testingCANAdapter.m_currentState = CANInterface::CLOSED;
    runProtocolExecute(testingSerialAdapter.writeInput("t1234AABBCCDD"));
    testingCANAdapter.enterInputFrame(0x000, false, false, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    TEST_ASSERT_TRUE_MESSAGE(testingCANAdapter.compareFrames(testingCANAdapter.m_inputFrame, 
                                                            testingCANAdapter.m_outputFrame), 
                                                            "Frame Compare");

    testingCANAdapter.clearOutputFrame();
    testingCANAdapter.m_currentState = CANInterface::LISTEN_ONLY;
    runProtocolExecute(testingSerialAdapter.writeInput("t1234AABBCCDD"));
    testingCANAdapter.enterInputFrame(0x000, false, false, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    TEST_ASSERT_TRUE_MESSAGE(testingCANAdapter.compareFrames(testingCANAdapter.m_inputFrame, 
                                                            testingCANAdapter.m_outputFrame), 
                                                            "Frame Compare");
}

/**************************************************************************************************/

/**
*   Test Send EXT Frame
*/
void test_tx_ext(void)
{
    testingCANAdapter.setState(CANInterface::NORMAL);
    testingCANAdapter.setBaudrate(500E3);

    testingCANAdapter.clearOutputFrame();
    testingCANAdapter.m_currentState = CANInterface::NORMAL;
    runProtocolExecute(testingSerialAdapter.writeInput("T000000000"));
    testingCANAdapter.enterInputFrame(0x000, false, true, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    TEST_ASSERT_TRUE_MESSAGE(testingCANAdapter.compareFrames(testingCANAdapter.m_inputFrame, 
                                                            testingCANAdapter.m_outputFrame), 
                                                            "Frame Compare");

    testingCANAdapter.clearOutputFrame();
    testingCANAdapter.m_currentState = CANInterface::NORMAL;
    runProtocolExecute(testingSerialAdapter.writeInput("T1FFFFFFF81122334455667788"));
    testingCANAdapter.enterInputFrame(0x1FFFFFFF, false, true, 8,0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88);
    TEST_ASSERT_TRUE_MESSAGE(testingCANAdapter.compareFrames(testingCANAdapter.m_inputFrame, 
                                                            testingCANAdapter.m_outputFrame), 
                                                            "Frame Compare");

    testingCANAdapter.clearOutputFrame();
    testingCANAdapter.m_currentState = CANInterface::NORMAL;
    runProtocolExecute(testingSerialAdapter.writeInput("T0000ABCD411223344"));
    testingCANAdapter.enterInputFrame(0x0000ABCD, false, true, 4,0x11, 0x22, 0x33, 0x44, 0, 0, 0, 0);
    TEST_ASSERT_TRUE_MESSAGE(testingCANAdapter.compareFrames(testingCANAdapter.m_inputFrame, 
                                                            testingCANAdapter.m_outputFrame), 
                                                            "Frame Compare");

    testingCANAdapter.clearOutputFrame();
    testingCANAdapter.m_currentState = CANInterface::CLOSED;
    runProtocolExecute(testingSerialAdapter.writeInput("T0000ABCD411223344"));
    testingCANAdapter.enterInputFrame(0x000, false, false, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    TEST_ASSERT_TRUE_MESSAGE(testingCANAdapter.compareFrames(testingCANAdapter.m_inputFrame, 
                                                            testingCANAdapter.m_outputFrame), 
                                                            "Frame Compare");

    testingCANAdapter.clearOutputFrame();
    testingCANAdapter.m_currentState = CANInterface::LISTEN_ONLY;
    runProtocolExecute(testingSerialAdapter.writeInput("T0000ABCD411223344"));
    testingCANAdapter.enterInputFrame(0x000, false, false, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    TEST_ASSERT_TRUE_MESSAGE(testingCANAdapter.compareFrames(testingCANAdapter.m_inputFrame, 
                                                            testingCANAdapter.m_outputFrame), 
                                                            "Frame Compare");
}

/**************************************************************************************************/

/**
*   Test Send STD RTR Frame
*/
void test_tx_std_rtr(void)
{
    testingCANAdapter.clearOutputFrame();
    testingCANAdapter.m_currentState = CANInterface::NORMAL;
    runProtocolExecute(testingSerialAdapter.writeInput("r0000"));
    testingCANAdapter.enterInputFrame(0x000, true, false, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    TEST_ASSERT_TRUE_MESSAGE(testingCANAdapter.compareFrames(testingCANAdapter.m_inputFrame, 
                                                            testingCANAdapter.m_outputFrame), 
                                                            "Frame Compare");

    testingCANAdapter.clearOutputFrame();
    testingCANAdapter.m_currentState = CANInterface::NORMAL;
    runProtocolExecute(testingSerialAdapter.writeInput("r00081122334455667788"));
    testingCANAdapter.enterInputFrame(0x000, false, false, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    TEST_ASSERT_TRUE_MESSAGE(testingCANAdapter.compareFrames(testingCANAdapter.m_inputFrame, 
                                                            testingCANAdapter.m_outputFrame), 
                                                            "Frame Compare");

    testingCANAdapter.clearOutputFrame();
    testingCANAdapter.m_currentState = CANInterface::NORMAL;
    runProtocolExecute(testingSerialAdapter.writeInput("r1FF8"));
    testingCANAdapter.enterInputFrame(0x1FF, true, false, 8, 0, 0, 0, 0, 0, 0, 0, 0);
    TEST_ASSERT_TRUE_MESSAGE(testingCANAdapter.compareFrames(testingCANAdapter.m_inputFrame, 
                                                            testingCANAdapter.m_outputFrame), 
                                                            "Frame Compare");

    testingCANAdapter.clearOutputFrame();
    testingCANAdapter.m_currentState = CANInterface::NORMAL;
    runProtocolExecute(testingSerialAdapter.writeInput("r1234"));
    testingCANAdapter.enterInputFrame(0x123, true, false, 4, 0, 0, 0, 0, 0, 0, 0, 0);
    TEST_ASSERT_TRUE_MESSAGE(testingCANAdapter.compareFrames(testingCANAdapter.m_inputFrame, 
                                                            testingCANAdapter.m_outputFrame), 
                                                            "Frame Compare");

    testingCANAdapter.clearOutputFrame();
    testingCANAdapter.m_currentState = CANInterface::CLOSED;
    runProtocolExecute(testingSerialAdapter.writeInput("r1234AABBCCDD"));
    testingCANAdapter.enterInputFrame(0x000, false, false, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    TEST_ASSERT_TRUE_MESSAGE(testingCANAdapter.compareFrames(testingCANAdapter.m_inputFrame, 
                                                            testingCANAdapter.m_outputFrame), 
                                                            "Frame Compare");

    testingCANAdapter.clearOutputFrame();
    testingCANAdapter.m_currentState = CANInterface::LISTEN_ONLY;
    runProtocolExecute(testingSerialAdapter.writeInput("r1234AABBCCDD"));
    testingCANAdapter.enterInputFrame(0x000, false, false, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    TEST_ASSERT_TRUE_MESSAGE(testingCANAdapter.compareFrames(testingCANAdapter.m_inputFrame, 
                                                            testingCANAdapter.m_outputFrame), 
                                                            "Frame Compare");
}

/**************************************************************************************************/

/**
*   Test Send EXT RTR Frame
*/
void test_tx_ext_rtr(void)
{
    testingCANAdapter.clearOutputFrame();
    testingCANAdapter.m_currentState = CANInterface::NORMAL;
    runProtocolExecute(testingSerialAdapter.writeInput("R000000000"));
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(0x0000000, testingCANAdapter.m_outputFrame.m_id, "ID");
    testingCANAdapter.enterInputFrame(0x0000000, true, true, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    TEST_ASSERT_TRUE_MESSAGE(testingCANAdapter.compareFrames(testingCANAdapter.m_inputFrame, 
                                                            testingCANAdapter.m_outputFrame), 
                                                            "Frame Compare");

    testingCANAdapter.clearOutputFrame();
    testingCANAdapter.m_currentState = CANInterface::NORMAL;
    runProtocolExecute(testingSerialAdapter.writeInput("R1FFFFFFF8"));
    testingCANAdapter.enterInputFrame(0x1FFFFFFF, true, true, 8, 0, 0, 0, 0, 0, 0, 0, 0);
    TEST_ASSERT_TRUE_MESSAGE(testingCANAdapter.compareFrames(testingCANAdapter.m_inputFrame, 
                                                            testingCANAdapter.m_outputFrame), 
                                                            "Frame Compare");

    testingCANAdapter.clearOutputFrame();
    testingCANAdapter.m_currentState = CANInterface::NORMAL;
    runProtocolExecute(testingSerialAdapter.writeInput("R0000ABCD4"));
    testingCANAdapter.enterInputFrame(0x0000ABCD, true, true, 4, 0, 0, 0, 0, 0, 0, 0, 0);
    TEST_ASSERT_TRUE_MESSAGE(testingCANAdapter.compareFrames(testingCANAdapter.m_inputFrame, 
                                                            testingCANAdapter.m_outputFrame), 
                                                            "Frame Compare");

    testingCANAdapter.clearOutputFrame();
    testingCANAdapter.m_currentState = CANInterface::NORMAL;
    runProtocolExecute(testingSerialAdapter.writeInput("R0000ABCD412233187"));
    testingCANAdapter.enterInputFrame(0x000, false, false, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    TEST_ASSERT_TRUE_MESSAGE(testingCANAdapter.compareFrames(testingCANAdapter.m_inputFrame, 
                                                            testingCANAdapter.m_outputFrame), 
                                                            "Frame Compare");

    testingCANAdapter.clearOutputFrame();
    testingCANAdapter.m_currentState = CANInterface::CLOSED;
    runProtocolExecute(testingSerialAdapter.writeInput("R0000ABCD4"));
    testingCANAdapter.enterInputFrame(0x000, false, false, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    TEST_ASSERT_TRUE_MESSAGE(testingCANAdapter.compareFrames(testingCANAdapter.m_inputFrame, 
                                                            testingCANAdapter.m_outputFrame), 
                                                            "Frame Compare");

    testingCANAdapter.clearOutputFrame();
    testingCANAdapter.m_currentState = CANInterface::LISTEN_ONLY;
    runProtocolExecute(testingSerialAdapter.writeInput("R0000ABCD4"));
    testingCANAdapter.enterInputFrame(0x000, false, false, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    TEST_ASSERT_TRUE_MESSAGE(testingCANAdapter.compareFrames(testingCANAdapter.m_inputFrame, 
                                                            testingCANAdapter.m_outputFrame), 
                                                            "Frame Compare");
}

/**************************************************************************************************/

/**
*   Test set Filter Mode
*/
void test_filter_mode(void)
{
    testingCANAdapter.m_currentState = CANInterface::CLOSED;
    testingCANAdapter.m_filterMode = 0;
    runProtocolExecute(testingSerialAdapter.writeInput("W0"));
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_filterMode, "FilterMode Dual");

    testingCANAdapter.m_filterMode = 0;
    runProtocolExecute(testingSerialAdapter.writeInput("W1"));
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(1, testingCANAdapter.m_filterMode, "FilterMode Dual");

    testingCANAdapter.m_filterMode = 0;
    runProtocolExecute(testingSerialAdapter.writeInput("W"));
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_filterMode, "FilterMode Dual");

    testingCANAdapter.m_filterMode = 0;
    runProtocolExecute(testingSerialAdapter.writeInput("W2"));
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_filterMode, "FilterMode Dual");

    testingCANAdapter.m_filterMode = 1;
    runProtocolExecute(testingSerialAdapter.writeInput("W0"));
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_filterMode, "FilterMode Dual");

    testingCANAdapter.m_currentState = CANInterface::NORMAL;
    testingCANAdapter.m_filterMode = 1;
    runProtocolExecute(testingSerialAdapter.writeInput("W0"));
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(1, testingCANAdapter.m_filterMode, "FilterMode Dual");
}

/**************************************************************************************************/

/**
*   Test set ACRn
*/
void test_acn_register(void)
{
    for (int i = 0; i < 4; i++)
    {
        testingCANAdapter.m_ACRn.m_filterBytes[i] = 0;
    }
    testingCANAdapter.m_currentState = CANInterface::CLOSED;
    runProtocolExecute(testingSerialAdapter.writeInput("MFFFFFFFF"));
    for (int i = 0; i < 4; i++)
    {
        TEST_ASSERT_EQUAL_UINT8(0xFF, testingCANAdapter.m_ACRn.m_filterBytes[i]);
    }

    for (int i = 0; i < 4; i++)
    {
        testingCANAdapter.m_ACRn.m_filterBytes[i] = 0;
    }
    testingCANAdapter.m_currentState = CANInterface::CLOSED;
    runProtocolExecute(testingSerialAdapter.writeInput("MABCDEF01"));
    TEST_ASSERT_EQUAL_UINT8(0xAB, testingCANAdapter.m_ACRn.m_filterBytes[0]);
    TEST_ASSERT_EQUAL_UINT8(0xCD, testingCANAdapter.m_ACRn.m_filterBytes[1]);
    TEST_ASSERT_EQUAL_UINT8(0xEF, testingCANAdapter.m_ACRn.m_filterBytes[2]);
    TEST_ASSERT_EQUAL_UINT8(0x01, testingCANAdapter.m_ACRn.m_filterBytes[3]);
}

/**************************************************************************************************/

/**
*   Test set AMRn
*/
void test_amn_register(void)
{
    for (int i = 0; i < 4; i++)
    {
        testingCANAdapter.m_AMRn.m_filterBytes[i] = 0;
    }
    testingCANAdapter.m_currentState = CANInterface::CLOSED;
    runProtocolExecute(testingSerialAdapter.writeInput("mFFFFFFFF"));
    for (int i = 0; i < 4; i++)
    {
        TEST_ASSERT_EQUAL_UINT8(0xFF, testingCANAdapter.m_AMRn.m_filterBytes[i]);
    }

    for (int i = 0; i < 4; i++)
    {
        testingCANAdapter.m_AMRn.m_filterBytes[i] = 0;
    }
    testingCANAdapter.m_currentState = CANInterface::CLOSED;
    runProtocolExecute(testingSerialAdapter.writeInput("mABCDEF01"));
    TEST_ASSERT_EQUAL_UINT8(0xAB, testingCANAdapter.m_AMRn.m_filterBytes[0]);
    TEST_ASSERT_EQUAL_UINT8(0xCD, testingCANAdapter.m_AMRn.m_filterBytes[1]);
    TEST_ASSERT_EQUAL_UINT8(0xEF, testingCANAdapter.m_AMRn.m_filterBytes[2]);
    TEST_ASSERT_EQUAL_UINT8(0x01, testingCANAdapter.m_AMRn.m_filterBytes[3]);
}

/**************************************************************************************************/

/**
*   Test set Serial Baudrate
*/
void test_serial_baudrate(void)
{
    testingCANAdapter.m_currentState = CANInterface::CLOSED;
    runProtocolExecute(testingSerialAdapter.writeInput("U0"));
    TEST_ASSERT_EQUAL_UINT32(230400, testingSerialAdapter.m_serialBaudrate);
    TEST_ASSERT_EQUAL_STRING("U0", testingNVMAdapter.m_outputString.c_str());

    testingSerialAdapter.m_serialBaudrate = 115200;
    runProtocolExecute(testingSerialAdapter.writeInput("U1"));
    TEST_ASSERT_EQUAL_UINT32(115200, testingSerialAdapter.m_serialBaudrate);
    TEST_ASSERT_EQUAL_STRING("U1", testingNVMAdapter.m_outputString.c_str());

    testingSerialAdapter.m_serialBaudrate = 115200;

    runProtocolExecute(testingSerialAdapter.writeInput("U2"));
    TEST_ASSERT_EQUAL_UINT32(57600, testingSerialAdapter.m_serialBaudrate);
    testingSerialAdapter.m_serialBaudrate = 115200;
    TEST_ASSERT_EQUAL_STRING("U2", testingNVMAdapter.m_outputString.c_str());

    runProtocolExecute(testingSerialAdapter.writeInput("U3"));
    TEST_ASSERT_EQUAL_UINT32(38400, testingSerialAdapter.m_serialBaudrate);
    testingSerialAdapter.m_serialBaudrate = 115200;
    TEST_ASSERT_EQUAL_STRING("U3", testingNVMAdapter.m_outputString.c_str());

    runProtocolExecute(testingSerialAdapter.writeInput("U4"));
    TEST_ASSERT_EQUAL_UINT32(19200, testingSerialAdapter.m_serialBaudrate);
    TEST_ASSERT_EQUAL_STRING("U4", testingNVMAdapter.m_outputString.c_str());

    runProtocolExecute(testingSerialAdapter.writeInput("U"));
    TEST_ASSERT_EQUAL_UINT32(19200, testingSerialAdapter.m_serialBaudrate);
    TEST_ASSERT_EQUAL_STRING("U4", testingNVMAdapter.m_outputString.c_str());

    runProtocolExecute(testingSerialAdapter.writeInput("'U54'"));
    TEST_ASSERT_EQUAL_UINT32(19200, testingSerialAdapter.m_serialBaudrate);
    TEST_ASSERT_EQUAL_STRING("U4", testingNVMAdapter.m_outputString.c_str());
}

/**************************************************************************************************/

/**
*   Test get Version
*/
void test_version(void)
{
    runProtocolExecute(testingSerialAdapter.writeInput("V"));
    TEST_ASSERT_EQUAL_STRING("V0101\r", testingSerialAdapter.m_outputString.c_str());
}

/**************************************************************************************************/

/**
*   Test get Serial number
*/
void test_serialnumber(void)
{
    runProtocolExecute(testingSerialAdapter.writeInput("N"));
    TEST_ASSERT_EQUAL_STRING("NNT32\r", testingSerialAdapter.m_outputString.c_str());
}

/**************************************************************************************************/

/**
*   Test set Timestamp mode
*/
void test_timestamp(void)
{
    runProtocolExecute(testingSerialAdapter.writeInput("Z0"));
    TEST_ASSERT_EQUAL_UINT32(0, testingNVMAdapter.m_outputInt);

    runProtocolExecute(testingSerialAdapter.writeInput("Z1"));
    TEST_ASSERT_EQUAL_UINT32(1, testingNVMAdapter.m_outputInt);

    runProtocolExecute(testingSerialAdapter.writeInput("Z2"));
    TEST_ASSERT_EQUAL_UINT32(1, testingNVMAdapter.m_outputInt);
}

/**************************************************************************************************/

/**
*   Test set Autostart Mode
*/
void test_autostart(void)
{
    testingCANAdapter.m_currentState = CANInterface::NORMAL;
    runProtocolExecute(testingSerialAdapter.writeInput("Q0"));
    TEST_ASSERT_EQUAL_UINT32(0, testingNVMAdapter.m_outputInt);

    runProtocolExecute(testingSerialAdapter.writeInput("Q1"));
    TEST_ASSERT_EQUAL_UINT32(1, testingNVMAdapter.m_outputInt);

    runProtocolExecute(testingSerialAdapter.writeInput("Q2"));
    TEST_ASSERT_EQUAL_UINT32(2, testingNVMAdapter.m_outputInt);

    runProtocolExecute(testingSerialAdapter.writeInput("Q3"));
    TEST_ASSERT_EQUAL_UINT32(2, testingNVMAdapter.m_outputInt);
}

/* EXTERNAL FUNCTIONS *****************************************************************************/

/* INTERNAL FUNCTIONS *****************************************************************************/

/**************************************************************************************************/

/**
*   Runs Lawicel Cycle the amount of times specified
*/
void runProtocolExecute(uint8_t cycles)
{
    for (uint8_t i = 0; i < cycles; i++)
    {
        ProtocolTest.executeCycle();
    }
}
