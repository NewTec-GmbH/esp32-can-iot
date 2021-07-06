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
@addtogroup Interfaces
@ingroup Lawicel
@{
@file       SerialInterface.h

SerialInterface for Lawicel Protocol

***************************************************************************************************/
#ifndef SERIAL_INTERFACE_H
#define SERIAL_INTERFACE_H

/* INCLUDES ***************************************************************************************/

/* C-Interface ************************************************************************************/
extern "C"
{
}

/* FORWARD DECLARATIONS ***************************************************************************/

/**
 *  Interface of the Lawicel Protocol to the Serial Port of the board. Defines the Methods to read 
 *  and write to the Serial Port, in ordert o communicate with other devices.
 */
class SerialInterface
{
public:
    /* CONSTANTS ******************************************************************************/

    /* TYPES **********************************************************************************/

    /** 
     *  Default constructor creates instance of the class using default values.
     */
    SerialInterface()
    {
    }

    /** 
     *  Default destructor deletes instance of the class.
     */
    virtual ~SerialInterface()
    {
    }

    /** 
     *  Configures and starts the Serial Controller to use the user values.
     * 
     *  @return success
     */
    virtual bool begin() = 0;

    /** 
     *  Stops the Serial Module without destroying the instance.
     * 
     *  @return success
     */
    virtual bool end() = 0;

    /** 
     *  Sets the Baudrate for Serial Communication.
     * 
     *  @param[in] baudrate      Baudrate for Serial Communication
     *  @return success
     */
    virtual bool setBaudrate(uint32_t baudrate) = 0;

    /** 
     *  Reads the Serial Adapter into a buffer.
     * 
     *  @param[in,out] c   Character received on the Serial Interface
     *  @return success
     */
    virtual bool read(char &c) = 0;

    /** 
     *  Prints a String to Serial Adapter.
     * 
     *  @param[in] string     String to be printed
     */
    virtual void print(const String &string) = 0;

    /** 
     *  Prints an Integer to Serial Adapter.
     * 
     *  @param[in] num     Integer to be printed
     */
    virtual void print(uint32_t num) = 0;

    /** 
     *  Prints a Character to Serial Adapter.
     * 
     *  @param[in] c     Character to be printed
     */
    virtual void print(char c) = 0;

private:
};

/* INLINE FUNCTIONS ***************************************************************************/

/* PROTOTYPES *********************************************************************************/

#endif /* SERIAL_INTERFACE_H */

/** @} */