/***************************************************************************************************
BSD 3-Clause License


Copyright (c) 2020-2021, NewTec GmbH - www.newtec.de
All rights reserved.


Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:


1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.


2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.


3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.


THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/

static void executeProtocolCycle(uint8_t cycles); /**< Runs Lawicel Cycle the amount of times specified */
static void testCanBaudrate(void);                /**< Test set CAN Baudrate */
static void testCanBtr(void);                     /**< Test set CAN BTR Registers */
static void testCanOpenNormal(void);              /**< Test Open Normal CAN Channel */
static void testCanOpenListenOnly(void);          /**< Test Open Listen Only CAN Channel */
static void testCanClose(void);                   /**< Test Close CAN Channel */
static void testTxStd(void);                      /**< Test Send STD Frame */
static void testTxExt(void);                      /**< Test Send EXT Frame */
static void testTxStdRtr(void);                   /**< Test Send STD RTR Frame */
static void testTxExtRtr(void);                   /**< Test Send EXT RTR Frame */
static void testFilterMode(void);                 /**< Test set Filter Mode */
static void testAcnRegister(void);                /**< Test set ACRn */
static void testAmnRegister(void);                /**< Test set AMRn */
static void testSerialBaudrate(void);             /**< Test set Serial Baudrate */
static void testVersion(void);                    /**< Test get Version */
static void testSerialNumber(void);               /**< Test get Serial number */
static void testTimestamp(void);                  /**< Test set Timestamp mode */
static void testAutostart(void);                  /**< Test set Autostart Mode */

/* VARIABLES **************************************************************************************/

static TestSerialAdapter testingSerialAdapter;                                           /**< Serial Adapter */
static TestCANAdapter testingCANAdapter;                                                 /**< CAN Adapter */
static TestNVMAdapter testingNVMAdapter;                                                 /**< NVM Adapter */
static Lawicel ProtocolTest(testingSerialAdapter, testingCANAdapter, testingNVMAdapter); /**< Lawicel Protocol Instance */

/* PUBLIC METHODES ********************************************************************************/

/**************************************************************************************************/

/**
 *  Main Testing Programm. Runs the Different Unity Tests
 */
int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(testCanBaudrate);
    RUN_TEST(testCanBtr);
    RUN_TEST(testCanOpenNormal);
    RUN_TEST(testCanOpenListenOnly);
    RUN_TEST(testCanClose);
    RUN_TEST(testTxStd);
    RUN_TEST(testTxExt);
    RUN_TEST(testTxStdRtr);
    RUN_TEST(testTxExtRtr);
    RUN_TEST(testFilterMode);
    RUN_TEST(testAcnRegister);
    RUN_TEST(testAmnRegister);
    RUN_TEST(testSerialBaudrate);
    RUN_TEST(testVersion);
    RUN_TEST(testSerialNumber);
    RUN_TEST(testTimestamp);
    RUN_TEST(testAutostart);
    return UNITY_END();
}

/* PROTECTED METHODES *****************************************************************************/

/* PRIVATE METHODES *******************************************************************************/

/**************************************************************************************************/

/**
 *  Test set CAN Baudrate
 */
static void testCanBaudrate(void)
{
    testingCANAdapter.m_currentState = CANInterface::CLOSED;
    testingCANAdapter.m_baudRate = 0;

    executeProtocolCycle(testingSerialAdapter.writeInput("S0"));
    TEST_ASSERT_EQUAL(10E3, testingCANAdapter.m_baudRate);

    executeProtocolCycle(testingSerialAdapter.writeInput("S1"));
    TEST_ASSERT_EQUAL(20E3, testingCANAdapter.m_baudRate);

    executeProtocolCycle(testingSerialAdapter.writeInput("S2"));
    TEST_ASSERT_EQUAL(50E3, testingCANAdapter.m_baudRate);

    executeProtocolCycle(testingSerialAdapter.writeInput("S3"));
    TEST_ASSERT_EQUAL(100E3, testingCANAdapter.m_baudRate);

    executeProtocolCycle(testingSerialAdapter.writeInput("S4"));
    TEST_ASSERT_EQUAL(125E3, testingCANAdapter.m_baudRate);

    executeProtocolCycle(testingSerialAdapter.writeInput("S5"));
    TEST_ASSERT_EQUAL(250E3, testingCANAdapter.m_baudRate);

    executeProtocolCycle(testingSerialAdapter.writeInput("S6"));
    TEST_ASSERT_EQUAL(500E3, testingCANAdapter.m_baudRate);

    executeProtocolCycle(testingSerialAdapter.writeInput("S7"));
    TEST_ASSERT_EQUAL(800E3, testingCANAdapter.m_baudRate);

    executeProtocolCycle(testingSerialAdapter.writeInput("S8"));
    TEST_ASSERT_EQUAL(1000E3, testingCANAdapter.m_baudRate);
}

/**************************************************************************************************/

/**
 *  Test set CAN BTR Registers
 */
static void testCanBtr(void)
{
    executeProtocolCycle(testingSerialAdapter.writeInput("s0000"));
    TEST_ASSERT_EQUAL(0x00, testingCANAdapter.m_btr0);
    TEST_ASSERT_EQUAL(0x00, testingCANAdapter.m_btr1);

    executeProtocolCycle(testingSerialAdapter.writeInput("s031C"));
    TEST_ASSERT_EQUAL(0x03, testingCANAdapter.m_btr0);
    TEST_ASSERT_EQUAL(0x1C, testingCANAdapter.m_btr1);

    executeProtocolCycle(testingSerialAdapter.writeInput("sFFFF"));
    TEST_ASSERT_EQUAL(0xFF, testingCANAdapter.m_btr0);
    TEST_ASSERT_EQUAL(0xFF, testingCANAdapter.m_btr1);
}

/**************************************************************************************************/

/**
 *  Test Open Normal CAN Channel
 */
static void testCanOpenNormal(void)
{
    testingCANAdapter.m_currentState = CANInterface::CLOSED;
    executeProtocolCycle(testingSerialAdapter.writeInput("O"));
    TEST_ASSERT_EQUAL(1, testingCANAdapter.getChannelState());

    testingCANAdapter.m_currentState = CANInterface::NORMAL;
    executeProtocolCycle(testingSerialAdapter.writeInput("O"));
    TEST_ASSERT_EQUAL(1, testingCANAdapter.getChannelState());

    testingCANAdapter.m_currentState = CANInterface::LISTEN_ONLY;
    executeProtocolCycle(testingSerialAdapter.writeInput("O"));
    TEST_ASSERT_EQUAL(2, testingCANAdapter.getChannelState());
}

/**************************************************************************************************/

/**
 *  Test Open Listen Only CAN Channel
 */
static void testCanOpenListenOnly(void)
{
    testingCANAdapter.m_currentState = CANInterface::CLOSED;
    executeProtocolCycle(testingSerialAdapter.writeInput("L"));
    TEST_ASSERT_EQUAL(2, testingCANAdapter.getChannelState());

    testingCANAdapter.m_currentState = CANInterface::CLOSED;
    executeProtocolCycle(testingSerialAdapter.writeInput("L0"));
    TEST_ASSERT_EQUAL(0, testingCANAdapter.getChannelState());

    testingCANAdapter.m_currentState = CANInterface::NORMAL;
    executeProtocolCycle(testingSerialAdapter.writeInput("L"));
    TEST_ASSERT_EQUAL(1, testingCANAdapter.getChannelState());

    testingCANAdapter.m_currentState = CANInterface::LISTEN_ONLY;
    executeProtocolCycle(testingSerialAdapter.writeInput("L"));
    TEST_ASSERT_EQUAL(2, testingCANAdapter.getChannelState());
}

/**************************************************************************************************/

/**
 * Test Close CAN Channel
 */
static void testCanClose(void)
{
    testingCANAdapter.setState(CANInterface::NORMAL);
    executeProtocolCycle(testingSerialAdapter.writeInput("C"));
    TEST_ASSERT_EQUAL(0, testingCANAdapter.getChannelState());

    testingCANAdapter.setState(CANInterface::LISTEN_ONLY);
    executeProtocolCycle(testingSerialAdapter.writeInput("C"));
    TEST_ASSERT_EQUAL(0, testingCANAdapter.getChannelState());
}

/**************************************************************************************************/

/**
 * Test Send STD Frame
 */
static void testTxStd(void)
{
    testingCANAdapter.setState(CANInterface::NORMAL);
    testingCANAdapter.setBaudrate(500E3);

    testingCANAdapter.clearOutputFrame();
    executeProtocolCycle(testingSerialAdapter.writeInput("t0010"));
    testingCANAdapter.enterInputFrame(0x001, false, false, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    TEST_ASSERT_TRUE_MESSAGE(testingCANAdapter.compareFrames(testingCANAdapter.m_inputFrame,
                                                             testingCANAdapter.m_outputFrame),
                             "Frame Compare");

    testingCANAdapter.clearOutputFrame();
    executeProtocolCycle(testingSerialAdapter.writeInput("t1FF81122334455667788"));
    testingCANAdapter.enterInputFrame(0x1FF, false, false, 8, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88);
    TEST_ASSERT_TRUE_MESSAGE(testingCANAdapter.compareFrames(testingCANAdapter.m_inputFrame,
                                                             testingCANAdapter.m_outputFrame),
                             "Frame Compare");

    testingCANAdapter.clearOutputFrame();
    executeProtocolCycle(testingSerialAdapter.writeInput("t1234AABBCCDD"));
    testingCANAdapter.enterInputFrame(0x123, false, false, 4, 0xAA, 0xBB, 0xCC, 0xDD, 0, 0, 0, 0);
    TEST_ASSERT_TRUE_MESSAGE(testingCANAdapter.compareFrames(testingCANAdapter.m_inputFrame,
                                                             testingCANAdapter.m_outputFrame),
                             "Frame Compare");

    testingCANAdapter.clearOutputFrame();
    testingCANAdapter.m_currentState = CANInterface::CLOSED;
    executeProtocolCycle(testingSerialAdapter.writeInput("t1234AABBCCDD"));
    testingCANAdapter.enterInputFrame(0x000, false, false, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    TEST_ASSERT_TRUE_MESSAGE(testingCANAdapter.compareFrames(testingCANAdapter.m_inputFrame,
                                                             testingCANAdapter.m_outputFrame),
                             "Frame Compare");

    testingCANAdapter.clearOutputFrame();
    testingCANAdapter.m_currentState = CANInterface::LISTEN_ONLY;
    executeProtocolCycle(testingSerialAdapter.writeInput("t1234AABBCCDD"));
    testingCANAdapter.enterInputFrame(0x000, false, false, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    TEST_ASSERT_TRUE_MESSAGE(testingCANAdapter.compareFrames(testingCANAdapter.m_inputFrame,
                                                             testingCANAdapter.m_outputFrame),
                             "Frame Compare");
}

/**************************************************************************************************/

/**
 *  Test Send EXT Frame
 */
static void testTxExt(void)
{
    testingCANAdapter.setState(CANInterface::NORMAL);
    testingCANAdapter.setBaudrate(500E3);

    testingCANAdapter.clearOutputFrame();
    testingCANAdapter.m_currentState = CANInterface::NORMAL;
    executeProtocolCycle(testingSerialAdapter.writeInput("T000000000"));
    testingCANAdapter.enterInputFrame(0x000, false, true, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    TEST_ASSERT_TRUE_MESSAGE(testingCANAdapter.compareFrames(testingCANAdapter.m_inputFrame,
                                                             testingCANAdapter.m_outputFrame),
                             "Frame Compare");

    testingCANAdapter.clearOutputFrame();
    testingCANAdapter.m_currentState = CANInterface::NORMAL;
    executeProtocolCycle(testingSerialAdapter.writeInput("T1FFFFFFF81122334455667788"));
    testingCANAdapter.enterInputFrame(0x1FFFFFFF, false, true, 8, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88);
    TEST_ASSERT_TRUE_MESSAGE(testingCANAdapter.compareFrames(testingCANAdapter.m_inputFrame,
                                                             testingCANAdapter.m_outputFrame),
                             "Frame Compare");

    testingCANAdapter.clearOutputFrame();
    testingCANAdapter.m_currentState = CANInterface::NORMAL;
    executeProtocolCycle(testingSerialAdapter.writeInput("T0000ABCD411223344"));
    testingCANAdapter.enterInputFrame(0x0000ABCD, false, true, 4, 0x11, 0x22, 0x33, 0x44, 0, 0, 0, 0);
    TEST_ASSERT_TRUE_MESSAGE(testingCANAdapter.compareFrames(testingCANAdapter.m_inputFrame,
                                                             testingCANAdapter.m_outputFrame),
                             "Frame Compare");

    testingCANAdapter.clearOutputFrame();
    testingCANAdapter.m_currentState = CANInterface::CLOSED;
    executeProtocolCycle(testingSerialAdapter.writeInput("T0000ABCD411223344"));
    testingCANAdapter.enterInputFrame(0x000, false, false, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    TEST_ASSERT_TRUE_MESSAGE(testingCANAdapter.compareFrames(testingCANAdapter.m_inputFrame,
                                                             testingCANAdapter.m_outputFrame),
                             "Frame Compare");

    testingCANAdapter.clearOutputFrame();
    testingCANAdapter.m_currentState = CANInterface::LISTEN_ONLY;
    executeProtocolCycle(testingSerialAdapter.writeInput("T0000ABCD411223344"));
    testingCANAdapter.enterInputFrame(0x000, false, false, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    TEST_ASSERT_TRUE_MESSAGE(testingCANAdapter.compareFrames(testingCANAdapter.m_inputFrame,
                                                             testingCANAdapter.m_outputFrame),
                             "Frame Compare");
}

/**************************************************************************************************/

/**
 *  Test Send STD RTR Frame
 */
static void testTxStdRtr(void)
{
    testingCANAdapter.clearOutputFrame();
    testingCANAdapter.m_currentState = CANInterface::NORMAL;
    executeProtocolCycle(testingSerialAdapter.writeInput("r0000"));
    testingCANAdapter.enterInputFrame(0x000, true, false, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    TEST_ASSERT_TRUE_MESSAGE(testingCANAdapter.compareFrames(testingCANAdapter.m_inputFrame,
                                                             testingCANAdapter.m_outputFrame),
                             "Frame Compare");

    testingCANAdapter.clearOutputFrame();
    testingCANAdapter.m_currentState = CANInterface::NORMAL;
    executeProtocolCycle(testingSerialAdapter.writeInput("r00081122334455667788"));
    testingCANAdapter.enterInputFrame(0x000, false, false, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    TEST_ASSERT_TRUE_MESSAGE(testingCANAdapter.compareFrames(testingCANAdapter.m_inputFrame,
                                                             testingCANAdapter.m_outputFrame),
                             "Frame Compare");

    testingCANAdapter.clearOutputFrame();
    testingCANAdapter.m_currentState = CANInterface::NORMAL;
    executeProtocolCycle(testingSerialAdapter.writeInput("r1FF8"));
    testingCANAdapter.enterInputFrame(0x1FF, true, false, 8, 0, 0, 0, 0, 0, 0, 0, 0);
    TEST_ASSERT_TRUE_MESSAGE(testingCANAdapter.compareFrames(testingCANAdapter.m_inputFrame,
                                                             testingCANAdapter.m_outputFrame),
                             "Frame Compare");

    testingCANAdapter.clearOutputFrame();
    testingCANAdapter.m_currentState = CANInterface::NORMAL;
    executeProtocolCycle(testingSerialAdapter.writeInput("r1234"));
    testingCANAdapter.enterInputFrame(0x123, true, false, 4, 0, 0, 0, 0, 0, 0, 0, 0);
    TEST_ASSERT_TRUE_MESSAGE(testingCANAdapter.compareFrames(testingCANAdapter.m_inputFrame,
                                                             testingCANAdapter.m_outputFrame),
                             "Frame Compare");

    testingCANAdapter.clearOutputFrame();
    testingCANAdapter.m_currentState = CANInterface::CLOSED;
    executeProtocolCycle(testingSerialAdapter.writeInput("r1234AABBCCDD"));
    testingCANAdapter.enterInputFrame(0x000, false, false, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    TEST_ASSERT_TRUE_MESSAGE(testingCANAdapter.compareFrames(testingCANAdapter.m_inputFrame,
                                                             testingCANAdapter.m_outputFrame),
                             "Frame Compare");

    testingCANAdapter.clearOutputFrame();
    testingCANAdapter.m_currentState = CANInterface::LISTEN_ONLY;
    executeProtocolCycle(testingSerialAdapter.writeInput("r1234AABBCCDD"));
    testingCANAdapter.enterInputFrame(0x000, false, false, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    TEST_ASSERT_TRUE_MESSAGE(testingCANAdapter.compareFrames(testingCANAdapter.m_inputFrame,
                                                             testingCANAdapter.m_outputFrame),
                             "Frame Compare");
}

/**************************************************************************************************/

/**
 * Test Send EXT RTR Frame
 */
static void testTxExtRtr(void)
{
    testingCANAdapter.clearOutputFrame();
    testingCANAdapter.m_currentState = CANInterface::NORMAL;
    executeProtocolCycle(testingSerialAdapter.writeInput("R000000000"));
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(0x0000000, testingCANAdapter.m_outputFrame.m_id, "ID");
    testingCANAdapter.enterInputFrame(0x0000000, true, true, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    TEST_ASSERT_TRUE_MESSAGE(testingCANAdapter.compareFrames(testingCANAdapter.m_inputFrame,
                                                             testingCANAdapter.m_outputFrame),
                             "Frame Compare");

    testingCANAdapter.clearOutputFrame();
    testingCANAdapter.m_currentState = CANInterface::NORMAL;
    executeProtocolCycle(testingSerialAdapter.writeInput("R1FFFFFFF8"));
    testingCANAdapter.enterInputFrame(0x1FFFFFFF, true, true, 8, 0, 0, 0, 0, 0, 0, 0, 0);
    TEST_ASSERT_TRUE_MESSAGE(testingCANAdapter.compareFrames(testingCANAdapter.m_inputFrame,
                                                             testingCANAdapter.m_outputFrame),
                             "Frame Compare");

    testingCANAdapter.clearOutputFrame();
    testingCANAdapter.m_currentState = CANInterface::NORMAL;
    executeProtocolCycle(testingSerialAdapter.writeInput("R0000ABCD4"));
    testingCANAdapter.enterInputFrame(0x0000ABCD, true, true, 4, 0, 0, 0, 0, 0, 0, 0, 0);
    TEST_ASSERT_TRUE_MESSAGE(testingCANAdapter.compareFrames(testingCANAdapter.m_inputFrame,
                                                             testingCANAdapter.m_outputFrame),
                             "Frame Compare");

    testingCANAdapter.clearOutputFrame();
    testingCANAdapter.m_currentState = CANInterface::NORMAL;
    executeProtocolCycle(testingSerialAdapter.writeInput("R0000ABCD412233187"));
    testingCANAdapter.enterInputFrame(0x000, false, false, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    TEST_ASSERT_TRUE_MESSAGE(testingCANAdapter.compareFrames(testingCANAdapter.m_inputFrame,
                                                             testingCANAdapter.m_outputFrame),
                             "Frame Compare");

    testingCANAdapter.clearOutputFrame();
    testingCANAdapter.m_currentState = CANInterface::CLOSED;
    executeProtocolCycle(testingSerialAdapter.writeInput("R0000ABCD4"));
    testingCANAdapter.enterInputFrame(0x000, false, false, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    TEST_ASSERT_TRUE_MESSAGE(testingCANAdapter.compareFrames(testingCANAdapter.m_inputFrame,
                                                             testingCANAdapter.m_outputFrame),
                             "Frame Compare");

    testingCANAdapter.clearOutputFrame();
    testingCANAdapter.m_currentState = CANInterface::LISTEN_ONLY;
    executeProtocolCycle(testingSerialAdapter.writeInput("R0000ABCD4"));
    testingCANAdapter.enterInputFrame(0x000, false, false, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    TEST_ASSERT_TRUE_MESSAGE(testingCANAdapter.compareFrames(testingCANAdapter.m_inputFrame,
                                                             testingCANAdapter.m_outputFrame),
                             "Frame Compare");
}

/**************************************************************************************************/

/**
 * Test set Filter Mode
 */
static void testFilterMode(void)
{
    testingCANAdapter.m_currentState = CANInterface::CLOSED;
    testingCANAdapter.m_filterMode = 0;
    executeProtocolCycle(testingSerialAdapter.writeInput("W0"));
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_filterMode, "FilterMode Dual");

    testingCANAdapter.m_filterMode = 0;
    executeProtocolCycle(testingSerialAdapter.writeInput("W1"));
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(1, testingCANAdapter.m_filterMode, "FilterMode Dual");

    testingCANAdapter.m_filterMode = 0;
    executeProtocolCycle(testingSerialAdapter.writeInput("W"));
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_filterMode, "FilterMode Dual");

    testingCANAdapter.m_filterMode = 0;
    executeProtocolCycle(testingSerialAdapter.writeInput("W2"));
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_filterMode, "FilterMode Dual");

    testingCANAdapter.m_filterMode = 1;
    executeProtocolCycle(testingSerialAdapter.writeInput("W0"));
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, testingCANAdapter.m_filterMode, "FilterMode Dual");

    testingCANAdapter.m_currentState = CANInterface::NORMAL;
    testingCANAdapter.m_filterMode = 1;
    executeProtocolCycle(testingSerialAdapter.writeInput("W0"));
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(1, testingCANAdapter.m_filterMode, "FilterMode Dual");
}

/**************************************************************************************************/

/**
 *  Test set ACRn
 */
static void testAcnRegister(void)
{
    for (int i = 0; i < 4; i++)
    {
        testingCANAdapter.m_ACRn.m_filterBytes[i] = 0;
    }
    testingCANAdapter.m_currentState = CANInterface::CLOSED;
    executeProtocolCycle(testingSerialAdapter.writeInput("MFFFFFFFF"));
    for (int i = 0; i < 4; i++)
    {
        TEST_ASSERT_EQUAL_UINT8(0xFF, testingCANAdapter.m_ACRn.m_filterBytes[i]);
    }

    for (int i = 0; i < 4; i++)
    {
        testingCANAdapter.m_ACRn.m_filterBytes[i] = 0;
    }
    testingCANAdapter.m_currentState = CANInterface::CLOSED;
    executeProtocolCycle(testingSerialAdapter.writeInput("MABCDEF01"));
    TEST_ASSERT_EQUAL_UINT8(0xAB, testingCANAdapter.m_ACRn.m_filterBytes[0]);
    TEST_ASSERT_EQUAL_UINT8(0xCD, testingCANAdapter.m_ACRn.m_filterBytes[1]);
    TEST_ASSERT_EQUAL_UINT8(0xEF, testingCANAdapter.m_ACRn.m_filterBytes[2]);
    TEST_ASSERT_EQUAL_UINT8(0x01, testingCANAdapter.m_ACRn.m_filterBytes[3]);
}

/**************************************************************************************************/

/**
 *  Test set AMRn
 */
static void testAmnRegister(void)
{
    for (int i = 0; i < 4; i++)
    {
        testingCANAdapter.m_AMRn.m_filterBytes[i] = 0;
    }
    testingCANAdapter.m_currentState = CANInterface::CLOSED;
    executeProtocolCycle(testingSerialAdapter.writeInput("mFFFFFFFF"));
    for (int i = 0; i < 4; i++)
    {
        TEST_ASSERT_EQUAL_UINT8(0xFF, testingCANAdapter.m_AMRn.m_filterBytes[i]);
    }

    for (int i = 0; i < 4; i++)
    {
        testingCANAdapter.m_AMRn.m_filterBytes[i] = 0;
    }
    testingCANAdapter.m_currentState = CANInterface::CLOSED;
    executeProtocolCycle(testingSerialAdapter.writeInput("mABCDEF01"));
    TEST_ASSERT_EQUAL_UINT8(0xAB, testingCANAdapter.m_AMRn.m_filterBytes[0]);
    TEST_ASSERT_EQUAL_UINT8(0xCD, testingCANAdapter.m_AMRn.m_filterBytes[1]);
    TEST_ASSERT_EQUAL_UINT8(0xEF, testingCANAdapter.m_AMRn.m_filterBytes[2]);
    TEST_ASSERT_EQUAL_UINT8(0x01, testingCANAdapter.m_AMRn.m_filterBytes[3]);
}

/**************************************************************************************************/

/**
 *  Test set Serial Baudrate
 */
static void testSerialBaudrate(void)
{
    testingCANAdapter.m_currentState = CANInterface::CLOSED;
    executeProtocolCycle(testingSerialAdapter.writeInput("U0"));
    TEST_ASSERT_EQUAL_UINT32(230400, testingSerialAdapter.m_serialBaudrate);
    TEST_ASSERT_EQUAL_STRING("U0", testingNVMAdapter.m_outputString.c_str());

    testingSerialAdapter.m_serialBaudrate = 115200;
    executeProtocolCycle(testingSerialAdapter.writeInput("U1"));
    TEST_ASSERT_EQUAL_UINT32(115200, testingSerialAdapter.m_serialBaudrate);
    TEST_ASSERT_EQUAL_STRING("U1", testingNVMAdapter.m_outputString.c_str());

    testingSerialAdapter.m_serialBaudrate = 115200;

    executeProtocolCycle(testingSerialAdapter.writeInput("U2"));
    TEST_ASSERT_EQUAL_UINT32(57600, testingSerialAdapter.m_serialBaudrate);
    testingSerialAdapter.m_serialBaudrate = 115200;
    TEST_ASSERT_EQUAL_STRING("U2", testingNVMAdapter.m_outputString.c_str());

    executeProtocolCycle(testingSerialAdapter.writeInput("U3"));
    TEST_ASSERT_EQUAL_UINT32(38400, testingSerialAdapter.m_serialBaudrate);
    testingSerialAdapter.m_serialBaudrate = 115200;
    TEST_ASSERT_EQUAL_STRING("U3", testingNVMAdapter.m_outputString.c_str());

    executeProtocolCycle(testingSerialAdapter.writeInput("U4"));
    TEST_ASSERT_EQUAL_UINT32(19200, testingSerialAdapter.m_serialBaudrate);
    TEST_ASSERT_EQUAL_STRING("U4", testingNVMAdapter.m_outputString.c_str());

    executeProtocolCycle(testingSerialAdapter.writeInput("U"));
    TEST_ASSERT_EQUAL_UINT32(19200, testingSerialAdapter.m_serialBaudrate);
    TEST_ASSERT_EQUAL_STRING("U4", testingNVMAdapter.m_outputString.c_str());

    executeProtocolCycle(testingSerialAdapter.writeInput("'U54'"));
    TEST_ASSERT_EQUAL_UINT32(19200, testingSerialAdapter.m_serialBaudrate);
    TEST_ASSERT_EQUAL_STRING("U4", testingNVMAdapter.m_outputString.c_str());
}

/**************************************************************************************************/

/**
 *  Test get Version
 */
static void testVersion(void)
{
    executeProtocolCycle(testingSerialAdapter.writeInput("V"));
    TEST_ASSERT_EQUAL_STRING("V0101\r", testingSerialAdapter.m_outputString.c_str());
}

/**************************************************************************************************/

/**
 *  Test get Serial number
 */
static void testSerialNumber(void)
{
    executeProtocolCycle(testingSerialAdapter.writeInput("N"));
    TEST_ASSERT_EQUAL_STRING("NNT32\r", testingSerialAdapter.m_outputString.c_str());
}

/**************************************************************************************************/

/**
 *  Test set Timestamp mode
 */
static void testTimestamp(void)
{
    executeProtocolCycle(testingSerialAdapter.writeInput("Z0"));
    TEST_ASSERT_EQUAL_UINT32(0, testingNVMAdapter.m_outputInt);

    executeProtocolCycle(testingSerialAdapter.writeInput("Z1"));
    TEST_ASSERT_EQUAL_UINT32(1, testingNVMAdapter.m_outputInt);

    executeProtocolCycle(testingSerialAdapter.writeInput("Z2"));
    TEST_ASSERT_EQUAL_UINT32(1, testingNVMAdapter.m_outputInt);
}

/**************************************************************************************************/

/**
 *  Test set Autostart Mode
 */
static void testAutostart(void)
{
    testingCANAdapter.m_currentState = CANInterface::NORMAL;
    executeProtocolCycle(testingSerialAdapter.writeInput("Q0"));
    TEST_ASSERT_EQUAL_UINT32(0, testingNVMAdapter.m_outputInt);

    executeProtocolCycle(testingSerialAdapter.writeInput("Q1"));
    TEST_ASSERT_EQUAL_UINT32(1, testingNVMAdapter.m_outputInt);

    executeProtocolCycle(testingSerialAdapter.writeInput("Q2"));
    TEST_ASSERT_EQUAL_UINT32(2, testingNVMAdapter.m_outputInt);

    executeProtocolCycle(testingSerialAdapter.writeInput("Q3"));
    TEST_ASSERT_EQUAL_UINT32(2, testingNVMAdapter.m_outputInt);
}

/* EXTERNAL FUNCTIONS *****************************************************************************/

/**
 * Setup a test. This function will be called before every test by unity.
 */
extern void setUp(void)
{
    /* Not used. */
}

/**************************************************************************************************/

/**
 * Clean up test. This function will be called after every test by unity.
 */
extern void tearDown(void)
{
    /* Not used. */
}

/* INTERNAL FUNCTIONS *****************************************************************************/

/**************************************************************************************************/

/**
 *  Runs Lawicel Cycle the amount of times specified
 * 
 *  @param[in] cycles Amount of Lawicel cycles to run/Simulate
 */
static void executeProtocolCycle(uint8_t cycles)
{
    for (uint8_t i = 0; i < cycles; i++)
    {
        ProtocolTest.executeCycle();
    }
}
