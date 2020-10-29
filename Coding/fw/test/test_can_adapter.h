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

    uint8_t begin()
    {
        return 0;
    }

    uint8_t end()
    {
        return 0;
    }

    uint8_t send(const Frame &frame)
    {
        m_outputFrame = frame;
        return 0;
    }

    uint8_t setState(BUS_STATE state)
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

    uint8_t setBaudrate(uint32_t baudrate)
    {
        m_baudrate = baudrate;
        return 0;
    }

    uint8_t setBTR(uint8_t btr0, uint8_t btr1)
    {
        m_BTR0 = btr0;
        m_BTR1 = btr1;
        return 0;
    }

    uint8_t setFilterMode(uint8_t filter)
    {
        m_filtermode = filter;
        return 0;
    }

    uint8_t setACn(const uint8_t *acn)
    {
        for (int i = 0; i < 4; i++)
        {
            m_ACn[i] = acn[i];
        }
        return 0;
    }

    uint8_t setAMn(const uint8_t *amn)
    {
        for (int i = 0; i < 4; i++)
        {
            m_AMn[i] = amn[i];
        }
        return 0;
    }

    uint8_t getChannelState()
    {
        return m_currentstate;
    }

    uint8_t getStatusFlags()
    {
        return 0;
    }

    uint8_t pollSingle(Frame& frame)
    {
        frame = m_inputFrame;
        return 0;
    }

    void writeInputFrame(uint32_t _id, bool _rtr, bool _ext, uint8_t _dlc, uint8_t _data[8])
    {
        m_inputFrame.m_id = _id;
        m_inputFrame.m_rtr = _rtr;
        m_inputFrame.m_extended = _ext;
        m_inputFrame.m_dlc = _dlc;
        for (int i = 0; i < 8; i++)
        {
            m_inputFrame.m_data[i] = _data[i];
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
        m_outputFrame.m_id = 0x000;
        m_outputFrame.m_dlc = 0;
        m_outputFrame.m_extended = false;
        m_outputFrame.m_rtr = false;
        for (int i = 0; i < 8; i++)
        {
            m_outputFrame.m_data[i] = 0;
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