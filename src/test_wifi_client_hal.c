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
* @file test_wifi_client_hal.c
* @page wifi_client_hal Level 1 Tests
*
* ## Module's Role
* This module includes Level 1 functional tests (success and failure scenarios).
* This is to ensure that the wifi_client_hal APIs meet the requirements across all vendors.
*
* **Pre-Conditions:**  None @n
* **Dependencies:** None @n
*
* Ref to API Definition specification documentation : [halSpec.md](../../../docs/halSpec.md)
*/

#include <ut.h>
#include <ut_log.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "wifi_client_hal.h"

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
        UT_FAIL("WiFi initialization with config pre-requisite failed");
    }
}

void WiFi_InitWithConfigPreReq(){
    int ret = 0;
    wifi_halConfig_t *conf = (wifi_halConfig_t*)malloc(sizeof(wifi_halConfig_t));
    if(conf != NULL){
        ret = wifi_initWithConfig(conf);
        if (ret == 0)
        {
            UT_LOG("WiFi init with config returned success");
        }
        else
        {
           UT_LOG("WiFi init with config returned failure");
           UT_FAIL("WiFi initialization with config pre-requisite failed");
        }        
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
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
        UT_FAIL("WiFi uninit post-requisite failed");
    }
}

/**
* @brief This function checks if wifi_getCliWpsConfigMethodsSupported works as expected, when invoked after calling wifi_init().
*
* This unit test case check whether the function correctly fetches the supported config methods when provided with a valid ssidIndex and an appropriate output buffer.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 001 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking the wifi_getCliWpsConfigMethodsSupported() API with ssidIndex = 1 and methods = valid buffer | ssidIndex = 1, methods = valid buffer | RETURN_OK | Should Pass |
*/
void test_l1_wifi_client_hal_positive1_wifi_getCliWpsConfigMethodsSupported( void )
{
    UT_LOG("Entering test_l1_wifi_client_hal_positive1_wifi_getCliWpsConfigMethodsSupported...\n");
    INT ssidIndex = 1;
    CHAR methods[] = {"\0"};

    UT_LOG("Invoking wifi_getCliWpsConfigMethodsSupported with ssidIndex = 1 and valid buffer for methods");
    INT res = wifi_getCliWpsConfigMethodsSupported(ssidIndex, methods);
    
    UT_LOG("wifi_getCliWpsConfigMethodsSupported API returns : %d and the configuration method is %s",res,methods);
    UT_ASSERT_EQUAL(res, RETURN_OK);
    const char *validMethods[] = {"USBFlashDrive", "Ethernet", "ExternalNFCToken","IntegratedNFCToken", "NFCInterface", "PushButton", "PIN"};
    char *method = strtok(methods, ",");
    while (method != NULL) 
    {
        for (int i = 0; i < sizeof(validMethods) / sizeof(validMethods[0]); i++) 
        {
            if (strcmp(method, validMethods[i]) == 0) 
            {
                UT_LOG("WPS supported methods is %s which is a valid value", method);
                UT_PASS("WPS supported methods  validation success");
            }
            else
            {
                UT_LOG("WPS supported methods is %s which is an invalid value", method);
                UT_FAIL("WPS supported methods validation failed");

            }
        }
        method = strtok(NULL, ",");
    }
    UT_LOG("Exiting test_l1_wifi_client_hal_positive1_wifi_getCliWpsConfigMethodsSupported...\n");
}

/**
* @brief This function checks if wifi_getCliWpsConfigMethodsSupported works as expected, when invoked after calling  wifi_initWithConfig()
*
* This unit test case check whether the function correctly fetches the supported config methods when provided with a valid ssidIndex and an appropriate output buffer.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 002 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking the wifi_getCliWpsConfigMethodsSupported() API with ssidIndex = 1 and methods = valid buffer | ssidIndex = 1, methods = valid buffer | RETURN_OK | Should Pass |
*/
void test_l1_wifi_client_hal_positive2_wifi_getCliWpsConfigMethodsSupported( void )
{
    UT_LOG("Entering test_l1_wifi_client_hal_positive2_wifi_getCliWpsConfigMethodsSupported...\n");
    INT ssidIndex = 1;
    CHAR methods[] = {"\0"};

    WiFi_UnInitPosReq();
    WiFi_InitWithConfigPreReq();

    UT_LOG("Invoking wifi_getCliWpsConfigMethodsSupported with ssidIndex = 1 and valid buffer for methods");
    INT res = wifi_getCliWpsConfigMethodsSupported(ssidIndex, methods);
    
    UT_LOG("wifi_getCliWpsConfigMethodsSupported API returns : %d and the configuration method is %s",res,methods);
    UT_ASSERT_EQUAL(res, RETURN_OK);
    const char *validMethods[] = {"USBFlashDrive", "Ethernet", "ExternalNFCToken","IntegratedNFCToken", "NFCInterface", "PushButton", "PIN"};
    char *method = strtok(methods, ",");
    while (method != NULL) 
    {
        for (int i = 0; i < sizeof(validMethods) / sizeof(validMethods[0]); i++) 
        {
            if (strcmp(method, validMethods[i]) == 0) 
            {
                UT_LOG("WPS supported methods is %s which is a valid value", method);
                UT_PASS("WPS supported methods  validation success");
            }
            else
            {
                UT_LOG("WPS supported methods is %s which is an invalid value", method);
                UT_FAIL("WPS supported methods validation failed");

            }
        }
        method = strtok(NULL, ",");
    }
    WiFi_UnInitPosReq();
    WiFi_InitPreReq();

    UT_LOG("Exiting test_l1_wifi_client_hal_positive2_wifi_getCliWpsConfigMethodsSupported...\n");
}

/**
* @brief This function checks if wifi_getCliWpsConfigMethodsSupported() works as expected
*
* The test verifies the wifi_getCliWpsConfigMethodsSupported API is returns error code when it is invoked with invalid values
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 003  @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:** @n
*| Variation / Step | Description | Test Data |Expected Result |Notes |
*| :----: | --------- | ---------- |-------------- | ----- |
*| 01 | Invoking the wifi_getCliWpsConfigMethodsSupported API with invalid ssidIndex=-1 and methods = valid buffer | ssidIndex=-1 and methods = valid buffer | RETURN_ERR | Should Fail |
*/
void test_l1_wifi_client_hal_negative1_wifi_getCliWpsConfigMethodsSupported( void )
{
    UT_LOG("Entering test_l1_wifi_client_hal_negative1_wifi_getCliWpsConfigMethodsSupported...\n");
    INT ssidIndex = -1;
    CHAR methods[200] = {"\0"};

    UT_LOG("Invoking wifi_getCliWpsConfigMethodsSupported with invalid ssidIndex=-1");
    INT res = wifi_getCliWpsConfigMethodsSupported(ssidIndex, methods);

    UT_LOG("wifi_getCliWpsConfigMethodsSupported retuns %d", res);
    UT_ASSERT_EQUAL(res, RETURN_ERR);
   
    UT_LOG("Exiting test_l1_wifi_client_hal_negative1_wifi_getCliWpsConfigMethodsSupported...\n");
}

/**
* @brief This function checks if wifi_getCliWpsConfigMethodsSupported() works as expected
*
* The test verifies the wifi_getCliWpsConfigMethodsSupported API is returns error code when it is invoked with invalid values
*
* **Test Group ID:** Basic: 01  @n
* **Test Case ID:** 004  @n
* **Priority:** High  @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
* 
* **Test Procedure:** @n
* Below is the outline of steps followed in this test. 
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invokig the wifi_getCliWpsConfigMethodsSupported API with ssidIndex = 1 and invalid methods = NULL | ssidIndex = 1, methods = NULL | RETURN_ERR | Should Fail |
*/ 
void test_l1_wifi_client_hal_negative2_wifi_getCliWpsConfigMethodsSupported( void )
{
    UT_LOG("Entering test_l1_wifi_client_hal_negative2_wifi_getCliWpsConfigMethodsSupported...\n");
    INT ssidIndex = 1;
    CHAR *methods = NULL;
    
    UT_LOG("Invoking wifi_getCliWpsConfigMethodsSupported with NULL buffer for methods");
    INT res = wifi_getCliWpsConfigMethodsSupported(ssidIndex, methods);

    UT_LOG("wifi_getCliWpsConfigMethodsSupported API returns %d", res);
    UT_ASSERT_EQUAL(res, RETURN_ERR);
   
    UT_LOG("Exiting test_l1_wifi_client_hal_negative2_wifi_getCliWpsConfigMethodsSupported...\n");
}

/**
* @brief This function checks if wifi_getCliWpsConfigMethodsSupported works as expected
*
* In this test, the behaviour of wifi_getCliWpsConfigMethodsSupported() is verified when it is called without first initializing Wi-Fi using wifi_init() or wifi_initWithConfig()
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 005 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
* 
* **Test Procedure:** @n
* The steps to run this test and add a line in the below table for each input variation tried in this function.
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking wifi_getCliWpsConfigMethodsSupported API without calling wifi_init() or wifi_initWithConfig() | ssidIndex = 1, methods = valid buffer | RETURN_ERR | Should Fail |
*/
void test_l1_wifi_client_hal_negative3_wifi_getCliWpsConfigMethodsSupported( void )
{
    UT_LOG("Entering test_l1_wifi_client_hal_negative3_wifi_getCliWpsConfigMethodsSupported...\n");
    INT ssidIndex = 1;
    CHAR methods[200] = {"\0"};
    WiFi_UnInitPosReq();
    
    UT_LOG("Invoking wifi_getCliWpsConfigMethodsSupported without calling wifi_init()");
    INT res = wifi_getCliWpsConfigMethodsSupported(ssidIndex, methods);

    UT_LOG("wifi_getCliWpsConfigMethodsSupported API returns %d",res);
    UT_ASSERT_EQUAL(res, RETURN_ERR);

    WiFi_InitPreReq();
    UT_LOG("Exiting test_l1_wifi_client_hal_negative3_wifi_getCliWpsConfigMethodsSupported...\n");
}

/**
 * @brief This function checks if wifi_getCliWpsConfigMethodsEnabled() works as expected, when invoked after wifi_init()
 *
 * The objective of this test function is to invoke the wifi_getCliWpsConfigMethodsEnabled API with valid arguments and verify the return value is as expected
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 006 @n
 * **Priority:** High @n@n
 * 
 * **Pre-Conditions:** None @n
 * **Dependencies:**  None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 * 
 * **Test Procedure:**  @n
 *
 * | Variation / Step     | Description                                                                                           | Test Data                                      | Expected Result | Notes       |
 * | :------------------: | ----------------------------------------------------------------------------------------------------- | -----------------------------------------------| ----------------|-------------|
 * | 01                   | Invoke the wifi_getCliWpsConfigMethodsEnabled API with ssidIndex = 1 and output_string = valid buffer | ssidIndex = 1 and output_string = valid buffer | RETURN_OK       | Should Pass |
 */
void test_l1_wifi_client_hal_positive1_wifi_getCliWpsConfigMethodsEnabled( void ){
    UT_LOG("Entering test_l1_wifi_client_hal_positive1_wifi_getCliWpsConfigMethodsEnabled...");
    
    INT ssidIndex = 1;
    CHAR output_string[] = {"\0"};
    
    UT_LOG("Invoking wifi_getCliWpsConfigMethodsEnabled with input parameter ssidIndex=1 and valid output_string buffer");
    INT return_val = wifi_getCliWpsConfigMethodsEnabled(ssidIndex, output_string);
    
    UT_LOG("wifi_getCliWpsConfigMethodsEnabled API retunrs : %d",return_val);
    UT_ASSERT_EQUAL(return_val, RETURN_OK);
    const char *validMethods[] = {"USBFlashDrive", "Ethernet", "ExternalNFCToken","IntegratedNFCToken", "NFCInterface", "PushButton", "PIN"};
    char *method = strtok(output_string, ",");
    while (method != NULL) 
    {
        for (int i = 0; i < sizeof(validMethods) / sizeof(validMethods[0]); i++) 
        {
            if (strcmp(method, validMethods[i]) == 0) 
            {
                UT_LOG("current WPS methods is %s which is a valid value", method);
                UT_PASS("current WPS methods  validation success");
            }
            else
            {
                UT_LOG("current WPS methods is %s which is an invalid value", method);
                UT_FAIL("current WPS methods validation failed");

            }
        }
        method = strtok(NULL, ",");
    }
    UT_LOG("Exiting test_l1_wifi_client_hal_positive1_wifi_getCliWpsConfigMethodsEnabled...");
}

/**
 * @brief This function checks if wifi_getCliWpsConfigMethodsEnabled() works as expected, when invoked after calling wifi_initWithConfig().
 *
 * The objective of this test function is to invoke the wifi_getCliWpsConfigMethodsEnabled API with valid arguments and verify the return value is as expected
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 007 @n
 * **Priority:** High @n@n
 * 
 * **Pre-Conditions:** None @n
 * **Dependencies:**  None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 * 
 * **Test Procedure:**  @n
 *
 * | Variation / Step     | Description                                                                                           | Test Data                                      | Expected Result | Notes       |
 * | :------------------: | ----------------------------------------------------------------------------------------------------- | -----------------------------------------------| ----------------|-------------|
 * | 01                   | Invoke the wifi_getCliWpsConfigMethodsEnabled API with ssidIndex = 1 and output_string = valid buffer | ssidIndex = 1 and output_string = valid buffer | RETURN_OK       | Should Pass |
 */
void test_l1_wifi_client_hal_positive2_wifi_getCliWpsConfigMethodsEnabled( void ){
    UT_LOG("Entering test_l1_wifi_client_hal_positive2_wifi_getCliWpsConfigMethodsEnabled...");
    
    INT ssidIndex = 1;
    CHAR output_string[100] = {"\0"};
    WiFi_UnInitPosReq();
    WiFi_InitWithConfigPreReq();

    UT_LOG("Invoking wifi_getCliWpsConfigMethodsEnabled with input parameter ssidIndex=1 and valid output_string buffer");
    INT return_val = wifi_getCliWpsConfigMethodsEnabled(ssidIndex, output_string);

    UT_LOG("wifi_getCliWpsConfigMethodsEnabled API returns %d and the WPS configuration methods enabled on the device is %s", return_val,output_string);
    UT_ASSERT_EQUAL(return_val, RETURN_OK);
    const char *validMethods[] = {"USBFlashDrive", "Ethernet", "ExternalNFCToken","IntegratedNFCToken", "NFCInterface", "PushButton", "PIN"};
    char *method = strtok(output_string, ",");
    while (method != NULL) 
    {
        for (int i = 0; i < sizeof(validMethods) / sizeof(validMethods[0]); i++) 
        {
            if (strcmp(method, validMethods[i]) == 0) 
            {
                UT_LOG("WPS supported methods is %s which is a valid value", method);
                UT_PASS("WPS supported methods  validation success");
            }
            else
            {
                UT_LOG("WPS supported methods is %s which is an invalid value", method);
                UT_FAIL("WPS supported methods validation failed");

            }
        }
        method = strtok(NULL, ",");
    }
    WiFi_UnInitPosReq();
    WiFi_InitPreReq();

    UT_LOG("Exiting test_l1_wifi_client_hal_positive2_wifi_getCliWpsConfigMethodsEnabled...");
}

/**
* @brief This function checks if wifi_getCliWpsConfigMethodsEnabled works as expected, when it is invoked without calling wiif_init() or wifi_initWithConfig()
*
* This test checks if the wifi_getCliWpsConfigMethodsEnabled function properly returns an error when it is invoked before calling wifi_init() or wifi_initWithConfig().
*
* **Test Group ID:** Basic: 01  @n
* **Test Case ID:** 008 @n
* **Priority:** High  @n@n
* 
* **Pre-Conditions:** None  @n
* **Dependencies:** None  @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking the wifi_getCliWpsConfigMethodsEnabled API without calling wifi_init() or wifi_initWithConfig()| ssidIndex = 1, output_string = valid buffer | RETURN_ERR | Should Fail |
*/
void test_l1_wifi_client_hal_negative1_wifi_getCliWpsConfigMethodsEnabled( void ){
    
    UT_LOG("Entering test_l1_wifi_client_hal_negative1_wifi_getCliWpsConfigMethodsEnabled...");
    INT ssidIndex = 1;
    CHAR output_string[100] = {"\0"};
    WiFi_UnInitPosReq();

    UT_LOG("Invoking wifi_getCliWpsConfigMethodsEnabled with input parameter ssidIndex=1 and valid output_string buffer without calling wifi_init or wifi_initWithConfig");
    INT return_val = wifi_getCliWpsConfigMethodsEnabled(ssidIndex, output_string);
    
    UT_LOG("wifi_getCliWpsConfigMethodsEnabled API returns %d",return_val);
    UT_ASSERT_EQUAL(return_val, RETURN_ERR);

    WiFi_InitPreReq();
    UT_LOG("Exiting test_l1_wifi_client_hal_negative1_wifi_getCliWpsConfigMethodsEnabled...");
}

/**
 * @brief This function checks if wifi_getCliWpsConfigMethodsEnabled works as expected
 *
 * This test verifies the behavior of wifi_getCliWpsConfigMethodsEnabled() function when it is invoked with an invalid ssidIndex argument. 
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 009 @n
 * **Priority:** High @n@n
 * 
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 * 
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data |Expected Result |Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Invoking wifi_getCliWpsConfigMethodsEnabled with invalid ssidIndex = 2 and output_string = valid buffer | ssidIndex = 2, output_string = valid buffer | RETURN_ERR | Should Fail |
 */
void test_l1_wifi_client_hal_negative2_wifi_getCliWpsConfigMethodsEnabled( void ){
    UT_LOG("Entering test_l1_wifi_client_hal_negative2_wifi_getCliWpsConfigMethodsEnabled...");
    INT ssidIndex = 2;
    CHAR output_string[100] = {"\0"};
    
    UT_LOG("Invoking wifi_getCliWpsConfigMethodsEnabled with invalid input parameter ssidIndex=2 and valid output_string buffer.");
    INT return_val = wifi_getCliWpsConfigMethodsEnabled(ssidIndex, output_string);
    
    UT_LOG("wifi_getCliWpsConfigMethodsEnabled API returns %d",return_val);
    UT_ASSERT_EQUAL(return_val, RETURN_ERR);
    
    UT_LOG("Exiting test_l1_wifi_client_hal_negative2_wifi_getCliWpsConfigMethodsEnabled...");
}

/**
* @brief @brief This function checks if wifi_getCliWpsConfigMethodsEnabled() works as expected
*
* The test verifies, wifi_getCliWpsConfigMethodsEnabled API retunrs error code when NULL is passed as output_string.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 010 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking wifi_getCliWpsConfigMethodsEnabled API with ssidIndex = 1, invalid output_string = NULL  | ssidIndex = 1, output_string = NULL | RETURN_ERR | Should Fail |
*/
void test_l1_wifi_client_hal_negative3_wifi_getCliWpsConfigMethodsEnabled( void ){
    UT_LOG("Entering test_l1_wifi_client_hal_negative3_wifi_getCliWpsConfigMethodsEnabled...");
    INT ssidIndex = 1;
    CHAR *output_string = NULL;
  
    UT_LOG("WiFi init returned success");
    UT_LOG("Invoking wifi_getCliWpsConfigMethodsEnabled with input parameter ssidIndex=1 and NULL output_string buffer.");
    INT return_val = wifi_getCliWpsConfigMethodsEnabled(ssidIndex, output_string);
    
    UT_LOG("wifi_getCliWpsConfigMethodsEnabled API retuns %d",return_val);
    UT_ASSERT_EQUAL(return_val, RETURN_ERR);
    
    UT_LOG("Exiting test_l1_wifi_client_hal_negative3_wifi_getCliWpsConfigMethodsEnabled...");
}

/**
 * @brief This function checks if wifi_setCliWpsConfigMethodsEnabled() works as expected, when it is invoked after calling wifi_init().
 *
 * This test verifies the behavior of wifi_setCliWpsConfigMethodsEnabled API when it is invoked with valid values.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 011 @n
 * **Priority:** High @n@n
 * 
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 * 
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data |Expected Result |Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Invoking the wifi_setCliWpsConfigMethodsEnabled API with ssidIndex = 1, methodString = "USBFlashDrive" | ssidIndex = 1, methodString = "USBFlashDrive" | RETURN_OK | Should Pass |
 */
void test_l1_wifi_client_hal_positive1_wifi_setCliWpsConfigMethodsEnabled(void) {
    UT_LOG("Entering test_l1_wifi_client_hal_positive1_wifi_setCliWpsConfigMethodsEnabled...");
    
    INT ssidIndex = 1;
    CHAR* methodString = "USBFlashDrive";

    UT_LOG("Invoking wifi_setCliWpsConfigMethodsEnabled with ssidIndex 1 and methodString \"USBFlashDrive\".");
    INT returnStatus = wifi_setCliWpsConfigMethodsEnabled(ssidIndex, methodString);
    
    UT_LOG("wifi_setCliWpsConfigMethodsEnabled API returns %d",returnStatus);
    UT_ASSERT_EQUAL(returnStatus, RETURN_OK);

    UT_LOG("Exiting test_l1_wifi_client_hal_positive1_wifi_setCliWpsConfigMethodsEnabled...");
}

/**
 * @brief This function checks if wifi_setCliWpsConfigMethodsEnabled() works as expected, when it is invoked after calling wifi_initWithConfig().
 *
 * This test verifies the behavior of wifi_setCliWpsConfigMethodsEnabled API when it is invoked with valid values.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 012 @n
 * **Priority:** High @n@n
 * 
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 * 
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data |Expected Result |Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Invoking the wifi_setCliWpsConfigMethodsEnabled API with ssidIndex = 1, methodString = "USBFlashDrive" | ssidIndex = 1, methodString = "USBFlashDrive" | RETURN_OK | Should Pass |
 */
void test_l1_wifi_client_hal_positive2_wifi_setCliWpsConfigMethodsEnabled(void) {
    UT_LOG("Entering test_l1_wifi_client_hal_positive2_wifi_setCliWpsConfigMethodsEnabled...");
    INT ssidIndex = 1;
    CHAR* methodString = "USBFlashDrive";
    WiFi_UnInitPosReq();
    WiFi_InitWithConfigPreReq();
    
    UT_LOG("Invoking wifi_setCliWpsConfigMethodsEnabled with ssidIndex 1 and methodString \"USBFlashDrive\".");
    INT returnStatus = wifi_setCliWpsConfigMethodsEnabled(ssidIndex, methodString);
    
    UT_LOG("wifi_setCliWpsConfigMethodsEnabled API returns %d",returnStatus);
    UT_ASSERT_EQUAL(returnStatus, RETURN_OK);
    
    WiFi_UnInitPosReq();
    WiFi_InitPreReq();
    
    UT_LOG("Exiting test_l1_wifi_client_hal_positive2_wifi_setCliWpsConfigMethodsEnabled...");
}

/**
 * @brief This function checks if wifi_setCliWpsConfigMethodsEnabled() works as expected
 *
 * This function specifically tests the 'wifi_setCliWpsConfigMethodsEnabled' API by initializing Wifi and then invoking the API with a valid ssidIndex and a WPS config method string. The test checks if the API returns successfully.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 013 @n
 * **Priority:** High @n@n
 * 
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 * 
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data |Expected Result |Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Invoke the wifi_setCliWpsConfigMethodsEnabled' API with ssidIndex = 1 methodString = "Ethernet" | ssidIndex = 1, methodString = "Ethernet" | RETURN_OK | Should Pass |
 */
void test_l1_wifi_client_hal_positive3_wifi_setCliWpsConfigMethodsEnabled(void) {
    UT_LOG("Entering test_l1_wifi_client_hal_positive3_wifi_setCliWpsConfigMethodsEnabled...");
    
    INT ssidIndex = 1;
    CHAR* methodString = "Ethernet";

    UT_LOG("WiFi init returned success");
        
    UT_LOG("Invoking wifi_setCliWpsConfigMethodsEnabled with ssidIndex 1 and methodString \"Ethernet\".");
    INT returnStatus = wifi_setCliWpsConfigMethodsEnabled(ssidIndex, methodString);
    
    UT_LOG("wifi_setCliWpsConfigMethodsEnabled API returns %d",returnStatus);
    UT_ASSERT_EQUAL(returnStatus, RETURN_OK);
    
    UT_LOG("Exiting test_l1_wifi_client_hal_positive3_wifi_setCliWpsConfigMethodsEnabled...");
}

/**
* @brief This function checks if wifi_setCliWpsConfigMethodsEnabled() works as expected
*
* This test verifies, the wifi_setCliWpsConfigMethodsEnabled() API returns error code when invalid argument is passed 
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 014 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke the wifi_setCliWpsConfigMethodsEnabled API with invalid ssidIndex = 0,methodString = "USBFlashDrive." | ssidIndex = 0, methodString = "USBFlashDrive" | RETURN_ERR | Should Fail|
*/
void test_l1_wifi_client_hal_negative1_wifi_setCliWpsConfigMethodsEnabled(void) {
    UT_LOG("Entering test_l1_wifi_client_hal_negative1_wifi_setCliWpsConfigMethodsEnabled...");
    INT ssidIndex = 0;
    CHAR* methodString = "USBFlashDrive";

    UT_LOG("Invoking wifi_setCliWpsConfigMethodsEnabled with invalid ssidIndex 0 and methodString \"USBFlashDrive\".");
    INT returnStatus = wifi_setCliWpsConfigMethodsEnabled(ssidIndex, methodString);
    
    UT_LOG("wifi_setCliWpsConfigMethodsEnabled API returns %d",returnStatus);
    UT_ASSERT_EQUAL(returnStatus, RETURN_ERR);
  
    UT_LOG("Exiting test_l1_wifi_client_hal_negative1_wifi_setCliWpsConfigMethodsEnabled...");
}

/**
* @brief This function checks if wifi_setCliWpsConfigMethodsEnabled() works as expected
*
* This test checks the behavior of wifi_setCliWpsConfigMethodsEnabled when ssidIndex of value 1 and empty methodString are provided as input. The function is expected to return an error code. The objective of this test is to validate the error handling of the function.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 015 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking wifi_setCliWpsConfigMethodsEnabled with ssidIndex = 1 and methodString = ""(Empty string) | ssidIndex = 1, methodString = "" | RETURN_ERR | Should Fail |
*/
void test_l1_wifi_client_hal_negative2_wifi_setCliWpsConfigMethodsEnabled(void) {
    UT_LOG("Entering test_l1_wifi_client_hal_negative2_wifi_setCliWpsConfigMethodsEnabled...");
    INT ssidIndex = 1;
    CHAR* methodString = "";

    UT_LOG("WiFi init returned success");
    UT_LOG("Invoking wifi_setCliWpsConfigMethodsEnabled with ssidIndex 1 and empty methodString.");
    INT returnStatus = wifi_setCliWpsConfigMethodsEnabled(ssidIndex, methodString);
        
    UT_LOG("wifi_setCliWpsConfigMethodsEnabled API returns %d",returnStatus);
    UT_ASSERT_EQUAL(returnStatus, RETURN_ERR);
   
    UT_LOG("Exiting test_l1_wifi_client_hal_negative2_wifi_setCliWpsConfigMethodsEnabled...");
}
/**
* @brief This function checks if works wifi_setCliWpsConfigMethodsEnabled() as expected
*
* This test checks the behavior of wifi_setCliWpsConfigMethodsEnabled when ssidIndex of value 1 and NULL methodString are provided as input. The function is expected to return an error code. The objective of this test is to validate the error handling of the function.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 016 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking the wifi_setCliWpsConfigMethodsEnabled API with ssidIndex = 1, methodString = NULL| ssidIndex = 1, methodString = NULL | RETURN_ERR | Should Fail |
*/
void test_l1_wifi_client_hal_negative3_wifi_setCliWpsConfigMethodsEnabled(void) {
    UT_LOG("Entering test_l1_wifi_client_hal_negative3_wifi_setCliWpsConfigMethodsEnabled...");
    
    INT ssidIndex = 1;
    CHAR* methodString = NULL;

    UT_LOG("Invoking wifi_setCliWpsConfigMethodsEnabled with ssidIndex 1 and methodString = NULL.");
    INT returnStatus = wifi_setCliWpsConfigMethodsEnabled(ssidIndex, methodString);
        
    UT_LOG("wifi_setCliWpsConfigMethodsEnabled API returns %d",returnStatus);
    UT_ASSERT_EQUAL(returnStatus, RETURN_ERR);
 
    UT_LOG("Exiting test_l1_wifi_client_hal_negative3_wifi_setCliWpsConfigMethodsEnabled...");
}

/**
* @brief This function checks if wifi_setCliWpsConfigMethodsEnabled() works as expected when invalid value is passed.
*
* This test checks the behavior of wifi_setCliWpsConfigMethodsEnabled when ssidIndex of value 1 and invalid methodString are provided as input. The function is expected to return an error code. The objective of this test is to validate the error handling of the function.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 017 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking wifi_setCliWpsConfigMethodsEnabled with ssidIndex = 1, invalid methodString = "IntegratedNFC"| ssidIndex = 1, methodString = "IntegratedNFC" | RETURN_ERR | Should Fail |
*/
void test_l1_wifi_client_hal_negative4_wifi_setCliWpsConfigMethodsEnabled(void) {
    UT_LOG("Entering test_l1_wifi_client_hal_negative4_wifi_setCliWpsConfigMethodsEnabled...");
    
    INT ssidIndex = 1;
    CHAR* methodString = "IntegratedNFC";
    
    UT_LOG("Invoking wifi_setCliWpsConfigMethodsEnabled with ssidIndex 1 and methodString = \"IntegratedNFC\".");
    INT returnStatus = wifi_setCliWpsConfigMethodsEnabled(ssidIndex, methodString);
        
    UT_LOG("wifi_setCliWpsConfigMethodsEnabled API returns %d",returnStatus);
    UT_ASSERT_EQUAL(returnStatus, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_client_hal_negative4_wifi_setCliWpsConfigMethodsEnabled...");
}

/**
* @brief This function checks if wifi_setCliWpsConfigMethodsEnabled works as expected.
*
* This test checks whether the wifi_setCliWpsConfigMethodsEnabled API returns an error when invoked without initializing WiFi, and verifies its correct operation with given inputs.
*
* **Test Group ID:** Basic: 01  @n
* **Test Case ID:** 018  @n
* **Priority:** High  @n@n
* 
* **Pre-Conditions:** None  @n
* **Dependencies:** None  @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console  @n
* 
* **Test Procedure:**  @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking the wifi_setCliWpsConfigMethodsEnabled API without calling wifi_init() or wifi_initWithConfig() | ssidIndex = 1, methodString = "USBFlashDrive" | RETURN_ERR | Should Fail |
*/
void test_l1_wifi_client_hal_negative5_wifi_setCliWpsConfigMethodsEnabled(void) {
    UT_LOG("Entering test_l1_wifi_client_hal_negative5_wifi_setCliWpsConfigMethodsEnabled...");
    INT ssidIndex = 1;
    CHAR* methodString = "USBFlashDrive";
    WiFi_UnInitPosReq();

    UT_LOG("Invoking wifi_setCliWpsConfigMethodsEnabled without initializing WiFi, with ssidIndex 1 and methodString \"USBFlashDrive\".");
    INT returnStatus = wifi_setCliWpsConfigMethodsEnabled(ssidIndex, methodString);
    
    UT_LOG("wifi_setCliWpsConfigMethodsEnabled API returns : %d",returnStatus);
    UT_ASSERT_EQUAL(returnStatus, RETURN_ERR);
    
    WiFi_InitPreReq();
    UT_LOG("Exiting test_l1_wifi_client_hal_negative5_wifi_setCliWpsConfigMethodsEnabled...");
}

/**
** @brief This function checks if  wifi_setCliWpsEnrolleePin works as expected when it is invoked after calling wifi_init(), with valid values.
*
* This test aims at verifying the proper execution of the 'wifi_setCliWpsEnrolleePin' function, when provided with valid input. The function should return 'RETURN_OK', indicating successful operation.
*
* **Test Group ID:** Basic: 01  @n
* **Test Case ID:** 019  @n
* **Priority:** High  @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking the wifi_setCliWpsEnrolleePin API with valid ssidIndex = 1, EnrolleePin = "12345678" | ssidIndex = 1, EnrolleePin = "12345678" | RETURN_OK | Should Pass |
*/
void test_l1_wifi_client_hal_positive1_wifi_setCliWpsEnrolleePin( void )
{
    UT_LOG("Entering test_l1_wifi_client_hal_positive1_wifi_setCliWpsEnrolleePin...");
    INT ssidIndex = 1;
    CHAR EnrolleePin[] = "12345678";  /*Need to change to a valid value*/

    UT_LOG("Invoking wifi_setCliWpsEnrolleePin with valid ssidIndex and EnrolleePin");
    INT retVal = wifi_setCliWpsEnrolleePin(ssidIndex, EnrolleePin);

    UT_LOG("wifi_setCliWpsEnrolleePin API returns %d",retVal);
    UT_ASSERT_EQUAL(retVal, RETURN_OK);
 
    UT_LOG("Exiting test_l1_wifi_client_hal_positive1_wifi_setCliWpsEnrolleePin...");
}

/**
** @brief This function checks if  wifi_setCliWpsEnrolleePin works as expected when it is invoked after calling wifi_initWithConfig(), with valid values.
*
* This test aims at verifying the proper execution of the 'wifi_setCliWpsEnrolleePin' function, when provided with valid input. The function should return 'RETURN_OK', indicating successful operation.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 020 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking the wifi_setCliWpsEnrolleePin API with valid ssidIndex = 1, EnrolleePin = "12345678" | ssidIndex = 1, EnrolleePin = "12345678" | RETURN_OK | Should Pass |
*/
void test_l1_wifi_client_hal_positive2_wifi_setCliWpsEnrolleePin( void )
{
    UT_LOG("Entering test_l1_wifi_client_hal_positive2_wifi_setCliWpsEnrolleePin...");
    INT ssidIndex = 1;
    CHAR EnrolleePin[] = "12345678";  /*Need to change to a valid value*/

    WiFi_UnInitPosReq();
    WiFi_InitWithConfigPreReq();

    UT_LOG("Invoking wifi_setCliWpsEnrolleePin with valid ssidIndex and EnrolleePin");
    INT retVal = wifi_setCliWpsEnrolleePin(ssidIndex, EnrolleePin);

    UT_LOG("wifi_setCliWpsEnrolleePin API returns %d",retVal);
    UT_ASSERT_EQUAL(retVal, RETURN_OK);
 
    WiFi_UnInitPosReq();
    WiFi_InitPreReq();

    UT_LOG("Exiting test_l1_wifi_client_hal_positive2_wifi_setCliWpsEnrolleePin...");
}

/**
* @brief This function checks if wifi_setCliWpsEnrolleePin() works as expected when invalid value is passed.
*
* This test will call the wifi_setCliWpsEnrolleePin() function with an invalid SSID index to make sure it handles invalid inputs correctly. It's important for the function to respond with an appropriate error when receiving invalid input.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 021 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking wifi_setCliWpsEnrolleePin() with invalid ssidIndex = 2, EnrolleePin = "12345678" | ssidIndex = 2, EnrolleePin = "12345678" | RETURN_ERR | Should Fail |
*/
void test_l1_wifi_client_hal_negative1_wifi_setCliWpsEnrolleePin( void )
{
    UT_LOG("Entering test_l1_wifi_client_hal_negative1_wifi_setCliWpsEnrolleePin...");
    INT ssidIndex = 2;
    CHAR EnrolleePin[] = "12345678"; /*Need to change to a valid value*/

    UT_LOG("WiFi init returned success");
    UT_LOG("Invoking wifi_setCliWpsEnrolleePin with invalid ssidIndex");
    INT retVal = wifi_setCliWpsEnrolleePin(ssidIndex, EnrolleePin);
    
    UT_LOG("wifi_setCliWpsEnrolleePin API returns %d",retVal);
    UT_ASSERT_EQUAL(retVal, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_client_hal_negative1_wifi_setCliWpsEnrolleePin...");
}

/**
* @brief This function checks if wifi_setCliWpsEnrolleePin() works as expected when invalid value is passed.
*
* The test checks if the API `wifi_setCliWpsEnrolleePin` returns error when invoked with `EnrolleePin` parameter set to NULL. It is essential to ensure that this function handles erroneous inputs gracefully and returns expected error codes.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 022 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking the wifi_setCliWpsEnrolleePin API with ssidIndex = 1, invalid EnrolleePin = NULL | ssidIndex = 1, EnrolleePin = NULL | RETURN_ERR | Should Fail |
*/
void test_l1_wifi_client_hal_negative2_wifi_setCliWpsEnrolleePin( void )
{
    UT_LOG("Entering test_l1_wifi_client_hal_negative2_wifi_setCliWpsEnrolleePin...");  
    INT ssidIndex = 1;
    CHAR *EnrolleePin = NULL;

    UT_LOG("Invoking wifi_setCliWpsEnrolleePin with EnrolleePin is NULL");
    INT retVal = wifi_setCliWpsEnrolleePin(ssidIndex, EnrolleePin);
    
    UT_LOG("wifi_setCliWpsEnrolleePin API returns : %d",retVal);
    UT_ASSERT_EQUAL(retVal, RETURN_ERR);
 
    UT_LOG("Exiting test_l1_wifi_client_hal_negative2_wifi_setCliWpsEnrolleePin...");
}

/**
* @brief This function checks if wifi_setCliWpsEnrolleePin() works as expected. 
*
* wifi_setCliWpsEnrolleePin API should return error code while invoking without calling wifi_init() and wifi_connectEndpoint_callback_register() 
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 023 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invokung the wifi_setCliWpsEnrolleePin API without calling wifi_init() and wifi_connectEndpoint_callback_register() | ssidIndex = 1, EnrolleePin = "12345678" | RETURN_ERR | Should Fail |
*/
void test_l1_wifi_client_hal_negative3_wifi_setCliWpsEnrolleePin( void )
{
    UT_LOG("Entering test_l1_wifi_client_hal_negative3_wifi_setCliWpsEnrolleePin...");  
    INT ssidIndex = 1;
    CHAR *EnrolleePin = "12345678"; /*Need to change to a valid value*/
    WiFi_UnInitPosReq();

    UT_LOG("Invoking wifi_setCliWpsEnrolleePin without calling wifi_init() and wifi_connectEndpoint_callback_register() ");
    INT retVal = wifi_setCliWpsEnrolleePin(ssidIndex, EnrolleePin);
    
    UT_LOG("wifi_setCliWpsEnrolleePin API returns : %d",retVal);
    UT_ASSERT_EQUAL(retVal, RETURN_ERR);
    
    WiFi_InitPreReq();
    UT_LOG("Exiting test_l1_wifi_client_hal_negative3_wifi_setCliWpsEnrolleePin...");
}

/**
 * @brief This function checks if wifi_setCliWpsEnrolleePin works as expected when invalid value is passed.
 *
 * In this test, we are validating the wifi_setCliWpsEnrolleePin functionality when EnrolleePin contains character values, which it should not.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 024 @n
 * **Priority:** High @n@n
 * 
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 * 
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data |Expected Result |Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Invoking the wifi_setCliWpsEnrolleePin API with ssidIndex = 1, invalid EnrolleePin = "1234ABCD" | ssidIndex = 1, EnrolleePin = '1234ABCD' | RETURN_ERR | Should Fail |
 */
void test_l1_wifi_client_hal_negative4_wifi_setCliWpsEnrolleePin(void)
{
    UT_LOG("Entering test_l1_wifi_client_hal_negative4_wifi_setCliWpsEnrolleePin...");
    INT ssidIndex = 1;
    CHAR EnrolleePin[] = "1234ABCD";

    UT_LOG("Invoking wifi_setCliWpsEnrolleePin with EnrolleePin containing character values");
    INT retVal = wifi_setCliWpsEnrolleePin(ssidIndex, EnrolleePin);
        
    UT_LOG("wifi_setCliWpsEnrolleePin API returns : %d",retVal);
    UT_ASSERT_EQUAL(retVal, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_client_hal_negative4_wifi_setCliWpsEnrolleePin...");
}

/**
* @brief This function checks if works as expected when it is invoked after calling wifi_init(), with valid values.
*
* The test verifies the ability of the wifi_setCliWpsButtonPush() function to successfully update the WPS settings of an endpoint in a scenario where the function is invoked with a valid ssidIndex, which is expected to be present in the system.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 025 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking the wifi_setCliWpsButtonPush API with valid ssidIndex = 1 | ssidIndex = 1 | RETURN_OK | Should Pass |
**/
void test_l1_wifi_client_hal_positive1_wifi_setCliWpsButtonPush( void )
{
    UT_LOG("Entering test_l1_wifi_client_hal_positive1_wifi_setCliWpsButtonPush...");
    INT ssidIndex = 1;

    UT_LOG("Invoked wifi_setCliWpsButtonPush with valid ssidIndex = 1");
    INT returnStatus = wifi_setCliWpsButtonPush(ssidIndex);
        
    UT_LOG("wifi_setCliWpsButtonPush API returns : %d",returnStatus);
    UT_ASSERT_EQUAL(returnStatus, RETURN_OK);
    
    UT_LOG("Exiting test_l1_wifi_client_hal_positive1_wifi_setCliWpsButtonPush...");
}

/**
* @brief This function checks if works as expected when it is invoked after calling wifi_initWithConfig(), with valid values.
*
* The test verifies the ability of the wifi_setCliWpsButtonPush() function to successfully update the WPS settings of an endpoint in a scenario where the function is invoked with a valid ssidIndex, which is expected to be present in the system.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 026 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking the wifi_setCliWpsButtonPush API with valid ssidIndex = 1 | ssidIndex = 1 | RETURN_OK | Should Pass |
**/
void test_l1_wifi_client_hal_positive2_wifi_setCliWpsButtonPush( void )
{
    UT_LOG("Entering test_l1_wifi_client_hal_positive2_wifi_setCliWpsButtonPush...");
    INT ssidIndex = 1;  
    WiFi_UnInitPosReq();
    WiFi_InitWithConfigPreReq();

    UT_LOG("Invoked wifi_setCliWpsButtonPush with valid ssidIndex = 1");
    INT returnStatus = wifi_setCliWpsButtonPush(ssidIndex);
        
    UT_LOG("wifi_setCliWpsButtonPush API returns : %d",returnStatus);
    UT_ASSERT_EQUAL(returnStatus, RETURN_OK);
    
    WiFi_UnInitPosReq();
    WiFi_InitPreReq();
    UT_LOG("Exiting test_l1_wifi_client_hal_positive2_wifi_setCliWpsButtonPush...");
}

/**
* @brief This function checks if wifi_setCliWpsButtonPush works as expected, when it is invoked before calling wifi_init() or wifi_initWithConfig() and wifi_connectEndpoint_callback_register().
*
* This test is designed to validate the behavior of the he wifi_setCliWpsButtonPush function when it is invoked without pre-initializing. The test will call the function
* without the required initialization and check that it returns theexpected error code.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 027 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
* 
* **Test Procedure:** @n
* | Variation / Step  | Description | Test Data | Expected Result | Notes |
* | :---------------: | ---------------| ------------ |------------| --------------- |
* | 01 | Invoking wifi_setCliWpsButtonPush without initializing wifi_init() or wifi_initWithConfig() and wifi_connectEndpoint_callback_register()| ssidIndex = 1 | RETURN_ERR | Should Fail |
*/
void test_l1_wifi_client_hal_negative1_wifi_setCliWpsButtonPush( void )
{
    UT_LOG("Entering test_l1_wifi_client_hal_negative1_wifi_setCliWpsButtonPush...");
    INT ssidIndex = 1;
    WiFi_UnInitPosReq();

    UT_LOG("Invoking the wifi_setCliWpsButtonPush API without pre-initializing.");
    INT returnStatus = wifi_setCliWpsButtonPush(ssidIndex);
    
    UT_LOG("wifi_setCliWpsButtonPush API returns : %d",returnStatus);
    UT_ASSERT_EQUAL(returnStatus, RETURN_ERR);

    WiFi_InitPreReq();
    UT_LOG("Exiting test_l1_wifi_client_hal_negative1_wifi_setCliWpsButtonPush...");
}

/**
* @brief This function checks if wifi_setCliWpsButtonPush() works as expected when invalid value is passed.
*
* This test is designed to validate the behavior of the wifi_setCliWpsButtonPush API when provided with invalid SSID Index.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 028 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:** @n
* | Variation / Step  | Description | Test Data | Expected Result | Notes |
* | :---------------: | ---------------| ------------ |------------| --------------- |
* | 01 | Invoking the wifi_setCliWpsButtonPush API with invalid ssidIndex = -1 | ssidIndex = -1 | RETURN_ERR | Should Fail |
*/
void test_l1_wifi_client_hal_negative2_wifi_setCliWpsButtonPush( void )
{
    UT_LOG("Entering test_l1_wifi_client_hal_negative2_wifi_setCliWpsButtonPush...");
    INT ssidIndex = -1;

    UT_LOG("Invoking the wifi_setCliWpsButtonPush API with ssidIndex = -1.");
    INT returnStatus = wifi_setCliWpsButtonPush(ssidIndex);
    
    UT_LOG("wifi_setCliWpsButtonPush API returns : %d",returnStatus);
    UT_ASSERT_EQUAL(returnStatus, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_client_hal_negative2_wifi_setCliWpsButtonPush...");
}

/**
* @brief Test case to validate the wifi_connectEndpoint function with valid inputs.
*
* This test case is used to test the wifi_connectEndpoint function with valid inputs and to verify if it returns the expected result.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 029 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking wifi_connectEndpoint() API with valid input values | ssidIndex = 1, AP_SSID = "ValidSSID", AP_security_mode = VALID_MODE, AP_security_WEPKey = "ExampleWEPKey", AP_security_PreSharedKey = "ExamplePreSharedKey", AP_security_KeyPassphrase = "ExamplePassphrase", saveSSID = 1, eapIdentity = "ValidIdentity", carootcert = "ValidCARootCertFilePath", clientcert = "ValidClientCertFilePath", privatekey = "ValidPrivateKeyFilePath" | RETURN_OK | Should Pass|
*/
void test_l1_wifi_client_hal_positive1_wifi_connectEndpoint(void) {
    UT_LOG("Entering test_l1_wifi_client_hal_positive1_wifi_connectEndpoint...");

    INT ssidIndex = 1;
    CHAR AP_SSID[] = "ValidSSID";                                  /*Need to replace with valid value*/
    wifiSecurityMode_t AP_security_mode = WIFI_SECURITY_WEP_64;
    CHAR AP_security_WEPKey[] = "ExampleWEPKey";                   /*Need to replace with valid value*/
    CHAR AP_security_PreSharedKey[] = "ExamplePreSharedKey";       /*Need to replace with valid value*/
    CHAR AP_security_KeyPassphrase[] = "ExamplePassphrase";        /*Need to replace with valid value*/
    INT saveSSID = 1;                   
    CHAR eapIdentity[] = "ValidIdentity";                          /*Need to replace with valid value*/
    CHAR carootcert[] = "ValidCARootCertFilePath";                 /*Need to replace with valid value*/
    CHAR clientcert[] = "ValidClientCertFilePath";                 /*Need to replace with valid value*/
    CHAR privatekey[] = "ValidPrivateKeyFilePath";                 /*Need to replace with valid value*/

    UT_LOG("Invoking the API wifi_connectEndpoint with valid values");
    INT result = wifi_connectEndpoint(ssidIndex, AP_SSID, AP_security_mode, AP_security_WEPKey, AP_security_PreSharedKey, AP_security_KeyPassphrase, saveSSID, eapIdentity, carootcert, clientcert, privatekey);

    UT_LOG("The API wifi_connectEndpoint returns: %d", result);
    UT_ASSERT_EQUAL(result, RETURN_OK);
    
    UT_LOG("Exiting test_l1_wifi_client_hal_positive1_wifi_connectEndpoint...");
}

/**
* @brief Test case to verify the behavior when the SSID has zero length.
*
* This test case verifies the behavior of the wifi_connectEndpoint function when the SSID has zero length. The objective of this test is to ensure that the function handles this scenario correctly.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 030 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking wifi_connectEndpoint() API with valid input values | ssidIndex = 1, AP_SSID = "", AP_security_mode = WIFI_SECURITY_WEP_64, AP_security_WEPKey = "ExampleWEPKey", AP_security_PreSharedKey = "ExamplePreSharedKey", AP_security_KeyPassphrase = "ExamplePassphrase", saveSSID = 1, eapIdentity = "ValidIdentity", carootcert = "ValidCARootCertFilePath", clientcert = "ValidClientCertFilePath", privatekey = "ValidPrivateKeyFilePath" | RETURN_OK | Should Pass |
*/
void test_l1_wifi_client_hal_positive2_wifi_connectEndpoint(void) {
    UT_LOG("Entering test_l1_wifi_client_hal_positive2_wifi_connectEndpoint...");

    INT ssidIndex = 1;
    CHAR AP_SSID[] = "";                                  
    wifiSecurityMode_t AP_security_mode = WIFI_SECURITY_WEP_64;    
    CHAR AP_security_WEPKey[] = "ExampleWEPKey";                   /*Need to replace with valid value*/
    CHAR AP_security_PreSharedKey[] = "ExamplePreSharedKey";       /*Need to replace with valid value*/
    CHAR AP_security_KeyPassphrase[] = "ExamplePassphrase";        /*Need to replace with valid value*/
    INT saveSSID = 1;                   
    CHAR eapIdentity[] = "ValidIdentity";                          /*Need to replace with valid value*/
    CHAR carootcert[] = "ValidCARootCertFilePath";                 /*Need to replace with valid value*/
    CHAR clientcert[] = "ValidClientCertFilePath";                 /*Need to replace with valid value*/
    CHAR privatekey[] = "ValidPrivateKeyFilePath";                 /*Need to replace with valid value*/

    UT_LOG("Invoking the API wifi_connectEndpoint with valid values");
    INT result = wifi_connectEndpoint(ssidIndex, AP_SSID, AP_security_mode, AP_security_WEPKey, AP_security_PreSharedKey, AP_security_KeyPassphrase, saveSSID, eapIdentity, carootcert, clientcert, privatekey);

    UT_LOG("The API wifi_connectEndpoint returns: %d", result);
    UT_ASSERT_EQUAL(result, RETURN_OK);
    
    UT_LOG("Exiting test_l1_wifi_client_hal_positive2_wifi_connectEndpoint...");
}

/**
* @brief This test case verifies the functionality of the wifi_connectEndpoint API when saveSSID is set to 0.
*
* The objective of this test is to verify that the wifi_connectEndpoint API behaves correctly when the saveSSID parameter is set to 0.
* The function should connect to an endpoint using the provided SSID, security mode, and security keys, but should not save the SSID.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 031 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking wifi_connectEndpoint() API with valid input values | ssidIndex = 1, AP_SSID = "ValidSSID", AP_security_mode = WIFI_SECURITY_WEP_64, AP_security_WEPKey = "ExampleWEPKey", AP_security_PreSharedKey = "ExamplePreSharedKey", AP_security_KeyPassphrase = "ExamplePassphrase", saveSSID = 0, eapIdentity = "ValidIdentity", carootcert = "ValidCARootCertFilePath", clientcert = "ValidClientCertFilePath", privatekey = "ValidPrivateKeyFilePath" | RETURN_OK | Should Pass |
*/
void test_l1_wifi_client_hal_positive3_wifi_connectEndpoint(void) {
    UT_LOG("Entering test_l1_wifi_client_hal_positive3_validInputs...");

    INT ssidIndex = 1;
    CHAR AP_SSID[] = "ValidSSID";                                  /*Need to replace with valid value*/
    wifiSecurityMode_t AP_security_mode = WIFI_SECURITY_WEP_64;    
    CHAR AP_security_WEPKey[] = "ExampleWEPKey";                   /*Need to replace with valid value*/
    CHAR AP_security_PreSharedKey[] = "ExamplePreSharedKey";       /*Need to replace with valid value*/
    CHAR AP_security_KeyPassphrase[] = "ExamplePassphrase";        /*Need to replace with valid value*/
    INT saveSSID = 0;                   
    CHAR eapIdentity[] = "ValidIdentity";                          /*Need to replace with valid value*/
    CHAR carootcert[] = "ValidCARootCertFilePath";                 /*Need to replace with valid value*/
    CHAR clientcert[] = "ValidClientCertFilePath";                 /*Need to replace with valid value*/
    CHAR privatekey[] = "ValidPrivateKeyFilePath";                 /*Need to replace with valid value*/

    UT_LOG("Invoking the API wifi_connectEndpoint with valid values");
    INT result = wifi_connectEndpoint(ssidIndex, AP_SSID, AP_security_mode, AP_security_WEPKey, AP_security_PreSharedKey, AP_security_KeyPassphrase, saveSSID, eapIdentity, carootcert, clientcert, privatekey);

    UT_LOG("The API wifi_connectEndpoint returns: %d", result);
    UT_ASSERT_EQUAL(result, RETURN_OK);
    
    UT_LOG("Exiting test_l1_wifi_client_hal_positive3_wifi_connectEndpoint...");
}

/**
* @brief This test case verifies the functionality of the wifi_connectEndpoint API when it is invoked after calling wifi_initWithConfig().
*
* The objective of this test is to verify that the wifi_connectEndpoint API behaves correctly when the saveSSID parameter is set to 0.
* The function should connect to an endpoint using the provided SSID, security mode, and security keys, but should not save the SSID.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 032 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking wifi_connectEndpoint() API with valid input values after calling wifi_initWithConfig() | ssidIndex = 1, AP_SSID = "ValidSSID", AP_security_mode = WIFI_SECURITY_WEP_64, AP_security_WEPKey = "ExampleWEPKey", AP_security_PreSharedKey = "ExamplePreSharedKey", AP_security_KeyPassphrase = "ExamplePassphrase", saveSSID = 0, eapIdentity = "ValidIdentity", carootcert = "ValidCARootCertFilePath", clientcert = "ValidClientCertFilePath", privatekey = "ValidPrivateKeyFilePath" | RETURN_OK | Should Pass |
*/
void test_l1_wifi_client_hal_positive4_wifi_connectEndpoint(void) {
    UT_LOG("Entering test_l1_wifi_client_hal_positive4_wifi_connectEndpoint...");
    WiFi_UnInitPosReq();
    WiFi_InitWithConfigPreReq();

    INT ssidIndex = 1;
    CHAR AP_SSID[] = "ValidSSID";                                  /*Need to replace with valid value*/
    wifiSecurityMode_t AP_security_mode = WIFI_SECURITY_WEP_64;    
    CHAR AP_security_WEPKey[] = "ExampleWEPKey";                   /*Need to replace with valid value*/
    CHAR AP_security_PreSharedKey[] = "ExamplePreSharedKey";       /*Need to replace with valid value*/
    CHAR AP_security_KeyPassphrase[] = "ExamplePassphrase";        /*Need to replace with valid value*/
    INT saveSSID = 0;                   
    CHAR eapIdentity[] = "ValidIdentity";                          /*Need to replace with valid value*/
    CHAR carootcert[] = "ValidCARootCertFilePath";                 /*Need to replace with valid value*/
    CHAR clientcert[] = "ValidClientCertFilePath";                 /*Need to replace with valid value*/
    CHAR privatekey[] = "ValidPrivateKeyFilePath";                 /*Need to replace with valid value*/

    UT_LOG("Invoking the API wifi_connectEndpoint with valid values");
    INT result = wifi_connectEndpoint(ssidIndex, AP_SSID, AP_security_mode, AP_security_WEPKey, AP_security_PreSharedKey, AP_security_KeyPassphrase, saveSSID, eapIdentity, carootcert, clientcert, privatekey);

    UT_LOG("The API wifi_connectEndpoint returns: %d", result);
    UT_ASSERT_EQUAL(result, RETURN_OK);
    
    WiFi_UnInitPosReq();
    WiFi_InitPreReq();

    UT_LOG("Exiting test_l1_wifi_client_hal_positive4_wifi_connectEndpoint...");
}

/**
* @brief This test case is used to test the behavior of the wifi_connectEndpoint function when an invalid SSID index is provided.
*
* The objective of this test is to verify that the function returns an error code when an invalid SSID index is used.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 033 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking wifi_connectEndpoint() with an invalid SSID index | ssidIndex = 0, AP_SSID = ValidSSID, AP_security_mode = WIFI_SECURITY_WEP_64, AP_security_WEPKey = ExampleWEPKey, AP_security_PreSharedKey = ExamplePreSharedKey, AP_security_KeyPassphrase = ExamplePassphrase, saveSSID = 1, eapIdentity = ValidIdentity, carootcert = ValidCARootCertFilePath, clientcert = ValidClientCertFilePath, privatekey = ValidPrivateKeyFilePath | RETURN_ERR | Should Fail |
*/
void test_l1_wifi_client_hal_negative1_wifi_connectEndpoint(void) {
    UT_LOG("Entering test_l1_wifi_client_hal_negative1_wifi_connectEndpoint...");

    INT ssidIndex = 0;
    CHAR AP_SSID[] = "ValidSSID";                                  /*Need to replace with valid value*/
    wifiSecurityMode_t AP_security_mode = WIFI_SECURITY_WEP_64;    
    CHAR AP_security_WEPKey[] = "ExampleWEPKey";                   /*Need to replace with valid value*/
    CHAR AP_security_PreSharedKey[] = "ExamplePreSharedKey";       /*Need to replace with valid value*/
    CHAR AP_security_KeyPassphrase[] = "ExamplePassphrase";        /*Need to replace with valid value*/
    INT saveSSID = 1;                   
    CHAR eapIdentity[] = "ValidIdentity";                          /*Need to replace with valid value*/
    CHAR carootcert[] = "ValidCARootCertFilePath";                 /*Need to replace with valid value*/
    CHAR clientcert[] = "ValidClientCertFilePath";                 /*Need to replace with valid value*/
    CHAR privatekey[] = "ValidPrivateKeyFilePath";                 /*Need to replace with valid value*/

    UT_LOG("Invoking the API wifi_connectEndpoint with an invalid SSID index");
    INT result = wifi_connectEndpoint(ssidIndex, AP_SSID, AP_security_mode, AP_security_WEPKey, AP_security_PreSharedKey, AP_security_KeyPassphrase, saveSSID, eapIdentity, carootcert, clientcert, privatekey);

    UT_LOG("The API wifi_connectEndpoint returns: %d", result);
    UT_ASSERT_EQUAL(result, RETURN_ERR);
    
    UT_LOG("Exiting ttest_l1_wifi_client_hal_negative1_wifi_connectEndpoint...");
}

/**
* @brief This test case is used to verify the behavior of the wifi_connectEndpoint function when providing an invalid security mode.
*
* The purpose of this test is to ensure that the wifi_connectEndpoint function handles the case of an invalid security mode correctly and returns RETURN_ERR.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 034 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If the user chooses to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
*  | Variation / Step | Description | Test Data | Expected Result | Notes |
*  | :----: | ----------- | --------- | --------------- | ----- |
*  | 01 | Invoking wifi_connectEndpoint() with an invalid AP_security_mode | ssidIndex = 1, AP_SSID = "ValidSSID", AP_security_mode = WIFI_SECURITY_NOT_SUPPORTED + 1, AP_security_WEPKey = "ExampleWEPKey", AP_security_PreSharedKey = "ExamplePreSharedKey", AP_security_KeyPassphrase = "ExamplePassphrase", saveSSID = 1, eapIdentity = "ValidIdentity", carootcert = "ValidCARootCertFilePath", clientcert = "ValidClientCertFilePath", privatekey = "ValidPrivateKeyFilePath" | RETURN_ERR | Should Fail |
*/
void test_l1_wifi_client_hal_negative2_wifi_connectEndpoint(void) {
    UT_LOG("Entering test_l1_wifi_client_hal_negative2_wifi_connectEndpoint...");

    INT ssidIndex = 1;
    CHAR AP_SSID[] = "ValidSSID";                                           /*Need to replace with valid value*/
    wifiSecurityMode_t AP_security_mode = WIFI_SECURITY_NOT_SUPPORTED + 1;    
    CHAR AP_security_WEPKey[] = "ExampleWEPKey";                            /*Need to replace with valid value*/
    CHAR AP_security_PreSharedKey[] = "ExamplePreSharedKey";                /*Need to replace with valid value*/
    CHAR AP_security_KeyPassphrase[] = "ExamplePassphrase";                 /*Need to replace with valid value*/
    INT saveSSID = 1;                   
    CHAR eapIdentity[] = "ValidIdentity";                                   /*Need to replace with valid value*/
    CHAR carootcert[] = "ValidCARootCertFilePath";                          /*Need to replace with valid value*/
    CHAR clientcert[] = "ValidClientCertFilePath";                          /*Need to replace with valid value*/
    CHAR privatekey[] = "ValidPrivateKeyFilePath";                          /*Need to replace with valid value*/

    UT_LOG("Invoking the API wifi_connectEndpoint with an invalid AP_security_mode");
    INT result = wifi_connectEndpoint(ssidIndex, AP_SSID, AP_security_mode, AP_security_WEPKey, AP_security_PreSharedKey, AP_security_KeyPassphrase, saveSSID, eapIdentity, carootcert, clientcert, privatekey);

    UT_LOG("The API wifi_connectEndpoint returns: %d", result);
    UT_ASSERT_EQUAL(result, RETURN_ERR);
    
    UT_LOG("Exiting ttest_l1_wifi_client_hal_negative2_wifi_connectEndpoint...");
}

/**
* @brief Test case to check wifi_connectEndpoint function with invalid security WEP key.
*
* This test case checks if the wifi_connectEndpoint function returns RETURN_ERR when an invalid security WEP key is provided.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 035 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | --------------- | ----- |
* | 01 | Invoking wifi_connectEndpoint() with invalid AP_security_WEPKey | ssidIndex = 1, AP_SSID = "ValidSSID", AP_security_mode = WIFI_SECURITY_WEP_64 , AP_security_WEPKey = NULL, AP_security_PreSharedKey = "ExamplePreSharedKey", AP_security_KeyPassphrase = "ExamplePassphrase", saveSSID = 1, eapIdentity = "ValidIdentity", carootcert = "ValidCARootCertFilePath", clientcert = "ValidClientCertFilePath", privatekey = "ValidPrivateKeyFilePath" | RETURN_ERR | Should Fail |
*/
void test_l1_wifi_client_hal_negative3_wifi_connectEndpoint(void) {
    UT_LOG("Entering test_l1_wifi_client_hal_negative3_wifi_connectEndpoint...");

    INT ssidIndex = 1;
    CHAR AP_SSID[] = "ValidSSID";                                           /*Need to replace with valid value*/
    wifiSecurityMode_t AP_security_mode = WIFI_SECURITY_WEP_64 ;    
    CHAR *AP_security_WEPKey = NULL;                           
    CHAR AP_security_PreSharedKey[] = "ExamplePreSharedKey";                /*Need to replace with valid value*/
    CHAR AP_security_KeyPassphrase[] = "ExamplePassphrase";                 /*Need to replace with valid value*/
    INT saveSSID = 1;                   
    CHAR eapIdentity[] = "ValidIdentity";                                   /*Need to replace with valid value*/
    CHAR carootcert[] = "ValidCARootCertFilePath";                          /*Need to replace with valid value*/
    CHAR clientcert[] = "ValidClientCertFilePath";                          /*Need to replace with valid value*/
    CHAR privatekey[] = "ValidPrivateKeyFilePath";                          /*Need to replace with valid value*/

    UT_LOG("Invoking the API wifi_connectEndpoint with an invalid AP_security_WEPKey");
    INT result = wifi_connectEndpoint(ssidIndex, AP_SSID, AP_security_mode, AP_security_WEPKey, AP_security_PreSharedKey, AP_security_KeyPassphrase, saveSSID, eapIdentity, carootcert, clientcert, privatekey);

    UT_LOG("The API wifi_connectEndpoint returns: %d", result);
    UT_ASSERT_EQUAL(result, RETURN_ERR);
    
    UT_LOG("Exiting ttest_l1_wifi_client_hal_negative3_wifi_connectEndpoint...");
}

/**
 * @brief Tests the wifi_connectEndpoint function with an invalid security pre-shared key.
 *
 * This test case is used to validate the behavior of the wifi_connectEndpoint function when an invalid security
 * pre-shared key is provided as input. The function should return a specific error code.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 036 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Invoking wifi_connectEndpoint() with invalid AP_security_PreSharedKey | ssidIndex = 1, AP_SSID = ValidSSID, AP_security_mode = VALID_MODE, AP_security_WEPKey = ExampleWEPKey, AP_security_PreSharedKey = NULL, AP_security_KeyPassphrase = ExamplePassphrase, saveSSID = 1, eapIdentity = ValidIdentity, carootcert = ValidCARootCertFilePath, clientcert = ValidClientCertFilePath, privatekey = ValidPrivateKeyFilePath | RETURN_ERR | Should Fail |
 */
void test_l1_wifi_client_hal_negative4_wifi_connectEndpoint(void) {
    UT_LOG("Entering test_l1_wifi_client_hal_negative4_wifi_connectEndpoint...");

    INT ssidIndex = 1;
    CHAR AP_SSID[] = "ValidSSID";                                           /*Need to replace with valid value*/
    wifiSecurityMode_t AP_security_mode = WIFI_SECURITY_WEP_64 ;    
    CHAR AP_security_WEPKey[] = "ExampleWEPKey";                            /*Need to replace with valid value*/
    CHAR *AP_security_PreSharedKey = NULL;                
    CHAR AP_security_KeyPassphrase[] = "ExamplePassphrase";                 /*Need to replace with valid value*/
    INT saveSSID = 1;                   
    CHAR eapIdentity[] = "ValidIdentity";                                   /*Need to replace with valid value*/
    CHAR carootcert[] = "ValidCARootCertFilePath";                          /*Need to replace with valid value*/
    CHAR clientcert[] = "ValidClientCertFilePath";                          /*Need to replace with valid value*/
    CHAR privatekey[] = "ValidPrivateKeyFilePath";                          /*Need to replace with valid value*/

    UT_LOG("Invoking the API wifi_connectEndpoint with an invalid AP_security_PreSharedKey");
    INT result = wifi_connectEndpoint(ssidIndex, AP_SSID, AP_security_mode, AP_security_WEPKey, AP_security_PreSharedKey, AP_security_KeyPassphrase, saveSSID, eapIdentity, carootcert, clientcert, privatekey);

    UT_LOG("The API wifi_connectEndpoint returns: %d", result);
    UT_ASSERT_EQUAL(result, RETURN_ERR);
    
    UT_LOG("Exiting ttest_l1_wifi_client_hal_negative4_wifi_connectEndpoint...");
}

/**
* @brief This test case checks the behavior of the wifi_connectEndpoint function when an invalid security key passphrase is provided.
*
* The objective of this test is to ensure that the function returns RETURN_ERR when an invalid security key passphrase is provided as input.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 037 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If the user chooses to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking wifi_connectEndpoint() with invalid AP_security_KeyPassphrase | ssidIndex=1, AP_SSID="ValidSSID", AP_security_mode=WIFI_SECURITY_WEP_64, AP_security_WEPKey="ExampleWEPKey", AP_security_PreSharedKey="ExamplePreSharedKey", AP_security_KeyPassphrase=NULL, saveSSID=1, eapIdentity="ValidIdentity", carootcert="ValidCARootCertFilePath", clientcert="ValidClientCertFilePath", privatekey="ValidPrivateKeyFilePath" | RETURN_ERR | Should Fail |
*/
void test_l1_wifi_client_hal_negative5_wifi_connectEndpoint(void) {
    UT_LOG("Entering test_l1_wifi_client_hal_negative5_wifi_connectEndpoint...");

    INT ssidIndex = 1;
    CHAR AP_SSID[] = "ValidSSID";                                           /*Need to replace with valid value*/
    wifiSecurityMode_t AP_security_mode = WIFI_SECURITY_WEP_64 ;    
    CHAR AP_security_WEPKey[] = "ExampleWEPKey";                            /*Need to replace with valid value*/
    CHAR AP_security_PreSharedKey[] = "ExamplePreSharedKey";                /*Need to replace with valid value*/
    CHAR *AP_security_KeyPassphrase = NULL;
    INT saveSSID = 1;                   
    CHAR eapIdentity[] = "ValidIdentity";                                   /*Need to replace with valid value*/
    CHAR carootcert[] = "ValidCARootCertFilePath";                          /*Need to replace with valid value*/
    CHAR clientcert[] = "ValidClientCertFilePath";                          /*Need to replace with valid value*/
    CHAR privatekey[] = "ValidPrivateKeyFilePath";                          /*Need to replace with valid value*/

    UT_LOG("Invoking the API wifi_connectEndpoint with an invalid AP_security_KeyPassphrase");
    INT result = wifi_connectEndpoint(ssidIndex, AP_SSID, AP_security_mode, AP_security_WEPKey, AP_security_PreSharedKey, AP_security_KeyPassphrase, saveSSID, eapIdentity, carootcert, clientcert, privatekey);

    UT_LOG("The API wifi_connectEndpoint returns: %d", result);
    UT_ASSERT_EQUAL(result, RETURN_ERR);
    
    UT_LOG("Exiting ttest_l1_wifi_client_hal_negative5_wifi_connectEndpoint...");
}
/**
 * @brief Test case to verify the behavior of the wifi_connectEndpoint function when an invalid saveSSID value is provided.
 *
 * This test case verifies that the wifi_connectEndpoint function returns RETURN_ERR when an invalid saveSSID value is passed as an argument.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 038 @n
 * **Priority:** High @n@n
 * 
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 * 
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Invoking wifi_connectEndpoint() with invalid saveSSID value | ssidIndex = 1, AP_SSID = "ValidSSID", AP_security_mode = WIFI_SECURITY_WEP_64, AP_security_WEPKey = "ExampleWEPKey", AP_security_PreSharedKey = "ExamplePreSharedKey", AP_security_KeyPassphrase = "ExamplePassphrase", saveSSID = 2, eapIdentity = "ValidIdentity", carootcert = "ValidCARootCertFilePath", clientcert = "ValidClientCertFilePath", privatekey = "ValidPrivateKeyFilePath" | RETURN_ERR | Should Fail |
 */
void test_l1_wifi_client_hal_negative6_wifi_connectEndpoint(void) {
    UT_LOG("Entering test_l1_wifi_client_hal_negative6_wifi_connectEndpoint...");

    INT ssidIndex = 1;
    CHAR AP_SSID[] = "ValidSSID";                                           /*Need to replace with valid value*/
    wifiSecurityMode_t AP_security_mode = WIFI_SECURITY_WEP_64 ;    
    CHAR AP_security_WEPKey[] = "ExampleWEPKey";                            /*Need to replace with valid value*/
    CHAR AP_security_PreSharedKey[] = "ExamplePreSharedKey";                /*Need to replace with valid value*/
    CHAR AP_security_KeyPassphrase[] = "ExamplePassphrase";                  /*Need to replace with valid value*/
    INT saveSSID = 2;                   
    CHAR eapIdentity[] = "ValidIdentity";                                   /*Need to replace with valid value*/
    CHAR carootcert[] = "ValidCARootCertFilePath";                          /*Need to replace with valid value*/
    CHAR clientcert[] = "ValidClientCertFilePath";                          /*Need to replace with valid value*/
    CHAR privatekey[] = "ValidPrivateKeyFilePath";                          /*Need to replace with valid value*/

    UT_LOG("Invoking the API wifi_connectEndpoint with an invalid saveSSID");
    INT result = wifi_connectEndpoint(ssidIndex, AP_SSID, AP_security_mode, AP_security_WEPKey, AP_security_PreSharedKey, AP_security_KeyPassphrase, saveSSID, eapIdentity, carootcert, clientcert, privatekey);

    UT_LOG("The API wifi_connectEndpoint returns: %d", result);
    UT_ASSERT_EQUAL(result, RETURN_ERR);
    
    UT_LOG("Exiting ttest_l1_wifi_client_hal_negative6_wifi_connectEndpoint...");
} 

/**
 * @brief Test case to verify the behavior of the wifi_connectEndpoint function when an invalid eapIdentity value is provided.
 *
 * This test case verifies that the wifi_connectEndpoint function returns RETURN_ERR when an invalid eapIdentity value is passed as an argument.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 039 @n
 * **Priority:** High @n@n
 * 
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 * 
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Invoking wifi_connectEndpoint() with invalid eapIdentity value | ssidIndex = 1, AP_SSID = "ValidSSID", AP_security_mode = WIFI_SECURITY_WEP_64, AP_security_WEPKey = "ExampleWEPKey", AP_security_PreSharedKey = "ExamplePreSharedKey", AP_security_KeyPassphrase = "ExamplePassphrase", saveSSID = 1, eapIdentity = NULL, carootcert = "ValidCARootCertFilePath", clientcert = "ValidClientCertFilePath", privatekey = "ValidPrivateKeyFilePath" | RETURN_ERR | Should Fail |
 */
void test_l1_wifi_client_hal_negative7_wifi_connectEndpoint(void) {
    UT_LOG("Entering test_l1_wifi_client_hal_negative7_wifi_connectEndpoint...");

    INT ssidIndex = 1;
    CHAR AP_SSID[] = "ValidSSID";                                           /*Need to replace with valid value*/
    wifiSecurityMode_t AP_security_mode = WIFI_SECURITY_WEP_64 ;    
    CHAR AP_security_WEPKey[] = "ExampleWEPKey";                            /*Need to replace with valid value*/
    CHAR AP_security_PreSharedKey[] = "ExamplePreSharedKey";                /*Need to replace with valid value*/
    CHAR AP_security_KeyPassphrase[] = "ExamplePassphrase";                  /*Need to replace with valid value*/
    INT saveSSID = 1;                   
    CHAR *eapIdentity = NULL; 
    CHAR carootcert[] = "ValidCARootCertFilePath";                          /*Need to replace with valid value*/
    CHAR clientcert[] = "ValidClientCertFilePath";                          /*Need to replace with valid value*/
    CHAR privatekey[] = "ValidPrivateKeyFilePath";                          /*Need to replace with valid value*/

    UT_LOG("Invoking the API wifi_connectEndpoint with an invalid eapIdentity");
    INT result = wifi_connectEndpoint(ssidIndex, AP_SSID, AP_security_mode, AP_security_WEPKey, AP_security_PreSharedKey, AP_security_KeyPassphrase, saveSSID, eapIdentity, carootcert, clientcert, privatekey);

    UT_LOG("The API wifi_connectEndpoint returns: %d", result);
    UT_ASSERT_EQUAL(result, RETURN_ERR);
    
    UT_LOG("Exiting ttest_l1_wifi_client_hal_negative7_wifi_connectEndpoint...");
} 

/**
 * @brief Test case to verify the behavior when invalid CA Root Certificate file path is provided.
 *
 * This test case aims to verify the behavior of the wifi_connectEndpoint() function when an invalid CA Root Certificate file path is provided as one of the input arguments. The test checks if the function returns the expected result and logs the appropriate message.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 040 @n
 * **Priority:** High @n@n
 *
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 *
 * **Test Procedure:** @n
 *
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- | --------------- | ----- |
 * | 01 | Invoking wifi_connectEndpoint() with invalid carootcert | ssidIndex = 1, AP_SSID = "ValidSSID", AP_security_mode = WIFI_SECURITY_WEP_64, AP_security_WEPKey = "ExampleWEPKey", AP_security_PreSharedKey = "ExamplePreSharedKey", AP_security_KeyPassphrase = "ExamplePassphrase", saveSSID = 1, eapIdentity = "ValidIdentity", carootcert = NULL, clientcert = "ValidClientCertFilePath", privatekey = "ValidPrivateKeyFilePath" | RETURN_ERR | Should Fail |
 */
void test_l1_wifi_client_hal_negative8_wifi_connectEndpoint(void) {
    UT_LOG("Entering test_l1_wifi_client_hal_negative8_wifi_connectEndpoint...");

    INT ssidIndex = 1;
    CHAR AP_SSID[] = "ValidSSID";                                           /*Need to replace with valid value*/
    wifiSecurityMode_t AP_security_mode = WIFI_SECURITY_WEP_64 ;    
    CHAR AP_security_WEPKey[] = "ExampleWEPKey";                            /*Need to replace with valid value*/
    CHAR AP_security_PreSharedKey[] = "ExamplePreSharedKey";                /*Need to replace with valid value*/
    CHAR AP_security_KeyPassphrase[] = "ExamplePassphrase";                 /*Need to replace with valid value*/
    INT saveSSID = 1;                                                       
    CHAR eapIdentity[] = "ValidIdentity";                                    /*Need to replace with valid value*/
    CHAR *carootcert = NULL;                          
    CHAR clientcert[] = "ValidClientCertFilePath";                          /*Need to replace with valid value*/
    CHAR privatekey[] = "ValidPrivateKeyFilePath";                          /*Need to replace with valid value*/

    UT_LOG("Invoking the API wifi_connectEndpoint with an invalid carootcert");
    INT result = wifi_connectEndpoint(ssidIndex, AP_SSID, AP_security_mode, AP_security_WEPKey, AP_security_PreSharedKey, AP_security_KeyPassphrase, saveSSID, eapIdentity, carootcert, clientcert, privatekey);

    UT_LOG("The API wifi_connectEndpoint returns: %d", result);
    UT_ASSERT_EQUAL(result, RETURN_ERR);
    
    UT_LOG("Exiting ttest_l1_wifi_client_hal_negative8_wifi_connectEndpoint...");
}

/**
* @brief This test case is used to verify the behavior of the wifi_connectEndpoint() function when an invalid client certificate file path is provided.
*
* The purpose of this test is to ensure that the function returns the expected result when an invalid client certificate file path is provided.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 041 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoking the API wifi_connectEndpoint with an invalid clientcert | ssidIndex = 1, AP_SSID = "ValidSSID", AP_security_mode = WIFI_SECURITY_WEP_64, AP_security_WEPKey = "ExampleWEPKey", AP_security_PreSharedKey = "ExamplePreSharedKey", AP_security_KeyPassphrase = "ExamplePassphrase", saveSSID = 1, eapIdentity = "ValidIdentity", carootcert = "ValidCARootCertFilePath", clientcert = NULL, privatekey = "ValidPrivateKeyFilePath" | RETURN_ERR | Should Fail |
*/
void test_l1_wifi_client_hal_negative9_wifi_connectEndpoint(void) {
    UT_LOG("Entering test_l1_wifi_client_hal_negative9_wifi_connectEndpoint...");

    INT ssidIndex = 1;
    CHAR AP_SSID[] = "ValidSSID";                                           /*Need to replace with valid value*/
    wifiSecurityMode_t AP_security_mode = WIFI_SECURITY_WEP_64;    
    CHAR AP_security_WEPKey[] = "ExampleWEPKey";                            /*Need to replace with valid value*/
    CHAR AP_security_PreSharedKey[] = "ExamplePreSharedKey";                /*Need to replace with valid value*/
    CHAR AP_security_KeyPassphrase[] = "ExamplePassphrase";                 /*Need to replace with valid value*/
    INT saveSSID = 1;                                                       
    CHAR eapIdentity[] = "ValidIdentity";                                   /*Need to replace with valid value*/
    CHAR carootcert[] = "ValidCARootCertFilePath";;                          /*Need to replace with valid value*/
    CHAR *clientcert = NULL;                                                
    CHAR privatekey[] = "ValidPrivateKeyFilePath";                          /*Need to replace with valid value*/

    UT_LOG("Invoking the API wifi_connectEndpoint with an invalid clientcert");
    INT result = wifi_connectEndpoint(ssidIndex, AP_SSID, AP_security_mode, AP_security_WEPKey, AP_security_PreSharedKey, AP_security_KeyPassphrase, saveSSID, eapIdentity, carootcert, clientcert, privatekey);

    UT_LOG("The API wifi_connectEndpoint returns: %d", result);
    UT_ASSERT_EQUAL(result, RETURN_ERR);
    
    UT_LOG("Exiting ttest_l1_wifi_client_hal_negative9_wifi_connectEndpoint...");
}

/**
* @brief This test case is used to verify the behavior of the wifi_connectEndpoint() function when the private key file path is invalid
*
* This test case checks the behavior of the wifi_connectEndpoint function when the private key file path is invalid. The focus is to ensure that the function returns RETURN_ERR when provided with an invalid private key file path.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 042 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoking the API wifi_connectEndpoint with an invalid privatekey | ssidIndex = 1, AP_SSID = "ValidSSID", AP_security_mode = WIFI_SECURITY_WEP_64, AP_security_WEPKey = "ExampleWEPKey", AP_security_PreSharedKey = "ExamplePreSharedKey", AP_security_KeyPassphrase = "ExamplePassphrase", saveSSID = 1, eapIdentity = "ValidIdentity", carootcert = "ValidCARootCertFilePath", clientcert = "ValidClientCertFilePath", privatekey = NULL | RETURN_ERR | Should Fail |
*/
void test_l1_wifi_client_hal_negative10_wifi_connectEndpoint(void) {
    UT_LOG("Entering test_l1_wifi_client_hal_negative10_wifi_connectEndpoint...");

    INT ssidIndex = 1;
    CHAR AP_SSID[] = "ValidSSID";                                           /*Need to replace with valid value*/
    wifiSecurityMode_t AP_security_mode = WIFI_SECURITY_WEP_64;    
    CHAR AP_security_WEPKey[] = "ExampleWEPKey";                            /*Need to replace with valid value*/
    CHAR AP_security_PreSharedKey[] = "ExamplePreSharedKey";                /*Need to replace with valid value*/
    CHAR AP_security_KeyPassphrase[] = "ExamplePassphrase";                 /*Need to replace with valid value*/
    INT saveSSID = 1;                                                       
    CHAR eapIdentity[] = "ValidIdentity";                                   /*Need to replace with valid value*/
    CHAR carootcert[] = "ValidCARootCertFilePath";;                         /*Need to replace with valid value*/
    CHAR clientcert[] = "ValidClientCertFilePath";                          /*Need to replace with valid value*/                      
    CHAR *privatekey = NULL;                                                 

    UT_LOG("Invoking the API wifi_connectEndpoint with an invalid privatekey");
    INT result = wifi_connectEndpoint(ssidIndex, AP_SSID, AP_security_mode, AP_security_WEPKey, AP_security_PreSharedKey, AP_security_KeyPassphrase, saveSSID, eapIdentity, carootcert, clientcert, privatekey);

    UT_LOG("The API wifi_connectEndpoint returns: %d", result);
    UT_ASSERT_EQUAL(result, RETURN_ERR);
    
    UT_LOG("Exiting ttest_l1_wifi_client_hal_negative10_wifi_connectEndpoint...");
}

/**
* @brief Test case to verify the behavior of wifi_connectEndpoint() when it is invoked without calling wifi_init() or wifi_initWithConfig().
*
* This test case verifies, the wifi_connectEndpoint() API returns error code when it is invoked before calling wifi_init() or wifi_initWithConfig(), with valid values. 
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 043 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking wifi_connectEndpoint() API without calling wifi_init() or wifi_initWithConfig() | ssidIndex = 1, AP_SSID = "", AP_security_mode = WIFI_SECURITY_WEP_64, AP_security_WEPKey = "ExampleWEPKey", AP_security_PreSharedKey = "ExamplePreSharedKey", AP_security_KeyPassphrase = "ExamplePassphrase", saveSSID = 1, eapIdentity = "ValidIdentity", carootcert = "ValidCARootCertFilePath", clientcert = "ValidClientCertFilePath", privatekey = "ValidPrivateKeyFilePath" | RETURN_OK | Should Pass |
*/
void test_l1_wifi_client_hal_negative11_wifi_connectEndpoint(void) {
    UT_LOG("Entering test_l1_wifi_client_hal_negative11_wifi_connectEndpoint...");
    WiFi_UnInitPosReq();

    INT ssidIndex = 1;
    CHAR AP_SSID[] = "";                                  
    wifiSecurityMode_t AP_security_mode = WIFI_SECURITY_WEP_64;    
    CHAR AP_security_WEPKey[] = "ExampleWEPKey";                   /*Need to replace with valid value*/
    CHAR AP_security_PreSharedKey[] = "ExamplePreSharedKey";       /*Need to replace with valid value*/
    CHAR AP_security_KeyPassphrase[] = "ExamplePassphrase";        /*Need to replace with valid value*/
    INT saveSSID = 1;                   
    CHAR eapIdentity[] = "ValidIdentity";                          /*Need to replace with valid value*/
    CHAR carootcert[] = "ValidCARootCertFilePath";                 /*Need to replace with valid value*/
    CHAR clientcert[] = "ValidClientCertFilePath";                 /*Need to replace with valid value*/
    CHAR privatekey[] = "ValidPrivateKeyFilePath";                 /*Need to replace with valid value*/

    UT_LOG("Invoking wifi_connectEndpoint() API without calling wifi_init() or wifi_initWithConfig()");
    INT result = wifi_connectEndpoint(ssidIndex, AP_SSID, AP_security_mode, AP_security_WEPKey, AP_security_PreSharedKey, AP_security_KeyPassphrase, saveSSID, eapIdentity, carootcert, clientcert, privatekey);

    UT_LOG("The API wifi_connectEndpoint returns: %d", result);
    UT_ASSERT_EQUAL(result, RETURN_OK);
    
    WiFi_InitPreReq();
    UT_LOG("Exiting test_l1_wifi_client_hal_negative11_wifi_connectEndpoint...");
}

/**
* @brief This function checks if wifi_disconnectEndpoint() works as expected, when it is invoked after calling wifi_init() and wifi_disconnectEndpoint_callback_register(), with valid values.
*
* Tests the behavior of the 'wifi_disconnectEndpoint' API when supplied with a valid SSID index.
* This test is conducted to ensure smooth disconnection from a specific WiFi endpoint using the SSID index.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 044 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:** @n
* This test involves the following steps:
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking the wifi_disconnectEndpoint API with valid ssidIndex = 1, AP_SSID = "valid_value" | ssidIndex = 1, AP_SSID = "valid_value" | RETURN_OK | Should Pass |
*/
void test_l1_wifi_client_hal_positive1_wifi_disconnectEndpoint( void )
{
    UT_LOG("Entering test_l1_wifi_client_hal_positive1_wifi_disconnectEndpoint...");
    INT ssidIndex = 1;
    CHAR AP_SSID[] = "valid_value";     /*Need to replace with valid value*/

    UT_LOG("Invoking wifi_disconnectEndpoint API with ssidIndex = 1 and AP_SSID = \"valid_value\"");
    INT status = wifi_disconnectEndpoint(ssidIndex, AP_SSID);
    
    UT_LOG("wifi_disconnectEndpoint API returns : %d",status);
    UT_ASSERT_EQUAL(status, RETURN_OK);
    
    UT_LOG("Exiting test_l1_wifi_client_hal_positive1_wifi_disconnectEndpoint...");
}

/**
* @brief This function checks if wifi_disconnectEndpoint() works as expected, when it is invoked after calling wifi_initWithConfig() and wifi_disconnectEndpoint_callback_register(), with valid values.
*
* Tests the behavior of the 'wifi_disconnectEndpoint' API when supplied with a valid SSID index.
* This test is conducted to ensure smooth disconnection from a specific WiFi endpoint using the SSID index.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 045 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:** @n
* This test involves the following steps:
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking the wifi_disconnectEndpoint API with valid ssidIndex = 1, AP_SSID = "valid_value" | ssidIndex = 1, AP_SSID = "valid_value" | RETURN_OK | Should Pass |
*/
void test_l1_wifi_client_hal_positive2_wifi_disconnectEndpoint( void )
{
    UT_LOG("Entering test_l1_wifi_client_hal_positive2_wifi_disconnectEndpoint...");
    INT ssidIndex = 1;
    CHAR AP_SSID[] = "valid_value";  /*Need to replace with valid value*/

    WiFi_UnInitPosReq();
    WiFi_InitWithConfigPreReq();

    UT_LOG("Invoking wifi_disconnectEndpoint API with ssidIndex = 1 and AP_SSID = \"valid_value\"");
    INT status = wifi_disconnectEndpoint(ssidIndex, AP_SSID);
    
    UT_LOG("wifi_disconnectEndpoint API returns : %d",status);
    UT_ASSERT_EQUAL(status, RETURN_OK);
    
    WiFi_UnInitPosReq();
    WiFi_InitPreReq();
    UT_LOG("Exiting test_l1_wifi_client_hal_positive2_wifi_disconnectEndpoint...");
}

/**
 * @brief This function checks if works as expected when invalid value is passed.
 *
 * This test is designed to validate the robustness of wifi_disconnectEndpoint function. It tests the scenario where the function is invoked with an invalid SSID index and expects the function to return an error.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 046 @n
 * **Priority:** High @n@n
 * 
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 * 
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data |Expected Result |Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Invoking wifi_disconnectEndpoint with invalid ssidIndex = 0, AP_SSID = "valid_value" | ssidIndex = 0, AP_SSID = "valid_value" | RETURN_ERR | Should Fail |
 */
void test_l1_wifi_client_hal_negative1_wifi_disconnectEndpoint( void )
{
    UT_LOG("Entering test_l1_wifi_client_hal_negative1_wifi_disconnectEndpoint...");
    INT ssidIndex = 0;
    CHAR AP_SSID[] = "valid_value";  /*Need to replace with valid value*/

    UT_LOG("Invoking wifi_disconnectEndpoint API with ssidIndex = 0 and AP_SSID = \"valid_value\"");
    INT status = wifi_disconnectEndpoint(ssidIndex, AP_SSID);
    
    UT_LOG("wifi_disconnectEndpoint API returns : %d",status);
    UT_ASSERT_EQUAL(status, RETURN_ERR);
    
    UT_LOG("Exiting test_l1_wifi_client_hal_negative1_wifi_disconnectEndpoint...");
}

/**
 * @brief This function checks if works as expected when invalid value is passed.
 *
 * This test is designed to validate the robustness of wifi_disconnectEndpoint function. It tests the scenario where the function is invoked with an invalid AP_SSID and expects the function to return an error.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 047 @n
 * **Priority:** High @n@n
 * 
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 * 
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data |Expected Result |Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Invoking wifi_disconnectEndpoint with invalid ssidIndex = 1, AP_SSID = "Invalid_value" | ssidIndex = 0, AP_SSID = "Invalid_value" | RETURN_ERR | Should Fail |
 */
void test_l1_wifi_client_hal_negative2_wifi_disconnectEndpoint( void )
{
    UT_LOG("Entering test_l1_wifi_client_hal_negative2_wifi_disconnectEndpoint...");
    INT ssidIndex = 1;
    CHAR AP_SSID[] = "Invalid_value"; /*Need to replace with proper invalid value*/

    UT_LOG("Invoking wifi_disconnectEndpoint API with ssidIndex = 0 and AP_SSID = \"Invalid_value\"");
    INT status = wifi_disconnectEndpoint(ssidIndex, AP_SSID);
    
    UT_LOG("wifi_disconnectEndpoint API returns : %d",status);
    UT_ASSERT_EQUAL(status, RETURN_ERR);
    
    UT_LOG("Exiting test_l1_wifi_client_hal_negative2_wifi_disconnectEndpoint...");
}

/**
 * @brief This function checks if wifi_disconnectEndpoint() works as expected when invalid value is passed.
 *
 * This test is designed to validate the robustness of wifi_disconnectEndpoint function. It tests the scenario where the function is invoked with an invalid AP_SSID = NULL and expects the function to return an error.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 048 @n
 * **Priority:** High @n@n
 * 
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 * 
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data |Expected Result |Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Invoking wifi_disconnectEndpoint with invalid ssidIndex = 1, AP_SSID = NULL | ssidIndex = 0, AP_SSID = NULL | RETURN_ERR | Should Fail |
 */
void test_l1_wifi_client_hal_negative3_wifi_disconnectEndpoint( void )
{
    UT_LOG("Entering test_l1_wifi_client_hal_negative3_wifi_disconnectEndpoint...");
    INT ssidIndex = 1;
    CHAR *AP_SSID = NULL;

    UT_LOG("Invoking wifi_disconnectEndpoint API with ssidIndex = 0 and AP_SSID = \"Invalid_value\"");
    INT status = wifi_disconnectEndpoint(ssidIndex, AP_SSID);
    
    UT_LOG("wifi_disconnectEndpoint API returns : %d",status);
    UT_ASSERT_EQUAL(status, RETURN_ERR);
    
    UT_LOG("Exiting test_l1_wifi_client_hal_negative3_wifi_disconnectEndpoint...");
}

/**
* @brief @brief This function checks if wifi_disconnectEndpoint() works as expected.
*
* This test is designed to validate the behavior of the wifi_disconnectEndpoint function when it is invoked without pre-initializing. The test will call the function
* without the required initialization and check that it returns theexpected error code.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 049 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
* 
* **Test Procedure:** @n
* | Variation / Step  | Description | Test Data | Expected Result | Notes |
* | :---------------: | ---------------| ------------ |------------| --------------- |
* | 01 | Invoking wifi_disconnectEndpoint without initializing wifi_init() or wifi_initWithConfig() and wifi_connectEndpoint_callback_register()| ssidIndex = 1, AP_SSID = "valid_value" | RETURN_ERR | Should Fail |
*/
void test_l1_wifi_client_hal_negaitive4_wifi_disconnectEndpoint( void )
{
    UT_LOG("Entering test_l1_wifi_client_hal_negaitive4_wifi_disconnectEndpoint...");
    INT ssidIndex = 1;
    CHAR AP_SSID[] = "valid_value";  /*Need to replace with valid value*/
    WiFi_UnInitPosReq();

    UT_LOG("Invoking wifi_disconnectEndpoint API without initializing wifi_init() and with ssidIndex = 1 and AP_SSID = \"valid_value\"");
    INT status = wifi_disconnectEndpoint(ssidIndex, AP_SSID);
    
    UT_LOG("wifi_disconnectEndpoint API returns : %d",status);
    UT_ASSERT_EQUAL(status, RETURN_ERR);
    
    WiFi_InitPreReq();
    UT_LOG("Exiting test_l1_wifi_client_hal_negaitive4_wifi_disconnectEndpoint...");
}

/**
* @brief This function checks if works as expected, when it is invoked after wifi_init(), with valid values.
*
* This test ensures that the wifi_clearSSIDInfo API behaves as expected when provided with a valid SSID index.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 050 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking the wifi_clearSSIDInfo API with ssidIndex = 1 | ssidIndex = 1 | RETURN_OK | Should pass |
*/
void test_l1_wifi_client_hal_positive1_wifi_clearSSIDInfo(void)
{
    UT_LOG("Entering test_l1_wifi_client_hal_positive1_wifi_clearSSIDInfo...\n");
    INT ssidIndex = 1;
    
    UT_LOG("Invoking wifi_clearSSIDInfo with valid SSID index %d", ssidIndex);
    INT returnValue = wifi_clearSSIDInfo(ssidIndex);

    UT_LOG("wifi_clearSSIDInfo API returns : %d",returnValue);
    UT_ASSERT_EQUAL(returnValue, RETURN_OK);

    UT_LOG("Exiting test_l1_wifi_client_hal_positive1_wifi_clearSSIDInfo...\n");
}

/**
* @brief This function checks if works as expected, when it is invoked after wifi_initWithConfig(), with valid values.
*
* This test ensures that the wifi_clearSSIDInfo API behaves as expected when provided with a valid SSID index.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 051 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking the wifi_clearSSIDInfo API with ssidIndex = 1 | ssidIndex = 1 | RETURN_OK | Should pass |
*/
void test_l1_wifi_client_hal_positive2_wifi_clearSSIDInfo(void)
{
    UT_LOG("Entering test_l1_wifi_client_hal_positive2_wifi_clearSSIDInfo...\n");
    INT ssidIndex = 1;

    WiFi_UnInitPosReq();
    WiFi_InitWithConfigPreReq();

    UT_LOG("Invoking wifi_clearSSIDInfo with valid SSID index %d", ssidIndex);
    INT returnValue = wifi_clearSSIDInfo(ssidIndex);

    UT_LOG("wifi_clearSSIDInfo API returns : %d",returnValue);
    UT_ASSERT_EQUAL(returnValue, RETURN_OK);

    WiFi_UnInitPosReq();
    WiFi_InitPreReq();

    UT_LOG("Exiting test_l1_wifi_client_hal_positive2_wifi_clearSSIDInfo...\n");
}

/**
* @brief This function checks if works as expected when invalid value is passed.
*
* The objective of this test is to analyze the wifi_clearSSIDInfo function's handling when passed with an invalid SSID. This helps to ensure stability and error handling 
* capacity of the respective functionality.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 052 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking the wifi_clearSSIDInfo API with invalid ssidIndex = 0 | SSID index = 0 | RETURN_ERR | Should Fail |
*/
void test_l1_wifi_client_hal_negative1_wifi_clearSSIDInfo(void)
{
    UT_LOG("Entering test_l1_wifi_client_hal_negative1_wifi_clearSSIDInfo...\n");
    INT ssidIndex = 0;
    
    UT_LOG("Invoking wifi_clearSSIDInfo with ssidIndex = 0");
    INT returnValue = wifi_clearSSIDInfo(ssidIndex);
        
    UT_LOG("wifi_clearSSIDInfo API returns : %d", returnValue);
    UT_ASSERT_EQUAL(returnValue, RETURN_ERR);
    
    UT_LOG("Exiting test_l1_wifi_client_hal_negative1_wifi_clearSSIDInfo...\n");
}

/**
* @brief This function checks if works as expected when invalid value is passed.
*
* The objective of this test is to analyze the wifi_clearSSIDInfo function's handling when passed with an invalid SSID(Negative value). This helps to ensure stability.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 053 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking the wifi_clearSSIDInfo API with invalid ssidIndex = -1 | SSID index = -1 | RETURN_ERR | Should Fail |
*/
void test_l1_wifi_client_hal_negative2_wifi_clearSSIDInfo(void)
{
    UT_LOG("Entering test_l1_wifi_client_hal_negative2_wifi_clearSSIDInfo...\n");
    INT ssidIndex = -1;
    
    UT_LOG("Invoking wifi_clearSSIDInfo with ssidIndex = -1");
    INT returnValue = wifi_clearSSIDInfo(ssidIndex);
        
    UT_LOG("wifi_clearSSIDInfo API returns : %d", returnValue);
    UT_ASSERT_EQUAL(returnValue, RETURN_ERR);
    
    UT_LOG("Exiting test_l1_wifi_client_hal_negative2_wifi_clearSSIDInfo...\n");
}

/**
* @brief This function checks if wifi_clearSSIDInfo() works as expected.
*
* This test is designed to validate the behavior of the wifi_clearSSIDInfo function when it is invoked without pre-initializing. The test will call the function
* without the required initialization and check that it returns theexpected error code.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 054 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
* 
* **Test Procedure:** @n
* | Variation / Step  | Description | Test Data | Expected Result | Notes |
* | :---------------: | ---------------| ------------ |------------| --------------- |
* | 01 | Invoking wifi_clearSSIDInfo without initializing wifi_init() or wifi_initWithConfig()| ssidIndex = 1 | RETURN_ERR | Should Fail |
*/
void test_l1_wifi_client_hal_negative3_wifi_clearSSIDInfo(void)
{
    UT_LOG("Entering test_l1_wifi_client_hal_negative3_wifi_clearSSIDInfo...\n");
    INT ssidIndex = 1;    
    WiFi_UnInitPosReq();

    UT_LOG("Invoking wifi_clearSSIDInfo without initializing wifi_init()");
    INT returnValue = wifi_clearSSIDInfo(ssidIndex);
        
    UT_LOG("wifi_clearSSIDInfo API returns : %d", returnValue);
    UT_ASSERT_EQUAL(returnValue, RETURN_ERR);
    
    WiFi_InitPreReq();
    UT_LOG("Exiting test_l1_wifi_client_hal_negative3_wifi_clearSSIDInfo...\n");
}

/**
* @brief This function checks if  wifi_lastConnected_Endpoint() works as expected. when it is invoked with wifi_init(), with valid values.
*
* In this test, the wifi_lastConnected_Endpoint() API is tested with valid ssidInfo structure.
* To confirm that it returns the correct value upon invocation, the result is tested against the expected return value. 
* This test is necessary to ensure the robustness of the API under normal conditions.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 055  @n
* **Priority:** High  @n@n
* 
* **Pre-Conditions:** None  @n
* **Dependencies:** None  @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.  @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 02 | Invoking wifi_lastConnected_Endpoint API with ssidInfo = valid structure | ssidInfo = valid structure | RETURN_OK | Should Fail |
*/     
void test_l1_wifi_client_hal_positive1_wifi_lastConnected_Endpoint( void )
{
    UT_LOG("Entering test_l1_wifi_client_hal_positive1_wifi_lastConnected_Endpoint...");
    
    wifi_pairedSSIDInfo_t *ssidInfo = (wifi_pairedSSIDInfo_t*)malloc(sizeof(wifi_pairedSSIDInfo_t));
    if(ssidInfo != NULL)
    {
        UT_LOG("Invoking the wifi_lastConnected_Endpoint API with valid ssidInfo structure");
        INT ret = wifi_lastConnected_Endpoint(ssidInfo);

        UT_LOG("wifi_lastConnected_Endpoint API returns : %d",ret);
        UT_ASSERT_EQUAL(ret, RETURN_OK);

        UT_LOG("Values are, ap_ssid :%s, ap_bssid : %s, ap_security : %s, ap_passphrase : %s, ap_wep_key : %s",ssidInfo->ap_ssid, ssidInfo->ap_bssid,ssidInfo->ap_security,ssidInfo->ap_passphrase,ssidInfo->ap_wep_key);
        if(!strcmp(ssidInfo->ap_ssid,"") || !strcmp(ssidInfo->ap_ssid,"valid_value"))  /*TODO need to replace with to valid value*/
        {
            UT_LOG("Current service set identifier %s which is an valid value", ssidInfo->ap_ssid);
            UT_PASS("Current service set identifier validation success");
        }
        else
        {
            UT_LOG("Current service set identifier %s which is a invalid value", ssidInfo->ap_ssid);
            UT_FAIL("Current service set identifier validation failed");
        }
        if(!strcmp(ssidInfo->ap_bssid,""))  /*TODO need to replace with to valid value*/
        {
            UT_LOG("Basic Service Set ID %s which is a valid value", ssidInfo->ap_bssid);
            UT_PASS("Basic Service Set ID validation success");
        }
        else
        {
            UT_LOG("Basic Service Set ID %s which is an invalid value", ssidInfo->ap_bssid);
            UT_FAIL("Basic Service Set ID validation failed");
        }
        const char *valid_security_values[] = {"NONE", "WPA-NONE", "WPA-PSK", "WPA-EAP", "IEEE8021X", "FT-PSK", "FT-EAP", "FT-EAP-SHA384", "WPA-PSK-SHA256", "WPA-EAP-SHA256", "SAE", "FT-SAE", "WPA-EAP-SUITE-B", "WPA-EAP-SUITE-B-192", "OSEN", "FILS-SHA256", "FILS-SHA384", "FT-FILS-SHA256", "FT-FILS-SHA384", "OWE", "DPP"};
        for (int i = 0; i < sizeof(valid_security_values) / sizeof(valid_security_values[0]); i++) {
            if (!strcmp(ssidInfo->ap_security, valid_security_values[i])) {
                UT_LOG("Security mode of AP is %s which is a valid value", ssidInfo->ap_security);
                UT_PASS("Security mode of AP validation success");
            }
            else
            {
                UT_LOG("Security mode of AP is %s which is a invalid value", ssidInfo->ap_security);
                UT_FAIL("Security mode of AP validation failed");
            }
        }
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }   
    UT_LOG("Exiting test_l1_wifi_client_hal_positive1_wifi_lastConnected_Endpoint...");
}

/**
* @brief This function checks if  wifi_lastConnected_Endpoint() works as expected. when it is invoked with wifi_initWithConfig(), with valid values.
*
* In this test, the wifi_lastConnected_Endpoint() API is tested with valid ssidInfo structure.
* To confirm that it returns the correct value upon invocation, the result is tested against the expected return value. 
* This test is necessary to ensure the robustness of the API under normal conditions.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 056  @n
* **Priority:** High  @n@n
* 
* **Pre-Conditions:** None  @n
* **Dependencies:** None  @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.  @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 02 | Invoking wifi_lastConnected_Endpoint API with ssidInfo = valid structure | ssidInfo = valid structure | RETURN_OK | Should Fail |
*/     
void test_l1_wifi_client_hal_positive2_wifi_lastConnected_Endpoint( void )
{
    UT_LOG("Entering test_l1_wifi_client_hal_positive2_wifi_lastConnected_Endpoint...");
    WiFi_UnInitPosReq();
    WiFi_InitWithConfigPreReq();
    
    wifi_pairedSSIDInfo_t *ssidInfo = (wifi_pairedSSIDInfo_t*)malloc(sizeof(wifi_pairedSSIDInfo_t));
    if(ssidInfo != NULL)
    {
        UT_LOG("Invoking the wifi_lastConnected_Endpoint API with valid ssidInfo structure");
        INT ret = wifi_lastConnected_Endpoint(ssidInfo);

        UT_LOG("wifi_lastConnected_Endpoint API returns : %d",ret);
        UT_ASSERT_EQUAL(ret, RETURN_OK);

        UT_LOG("Values are, ap_ssid :%s, ap_bssid : %s, ap_security : %s, ap_passphrase : %s, ap_wep_key : %s",ssidInfo->ap_ssid, ssidInfo->ap_bssid,ssidInfo->ap_security,ssidInfo->ap_passphrase,ssidInfo->ap_wep_key);
        if(!strcmp(ssidInfo->ap_ssid,"") || !strcmp(ssidInfo->ap_ssid,"valid_value"))  /*TODO need to replace with to valid value*/
        {
            UT_LOG("Current service set identifier %s which is an valid value", ssidInfo->ap_ssid);
            UT_PASS("Current service set identifier validation success");
        }
        else
        {
            UT_LOG("Current service set identifier %s which is a invalid value", ssidInfo->ap_ssid);
            UT_FAIL("Current service set identifier validation failed");
        }
        if(!strcmp(ssidInfo->ap_bssid,""))  /*TODO need to replace with to valid value*/
        {
            UT_LOG("Basic Service Set ID %s which is a valid value", ssidInfo->ap_bssid);
            UT_PASS("Basic Service Set ID validation success");
        }
        else
        {
            UT_LOG("Basic Service Set ID %s which is an invalid value", ssidInfo->ap_bssid);
            UT_FAIL("Basic Service Set ID validation failed");
        }
        const char *valid_security_values[] = {"NONE", "WPA-NONE", "WPA-PSK", "WPA-EAP", "IEEE8021X", "FT-PSK", "FT-EAP", "FT-EAP-SHA384", "WPA-PSK-SHA256", "WPA-EAP-SHA256", "SAE", "FT-SAE", "WPA-EAP-SUITE-B", "WPA-EAP-SUITE-B-192", "OSEN", "FILS-SHA256", "FILS-SHA384", "FT-FILS-SHA256", "FT-FILS-SHA384", "OWE", "DPP"};
        for (int i = 0; i < sizeof(valid_security_values) / sizeof(valid_security_values[0]); i++) {
            if (!strcmp(ssidInfo->ap_security, valid_security_values[i])) {
                UT_LOG("Security mode of AP is %s which is a valid value", ssidInfo->ap_security);
                UT_PASS("Security mode of AP validation success");
            }
            else
            {
                UT_LOG("Security mode of AP is %s which is a invalid value", ssidInfo->ap_security);
                UT_FAIL("Security mode of AP validation failed");
            }
        }
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    } 
    WiFi_UnInitPosReq();
    WiFi_InitPreReq();  

    UT_LOG("Exiting test_l1_wifi_client_hal_positive2_wifi_lastConnected_Endpoint...");
}


/**
* @brief This function checks if wifi_lastConnected_Endpoint works as expected when invalid value is passed.
*
* This test verifies the operation of the wifi_lastConnected_Endpoint API when passed NULL parameters.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 057 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 02 | Invoking wifi_lastConnected_Endpoint with ssidInfo = NULL | ssidInfo = NULL | RETURN_ERR | Should Fail |
*/
void test_l1_wifi_client_hal_negative1_wifi_lastConnected_Endpoint( void )
{
    UT_LOG("Entering test_l1_wifi_client_hal_negative1_wifi_lastConnected_Endpoint...");
    wifi_pairedSSIDInfo_t *ssidInfo = NULL;

    UT_LOG("Invoking wifi_lastConnected_Endpoint with NULL ssidInfo structure");
    INT ret = wifi_lastConnected_Endpoint(ssidInfo);

    UT_LOG("wifi_lastConnected_Endpoint API returns : %d",ret);
    UT_ASSERT_EQUAL(ret, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_client_hal_negative1_wifi_lastConnected_Endpoint...");
}

/**
* @brief @brief This function checks if wifi_lastConnected_Endpoint() works as expected for uninitialized wifi
*
* This test is designed to evaluate the proper handling of the wifi_lastConnected_Endpoint function when the wifi has not been initialized. The importance of such a test is to ensure system robustness even in the presence of negative scenarios.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 058 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke the wifi_lastConnected_Endpoint function without initializing wifi_init() or wifi_initWithConfig()| ssidInfo = valid structure | RETURN_ERR | Should Fail |
*/
void test_l1_wifi_client_hal_negative2_wifi_lastConnected_Endpoint( void )
{
    UT_LOG("Entering test_l1_wifi_client_hal_negative2_wifi_lastConnected_Endpoint...");
    WiFi_UnInitPosReq();

    wifi_pairedSSIDInfo_t *ssidInfo = (wifi_pairedSSIDInfo_t*)malloc(sizeof(wifi_pairedSSIDInfo_t));
    if(ssidInfo != NULL)
    {
        UT_LOG("Invoking wifi_lastConnected_Endpoint without initialising wifi");
        INT ret = wifi_lastConnected_Endpoint(ssidInfo);

        UT_LOG("wifi_lastConnected_Endpoint API returns : %d",ret);
        UT_ASSERT_EQUAL(ret, RETURN_ERR);
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    } 

    WiFi_InitPreReq();
    UT_LOG("Exiting test_l1_wifi_client_hal_negative2_wifi_lastConnected_Endpoint...");
}

/**
* @brief This function checks if wifi_setRoamingControl() works as expected, when it is invoked after calling wifi_init(), with valid values.
*
* This test intents to validate wifi_setRoamingControl API when invoked with valid ssidIndex and wifi_roamingCtrl_t structure. The API should return RETURN_OK, indicating success.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 059 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking wifi_setRoamingControl with ssidIndex =1, pRoamingCtrl_data = valid structure | ssidIndex = 1, pRoamingCtrl_data = valid data structure | RETURN_OK | Should Pass |
*/
void test_l1_wifi_client_hal_positive1_wifi_setRoamingControl(void) 
{
    UT_LOG("Entering test_l1_wifi_client_hal_positive1_wifi_setRoamingControl...");

    int ssidIndex = 1;
    wifi_roamingCtrl_t *pRoamingCtrl_data = (wifi_roamingCtrl_t*)malloc(sizeof(wifi_roamingCtrl_t));
    if(pRoamingCtrl_data != NULL )
    {
        pRoamingCtrl_data->roamingEnable = 1;                          
        pRoamingCtrl_data->selfSteerOverride = 1;                      
        pRoamingCtrl_data->roam80211kvrEnable = 1;                     
        pRoamingCtrl_data->preassnBestThreshold = -67;                    
        pRoamingCtrl_data->preassnBestDelta = 3;                        
        pRoamingCtrl_data->postAssnLevelDeltaConnected = 12;             
        pRoamingCtrl_data->postAssnLevelDeltaDisconnected = 8;          
        pRoamingCtrl_data->postAssnSelfSteerThreshold = -75;              
        pRoamingCtrl_data->postAssnSelfSteerTimeframe = 60;              
        pRoamingCtrl_data->postAssnBackOffTime = 2;                     
        pRoamingCtrl_data->postAssnAPctrlThreshold = -75;                 
        pRoamingCtrl_data->postAssnAPctrlTimeframe = 60;
    
        UT_LOG("Invoking wifi_setRoamingControl with ssidIndex = 1 and a valid pRoamingCtrl_data structure."); 
        int retVal = wifi_setRoamingControl(ssidIndex, pRoamingCtrl_data);
        
        UT_LOG("wifi_setRoamingControl API returns : %d", retVal);
        UT_ASSERT_EQUAL(retVal, RETURN_OK);
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    } 
    UT_LOG("Exiting test_l1_wifi_client_hal_positive1_wifi_setRoamingControl...");
}

/**
* @brief This function checks if wifi_setRoamingControl() works as expected, when it is invoked after calling wifi_initWithConfig(), with valid values.
*
* This test intents to validate wifi_setRoamingControl API when invoked with valid ssidIndex and wifi_roamingCtrl_t structure. The API should return RETURN_OK, indicating success.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 060 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking wifi_setRoamingControl with ssidIndex =1, pRoamingCtrl_data = valid structure | ssidIndex = 1, pRoamingCtrl_data = valid data structure | RETURN_OK | Should Pass |
*/
void test_l1_wifi_client_hal_positive2_wifi_setRoamingControl(void) 
{
    UT_LOG("Entering test_l1_wifi_client_hal_positive2_wifi_setRoamingControl...");
    WiFi_UnInitPosReq();
    WiFi_InitWithConfigPreReq();

    int ssidIndex = 1;
    wifi_roamingCtrl_t *pRoamingCtrl_data = (wifi_roamingCtrl_t*)malloc(sizeof(wifi_roamingCtrl_t));
    if(pRoamingCtrl_data != NULL )
    {
        pRoamingCtrl_data->roamingEnable = 1;                          
        pRoamingCtrl_data->selfSteerOverride = 1;                      
        pRoamingCtrl_data->roam80211kvrEnable = 1;                     
        pRoamingCtrl_data->preassnBestThreshold = -67;                    
        pRoamingCtrl_data->preassnBestDelta = 3;                        
        pRoamingCtrl_data->postAssnLevelDeltaConnected = 12;             
        pRoamingCtrl_data->postAssnLevelDeltaDisconnected = 8;          
        pRoamingCtrl_data->postAssnSelfSteerThreshold = -75;              
        pRoamingCtrl_data->postAssnSelfSteerTimeframe = 60;              
        pRoamingCtrl_data->postAssnBackOffTime = 2;                     
        pRoamingCtrl_data->postAssnAPctrlThreshold = -75;                 
        pRoamingCtrl_data->postAssnAPctrlTimeframe = 60;
    
        UT_LOG("Invoking wifi_setRoamingControl with ssidIndex = 1 and a valid pRoamingCtrl_data structure."); 
        int retVal = wifi_setRoamingControl(ssidIndex, pRoamingCtrl_data);
        
        UT_LOG("wifi_setRoamingControl API returns : %d", retVal);
        UT_ASSERT_EQUAL(retVal, RETURN_OK);
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }
    WiFi_UnInitPosReq();
    WiFi_InitPreReq(); 

    UT_LOG("Exiting test_l1_wifi_client_hal_positive2_wifi_setRoamingControl...");
}

/**
* @brief This function checks if  wifi_setRoamingControl() works as expected when invalid value is passed.
*
* This test is aimed at verifying the functionality of wifi_setRoamingControl function in the scenario where input pRoamingCtrl_data is NULL. The function's robustness and error handling capability is being tested in this test.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 061 @n
* **Priority:** High  @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking the wifi_setRoamingControl API with assidIndex = 1, pRoamingCtrl_data = NULL | ssidIndex = 1, pRoamingCtrl_data = NULL | RETURN_ERR | Should Fail |
*/
void test_l1_wifi_client_hal_negative1_wifi_setRoamingControl(void) 
{
    UT_LOG("Entering test_l1_wifi_client_hal_negative1_wifi_setRoamingControl...");
    int ssidIndex = 1;
    wifi_roamingCtrl_t* pRoamingCtrl_data = NULL;
    
    UT_LOG("Invoking wifi_setRoamingControl with ssidIndex = 1 and pRoamingCtrl_data structure = NULL.");
    int retVal = wifi_setRoamingControl(ssidIndex, pRoamingCtrl_data);

    UT_LOG("wifi_setRoamingControl API returns : %d",retVal);
    UT_ASSERT_EQUAL(retVal, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_client_hal_negative1_wifi_setRoamingControl...");
}

/**
* @brief This test verifies the 'wifi_setRoamingControl' function's behavior when invoked without the 'wifi_init' function being called first.
*
* The wifi_setRoamingControl function is tested to ensure it behaves as expected when the wifi_init or wifi_initWithConfig functions, which are normally expected to be executed before it, have not been called. If these prerequisites are not met, the wifi_setRoamingControl function should fail and return an error, hence ensuring the robustness of the Wi-Fi stack.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 062 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If the user chose to run the test in interactive mode, then the test case has to be selected via the console. @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking wifi_setRoamingControl without calling wifi_init() or wifi_initWithConfig() | ssidIndex =1, pRoamingCtrl_data = valid structure | RETURN_ERR | Should Fail  |
*/
void test_l1_wifi_client_hal_negative2_wifi_setRoamingControl(void) 
{
    UT_LOG("Entering test_l1_wifi_client_hal_negative2_wifi_setRoamingControl...");
    WiFi_UnInitPosReq();

    int ssidIndex = 1;
    wifi_roamingCtrl_t *pRoamingCtrl_data = (wifi_roamingCtrl_t*)malloc(sizeof(wifi_roamingCtrl_t));
    if(pRoamingCtrl_data != NULL )
    {
        pRoamingCtrl_data->roamingEnable = 1;                          
        pRoamingCtrl_data->selfSteerOverride = 1;                      
        pRoamingCtrl_data->roam80211kvrEnable = 1;                     
        pRoamingCtrl_data->preassnBestThreshold = -67;                    
        pRoamingCtrl_data->preassnBestDelta = 3;                        
        pRoamingCtrl_data->postAssnLevelDeltaConnected = 12;             
        pRoamingCtrl_data->postAssnLevelDeltaDisconnected = 8;          
        pRoamingCtrl_data->postAssnSelfSteerThreshold = -75;              
        pRoamingCtrl_data->postAssnSelfSteerTimeframe = 60;              
        pRoamingCtrl_data->postAssnBackOffTime = 2;                     
        pRoamingCtrl_data->postAssnAPctrlThreshold = -75;                 
        pRoamingCtrl_data->postAssnAPctrlTimeframe = 60;
    
        UT_LOG("Invoking wifi_setRoamingControl without calling wifi_init()");
        int retVal = wifi_setRoamingControl(ssidIndex, pRoamingCtrl_data);
        
        UT_LOG("wifi_setRoamingControl API returns : %d",retVal);
        UT_ASSERT_EQUAL(retVal, RETURN_ERR);
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }
    WiFi_InitPreReq();

    UT_LOG("Exiting test_l1_wifi_client_hal_negative2_wifi_setRoamingControl...");
}

/**
* @brief This function checks if  wifi_setRoamingControl() works as expected when invalid value is passed.
*
* The test case verifies the wifi_setRoamingControl API returns error code when invalid ssidIndex(0) is passed.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 063 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If the user chose to run the test in interactive mode, then the test case has to be selected via the console. @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking the wifi_setRoamingControl API with a invalid ssidIndex = 0, pRoamingCtrl_data = valid structure | ssidIndex = 0, pRoamingCtrl_data = valid structure | RETURN_ERR | Should Fail  |
*/
void test_l1_wifi_client_hal_negative3_wifi_setRoamingControl(void) 
{
    UT_LOG("Entering test_l1_wifi_client_hal_negative3_wifi_setRoamingControl...");
    
    int ssidIndex = 0;
    wifi_roamingCtrl_t *pRoamingCtrl_data = (wifi_roamingCtrl_t*)malloc(sizeof(wifi_roamingCtrl_t));
    if(pRoamingCtrl_data != NULL )
    {
        pRoamingCtrl_data->roamingEnable = 1;                          
        pRoamingCtrl_data->selfSteerOverride = 1;                      
        pRoamingCtrl_data->roam80211kvrEnable = 1;                     
        pRoamingCtrl_data->preassnBestThreshold = -67;                    
        pRoamingCtrl_data->preassnBestDelta = 3;                        
        pRoamingCtrl_data->postAssnLevelDeltaConnected = 12;             
        pRoamingCtrl_data->postAssnLevelDeltaDisconnected = 8;          
        pRoamingCtrl_data->postAssnSelfSteerThreshold = -75;              
        pRoamingCtrl_data->postAssnSelfSteerTimeframe = 60;              
        pRoamingCtrl_data->postAssnBackOffTime = 2;                     
        pRoamingCtrl_data->postAssnAPctrlThreshold = -75;                 
        pRoamingCtrl_data->postAssnAPctrlTimeframe = 60;
    
        UT_LOG("Invoking wifi_setRoamingControl ssidIndex = 0, pRoamingCtrl_data = valid structure");
        int retVal = wifi_setRoamingControl(ssidIndex, pRoamingCtrl_data);
        
        UT_LOG("wifi_setRoamingControl API returns : %d",retVal);
        UT_ASSERT_EQUAL(retVal, RETURN_ERR);
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }
    UT_LOG("Exiting test_l1_wifi_client_hal_negative3_wifi_setRoamingControl...");
}

/**
* brief This function checks if  wifi_setRoamingControl() works as expected when invalid value is passed.
*
* The test case verifies the wifi_setRoamingControl API returns error code when invalid ssidIndex(100) is passed.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 064 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If the user chose to run the test in interactive mode, then the test case has to be selected via the console. @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking the wifi_setRoamingControl API with a invalid ssidIndex = 100, pRoamingCtrl_data = valid structure | ssidIndex = 100, pRoamingCtrl_data = valid structure | RETURN_ERR | Should Fail  |
*/
void test_l1_wifi_client_hal_negative4_wifi_setRoamingControl(void) 
{
    UT_LOG("Entering test_l1_wifi_client_hal_negative4_wifi_setRoamingControl...");
    
    int ssidIndex = 100;
    wifi_roamingCtrl_t *pRoamingCtrl_data = (wifi_roamingCtrl_t*)malloc(sizeof(wifi_roamingCtrl_t));
    if(pRoamingCtrl_data != NULL )
    {
        pRoamingCtrl_data->roamingEnable = 1;                          
        pRoamingCtrl_data->selfSteerOverride = 1;                      
        pRoamingCtrl_data->roam80211kvrEnable = 1;                     
        pRoamingCtrl_data->preassnBestThreshold = -67;                    
        pRoamingCtrl_data->preassnBestDelta = 3;                        
        pRoamingCtrl_data->postAssnLevelDeltaConnected = 12;             
        pRoamingCtrl_data->postAssnLevelDeltaDisconnected = 8;          
        pRoamingCtrl_data->postAssnSelfSteerThreshold = -75;              
        pRoamingCtrl_data->postAssnSelfSteerTimeframe = 60;              
        pRoamingCtrl_data->postAssnBackOffTime = 2;                     
        pRoamingCtrl_data->postAssnAPctrlThreshold = -75;                 
        pRoamingCtrl_data->postAssnAPctrlTimeframe = 60;
    
        UT_LOG("Invoking wifi_setRoamingControl ssidIndex = 100, pRoamingCtrl_data = valid structure");
        int retVal = wifi_setRoamingControl(ssidIndex, pRoamingCtrl_data);
        
        UT_LOG("wifi_setRoamingControl API returns : %d",retVal);
        UT_ASSERT_EQUAL(retVal, RETURN_ERR);
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }
    UT_LOG("Exiting test_l1_wifi_client_hal_negative4_wifi_setRoamingControl...");
}

/**
* brief This function checks if wifi_setRoamingControl() works as expected when invalid value is passed.
*
* The test case verifies the wifi_setRoamingControl API returns error code when invalid ssidIndex(-1) is passed.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 065 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If the user chose to run the test in interactive mode, then the test case has to be selected via the console. @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking the wifi_setRoamingControl API with a invalid ssidIndex = -1, pRoamingCtrl_data = valid structure | ssidIndex = -1, pRoamingCtrl_data = valid structure | RETURN_ERR | Should Fail  |
*/
void test_l1_wifi_client_hal_negative5_wifi_setRoamingControl(void) 
{
    UT_LOG("Entering test_l1_wifi_client_hal_negative5_wifi_setRoamingControl...");
    
    int ssidIndex = -1;
    wifi_roamingCtrl_t *pRoamingCtrl_data = (wifi_roamingCtrl_t*)malloc(sizeof(wifi_roamingCtrl_t));
    if(pRoamingCtrl_data != NULL )
    {
        pRoamingCtrl_data->roamingEnable = 1;                          
        pRoamingCtrl_data->selfSteerOverride = 1;                      
        pRoamingCtrl_data->roam80211kvrEnable = 1;                     
        pRoamingCtrl_data->preassnBestThreshold = -67;                    
        pRoamingCtrl_data->preassnBestDelta = 3;                        
        pRoamingCtrl_data->postAssnLevelDeltaConnected = 12;             
        pRoamingCtrl_data->postAssnLevelDeltaDisconnected = 8;          
        pRoamingCtrl_data->postAssnSelfSteerThreshold = -75;              
        pRoamingCtrl_data->postAssnSelfSteerTimeframe = 60;              
        pRoamingCtrl_data->postAssnBackOffTime = 2;                     
        pRoamingCtrl_data->postAssnAPctrlThreshold = -75;                 
        pRoamingCtrl_data->postAssnAPctrlTimeframe = 60;
    
        UT_LOG("Invoking wifi_setRoamingControl ssidIndex = -1, pRoamingCtrl_data = valid structure");
        int retVal = wifi_setRoamingControl(ssidIndex, pRoamingCtrl_data);
        
        UT_LOG("wifi_setRoamingControl API returns : %d",retVal);
        UT_ASSERT_EQUAL(retVal, RETURN_ERR);
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }
    UT_LOG("Exiting test_l1_wifi_client_hal_negative5_wifi_setRoamingControl...");
}

/**
* @brief This function checks if wifi_getRoamingControl works as expected, when it is invoked after calling wifi_init(), with valid values.
*
* This test aims to verify the correct behavior of wifi_getRoamingControl API when provided with valid arguments.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 066 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:** @n
*
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking the wifi_getRoamingControl API with ssidIndex = 1 and pRoamingCtrl_data = valid structure | ssidIndex = 1 and pRoamingCtrl_data = valid structure | RETURN_OK | Should Pass |
*/
void test_l1_wifi_client_hal_positive1_wifi_getRoamingControl( void )
{
    UT_LOG("Entering test_l1_wifi_client_hal_positive1_wifi_getRoamingControl...");
    int ssidIndex = 1;
    wifi_roamingCtrl_t *pRoamingCtrl_data = (wifi_roamingCtrl_t*)malloc(sizeof(wifi_roamingCtrl_t));
    if(pRoamingCtrl_data != NULL)
    { 
        UT_LOG("Invoking wifi_getRoamingControl with ssidIndex = 1 and pRoamingCtrl_data = valid structure.");
        int retVal = wifi_getRoamingControl(ssidIndex, pRoamingCtrl_data);
    
        UT_LOG("wifi_getRoamingControl API returns : %d",retVal);
        UT_ASSERT_EQUAL(retVal, RETURN_OK);
    
        UT_LOG("Values are, roaming control :%d, selfSteerOverride : %d, roam80211kvrEnable : %d, Pre-association best RSSI threshold : %d, Pre-association best RSSI delta : %d, Post-association delta level if WiFi connected : %d, Post-association delta level if WiFi disconnected : %d, Post-association self steer threshold : %d, Post-association self steer timeframe : %d, Post-association backoff time : %d, Post-association AP steer control threshold : %d, Post-association AP steer control time frame : %d",pRoamingCtrl_data->roamingEnable, pRoamingCtrl_data->selfSteerOverride, pRoamingCtrl_data->preassnBestThreshold, pRoamingCtrl_data->preassnBestDelta, pRoamingCtrl_data->postAssnLevelDeltaConnected, pRoamingCtrl_data->postAssnLevelDeltaDisconnected,pRoamingCtrl_data->postAssnSelfSteerThreshold, pRoamingCtrl_data->postAssnSelfSteerTimeframe, pRoamingCtrl_data->postAssnBackOffTime, pRoamingCtrl_data->postAssnAPctrlThreshold, pRoamingCtrl_data->postAssnAPctrlTimeframe );
        if ( pRoamingCtrl_data->roamingEnable == 0 || pRoamingCtrl_data->roamingEnable == 1 )
        {
            UT_LOG("roaming control is %d which is a valid value", pRoamingCtrl_data->roamingEnable);
            UT_PASS("roaming control validation success");
        }
        else
        {
            UT_LOG("roaming control is %d which is an invalid value", pRoamingCtrl_data->roamingEnable);
            UT_FAIL("roaming control validation failed");
        }
        if ( pRoamingCtrl_data-> selfSteerOverride == 0 || pRoamingCtrl_data-> selfSteerOverride == 1 )
        {
            UT_LOG("self Steer Override is %d which is a valid value", pRoamingCtrl_data-> selfSteerOverride);
            UT_PASS("self Steer Override validation success");
        }
        else
        {
            UT_LOG("self Steer Override is %d which is a valid value", pRoamingCtrl_data-> selfSteerOverride);
            UT_FAIL("self Steer Override validation failed");
        }
        if ( pRoamingCtrl_data-> roam80211kvrEnable == 0 || pRoamingCtrl_data-> roam80211kvrEnable == 1 )
        {
            UT_LOG("roam 80211kvr Enable is %d which is a valid value", pRoamingCtrl_data-> roam80211kvrEnable);
            UT_PASS("roam 80211kvr Enable validation success");
        }
        else
        {
            UT_LOG("roam 80211kvr Enable is %d which is an invalid value", pRoamingCtrl_data-> roam80211kvrEnable);
            UT_FAIL("roam 80211kvr Enable validation failed");
        }
        if ( pRoamingCtrl_data->preassnBestThreshold >= -100 && pRoamingCtrl_data->preassnBestThreshold <= 0 )
        {
            UT_LOG("Pre-association best RSSI threshold is %d which is a valid value", pRoamingCtrl_data->preassnBestThreshold);
            UT_PASS("Pre-association best RSSI threshold validation success");
        }
        else
        {
            UT_LOG("Pre-association best RSSI threshold is %d which is a invalid value", pRoamingCtrl_data->preassnBestThreshold);
            UT_FAIL("Pre-association best RSSI threshold validation failed");
        }
        if ( pRoamingCtrl_data->preassnBestDelta >= 0 && pRoamingCtrl_data->preassnBestDelta <= 100 )
        {
            UT_LOG("Pre-association best RSSI delta is %d which is a valid value", pRoamingCtrl_data->preassnBestDelta);
            UT_PASS("Pre-association best RSSI delta validation success");
        }
        else
        {
            UT_LOG("Pre-association best RSSI delta %d which is an invalid value", pRoamingCtrl_data->preassnBestDelta);
            UT_FAIL("Pre-association best RSSI delta validation failed");
        }
        if ( pRoamingCtrl_data->postAssnLevelDeltaConnected >= 0 && pRoamingCtrl_data->postAssnLevelDeltaConnected <= 100 )
        {
            UT_LOG("Post-association delta level if WiFi connected is %d which is a valid value", pRoamingCtrl_data->postAssnLevelDeltaConnected);
            UT_PASS("Post-association delta level validation success");
        }
        else
        {
            UT_LOG("Post-association delta level if WiFi connected is %d which is a invalid value", pRoamingCtrl_data->postAssnLevelDeltaConnected);
            UT_FAIL("Post-association delta level validation failed");
        }
        if ( pRoamingCtrl_data->postAssnLevelDeltaDisconnected >= 0 && pRoamingCtrl_data->postAssnLevelDeltaDisconnected <= 100 )
        {
            UT_LOG("Post-association delta level if WiFi disconnected is %d which is a valid value", pRoamingCtrl_data->postAssnLevelDeltaDisconnected);
            UT_PASS("Post-association delta level if WiFi disconnected validation success");
        }
        else
        {
            UT_LOG("Post-association delta level if WiFi disconnected is %d which is a invalid value", pRoamingCtrl_data->postAssnLevelDeltaDisconnected);
            UT_FAIL("Post-association delta level if WiFi disconnected validation failed");
        }
        if ( pRoamingCtrl_data-> postAssnSelfSteerThreshold >= -100 && pRoamingCtrl_data-> postAssnSelfSteerThreshold <= 0 )
        {
            UT_LOG("Post-association self steer threshold is %d which is a valid value", pRoamingCtrl_data-> postAssnSelfSteerThreshold);
            UT_PASS("Post-association self steer threshold validation success");
        }
        else
        {
            UT_LOG("Post-association self steer threshold is %d which is a invalid value", pRoamingCtrl_data-> postAssnSelfSteerThreshold);
            UT_FAIL("Post-association self steer threshold validation failed");
        }
        if ( pRoamingCtrl_data-> postAssnSelfSteerTimeframe >= 0 && pRoamingCtrl_data-> postAssnSelfSteerTimeframe <= 36000 )
        {
            UT_LOG("Post-association self steer timeframe is %d which is a valid value", pRoamingCtrl_data-> postAssnSelfSteerTimeframe);
            UT_PASS("Post-association self steer timeframe validation success");
        }
        else
        {
            UT_LOG("Post-association self steer timeframe is  %d which is a invalid value", pRoamingCtrl_data-> postAssnSelfSteerTimeframe);
            UT_FAIL("Post-association self steer timeframe validation failed");
        }
        if ( pRoamingCtrl_data-> postAssnBackOffTime >= 0 && pRoamingCtrl_data-> postAssnBackOffTime <= 36000 )
        {
            UT_LOG("Post-association backoff time is %d which is a valid value", pRoamingCtrl_data-> postAssnBackOffTime);
            UT_PASS("Post-association backoff time validation success");
        }
        else
        {
            UT_LOG("Post-association backoff time is  %d which is a invalid value", pRoamingCtrl_data-> postAssnBackOffTime);
            UT_FAIL("Post-association backoff time validation failed");
        }
        if ( pRoamingCtrl_data-> postAssnAPctrlThreshold >= -100 && pRoamingCtrl_data-> postAssnAPctrlThreshold <= 0 )
        {
            UT_LOG("Post-association AP steer control threshold is %d which is a valid value", pRoamingCtrl_data-> postAssnAPctrlThreshold);
            UT_PASS("Post-association AP steer control threshold validation success");
        }
        else
        {
            UT_LOG("Post-association AP steer control threshold is %d which is a invalid value", pRoamingCtrl_data-> postAssnAPctrlThreshold);
            UT_FAIL("Post-association AP steer control threshold validation failed");
        }
        if ( pRoamingCtrl_data-> postAssnAPctrlTimeframe >= -100 && pRoamingCtrl_data->postAssnAPctrlTimeframe <= 0 )
        {
            UT_LOG("Post-association AP steer control time frame is %d which is a valid value", pRoamingCtrl_data-> postAssnAPctrlTimeframe);
            UT_PASS("Post-association AP steer control time frame validation success");
        }
        else
        {
            UT_LOG("Post-association AP steer control time frame is %d which is a invalid value", pRoamingCtrl_data-> postAssnAPctrlTimeframe);
            UT_FAIL("Post-association AP steer control time frame validation failed");
        }
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }
    UT_LOG("Exiting test_l1_wifi_client_hal_positive1_wifi_getRoamingControl...");
}

/**
* @brief This function checks if wifi_getRoamingControl works as expected, when it is invoked after calling wifi_initWithConfig(), with valid values.
*
* This test aims to verify the correct behavior of wifi_getRoamingControl API when provided with valid arguments.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 067 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:** @n
*
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking the wifi_getRoamingControl API with ssidIndex = 1 and pRoamingCtrl_data = valid structure | ssidIndex = 1 and pRoamingCtrl_data = valid structure | RETURN_OK | Should Pass |
*/
void test_l1_wifi_client_hal_positive2_wifi_getRoamingControl( void )
{
    UT_LOG("Entering test_l1_wifi_client_hal_positive2_wifi_getRoamingControl...");
    WiFi_UnInitPosReq();
    WiFi_InitWithConfigPreReq();

    int ssidIndex = 1;
    wifi_roamingCtrl_t *pRoamingCtrl_data = (wifi_roamingCtrl_t*)malloc(sizeof(wifi_roamingCtrl_t));
    if(pRoamingCtrl_data != NULL)
    { 
        UT_LOG("Invoking wifi_getRoamingControl with ssidIndex = 1 and pRoamingCtrl_data = valid structure.");
        int retVal = wifi_getRoamingControl(ssidIndex, pRoamingCtrl_data);
    
        UT_LOG("wifi_getRoamingControl API returns : %d",retVal);
        UT_ASSERT_EQUAL(retVal, RETURN_OK);
    
        UT_LOG("Values are, roaming control :%d, selfSteerOverride : %d, roam80211kvrEnable : %d, Pre-association best RSSI threshold : %d, Pre-association best RSSI delta : %d, Post-association delta level if WiFi connected : %d, Post-association delta level if WiFi disconnected : %d, Post-association self steer threshold : %d, Post-association self steer timeframe : %d, Post-association backoff time : %d, Post-association AP steer control threshold : %d, Post-association AP steer control time frame : %d",pRoamingCtrl_data->roamingEnable, pRoamingCtrl_data->selfSteerOverride, pRoamingCtrl_data->preassnBestThreshold, pRoamingCtrl_data->preassnBestDelta, pRoamingCtrl_data->postAssnLevelDeltaConnected, pRoamingCtrl_data->postAssnLevelDeltaDisconnected,pRoamingCtrl_data->postAssnSelfSteerThreshold, pRoamingCtrl_data->postAssnSelfSteerTimeframe, pRoamingCtrl_data->postAssnBackOffTime, pRoamingCtrl_data->postAssnAPctrlThreshold, pRoamingCtrl_data->postAssnAPctrlTimeframe );
        if ( pRoamingCtrl_data->roamingEnable == 0 || pRoamingCtrl_data->roamingEnable == 1 )
        {
            UT_LOG("roaming control is %d which is a valid value", pRoamingCtrl_data->roamingEnable);
            UT_PASS("roaming control validation success");
        }
        else
        {
            UT_LOG("roaming control is %d which is an invalid value", pRoamingCtrl_data->roamingEnable);
            UT_FAIL("roaming control validation failed");
        }
        if ( pRoamingCtrl_data-> selfSteerOverride == 0 || pRoamingCtrl_data-> selfSteerOverride == 1 )
        {
            UT_LOG("self Steer Override is %d which is a valid value", pRoamingCtrl_data-> selfSteerOverride);
            UT_PASS("self Steer Override validation success");
        }
        else
        {
            UT_LOG("self Steer Override is %d which is a valid value", pRoamingCtrl_data-> selfSteerOverride);
            UT_FAIL("self Steer Override validation failed");
        }
        if ( pRoamingCtrl_data-> roam80211kvrEnable == 0 || pRoamingCtrl_data-> roam80211kvrEnable == 1 )
        {
            UT_LOG("roam 80211kvr Enable is %d which is a valid value", pRoamingCtrl_data-> roam80211kvrEnable);
            UT_PASS("roam 80211kvr Enable validation success");
        }
        else
        {
            UT_LOG("roam 80211kvr Enable is %d which is an invalid value", pRoamingCtrl_data-> roam80211kvrEnable);
            UT_FAIL("roam 80211kvr Enable validation failed");
        }
        if ( pRoamingCtrl_data->preassnBestThreshold >= -100 && pRoamingCtrl_data->preassnBestThreshold <= 0 )
        {
            UT_LOG("Pre-association best RSSI threshold is %d which is a valid value", pRoamingCtrl_data->preassnBestThreshold);
            UT_PASS("Pre-association best RSSI threshold validation success");
        }
        else
        {
            UT_LOG("Pre-association best RSSI threshold is %d which is a invalid value", pRoamingCtrl_data->preassnBestThreshold);
            UT_FAIL("Pre-association best RSSI threshold validation failed");
        }
        if ( pRoamingCtrl_data->preassnBestDelta >= 0 && pRoamingCtrl_data->preassnBestDelta <= 100 )
        {
            UT_LOG("Pre-association best RSSI delta is %d which is a valid value", pRoamingCtrl_data->preassnBestDelta);
            UT_PASS("Pre-association best RSSI delta validation success");
        }
        else
        {
            UT_LOG("Pre-association best RSSI delta %d which is an invalid value", pRoamingCtrl_data->preassnBestDelta);
            UT_FAIL("Pre-association best RSSI delta validation failed");
        }
        if ( pRoamingCtrl_data->postAssnLevelDeltaConnected >= 0 && pRoamingCtrl_data->postAssnLevelDeltaConnected <= 100 )
        {
            UT_LOG("Post-association delta level if WiFi connected is %d which is a valid value", pRoamingCtrl_data->postAssnLevelDeltaConnected);
            UT_PASS("Post-association delta level validation success");
        }
        else
        {
            UT_LOG("Post-association delta level if WiFi connected is %d which is a invalid value", pRoamingCtrl_data->postAssnLevelDeltaConnected);
            UT_FAIL("Post-association delta level validation failed");
        }
        if ( pRoamingCtrl_data->postAssnLevelDeltaDisconnected >= 0 && pRoamingCtrl_data->postAssnLevelDeltaDisconnected <= 100 )
        {
            UT_LOG("Post-association delta level if WiFi disconnected is %d which is a valid value", pRoamingCtrl_data->postAssnLevelDeltaDisconnected);
            UT_PASS("Post-association delta level if WiFi disconnected validation success");
        }
        else
        {
            UT_LOG("Post-association delta level if WiFi disconnected is %d which is a invalid value", pRoamingCtrl_data->postAssnLevelDeltaDisconnected);
            UT_FAIL("Post-association delta level if WiFi disconnected validation failed");
        }
        if ( pRoamingCtrl_data-> postAssnSelfSteerThreshold >= -100 && pRoamingCtrl_data-> postAssnSelfSteerThreshold <= 0 )
        {
            UT_LOG("Post-association self steer threshold is %d which is a valid value", pRoamingCtrl_data-> postAssnSelfSteerThreshold);
            UT_PASS("Post-association self steer threshold validation success");
        }
        else
        {
            UT_LOG("Post-association self steer threshold is %d which is a invalid value", pRoamingCtrl_data-> postAssnSelfSteerThreshold);
            UT_FAIL("Post-association self steer threshold validation failed");
        }
        if ( pRoamingCtrl_data-> postAssnSelfSteerTimeframe >= 0 && pRoamingCtrl_data-> postAssnSelfSteerTimeframe <= 36000 )
        {
            UT_LOG("Post-association self steer timeframe is %d which is a valid value", pRoamingCtrl_data-> postAssnSelfSteerTimeframe);
            UT_PASS("Post-association self steer timeframe validation success");
        }
        else
        {
            UT_LOG("Post-association self steer timeframe is  %d which is a invalid value", pRoamingCtrl_data-> postAssnSelfSteerTimeframe);
            UT_FAIL("Post-association self steer timeframe validation failed");
        }
        if ( pRoamingCtrl_data-> postAssnBackOffTime >= 0 && pRoamingCtrl_data-> postAssnBackOffTime >= 36000 )
        {
            UT_LOG("Post-association backoff time is %d which is a valid value", pRoamingCtrl_data-> postAssnBackOffTime);
            UT_PASS("Post-association backoff time validation success");
        }
        else
        {
            UT_LOG("Post-association backoff time is  %d which is a invalid value", pRoamingCtrl_data-> postAssnBackOffTime);
            UT_FAIL("Post-association backoff time validation failed");
        }
        if ( pRoamingCtrl_data-> postAssnAPctrlThreshold >= -100 && pRoamingCtrl_data-> postAssnAPctrlThreshold <= 0 )
        {
            UT_LOG("Post-association AP steer control threshold is %d which is a valid value", pRoamingCtrl_data-> postAssnAPctrlThreshold);
            UT_PASS("Post-association AP steer control threshold validation success");
        }
        else
        {
            UT_LOG("Post-association AP steer control threshold is %d which is a invalid value", pRoamingCtrl_data-> postAssnAPctrlThreshold);
            UT_FAIL("Post-association AP steer control threshold validation failed");
        }
        if ( pRoamingCtrl_data-> postAssnAPctrlTimeframe >= -100 && pRoamingCtrl_data->postAssnAPctrlTimeframe <= 0 )
        {
            UT_LOG("Post-association AP steer control time frame is %d which is a valid value", pRoamingCtrl_data-> postAssnAPctrlTimeframe);
            UT_PASS("Post-association AP steer control time frame validation success");
        }
        else
        {
            UT_LOG("Post-association AP steer control time frame is %d which is a invalid value", pRoamingCtrl_data-> postAssnAPctrlTimeframe);
            UT_FAIL("Post-association AP steer control time frame validation failed");
        }
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }
    WiFi_UnInitPosReq();
    WiFi_InitPreReq();

    UT_LOG("Exiting test_l1_wifi_client_hal_positive2_wifi_getRoamingControl...");
}

/**
 * @brief This function checks if wifi_getRoamingControl works as expected when valid value is passed.
 *
 * In this test, we will invoke the wifi_getRoamingControl API on an invalid SSID index and expect it to fail.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 068 @n
 * **Priority:** High @n@n
 * 
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
 * 
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data |Expected Result |Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Invoke wifi_getRoamingControl with invalid ssidIndex = 0, pRoamingCtrl_data = valid strcuture  | ssidIndex = 0, pRoamingCtrl_data = valid strcuture | RETURN_ERR | Should Fail |
 */
void test_l1_wifi_client_hal_negative1_wifi_getRoamingControl( void )
{
    UT_LOG("Entering test_l1_wifi_client_hal_negative1_wifi_getRoamingControl...");
    int ssidIndex = 0;
    wifi_roamingCtrl_t *pRoamingCtrl_data = (wifi_roamingCtrl_t*)malloc(sizeof(wifi_roamingCtrl_t));
    if(pRoamingCtrl_data != NULL)
    { 
        UT_LOG("Invoked wifi_getRoamingControl with ssidIndex=0 and pRoamingCtrl_data = valid structure.");
        int retVal = wifi_getRoamingControl(ssidIndex, pRoamingCtrl_data);
        
        UT_LOG("wifi_getRoamingContro API returns :%d", retVal);
        UT_ASSERT_EQUAL(retVal, RETURN_ERR);
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }  
    UT_LOG("Exiting test_l1_wifi_client_hal_negative1_wifi_getRoamingControl...");
}

/**
 * @brief This function checks if wifi_getRoamingControl works as expected when valid value is passed.
 *
 * This test function invokes the wifi_getRoamingControl API with valid ssidIndex and NULL pointer for the output parameter.
 * It checks if the API behaves as per expectation when invoked with invalid output pointer (NULL). If the function returns without any error then the API is not behaving as per expectation.
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 069 @n
 * **Priority:** High @n@n
 * 
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
 * 
 * **Test Procedure:** @n
 * | Variation / Step | Description | Test Data |Expected Result |Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | The wifi_getRoamingControl API is invoked with ssidIndex = 1, pRoamingCtrl_data = NULL | ssidIndex = 1, pRoamingCtrl_data = NULL | RETURN_ERR | Should Fail |
 */
void test_l1_wifi_client_hal_negative2_wifi_getRoamingControl( void )
{
    UT_LOG("Entering test_l1_wifi_client_hal_negative2_wifi_getRoamingControl...");
    int ssidIndex = 1;
    wifi_roamingCtrl_t *pRoamingCtrl_data = NULL;

    UT_LOG("Invoking wifi_getRoamingControl with ssidIndex = 1 and pRoamingCtrl_data = NULL");
    int retVal = wifi_getRoamingControl(ssidIndex, pRoamingCtrl_data);
    
    UT_LOG("wifi_getRoamingControl API returns : %d",retVal);
    UT_ASSERT_EQUAL(retVal, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_client_hal_negative2_wifi_getRoamingControl...");
}

/**
* @brief This test aims to verify the function wifi_getRoamingControl in a scenario where the wifi_init or wifi_initWithConfig function has not been called.
*
* In this test, the function wifi_getRoamingControl is executed without having invoked the wifi_init or wifi_initWithConfig earlier, this to simulate an error/exception scenario.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 070 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: |--------- | ---------- |-------------- | ----- |
* | 01 | Call the function wifi_getRoamingControl without calling wifi_init or wifi_initWithConfig | ssidIndex = 1, pRoamingCtrl_data = valid structure | RETURN_ERR | Should Fail |
*/
void test_l1_wifi_client_hal_negative3_wifi_getRoamingControl( void )
{
    UT_LOG("Entering test_l1_wifi_client_hal_negative3_wifi_getRoamingControl...");
    WiFi_UnInitPosReq();

    int ssidIndex = 1;
    wifi_roamingCtrl_t *pRoamingCtrl_data = (wifi_roamingCtrl_t*)malloc(sizeof(wifi_roamingCtrl_t));
    if(pRoamingCtrl_data != NULL)
    {
        UT_LOG("Invoked wifi_getRoamingControl without prior call to wifi_init or wifi_initWithConfig");
        int retVal = wifi_getRoamingControl(ssidIndex, pRoamingCtrl_data);
    
        UT_LOG("wifi_getRoamingControl API Returns : %d",retVal);
        UT_ASSERT_EQUAL(retVal, RETURN_ERR);
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    } 

    WiFi_InitPreReq();
    UT_LOG("Exiting test_l1_wifi_client_hal_negative3_wifi_getRoamingControl...");
}

/**
* @brief This function checks if wifi_cancelWpsPairing  works as expected, when it is invoked after calling wifi_init().
*
* This test aims to verify that the wifi_cancelWpsPairing API successfully cancels the WPS pairing when invoked with valid input parameters. It also ensures that the API returns the correct status code.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 071 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking wifi_cancelWpsPairing API | NA | RETURN_OK | Should Pass |
*/
void test_l1_wifi_client_hal_positive1_wifi_cancelWpsPairing(void) {
    UT_LOG("Entering test_l1_wifi_client_hal_positive1_wifi_cancelWpsPairing...");

    UT_LOG("Invoking wifi_cancelWpsPairing API.");
    INT status = wifi_cancelWpsPairing();
    
    UT_LOG("wifi_cancelWpsPairing API returns : %d",status);
    UT_ASSERT_EQUAL(status, RETURN_OK);

    UT_LOG("Exiting test_l1_wifi_client_hal_positive1_wifi_cancelWpsPairing...");
}

/**
* @brief This function checks if wifi_cancelWpsPairing  works as expected, when it is invoked after calling wifi_initWithConfig().
*
* This test aims to verify that the wifi_cancelWpsPairing API successfully cancels the WPS pairing when invoked with valid input parameters. It also ensures that the API returns the correct status code.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 072 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking wifi_cancelWpsPairing API | NA | RETURN_OK | Should Pass |
*/
void test_l1_wifi_client_hal_positive2_wifi_cancelWpsPairing(void) {
    UT_LOG("Entering test_l1_wifi_client_hal_positive2_wifi_cancelWpsPairing...");

    WiFi_UnInitPosReq();
    WiFi_InitWithConfigPreReq();

    UT_LOG("Invoking wifi_cancelWpsPairing API.");
    INT status = wifi_cancelWpsPairing();
    
    UT_LOG("wifi_cancelWpsPairing API returns : %d",status);
    UT_ASSERT_EQUAL(status, RETURN_OK);

    WiFi_UnInitPosReq();
    WiFi_InitPreReq();

    UT_LOG("Exiting test_l1_wifi_client_hal_positive2_wifi_cancelWpsPairing...");
}

/**
* @brief This test verifies the wifi_setRoamingControl function's behavior when invoked without the wifi_init() or wifi_initWithConfig() function being called first.
*
* The test verifies the behavior of the wifi_setRoamingControl when invoked without calling wifi_init.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 073 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 02 | Invoking wifi_cancelWpsPairing API without calling wifi_init() or wifi_initWithConfig() | NA | RETURN_ERR| Should Fail | 
*/
void test_l1_wifi_client_hal_negative1_wifi_cancelWpsPairing(void) {
    UT_LOG("Entering test_l1_wifi_client_hal_negative1_wifi_cancelWpsPairing...");
    WiFi_UnInitPosReq();

    UT_LOG("Invoking wifi_cancelWpsPairing API.");
    INT status = wifi_cancelWpsPairing();
    
    UT_LOG("wifi_cancelWpsPairing API returns : %d",status);
    UT_ASSERT_EQUAL(status, RETURN_OK);
    
    WiFi_InitPreReq();
    UT_LOG("Exiting test_l1_wifi_client_hal_negative1_wifi_cancelWpsPairing...");
}

static UT_test_suite_t * pSuite = NULL;

/**
 * @brief Register the main tests for this module
 *
 * @return int - 0 on success, otherwise failure
 */

int test_wifi_client_hal_register(void)
{
    // Create the test suite
    pSuite = UT_add_suite("[L1 wifi_client_hal]", NULL, NULL);
    if (pSuite == NULL) {
        return -1;
    }

    // List of test function names and strings
    const char* list1[] = {"l1_wifi_client_hal_positive1_wifi_getCliWpsConfigMethodsSupported", "l1_wifi_client_hal_positive2_wifi_getCliWpsConfigMethodsSupported", "l1_wifi_client_hal_negative1_wifi_getCliWpsConfigMethodsSupported", "l1_wifi_client_hal_negative2_wifi_getCliWpsConfigMethodsSupported", "l1_wifi_client_hal_negative3_wifi_getCliWpsConfigMethodsSupported", "l1_wifi_client_hal_positive1_wifi_getCliWpsConfigMethodsEnabled", "l1_wifi_client_hal_positive2_wifi_getCliWpsConfigMethodsEnabled", "l1_wifi_client_hal_negative1_wifi_getCliWpsConfigMethodsEnabled", "l1_wifi_client_hal_negative2_wifi_getCliWpsConfigMethodsEnabled", "l1_wifi_client_hal_negative3_wifi_getCliWpsConfigMethodsEnabled", "l1_wifi_client_hal_positive1_wifi_setCliWpsConfigMethodsEnabled", "l1_wifi_client_hal_positive2_wifi_setCliWpsConfigMethodsEnabled", "l1_wifi_client_hal_positive3_wifi_setCliWpsConfigMethodsEnabled", "l1_wifi_client_hal_negative1_wifi_setCliWpsConfigMethodsEnabled", "l1_wifi_client_hal_negative2_wifi_setCliWpsConfigMethodsEnabled", "l1_wifi_client_hal_negative3_wifi_setCliWpsConfigMethodsEnabled", "l1_wifi_client_hal_negative4_wifi_setCliWpsConfigMethodsEnabled", "l1_wifi_client_hal_negative5_wifi_setCliWpsConfigMethodsEnabled", "l1_wifi_client_hal_positive1_wifi_setCliWpsEnrolleePin", "l1_wifi_client_hal_positive2_wifi_setCliWpsEnrolleePin", "l1_wifi_client_hal_negative1_wifi_setCliWpsEnrolleePin", "l1_wifi_client_hal_negative2_wifi_setCliWpsEnrolleePin", "l1_wifi_client_hal_negative3_wifi_setCliWpsEnrolleePin", "l1_wifi_client_hal_negative4_wifi_setCliWpsEnrolleePin", "l1_wifi_client_hal_positive1_wifi_setCliWpsButtonPush", "l1_wifi_client_hal_positive2_wifi_setCliWpsButtonPush", "l1_wifi_client_hal_negative1_wifi_setCliWpsButtonPush", "l1_wifi_client_hal_negative2_wifi_setCliWpsButtonPush", "l1_wifi_client_hal_positive1_wifi_connectEndpoint", "l1_wifi_client_hal_positive2_wifi_connectEndpoint", "l1_wifi_client_hal_positive3_wifi_connectEndpoint", "l1_wifi_client_hal_positive4_wifi_connectEndpoint", "l1_wifi_client_hal_negative1_wifi_connectEndpoint", "l1_wifi_client_hal_negative2_wifi_connectEndpoint", "l1_wifi_client_hal_negative3_wifi_connectEndpoint", "l1_wifi_client_hal_negative4_wifi_connectEndpoint", "l1_wifi_client_hal_negative5_wifi_connectEndpoint", "l1_wifi_client_hal_negative6_wifi_connectEndpoint", "l1_wifi_client_hal_negative7_wifi_connectEndpoint", "l1_wifi_client_hal_negative8_wifi_connectEndpoint", "l1_wifi_client_hal_negative9_wifi_connectEndpoint", "l1_wifi_client_hal_negative10_wifi_connectEndpoint", "l1_wifi_client_hal_negative11_wifi_connectEndpoint", "l1_wifi_client_hal_positive1_wifi_disconnectEndpoint", "l1_wifi_client_hal_positive2_wifi_disconnectEndpoint", "l1_wifi_client_hal_negative1_wifi_disconnectEndpoint", "l1_wifi_client_hal_negative2_wifi_disconnectEndpoint", "l1_wifi_client_hal_negative3_wifi_disconnectEndpoint", "l1_wifi_client_hal_negaitive4_wifi_disconnectEndpoint", "l1_wifi_client_hal_positive1_wifi_clearSSIDInfo", "l1_wifi_client_hal_positive2_wifi_clearSSIDInfo", "l1_wifi_client_hal_negative1_wifi_clearSSIDInfo", "l1_wifi_client_hal_negative2_wifi_clearSSIDInfo", "l1_wifi_client_hal_negative3_wifi_clearSSIDInfo", "l1_wifi_client_hal_positive1_wifi_lastConnected_Endpoint", "l1_wifi_client_hal_positive2_wifi_lastConnected_Endpoint", "l1_wifi_client_hal_negative1_wifi_lastConnected_Endpoint", "l1_wifi_client_hal_negative2_wifi_lastConnected_Endpoint", "l1_wifi_client_hal_positive1_wifi_setRoamingControl", "l1_wifi_client_hal_positive2_wifi_setRoamingControl", "l1_wifi_client_hal_negative1_wifi_setRoamingControl", "l1_wifi_client_hal_negative2_wifi_setRoamingControl", "l1_wifi_client_hal_negative3_wifi_setRoamingControl", "l1_wifi_client_hal_negative4_wifi_setRoamingControl", "l1_wifi_client_hal_negative5_wifi_setRoamingControl", "l1_wifi_client_hal_positive1_wifi_getRoamingControl", "l1_wifi_client_hal_positive2_wifi_getRoamingControl", "l1_wifi_client_hal_negative1_wifi_getRoamingControl", "l1_wifi_client_hal_negative2_wifi_getRoamingControl", "l1_wifi_client_hal_negative3_wifi_getRoamingControl", "l1_wifi_client_hal_positive1_wifi_cancelWpsPairing", "l1_wifi_client_hal_positive2_wifi_cancelWpsPairing", "l1_wifi_client_hal_negative1_wifi_cancelWpsPairing" };
    void (*list2[])() = {test_l1_wifi_client_hal_positive1_wifi_getCliWpsConfigMethodsSupported, test_l1_wifi_client_hal_positive2_wifi_getCliWpsConfigMethodsSupported, test_l1_wifi_client_hal_negative1_wifi_getCliWpsConfigMethodsSupported, test_l1_wifi_client_hal_negative2_wifi_getCliWpsConfigMethodsSupported, test_l1_wifi_client_hal_negative3_wifi_getCliWpsConfigMethodsSupported, test_l1_wifi_client_hal_positive1_wifi_getCliWpsConfigMethodsEnabled, test_l1_wifi_client_hal_positive2_wifi_getCliWpsConfigMethodsEnabled, test_l1_wifi_client_hal_negative1_wifi_getCliWpsConfigMethodsEnabled, test_l1_wifi_client_hal_negative2_wifi_getCliWpsConfigMethodsEnabled, test_l1_wifi_client_hal_negative3_wifi_getCliWpsConfigMethodsEnabled, test_l1_wifi_client_hal_positive1_wifi_setCliWpsConfigMethodsEnabled, test_l1_wifi_client_hal_positive2_wifi_setCliWpsConfigMethodsEnabled, test_l1_wifi_client_hal_positive3_wifi_setCliWpsConfigMethodsEnabled, test_l1_wifi_client_hal_negative1_wifi_setCliWpsConfigMethodsEnabled, test_l1_wifi_client_hal_negative2_wifi_setCliWpsConfigMethodsEnabled, test_l1_wifi_client_hal_negative3_wifi_setCliWpsConfigMethodsEnabled, test_l1_wifi_client_hal_negative4_wifi_setCliWpsConfigMethodsEnabled, test_l1_wifi_client_hal_negative5_wifi_setCliWpsConfigMethodsEnabled, test_l1_wifi_client_hal_positive1_wifi_setCliWpsEnrolleePin, test_l1_wifi_client_hal_positive2_wifi_setCliWpsEnrolleePin, test_l1_wifi_client_hal_negative1_wifi_setCliWpsEnrolleePin, test_l1_wifi_client_hal_negative2_wifi_setCliWpsEnrolleePin, test_l1_wifi_client_hal_negative3_wifi_setCliWpsEnrolleePin, test_l1_wifi_client_hal_negative4_wifi_setCliWpsEnrolleePin, test_l1_wifi_client_hal_positive1_wifi_setCliWpsButtonPush, test_l1_wifi_client_hal_positive2_wifi_setCliWpsButtonPush, test_l1_wifi_client_hal_negative1_wifi_setCliWpsButtonPush, test_l1_wifi_client_hal_negative2_wifi_setCliWpsButtonPush, test_l1_wifi_client_hal_positive1_wifi_connectEndpoint, test_l1_wifi_client_hal_positive2_wifi_connectEndpoint, test_l1_wifi_client_hal_positive3_wifi_connectEndpoint, test_l1_wifi_client_hal_positive4_wifi_connectEndpoint, test_l1_wifi_client_hal_negative1_wifi_connectEndpoint, test_l1_wifi_client_hal_negative2_wifi_connectEndpoint, test_l1_wifi_client_hal_negative3_wifi_connectEndpoint, test_l1_wifi_client_hal_negative4_wifi_connectEndpoint, test_l1_wifi_client_hal_negative5_wifi_connectEndpoint, test_l1_wifi_client_hal_negative6_wifi_connectEndpoint, test_l1_wifi_client_hal_negative7_wifi_connectEndpoint, test_l1_wifi_client_hal_negative8_wifi_connectEndpoint, test_l1_wifi_client_hal_negative9_wifi_connectEndpoint, test_l1_wifi_client_hal_negative10_wifi_connectEndpoint, test_l1_wifi_client_hal_negative11_wifi_connectEndpoint, test_l1_wifi_client_hal_positive1_wifi_disconnectEndpoint, test_l1_wifi_client_hal_positive2_wifi_disconnectEndpoint, test_l1_wifi_client_hal_negative1_wifi_disconnectEndpoint, test_l1_wifi_client_hal_negative2_wifi_disconnectEndpoint, test_l1_wifi_client_hal_negative3_wifi_disconnectEndpoint, test_l1_wifi_client_hal_negaitive4_wifi_disconnectEndpoint, test_l1_wifi_client_hal_positive1_wifi_clearSSIDInfo, test_l1_wifi_client_hal_positive2_wifi_clearSSIDInfo, test_l1_wifi_client_hal_negative1_wifi_clearSSIDInfo, test_l1_wifi_client_hal_negative2_wifi_clearSSIDInfo, test_l1_wifi_client_hal_negative3_wifi_clearSSIDInfo, test_l1_wifi_client_hal_positive1_wifi_lastConnected_Endpoint, test_l1_wifi_client_hal_positive2_wifi_lastConnected_Endpoint, test_l1_wifi_client_hal_negative1_wifi_lastConnected_Endpoint, test_l1_wifi_client_hal_negative2_wifi_lastConnected_Endpoint, test_l1_wifi_client_hal_positive1_wifi_setRoamingControl, test_l1_wifi_client_hal_positive2_wifi_setRoamingControl, test_l1_wifi_client_hal_negative1_wifi_setRoamingControl, test_l1_wifi_client_hal_negative2_wifi_setRoamingControl, test_l1_wifi_client_hal_negative3_wifi_setRoamingControl, test_l1_wifi_client_hal_negative4_wifi_setRoamingControl, test_l1_wifi_client_hal_negative5_wifi_setRoamingControl, test_l1_wifi_client_hal_positive1_wifi_getRoamingControl, test_l1_wifi_client_hal_positive2_wifi_getRoamingControl, test_l1_wifi_client_hal_negative1_wifi_getRoamingControl, test_l1_wifi_client_hal_negative2_wifi_getRoamingControl, test_l1_wifi_client_hal_negative3_wifi_getRoamingControl, test_l1_wifi_client_hal_positive1_wifi_cancelWpsPairing, test_l1_wifi_client_hal_positive2_wifi_cancelWpsPairing, test_l1_wifi_client_hal_negative1_wifi_cancelWpsPairing };
    
   // Add tests to the suite
    for (int i = 0; i < sizeof(list1) / sizeof(list1[0]); i++) {
        UT_add_test(pSuite, list1[i], list2[i]);
    }
    return 0;
}

int main(int argc, char** argv)
{
    int registerReturn = 0;
    
    /* Register tests as required, then call the UT-main to support switches and triggering */
    UT_init( argc, argv );
    /* Check if tests are registered successfully */
    registerReturn = test_wifi_client_hal_register();
    if (registerReturn == 0)
    {
        printf("test_wifi_client_hal_register() returned success");
    }
    else
    {
        printf("test_wifi_client_hal_register() returned failure");
        return 1;
    }
    
    WiFi_InitPreReq();
    
    /* Begin test executions */
    UT_run_tests();
    
    WiFi_UnInitPosReq();
   
    return 0;
}
