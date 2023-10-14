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
 

#include <ut.h>
#include <ut_log.h>
#include <stdlib.h>
#include "wifi_common_hal.h"

extern int register_hal_l1_tests( void );

void WiFi_InitPreReq(){
    int ret = 0;
    ret = wifi_init();
    if (ret == 0)
    {
        UT_LOG("WiFi init returned success");
    }
    else
    {
        UT_LOG("WiFi init returned failure");
        UT_FAIL_FATAL("WiFi initialization with config pre-requisite failed");
    }
}

void WiFi_InitWithConfigPreReq(){
    int ret = 0;
    wifi_halConfig_t *conf = (wifi_halConfig_t*)malloc(sizeof(wifi_halConfig_t));
    if(conf != NULL){
	strcpy(conf->wlan_Interface,"wlan1");
        ret = wifi_initWithConfig(conf);
        if (ret == 0)
        {
            UT_LOG("WiFi init with config returned success");
        }
        else
        {
           UT_LOG("WiFi init with config returned failure");
           UT_FAIL_FATAL("WiFi initialization with config pre-requisite failed");
        }        
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL_FATAL("Memory allocation with malloc failed");
    }
}

void WiFi_UnInitPosReq(){
    int ret = 0;
    ret = wifi_uninit();
    if (ret == 0)
    {
        UT_LOG("WiFi uninit returned success");
    }
    else
    {
        UT_LOG("WiFi uninit returned failure");
        UT_FAIL_FATAL("WiFi uninit post-requisite failed");
    }
}

 
int main(int argc, char** argv)
{
    int registerReturn = 0;
    /* Register tests as required, then call the UT-main to support switches and triggering */
    UT_init( argc, argv );
    /* Check if tests are registered successfully */
    registerReturn = register_hal_l1_tests();
    if (registerReturn == 0)
    {
        printf("register_hal_l1_tests() returned success");
    }
    else
    {
        printf("register_hal_l1_tests() returned failure");
        return 1;
    }
	
    WiFi_InitPreReq();
    
    /* Begin test executions */
    UT_run_tests();
    
    WiFi_UnInitPosReq();
	
    return 0;
}

