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

/**
 * @addtogroup HPK Hardware Porting Kit
 * @{
 * @par The Hardware Porting Kit
 * HPK is the next evolution of the well-defined Hardware Abstraction Layer
 * (HAL), but augmented with more comprehensive documentation and test suites
 * that OEM or SOC vendors can use to self-certify their ports before taking
 * them to RDKM for validation or to an operator for final integration and
 * deployment. The Hardware Porting Kit effectively enables an OEM and/or SOC
 * vendor to self-certify their own Video Accelerator devices, with minimal RDKM
 * assistance.
 *
 */
/**
 * @addtogroup RDKV_WIFI RDK-V WiFi
 * @{
 */
/**
 * @defgroup RDKV_WIFI_HALTEST RDK-V WiFi HAL Tests
 * @{
 */
/**
 * @defgroup RDKV_WIFI_HALTEST_MAIN RDKV WiFi HAL Test Main File
 * @{
 * @parblock
 *
 * ### Tests for RDK-V WiFi HAL :
 *
 * This is to ensure that the API meets the operational requirements of the module across all vendors.
 *
 * **Pre-Conditions:**  None @n
 * **Dependencies:** None @n
 *
 * Refer to API Definition specification documentation : [rdkv-wifi_halSpec.md](../../docs/pages/rdkv-wifi_halSpec.md)
 * @endparblock
 *
 */

/**
* @file main.c
*
*/

#include <ut.h>
#include <ut_log.h>
#include <stdlib.h>
#include <glib.h>
#include "wifi_common_hal.h"

GKeyFile *key_file;

extern int register_hal_l1_tests( void );

int WiFi_InitPreReq(){
    int ret = 0;
    ret = wifi_init();
    if (ret == 0)
    {
        UT_LOG("WiFi init returned success");
        return 0;
    }
    else
    {
        UT_LOG("WiFi init returned failure");
        UT_FAIL_FATAL("WiFi initialization with config pre-requisite failed");
    }
    return -1;
}

int WiFi_InitWithConfigPreReq()
{
    int ret = 0;
    wifi_halConfig_t conf;
    strcpy(conf.wlan_Interface,"wlan0");
    ret = wifi_initWithConfig(&conf);
    if (ret == 0)
    {
        UT_LOG("WiFi init with config returned success");
        return 0;
    }
    else
    {
        UT_LOG("WiFi init with config returned failure");
        UT_FAIL_FATAL("WiFi initialization with config pre-requisite failed");
    }
    return -1;
}

int WiFi_UnInitPosReq(){
    int ret = 0;
    ret = wifi_uninit();
    if (ret == 0)
    {
        UT_LOG("WiFi uninit returned success");
        return 0;
    }
    else
    {
        UT_LOG("WiFi uninit returned failure");
        UT_FAIL_FATAL("WiFi uninit post-requisite failed");
    }
    return -1;
}

GKeyFile *KeyFile_new(char *config_FilePath)
{
    GError *error = NULL;
    GKeyFile *key_file = NULL;
    key_file = g_key_file_new();

    if(!key_file) {
        UT_LOG("Failed to g_key_file_new()");
        return NULL;
    }

    if(!g_key_file_load_from_file(key_file, config_FilePath, G_KEY_FILE_KEEP_COMMENTS, &error))
    {
        UT_LOG("Failed with \"%s\"", error->message);
        return NULL;
    }
    return key_file;
}

void KeyFile_delete(GKeyFile *key_file)
{
    if(key_file) g_key_file_free(key_file);
}

char *Config_key_new(GKeyFile *key_file, char *test_case, char *key)
{
    if (!key_file || !test_case || !key)
    {
        UT_LOG("key_file or test_case or key is null");
        return NULL;
    }
    if (!g_key_file_has_group(key_file, test_case))
    {
        UT_LOG("Test case not found: %s\n", test_case);
        return NULL;
    }
    char *key_value = g_key_file_get_string(key_file, test_case, key, NULL);

    return key_value;
}

void Config_key_delete(char *key)
{
    g_free(key);
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

    key_file = KeyFile_new ("/opt/wifi_hal_l1_test_config");
    if (!key_file) {
        printf("Failed to read /opt/wifi_hal_l1_test_config");
    }

    /* Begin test executions */
    UT_run_tests();

    KeyFile_delete(key_file);

    return 0;
}

/** @} */ // End of RDKV_WIFI_HALTEST_MAIN
/** @} */ // End of RDKV_WIFI_HALTEST
/** @} */ // End of RDKV_WIFI
/** @} */ // End of HPK
