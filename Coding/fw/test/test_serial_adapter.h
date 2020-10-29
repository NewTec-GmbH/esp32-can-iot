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

    uint8_t begin()
    {
        return 0;
    }

    uint8_t end()
    {
        return 0;
    }

    uint8_t setBaudrate(uint32_t baudrate)
    {
        m_baudrate = baudrate;
        return 0;
    }

    uint8_t read(char &c)
    {
        return 0;
    }

    void print(const String &string)
    {
        outputString = string;
    }

    void print(uint32_t num)
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

    void writeInput(String str)
    {
        input = str;
    }

    String input;
    String outputString;
    int outputInt;
    char outputChar;
    bool m_status;
    long m_baudrate;

private:
};
#endif