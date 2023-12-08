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
 * @defgroup RDKV_WIFI_HALTEST_MAIN RDKV WiFi HALTEST MAIN
 * @{
 */

#include <ut.h>
#include <ut_log.h>
#include <stdlib.h>
#include <glib.h>
#include "wifi_common_hal.h"

#define SSID "AP_SSID"
#define AP_SSID_INVALID "AP_SSID_invalid"
#define PSK "PRESHAREDKEY"
#define EAP_IDENTITY "EAP_IDENTITY"
#define CA_ROOT_CERT "CA_ROOT_CERT"
#define CLIENT_CERT "CLIENT_CERT"
#define PASSPHRASE "PASSPHRASE"
#define PRIVATE_KEY "PRIVATE_KEY"
#define WEP_KEY "WEP_KEY"

extern int register_hal_l1_tests( void );
GKeyFile *key_file = NULL;

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

void Init_Config(char *config_FilePath)
{
    GError *error = NULL;
    key_file = g_key_file_new();

    if(!key_file) {
        UT_LOG("Failed to g_key_file_new()");
        return;
    }

    if(!g_key_file_load_from_file(key_file, config_FilePath, G_KEY_FILE_KEEP_COMMENTS, &error))
        UT_LOG("Failed with \"%s\"", error->message);
    return;
}

void UnInit_Config()
{
    if(key_file) g_key_file_free(key_file);
}

BOOL read_Config(char *test_case, char *ap, char *psk, char *passphrase, char *eapIdentity, char *carootcert, char *clientcert, char *privatekey, char *wepkey)
{
    GError *error = NULL;
    guint group = 0, key = 0;

    if(!key_file) {
        UT_LOG("Init_config not done");
        return 0;
    }
    else
    {
        gsize groups_id, num_keys;
        gchar **groups = NULL, **keys = NULL, *value = NULL;

        groups = g_key_file_get_groups(key_file, &groups_id);

        for(group = 0; group < groups_id; group++)
        {
            UT_LOG("Group %u/%u: \t%s", group, groups_id - 1, groups[group]);
            if(0 == strncasecmp(test_case, groups[group], strlen(groups[group])))
            {
                keys = g_key_file_get_keys(key_file, groups[group], &num_keys, &error);
                for(key = 0; key < num_keys; key++)
                {
                    value = g_key_file_get_value(key_file,	groups[group],	keys[key],	&error);
                    if(0 == strncasecmp(SSID, keys[key], strlen(keys[key])))
                    {
                        UT_LOG("[ \t\tkey %u/%u: \t%s => %s]", key, num_keys - 1, keys[key], value);
                        strcpy(ap, value);
                    }
                    if(0 == strncasecmp(PSK, keys[key], strlen(keys[key])))
                    {
                        UT_LOG("[ \t\tkey %u/%u: \t%s => %s]", key, num_keys - 1, keys[key], value);
                        strcpy(psk, value);
                    }
                    if(0 == strncasecmp(EAP_IDENTITY, keys[key], strlen(keys[key])))
                    {
                        UT_LOG("[ \t\tkey %u/%u: \t%s => %s]", key, num_keys - 1, keys[key], value);
                        strcpy(eapIdentity, value);
                    }
                    if(0 == strncasecmp(CA_ROOT_CERT, keys[key], strlen(keys[key])))
                    {
                        UT_LOG("[ \t\tkey %u/%u: \t%s => %s]", key, num_keys - 1, keys[key], value);
                        strcpy(carootcert, value);
                    }
                    if(0 == strncasecmp(CLIENT_CERT, keys[key], strlen(keys[key])))
                    {
                        UT_LOG("[ \t\tkey %u/%u: \t%s => %s]", key, num_keys - 1, keys[key], value);
                        strcpy(clientcert, value);
                    }
                    if(0 == strncasecmp(PRIVATE_KEY, keys[key], strlen(keys[key])))
                    {
                        UT_LOG("[ \t\tkey %u/%u: \t%s => %s]", key, num_keys - 1, keys[key], value);
                        strcpy(privatekey, value);
                    }
                    if(0 == strncasecmp(PASSPHRASE, keys[key], strlen(keys[key])))
                    {
                        UT_LOG("[ \t\tkey %u/%u: \t%s => %s]", key, num_keys - 1, keys[key], value);
                        strcpy(passphrase, value);
                    }
                    if(0 == strncasecmp(AP_SSID_INVALID, keys[key], strlen(keys[key])))
                    {
                        UT_LOG("[ \t\tkey %u/%u: \t%s => %s]", key, num_keys - 1, keys[key], value);
                        strcpy(ap, value);
                    }
                    if(0 == strncasecmp(WEP_KEY, keys[key], strlen(keys[key])))
                    {
                        UT_LOG("[ \t\tkey %u/%u: \t%s => %s]", key, num_keys - 1, keys[key], value);
                        strcpy(wepkey, value);
                    }
                    if(value) g_free(value);
                }
                if(keys) g_strfreev(keys);
                break;
            }
        }
        if(groups) g_strfreev(groups);
    }

    return 1;
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

    Init_Config ("/opt/wifi_hal_l1_test_config");

    /* Begin test executions */
    UT_run_tests();

    UnInit_Config();

    return 0;
}

/** @} */ // End of RDKV_WIFI_HALTEST_MAIN
/** @} */ // End of RDKV_WIFI_HALTEST
/** @} */ // End of RDKV_WIFI
/** @} */ // End of HPK
