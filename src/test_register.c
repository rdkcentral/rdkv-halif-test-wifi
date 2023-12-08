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
 * @addtogroup RDKV_WIFI_HALTEST RDK-V WiFi HAL Tests
 * @{
 */
/**
 * @defgroup RDKV_WIFI_HALTEST_REGISTER RDKV WiFi HALTEST REGISTER
 * @{
 */

/* L1 Testing Functions */
 
extern int test_wifi_common_hal_register_pre_init_tests (void);
extern int test_wifi_client_hal_register_pre_init_tests (void);
extern int test_wifi_common_hal_register_init_uninit_tests (void);
extern int test_wifi_common_hal_register_post_init_with_config_tests (void);
extern int test_wifi_client_hal_register_post_init_with_config_tests (void);
extern int test_wifi_common_hal_register_post_init_tests (void);
extern int test_wifi_client_hal_register_post_init_tests (void);
 
int register_hal_l1_tests( void )
{
    int registerFailed=0;

    registerFailed |= test_wifi_common_hal_register_pre_init_tests();
    registerFailed |= test_wifi_client_hal_register_pre_init_tests();
    registerFailed |= test_wifi_common_hal_register_init_uninit_tests();
    registerFailed |= test_wifi_common_hal_register_post_init_with_config_tests();
    registerFailed |= test_wifi_client_hal_register_post_init_with_config_tests();
    registerFailed |= test_wifi_common_hal_register_post_init_tests();
    registerFailed |= test_wifi_client_hal_register_post_init_tests();
 
    return registerFailed;
}

/** @} */ // End of RDKV_WIFI_HALTEST_REGISTER
/** @} */ // End of RDKV_WIFI_HALTEST
/** @} */ // End of RDKV_WIFI
/** @} */ // End of HPK
