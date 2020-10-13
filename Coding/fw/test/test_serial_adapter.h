#ifndef TEST_SERIAL_ADAPTER_H_
#define TEST_SERIAL_ADAPTER_H_

#include <SerialInterface.h>
#include <WString.h>

class testSerial : public SerialInterface
{
public:

testSerial() : SerialInterface(), m_baudrate(115200), m_status(false)
{
}

~testSerial()
{
}

void begin()
{
}

void end()
{
}

void setBaudrate(long _baudrate)
{
    m_baudrate = _baudrate;
}

String read()
{
    return input;
}

void print(String string)
{
    outputString = string;
}

void print( int num)
{
    outputInt = num;
}

void print(char c)
{
    outputChar = c;
}

String getOutputString()
{
    return outputString;
}

int getOutputInt()
{
    return outputInt;
}

char getOutputChar()
{
    return outputChar;
}

long getBaudrate()
{
    return m_baudrate;
}

bool getStatus()
{
    return m_status;
}

private:

String input;
String outputString;
int outputInt;
char outputChar;
bool m_status;
long m_baudrate;


};
#endif