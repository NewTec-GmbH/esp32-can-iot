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
@addtogroup Webserver
@{
@file       Web_config.h

Configuration of ESP32 WebServer

* @}
***************************************************************************************************/
#ifndef WEB_CONFIG_H_
#define WEB_CONFIG_H_

/* INCLUDES ***************************************************************************************/
#include "FlashMem.h"

/* C-Interface ************************************************************************************/
extern "C"
{
}

/* CONSTANTS **************************************************************************************/

/**
 *  Handler of Web Configuration and HTML Responses
 */
namespace WebConfig
{
    static const uint32_t DNS_PORT = 53U;       /**< DNS Port */
    static const uint32_t WEBSERVER_PORT = 80U; /**< HTTP Port */

    const String &getWEB_USER(); /**< Get saved Webserver Username */
    const String &getWEB_PASS(); /**< Get saved Webserver Password */

    /**
     *  HTTP Status Codes for as Responses for Client Requests 
     */
    enum StatusCodes
    {
        HTTP_OK = 200,           /**< OK */
        HTTP_BAD_REQUEST = 400,  /**< Bad Request */
        HTTP_UNAUTHORIZED = 401, /**< Unauthorized */
        HTTP_NOT_FOUND = 404     /**< Not Found */
    };

} /* namespace WebConfig */

/* FORWARD DECLARATIONS **************************************************************************/

/* INLINE FUNCTIONS ******************************************************************************/

/* PROTOTYPES ************************************************************************************/
#endif /* WEB_CONFIG_H_ */