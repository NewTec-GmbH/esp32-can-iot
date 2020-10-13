#ifndef TEST_CAN_ADAPTER_H_
#define TEST_CAN_ADAPTER_H_

#include <CANInterface.h>
#include <stdint.h>

class testCAN : public CANInterface
{
public:
    testCAN() : CANInterface(),
                m_baudrate(0),
                m_currentstate(CLOSED),
                m_BTR0(0),
                m_BTR1(0)
    {
    }

    ~testCAN()
    {
    }

    uint8_t send(const Frame &Frame)
    {
        m_outputFrame = Frame;
        return 0;
    }

    uint8_t setState(const BUS_STATE state)
    {
        switch (state)
        {
        case CLOSED:
            m_currentstate = CLOSED;
            return 0;

        case NORMAL:
            if (m_baudrate == 0)
            {
                return 1;
            }
            m_currentstate = NORMAL;
            return 0;

        case LISTEN_ONLY:
            if (m_baudrate == 0)
            {
                return 1;
            }
            m_currentstate = LISTEN_ONLY;
            return 0;

        default:
            return 1;
        }
    }

    uint8_t setBaudrate(const long baudrate)
    {
        m_baudrate = baudrate;
        return 0;
    }

    uint8_t setBTR(const uint8_t BTR0, const uint8_t BTR1)
    {
        m_BTR0 = BTR0;
        m_BTR1 = BTR1;
        return 0;
    }

    uint8_t setFilterMode(const bool Filter)
    {
        m_filtermode = Filter;
        return 0;
    }

    uint8_t setACn(const uint8_t *ACn)
    {
        for (int i = 0; i < 4; i++)
        {
            m_ACn[i] = ACn[i];
        }
        return 0;
    }

    uint8_t setAMn(const uint8_t *AMn)
    {
        for (int i = 0; i < 4; i++)
        {
            m_AMn[i] = AMn[i];
        }
        return 0;
    }

    uint8_t getChannelState()
    {
        return m_currentstate;
    }

    uint8_t getStatusFlags(bool *_flags)
    {
        for (int i = 0; i < 8; i++)
        {
            _flags[i] = m_flags[i];
        }
        return 0;
    }

    Frame pollSingle()
    {
        m_inputFrame.ID = 0xFFF;
        return m_inputFrame;
    }

    void writeInputFrame(uint32_t _id, bool _rtr, bool _ext, uint8_t _dlc, uint8_t _data[8])
    {
        m_inputFrame.ID = _id;
        m_inputFrame.RTR = _rtr;
        m_inputFrame.Extended = _ext;
        m_inputFrame.DLC = _dlc;
        for (int i = 0; i < 8; i++)
        {
            m_inputFrame.Data[i] = _data[i];
        }
    }

    void writeFlags(bool _flags[8])
    {
        for (int i = 0; i < 8; i++)
        {
            m_flags[i] = _flags[i];
        }
    }

    Frame getOutputFrame()
    {
        return m_outputFrame;
    }

    long getBaudrate()
    {
        return m_baudrate;
    }

    void clearOutputframe()
    {
        m_outputFrame.ID = 0x000;
        m_outputFrame.DLC = 0;
        m_outputFrame.Extended = false;
        m_outputFrame.RTR = false;
        for (int i = 0; i < 8; i++)
        {
            m_outputFrame.Data[i] = 0;
        }
    }

    long m_baudrate;
    uint8_t m_BTR0;
    uint8_t m_BTR1;
    BUS_STATE m_currentstate;
    bool m_filtermode;
    uint8_t m_ACn[4];
    uint8_t m_AMn[4];
    bool m_flags[8] = {1, 1, 1, 1, 1, 1, 1, 1};
    Frame m_inputFrame;
    Frame m_outputFrame;

private:
};

#endif