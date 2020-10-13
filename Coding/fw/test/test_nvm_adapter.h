#ifndef TEST_NVM_ADAPTER_H_
#define TEST_NVM_ADAPTER_H_

#include <NVMInterface.h>
#include <WString.h>

class testNVM : public NVMInterface
{
public:
    testNVM() : NVMInterface()
    {
    }

    ~testNVM()
    {
    }

    void begin()
    {
    }

    void end()
    {
    }

    void save(const char *name, int32_t value)
    {
    }

    void saveString(const char *name, String value)
    {
    }

    uint32_t read(const char *name)
    {
        return 0;
    }

    String readString(const char *name)
    {
        String str;
        String out;
        int counter = 0;

        while (name[counter] != 0)
        {
            str += name[counter];
            counter++;
        }

        if (str == "SerialBaud")
        {
            out = "U1";
        }
        else if (str == "CanBaud")
        {
            out = "S6";
        }
        else if (str == "FilterMode")
        {
            out = "W0";
        }
        else if (str == "FilterACn")
        {
            out = "M00000000";
        }
        else if (str == "FilterAMn")
        {
            out = "mFFFFFFFF";
        }

        return out;
    }

private:
};

#endif