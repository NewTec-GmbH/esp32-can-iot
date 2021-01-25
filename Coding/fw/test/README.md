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

# Test Main
In this page are located the Tests which are going to be executed. The 
"main" function calls the individual tests between an UNITY_BEGIN() and UNITY_END() commands.
Each Test contains individual checks depending for each variable that we want to observate.
For Example:
- TEST_ASSERT_TRUE(condition): Checks if in the current state the condition is true.
- TEST_ASSERT_EQUAL(expected, current): Checks if the current value equals the expected value.

If any of these checks fail, the whole test will be failed and the main function skips onto the next test.

In this case we are testing the possible Lawicel Commands that can be sent to the Device.

# Test Adapters
Are the implementations of the Lawicel Interfaces in order to test inputs and outputs of the Protocol.