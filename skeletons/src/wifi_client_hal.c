/*
* If not stated otherwise in this file or this component's LICENSE file the
* following copyright and licenses apply:*
* Copyright 2023 RDK Management
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include "wifi_client_hal.h"


INT wifi_getCliWpsConfigMethodsSupported(INT ssidIndex, CHAR* methods)
{
  /*TODO: Implement Me!*/
  (void)ssidIndex;
  (void)methods;
  return (INT)0;
}

INT wifi_getCliWpsConfigMethodsEnabled(INT ssidIndex, CHAR* output_string)
{
  /*TODO: Implement Me!*/
  (void)ssidIndex;
  (void)output_string;
  return (INT)0;
}

INT wifi_setCliWpsConfigMethodsEnabled(INT ssidIndex, CHAR* methodString)
{
  /*TODO: Implement Me!*/
  (void)ssidIndex;
  (void)methodString;
  return (INT)0;
}

INT wifi_setCliWpsEnrolleePin(INT ssidIndex, CHAR* EnrolleePin)
{
  /*TODO: Implement Me!*/
  (void)ssidIndex;
  (void)EnrolleePin;
  return (INT)0;
}

INT wifi_setCliWpsButtonPush(INT ssidIndex)
{
  /*TODO: Implement Me!*/
  (void)ssidIndex;
  return (INT)0;
}

INT wifi_connectEndpoint(INT ssidIndex, CHAR* AP_SSID, wifiSecurityMode_t AP_security_mode, CHAR* AP_security_WEPKey, CHAR* AP_security_PreSharedKey, CHAR* AP_security_KeyPassphrase, INT saveSSID, CHAR* eapIdentity, CHAR* carootcert, CHAR* clientcert, CHAR* privatekey)
{
  /*TODO: Implement Me!*/
  (void)ssidIndex;
  (void)AP_SSID;
  (void)AP_security_mode;
  (void)AP_security_WEPKey;
  (void)AP_security_PreSharedKey;
  (void)AP_security_KeyPassphrase;
  (void)saveSSID;
  (void)eapIdentity;
  (void)carootcert;
  (void)clientcert;
  (void)privatekey;
  return (INT)0;
}

INT wifi_disconnectEndpoint(INT ssidIndex, CHAR* AP_SSID)
{
  /*TODO: Implement Me!*/
  (void)ssidIndex;
  (void)AP_SSID;
  return (INT)0;
}

INT wifi_clearSSIDInfo(INT ssidIndex)
{
  /*TODO: Implement Me!*/
  (void)ssidIndex;
  return (INT)0;
}

void wifi_disconnectEndpoint_callback_register(wifi_disconnectEndpoint_callback callback_proc)
{
  /*TODO: Implement Me!*/
  (void)callback_proc;
}

void wifi_connectEndpoint_callback_register(wifi_connectEndpoint_callback callback_proc)
{
  /*TODO: Implement Me!*/
  (void)callback_proc;
}

void wifi_telemetry_callback_register(wifi_telemetry_ops_t* telemetry_ops)
{
  /*TODO: Implement Me!*/
  (void)telemetry_ops;
}

INT wifi_lastConnected_Endpoint(wifi_pairedSSIDInfo_t* pairedSSIDInfo)
{
  /*TODO: Implement Me!*/
  (void)pairedSSIDInfo;
  return (INT)0;
}

INT wifi_setRoamingControl(int ssidIndex, wifi_roamingCtrl_t* pRoamingCtrl_data)
{
  /*TODO: Implement Me!*/
  (void)ssidIndex;
  (void)pRoamingCtrl_data;
  return (INT)0;
}

INT wifi_getRoamingControl(int ssidIndex, wifi_roamingCtrl_t* pRoamingCtrl_data)
{
  /*TODO: Implement Me!*/
  (void)ssidIndex;
  (void)pRoamingCtrl_data;
  return (INT)0;
}

INT wifi_cancelWpsPairing(void)
{
  /*TODO: Implement Me!*/
  return (INT)0;
}

