# Unit Testing
This directory is intended for PIO Unit Testing and project tests.


# Purpose
Unit Testing is a software testing method by which individual units of
source code, sets of one or more MCU program modules together with associated
control data, usage procedures, and operating procedures, are tested to
determine whether they are fit for use. Unit testing finds problems early
in the development cycle.

More information about PIO Unit Testing:
https://docs.platformio.org/page/plus/unit-testing.html

# Test Environment
In the [platformio.ini](../platformio.ini) file is the *native* environment defined in order to run these tests. This means that the unit tests are not run on the ESP32 but on Windows. 

For this to work is necesary to install a [C++ Compiler](https://dev.to/gamegods3/how-to-install-gcc-in-windows-10-the-easier-way-422j) and use the [Test](../lib/Test) Library in order to emulate the Arduino native libraries.

# Test Main
In this page are located the Tests which are going to be executed. 
The "main" function calls the individual tests between an UNITY_BEGIN() and UNITY_END() commands.
Each Test contains individual checks depending for each variable that we want to observate.
For example:
- TEST_ASSERT_TRUE(condition): Checks if in the current state the condition is true.
- TEST_ASSERT_EQUAL(expected, current): Checks if the current value equals the expected value.

If any of these checks fail, the whole test will be failed and the main function skips onto the next test.

In this case we are testing the possible Lawicel Commands that can be sent to the Device, for example:

```cpp
void test_version(void)
{
    runProtocolExecute(testingSerialAdapter.writeInput("V"));
    TEST_ASSERT_EQUAL_STRING("V0101\r", testingSerialAdapter.m_outputString.c_str());
}
```
The input Command "V" is written as input for the Lawicel Protocol, and gets processed. The result should be a serial output of V followed by the Software Version (0101 in this case), and with '\r' as terminator (as Lawicel specifies). The TEST_ASSERT_EQUAL_STRING method compared the expected string (first parameter) with the output string after the command gets processed (second parameter). If everything works as intended, the check is successful and the Test is Passed.


# Test Adapters
Are the implementations of the Lawicel Interfaces in order to test inputs and outputs of the Protocol.