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
* @file test_wifi_common_hal.c
* @page wifi_common_hal Level 1 Tests
*
* ## Module's Role
* This module includes Level 1 functional tests (success and failure scenarios).
* This is to ensure that the wifi_common_hal APIs meet the requirements across all vendors.
*
* **Pre-Conditions:**  None@n
* **Dependencies:** None@n
*
* Ref to API Definition specification documentation : [halSpec.md](../../../docs/halSpec.md)
*/

#include <ut.h>
#include <ut_log.h>
#include<stdlib.h>
#include<string.h>

#include "wifi_common_hal.h"

extern void WiFi_InitPreReq(void);                               
extern void WiFi_InitWithConfigPreReq(void);                     
extern void WiFi_UnInitPosReq(void); 

#define MAX_OUTPUT_STRING_LEN 50
#define MAX_LENGTH 256

const char* secmode[] = {"None", "WEP", "WPA", "WPA2", "WPA3", "WPA-WPA2", "WPA2-WPA3", "WPA-Enterprise", "WPA2-Enterprise", "WPA-WPA2-Enterprise"};
int freqList[] = {2412, 2417, 2422, 2427, 2432, 2437, 2442, 2447, 2452, 2457, 2462, 2467, 2472, 5160, 5180, 5200, 5220, 5240, 5260, 5280, 5300, 5320, 5340, 5480, 5500, 5520, 5540, 5560, 5580, 5600, 5620, 5640, 5660, 5680, 5700, 5720, 5745, 5765, 5785, 5805, 5825, 5845, 5865, 5885};
const char* radiostatus[] = {"Up", "Down", "Unknown", "Dormant", "NotPresent", "LowerLayerDown"};
const char* bandwidth[] = {"20MHz", "40MHz", "80MHz", "160MHz", "Auto"};

int check_value(const char* target, const char* list[], int count) {
    for (int i = 0; i < count; i++) {
        if (strcmp(target, list[i]) == 0) {
            return 1; // String found in the list
        }
    }
    return 0; // String not found in the list
}

/**
* @brief Test to verify the functionality of wifi_getHalVersion
*
* This test verifies the correct operation of wifi_getHalVersion API when a valid output string buffer is provided. It mainly scrutinizes the return value to assert the success of invocation. @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 001 @n
* **Priority:** High @n 
* @n
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking the wifi_getHalVersion API with a valid buffer | output_test_string = valid buffer | RETURN_OK| Should be successful |
*/
void test_l1_wifi_common_hal_positive1_wifi_getHalVersion(void)
{
    UT_LOG("Entering test_l1_wifi_common_hal_positive1_wifi_getHalVersion...");
    /* Variables for test */
    CHAR output_test_string[20];
    INT return_status;	

    UT_LOG("Invoking wifi_getHalVersion with valid output_string buffer.");
    /* Call the wifi_getHalVersion function */
    return_status = wifi_getHalVersion(output_test_string);
	/* Log the test description and result */
    UT_LOG("The returned status is %d, and the obtained HAL version is %s",return_status, output_test_string);
    /* Assert using UT_ASSERT_EQUAL to check the return value */
    UT_ASSERT_EQUAL(return_status, RETURN_OK);
    UT_LOG("Exiting test_l1_wifi_common_hal_positive1_wifi_getHalVersion...");
}

/**
* @brief Test the wifi_getHalVersion function for NULL output_string buffer
*
* This test verifies the correct error return when the wifi_getHalVersion function is invoked with the output_string parameter set to NULL. This is relevant to ensure robustness and validate error handling. @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 002 @n
* **Priority:** High @n
* @n
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_getHalVersion with Null output_string buffer | output_test_string = NULL | RETURN_ERR | Should return error |
*/
void test_l1_wifi_common_hal_negative1_wifi_getHalVersion(void)
{
    /* Start of Logging */
    UT_LOG("Entering test_l1_wifi_common_hal_negative1_wifi_getHalVersion...");

    /* Variables for test */
    CHAR *output_test_string = NULL;
    INT return_status;
    UT_LOG("Invoking wifi_getHalVersion with NULL output_string buffer.");
    /* Call the wifi_getHalVersion function */
    return_status = wifi_getHalVersion(output_test_string);

    /* Log the test description and result */
    UT_LOG(" The returned status is %d", return_status);

    /* Assert using UT_ASSERT_EQUAL to check the return value */
    UT_ASSERT_EQUAL(return_status, RETURN_ERR);
    UT_LOG("Exiting test_l1_wifi_common_hal_negative1_wifi_getHalVersion...");
}

/**
* @brief This test case checks whether wifi_init API is working correctly without any input parameters.
*
* In this test, we are invoking the wifi_init API with no input parameters. The expected result is RETURN_OK. The purpose of this test is to check the basic functionality and robustness of the wifi_init API. @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 003 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data|Expected Result  |Notes |
* | :----: | ---------  | ----------   |--------------  | -----|
* | 01 | Invoke wifi_init without parameters | None  | RETURN_OK | Should be successful |
*/
void test_l1_wifi_common_hal_positive1_wifi_init( void )
{
    UT_LOG("Entering test_l1_wifi_common_hal_positive1_wifi_init...");
    INT result;

    // Log the test description and result
    UT_LOG("Invoking wifi_init without any input parameters. Expecting RETURN_OK.");
	WiFi_UnInitPosReq();
    result = wifi_init();
    UT_LOG("Returned value was %d", result);
    // Check the result
    UT_ASSERT_EQUAL(result, RETURN_OK);
    UT_LOG("Exiting test_l1_wifi_common_hal_positive1_wifi_init...\n");
}

/**
* @brief Tests the initialization of wifi_initWithConfig with valid configuration
*
* This test checks if the Wifi HAL API initializes correctly when provided wifi_initWithConfig with a valid configuration. @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 004 @n
* **Priority:** High @n
* @n
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_initWithConfig with a valid configuration defined in wifi_halConfig_t | conf = valid pointer | RETURN_OK | Should be successful |
*/
void test_l1_wifi_common_hal_positive1_wifi_initWithConfig(void) {
    wifi_halConfig_t conf;
	int result;
    UT_LOG("Entering test_l1_wifi_common_hal_positive1_wifi_initWithConfig...");

	strcpy(conf.wlan_Interface,"wlan0");
	WiFi_UnInitPosReq();
	UT_LOG("Invoking wifi_initWithConfig with valid structure");	
	result = wifi_initWithConfig(&conf);
    UT_LOG("Returned value was %d", result);
	WiFi_UnInitPosReq();
	WiFi_InitPreReq();
    UT_ASSERT_EQUAL(result, RETURN_OK);	
    UT_LOG("Exiting test_l1_wifi_common_hal_positive1_wifi_initWithConfig...");	
}

/**
* @brief  Tests the initialization of wifi wifi_initWithConfig with NULL configuration
*
* This test aims to verify the handling of invalid configuration while initializing Wi-Fi via wifi_initWithConfigin the HAL layer. It forms a vital part of the negative testing for robustness of the software. @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 005 @n
* **Priority:** High @n
* @n
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | ------------- | ---------- |-------------- | ----- |
* | 01 | Initialize wifi_initWithConfig with a null configuration | config = NULL| RETURN_ERR | Should return error |
*/
void test_l1_wifi_common_hal_negative1_wifi_initWithConfig(void) {

	int result;
    UT_LOG("Entering test_l1_wifi_common_hal_negative1_wifi_initWithConfig...");
	WiFi_UnInitPosReq();
	UT_LOG("Invoking wifi_initWithConfig with NULL");

	result = wifi_initWithConfig(NULL);
    UT_LOG("Returned value was %d", result);
	WiFi_UnInitPosReq();	
	WiFi_InitPreReq();
    UT_ASSERT_EQUAL(result, RETURN_ERR);	
    UT_LOG("Exiting test_l1_wifi_common_hal_negative1_wifi_initWithConfig...");
}

/**
* @brief This test validates how gracefully negative scenario is handled in the wifi_initWithConfig which initializes WIFI
*
* This test is designed to validate the wifi_initWithConfig API. It simulates a negative test condition where incorrect configuration values are passed to the API. @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 006 @n
* **Priority:** High @n
* @n
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Initialize wifi_initWithConfig with incorrect configuration | conf = invalid pointer | RETURN_ERR | Should return error |
*/
void test_l1_wifi_common_hal_negative2_wifi_initWithConfig(void) {
    wifi_halConfig_t conf;
	int result;
    UT_LOG("Entering test_l1_wifi_common_hal_negative2_wifi_initWithConfig...");
    WiFi_UnInitPosReq();
	strcpy(conf.wlan_Interface,"WlAn1");
	UT_LOG("Invoking wifi_initWithConfig with invalid content");
	result = wifi_initWithConfig(&conf);
    UT_LOG("Returned value was %d", result);
	WiFi_UnInitPosReq();
	WiFi_InitPreReq();
    UT_ASSERT_EQUAL(result, RETURN_ERR);	
    UT_LOG("Exiting test_l1_wifi_common_hal_negative2_wifi_initWithConfig...");	
}

/**
* @brief This test aims to verify the effect of invoking the wifi_initWithConfig API with empty configuration.
*
* This unit test checks the response of the wifi_initWithConfig function when called with empty configuration. This is done to ensure that the function appropriately handles incorrect usage and returns the correct error status@n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 007 @n
* **Priority:** High @n
* @n
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_initWithConfig function with empty configuration | conf.wlan_Interface = " " |RETURN_ERR| Should return error |
*/
void test_l1_wifi_common_hal_negative3_wifi_initWithConfig(void) {
    wifi_halConfig_t conf;
	int result;
    UT_LOG("Entering test_l1_wifi_common_hal_negative3_wifi_initWithConfig...");
    WiFi_UnInitPosReq();
	strcpy(conf.wlan_Interface," ");
	UT_LOG("Invoking wifi_initWithConfig with invalid content");
	result = wifi_initWithConfig(&conf);
    UT_LOG("Returned value was %d", result);
	WiFi_UnInitPosReq();
	WiFi_InitPreReq();
    UT_ASSERT_EQUAL(result, RETURN_ERR);	
    UT_LOG("Exiting test_l1_wifi_common_hal_negative3_wifi_initWithConfig...");	
}

/**
* @brief This is a test function for wifi_down function which disables all WiFi interfaces
*
* This test case is to check if the wifi_down function correctly shuts down the Wi-Fi when it is already initiated with wifi_init or wifi_initWithConfig. @n
* 
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 009 @n
* **Priority:** High @n
* @n
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run this test in interactive mode, then the test case has to be selected via console.
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_down after wifi_init or wifi_initWithConfig | None| RETURN_OK | Should be successful |
*/
void test_l1_wifi_common_hal_positive1_wifi_down() {
    UT_LOG("Entering test_l1_wifi_common_hal_positive1_wifi_down..");
    INT return_val;	
    UT_LOG("Invoking wifi_down().");
    return_val = wifi_down();
    UT_LOG("Invoking wifi_down(). Return value: %d\n", return_val);
    UT_ASSERT_EQUAL(return_val, RETURN_OK);
    UT_LOG("Exiting test_l1_wifi_common_hal_positive1_wifi_down...\n");
}

/**
* @brief Tests the behavior of wifi_down() when wifi has not been initialized.
*
* This test case is designed to ensure that the wifi_down() API behaves as expected when invoked without initializing wifi. The expectation is that the API will return an error.@n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 011 @n
* **Priority:** High @n
* @n
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_down() without initializing wifi.| None| RETURN_ERR | Should return error|
*/
void test_l1_wifi_common_hal_negative1_wifi_down() {
    UT_LOG("Entering test_l1_wifi_common_hal_negative1_wifi_down...\n");
    INT return_val;
    UT_LOG("Invoking wifi_down() without initialization.");
    // Assuming wifi_init() or wifi_initWithConfig() has not been called before
	WiFi_UnInitPosReq();
    return_val = wifi_down();

    UT_LOG("Invoking wifi_down() without initialization. Return value: %d\n", return_val);
    WiFi_InitPreReq();
    UT_ASSERT_EQUAL(return_val, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative1_wifi_down...\n");
}

/**
* @brief Test for positive scenario of wifi_common_hal's wifi_uninit function.
*
* This test is designed to validate the successful uninitialization of wifi module via wifi_uninit function. We first initialize the wifi module using wifi_init and then uninitialize the same using wifi_uninit. @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 012 @n
* **Priority:** High @n
* @n
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Initialize the wifi module via wifi_init() | None | RETURN_OK | Should be successful |
* | 02 | Invoke wifi_uninit() after wifi_init() to uninitialize the wifi | None | RETURN_OK | Should be successful  |
*/
void test_l1_wifi_common_hal_positive1_wifi_uninit(void)
{
    UT_LOG("Entering test_l1_wifi_common_hal_positive1_wifi_uninit...");
    int ret ;
    UT_LOG("Invoking wifi_uninit() after wifi_init()");
    ret = wifi_uninit();
    UT_LOG("Invoking wifi_uninit() after wifi_init(), Expected return value is RETURN_OK, got: %d", ret);
	
    WiFi_InitPreReq();
	
	
    UT_ASSERT_EQUAL(ret, RETURN_OK);


    UT_LOG("Exiting test_l1_wifi_common_hal_positive1_wifi_uninit...");
}


/**
* @brief This function tests the wifi_uninit function immediately after invoking the wifi_initWithConfig function in a positive scenario.
*
* This unit test aims to ensure that the wifi_uninit function is working correctly when called immediately after the wifi_initWithConfig function. The primary objective here is to make sure that wifi_uninit destroys all resources that has been allocated by wifi_initWithConfig without causing any errors.@n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 013 @n
* **Priority:** High @n
* @n
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_initWithConfig() function with valid configuration | conf = valid pointer| RETURN_OK | Should be successful|
* | 02 | Invoke wifi_uninit() function after wifi_initWithConfig() | None | RETURN_OK | Should be successful |
*/
void test_l1_wifi_common_hal_positive2_wifi_uninit(void)
{
	wifi_halConfig_t conf;
	
    UT_LOG("Entering test_l1_wifi_common_hal_positive2_wifi_uninit...");
	int result;
    int ret;
    WiFi_UnInitPosReq();

	strcpy(conf.wlan_Interface,"wlan0");
	UT_LOG("Invoking wifi_initWithConfig with valid structure");
    result = wifi_initWithConfig(&conf);
    UT_LOG("Returned value was %d", result);
	
	
    UT_LOG("Invoking wifi_uninit() after wifi_initWithConfig()");
    ret = wifi_uninit();
    UT_LOG("Invoking wifi_uninit() after wifi_initWithConfig(), Expected return value is RETURN_OK, got: %d", ret);
    UT_ASSERT_EQUAL(ret, RETURN_OK);
	
	WiFi_InitPreReq();
	
    UT_LOG("Exiting test_l1_wifi_common_hal_positive2_wifi_uninit...");
}

/**
* @brief Testing of the wifi_uninit function without prior execution of wifi_init or wifi_initWithConfig.
*
* This test aims to verify the return value of wifi_uninit function when it is invoked without prior execution of wifi_init or wifi_initWithConfig functions. The function is expected to return "RETURN_ERR". @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 014 @n
* **Priority:** High @n
* @n
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke "wifi_uninit" without first calling either of wifi_init or wifi_initWithConfig | None | RETURN_ERR | Should return an error |
*/
void test_l1_wifi_common_hal_negative1_wifi_uninit(void)
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative1_wifi_uninit...");
    INT ret;	
	WiFi_UnInitPosReq();
	
    UT_LOG("Invoking wifi_uninit() without prior execution of wifi_init() or wifi_initWithConfig()");
    ret = wifi_uninit();
    UT_LOG("Invoking wifi_uninit() without prior execution of wifi_init() or wifi_initWithConfig(), Expected return value is RETURN_ERR, got: %d", ret);
	
	WiFi_InitPreReq();
	
    UT_ASSERT_EQUAL(ret, RETURN_ERR);
    UT_LOG("Exiting test_l1_wifi_common_hal_negative1_wifi_uninit...");
}

/**
* @brief Verifies the wifi_getStats API for expected results with valid inputs
*
* In this test case, wifi_getStats() API is invoked with valid radioIndex and valid wifi_sta_stats_t structure. The objective of the test case is to verify if the fetched wifi_sta_stats values are matching the expected values. This is essential for ensuring the correctness and functioning of the wifi_getStats API. @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 015 @n
* **Priority:** High @n
* @n
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. 
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_getStats() API with valid radioIndex and valid wifi_sta_stats_t structure| radioIndex = valid value, wifi_sta_stats = valid structure | Should return correct wifi_sta_stats values | Should be successful |
*/
void test_l1_wifi_common_hal_positive1_getStats(void) 
{
    UT_LOG("Entering test_l1_wifi_common_hal_positive1_getStats...\n");
    INT radioIndex = 1;

    wifi_sta_stats_t *wifi_sta_stats = (wifi_sta_stats_t*)malloc(sizeof(wifi_sta_stats_t));
    if(wifi_sta_stats != NULL)
    {
       UT_LOG("Invoking wifi_getStats with valid radioIndex=1 and valid &wifi_sta_stats buffer.\n");
       wifi_getStats(radioIndex, wifi_sta_stats); 

       UT_LOG("Station status data :  sta_SSID = %s, sta_BSSID = %s, sta_BAND = %s, sta_SecMode %s, sta_Encryption = %s, sta_PhyRate = %f, sta_Noise = %f, sta_RSSI = %f, sta_Frequency = %d, sta_LastDataDownlinkRate = %d, sta_LastDataUplinkRate =%d, sta_Retransmissions = %d",wifi_sta_stats->sta_SSID, wifi_sta_stats->sta_BSSID, wifi_sta_stats->sta_BAND, wifi_sta_stats->sta_SecMode, wifi_sta_stats->sta_Encryption, wifi_sta_stats->sta_PhyRate, wifi_sta_stats->sta_Noise, wifi_sta_stats->sta_RSSI, wifi_sta_stats->sta_Frequency, wifi_sta_stats->sta_LastDataDownlinkRate, wifi_sta_stats->sta_Retransmissions);
       if(!strcmp(wifi_sta_stats->sta_SSID,"") || !strcmp(wifi_sta_stats->sta_SSID,"valid_value"))   /*TODO need to replace with to valid value*/
        {
            UT_LOG("sta_SSID %s which is an valid value", wifi_sta_stats->sta_SSID);
            UT_PASS("sta_SSID validation success");
        }
        else
        {
            UT_LOG("sta_SSID %s which is a invalid value", wifi_sta_stats->sta_SSID);
            UT_FAIL("sta_SSID validation failed");
        }
        if(!strcmp(wifi_sta_stats->sta_BAND,"5GHz") || !strcmp(wifi_sta_stats->sta_BAND,"2.4GHz"))  
        {
            UT_LOG("sta_BAND %s which is an valid value", wifi_sta_stats->sta_BAND);
            UT_PASS("sta_BAND validation success");
        }
        else
        {
            UT_LOG("sta_BAND %s which is a invalid value", wifi_sta_stats->sta_BAND);
            UT_FAIL("sta_BAND validation failed");
        }
        if(!strcmp(wifi_sta_stats->sta_SecMode,"None") || !strcmp(wifi_sta_stats->sta_SecMode,"WEP")|| !strcmp(wifi_sta_stats->sta_SecMode,"WPA")|| !strcmp(wifi_sta_stats->sta_SecMode,"WPA2")|| !strcmp(wifi_sta_stats->sta_SecMode,"WPA3")|| !strcmp(wifi_sta_stats->sta_SecMode,"WPA-WPA2")|| !strcmp(wifi_sta_stats->sta_SecMode,"WPA2-WPA3")|| !strcmp(wifi_sta_stats->sta_SecMode,"WPA-Enterprise")|| !strcmp(wifi_sta_stats->sta_SecMode,"WPA2-Enterprise")|| !strcmp(wifi_sta_stats->sta_SecMode,"WPA-WPA2-Enterprise"))  
        {
            UT_LOG("sta_SecMode is %s which is an valid value", wifi_sta_stats->sta_SecMode);
            UT_PASS("sta_SecMode validation success");
        }
        else
        {
            UT_LOG("sta_SecMode is %s which is a invalid value", wifi_sta_stats->sta_SecMode);
            UT_FAIL("sta_SecMode validation failed");
        }
        if(!strcmp(wifi_sta_stats->sta_Encryption,"TKIP") || !strcmp(wifi_sta_stats->sta_Encryption,"AES"))  
        {
            UT_LOG("sta_Encryption is %s which is an valid value", wifi_sta_stats->sta_Encryption);
            UT_PASS("sta_Encryption validation success");
        }
        else
        {
            UT_LOG("sta_Encryption is %s which is a invalid value", wifi_sta_stats->sta_Encryption);
            UT_FAIL("sta_Encryption validation failed");
        }
        if (wifi_sta_stats->sta_PhyRate >= 0 && wifi_sta_stats->sta_PhyRate <= 2457.6)
        {
            UT_LOG("sta_PhyRate is %f which is a valid value", wifi_sta_stats->sta_PhyRate);
            UT_PASS("sta_PhyRate validation success");
        }
        else
        {
            UT_LOG("sta_PhyRate is %f which is an invalid value", wifi_sta_stats->sta_PhyRate);
            UT_FAIL("sta_PhyRate validation failed");
        }
        if (wifi_sta_stats->sta_Noise >= -200 && wifi_sta_stats->sta_Noise <= 0)
        {
            UT_LOG("sta_Noise is %f which is a valid value", wifi_sta_stats->sta_Noise);
            UT_PASS("sta_Noise validation success");
        }
        else
        {
            UT_LOG("sta_Noise is %f which is an invalid value", wifi_sta_stats->sta_Noise);
            UT_FAIL("sta_Noise validation failed");
        }
        if (wifi_sta_stats->sta_RSSI >= -200 && wifi_sta_stats->sta_RSSI <= 0)
        {
            UT_LOG("sta_RSSI is %f which is a valid value", wifi_sta_stats->sta_RSSI);
            UT_PASS("sta_RSSI validation success");
        }
        else
        {
            UT_LOG("sta_RSSI is %f which is an invalid value", wifi_sta_stats->sta_RSSI);
            UT_FAIL("sta_RSSI validation failed");
        }
        UINT valid_frequencies[] = {2412, 2417, 2422, 2427, 2432, 2437, 2442, 2447, 2452, 2457, 2462, 2467, 2472, 5160, 5180, 5200, 5220, 5240, 5260, 5280, 5300, 5320, 5340, 5480, 5500, 5520, 5540, 5560, 5580, 5600, 5620, 5640, 5660, 5680, 5700, 5720, 5745, 5765, 5785, 5805, 5825, 5845, 5865, 5885};
        for (int i = 0; i < sizeof(valid_frequencies) / sizeof(valid_frequencies[0]); i++) {
            if (wifi_sta_stats->sta_Frequency == valid_frequencies[i]) {
                UT_LOG("sta_Frequency %d which is a valid value", wifi_sta_stats->sta_Frequency);
                UT_PASS("sta_Frequency validation success");
            }
            else
            {
                UT_LOG("sta_Frequency is %d which is a invalid value", wifi_sta_stats->sta_Frequency);
                UT_FAIL("sta_Frequency of AP validation failed");
            }
        }
        if (wifi_sta_stats->sta_LastDataDownlinkRate >= 1000 && wifi_sta_stats->sta_LastDataDownlinkRate <= 600000)
        {
            UT_LOG("sta_LastDataDownlinkRate is %d which is a valid value", wifi_sta_stats->sta_LastDataDownlinkRate);
            UT_PASS("sta_LastDataDownlinkRate validation success");
        }
        else
        {
            UT_LOG("sta_LastDataDownlinkRate is %d which is an invalid value", wifi_sta_stats->sta_LastDataDownlinkRate);
            UT_FAIL("sta_LastDataDownlinkRate validation failed");
        }
        if (wifi_sta_stats->sta_LastDataUplinkRate >= 1000 && wifi_sta_stats->sta_LastDataUplinkRate <= 600000)
        {
            UT_LOG("sta_LastDataUplinkRate is %d which is a valid value", wifi_sta_stats->sta_LastDataUplinkRate);
            UT_PASS("sta_LastDataUplinkRate validation success");
        }
        else
        {
            UT_LOG("sta_LastDataUplinkRate is %d which is an invalid value", wifi_sta_stats->sta_LastDataUplinkRate);
            UT_FAIL("sta_LastDataUplinkRate validation failed");
        }
        if (wifi_sta_stats->sta_Retransmissions >= 0 && wifi_sta_stats->sta_Retransmissions <= 100)
        {
            UT_LOG("sta_Retransmissions is %d which is a valid value", wifi_sta_stats->sta_Retransmissions);
            UT_PASS("sta_Retransmissions validation success");
        }
        else
        {
            UT_LOG("sta_Retransmissions is %d which is an invalid value", wifi_sta_stats->sta_Retransmissions);
            UT_FAIL("sta_Retransmissions validation failed");
        }
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }
    		
    UT_LOG("Exiting test_l1_wifi_common_hal_positive1_getStats...\n");
}

/**
* @brief Testing wifi_getStats with invalid radioIndex.
*
* The objective of this test is to ensure that the wifi_getStats function handled invalid radioIndex correctly, without altering wifi_sta_stats. An invalid radioIndex is passed and the function behavior is analyzed. @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 016 @n
* **Priority:** High @n
* @n
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_getStats with invalid radioIndex and valid wifi_sta_stats pointers | radioIndex = invalid value, wifi_sta_stats = valid pointer | wifi_sta_stats remains unchanged | Should be successful |
*/
void test_l1_wifi_common_hal_negative1_getStats(void) {
    UT_LOG("Entering test_l1_wifi_common_hal_negative1_getStats...\n");
    INT radioIndex = 0; // Invalid
    wifi_sta_stats_t *wifi_sta_stats = (wifi_sta_stats_t*)malloc(sizeof(wifi_sta_stats_t));
    if(wifi_sta_stats != NULL)
    {
        UT_LOG("Invoking wifi_getStats with invalid radioIndex=0 and valid preallocated &wifi_sta_stats buffer.\n");
        wifi_getStats(radioIndex, wifi_sta_stats);
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }
    UT_LOG("Exiting test_l1_wifi_common_hal_negative1_getStats...\n");
}

/**
* @brief Tests the wifi_getStats function with invalid arguments
*
* This test aims to verify that the wifi_getStats function can handle invalid arguments gracefully. This is an important aspect of robustness in the API's error checking mechanism. @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 017 @n
* **Priority:** High @n
* @n
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
* @n
* **Test Procedure:**@n
* The following steps are performed in the test:
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking wifi_getStats function with valid radioIndex and NULL wifi_sta_stats pointer | radioIndex = valid value , wifi_sta_stats = NULL | Function should handle NULL gracefully | Should handle NULL arguments properly |
*/
void test_l1_wifi_common_hal_negative2_getStats(void) {
    UT_LOG("Entering test_l1_wifi_common_hal_negative2_getStats...\n");
    INT radioIndex = 1;	
	wifi_sta_stats_t *wifi_sta_stats = NULL;
    
    UT_LOG("Invoking wifi_getStats with valid radioIndex=1 and NULL &wifi_sta_stats buffer.\n");
    wifi_getStats(radioIndex, wifi_sta_stats); 
    
    UT_LOG("Exiting test_l1_wifi_common_hal_negative2_getStats...\n");
}

/**
* @brief Verifies the behavior of wifi_getStats when it has not been initialized previously.
*
* In this test, we are verifying that if we call wifi_getStats without having called wifi_init or wifi_initWithConfig, it does not alter the wifi_sta_stats information. @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 018 @n
* **Priority:** High @n
* @n
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_getStats without calling wifi_init or wifi_initWithConfig, with valid radioIndex and valid wifi_sta_stats pointer. | radioIndex = valid value, wifi_sta_stats = valid pointer| The call should not alter the wifi_sta_stats information | The information should remain at its uninitialized state |
*/
void test_l1_wifi_common_hal_negative3_getStats(void) {
    UT_LOG("Entering test_l1_wifi_common_hal_negative3_getStats...\n");
    INT radioIndex = 1;
    wifi_sta_stats_t *wifi_sta_stats = (wifi_sta_stats_t*)malloc(sizeof(wifi_sta_stats_t));
    if(wifi_sta_stats != NULL)
    {
		WiFi_UnInitPosReq();
        UT_LOG("Invoking wifi_getStats without calling wifi_init or wifi_initWithConfig");
        
        wifi_getStats(radioIndex, wifi_sta_stats);
		WiFi_InitPreReq();
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }
    
    UT_LOG("Exiting test_l1_wifi_common_hal_negative3_getStats...\n");
}

/**
* @brief This test case checks if the 'wifi_getRadioNumberOfEntries' function returns the correct number of Wi-Fi radio entries
*
* The test calls the radio initializing function and then invokes the function 'wifi_getRadioNumberOfEntries' to receive the number of Wi-Fi radio entries. The test then asserts whether the function returns the correct status code. @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 019 @n
* **Priority:** High @n
* @n
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Initialize the Wi-Fi radio | None | Wi-Fi radio initialized | Should be successful |
* | 02 | Invoke 'wifi_getRadioNumberOfEntries' function with valid output buffer | output = valid buffer| RETURN_OK | Should be successful |
*/
void test_l1_wifi_common_hal_positive1_wifi_getRadioNumberOfEntries( void )
{
    //Start Logging
    UT_LOG("Entering test_l1_wifi_common_hal_positive1_wifi_getRadioNumberOfEntries...");

    //Initialize variables
    ULONG output;
    INT ret;    
    //Invoke API
    UT_LOG("Invoking wifi_getRadioNumberOfEntries with valid output reference.");
    ret = wifi_getRadioNumberOfEntries(&output);
    if(output != 1)
	{
	UT_LOG("failed due to invalid RadioNumberOfEntries : %d",output);
    UT_FAIL("failed due to invalid RadioNumberOfEntries");
	}
    //Log after invocation
    UT_LOG("Returned value: %d", ret);

    //Check the return value
    UT_ASSERT_EQUAL(ret, RETURN_OK);

    //Stop Logging
    UT_LOG("Exiting test_l1_wifi_common_hal_positive1_wifi_getRadioNumberOfEntries...");
}

/**
* @brief This unit test checks for the robustness of wifi_getRadioNumberOfEntries API when invoked with invalid input parameters
*
* This test case validates the API's robustness against problematic inputs, and checks if it correctly returns an error value in the event of receiving NULL as outout reference @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 020 @n
* **Priority:** High @n
* @n
* **Pre-Conditions:** None @n 
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_getRadioNumberOfEntries API with NULL output buffer | output = NULL | RETURN_ERR | Should return error |
*/
void test_l1_wifi_common_hal_negative1_wifi_getRadioNumberOfEntries( void )
{
   //Start Logging
   UT_LOG("Entering test_l1_wifi_common_hal_negative1_wifi_getRadioNumberOfEntries...");
   INT ret;
   //Initialize variables
   ULONG *output = NULL;
      
   //Invoke API
   ret = wifi_getRadioNumberOfEntries(output);

   //Log after invocation
   UT_LOG("Invoking wifi_getRadioNumberOfEntries with NULL output reference. Returned value: %d", ret);

   //Check the return value
   UT_ASSERT_EQUAL(ret, RETURN_ERR);

   //Stop Logging
   UT_LOG("Exiting test_l1_wifi_common_hal_negative1_wifi_getRadioNumberOfEntries...");
}


/**
* @brief Test the 'wifi_getRadioNumberOfEntries' function when 'wifi_init' or 'wifi_initWithConfig' is not called.
*
* This unit test is designed to assert the return value of 'wifi_getRadioNumberOfEntries' function when neither 'wifi_init' nor 'wifi_initWithConfig' is invoked previously. It checks whether the function correctly returns 'RETURN_ERR' in such scenario. @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 021 @n
* **Priority:** High @n
* @n
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoke wifi_getRadioNumberOfEntries function without calling 'wifi_init' or 'wifi_initWithConfig' | output = valid buffer | RETURN_ERR| Should return error |
*/
void test_l1_wifi_common_hal_negative2_wifi_getRadioNumberOfEntries( void )
{
    //Start Logging
    UT_LOG("Entering test_l1_wifi_common_hal_negative2_wifi_getRadioNumberOfEntries...");
    INT ret;
    //Initialize variables
    ULONG output;
	
	WiFi_UnInitPosReq();
	
    UT_LOG("Invoking wifi_getRadioNumberOfEntries without calling wifi_init");    
    //Invoke API
    ret = wifi_getRadioNumberOfEntries(&output);

    //Log after invocation
    UT_LOG("Invoking wifi_getRadioNumberOfEntries without calling wifi_init or wifi_initWithConfig. Returned value: %d", ret);
	
    WiFi_InitPreReq();
    //Check the return value
    UT_ASSERT_EQUAL(ret, RETURN_ERR);

    //Stop Logging
    UT_LOG("Exiting test_l1_wifi_common_hal_negative2_wifi_getRadioNumberOfEntries...");
}


/**
* @brief Test for wifi_getSSIDNumberOfEntries function
*
* This test is conducted to verify if the wifi_getSSIDNumberOfEntries function behaves correctly. The function returns the number of SSID entries successfully. The return value is checked to ensure, it indicates successful completion of the operation. @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 022 @n
* **Priority:** High  @n
* @n
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.
* @n
* **Test Procedure:** @n
* | Variation / Step | Description  | Test Data  | Expected Result | Notes |
* | :----------: | ----------- | --------| ------- | ----------|
* | 01  | Invoke the wifi_getSSIDNumberOfEntries function with valid ssidNumber buffer | ssidNumber = valid buffer | RETURN_OK  | Should be successful |
*/
void test_l1_wifi_common_hal_positive1_wifi_getSSIDNumberOfEntries(void)
{
    UT_LOG("Entering test_l1_wifi_common_hal_positive1_wifi_getSSIDNumberOfEntries...\n");
    ULONG ssidNumber;
    INT result;		
    UT_LOG("Invoking wifi_getSSIDNumberOfEntries with a valid pointer.");
    result = wifi_getSSIDNumberOfEntries(&ssidNumber);
    UT_LOG(" SSID Number: %lu, Return status: %d\n", ssidNumber, result);
    UT_ASSERT_EQUAL(result, RETURN_OK);
	if(ssidNumber != 1)
	{
	UT_LOG("failed due to invalid number of ssid : %d",ssidNumber);
    UT_FAIL("failed due to invalid number of ssid");
	}
    UT_LOG("Exiting test_l1_wifi_common_hal_positive1_wifi_getSSIDNumberOfEntries...\n");
}

/**
* @brief This test case checks the error response when wifi_getSSIDNumberOfEntries API is invoked without initializing the Wi-Fi subsystem.
*
* The function wifi_getSSIDNumberOfEntries is an API that provides the number of SSID entries. This is a negative test case where the intention is to test the response of the API when it is invoked without the Wi-Fi subsystem being initialized. @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 023 @n
* **Priority:** High @n
* @n
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_getSSIDNumberOfEntries without initializing the wifi subsystem | ssidNumber = valid buffer | RETURN_ERR | Should return error |
*/
void test_l1_wifi_common_hal_negative1_wifi_getSSIDNumberOfEntries(void)
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative1_wifi_getSSIDNumberOfEntries...\n");
    ULONG ssidNumber;
    INT result;
	WiFi_UnInitPosReq();
	
    UT_LOG("Invoking wifi_getSSIDNumberOfEntries without initializing the Wi-Fi subsystem.");
    result = wifi_getSSIDNumberOfEntries(&ssidNumber);
    UT_LOG("Invoking wifi_getSSIDNumberOfEntries  Return status: %d\n", result);
    WiFi_InitPreReq();
    UT_ASSERT_EQUAL(result, RETURN_ERR);
    UT_LOG("Exiting test_l1_wifi_common_hal_negative1_wifi_getSSIDNumberOfEntries...\n");
}

/**
* @brief Test the behavior of wifi_getSSIDNumberOfEntries() if NULL pointer is passed as parameter
*
* This test validates the scenario where the wifi_getSSIDNumberOfEntries() API is invoked with NULL pointer @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 024 @n
* **Priority:** High @n
* @n
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
* @n
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_getSSIDNumberOfEntries() with a NULL argument | output = NULL | RETURN_ERR | Should return error |
*/
void test_l1_wifi_common_hal_negative2_wifi_getSSIDNumberOfEntries(void)
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative2_wifi_getSSIDNumberOfEntries...\n");
    INT result;	
    UT_LOG("Invoking wifi_getSSIDNumberOfEntries with a NULL pointer.");
    result = wifi_getSSIDNumberOfEntries(NULL);
    UT_LOG("Return status: %d\n", result);

    UT_ASSERT_EQUAL(result, RETURN_ERR);
    UT_LOG("Exiting test_l1_wifi_common_hal_negative2_wifi_getSSIDNumberOfEntries...\n");
}

/**
* @brief This test case tests the wifi_getRadioEnable function from the WiFi Common HAL
*
* In this test, the wifi_getRadioEnable function of WiFi Common HAL is tested to ensure that the function is functioning as expected and returning the desired results. @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 025 @n
* **Priority:** High @n
* @n
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_getRadioEnable with valid radioIndex | radioIndex = valid value | RETURN_OK | Should be successful |
*/
void test_l1_wifi_common_hal_positive1_wifi_getRadioEnable( void ) 
{
    UT_LOG("Entering test_l1_wifi_common_hal_positive1_wifi_getRadioEnable...");
    BOOL output_bool;
    INT ret;
	INT radioIndex = 1;
		
    UT_LOG("Invoking wifi_getRadioEnable with index 1.");	
    ret = wifi_getRadioEnable(radioIndex, &output_bool);

    UT_LOG("Invoking wifi_getRadioEnable with index 1. Returned: %d, Output: %d", ret, output_bool);
    UT_ASSERT_EQUAL(ret, RETURN_OK);
    if((output_bool != '0') && (output_bool != '1'))
	{
	UT_LOG("failed due to invalid Radio Enable value: %c",output_bool);
    UT_FAIL("failed due to invalid Radio Enable value");
	}
    UT_LOG("Exiting test_l1_wifi_common_hal_positive1_wifi_getRadioEnable...");
}

/**
* @brief This test verifies the wifi_getRadioEnable function in the wifi common module
*
* The test function invokes the wifi_getRadioEnable function and checks if it returns the correct status and output. It is essential to ensure the functionality of the Wi-Fi common module operates as expected. @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 026 @n
* **Priority:** High @n
* @n
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_getRadioEnable function with valid radioindex and valid output_bool buffer | index = valid value, output_bool = valid buffer | RETURN_OK| Should be successful |
*/
void test_l1_wifi_common_hal_positive2_wifi_getRadioEnable( void ) 
{
    UT_LOG("Entering test_l1_wifi_common_hal_positive2_wifi_getRadioEnable...");
    BOOL output_bool = 0;
	INT radioIndex = 1;
    INT ret;	
    UT_LOG("Invoking wifi_getRadioEnable with index 1.  output_bool =0");
    ret = wifi_getRadioEnable(radioIndex, &output_bool);

    UT_LOG("Invoking wifi_getRadioEnable with index 1. Returned: %d, Output: %d", ret, output_bool);
    UT_ASSERT_EQUAL(ret, RETURN_OK);
    if((output_bool != '0') && (output_bool != '1'))
	{
	UT_LOG("failed due to invalid Radio Enable value : %c",output_bool);
    UT_FAIL("failed due to invalid Radio Enable value");
	}

    UT_LOG("Exiting test_l1_wifi_common_hal_positive2_wifi_getRadioEnable...");
}

/**
* @brief This test case tests the wifi_getRadioEnable API for a positive scenario.
*
* The objective of this unit test is to verify whether the wifi_getRadioEnable API returns the correct radio state for any given index. @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 027 @n
* **Priority:** High @n
* @n
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_getRadioEnable with index 1 and a TRUE output placeholder  | index = 1, output_bool = 1 | API should return RETURN_OK and the output_bool should also return 1 | Should be successful |
*/
void test_l1_wifi_common_hal_positive3_wifi_getRadioEnable( void ) 
{
    UT_LOG("Entering test_l1_wifi_common_hal_positive3_wifi_getRadioEnable...");
    BOOL output_bool = 1;
	INT radioIndex = 1;
    INT ret;
    UT_LOG("Invoking wifi_getRadioEnable with index 1.  output_bool =1");
    ret = wifi_getRadioEnable(radioIndex, &output_bool);

    UT_LOG("Invoking wifi_getRadioEnable with index 1. Returned: %d, Output: %d", ret, output_bool);
    UT_ASSERT_EQUAL(ret, RETURN_OK);
    if((output_bool != '0') && (output_bool != '1'))
	{
	UT_LOG("failed due to invalid Radio Enable value : %c",output_bool);
    UT_FAIL("failed due to invalid Radio Enable value");
	}

    UT_LOG("Exiting test_l1_wifi_common_hal_positive3_wifi_getRadioEnable...");
}

/**
* @brief This test validates the error handling of the wifi_getRadioEnable function
*
* This function tests the wifi_getRadioEnable API function by providing invalid index which is out of range, and checks whether the function can handle it and return the expected error. @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 028 @n
* **Priority:** High @n
* @n
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_getRadioEnable with invalid radioindex | radioindex = invalid value |RETURN_ERR| Should return error |
*/
void test_l1_wifi_common_hal_negative1_wifi_getRadioEnable( void ) 
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative1_wifi_getRadioEnable...");
    BOOL output_bool;
	INT radioIndex = 2;
    INT ret;	
    UT_LOG("Invoking wifi_getRadioEnable with invalid index 2.");	
    ret = wifi_getRadioEnable(radioIndex, &output_bool);

    UT_LOG("Invoking wifi_getRadioEnable with invalid index 2. Returned: %d", ret);
    UT_ASSERT_EQUAL(ret, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative1_wifi_getRadioEnable...");
}

/**
* @brief This is a unit test for the wifi_getRadioEnable() API in negative scenario.
*
* This test is designed to validate if the wifi_getRadioEnable() API handles NULL output_bool properly. The test case is necessary for ensuring that the API has proper error handling procedures in place. @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 029 @n
* **Priority:** High @n
* @n
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
* @n
* **Test Procedure:**@n
* | Variation / Step | Description  | Test Data | Expected Result | Notes |
* | :----: | --------- | ----------|-----------| ----- |
* | 01 | Call wifi_getRadioEnable with NULL output_bool and valid radioIndex| output_bool = NULL, radioIndex = valid value | RETURN_ERR | Should return error |
*/
void test_l1_wifi_common_hal_negative2_wifi_getRadioEnable( void ) 
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative2_wifi_getRadioEnable...");
    BOOL *output_bool = NULL;
	INT radioIndex = 1;	
    INT ret;	
    UT_LOG("Invoking wifi_getRadioEnable with NULL output_bool.");	
    ret = wifi_getRadioEnable(radioIndex, output_bool);

    UT_LOG("Invoking wifi_getRadioEnable with NULL output_bool. Returned: %d", ret);
    UT_ASSERT_EQUAL(ret, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative2_wifi_getRadioEnable...");
}

/**
* @brief Test to verify the "wifi_getRadioEnable" function can handle negative inputs
*
* This test case verifies that the wifi_getRadioEnable function can handle negative inputs, which are considered invalid, by returning an error code. @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 030 @n
* **Priority:** High @n
* @n
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. 
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data | Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke "wifi_getRadioEnable" with a negative radioIndex | radioIndex = negative value, output_bool = valid buffer |RETURN_ERR | Should return error |
*/
void test_l1_wifi_common_hal_negative3_wifi_getRadioEnable( void ) 
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative3_wifi_getRadioEnable...");
    BOOL output_bool;
	INT radioIndex = -1;
    INT ret;	
    UT_LOG("Invoking wifi_getRadioEnable with negative index -1.");	
    ret = wifi_getRadioEnable(radioIndex, &output_bool);

    UT_LOG("Invoking wifi_getRadioEnable with negative index -1. Returned: %d", ret);
    UT_ASSERT_EQUAL(ret, RETURN_ERR)

    UT_LOG("Exiting test_l1_wifi_common_hal_negative3_wifi_getRadioEnable...");
}

/**
* @brief Test to verify the "wifi_getRadioEnable" function before invoking wifi_init() or wifi_initWithConfig().
*
* This test case verifies that the wifi_getRadioEnable function can return RETURN_ERR, when invoking before wifi_init() or wifi_initWithConfig() @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 030 @n
* **Priority:** High @n
* @n
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. 
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data | Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_getRadioEnable before invoking wifi_init() or wifi_initWithConfig(). | radioIndex = valid value, output_bool = valid buffer| RETURN_ERR | Should return error |
*/
void test_l1_wifi_common_hal_negative4_wifi_getRadioEnable( void ) 
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative4_wifi_getRadioEnable...");
    INT ret;
    BOOL output_bool;
	INT radioIndex = 1;	
	WiFi_UnInitPosReq();
	
    UT_LOG("Invoking wifi_getRadioEnable before  wifi_init() or wifi_initWithConfig().");	
    ret = wifi_getRadioEnable(radioIndex, &output_bool);
    
    UT_LOG("Invoking wifi_getRadioEnable with index 1. Returned: %d, Output: %d", ret, output_bool);
	
	WiFi_InitPreReq();
    UT_ASSERT_EQUAL(ret, RETURN_ERR)

    UT_LOG("Exiting test_l1_wifi_common_hal_negative4_wifi_getRadioEnable...");
}

/**
* @brief Test for function wifi_getRadioStatus
*
* This test checks if the function wifi_getRadioStatus works as expected by validating the output string and the return value when passed with a valid radio index @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 031 @n
* **Priority:** High @n
* @n
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_getRadioStatus with valid radioIndex and valid output_string | radioIndex = valid value, output_string = valid buffer | RETURN_OK | Should be successful |
*/
void test_l1_wifi_common_hal_positive1_wifi_getRadioStatus(void){
    UT_LOG("Entering test_l1_wifi_common_hal_positive1_wifi_getRadioStatus...");

    INT radioIndex = 1;
    CHAR output_string[20];
    INT return_value;
	
    UT_LOG("Invoking wifi_getRadioStatus with valid radio index. ");
    return_value = wifi_getRadioStatus(radioIndex, output_string);

    UT_LOG("Invoking wifi_getRadioStatus with valid radio index. output_string obtained: %s, return value: %d", output_string, return_value);

    UT_ASSERT_EQUAL(return_value, RETURN_OK);

    if(check_value(output_string,radiostatus,6) != 1)
	{
	UT_LOG("failed due to invalid output_string : %s",output_string);
    UT_FAIL("failed due to invalid output_string");	
	}
    UT_LOG("Exiting test_l1_wifi_common_hal_positive1_wifi_getRadioStatus...");
}


/**
* @brief Testing the behavior of wifi_getRadioStatus for unitialized wifi
*
* This test is designed to evaluate the scenario where wifi_getRadioStatus API is invoked without initializing the wifi. This is crucial to ensure that the API responds appropriately when invoked under incorrect configuration. @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 032 @n
* **Priority:** High @n
* @n
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_getRadioStatus API without initializing the wifi | radioIndex = valid value, output_string = valid buffer | RETURN_ERR |Should return error |
*/
void test_l1_wifi_common_hal_negative1_wifi_getRadioStatus(void)
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative1_wifi_getRadioStatus...");
    INT return_value;
    INT radioIndex = 1;
    CHAR output_string[20];
    // Call the API without initializing the wifi

    WiFi_UnInitPosReq();	
    UT_LOG("Invoking wifi_getRadioStatus without wifi initialization.");
    return_value = wifi_getRadioStatus(radioIndex, output_string);

    UT_LOG("return status: %d", return_value);
    WiFi_InitPreReq();
    UT_ASSERT_EQUAL(return_value, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative1_wifi_getRadioStatus...");
}


/**
* @brief This function tests the wifi_getRadioStatus function against invalid radio index
*
* It tests if the wifi_getRadioStatus function handles negative scenarios correctly, particularly when it is provided with invalid input values. @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 033 @n
* **Priority:** High @n
* @n
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | ---------  | ---------- |-------------- | -----  |
* | 01  | Invoke wifi_getRadioStatus with an invalid radio index | radioIndex = invalid value |  RETURN_ERR | Should return error |
*/
void test_l1_wifi_common_hal_negative2_wifi_getRadioStatus(void)
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative2_wifi_getRadioStatus...");
    INT return_value;
    INT radioIndex = 2; // invalid radio index
    CHAR output_string[20];
			
    UT_LOG("Invoking wifi_getRadioStatus with invalid radio index.");	
    return_value = wifi_getRadioStatus(radioIndex, output_string);

    UT_LOG("Invoking wifi_getRadioStatus with invalid radio index. return value: %d", return_value);

    UT_ASSERT_EQUAL(return_value, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative2_wifi_getRadioStatus...");
}

/**
* @brief This test will validate the wifi_getRadioStatus API for NULL output_string
*
* This test is intended to validate the negative scenario of the wifi_getRadioStatus API. In this test, the wifi_getRadioStatus API is called with a NULL output_string. The API is expected to handle the NULL parameter and return an error code. @n
* 
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 034 @n
* **Priority:** High @n
* @n
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_getRadioStatus with NULL output_string and valid radio Index| radioIndex = valid value, output_string = NULL |RETURN_ERR | Should return error |
*/
void test_l1_wifi_common_hal_negative3_wifi_getRadioStatus(void)
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative3_wifi_getRadioStatus...");

    INT radioIndex = 1;
    CHAR *output_string = NULL; 
    INT return_value;
	
    UT_LOG("Invoking wifi_getRadioStatus with output_string as NULL");
    return_value = wifi_getRadioStatus(radioIndex, output_string);

    UT_LOG("Invoking wifi_getRadioStatus with output_string as NULL. return value: %d", return_value);

    UT_ASSERT_EQUAL(return_value, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative3_wifi_getRadioStatus...");
}


/**
* @brief Tests the API wifi_getRadioIfName for positive test case  with valid radio index and valid Interface buffer
*
* This function is designed to test whether the function wifi_getRadioIfName behaves as expected when called with valid parameters. The test verifies the correctness of the function by invoking it with an index for an existing radio and a valid CHAR pointer for output. @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 035 @n
* **Priority:** High @n
* @n
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking wifi_getRadioIfName with valid radio index and valid output_string buffer.| radio index = valid value, output_string = valid buffer | RETURN_OK | Should be successful |
*/
void test_l1_wifi_common_hal_positive1_wifi_getRadioIfName() {
    UT_LOG("Entering test_l1_wifi_common_hal_positive1_wifi_getRadioIfName...");
    CHAR output_string[MAX_OUTPUT_STRING_LEN];
    INT status;
    INT radioIndex = 1;	
    UT_LOG("Invoking wifi_getRadioIfName with valid radio index and valid CHAR pointer.");	
    status = wifi_getRadioIfName(radioIndex, output_string);
    UT_LOG(" The function status returned: %d, output string: %s", status, output_string);
    UT_ASSERT_EQUAL(status, RETURN_OK);
    UT_LOG("Exiting test_l1_wifi_common_hal_positive1_wifi_getRadioIfName...");
}

/**
* @brief To test the function wifi_getRadioIfName when run without calling either wifi_init or wifi_initWithConfig.
*
* The purpose of this unit test is to verify whether the function wifi_getRadioIfName returns an error when called without any prior calls to wifi_init or wifi_initWithConfig . @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 037 @n
* **Priority:** High @n
* @n
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_getRadioIfName without calling either wifi_init or wifi_initWithConfig | radioIndex = valid value, output_string = valid buffer| RETURN_ERR | Should return error |
*/
void test_l1_wifi_common_hal_negative1_wifi_getRadioIfName() {
    UT_LOG("Entering test_l1_wifi_common_hal_negative1_wifi_getRadioIfName...");
    CHAR output_string[MAX_OUTPUT_STRING_LEN];
    INT radioIndex = 1;	
	WiFi_UnInitPosReq();
    UT_LOG("Invoking wifi_getRadioIfName without calling either wifi_init or wifi_initWithConfig.");
    INT status = wifi_getRadioIfName(radioIndex, output_string);
    UT_LOG(" The function status returned: %d", status);
	WiFi_InitPreReq();
    UT_ASSERT_EQUAL(status, RETURN_ERR);
    UT_LOG("Exiting test_l1_wifi_common_hal_negative1_wifi_getRadioIfName...");
}

/**
* @brief Test for invalid radio index in "wifi_getRadioIfName" function
*
* This test verifies the behavior of the function "wifi_getRadioIfName" when invoked with an invalid radio index. The function should return an error code. @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 038 @n
* **Priority:** High @n
* @n
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data | Expected Result |Notes |
* | :----:  | ---------| ----------  |-------------- | -----|
* | 01 | Invoke wifi_getRadioIfName with invalid radio index. | radio index = invalid value, output_string = "" | RETURN_ERR| Should return error |
*/
void test_l1_wifi_common_hal_negative2_wifi_getRadioIfName() {
    UT_LOG("Entering test_l1_wifi_common_hal_negative2_wifi_getRadioIfName...");
    CHAR output_string[MAX_OUTPUT_STRING_LEN];
    INT radioIndex = 0;	
    INT status;	
    UT_LOG("Invoking wifi_getRadioIfName with invalid radio index.");	
    status = wifi_getRadioIfName(radioIndex, output_string);
    UT_LOG("The function status returned: %d", status);
    UT_ASSERT_EQUAL(status, RETURN_ERR);
    UT_LOG("Exiting test_l1_wifi_common_hal_negative2_wifi_getRadioIfName...");
}


/**
* @brief Test case to evaluate if wifi_getRadioIfName API handles invalid radio index correctly
*
* This test checks if the function wifi_getRadioIfName is robust enough to handle incorrect inputs. Specifically, it verifies that the function returns an error when invoked with invalid radio index. @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 039 @n
* **Priority:** High @n
* @n
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data|Expected Result |Notes| 
* | :----: | --------- | --------- |---------| --------- |
* | 01| Invoke wifi_getRadioIfName with invalid radio index | radio index = invalid value, output_string = valid buffer | RETURN_ERR | Should return error |
*/
void test_l1_wifi_common_hal_negative3_wifi_getRadioIfName() {
    UT_LOG("Entering test_l1_wifi_common_hal_negative3_wifi_getRadioIfName...");
    CHAR output_string[MAX_OUTPUT_STRING_LEN];
    INT radioIndex = 2;
    INT status;	
    UT_LOG("Invoking wifi_getRadioIfName with invalid radio index.");	
    status = wifi_getRadioIfName(radioIndex, output_string);
    UT_LOG("The function status returned: %d", status);
    UT_ASSERT_EQUAL(status, RETURN_ERR);
    UT_LOG("Exiting test_l1_wifi_common_hal_negative3_wifi_getRadioIfName...");
}


/**
* @brief This test is designed to test the negative scenario for the function wifi_getRadioIfName() in wifi common HAL.
*
* In this test, wifi_getRadioIfName is called with a valid radio index and NULL interface after calling wifi_init(). The expected behavior of the function is to handle this incorrect usage and return an error. @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 040 @n
* **Priority:** High @n
* @n
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_getRadioIfName with valid radio index and NULL interface after calling wifi_init() | radio index = valid value, output_string = NULL | RETURN_ERR |Should return an error |
*/
void test_l1_wifi_common_hal_negative4_wifi_getRadioIfName() {
    UT_LOG("Entering test_l1_wifi_common_hal_negative4_wifi_getRadioIfName...");
    INT radioIndex = 1;	
    INT status;	
    UT_LOG("Invoking wifi_getRadioIfName with valid radio index and NULL CHAR pointer.");	
    status = wifi_getRadioIfName(radioIndex, NULL);
    UT_LOG("Invoking wifi_getRadioIfName with valid radio index and NULL CHAR pointer. The function status returned: %d", status);
    UT_ASSERT_EQUAL(status, RETURN_ERR);
    UT_LOG("Exiting test_l1_wifi_common_hal_negative4_wifi_getRadioIfName...");
}


/**
* @brief Validates the failure scenario of the wifi_getRadioIfName API when provided with NULL interface.
*
* This test cases is designed to validate the failure case of the wifi_getRadioIfName function, where wifi_getRadioIfName is called after wifi_initWithConfig with valid radio index and NULL interface. @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 041 @n
* **Priority:** High @n
* @n
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke the wifi_getRadioIfName after wifi_initWithConfig with valid radioIndex, NULL interface | radioIndex = valid value, output_string = NULL | RETURN_ERR | Should return error |
*/
void test_l1_wifi_common_hal_negative5_wifi_getRadioIfName() {
    
    UT_LOG("Entering test_l1_wifi_common_hal_negative5_wifi_getRadioIfName...");
    INT radioIndex = 1; 
    CHAR *output_string = NULL;
    INT status;
    WiFi_UnInitPosReq();
	WiFi_InitWithConfigPreReq();
		
    UT_LOG("Invoking wifi_getRadioIfName after wifi_initWithConfig with valid radio index and NULL CHAR pointer.");	
    status = wifi_getRadioIfName(radioIndex, output_string);
    UT_LOG("Invoking wifi_getRadioIfName after wifi_initWithConfig with valid radio index and NULL CHAR pointer. The function status returned: %d", status);
    WiFi_UnInitPosReq();
    WiFi_InitPreReq();	
    UT_ASSERT_EQUAL(status, RETURN_ERR);
    UT_LOG("Exiting test_l1_wifi_common_hal_negative5_wifi_getRadioIfName...");
}

/**
* @brief This test checks if the function wifi_getRadioMaxBitRate returns the correct output.
*
* This function tests the wifi_getRadioMaxBitRate API from our wifi common HAL to ensure that it returns the correct maximum bitrate when provided with a valid radioIndex. @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 042 @n
* **Priority:** High @n
* @n
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_getRadioMaxBitRate with valid radioIndex and valid output_string buffer | radioIndex = valid value, output_string = valid buffer |RETURN_OK | Should be successful |
*/
void test_l1_wifi_common_hal_positive1_wifi_getRadioMaxBitRate(void)
    {
        UT_LOG("Entering test_l1_wifi_common_hal_positive1_wifi_getRadioMaxBitRate...");
        CHAR outputVal[50]; // Size can be adjusted if necessary
        INT bitrate;
        INT status;
        INT radioIndex = 1;
        UT_LOG("Invoking wifi_getRadioMaxBitRate with valid radioIndex 1.");
        status = wifi_getRadioMaxBitRate(radioIndex, outputVal);
        UT_LOG("The returned bit rate is %s, and the return status is %d", outputVal, status);
        UT_ASSERT_EQUAL(status, RETURN_OK);
		bitrate = atoi(outputVal);
		if((bitrate < 0) || (bitrate > 2458) ) 
		{
    	    UT_LOG("failed due to invalid output_string : %s",outputVal);
            UT_FAIL("failed due to invalid output_string");
		}

        UT_LOG("Exiting test_l1_wifi_common_hal_positive1_wifi_getRadioMaxBitRate...");
    }

/**
* @brief This test ensures that the wifi_getRadioMaxBitRate function works properly when invoked with invalid radio index.
*
* This unit tests verifies whether the wifi_getRadioMaxBitRate function returns the proper status code in response to invalid radio index. This situation might occur due to incorrect user input or internal issues. @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 043 @n
* **Priority:** High @n
* @n
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_getRadioMaxBitRate function with invalid radioIndex and valid output_string buffer| radioIndex = invalid value, output_string = valid buffer | RETURN_ERR | Should return error |
*/
void test_l1_wifi_common_hal_negative1_wifi_getRadioMaxBitRate(void)
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative1_wifi_getRadioMaxBitRate...");
    CHAR outputVal[50];  // Size can be adjusted if necessary
    INT radioIndex = 2;	
    INT status;	
    UT_LOG("Invoking wifi_getRadioMaxBitRate with invalid radioIndex 2");
    status = wifi_getRadioMaxBitRate(radioIndex, outputVal);
    UT_LOG("The return status is %d", status);
    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative1_wifi_getRadioMaxBitRate...");
}

/**
* @brief This test checks if wifi_getRadioMaxBitRate function returns an error when preconditions are not met
*
* This test aims to verify the behaviour of the wifi_getRadioMaxBitRate function when it is called without previously calling wifi_init function, the precondition for wifi_getRadioMaxBitRate. @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 044 @n
* **Priority:** High @n
* @n
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_getRadioMaxBitRate without calling wifi_init | radioIndex = valid value, outputVal = valid buffer | RETURN_ERR | Should return error |
*/
void test_l1_wifi_common_hal_negative2_wifi_getRadioMaxBitRate(void)
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative2_wifi_getRadioMaxBitRate...");
    CHAR outputVal[50];  // Size can be adjusted if necessary
    INT radioIndex = 1;
    INT status;
    WiFi_UnInitPosReq();
    UT_LOG("Invoking wifi_getRadioMaxBitRate without meeting the precondition of calling wifi_init().");    
    // precondition not met, but it's hard to simulate this in unit test without invoking wifi_init() intentionally
    status = wifi_getRadioMaxBitRate(radioIndex, outputVal);
    
    UT_LOG("The return status is %d", status);
	WiFi_InitPreReq();
    UT_ASSERT_EQUAL(status, RETURN_ERR);
    
    UT_LOG("Exiting test_l1_wifi_common_hal_negative2_wifi_getRadioMaxBitRate...");
}

/**
* @brief Test the function wifi_getRadioMaxBitRate for error condition
*
* This test case checks if wifi_getRadioMaxBitRate function handles NULL output string correctly. @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 045 @n
* **Priority:** High @n
* @n
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_getRadioMaxBitRate with valid radioIndex and NULL output_string | radioIndex = valid value , output_string = NULL | RETURN_ERR | Should return error |
*/
void test_l1_wifi_common_hal_negative3_wifi_getRadioMaxBitRate(void)
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative3_wifi_getRadioMaxBitRate...");
    INT radioIndex = 1;
    INT status;
    UT_LOG("Invoking wifi_getRadioMaxBitRate with NULL output_string.");
    status = wifi_getRadioMaxBitRate(radioIndex, NULL);    
    UT_LOG("Invoking wifi_getRadioMaxBitRate with NULL output_string. The return status is %d", status);
    UT_ASSERT_EQUAL(status, RETURN_ERR);
    
    UT_LOG("Exiting test_l1_wifi_common_hal_negative3_wifi_getRadioMaxBitRate...");
}

/**
* @brief Test for getting radio supported frequency bands
*
* This test case checks whether the function 'wifi_getRadioSupportedFrequencyBands' works properly when invoked with valid arguments. @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 046 @n
* **Priority:** High @n
* @n
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ----------  |-------------- | ----- |
* | 01 | Invoke "wifi_getRadioSupportedFrequencyBands" with valid radioIndex and valid output_string buffer | radioIndex = valid value, output_string = valid buffer| RETURN_OK | Should be successful |
*/
void test_l1_wifi_common_hal_positive1_wifi_getRadioSupportedFrequencyBands(void)
{
    UT_LOG("Entering test_l1_wifi_common_hal_positive1_wifi_getRadioSupportedFrequencyBands...");

    INT radioIndex = 1;
    CHAR output_string[12];
    INT return_status;
			
    UT_LOG("Invoking wifi_getRadioSupportedFrequencyBands with valid radioIndex and output_string buffer.");
    return_status = wifi_getRadioSupportedFrequencyBands(radioIndex, output_string);
    UT_LOG("Return Status: %d", return_status);

    UT_ASSERT_EQUAL(return_status, RETURN_OK);
    if((strcmp("output_string","2.4Ghz,5Ghz") != 0) && (strcmp("output_string","2.4Ghz") != 0) && (strcmp("output_string","5Ghz") != 0))
	{
	    UT_LOG("failed due to invalid output_string : %s",output_string);
        UT_FAIL("failed due to invalid output_string");
	}
    UT_LOG("Exiting test_l1_wifi_common_hal_positive1_wifi_getRadioSupportedFrequencyBands...");
}

/**
* @brief This test verifies if the wifi_getRadioSupportedFrequencyBands API handles an NULL output buffer.
*
* This test aims to verify the wifi_getRadioSupportedFrequencyBands API with NULL argument. It check how the API handles an erroneous call with NULL buffer. This is a negative testing scenario which intends to ensure robustness of API in unexpected situations. @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 047 @n
* **Priority:** High @n
* @n
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.
* @n
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data  | Expected Result | Notes  |
* | :----:  | ---------  | ---------- |-------------- | -----|
* | 01 | Invoke wifi_getRadioSupportedFrequencyBands API with valid radioIndex and NULL output_string |radioIndex = valid value, output_string = NULL |RETURN_ERR |Should return error |
*/
void test_l1_wifi_common_hal_negative1_wifi_getRadioSupportedFrequencyBands(void)
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative1_wifi_getRadioSupportedFrequencyBands...");

    INT radioIndex = 1;
    CHAR *output_string = NULL;
    INT return_status;
	
    UT_LOG("Invoking wifi_getRadioSupportedFrequencyBands with uninitialized output_string buffer.");
    return_status = wifi_getRadioSupportedFrequencyBands(radioIndex, output_string);
    UT_LOG("Return Status: %d", return_status);

    UT_ASSERT_EQUAL(return_status, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative1_wifi_getRadioSupportedFrequencyBands...");
}

/**
* @brief Tests the function "wifi_getRadioSupportedFrequencyBands" for negative scenarios
*
* This test checks the robustness of the "wifi_getRadioSupportedFrequencyBands" function when an invalid radio index is passed. The API should return an error when invoked with invalid arguments @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 048 @n
* **Priority:** High @n
* @n
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_getRadioSupportedFrequencyBands with an invalid radioIndex value | radioIndex = invalid value, output_string = valid buffer  | RETURN_ERR| Should return error |
*/
void test_l1_wifi_common_hal_negative2_wifi_getRadioSupportedFrequencyBands(void)
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative2_wifi_getRadioSupportedFrequencyBands...");

    CHAR output_string[12];
    INT return_status;
    INT radioIndex = 0;
		
    UT_LOG("Invoking wifi_getRadioSupportedFrequencyBands with invalid radioIndex.");
    return_status = wifi_getRadioSupportedFrequencyBands(radioIndex, output_string);
    UT_LOG("Return Status: %d", return_status);

    UT_ASSERT_EQUAL(return_status, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative2_wifi_getRadioSupportedFrequencyBands...");
}


/**
* @brief Unit test to verify the function wifi_getRadioSupportedFrequencyBands
*
* This test is designed to test the API wifi_getRadioSupportedFrequencyBands when wifi_init() and wifi_initWithConfig() functions are not called. It asserts the return status against the expected error status. @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 049 @n
* **Priority:** High @n
* @n
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Call wifi_getRadioSupportedFrequencyBands without initializing WiFi. | radioIndex = valid value, output_string = valid buffer | RETURN_ERR | Should return error|
*/
void test_l1_wifi_common_hal_negative3_wifi_getRadioSupportedFrequencyBands(void)
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative3_wifi_getRadioSupportedFrequencyBands...");
    
    INT radioIndex = 1;
    CHAR output_string[12];
    INT return_status;
	
    WiFi_UnInitPosReq();
    // Assuming wifi_init() and wifi_initWithConfig() functions are not called 
    UT_LOG("Invoking wifi_getRadioSupportedFrequencyBands without initializing WiFi.");
    return_status = wifi_getRadioSupportedFrequencyBands(radioIndex, output_string);
    UT_LOG("Return Status: %d", return_status);
    WiFi_InitPreReq();
    UT_ASSERT_EQUAL(return_status, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative3_wifi_getRadioSupportedFrequencyBands...");
}


/**
* @brief Testing insufficient buffer size for wifi_getRadioSupportedFrequencyBands
*
* This test focuses on validating the behavior of the function wifi_getRadioSupportedFrequencyBands when an insufficient buffer size is provided. The objective is to assess the robustness of the function against invalid arguments. @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 050 @n
* **Priority:** High @n
* @n
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_getRadioSupportedFrequencyBands with insufficient buffer size | radioIndex = valid value, output_string size=5 |RETURN_ERR | Should return error |
*/
void test_l1_wifi_common_hal_negative4_wifi_getRadioSupportedFrequencyBands(void)
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative4_wifi_getRadioSupportedFrequencyBands...");

    INT radioIndex = 1;
    CHAR output_string[3]; // insufficient size
    INT return_status;
		
    UT_LOG("Invoking wifi_getRadioSupportedFrequencyBands with insufficient buffer size");
    return_status = wifi_getRadioSupportedFrequencyBands(radioIndex, output_string);
    UT_LOG("Return Status: %d", return_status);

    UT_ASSERT_EQUAL(return_status, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative4_wifi_getRadioSupportedFrequencyBands...");
}

/**
* @brief This test is to verify the function wifi_getRadioOperatingFrequencyBand
*
* This test is intended to verify the operation of wifi_getRadioOperatingFrequencyBand API. It checks whether the function is returning the correct output for the given input @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 051 @n
* **Priority:** High @n
* @n
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.
* @n
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_getRadioOperatingFrequencyBand with valid radio index and valid output_string buffer| radioIndex = valid value, output_string = valid buffer |RETURN_OK | Should return error |
*/        
void test_l1_wifi_common_hal_positive1_wifi_getRadioOperatingFrequencyBand(void)
{
    UT_LOG("Entering test_l1_wifi_common_hal_positive1_wifi_getRadioOperatingFrequencyBand...");

    CHAR output_string[32];
    INT radioIndex = 1;
    INT result;
	
    UT_LOG("Invoking wifi_getRadioOperatingFrequencyBand with radioIndex 1");
    result = wifi_getRadioOperatingFrequencyBand(radioIndex, output_string);

    UT_LOG("Returned: status: %d, output_string: %s", result, output_string);
    UT_ASSERT_EQUAL(result, RETURN_OK);
    if( (output_string != NULL) && (strcmp(output_string,"2.4GHz") != 0) && (strcmp(output_string,"5GHz") != 0))
	{
	    UT_LOG("failed due to invalid output_string : %s",output_string);
        UT_FAIL("failed due to invalid output_string");
	}
    UT_LOG("Exiting test_l1_wifi_common_hal_positive1_wifi_getRadioOperatingFrequencyBand...");
}


/**
* @brief Testing negative scenario to validate wifi_getRadioOperatingFrequencyBand function
*
* This test checks wifi_getRadioOperatingFrequencyBand function by providing different invalid input data to verify its error handling ability. @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 052 @n
* **Priority:** High @n
* @n
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_getRadioOperatingFrequencyBand with invalid radioIndex and valid output_string buffer| radioIndex = invalid value, output_string = valid |RETURN_ERR| Should return error |
*/
void test_l1_wifi_common_hal_negative1_wifi_getRadioOperatingFrequencyBand(void)
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative1_wifi_getRadioOperatingFrequencyBand...");

    CHAR output_string[32];
    INT radioIndex = 0;
    INT result;
	
    UT_LOG("Invoking wifi_getRadioOperatingFrequencyBand with radioIndex 0");
    result = wifi_getRadioOperatingFrequencyBand(radioIndex, output_string);

    UT_LOG("Returned: status: %d, output_string: %s", result, output_string);
    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative1_wifi_getRadioOperatingFrequencyBand...");
}

/**
* @brief This test case tests the wifi_getRadioOperatingFrequencyBand API when wifi is not initialized 
*
* The test case invokes the wifi_getRadioOperatingFrequencyBand function without prior initialisation of wifi to validate how well the API handles such scenarios @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 053 @n
* **Priority:** High @n
* @n
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_getRadioOperatingFrequencyBand without initializing wifi | radioIndex = valid value , output_string = valid buffer| RETURN_ERR | Should return error |
*/
void test_l1_wifi_common_hal_negative2_wifi_getRadioOperatingFrequencyBand(void)
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative2_wifi_getRadioOperatingFrequencyBand...");

    CHAR output_string[32];
    INT radioIndex = 1;
    INT result;
	
    WiFi_UnInitPosReq();	
    UT_LOG("Invoking wifi_getRadioOperatingFrequencyBand without calling wifi_init.");
    result = wifi_getRadioOperatingFrequencyBand(radioIndex, output_string);
    UT_LOG("Returned: status: %d, output_string: %s", result, output_string);
    WiFi_InitPreReq();
    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative2_wifi_getRadioOperatingFrequencyBand...");
}

/**
* @brief This test case checks the functionality of wifi_getRadioOperatingFrequencyBand when given a NULL buffer
*
* The function wifi_getRadioOperatingFrequencyBand is tested for its response when provided with a NULL buffer. The API should properly handle null inputs without causing a crash, thus the need for this test. @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 054 @n
* **Priority:** High @n
* @n
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke the function wifi_getRadioOperatingFrequencyBand with valid radioIndex and NULL output_string buffer | radioIndex = valid value, output_string = NULL | RETURN_ERR | Should return error |
*/
void test_l1_wifi_common_hal_negative3_wifi_getRadioOperatingFrequencyBand(void)
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative3_wifi_getRadioOperatingFrequencyBand...");

    CHAR *output_string = NULL;
    INT radioIndex = 1;
    INT result;
	
    UT_LOG("Invoking wifi_getRadioOperatingFrequencyBand with Buffer is NULL.");
    result = wifi_getRadioOperatingFrequencyBand(radioIndex, output_string);

    UT_LOG("Returned: status: %d", result);

    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative3_wifi_getRadioOperatingFrequencyBand...");
}

/**
* @brief This function tests the 'wifi_getRadioSupportedStandards' API in successful scenarios.
*
* It verifies that the 'wifi_getRadioSupportedStandards' API can correctly handle valid input parameters and that it returns the expected standards from wifi radio. @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 055 @n
* **Priority:** High @n
* @n
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_getRadioSupportedStandards API with valid radioIndex and valid output_string buffer | radioIndex = valid value, output_string = valid buffer | RETURN_OK | Should be successful |
*/
void test_l1_wifi_common_hal_positive1_wifi_getRadioSupportedStandards(void)
{
    UT_LOG("Entering test_l1_wifi_common_hal_positive1_wifi_getRadioSupportedStandards ... \n"); 
    CHAR output_string[100];
	INT radioIndex = 1;	
    int status;
	
    UT_LOG("Invoking wifi_getRadioSupportedStandards with valid input parameters.");
    status = wifi_getRadioSupportedStandards(radioIndex, output_string);
    UT_LOG("Returned status: %d, output_string: %s \n", status, output_string);

    UT_ASSERT_EQUAL(status, RETURN_OK);
    if((strcmp(output_string,"b,g,n") != 0) && (strcmp(output_string,"a,n,ac") != 0))
	{
	    UT_LOG("failed due to invalid output_string : %s",output_string);
        UT_FAIL("failed due to invalid output_string");
	}
    UT_LOG("Exiting test_l1_wifi_common_hal_positive1_wifi_getRadioSupportedStandards ...\n");
}

/**
* @brief This test is designed to evaluate the failure scenario of wifi_getRadioSupportedStandards() function
*
* In this test, the wifi_getRadioSupportedStandards() function is invoked with an invalid radio index to test whether it returns an appropriate failure status. @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 056 @n
* **Priority:** High @n
* @n
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_getRadioSupportedStandards function with invalid radio index and valid output_string buffer | radio index = invalid value, output_string = valid buffer | RETURN_ERR | Should return error|
*/
void test_l1_wifi_common_hal_negative1_wifi_getRadioSupportedStandards(void){
    UT_LOG("Entering test_l1_wifi_common_hal_negative1_wifi_getRadioSupportedStandards ... \n");
    CHAR output_string[100];
	INT radioIndex = 0;
    int status;	
	
    UT_LOG("Invoking wifi_getRadioSupportedStandards with invalid radio index 0");	
    status = wifi_getRadioSupportedStandards(radioIndex, output_string);
    UT_LOG("Invoking wifi_getRadioSupportedStandards with invalid radio index. Returned status: %d\n", status);
    UT_ASSERT_EQUAL(status, RETURN_ERR);
    UT_LOG("Exiting test_l1_wifi_common_hal_negative1_wifi_getRadioSupportedStandards ...\n");
}

/**
* @brief This test is designed to test the negative scenario of the wifi_getRadioSupportedStandards API function.
*
* This test verifies the return value of the wifi_getRadioSupportedStandards function when the output_string parameter is NULL. This helps to ensure reliable error handling in the API. @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 057 @n
* **Priority:** High @n
* @n
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_getRadioSupportedStandards with valid radioIndex and output_string as NULL | radioIndex = valid value , output_string = NULL |RETURN_ERR |Should return error|
*/
void test_l1_wifi_common_hal_negative2_wifi_getRadioSupportedStandards(void)
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative2_wifi_getRadioSupportedStandards ... \n");
	INT radioIndex = 1;
    int status;
	
    UT_LOG("Invoking wifi_getRadioSupportedStandards with output_string as NULL. ");	
    status = wifi_getRadioSupportedStandards(radioIndex, NULL);
    UT_LOG("Returned status: %d\n", status);
    UT_ASSERT_EQUAL(status, RETURN_ERR);
    UT_LOG("Exiting test_l1_wifi_common_hal_negative2_wifi_getRadioSupportedStandards ...\n");
}

/**
* @brief Test the behavior of wifi_getRadioSupportedStandards function before wifi initialization
*
* This unit test checks the return status of wifi_getRadioSupportedStandards function when invoked before the initialization of wifi. It is performed to verify that this function should not be successfully performed without the necessary preliminary steps. @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 058 @n
* **Priority:** High @n
* @n
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_getRadioSupportedStandards before initializing wifi | radioIndex = valid value , output_string = valid buffer | RETURN_ERR | Should be successful |
*/
void test_l1_wifi_common_hal_negative3_wifi_getRadioSupportedStandards(void)
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative3_wifi_getRadioSupportedStandards ... \n");
    // Add code to ensure wifi is *not* initialized before this test
    CHAR output_string[100];
    int status;
	INT radioIndex = 1;
	
	WiFi_UnInitPosReq();
    UT_LOG("Invoking wifi_getRadioSupportedStandards without initializing wifi.");	
    status = wifi_getRadioSupportedStandards(radioIndex, output_string);
    UT_LOG("Returned status: %d\n", status);
	WiFi_InitPreReq();
    UT_ASSERT_EQUAL(status, RETURN_ERR);
    UT_LOG("Exiting test_l1_wifi_common_hal_negative3_wifi_getRadioSupportedStandards ...\n");
}

/**
* @brief Test to verify wifi_getRadioStandard function of l1_wifi_common_hal API
*
* This test is designed to validate the wifi_getRadioStandard function of l1_wifi_common_hal API by passing valid parameters and checking if the function call is successful and returns the expected results. @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 059 @n
* **Priority:** High @n
* @n
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_getRadioStandard function with valid radioIndex, valid output_string buffer, valid gOnly buffer, valid nOnly buffer and valid acOnly buffer | radioIndex = valid value, output_string = valid buffer, gOnly = valid buffer, nOnly = valid buffer, acOnly = valid buffer | RETURN_OK | Should be successful |
*/
void test_l1_wifi_common_hal_positive1_wifi_getRadioStandard(void) 
{
    UT_LOG("Entering test_l1_wifi_common_hal_positive1_wifi_getRadioStandard...");

    INT radioIndex = 1;
    CHAR output_string[50];
    BOOL gOnly, nOnly, acOnly;
    INT retStatus;
	
    UT_LOG("Invoking wifi_getRadioStandard with radioIndex 1. Output Buffer is NOT NULL."); 
    retStatus = wifi_getRadioStandard(radioIndex, output_string, &gOnly, &nOnly, &acOnly);
    
    UT_LOG("Return status is %d", retStatus);
    
    UT_ASSERT_EQUAL(retStatus, RETURN_OK);
    if((strcmp(output_string,"b,g,n") != 0) && (strcmp(output_string,"a,n,ac") != 0))
	{
	    UT_LOG("failed due to invalid output_string : %s",output_string);
        UT_FAIL("failed due to invalid output_string");
	}
    UT_LOG("Exiting test_l1_wifi_common_hal_positive1_wifi_getRadioStandard...");
}


/**
* @brief Test case for wifi_getRadioStandard API.
*
* The function wifi_getRadioStandard is tested with the input radioIndex = 2, for a negative boundary case. The expectation is that the function return value should be RETURN_ERR, as the specified radio index is invalid.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 060 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.@n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | :---------: | :----------: | :--------------: | :-----: |
* | 01 | Invoke wifi_getRadioStandard API with invalid radioIndex | radioIndex = 2 |  RETURN_ERR | API response is validated against the expected error code |
*/
void test_l1_wifi_common_hal_negative1_wifi_getRadioStandard(void) 
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative1_wifi_getRadioStandard...");

    INT radioIndex = 2;
    CHAR output_string[50];
    BOOL gOnly, nOnly, acOnly;
    INT retStatus;
	
    UT_LOG("Invoking wifi_getRadioStandard with radioIndex 2.");
    retStatus = wifi_getRadioStandard(radioIndex, output_string, &gOnly, &nOnly, &acOnly);

    UT_LOG("Return status is %d", retStatus);

    UT_ASSERT_EQUAL(retStatus, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative1_wifi_getRadioStandard...");
}


/**
* @brief This test ensures the function wifi_getRadioStandard fails when called without prior calling of wifi_init() or wifi_initWithConfig().
*
* This test invokes wifi_getRadioStandard without prior calling of wifi_init() or wifi_initWithConfig() and expected to return an error. This is to ensure the robustness of the API in case of any improper sequence of API calls.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 061 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | :---------: | :----------: | :--------------: | :-----: |
* | 01 | Invoke wifi_getRadioStandard without prior calling of wifi_init() or wifi_initWithConfig(). | radioIndex: 1, output_string: char array of size 50, gOnly: BOOL, nOnly: BOOL, acOnly: BOOL  | RETURN_ERR   | Test should fail |
*/
void test_l1_wifi_common_hal_negative2_wifi_getRadioStandard(void) 
{
    /* Correct implementation should involve an internal mechanism to check if wifi_init() or wifi_initWithConfig() was called */
    UT_LOG("Entering test_l1_wifi_common_hal_negative2_wifi_getRadioStandard...");

    INT radioIndex = 1;
    CHAR output_string[50];
    BOOL gOnly, nOnly, acOnly;
    INT retStatus;
	
	WiFi_UnInitPosReq();
    UT_LOG("Invoking wifi_getRadioStandard without prior calling of wifi_init() or wifi_initWithConfig().");
    retStatus = wifi_getRadioStandard(radioIndex, output_string, &gOnly, &nOnly, &acOnly);
    
    UT_LOG("Return status is %d", retStatus);
    WiFi_InitPreReq();
    UT_ASSERT_EQUAL(retStatus, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative2_wifi_getRadioStandard...");
}

/**
* @brief Tests the wifi_getRadioStandard API with all output buffers as NULL
*
* This test validates the wifi_getRadioStandard API when all output buffers are NULL.
* The test verifies if the API returns error when output pointers are NULL, thus aiming to test robustness of the API.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 062 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | :---------: | :----------: | :--------------: | :-----: |
* | 01 | Invoke wifi_getRadioStandard API with all output buffers as NULL | radioIndex = 1, all output buffers = NULL |  RETURN_ERR | Should fail and return error |
*/
void test_l1_wifi_common_hal_negative3_wifi_getRadioStandard(void) 
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative3_wifi_getRadioStandard...");

    INT radioIndex = 1;
    INT retStatus;
	
    UT_LOG("Invoking wifi_getRadioStandard with radioIndex 1. All Output Buffers are NULL.");
    retStatus = wifi_getRadioStandard(radioIndex, NULL, NULL, NULL, NULL);
    
    UT_LOG("Return status is %d", retStatus);

    UT_ASSERT_EQUAL(retStatus, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative3_wifi_getRadioStandard...");
}


/**
* @brief This test ensures that the function wifi_getRadioPossibleChannels is working correctly
*
* This test invokes the wifi_getRadioPossibleChannels API with valid parameters and checks if the return value is as expected. If the return value fulfills the conditions, the test is considered successful. The rational behind this test is to ensure the API's robustness and correct functionality.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 063 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
* 
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | :---------: | :----------: | :--------------: | :-----: |
* | 01 | Invoke the wifi_getRadioPossibleChannels API with valid parameters | radioIndex = 1, output_string = "empty array" |  RETURN_OK | Should be successful |
*/
void test_l1_wifi_common_hal_positive1_wifi_getRadioPossibleChannels(void)
{
    UT_LOG("Entering test_l1_wifi_common_hal_positive1_wifi_getRadioPossibleChannels...");

    INT radioIndex = 1;
    CHAR output_string[50];
    INT retVal;

    UT_LOG("Invoking wifi_getRadioPossibleChannels with valid radioIndex and output_string");
    retVal = wifi_getRadioPossibleChannels(radioIndex, output_string);
    UT_LOG("Returned value was %d", retVal);

    UT_ASSERT_EQUAL(retVal, RETURN_OK);
    if((strcmp(output_string,"1-13") != 0) && (strcmp(output_string,"36-64,100-165") != 0))
	{
	    UT_LOG("failed due to invalid output_string : %s",output_string);
        UT_FAIL("failed due to invalid output_string");
	}
    UT_LOG("Exiting test_l1_wifi_common_hal_positive1_wifi_getRadioPossibleChannels...");
}

/**
* @brief Tests wifi_getRadioPossibleChannels function with invalid radio index
*
* This test is designed to validate the wifi_getRadioPossibleChannels function when provided with invalid input. The test will invoke the function with an invalid radio index and assert whether the function returns the expected error value.@n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 064 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | :---------: | :----------: | :--------------: | :-----: |
* | 01 | Invoke wifi_getRadioPossibleChannels with invalid radioIndex | radioIndex = 2  | RETURN_ERR | Expected failure as the radioIndex is invalid |
*
*/
void test_l1_wifi_common_hal_negative1_wifi_getRadioPossibleChannels( void )
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative1_wifi_getRadioPossibleChannels...");

    INT radioIndex = 2;
    CHAR output_string[50];
    INT retVal;

    UT_LOG("Invoking wifi_getRadioPossibleChannels with invalid radioIndex");
    retVal = wifi_getRadioPossibleChannels(radioIndex, output_string);
    UT_LOG("Returned value was %d", retVal);

    UT_ASSERT_EQUAL(retVal, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative1_wifi_getRadioPossibleChannels...");
}

/**
* @brief This test aims to exercise the wifi_getRadioPossibleChannels API when wifi_init() has not been called
*
* The purpose of this test is to ensure that the wifi_getRadioPossibleChannels API function handles the case where it's invoked before wifi_init() is called appropriately.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 065 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:**@n
* Here's a detailed list of the procedure of this test, as well as the test inputs and expected results. @n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | :---------: | :----------: | :--------------: | :-----: |
* | 01 | invoke wifi_getRadioPossibleChannels without calling wifi_init() | radioIndex = 1, output_string = "", |  RETURN_ERR | Should fail and return error |
*
*/ 
void test_l1_wifi_common_hal_negative2_wifi_getRadioPossibleChannels( void )
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative2_wifi_getRadioPossibleChannels...");

    INT radioIndex = 1;
    CHAR output_string[50];
    INT retVal;

    // No wifi_init() called
    WiFi_UnInitPosReq();
    UT_LOG("Invoking wifi_getRadioPossibleChannels before wifi_init()");
    retVal = wifi_getRadioPossibleChannels(radioIndex, output_string);
    UT_LOG("Returned value was %d", retVal);
    WiFi_InitPreReq();	
    UT_ASSERT_EQUAL(retVal, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative2_wifi_getRadioPossibleChannels...");
}

/**
 * @brief Test for wifi_getRadioPossibleChannels function with null output_string
 *
 * This function executes a test scenario where wifi_getRadioPossibleChannels is invoked with a null output_string. The objective of this test is to verify if the function handles such scenario and returns an error code.@n
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 066 @n
 * **Priority:** High @n@n
 * 
 * **Pre-Conditions:** None@n
 * **Dependencies:** None@n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
 * 
 * **Test Procedure:**@n
 * | Variation / Step | Description | Test Data |Expected Result |Notes |
 * | :----: | :---------: | :----------: | :--------------: | :-----: |
 * | 01 | Invoke wifi_getRadioPossibleChannels with the null output_string | radioIndex = 1, output_string = NULL | Return code indicating failure | Should return an error code |
 */
void test_l1_wifi_common_hal_negative3_wifi_getRadioPossibleChannels( void )
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative3_wifi_getRadioPossibleChannels...");

    INT radioIndex = 1;
    CHAR* output_string = NULL;
    INT retVal;

    UT_LOG("Invoking wifi_getRadioPossibleChannels with null output_string");
    retVal = wifi_getRadioPossibleChannels(radioIndex, output_string);
    UT_LOG("Returned value was %d", retVal);
    UT_ASSERT_EQUAL(retVal, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative3_wifi_getRadioPossibleChannels...");
}

/**
* @brief This test case is designed to check the negative condition for the method 'wifi_getRadioPossibleChannels' in the WiFi Common HAL library.
*
* This test ensures that an error code is returned when we call 'wifi_getRadioPossibleChannels' function with insufficient storage size for output string. It helps in verifying the robustness of wifi_getRadioPossibleChannels API by testing negative conditions. 
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 067 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.
*
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | :---------: | :----------: | :--------------: | :-----: |
* | 01 | Call wifi_getRadioPossibleChannels with insufficient buffer size | radioIndex = 1, output_string size = insufficient | RETURN_ERR | Test is considered successful if it receives error code for insufficient buffer size |
*/
void test_l1_wifi_common_hal_negative4_wifi_getRadioPossibleChannels( void )
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative4_wifi_getRadioPossibleChannels...");

    INT radioIndex = 1;
    CHAR output_string[3]; // not enough to hold return string
    INT retVal;

    UT_LOG("Invoking wifi_getRadioPossibleChannels with insufficient size output_string");
    retVal = wifi_getRadioPossibleChannels(radioIndex, output_string);
    UT_LOG("Returned value was %d", retVal);

    UT_ASSERT_EQUAL(retVal, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative4_wifi_getRadioPossibleChannels...");
}


/**
* @brief This test verifies the function wifi_getRadioChannelsInUse
*
* This function tests if the wifi_getRadioChannelsInUse() correctly returns the channels in use
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 068 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | :---------: | :----------: | :--------------: | :-----: |
* | 01 | Invoke wifi_getRadioChannelsInUse with valid radioIndex (1) and valid output_string buffer | radioIndex = 1, output_string = valid buffer | RETURN_OK | Should be successful |
*
*/
void test_l1_wifi_common_hal_positive1_wifi_getRadioChannelsInUse( void )
{
    UT_LOG("Entering test_l1_wifi_common_hal_positive1_wifi_getRadioChannelsInUse...");
    CHAR output_string[MAX_LENGTH];
    INT returnValue;
	INT radioIndex = 1;
    /* Assume wifi_init() has been successfully called */
    UT_LOG("Invoking wifi_getRadioChannelsInUse with valid radioIndex (1) and valid output_string buffer.");
    returnValue = wifi_getRadioChannelsInUse(radioIndex, output_string);
    UT_LOG("Return Value: %d, output_string: %s", returnValue, output_string);
    UT_ASSERT_EQUAL(returnValue, RETURN_OK);
    if((strcmp(output_string,"1-13") != 0) && (strcmp(output_string,"36-64,100-165") != 0))
	{
	    UT_LOG("failed due to invalid output_string : %s",output_string);
        UT_FAIL("failed due to invalid output_string");
	}
    UT_LOG("Exiting test_l1_wifi_common_hal_positive1_wifi_getRadioChannelsInUse...");
}

/**
* @brief This test is to verify wifi_getRadioChannelsInUse API when wifi_init() or wifi_initWithConfig() has not been called
*
* This test invokes the `wifi_getRadioChannelsInUse` API without calling the setup APIs `wifi_init()` or `wifi_initWithConfig()`. It is expected that the API will return an error in this scenario. This is a negative test case.@n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 069 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | :---------: | :----------: | :--------------: | :-----: |
* | 01 | Invoke wifi_getRadioChannelsInUse API without calling the wifi_init() or wifi_initWithConfig(). | API Invocation: wifi_getRadioChannelsInUse(1, output_string) | Return Value should be RETURN_ERR. | Should fail and return error |
*/
void test_l1_wifi_common_hal_negative1_wifi_getRadioChannelsInUse( void )
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative1_wifi_getRadioChannelsInUse...");
    /* Assume wifi_init() or wifi_initWithConfig() hasn't been called here */
    CHAR output_string[MAX_LENGTH];
	INT radioIndex = 1;
    INT returnValue;
	
	WiFi_UnInitPosReq();
    UT_LOG("Invoking wifi_getRadioChannelsInUse without calling wifi_init() or wifi_initWithConfig().");	
    returnValue = wifi_getRadioChannelsInUse(radioIndex, output_string);
    UT_LOG("Return Value: %d", returnValue);
	WiFi_InitPreReq();
    UT_ASSERT_EQUAL(returnValue, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative1_wifi_getRadioChannelsInUse...");

}

/**
* @brief This test is designed to validate the negative scenario of the wifi_getRadioChannelsInUse API
*
* This test is testing the behavior of the wifi_getRadioChannelsInUse API when passed with an invalid radioIndex. The test aims to verify that the API returns an error hence establishing its robustness towards invalid input
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 070 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | :---------: | :----------: | :--------------: | :-----: |
* | 01 | Invoke wifi_getRadioChannelsInUse API with invalid radioIndex | radioIndex = 2 | RETURN_ERR | Should fail and return error |
*/ 
void test_l1_wifi_common_hal_negative2_wifi_getRadioChannelsInUse( void )
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative2_wifi_getRadioChannelsInUse...");

    CHAR output_string[MAX_LENGTH];
	INT radioIndex = 2;
    INT returnValue;
	
    /* Test with invalid radioIndex */
    UT_LOG("Invoking wifi_getRadioChannelsInUse with invalid radioIndex (2).");
    returnValue = wifi_getRadioChannelsInUse(radioIndex, output_string);
    UT_LOG("Return Value: %d", returnValue);
    UT_ASSERT_EQUAL(returnValue, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative2_wifi_getRadioChannelsInUse...");

}

/**
* @brief This test aims to check the functionality of function wifi_getRadioChannelsInUse for negative case.
*
* The negative test scenario for function wifi_getRadioChannelsInUse is validated in this test. The function is tested with NULL output_string to confirm it returns error code as expected.
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
* | :----: | :---------: | :----------: | :--------------: | :-----: |
* | 01 | Test wifi_getRadioChannelsInUse API with NULL output_string  with Valid Index | index = 1, output_string = NULL | RETRUN_ERR | Should fail and return error |
*/
void test_l1_wifi_common_hal_negative3_wifi_getRadioChannelsInUse( void )
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative3_wifi_getRadioChannelsInUse...");
	INT radioIndex = 1;
    INT returnValue;
    /* Test with NULL output_string */
    UT_LOG("Invoking wifi_getRadioChannelsInUse with NULL output_string.");
    returnValue = wifi_getRadioChannelsInUse(radioIndex, NULL);
    UT_LOG("Return Value: %d", returnValue);
    UT_ASSERT_EQUAL(returnValue, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative3_wifi_getRadioChannelsInUse...");

}

/**
* @brief This test validates the behavior of wifi_getRadioChannelsInUse when invoked with an output buffer of insufficient size.
*
* The test specifically tests the behavior of wifi_getRadioChannelsInUse API when it is invoked with insufficient buffer size in the output variable. 
* This is to ensure that the API handles this case without causing any memory overflow.@n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 072 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | :---------: | :----------: | :--------------: | :-----: |
* | 01 | Invoke wifi_getRadioChannelsInUse with insufficient output_string buffer size. | radioIndex = 1, output_string size = 2 | RETURN_ERRb| The function is tested against an abnormal case where the output buffer size is insufficient.|
*/
void test_l1_wifi_common_hal_negative4_wifi_getRadioChannelsInUse( void )
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative4_wifi_getRadioChannelsInUse...");
	INT radioIndex = 1;
    CHAR output_string[2]; /* buffer having insufficient size */
    INT returnValue;
    /* Test with output_string having insufficient size */
    UT_LOG("Invoking wifi_getRadioChannelsInUse with insufficient output_string buffer size.");
    returnValue = wifi_getRadioChannelsInUse(radioIndex, output_string);
    UT_LOG("Return Value: %d", returnValue);
    UT_ASSERT_EQUAL(returnValue, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative4_wifi_getRadioChannelsInUse...");
}

/**
* @brief This test aims to verify the correct functionality of the wifi_getRadioChannel function
*
* In this test, the wifi_getRadioChannel API is invoked with valid parameters, and the returned channel number and return status are asserted against expected values.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 073 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | :---------: | :----------: | :--------------: | :-----: |
* | 01 | Invoke the wifi_getRadioChannel API with valid parameters | input1 = 1, input2 is a pointer to ULONG |  RETURN_OK | Should be successful |
*/
void test_l1_wifi_common_hal_positive1_wifi_getRadioChannel( void )
{
    UT_LOG("Entering test_l1_wifi_common_hal_positive1_wifi_getRadioChannel...");
	INT radioIndex = 1;
    ULONG output_ulong;
    INT returnValue;	
    UT_LOG("Invoking wifi_getRadioChannel with valid input parameters. ");
    returnValue = wifi_getRadioChannel(radioIndex, &output_ulong);

    UT_LOG("The returned channel number is %lu and return status is %d", output_ulong, returnValue);
    UT_ASSERT_EQUAL(returnValue, RETURN_OK);
	if(output_ulong >= 1 && output_ulong <= 13)
	{
		UT_LOG("valid Radio channel %lu ",output_ulong);
		UT_PASS("valid Radio channel");
	}
	else if(output_ulong >= 36 && output_ulong <= 64)
	{
		UT_LOG("valid Radio channel %lu ",output_ulong);
		UT_PASS("valid Radio channel");		
	}	
	else if(output_ulong >= 100 && output_ulong <= 165)
	{
		UT_LOG("valid Radio channel %lu ",output_ulong);
		UT_PASS("valid Radio channel");		
	}
	else
	{
		UT_LOG("invalid Radio channel %lu ",output_ulong);
		UT_FAIL("invalid Radio channel");	
	}
    UT_LOG("Exiting test_l1_wifi_common_hal_positive1_wifi_getRadioChannel...");
}

/**
* @brief Test to check the wifi_getRadioChannel API with negative scenario
*
* This test invokes the wifi_getRadioChannel API with invalid radioIndex input. The purpose of the test is to ensure that the API is handling the invalid input as expected and returning the correct error code.
* 
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 074 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | :---------: | :----------: | :--------------: | :-----: |
* | 01 | Invoke wifi_getRadioChannel with invalid radioIndex input | radioIndex = 2 | RETURN_ERR| Return value from API should be RETURN_ERR |
*/
void test_l1_wifi_common_hal_negative1_wifi_getRadioChannel( void )
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative1_wifi_getRadioChannel...");

    ULONG output_ulong;
	INT radioIndex = 2;
    INT returnValue;
	
    UT_LOG("Invoking wifi_getRadioChannel with invalid radioIndex input.");
    returnValue = wifi_getRadioChannel(radioIndex, &output_ulong);

    UT_LOG("Return status is %d", returnValue);

    UT_ASSERT_EQUAL(returnValue, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative1_wifi_getRadioChannel...");
}

/**
* @brief This test checks the handling of a NULL pointer by the wifi_getRadioChannel API
*
* In this unit test, wifi_getRadioChannel() is called with a null pointer as a parameter to test how the function handles erroneous input
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 075 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_getRadioChannel() with a NULL output pointer | output_ulong = NULL | The return value should match RETURN_ERR | The function should handle invalid input gracefully |
*/
void test_l1_wifi_common_hal_negative2_wifi_getRadioChannel( void )
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative2_wifi_getRadioChannel...");

    ULONG *output_ulong = NULL;
	INT radioIndex = 1;
    INT returnValue;

    UT_LOG("Invoking wifi_getRadioChannel with NULL output_ulong pointer.");
    returnValue = wifi_getRadioChannel(radioIndex, output_ulong);

    UT_LOG("Return status is %d", returnValue);

    UT_ASSERT_EQUAL(returnValue, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative2_wifi_getRadioChannel...");
}

/**
* @brief This test aims to verify the  functionality of the wifi_getRadioChannel function when wifi_init() or wifi_initWithConfig() not invoked.
*
* In this test, the wifi_getRadioChannel API is invoked before wifi_init() or wifi_initWithConfig(), and the return status is RETURN_ERR .@n
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 073@n
* **Priority:** High@n
* @n
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke the wifi_getRadioChannel API before wifi_init() or wifi_initWithConfig() | radioIndex = 1, input2 is a pointer to ULONG | the function should return RETURN_ERR | Should  fail |
*/

void test_l1_wifi_common_hal_negative3_wifi_getRadioChannel( void )
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative3_wifi_getRadioChannel...");
	INT radioIndex = 1;
    ULONG output_ulong;
    INT returnValue;
	//wifi_uninit
	WiFi_UnInitPosReq();
    UT_LOG("Invoking wifi_getRadioChannel before wifi_init() or wifi_initWithConfig() ");
    returnValue = wifi_getRadioChannel(radioIndex, &output_ulong);

    UT_LOG("The returned channel number is %lu and return status is %d", output_ulong, returnValue);
    WiFi_InitPreReq();
    UT_ASSERT_EQUAL(returnValue, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative3_wifi_getRadioChannel...");
}

/**
* @brief Evaluates 'wifi_getRadioAutoChannelSupported' functionality for valid inputs
*
* Tests the 'wifi_getRadioAutoChannelSupported' function with a valid radio index and non-null output_bool to see whether it returns the correct integer and updates the output_bool parameter correctly@n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 076 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | :---------: | :----------: | :--------------: | :-----: |
* | 01 | Invoke 'wifi_getRadioAutoChannelSupported' method with valid radioIndex and non-null output_bool | radioIndex = 1, output_bool = non-null | RETURN_OK | Should be successful |
*/
void test_l1_wifi_common_hal_positive1_wifi_getRadioAutoChannelSupported(void)
{
    UT_LOG("Entering test_l1_wifi_common_hal_positive1_wifi_getRadioAutoChannelSupported...");

    INT radioIndex = 1;
    BOOL output_bool;
    INT result;
	
    UT_LOG("Invoking wifi_getRadioAutoChannelSupported with valid radioIndex and non-null output_bool");
    result = wifi_getRadioAutoChannelSupported(radioIndex, &output_bool);

    UT_LOG("return status: %d, output_bool: %d", result, output_bool);

    UT_ASSERT_EQUAL(result, RETURN_OK);
    if((output_bool != '0') && (output_bool != '1'))
	{
	    UT_LOG("failed due to invalid output_bool : %c",output_bool);
        UT_FAIL("failed due to invalid output_bool");		
	}
    UT_LOG("Exiting test_l1_wifi_common_hal_positive1_wifi_getRadioAutoChannelSupported...");
}


/**
* @brief This test checks if the function 'wifi_getRadioAutoChannelSupported' handles uninitialized WiFi scenario correctly.
*
* The function 'wifi_getRadioAutoChannelSupported' should return an error when called without WiFi initialization. This test validates this scenario.@n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 077 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.@n
* 
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | :---------: | :----------: | :--------------: | :-----: |
* | 01 | invoke 'wifi_getRadioAutoChannelSupported' without WiFi initialization | radioIndex = 1, output_bool  | RETURN_ERR | Should be Fail |
*/
void test_l1_wifi_common_hal_negative1_wifi_getRadioAutoChannelSupported(void)
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative1_wifi_getRadioAutoChannelSupported...");

    INT radioIndex = 1;
    BOOL output_bool;
    INT result;	
	
    WiFi_UnInitPosReq();
    // Assume wiFi is not initialized
    UT_LOG("Invoking wifi_getRadioAutoChannelSupported with no WiFi initialization.");
    result = wifi_getRadioAutoChannelSupported(radioIndex, &output_bool);

    UT_LOG("return status: %d", result);
    WiFi_InitPreReq();
    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative1_wifi_getRadioAutoChannelSupported...");
}

/**
 * @brief This test attempts to validate the function wifi_getRadioAutoChannelSupported with an invalid radioIndex
 *
 * This test aims to verify the wifi_getRadioAutoChannelSupported when an invalid radioIndex is provided. It is crucial to ensure that the function correctly handles such invalid inputs.@n
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 078 @n
 * **Priority:** High @n@n
 * 
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
 * 
 * **Test Procedure:**@n
 * | Variation / Step | Description | Test Data |Expected Result |Notes |
 * | :----: | :---------: | :----------: | :--------------: | :-----: |
 * | 01 | Invoking wifi_getRadioAutoChannelSupported with invalid radioIndex. | radioIndex = 2 | RETURN_ERR | The function wifi_getRadioAutoChannelSupported should correctly handle invalid inputs |
 */
void test_l1_wifi_common_hal_negative2_wifi_getRadioAutoChannelSupported(void)
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative2_wifi_getRadioAutoChannelSupported...");

    INT radioIndex = 2; // Invalid radioIndex
    BOOL output_bool;
    INT result;
	
    UT_LOG("Invoking wifi_getRadioAutoChannelSupported with invalid radioIndex.");
    result = wifi_getRadioAutoChannelSupported(radioIndex, &output_bool);

    UT_LOG("Returned value was :  %d", result);
    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative2_wifi_getRadioAutoChannelSupported...");
}

/**
* @brief Checks the negative scenarios of wifi_getRadioAutoChannelSupported API
*
* This function tests if the wifi_getRadioAutoChannelSupported API handles error scenarios properly. Specifically, it tests the condition where a NULL parameter is passed for the output_bool argument.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 079 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | :---------: | :----------: | :--------------: | :-----: |
* | 01 | Invoke wifi_getRadioAutoChannelSupported with NULL for output_bool | radioIndex = 1, output_bool = NULL | RETURN_ERR | Should be Fail |
*/
void test_l1_wifi_common_hal_negative3_wifi_getRadioAutoChannelSupported(void)
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative3_wifi_getRadioAutoChannelSupported...");
    INT radioIndex = 1;
    INT result;
    // Passing NULL for output_bool
    UT_LOG("Invoking wifi_getRadioAutoChannelSupported with NULL output_bool.");
    result = wifi_getRadioAutoChannelSupported(radioIndex, NULL);
    UT_LOG("Returned value was : %d ",result);
    UT_ASSERT_EQUAL(result, RETURN_ERR);
    UT_LOG("Exiting test_l1_wifi_common_hal_negative3_wifi_getRadioAutoChannelSupported...");
}


/**
* @brief This test is intended to validate the behavior of wifi_getRadioAutoChannelSupported API when invoked with invalid output_bool.
*
* In this test, the wifi_getRadioAutoChannelSupported API is called with an invalid output_bool value to test how it handles the erroneous condition.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 080 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | :---------: | :----------: | :--------------: | :-----: |
* | 01 | Invoke wifi_getRadioAutoChannelSupported api with output_bool not 0 or 1. | radioIndex = 1, output_bool = 3 |  RETURN_OK | Should be a failure |
*/
void test_l1_wifi_common_hal_positive2_wifi_getRadioAutoChannelSupported(void)
{
    UT_LOG("Entering test_l1_wifi_common_hal_positive2_wifi_getRadioAutoChannelSupported...");

    INT radioIndex = 1;
    BOOL output_bool = 3; // output_bool not 0 or 1
    INT result;
	
    UT_LOG("Invoking wifi_getRadioAutoChannelSupported with  output_bool = 3 ");
    result = wifi_getRadioAutoChannelSupported(radioIndex, &output_bool);

    UT_LOG("Returned value was: %d", result);

    UT_ASSERT_EQUAL(result, RETURN_OK);
    if((output_bool != '0') && (output_bool != '1'))
	{
	    UT_LOG("failed due to invalid output_bool : %c",output_bool);
        UT_FAIL("failed due to invalid output_bool");		
	}

    UT_LOG("Exiting test_l1_wifi_common_hal_positive2_wifi_getRadioAutoChannelSupported...");
}

/**
* @brief Test for wifi_getRadioAutoChannelEnable function.
*
* Verifies if the wifi_getRadioAutoChannelEnable function is working as expected, by calling it post successful initialization and then checking the return status.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 081 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | :---------: | :----------: | :--------------: | :-----: |
* | 01 | Call wifi_getRadioAutoChannelEnable function post initialization | radioIndex = 1, output_bool = valid buffer | Return OK Status  | Should be successful |
*/
void test_l1_wifi_common_hal_positive1_wifi_getRadioAutoChannelEnable( void )
{
    BOOL output_bool;
    INT ret;
    INT radioIndex = 1;
    UT_LOG("Entering test_l1_wifi_common_hal_positive1_wifi_getRadioAutoChannelEnable...");

    // The wifi_init or wifi_initWithConfig function call is assumed to be successful before this point.
    UT_LOG("Invoking wifi_getRadioAutoChannelEnable(1, &output_bool)");   
    ret = wifi_getRadioAutoChannelEnable(radioIndex, &output_bool);
    UT_LOG("Received output_bool: %c and return status: %d", output_bool, ret);
    
    UT_ASSERT_EQUAL(ret, RETURN_OK)
    if((output_bool != '0') && (output_bool != '1'))
	{
	    UT_LOG("failed due to invalid output_bool : %c",output_bool);
        UT_FAIL("failed due to invalid output_bool");		
	}    
    UT_LOG("Exiting test_l1_wifi_common_hal_positive1_wifi_getRadioAutoChannelEnable...");
}

/**
* @brief Test for 'wifi_getRadioAutoChannelEnable' when called with invalid parameter 
*
* This test aims at validating the wifi_getRadioAutoChannelEnable function from the Wifi Common HAL  when called with an invalid index. 
* 
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 082 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | :---------: | :----------: | :--------------: | :-----: |
* | 01 | Invoke wifi_getRadioAutoChannelEnable with invalid index 2 | index = 2, output_bool = Valid buffer | RETURN_ERR | Should be Fail |
*/
void test_l1_wifi_common_hal_negative1_wifi_getRadioAutoChannelEnable( void )
{
    BOOL output_bool;
    INT ret;
    INT radioIndex = 2;   
    UT_LOG("Entering test_l1_wifi_common_hal_negative1_wifi_getRadioAutoChannelEnable...");
    UT_LOG("Invoking wifi_getRadioAutoChannelEnable(2, &output_bool).");
    ret = wifi_getRadioAutoChannelEnable(radioIndex, &output_bool);
    UT_LOG("Received output_bool: %c and return status: %d", output_bool, ret);
    
    UT_ASSERT_EQUAL(ret, RETURN_ERR);
    
    UT_LOG("Exiting test_l1_wifi_common_hal_negative1_wifi_getRadioAutoChannelEnable...");
}

/**
* @brief This test validates the function wifi_getRadioAutoChannelEnable for negative scenarios.
*
* In this test, the function wifi_getRadioAutoChannelEnable is tested with invalid parameters to verify its robustness in handling error scenarios.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 083 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | :---------: | :----------: | :--------------: | :-----: |
* | 01 | Call wifi_getRadioAutoChannelEnable with NULL pointer for output parameter | input1 = 1, output = NULL | RETURN_ERR | Should be Fail |
*/
void test_l1_wifi_common_hal_negative2_wifi_getRadioAutoChannelEnable( void )
{
    INT ret;
    INT radioIndex = 1;     
    UT_LOG("Entering test_l1_wifi_common_hal_negative2_wifi_getRadioAutoChannelEnable...");
    UT_LOG("Invoking wifi_getRadioAutoChannelEnable(1, NULL).");
    ret = wifi_getRadioAutoChannelEnable(radioIndex, NULL);
    UT_LOG("Received return status: %i", ret);
    
    UT_ASSERT_EQUAL(ret, RETURN_ERR)
    
    UT_LOG("Exiting test_l1_wifi_common_hal_negative2_wifi_getRadioAutoChannelEnable...");
}

/**
* @brief Testing the wifi_getRadioAutoChannelEnable function when wifi_init or wifi_initWithConfig is not called.
*
* This test aims to test wifi_getRadioAutoChannelEnable behavior when it is invoked without a prior call to wifi_init or wifi_initWithConfig. This scenario should return a specific error status code which is what we expect.@n
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 084@n
* **Priority:** High@n
* @n
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console@n
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Not calling wifi_init or wifi_initWithConfig before wifi_getRadioAutoChannelEnable | radioIndex = 1, output_bool = valid buffer  | RETURN_ERR | Should be Fail |
*/
void test_l1_wifi_common_hal_negative3_wifi_getRadioAutoChannelEnable( void )
{
    BOOL output_bool;
    INT ret;
    INT radioIndex = 1;     
    UT_LOG("Entering test_l1_wifi_common_hal_negative3_wifi_getRadioAutoChannelEnable...");
    WiFi_UnInitPosReq();
    // The wifi_init or wifi_initWithConfig function is NOT called before this API. 
    UT_LOG("Invoking wifi_getRadioAutoChannelEnable(1, &output_bool).");   
    ret = wifi_getRadioAutoChannelEnable(radioIndex, &output_bool);
    UT_LOG("Received output_bool: %c and return status: %d", output_bool, ret);
    WiFi_InitPreReq();
    UT_ASSERT_EQUAL(ret, RETURN_ERR)
    
    UT_LOG("Exiting test_l1_wifi_common_hal_negative3_wifi_getRadioAutoChannelEnable...");
}

/**
* @brief To test the functionality of wifi_getRadioAutoChannelRefreshPeriod function in IoT module
*
* This unit test is designed to check if wifi_getRadioAutoChannelRefreshPeriod function returns the correct values when passed with valid arguments@n
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 085@n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | :---------: | :----------: | :--------------: | :-----: |
* | 01 | Invoke wifi_getRadioAutoChannelRefreshPeriod with radioIndex=1 | radioIndex=1, output is a valid buffer | The return status should be RETURN_OK | Should be successful |
*/
void test_l1_wifi_common_hal_positive1_getRadioAutoChannelRefreshPeriod( void )
{
    UT_LOG("Entering test_l1_wifi_common_hal_positive1_getRadioAutoChannelRefreshPeriod...");
    ULONG output = 0;
    INT ret;	
	INT radioIndex = 1;
    UT_LOG("Invoking wifi_getRadioAutoChannelRefreshPeriod with radioIndex = 1. Output pointer is valid.");
    ret = wifi_getRadioAutoChannelRefreshPeriod(radioIndex, &output);
    UT_LOG("Returned status is %d", ret);
    UT_ASSERT_EQUAL(ret, RETURN_OK); 
	if((output < 0) && (output > 4294967295))
	{
	    UT_LOG("failed due to invalid output_ulong : %lu",output);
        UT_FAIL("failed due to invalid output_ulong");		
	}
    UT_LOG("Exiting test_l1_wifi_common_hal_positive1_getRadioAutoChannelRefreshPeriod...");
}

/**
* @brief This is a test for the wifi_getRadioAutoChannelRefreshPeriod function under negative testing with invalid parameters.
*
* In this test, the wifi_getRadioAutoChannelRefreshPeriod function is called with invalid parameters. This is to verify how the function reacts to invalid inputs, ensuring it returns an error and does not produce undesired effects.@n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 086 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | :---------: | :----------: | :--------------: | :-----: |
* | 01 | Invoke wifi_getRadioAutoChannelRefreshPeriod API with INvalid radioIndex as 2 and output pointer as NULL | radioIndex=2, output pointer=NULL | RETURN_ERR | Should be Fail |
*/
void test_l1_wifi_common_hal_negative1_getRadioAutoChannelRefreshPeriod( void )
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative1_getRadioAutoChannelRefreshPeriod...");
    INT ret;
	INT radioIndex = 2;	
    UT_LOG("Invoking wifi_getRadioAutoChannelRefreshPeriod with radioIndex = 2. Output pointer is NULL.");
    ret = wifi_getRadioAutoChannelRefreshPeriod(radioIndex, NULL);
    UT_LOG("Returned status is %d", ret);
    UT_ASSERT_EQUAL(ret, RETURN_ERR);
    UT_LOG("Exiting test_l1_wifi_common_hal_negative1_getRadioAutoChannelRefreshPeriod...");
}

/**
 * @brief Tests getting auto channel refresh period without prior wifi initialization 
 *
 * This function tests the behavior of the wifi_getRadioAutoChannelRefreshPeriod API when invoked without initializing wifi. It checks whether the API returns appropriate error status.@n
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 087 @n
 * **Priority:** High @n@n
 * 
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
 * 
 * **Test Procedure:**@n
 * | Variation / Step | Description | Test Data |Expected Result |Notes |
 * | :----: | :---------: | :----------: | :--------------: | :-----: |
 * | 01 | Invoke wifi_getRadioAutoChannelRefreshPeriod without initializing WiFi. | input1 = 1, output = address to ULONG variable | RETURN_ERR | Should be Fail |
 *
 */
void test_l1_wifi_common_hal_negative2_getRadioAutoChannelRefreshPeriod( void )
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative2_getRadioAutoChannelRefreshPeriod...");
    ULONG output = 0;
	INT radioIndex = 1;	
    INT ret;
	
	WiFi_UnInitPosReq();
    UT_LOG("Invoking wifi_getRadioAutoChannelRefreshPeriod without calling wifi_init(). Output pointer is valid. ");
    ret = wifi_getRadioAutoChannelRefreshPeriod(radioIndex, &output);
    UT_LOG("Returned status is %d", ret);
	WiFi_InitPreReq();
    UT_ASSERT_EQUAL(ret, RETURN_ERR);
    UT_LOG("Exiting test_l1_wifi_common_hal_negative2_getRadioAutoChannelRefreshPeriod...");
}

/**
* @brief This test will verify if the wifi_getRadioAutoChannelRefreshPeriod function returns the expected results under given conditions
*
* This test will call wifi_getRadioAutoChannelRefreshPeriod function with a test input and verifies its return value. The aim is to validate whether this function correctly identifies and returns the refresh period for the auto channel selection @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 088 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | :---------: | :----------: | :--------------: | :-----: |
* | 01 | Invoke wifi_getRadioAutoChannelRefreshPeriod with the radioIndex set to 1 and the max possible value for the output pointer | radioIndex = 1, output = 4294967295 | RETURN_OK | The test should be successful |
*/
void test_l1_wifi_common_hal_positive2_getRadioAutoChannelRefreshPeriod( void )
{
    UT_LOG("Entering test_l1_wifi_common_hal_positive2_getRadioAutoChannelRefreshPeriod...");
    ULONG output = 4294967295;
    INT ret;
	INT radioIndex = 1;	
    UT_LOG("Invoking wifi_getRadioAutoChannelRefreshPeriod with radioIndex = 1 and max possible value. Output pointer is valid.");
    ret = wifi_getRadioAutoChannelRefreshPeriod(radioIndex, &output);
    UT_LOG("Returned status is %d", ret);
    UT_ASSERT_EQUAL(ret, RETURN_OK); 
	if((output < 0) && (output > 4294967295))
	{
	    UT_LOG("failed due to invalid output : %lu",output);
        UT_FAIL("failed due to invalid output");		
	}
    UT_LOG("Exiting test_l1_wifi_common_hal_positive2_getRadioAutoChannelRefreshPeriod...");
}

/**
* @brief Test function to verify the behavior of wifi_getRadioAutoChannelRefreshPeriod when passed NULL as output
*
* This unit test aims to verify the negative scenario where wifi_getRadioAutoChannelRefreshPeriod API is invoked with null pointer for output. It inspects the return value to be RETURN_ERR when the call is not successful.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 089 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke the function wifi_getRadioAutoChannelRefreshPeriod with invalid argument | index = 1, output = NULL |RETURN_ERR | Should be Fail |
*/
void test_l1_wifi_common_hal_negative3_getRadioAutoChannelRefreshPeriod( void )
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative3_getRadioAutoChannelRefreshPeriod...");
    INT ret;	
	INT radioIndex = 1;	
    UT_LOG("Invoking wifi_getRadioAutoChannelRefreshPeriod with null pointer for output.");
    ret = wifi_getRadioAutoChannelRefreshPeriod(radioIndex, NULL);
    UT_LOG("Returned status is %d", ret);
    UT_ASSERT_EQUAL(ret, RETURN_ERR);
    UT_LOG("Exiting test_l1_wifi_common_hal_negative3_getRadioAutoChannelRefreshPeriod...");
}

/**
* @brief  This test validates the correct functionality of the `wifi_getRadioGuardInterval` function  
*
* The objective of this test is to validate that the function wifi_getRadioGuardInterval returns the correct output when invoked with valid parameters. This function is critical to retrieve the radio guard  interval information from the specified radio and hence, should work correctly for smooth operation.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 090 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console@n
* 
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | :---------: | :----------: | :--------------: | :-----: |
* | 01 | Invoke the wifi_getRadioGuardInterval function with valid parameters | radioIndex = 1, output buffer is valid | RETURN_OK | Should be successful |
*/
void test_l1_wifi_common_hal_positive1_wifi_getRadioGuardInterval(void)
{
    UT_LOG("Entering test_l1_wifi_common_hal_positive1_wifi_getRadioGuardInterval...\n");
    
    INT radioIndex = 1;
    CHAR output_string[10];
    INT result;
	
    UT_LOG("Invoking wifi_getRadioGuardInterval with valid radioIndex, output buffer is valid."); 
    result = wifi_getRadioGuardInterval(radioIndex, output_string);

    UT_LOG("Return status is: %d\n", result);
    UT_LOG("Radio Guard Interval is: %s\n", output_string);
    UT_ASSERT_EQUAL(result, RETURN_OK);
    if((strcmp(output_string,"400nsec") != 0) &&  (strcmp(output_string,"800nsec") != 0) && (strcmp(output_string,"Auto") != 0))
	{
	    UT_LOG("failed due to invalid output_string : %s",output_string);
        UT_FAIL("failed due to invalid output_string");
	}		
    UT_LOG("Exiting test_l1_wifi_common_hal_positive1_wifi_getRadioGuardInterval...\n");
}

/**
 * @brief Test case for wifi_getRadioGuardInterval API using invalid radio index.
 *
 * This test aims to validate the 'wifi_getRadioGuardInterval' API when it is invoked with an invalid radio index. The test ensures that the proper error handling and return status is given when the API is invoked with out of bounds index.@n
 *
 * **Test Group ID:** Basic: 01 @n
 * **Test Case ID:** 091 @n
 * **Priority:** High @n@n
 * 
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
 * 
 * **Test Procedure:**@n
 * | Variation / Step | Description | Test Data |Expected Result |Notes |
 * | :----: | :---------: | :----------: | :--------------: | :-----: |
 * | 01 | Invoke wifi_getRadioGuardInterval API with invalid radio index. Ensure the output buffer is valid. | Radio Index = 2 output_string = Valid Buffer| RETURN_ERR | Should be Fail |
 */
void test_l1_wifi_common_hal_negative1_wifi_getRadioGuardInterval(void)
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative1_wifi_getRadioGuardInterval...\n");

    INT radioIndex = 2;
    CHAR output_string[10];
    INT result;
	
    UT_LOG("Invoking wifi_getRadioGuardInterval with invalid radioIndex, output buffer is valid.");
    result = wifi_getRadioGuardInterval(radioIndex, output_string);

    UT_LOG("Return status is: %d\n", result);
    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative1_wifi_getRadioGuardInterval...\n");
}

/**
* @brief This is a test for the function wifi_getRadioGuardInterval
*
* This test case is designed to validate the functionality of wifi_getRadioGuardInterval when provided with invalid output buffer. It checks whether the function behaves as expected when dealing with abnormal scenarios.@n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 092 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.@n
* 
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | :---------: | :----------: | :--------------: | :-----: |
* | 01 | Invoke wifi_getRadioGuardInterval function with valid radio index but null output buffer | radioIndex = 1, output buffer = NULL | RETURN_ERR | Should be Fail |
*/
void test_l1_wifi_common_hal_negative2_wifi_getRadioGuardInterval(void)
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative2_wifi_getRadioGuardInterval...\n");
    INT radioIndex = 1;
    CHAR *output_string = NULL;
    INT result;
	
    UT_LOG("Invoking wifi_getRadioGuardInterval with valid radioIndex, output buffer is NULL.");
    result = wifi_getRadioGuardInterval(radioIndex, output_string);
    UT_LOG("Return status is: %d\n", result);
    UT_ASSERT_EQUAL(result, RETURN_ERR);
    UT_LOG("Exiting test_l1_wifi_common_hal_negative2_wifi_getRadioGuardInterval...\n");
}

/**
* @brief Tests that the API wifi_getRadioGuardInterval responds correctly when provided with an uninitialized output buffer.
*
* This test validates the error handling of the wifi_getRadioGuardInterval function. This function is expected to return an error when an uninitialized buffer is passed as the output string parameter.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 093 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.@n
* 
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | :---------: | :----------: | :--------------: | :-----: |
* | 01 | Call wifi_getRadioGuardInterval with valid radioIndex and uninitialized buffer | radioIndex = 1, output_string = uninitialized | RETURN_ERR | Should be Fail |
*/
void test_l1_wifi_common_hal_negative3_wifi_getRadioGuardInterval(void)
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative3_wifi_getRadioGuardInterval...\n");
    
    INT radioIndex = 1;
    CHAR *output_string;
    INT result;
	
    UT_LOG("Invoking wifi_getRadioGuardInterval with valid radioIndex, output buffer is uninitialized.");
    result = wifi_getRadioGuardInterval(radioIndex, output_string);

    UT_LOG("Return status is: %d\n", result);
    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative3_wifi_getRadioGuardInterval...\n");
}

/**
 * @brief Tests the wifi_getRadioGuardInterval function without initialization
 * 
 * This test aims to verify the proper error handling of the wifi_getRadioGuardInterval function when it's called without firstly calling the wifi_init() or wifi_initWithConfig() functions@n
 *
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 094@n
 * **Priority:** High @n@n
 * 
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
 * 
 * **Test Procedure:**@n
 * | Variation / Step | Description | Test Data |Expected Result |Notes |
 * | :----: | :---------: | :----------: | :--------------: | :-----: |
 * | 01 | Invoke wifi_getRadioGuardInterval without previously calling wifi_init() or wifi_initWithConfig(). | radioIndex = 1, output_string[] | Return status should be RETURN_ERR | Should return an error |
 */
void test_l1_wifi_common_hal_negative4_wifi_getRadioGuardInterval(void)
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative4_wifi_getRadioGuardInterval...\n");

    /* the test setup should ensure that wifi_init() or wifi_initWithConfig() has not been called */

    INT radioIndex = 1;
    CHAR output_string[10];
    INT result;	
	
	WiFi_UnInitPosReq();
    UT_LOG("Invoking wifi_getRadioGuardInterval without previously calling wifi_init() or wifi_initWithConfig()");
    result = wifi_getRadioGuardInterval(radioIndex, output_string);
    UT_LOG("Invoking wifi_getRadioGuardInterval without previously calling wifi_init() or wifi_initWithConfig(). Return status is: %d\n", result );
	WiFi_InitPreReq();
    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative4_wifi_getRadioGuardInterval...\n");
}

/**
* @brief Test for wifi_getRadioOperatingChannelBandwidth() function
*
* This unit test case checks if the wifi_getRadioOperatingChannelBandwidth() API works as intended by invoking it with valid radioIndex and output_string.
* 
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 095 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:**
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | :---------: | :----------: | :--------------: | :-----: |
* | 01 | Invoke wifi_getRadioOperatingChannelBandwidth with valid radioIndex and output_string | radioIndex = 1, output_string= initialized empty string | The function should return RETURN_OK and output_string should get updated with the bandwidth value | Validate the bandwidth value  |
*/
void test_l1_wifi_common_hal_positive1_wifi_getRadioOperatingChannelBandwidth(void)
{
    UT_LOG("Entering test_l1_wifi_common_hal_positive1_wifi_getRadioOperatingChannelBandwidth...");

    INT radioIndex = 1;
    CHAR output_string[50];
    INT returnValue;
    // Call the wifi_init or wifi_initWithConfig function before calling the tested API
    UT_LOG("Invoking wifi_getRadioOperatingChannelBandwidth with valid radioIndex and output_string.");
    returnValue = wifi_getRadioOperatingChannelBandwidth(radioIndex, output_string);

    UT_LOG("Return status: %d", returnValue);
    UT_LOG("output value: %s", output_string);	
    UT_ASSERT_EQUAL(returnValue, RETURN_OK);
    if( (output_string != NULL) && (check_value(output_string,bandwidth,5) != 1))
	{
	    UT_LOG("failed due to invalid output_string : %s",output_string);
        UT_FAIL("failed due to invalid output_string");
	}
    UT_LOG("Exiting test_l1_wifi_common_hal_positive1_wifi_getRadioOperatingChannelBandwidth...");
}

/**
 * @brief Test to verify the correct behavior of wifi_getRadioOperatingChannelBandwidth API when an invalid radio index is given.
 *
 * The test checks if the return value of wifi_getRadioOperatingChannelBandwidth API matches the expected return error  code when invoked with a non-valid radio index. This scenario tests the robustness of the API against incorrect inputs.
 *
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 096@n
 * **Priority:** High @n@n
 * 
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
 * 
 * **Test Procedure:**@n
 * | Variation / Step | Description | Test Data |Expected Result |Notes |
 * | :----: | :---------: | :----------: | :--------------: | :-----: |
 * | 01 | Invoke wifi_getRadioOperatingChannelBandwidth with non-valid radioIndex and a valid output string. | radioIndex = 2, output_string = an empty string | RETURN_ERR| If the radioIndex is not valid, the function should return an error. |
 *
 */
void test_l1_wifi_common_hal_negative1_wifi_getRadioOperatingChannelBandwidth(void)
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative1_wifi_getRadioOperatingChannelBandwidth...");

    INT radioIndex = 2;   // non-valid index
    CHAR output_string[50];
    INT returnValue;
    // Call the wifi_init or wifi_initWithConfig function before calling the tested API
    UT_LOG("Invoking wifi_getRadioOperatingChannelBandwidth with non-valid radioIndex and valid output_string.");
    returnValue = wifi_getRadioOperatingChannelBandwidth(radioIndex, output_string);

    UT_LOG("Return value: %d", returnValue);
    UT_ASSERT_EQUAL(returnValue, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative1_wifi_getRadioOperatingChannelBandwidth...");
}

/**
* @brief Tests the "wifi_getRadioOperatingChannelBandwidth" function with a valid radio index and NULL output string.
*
* This test validates the proper error handling and integrity of the "wifi_getRadioOperatingChannelBandwidth" API when given a valid radio index and a NULL output string@n
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 097@n
* **Priority:** High@n
* @n
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_getRadioOperatingChannelBandwidth API with valid radioIndex and NULL output string | radioIndex = 1, output_string = NULL | returnValue should be RETURN_ERR | Test should be successful |
*/
void test_l1_wifi_common_hal_negative2_wifi_getRadioOperatingChannelBandwidth(void)
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative2_wifi_getRadioOperatingChannelBandwidth...");

    INT radioIndex = 1;
    CHAR *output_string = NULL;   // NULL buffer
    INT returnValue;
    UT_LOG("Invoking wifi_getRadioOperatingChannelBandwidth with valid radioIndex and NULL output_string. ");
    returnValue = wifi_getRadioOperatingChannelBandwidth(radioIndex, output_string);

    UT_LOG("Return value: %d", returnValue);
    UT_ASSERT_EQUAL(returnValue, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative2_wifi_getRadioOperatingChannelBandwidth...");
}

/**
 * @brief Unit test for wifi_getRadioOperatingChannelBandwidth API with negative scenario.
 *
 * This test case verifies the behavior of wifi_getRadioOperatingChannelBandwidth API when wifi_init or wifi_initWithConfig has not been called first.@n
 *
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 098@n
 * **Priority:** High@n
 * @n
 * **Pre-Conditions:** None@n
 * **Dependencies:** None@n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
 * @n
 * **Test Procedure:**@n
 * | Variation / Step | Description | Test Data |Expected Result |Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Call wifi_getRadioOperatingChannelBandwidth API without calling wifi_init or wifi_initWithConfig first | radioIndex = 1 , output_string = Valid buffer | RETURN_ERR | Should be Fail |
 */
void test_l1_wifi_common_hal_negative3_wifi_getRadioOperatingChannelBandwidth(void)
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative3_wifi_getRadioOperatingChannelBandwidth...");

    INT radioIndex = 1;
    CHAR output_string[50];
    INT returnValue;
	
    WiFi_UnInitPosReq();
    // Do not call the wifi_init or wifi_initWithConfig function before calling the tested API
    UT_LOG("Invoking wifi_getRadioOperatingChannelBandwidth without calling wifi_init or wifi_initWithConfig.");
    returnValue = wifi_getRadioOperatingChannelBandwidth(radioIndex, output_string);

    UT_LOG("Return value: %d", returnValue);
	WiFi_InitPreReq();
    UT_ASSERT_EQUAL(returnValue, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative3_wifi_getRadioOperatingChannelBandwidth...");
}

/**
* @brief Tests the operation of the wifi_getRadioOperatingChannelBandwidth API with invalid index data type.
*
* This test verifies the wifi_getRadioOperatingChannelBandwidth function by passing a radioIndex of -ve type. This API is expected to handle unexpected data type gracefully, by returning an error.@n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 099 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.
* 
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | :---------: | :----------: | :--------------: | :-----: |
* | 01 | run wifi_getRadioOperatingChannelBandwidth API with Invalid radioIndex | radioIndex = -1 | RETURN_ERR | Should be Fail |
*/
void test_l1_wifi_common_hal_negative4_wifi_getRadioOperatingChannelBandwidth(void)
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative4_wifi_getRadioOperatingChannelBandwidth...");

    FLOAT radioIndex = -1;  // different data type
    CHAR output_string[50];
    INT returnValue;
    // Call the wifi_init or wifi_initWithConfig function before calling the tested API
    UT_LOG("Invoking wifi_getRadioOperatingChannelBandwidth with invalid radioIndex ");
    returnValue = wifi_getRadioOperatingChannelBandwidth(radioIndex, output_string);

    UT_LOG("Return value: %d", returnValue);
    UT_ASSERT_EQUAL(returnValue, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative4_wifi_getRadioOperatingChannelBandwidth...");
}

/**
* @brief Unit test for the function wifi_getRadioExtChannel
*
* This test verifies if the function wifi_getRadioExtChannel correctly fetches the extended radio channel information 
* for a given radio index. The function is invoked with valid input parameters and result is cross-verified with expected RETURN_OK.@n
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 100@n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.@n
* 
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | :---------: | :----------: | :--------------: | :-----: |
* | 01 | Invoke wifi_getRadioExtChannel with valid parameters | radioIndex = 1 , output_string buffer size = 100 | RETURN_OK | Should be successful |
*/
void test_l1_wifi_common_hal_positive1_wifi_getRadioExtChannel( void )
{
    UT_LOG("Entering test_l1_wifi_common_hal_positive1_wifi_getRadioExtChannel...");

    INT radioIndex = 1;
    CHAR output_string[100]; // A buffer large enough for returned string
    INT result;	
	
    UT_LOG("Invoking wifi_getRadioExtChannel with valid parameters. The radio index is 1 and the output_string is a valid buffer.");
    result = wifi_getRadioExtChannel(radioIndex, output_string);
    UT_LOG("The returned string is %s and the return status is %d", output_string, result);
    UT_ASSERT_EQUAL(result, RETURN_OK);
    if((strcmp(output_string,"AboveControlChannel") != 0) && (strcmp(output_string,"BelowControlChannel") != 0) && (strcmp(output_string,"Auto") != 0))
	{
	    UT_LOG("failed due to invalid output_string : %s",output_string);
        UT_FAIL("failed due to invalid output_string");
	}
    UT_LOG("Exiting test_l1_wifi_common_hal_positive1_wifi_getRadioExtChannel...");
}

/**
* @brief Tests the wifi_getRadioExtChannel function with an invalid radio index
*
* This test validates if the wifi_getRadioExtChannel function will return an error when invoked with an invalid radio index. This ensures that error handling in the function is robust. 
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 101@n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | :---------: | :----------: | :--------------: | :-----: |
* | 01 | Invoke wifi_getRadioExtChannel with invalid radio index (0). The output_string is a valid buffer. | radioIndex = 0, output_string = valid buffer | Expected result is RETURN_ERR| This test ensures that the function properly handles invalid parameters |
*/
void test_l1_wifi_common_hal_negative1_wifi_getRadioExtChannel( void )
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative1_wifi_getRadioExtChannel...");
    
	INT result;
    INT radioIndex = 0;
    CHAR output_string[100]; 
	
    UT_LOG("Invoking wifi_getRadioExtChannel with invalid radio index. The output_string is a valid buffer.");
    result = wifi_getRadioExtChannel(radioIndex, output_string);
    UT_LOG("The return status is %d", result);

    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative1_wifi_getRadioExtChannel...");
}

/**
* @brief Tests wifi_getRadioExtChannel API when radioIndex is invalid
*
* Tests the negative case of the wifi_getRadioExtChannel API when an invalid radioIndex is passed. The goal is to ensure the function handles invalid input properly.@n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 102 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | :---------: | :----------: | :--------------: | :-----: |
* | 01 | Invoking wifi_getRadioExtChannel with invalid radio index. The output_string is a valid buffer. | radioIndex = 2, output_string = valid buffer | RETURN_ERR | Should be Fail |
*/
void test_l1_wifi_common_hal_negative2_wifi_getRadioExtChannel( void )
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative2_wifi_getRadioExtChannel...");

    INT radioIndex = 2;
    CHAR output_string[100]; 
    INT result;	
	
    UT_LOG("Invoking wifi_getRadioExtChannel with invalid radio index. The output_string is a valid buffer.");
    result = wifi_getRadioExtChannel(radioIndex, output_string);
    UT_LOG("The return status is %d", result);
    UT_ASSERT_EQUAL(result, RETURN_ERR);
    UT_LOG("Exiting test_l1_wifi_common_hal_negative2_wifi_getRadioExtChannel...");
}

/**
* @brief Testing wifi_getRadioExtChannel with null output string
*
* In this test, we invoke wifi_getRadioExtChannel() with a null output string and verify if it handles this properly by returning a FAILURE@n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 103 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | :---------: | :----------: | :--------------: | :-----: |
* | 01 | Invoke wifi_getRadioExtChannel with null output string | radioIndex = 1, output_string = NULL | RETURN_ERR | Should be Fail |
*/
void test_l1_wifi_common_hal_negative3_wifi_getRadioExtChannel( void )
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative3_wifi_getRadioExtChannel...");

    INT radioIndex = 1;
    CHAR *output_string = NULL;
    INT result;
	
    UT_LOG("Invoking wifi_getRadioExtChannel with null output string.");   
    result = wifi_getRadioExtChannel(radioIndex, output_string);
    UT_LOG("The return status is %d", result);

    UT_ASSERT_EQUAL(result, RETURN_ERR);
    UT_LOG("Exiting test_l1_wifi_common_hal_negative3_wifi_getRadioExtChannel...");
}

/**
* @brief This test verifies the negative behaviour of wifi_getRadioExtChannel function.

* This test is designed to validate the return value when wifi_getRadioExtChannel is invoked before calling wifi_init or wifi_initWithConfig. A successful test is ensured when the function returns error. Hence, the test aims at verifying failure case and handling of the function.@n
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 104@n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | :---------: | :----------: | :--------------: | :-----: |
* | 01 | Invoke wifi_getRadioExtChannel before calling wifi_init or wifi_initWithConfig | radioIndex = 1 , output_string = Valid buffer | RETURN_ERR | Should be Fail |
*/
void test_l1_wifi_common_hal_negative4_wifi_getRadioExtChannel( void )
{
    // Not calling wifi_init() or wifi_initWithConfig() before testing
    UT_LOG("Entering test_l1_wifi_common_hal_negative4_wifi_getRadioExtChannel...");

    INT radioIndex = 1;
    CHAR output_string[100]; 
    INT result;	
	
    WiFi_UnInitPosReq();
    UT_LOG("Invoking wifi_getRadioExtChannel before calling wifi_init or wifi_initWithConfig.");
    result = wifi_getRadioExtChannel(radioIndex, output_string);
    UT_LOG("The return status is %d", result);
    WiFi_InitPreReq();
    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative4_wifi_getRadioExtChannel...");
}

/**
* @brief This test is designed to check the successful execution of the function wifi_getRadioMCS
*
* It validates the function wifi_getRadioMCS by providing valid radioIndex and verifying the output_INT and status.
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 105@n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | :---------: | :----------: | :--------------: | :-----: |
* | 01 | Invoke wifi_getRadioMCS with valid radioIndex and valid status pointer | radioIndex = 1, status pointer = valid | RETURN_OK | Should be successful |
*/
void test_l1_wifi_common_hal_positive1_wifi_getRadioMCS( void )
{
    UT_LOG("Entering test_l1_wifi_common_hal_positive1_wifi_getRadioMCS...");

    INT radioIndex = 1;
    INT output_INT;
    INT status;
    //wifi_initWithConfig();
    UT_LOG("Invoking wifi_getRadioMCS with valid radioIndex and valid output_INT pointer.");
    status = wifi_getRadioMCS(radioIndex, &output_INT);
  
    UT_LOG("return Status: %d, Output Int: %d", status, output_INT);

    UT_ASSERT_EQUAL(status, RETURN_OK);
	if((output_INT >= 0) && (output_INT <= 31))
	{
	    UT_LOG("valid RadioMCS %d ",output_INT);
	}
	else if((output_INT >= 0) && (output_INT <= 9))
	{
	    UT_LOG("valid RadioMCS %d ",output_INT);
	}
	else if((output_INT >= 1) && (output_INT <= 11))
	{
	    UT_LOG("valid RadioMCS %d ",output_INT);
	}
    else
	{
	    UT_LOG("invalid RadioMCS %d ",output_INT);
	    UT_FAIL("invalid RadioMCS");		
	}		

    UT_LOG("Exiting test_l1_wifi_common_hal_positive1_wifi_getRadioMCS...");

}

/**
* @brief Test the behavior of wifi_getRadioMCS API with invalid arguments
*
* This unit test checks the robustness of wifi_getRadioMCS API when invoked with an invalid radioIndex and a valid output_INT pointer.The function is expected to handle this scenario gracefully and return appropriate error. @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 106 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | :---------: | :----------: | :--------------: | :-----: |
* | 01 | Invoke wifi_getRadioMCS API with invalid radioIndex and valid output_INT pointer | radioIndex = 2, output_INT = uninitialized | RETURN_ERR | Should be Fail |
*/
void test_l1_wifi_common_hal_negative1_wifi_getRadioMCS(void)
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative1_wifi_getRadioMCS...");

    INT radioIndex = 2;
    INT output_INT;
    INT status;	
	
    UT_LOG("Invoking wifi_getRadioMCS with invalid radioIndex and valid output_INT pointer.");
    status = wifi_getRadioMCS(radioIndex, &output_INT);

    UT_LOG("Retrun Status: %d", status);

    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative1_wifi_getRadioMCS...");
}

/**
* @brief Tests the error handling behavior of wifi_getRadioMCS function when passed a NULL pointer.
*
* This test checks whether wifi_getRadioMCS returns an error when it is invoked with a NULL output pointer.@n
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 107@n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking wifi_getRadioMCS with valid radioIndex and NULL output_INT pointer. | radioIndex = 1, output_INT pointer = NULL | RETURN_ERR | Should be Fail |
*/
void test_l1_wifi_common_hal_negative2_wifi_getRadioMCS( void )
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative2_wifi_getRadioMCS...");

    INT radioIndex = 1;
    INT status;	
	
    UT_LOG("Invoking wifi_getRadioMCS with valid radioIndex and NULL output_INT pointer.");
    status = wifi_getRadioMCS(radioIndex, NULL);
    
    UT_LOG("Retrun Status: %d", status);

    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative2_wifi_getRadioMCS...");

}

/**
* @brief Test to verify the functionality of wifi_getRadioMCS.
*
* This test case checks the negative case where wifi_getRadioMCS is called without previous calls to wifi_init or wifi_initWithConfig.@n
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 108@n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.@n
* 
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_getRadioMCS API with the radioIndex set to 1 without initializing WiFi | radioIndex = 1 | RETURN_ERR | Should be Fail |
*/
void test_l1_wifi_common_hal_negative3_wifi_getRadioMCS( void )
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative3_wifi_getRadioMCS...");

    INT radioIndex = 1;
    INT output_INT;
    INT status;	
	
    WiFi_UnInitPosReq();
    UT_LOG("Invoking wifi_getRadioMCS without calling wifi_init or wifi_initWithConfig. ");
    status = wifi_getRadioMCS(radioIndex, &output_INT);
 
    UT_LOG("Return Status: %d", status);
    WiFi_InitPreReq(); 
    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative3_wifi_getRadioMCS...");
}

/**
* @brief Test if wifi_getRadioTransmitPowerSupported method returns expected output when invoked with valid radioIndex.
*
* This test invokes the wifi_getRadioTransmitPowerSupported method with valid radioIndex and validates if the returned 'output_list' buffer is filled with expected data.
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 109@n
* **Priority:** High@n@n
* 
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | :---------: | :----------: | :--------------: | :-----: |
* | 01 | Invoke wifi_getRadioTransmitPowerSupported method with valid radioIndex | radioIndex = 1 | RETURN_OK | The test should be successful |
*/
void test_l1_wifi_common_hal_positive1_wifi_getRadioTransmitPowerSupported( void )
{
    UT_LOG("Entering test_l1_wifi_common_hal_positive1_wifi_getRadioTransmitPowerSupported...");

    INT radioIndex = 1;
    CHAR output_list[50];
    int return_status;	
	
    UT_LOG("Invoking wifi_getRadioTransmitPowerSupported with valid radioIndex 1");    
    return_status = wifi_getRadioTransmitPowerSupported(radioIndex, output_list);

    UT_LOG("return status: %d, output_list: %s", return_status, output_list);
    UT_ASSERT_EQUAL(return_status, RETURN_OK);

    UT_LOG("Exiting test_l1_wifi_common_hal_positive1_wifi_getRadioTransmitPowerSupported...");
}

/**
* @brief Test Case 110: Negative Test1 - wifi_getRadioTransmitPowerSupported with invalid radioIndex
*
* This function tests the wifi_getRadioTransmitPowerSupported API for the scenario when invalid radioIndex is given as input. The API is expected to handle the negative test scenario where an invalid value of radioIndex is input.@n
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 110@n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 |Test the wifi_getRadiotransmitPowerSupported API with invalid radioIndex | radioIndex = 0 |  RETURN_ERR | The API should handle incorrect inputs, especially for the radioIndex|
*/
void test_l1_wifi_common_hal_negative1_wifi_getRadioTransmitPowerSupported( void )
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative1_wifi_getRadioTransmitPowerSupported...");

    INT radioIndex = 0;
    CHAR output_list[50];
    int return_status;	
	
    UT_LOG("Invoking wifi_getRadioTransmitPowerSupported with invalid radioIndex 0");
    return_status = wifi_getRadioTransmitPowerSupported(radioIndex, output_list);
    
    UT_LOG("return status: %d", return_status);
    UT_ASSERT_EQUAL(return_status, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative1_wifi_getRadioTransmitPowerSupported...");
}

/**
* @brief Testing the transmit power supported by the WiFi Radio Index
*
* This test is designed to validate the 'wifi_getRadioTransmitPowerSupported' function with an invalid radioIndex. The test collects whether the return status is equal to RETURN_ERR when it's called with an invalid parameter.@n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 111 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | :---------: | :----------: | :--------------: | :-----: |
* | 01 | Invoking 'wifi_getRadioTransmitPowerSupported' with invalid radioIndex 2 | radioIndex=2 | Return status should be equal to RETURN_ERR | This step should highlight that the function properly checks for invalid inputs |
*/
void test_l1_wifi_common_hal_negative2_wifi_getRadioTransmitPowerSupported( void )
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative2_wifi_getRadioTransmitPowerSupported...");

    INT radioIndex = 2;
    CHAR output_list[50];
    int return_status;	
	
    UT_LOG("Invoking wifi_getRadioTransmitPowerSupported with invalid radioIndex 2");
    return_status = wifi_getRadioTransmitPowerSupported(radioIndex, output_list);
    
    UT_LOG("return status: %d", return_status);
    UT_ASSERT_EQUAL(return_status, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative2_wifi_getRadioTransmitPowerSupported...");
}

/**
* @brief This test verifies if wifi_getRadioTransmitPowerSupported() function handles the NULL 'output_list' buffer gracefully.
*
* It tests the situation where 'output_list' buffer is NULL and verifies if the function returns error code as expected.
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 112@n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console@n
* 
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_getRadioTransmitPowerSupported with valid radioIndex 1 and NULL 'output_list' buffer | radioIndex=1, output_list=NULL |  RETURN_ERR | Should return error as 'output_list' buffer is NULL |
*/
void test_l1_wifi_common_hal_negative3_wifi_getRadioTransmitPowerSupported( void )
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative3_wifi_getRadioTransmitPowerSupported...");

    INT radioIndex = 1;
    CHAR *output_list = NULL;
    int return_status;	
	
    UT_LOG("Invoking wifi_getRadioTransmitPowerSupported with valid radioIndex 1 and NULL 'output_list' buffer.");   
    return_status = wifi_getRadioTransmitPowerSupported(radioIndex, output_list);
    
    UT_LOG("return status: %d", return_status);
    UT_ASSERT_EQUAL(return_status, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative3_wifi_getRadioTransmitPowerSupported...");
}

/**
* @brief Test if wifi_getRadioTransmitPowerSupported method returns expected output when invoked before  wifi_init() or wifi_initWithConfig()
*
* This test invokes the wifi_getRadioTransmitPowerSupported method before wifi_init() or wifi_initWithConfig() , should return RETURN_ERR
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 113@n
* **Priority:** High@n@n
* 
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:**@n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking wifi_getRadioTransmitPowerSupported before wifi_init() or wifi_initWithConfig() | radioIndex = 1 , output_list = Valid Buffer |  RETURN_ERR  | The test should fail |
*/
void test_l1_wifi_common_hal_negative4_wifi_getRadioTransmitPowerSupported( void )
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative4_wifi_getRadioTransmitPowerSupported...");

    INT radioIndex = 1;
    CHAR output_list[50];
    int return_status;	
	
	WiFi_UnInitPosReq();
	//wifi_uninit()
    UT_LOG("Invoking wifi_getRadioTransmitPowerSupported before wifi_init() or wifi_initWithConfig()");    
    return_status = wifi_getRadioTransmitPowerSupported(radioIndex, output_list);

    UT_LOG("return status: %d, output_list: %s", return_status, output_list);
	WiFi_InitPreReq();
    UT_ASSERT_EQUAL(return_status, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative4_wifi_getRadioTransmitPowerSupported...");
}

/**
 * @brief Test to check the correct execution of wifi_getRadioTransmitPower API with valid input
 *
 * In this unit test we trigger wifi_getRadioTransmitPower API with a valid radioIndex and evaluates if the function is returning the correct transmit power level.@n
 *
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 114@n
 * **Priority:** High@n
 * 
 * **Pre-Conditions:** None @n
 * **Dependencies:** None @n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
 *
 * **Test Procedure:**@n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Invoke wifi_getRadioTransmitPower with valid radioIndex and initialized output_INT | radioIndex = 1, output_INT = 50 |  RETURN_OK | The test should be successful |
 */
void test_l1_wifi_common_hal_positive1_wifi_getRadioTransmitPower( void )
{
    UT_LOG("Entering test_l1_wifi_common_hal_positive1_wifi_getRadioTransmitPower...");

    INT radioIndex = 1;
    INT output_INT = 50;
    INT ret;	
	
    UT_LOG("Invoking wifi_getRadioTransmitPower with valid radioIndex and initialized output_INT. ");
    ret = wifi_getRadioTransmitPower(radioIndex, &output_INT);
    UT_LOG("Return status: %d", ret);

    UT_ASSERT_EQUAL(ret, RETURN_OK);
	if((output_INT < -1) || (output_INT > 100))
	{
	    UT_LOG("failed due to invalid TransmitPower : %d",output_INT);
        UT_FAIL("failed due to invalid TransmitPower");			
	}
	
    UT_LOG("Exiting test_l1_wifi_common_hal_positive1_wifi_getRadioTransmitPower...");
}

/**
* @brief Testing negative scenarios of wifi_getRadioTransmitPower() function call
*
* This test case is designed to test negative scenarios of wifi_getRadioTransmitPower() function call. This function is expected to return an error when called with an invalid radio index. It is important to verify whether function properly handles these types of edge case scenarios. Also, this function being a critical part of the WIFI HAL component of system, it is necessary to ensure that it can withstand with invalid arguments without crash or improper behaviour, which enhances the robustness of the system.@n
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 115@n
* **Priority:** High@n@n
* 
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | :---------: | :----------: | :--------------: | :-----: |
* | 01 | Invoke wifi_getRadioTransmitPower API is invoked with invalid argument, in this case invalid radio index | radioIndex = 2 |  RETURN_ERR | Despite erroneous input, the API should not crash and should properly return erroneous status |
*/
void test_l1_wifi_common_hal_negative1_wifi_getRadioTransmitPower( void )
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative1_wifi_getRadioTransmitPower...");

    INT radioIndex = 2;
    INT *output_INT = (INT *) malloc(sizeof(INT));
    INT ret;	
	
    UT_LOG("Invoking wifi_getRadioTransmitPower with invalid radioIndex.");
    ret = wifi_getRadioTransmitPower(radioIndex, output_INT);
    UT_LOG("Return status: %d", ret);
    free(output_INT);
    UT_ASSERT_EQUAL(ret, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative1_wifi_getRadioTransmitPower...");
}

/**
* @brief This test is to validate the negative scenario of wifi_getRadioTransmitPower API when output_INT parameter is NULL.
*
* This unit test case is designed to validate the wifi_getRadioTransmitPower API by passing NULL value to output_INT parameter. The main aim is to test how the API is behaving when a null parameter is passed. The expected behavior of the API is to return an error.@n
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 116@n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | :---------: | :----------: | :--------------: | :-----: |
* | 01 | Invoke wifi_getRadioTransmitPower API with the second argument as NULL | radioIndex = 1, output_INT = NULL | RETURN_ERR | Should be Fail |
*/
void test_l1_wifi_common_hal_negative2_wifi_getRadioTransmitPower( void )
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative2_wifi_getRadioTransmitPower...");

    INT radioIndex = 1;
    INT *output_INT = NULL;
    INT ret;	
	
    UT_LOG("Invoking wifi_getRadioTransmitPower with NULL output_INT.");
    ret = wifi_getRadioTransmitPower(radioIndex, output_INT);
    UT_LOG("Return status: %d", ret);

    UT_ASSERT_EQUAL(ret, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative2_wifi_getRadioTransmitPower...");
}

/**
 * @brief Test to check the  execution of wifi_getRadioTransmitPower API  before wifi_init() or wifi_initWithConfig()
 *
 * In this unit test we trigger wifi_getRadioTransmitPower API before wifi_init() or wifi_initWithConfig()  with a valid radioIndex and evaluates if the function is returns RETURN_ERR @n
 *
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 117@n
 * **Priority:** High @n@n
 * 
 * **Pre-Conditions:** None@n
 * **Dependencies:** None@n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
 *
 * **Test Procedure:**@n
 * | Variation / Step | Description | Test Data |Expected Result |Notes |
 * | :----: | :---------: | :----------: | :--------------: | :-----: |
 * | 01 | Invoke wifi_getRadioTransmitPower with valid radioIndex and initialized output_INT | radioIndex = 1, output_INT = 50 | RETURN_ERR | The test should be fail |
 */
void test_l1_wifi_common_hal_negative3_wifi_getRadioTransmitPower( void )
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative3_wifi_getRadioTransmitPower...");

    INT radioIndex = 1;
    INT output_INT = 50;
    INT ret;	
	
	//wifi_uninit()
    WiFi_UnInitPosReq();	
    UT_LOG("Invoking wifi_getRadioTransmitPower before wifi_init() or wifi_initWithConfig() ");
    ret = wifi_getRadioTransmitPower(radioIndex, &output_INT);
    UT_LOG("Return status: %d", ret);
    WiFi_InitPreReq();
    UT_ASSERT_EQUAL(ret, RETURN_ERR);
    UT_LOG("Exiting test_l1_wifi_common_hal_negative3_wifi_getRadioTransmitPower...");
}

/**
 * @brief Test to check the  execution of wifi_getRadioTransmitPower API  with uninitialized output_INT pointer
 * In this unit test we trigger wifi_getRadioTransmitPower API with uninitialized output_INT pointer and   valid radioIndex and evaluates if the function is returns RETURN_ERR @n
 *
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 118@n
 * **Priority:** High@n
 * @n
 * **Pre-Conditions:** None@n
 * **Dependencies:** None@n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. 
 *
 * **Test Procedure:**@n
 * | Variation / Step | Description | Test Data |Expected Result |Notes |
 * | :----: | :---------: | :----------: | :--------------: | :-----: |
 * | 01 | Invoke wifi_getRadioTransmitPower with valid radioIndex and initialized output_INT | radioIndex = 1, output_INT = Valid buffer | RETURN_ERR | The test should be fail |
 */
void test_l1_wifi_common_hal_negative4_wifi_getRadioTransmitPower( void )
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative4_wifi_getRadioTransmitPower...");

    INT radioIndex = 1;
    INT *output_INT;
    INT ret;
	//wifi_uninit()
	
    UT_LOG("Invoking wifi_getRadioTransmitPower with uninitialized output_INT pointer ");
    ret = wifi_getRadioTransmitPower(radioIndex, output_INT);
    UT_LOG("Return status: %d", ret);

    UT_ASSERT_EQUAL(ret, RETURN_ERR);
    UT_LOG("Exiting test_l1_wifi_common_hal_negative4_wifi_getRadioTransmitPower...");
}

/**
* @brief Test for checking if wifi_getRadioIEEE80211hSupported API works as expected
*
* This test checks if wifi_getRadioIEEE80211hSupported function from the wifi module successfully returns the expected results. This test is crucial to assure that 802.11h supported radios can be correctly detected.
*
* **Test Group ID:** Basic: 01
* **Test Case ID:** 116
* **Priority:** High
* @n
* **Pre-Conditions:** None
* **Dependencies:** None
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
* @n
* **Test Procedure:**@n
* The workflow of this API is to retrieve the 802.11h support status of radios. In this scenario, the wifi_init() function will be invoked initially as a pre-condition, then call wifi_getRadioIEEE80211hSupported function.
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | ----------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_init function | None | None | Initialization of Wifi |
* | 02 | Invoke wifi_getRadioIEEE80211hSupported function | radioIndex = 1 | RETURN_OK and supported flag filled | Function should return success |
*/
void test_l1_wifi_common_hal_positive_1_wifi_getRadioIEEE80211hSupported(void)
{
    UT_LOG("Entering test_l1_wifi_common_hal_positive_1_wifi_getRadioIEEE80211hSupported...");
    
    INT radioIndex = 1;
    BOOL supported = 0;
    INT returnValue;

    //wifi_init(); // Precondition   
    UT_LOG("Invoked wifi_getRadioIEEE80211hSupported with radioIndex = 1 and valid supported pointer.");
    returnValue = wifi_getRadioIEEE80211hSupported(radioIndex, &supported);
    UT_LOG("Returned status : %d  Returned value : %c", returnValue,supported);
    UT_ASSERT_EQUAL(returnValue, RETURN_OK);
    if((supported != '0') && (supported != '1'))
	{
	    UT_LOG("failed due to invalid output : %c",supported);
        UT_FAIL("failed due to invalid output");		
	}    
    UT_LOG("Exiting test_l1_wifi_common_hal_positive_1_wifi_getRadioIEEE80211hSupported...");
}

/**
 * @brief Test the wifi_getRadioIEEE80211hSupported function with invalid inputs
 *
 * This test verifies the wifi_getRadioIEEE80211hSupported function by passing an invalid radioIndex. The expected outcome is a return value of RETURN_ERR.@n
 *
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 117@n
 * **Priority:** High@n
 * @n
 * **Pre-Conditions:** wifi_init() has been called@n
 * **Dependencies:** None@n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
 * @n
 * **Test Procedure:**@n
 * | Variation / Step | Description | Test Data |Expected Result |Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Invoke wifi_getRadioIEEE80211hSupported with invalid radioIndex = 0 | radioIndex = 0 | returnValue should be RETURN_ERR | The function should not support invalid radioIndex |
 */
void test_l1_wifi_common_hal_negative_1_wifi_getRadioIEEE80211hSupported(void)
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative_1_wifi_getRadioIEEE80211hSupported...");

   INT radioIndex = 0;    // Invalid value
   BOOL supported;
   INT returnValue;

   UT_LOG("Invoked wifi_getRadioIEEE80211hSupported with invalid radioIndex = 0.");
   returnValue = wifi_getRadioIEEE80211hSupported(radioIndex, &supported);
   UT_LOG("Returned status : %d", returnValue);
   UT_ASSERT_EQUAL(returnValue, RETURN_ERR);

   UT_LOG("Exiting test_l1_wifi_common_hal_negative_1_wifi_getRadioIEEE80211hSupported...");
}

/**
* @brief This test aims at testing the negative scenario for function wifi_getRadioIEEE80211hSupported where NULL pointer is used.
*
* This test asserts if the function wifi_getRadioIEEE80211hSupported responds correctly to the inappropriate use of NULL pointer thereby confirming the function's resilience.
* 
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 118@n
* **Priority:** High@n
* @n
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Call the method wifi_getRadioIEEE80211hSupported with NULL pointer as input parameter. | radioIndex = 1, supported = NULL | Function should return RETURN_ERR | Should be successful |
*/
void test_l1_wifi_common_hal_negative_2_wifi_getRadioIEEE80211hSupported(void)
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative_2_wifi_getRadioIEEE80211hSupported...");

    INT radioIndex = 1;
    BOOL *supported = NULL;  // Null pointer
    INT returnValue;

    wifi_init();  // Precondition
    UT_LOG("Invoked wifi_getRadioIEEE80211hSupported with Supported as NULL pointer. Expected to return RETURN_ERR.");
    returnValue = wifi_getRadioIEEE80211hSupported(radioIndex, supported);
    UT_LOG("Returned status : %d", returnValue);

    UT_ASSERT_EQUAL(returnValue, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative_2_wifi_getRadioIEEE80211hSupported...");
}

/**
* @brief Unit test for wifi_getRadioIEEE80211hSupported() API without calling wifi_init() API
*
* The test should describe whether wifi_getRadioIEEE80211hSupported() API can be called without initializing wifi module using wifi_init() API.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 119 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
*
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoke wifi_getRadioIEEE80211hSupported without calling wifi_init() API | radioIndex = 1, supported = valid buffer | RETURN_ERR should be returned | Expected to fail as wifi_init() is not called |
*/
void test_l1_wifi_common_hal_negative_3_wifi_getRadioIEEE80211hSupported(void)
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative_2_wifi_getRadioIEEE80211hSupported...");

    INT radioIndex = 1;
    BOOL supported;
    INT returnValue;
	
    WiFi_UnInitPosReq();
    UT_LOG("Invoked wifi_getRadioIEEE80211hSupported without calling wifi_init(). Expected to return RETURN_ERR.");
    returnValue = wifi_getRadioIEEE80211hSupported(radioIndex, &supported);  // No wifi_init() call
    UT_LOG("Returned status : %d", returnValue);
    WiFi_InitPreReq();
    UT_ASSERT_EQUAL(returnValue, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative_3_wifi_getRadioIEEE80211hSupported...");
}

/**
* @brief This test checks if the IEEE802.11h is enabled on the radio device
*
* This function invokes the wifi_getRadioIEEE80211hEnabled API with valid index and checks the status and value returned by the API.
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 120@n
* **Priority:** High@n@n
*
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.@n
*
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_getRadioIEEE80211hEnabled with valid index | radioIndex = 1, enable = valid buffer | RETURN_OK | Test should be successful |
*/
void test_l1_wifi_common_hal_positive1_wifi_getRadioIEEE80211hEnabled(void)
{
  UT_LOG("Entering test_l1_wifi_common_hal_positive1_wifi_getRadioIEEE80211hEnabled...");
  BOOL enable;
  INT radioIndex = 1;
  INT result;  
  

  UT_LOG("Invoking wifi_getRadioIEEE80211hEnabled with valid index.");
  result = wifi_getRadioIEEE80211hEnabled(radioIndex, &enable);
  UT_LOG("return status: %d, enable: %c ", result, enable);
  UT_ASSERT_EQUAL(result, RETURN_OK);
    if((enable != '0') && (enable != '1'))
	{
	    UT_LOG("failed due to invalid RadioIEEE80211hEnabled value : %c",enable);
        UT_FAIL("failed due to invalid RadioIEEE80211hEnabled value");		
	}
  UT_LOG("Exiting test_l1_wifi_common_hal_positive1_wifi_getRadioIEEE80211hEnabled...");
}

/**
* @brief This test verifies the behavior of the API wifi_getRadioIEEE80211hEnabled when invoked without initialization.
*
* In this test, we are checking if the API wifi_getRadioIEEE80211hEnabled returns an error when it is called before the module initialization.
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 121@n
* **Priority:** High@n@n
*
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.@n
* 
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke the API wifi_getRadioIEEE80211hEnabled without initialization | radioIndex = 1, enable = valid buffer | RETURN_ERR | This should fail as the module has not been initialized |
*/ 
void test_l1_wifi_common_hal_negative1_wifi_getRadioIEEE80211hEnabled(void)
{
  UT_LOG("Entering test_l1_wifi_common_hal_negative1_wifi_getRadioIEEE80211hEnabled...");
  BOOL enable;
  INT radioIndex = 1;
  INT result; 
  
  WiFi_UnInitPosReq();
  UT_LOG("Invoking wifi_getRadioIEEE80211hEnabled without initialization.");
  result = wifi_getRadioIEEE80211hEnabled(radioIndex, &enable);
  UT_LOG("return status: %d",result);
  WiFi_InitPreReq();
  UT_ASSERT_EQUAL(result, RETURN_ERR);
  UT_LOG("Exiting test_l1_wifi_common_hal_negative1_wifi_getRadioIEEE80211hEnabled...");
}

/**
* @brief Test to check the function wifi_getRadioIEEE80211hEnabled for negative scenario
*
* In this test, the function wifi_getRadioIEEE80211hEnabled is tested with NULL parameters to see how it handles error cases. This test is important to ensure the robustness and stability of the system.
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 122@n
* **Priority:** High@n@n
* 
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.@n
* 
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_getRadioIEEE80211hEnabled with NULL parameter | radioIndex = 1, Enabled = NULL | RETURN_ERR | Should fail |
* 
*/
void test_l1_wifi_common_hal_negative2_wifi_getRadioIEEE80211hEnabled(void)
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative2_wifi_getRadioIEEE80211hEnabled...");
    INT radioIndex = 1;
    INT result;
	
    UT_LOG("Invoking wifi_getRadioIEEE80211hEnabled with NULL parameter.");
    result = wifi_getRadioIEEE80211hEnabled(radioIndex, NULL);
    UT_LOG("Return status: %d", result);
    UT_ASSERT_EQUAL(result, RETURN_ERR);
    UT_LOG("Exiting test_l1_wifi_common_hal_negative2_wifi_getRadioIEEE80211hEnabled...", "");
}

/**
* @brief Test to validate wifi_getRadioIEEE80211hEnabled API behavior with invalid input
*
* This Test case is designed to verify the negative behavior of wifi_getRadioIEEE80211hEnabled API. The API is expected to return an error when invoked with invalid index.@n
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 123@n
* **Priority:** High@n@n
* 
* **Pre-Conditions:** None@n
* **Dependencies**: None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console@n
* 
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_getRadioIEEE80211hEnabled with invalid index | radioIndex = 2, enable = valid buffer | RETURN_ERR | This operation should fail |
*/
void test_l1_wifi_common_hal_negative3_wifi_getRadioIEEE80211hEnabled(void)
{
  UT_LOG("Entering test_l1_wifi_common_hal_negative3_wifi_getRadioIEEE80211hEnabled...");
  BOOL enable;
  INT radioIndex = 2;
  INT result;  
  
  UT_LOG("Invoked wifi_getRadioIEEE80211hEnabled with invalid index.");
  result = wifi_getRadioIEEE80211hEnabled(radioIndex, &enable);
  UT_LOG("Return  status: %d", result);
  UT_ASSERT_EQUAL(result, RETURN_ERR);
  UT_LOG("Exiting test_l1_wifi_common_hal_negative3_wifi_getRadioIEEE80211hEnabled...", "");
}

 /**
 * @brief This test case checks for positive response of wifi_getRegulatoryDomain API
 *
 * Call is made to the "wifi_getRegulatoryDomain" API with a valid parameters and verify if the function returns the correct status.
 *
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 124@n
 * **Priority:** High@n@n
 * 
 * **Pre-Conditions:** None@n
 * **Dependencies:** None@n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console@n
 * 
 * **Test Procedure:**@n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- | -------------- | ----- |
 * | 01 | Invoke wifi_getRegulatoryDomain API with valid parameters | radioIndex = 1, output_string = valid buffer | RETURN_OK | Should be successful |
 */
void test_l1_wifi_common_hal_positive1_wifi_getRegulatoryDomain(void) {
    UT_LOG("Entering test_l1_wifi_common_hal_positive1_wifi_getRegulatoryDomain...\n");
    INT radioIndex = 1;
    CHAR output_string[50];
    INT status;	
	
    UT_LOG("Invoking wifi_getRegulatoryDomain with valid parameters.");
    status = wifi_getRegulatoryDomain(radioIndex, output_string);
    UT_LOG("Return status: %d \n", status);
    UT_LOG("Return value: %s \n", output_string);	
    UT_ASSERT_EQUAL(status, RETURN_OK); 
	if((output_string[2] != ' ') && (output_string[2] != 'O') && (output_string[2] != 'I'))
	{
	    UT_LOG("Invalid 3rd octet : %c ",output_string[2]);
        UT_FAIL("Invalid 3rd octet");
	}
    UT_LOG("Exiting test_l1_wifi_common_hal_positive1_wifi_getRegulatoryDomain...\n");
}


/**
* @brief Testing wifi_getRegulatoryDomain() API for negative radioIndex
*
* In this test, we verify that the wifi_getRegulatoryDomain() function returns an error when invoked with a negative radioIndex. This is to ensure that the API correctly handles incorrect inputs.
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 125@n
* **Priority:** High@n
* @n
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoke wifi_getRegulatoryDomain with negative radioIndex | radioIndex = -1, output_string = valid buffer  | RETURN_ERR | Should fail |
*/
void test_l1_wifi_common_hal_negative1_wifi_getRegulatoryDomain(void) {
    UT_LOG("Entering test_l1_wifi_common_hal_negative1_wifi_getRegulatoryDomain...\n");
    INT radioIndex = -1;
    CHAR output_string[50];
    INT status;	
	
    UT_LOG("Invoking wifi_getRegulatoryDomain with negative radioIndex.");
    status = wifi_getRegulatoryDomain(radioIndex, output_string);
    UT_LOG("Return status: %d\n", status);
    UT_ASSERT_EQUAL(status, RETURN_ERR);
    UT_LOG("Exiting test_l1_wifi_common_hal_negative1_wifi_getRegulatoryDomain...\n");
}

/**
* @brief Test to validate wifi_getRegulatoryDomain API when there are no valid access points
*
* This test checks the scenario when the wifi_getRegulatoryDomain API call returns error for radio index 0.
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 126@n
* **Priority:** High@n@n
* 
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console@n
* 
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_getRegulatoryDomain API with radio index 0 | radioIndex = 0, output_string = valid buffer | RETURN_ERR | Should fail |
*/
void test_l1_wifi_common_hal_negative2_wifi_getRegulatoryDomain(void) {
    UT_LOG("Entering test_l1_wifi_common_hal_negative2_wifi_getRegulatoryDomain...\n");
    INT radioIndex = 0;
    CHAR output_string[50];
    INT status;	
	
    UT_LOG("Invoking wifi_getRegulatoryDomain with radioIndex as 0");
    status = wifi_getRegulatoryDomain(radioIndex, output_string);
    UT_LOG("Return status: %d\n", status);
    UT_ASSERT_EQUAL(status, RETURN_ERR);
    UT_LOG("Exiting test_l1_wifi_common_hal_negative2_wifi_getRegulatoryDomain...\n");
}

/**
* @brief Unit test for wifi_getRegulatoryDomain API with invalid radioIndex value
*
* This test attempts to fetch the regulatory domain details for 
* a radioIndex greater than 1. As per design, the function only supports 
* radioIndex 0 or 1, hence it should return an error.@n
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 127@n
* **Priority:** High@n@n
* 
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console@n
* 
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01| Invoke wifi_getRegulatoryDomain API with radio index 2  | radioIndex = 2, output_string = valid buffer | RETURN_ERR | Should fail  |
*/
void test_l1_wifi_common_hal_negative3_wifi_getRegulatoryDomain(void) {
	UT_LOG("Entering test_l1_wifi_common_hal_negative3_wifi_getRegulatoryDomain...\n");
	INT radioIndex = 2;
	CHAR output_string[50];
	INT status;	
	
	UT_LOG("Invoking wifi_getRegulatoryDomain with radioIndex greater than 1. ");
	status = wifi_getRegulatoryDomain(radioIndex, output_string);
	UT_LOG("Return status: %d\n", status);
	UT_ASSERT_EQUAL(status, RETURN_ERR);
	UT_LOG("Exiting test_l1_wifi_common_hal_negative3_wifi_getRegulatoryDomain...\n");
}
	
/**
 * @brief Test for the function wifi_getRegulatoryDomain with negative scenario 
 *
 * This test function verifies the behavior of the wifi_getRegulatoryDomain API when invoked with 
 * uninitialized output_string. It checks whether the function handles such input properly, and returns an error code.@n
 *
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 128@n
 * **Priority:** High@n@n
 * 
 * **Pre-Conditions:** None@n
 * **Dependencies:** None@n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
 * 
 * **Test Procedure:**@n
 * | Variation / Step | Description | Test Data |Expected Result |Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Invoke wifi_getRegulatoryDomain with uninitialized output_string | radioIndex = 1, output_string = uninitialized | RETURN_ERR | Should fail |
 */
void test_l1_wifi_common_hal_negative4_wifi_getRegulatoryDomain(void) {
    UT_LOG("Entering test_l1_wifi_common_hal_negative4_wifi_getRegulatoryDomain...\n");
    INT radioIndex = 1;
    CHAR *output_string;
    INT status;
	
    UT_LOG("Invoking wifi_getRegulatoryDomain with uninitialized output_string.");
    status = wifi_getRegulatoryDomain(radioIndex, output_string);
    UT_LOG("Return status: %d\n", status);
    UT_ASSERT_EQUAL(status, RETURN_ERR);
    UT_LOG("Exiting test_l1_wifi_common_hal_negative4_wifi_getRegulatoryDomain...\n");
}


/**
* @brief Testing the wifi_getRegulatoryDomain function with NULL output_string
*
* This test checks if the wifi_getRegulatoryDomain function handles a null pointer for the output_string parameter properly.
* The purpose of this unit test is to check fault tolerance of the  wifi_getRegulatoryDomain function.
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 129@n
* **Priority:** High@n@n
* 
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console@n
* 
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | ------------- | ----- |
* | 01 | Invoke wifi_getRegulatoryDomain with NULL output_string | radioIndex = 1, output_string = NULL | RETURN_ERR | Should fail |
*/
void test_l1_wifi_common_hal_negative5_wifi_getRegulatoryDomain(void) {
    UT_LOG("Entering test_l1_wifi_common_hal_negative5_wifi_getRegulatoryDomain...\n");
    INT radioIndex = 1;
    CHAR *output_string = NULL;
    INT status;	
	
    UT_LOG("Invoking wifi_getRegulatoryDomain with NULL output_string.");
    status = wifi_getRegulatoryDomain(radioIndex, output_string);
    UT_LOG("Return status: %d\n", status);
    UT_ASSERT_EQUAL(status, RETURN_ERR);
    UT_LOG("Exiting test_l1_wifi_common_hal_negative5_wifi_getRegulatoryDomain...\n");
}


/**
* @brief To test wifi_getRegulatoryDomain function without initialization 
*
* This test case is designed to test the behavior of the 'wifi_getRegulatoryDomain' function when called before initialization. A successful test case should return a specific error.
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 130@n
* **Priority:** High@n@n
* 
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console@n
* 
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_getRegulatoryDomain function before wifi_init or wifi_initWithConfig | radioIndex = 0, output_string = valid buffer | RETURN_ERR | Should fail |
*/
void test_l1_wifi_common_hal_negative6_wifi_getRegulatoryDomain(void) {
    UT_LOG("Entering test_l1_wifi_common_hal_negative6_wifi_getRegulatoryDomain...\n");
    INT radioIndex = 1;
    CHAR output_string[50];
    INT status;
	
	WiFi_UnInitPosReq();
    UT_LOG("Invoking wifi_getRegulatoryDomain before wifi_init or wifi_initWithConfig function.");
    status = wifi_getRegulatoryDomain(radioIndex, output_string);
    UT_LOG("Return status: %d\n", status);
	WiFi_InitPreReq();
    UT_ASSERT_EQUAL(status, RETURN_ERR);
    UT_LOG("Exiting test_l1_wifi_common_hal_negative6_wifi_getRegulatoryDomain...\n");
}

/**
* @brief To test the functionality of wifi_getRadioTrafficStats API
*
* The objective of this test function is to verify whether the wifi_getRadioTrafficStats API retrieves traffic statistics as expected. The test invokes the wifi_getRadioTrafficStats api with a valid radio index and output struct and checks for a successful return status.@n
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 131@n
* **Priority:** High@n@n
*
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console@n
* 
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking wifi_getRadioTrafficStats with a valid radio index and output struct buffer | radioIndex = 1, output_struct buffer = valid buffer | RETURN_OK | Should be successful|
*/
void test_l1_wifi_common_hal_positive1_wifi_getRadioTrafficStats(void) {
    UT_LOG("Entering test_l1_wifi_common_hal_positive1_wifi_getRadioTrafficStats...");
    INT radioIndex = 1;
    wifi_radioTrafficStats_t output_struct;
    INT status;
 
    UT_LOG("Invoking wifi_getRadioTrafficStats with valid radio index and valid output struct buffer.");
    status = wifi_getRadioTrafficStats(radioIndex, &output_struct);

    UT_LOG("Return status: %d", status);

    UT_ASSERT_EQUAL(status, RETURN_OK);
    if((output_struct.radio_BytesSent < 0) || (output_struct.radio_BytesSent > 18446744073709551615))
	{
	    UT_LOG("Invalid RadioTrafficStats: %lu ",output_struct.radio_BytesSent);
        UT_FAIL("Invalid RadioTrafficStats");
	}
    if((output_struct.radio_BytesReceived < 0) || (output_struct.radio_BytesReceived > 18446744073709551615))
	{
	    UT_LOG("Invalid radio_BytesReceived : %lu ",output_struct.radio_BytesReceived);
        UT_FAIL("Invalid radio_BytesReceived");
	}
    if((output_struct.radio_PacketsSent < 0) || (output_struct.radio_PacketsSent > 18446744073709551615))
	{
	    UT_LOG("Invalid radio_PacketsSent : %lu ",output_struct.radio_PacketsSent);
        UT_FAIL("Invalid radio_PacketsSent");
	}
    if((output_struct.radio_PacketsReceived < 0) || (output_struct.radio_PacketsReceived > 18446744073709551615))
	{
	    UT_LOG("Invalid radio_PacketsReceived : %lu ",output_struct.radio_PacketsReceived);
        UT_FAIL("Invalid radio_PacketsReceived");
	}
    if((output_struct.radio_ErrorsSent < 0) || (output_struct.radio_ErrorsSent > 4294967295))
	{
	    UT_LOG("Invalid radio_ErrorsSent : %lu ",output_struct.radio_ErrorsSent);
        UT_FAIL("Invalid radio_ErrorsSent");
	}
    if((output_struct.radio_ErrorsReceived < 0) || (output_struct.radio_ErrorsReceived > 4294967295))
	{
	    UT_LOG("Invalid radio_ErrorsReceived : %lu",output_struct.radio_ErrorsReceived);
        UT_FAIL("Invalid radio_ErrorsReceived");
	}
    if((output_struct.radio_DiscardPacketsSent < 0) || (output_struct.radio_DiscardPacketsSent > 4294967295))
	{
	    UT_LOG("Invalid radio_DiscardPacketsSent : %lu",output_struct.radio_DiscardPacketsSent);
        UT_FAIL("Invalid radio_DiscardPacketsSent");
	}
    if((output_struct.radio_DiscardPacketsReceived < 0) || (output_struct.radio_DiscardPacketsReceived > 4294967295))
	{
	    UT_LOG("Invalid radio_DiscardPacketsReceived : %lu",output_struct.radio_DiscardPacketsReceived);
        UT_FAIL("Invalid radio_DiscardPacketsReceived");
	}
    if((output_struct.radio_PLCPErrorCount < 0) || (output_struct.radio_PLCPErrorCount > 4294967295))
	{
	    UT_LOG("Invalid radio_PLCPErrorCount : %lu",output_struct.radio_PLCPErrorCount);
        UT_FAIL("Invalid radio_PLCPErrorCount");
	}
    if((output_struct.radio_FCSErrorCount < 0) || (output_struct.radio_FCSErrorCount > 4294967295))
	{
	    UT_LOG("Invalid radio_FCSErrorCount : %lu",output_struct.radio_FCSErrorCount);
        UT_FAIL("Invalid radio_FCSErrorCount");
	}
    if((output_struct.radio_InvalidMACCount < 0) || (output_struct.radio_InvalidMACCount > 4294967295))
	{
	    UT_LOG("Invalid radio_InvalidMACCount :%lu",output_struct.radio_InvalidMACCount);
        UT_FAIL("Invalid radio_InvalidMACCount");
	}
    if((output_struct.radio_PacketsOtherReceived < 0) || (output_struct.radio_PacketsOtherReceived > 4294967295))
	{
	    UT_LOG("Invalid radio_PacketsOtherReceived :%lu ",output_struct.radio_PacketsOtherReceived);
        UT_FAIL("Invalid radio_PacketsOtherReceived");
	}
	
    if((output_struct.radio_NoiseFloor < -110) || (output_struct.radio_NoiseFloor > 0))
	{
	    UT_LOG("Invalid radio_NoiseFloor : %d",output_struct.radio_NoiseFloor);
        UT_FAIL("Invalid radio_NoiseFloor");
	}


    if((output_struct.radio_ChannelUtilization < 0) || (output_struct.radio_ChannelUtilization > 100))
	{
	    UT_LOG("Invalid radio_ChannelUtilization : %lu",output_struct.radio_ChannelUtilization);
        UT_FAIL("Invalid radio_ChannelUtilization");
	}
	
    if((output_struct.radio_ActivityFactor < 0) || (output_struct.radio_ActivityFactor > 100))
	{
	    UT_LOG("Invalid radio_ActivityFactor : %d",output_struct.radio_ActivityFactor);
        UT_FAIL("Invalid radio_ActivityFactor");
	}

    if((output_struct.radio_CarrierSenseThreshold_Exceeded < 0) || (output_struct.radio_CarrierSenseThreshold_Exceeded > 100))
	{
	    UT_LOG("Invalid radio_CarrierSenseThreshold_Exceeded :%d",output_struct.radio_CarrierSenseThreshold_Exceeded);
        UT_FAIL("Invalid radio_CarrierSenseThreshold_Exceeded");
	}	

    if((output_struct.radio_RetransmissionMetirc < 0) || (output_struct.radio_RetransmissionMetirc > 100))
	{
	    UT_LOG("Invalid radio_RetransmissionMetirc : %d",output_struct.radio_RetransmissionMetirc);
        UT_FAIL("Invalid radio_RetransmissionMetirc");
	}

    if((output_struct.radio_MaximumNoiseFloorOnChannel < -200) || (output_struct.radio_MaximumNoiseFloorOnChannel > 0))
	{
	    UT_LOG("Invalid radio_MaximumNoiseFloorOnChannel : %d ",output_struct.radio_MaximumNoiseFloorOnChannel);
        UT_FAIL("Invalid radio_MaximumNoiseFloorOnChannel");
	}
    if((output_struct.radio_MinimumNoiseFloorOnChannel < -200) || (output_struct.radio_MinimumNoiseFloorOnChannel > 0))
	{
	    UT_LOG("Invalid radio_MinimumNoiseFloorOnChannel : %d",output_struct.radio_MinimumNoiseFloorOnChannel);
        UT_FAIL("Invalid radio_MinimumNoiseFloorOnChannel");
	}
    if((output_struct.radio_MedianNoiseFloorOnChannel < -200) || (output_struct.radio_MedianNoiseFloorOnChannel > 0))
	{
	    UT_LOG("Invalid radio_MedianNoiseFloorOnChannel : %d ",output_struct.radio_MedianNoiseFloorOnChannel);
        UT_FAIL("Invalid radio_MedianNoiseFloorOnChannel");
	}
    if((output_struct.radio_StatisticsStartTime < 0) || (output_struct.radio_StatisticsStartTime > 18446744073709551615))
	{
	    UT_LOG("Invalid radio_StatisticsStartTime : %lu",output_struct.radio_StatisticsStartTime);
        UT_FAIL("Invalid radio_StatisticsStartTime");
	}

	UT_LOG("Exiting test_l1_wifi_common_hal_positive1_wifi_getRadioTrafficStats...");
}

/**
 * @brief To test the behavior of wifi_getRadioTrafficStats API when invoked with invalid parameters
 *
 * This test verifies the wifi_getRadioTrafficStats API's error handling effectiveness when it is invoked with an invalid radio index but with a valid output struct buffer. This is important to ensure robustness of the API to handle invalid inputs.@n
 *
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 132@n
 * **Priority:** High@n@n
 * 
 * **Pre-Conditions:** None@n
 * **Dependencies:** None@n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.@n
 *
 * **Test Procedure:**@n
 * | Variation / Step | Description | Test Data |Expected Result |Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Invoke wifi_getRadioTrafficStats with invalid radio index and valid output struct buffer | radio index = 2, output struct = valid pointer | RETURN_ERR | Should fail|
 */
void test_l1_wifi_common_hal_negative1_wifi_getRadioTrafficStats(void) {
    UT_LOG("Entering test_l1_wifi_common_hal_negative1_wifi_getRadioTrafficStats...");	
    INT radioIndex = 0;
    INT status;
    wifi_radioTrafficStats_t output_struct;
	
    UT_LOG("Invoked wifi_getRadioTrafficStats with invalid radio index and valid output struct buffer.");    
    status = wifi_getRadioTrafficStats(radioIndex, &output_struct);

    UT_LOG("Return status: %d", status);

    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative1_wifi_getRadioTrafficStats...");
}

/**
* @brief Test for negative scenario of HAL function wifi_getRadioTrafficStats
*
* This test exercises the negative situations that can happen when calling wifi_getRadioTrafficStats() API by passing NULL as output struct buffer.@n
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 133@n
* **Priority:** High@n@n
* 
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console@n
* 
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_getRadioTrafficStats with valid radio index and NULL output struct buffer | radio index = 1, output struct buffer = NULL | RETURN_ERR | Should fail |
*/
void test_l1_wifi_common_hal_negative2_wifi_getRadioTrafficStats(void) {
    UT_LOG("Entering test_l1_wifi_common_hal_negative2_wifi_getRadioTrafficStats...");
    INT radioIndex = 1;	
    INT status;
	
    UT_LOG("Invoked wifi_getRadioTrafficStats with valid radio index and NULL output struct buffer.");
    status = wifi_getRadioTrafficStats(radioIndex, NULL);

    UT_LOG("Return status: %d", status);

    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative2_wifi_getRadioTrafficStats...");
}

/**
 * @brief Test the wifi_getRadioTrafficStats function handling when wifi_init() has not been executed previously
 *
 * This test will assess the capability of the wifi_getRadioTrafficStats function to handle cases when it is executed without prior execution of wifi_init() or wifi_initWithConfig()@n
 *
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 134@n
 * **Priority:** High@n@n
 * 
 * **Pre-Conditions:** None@n
 * **Dependencies:** None@n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console@n
 *
 * **Test Procedure:**@n
 * | Variation / Step | Description | Test Data |Expected Result |Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Invoke wifi_getRadioTrafficStats without executing wifi_init() or wifi_initWithConfig() | radioIndex = 1, output_struct = valid buffer | RETURN_ERR | Should fail |
 */
void test_l1_wifi_common_hal_negative3_wifi_getRadioTrafficStats(void) {
    UT_LOG("Entering test_l1_wifi_common_hal_negative3_wifi_getRadioTrafficStats...");
    INT radioIndex = 1;	
    INT status;
    wifi_radioTrafficStats_t output_struct;
	
    WiFi_UnInitPosReq();
    UT_LOG("Invoked wifi_getRadioTrafficStats without executing wifi_init()");
    status = wifi_getRadioTrafficStats(radioIndex, &output_struct);
    UT_LOG("Return status: %d", status);
    WiFi_InitPreReq();
    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative3_wifi_getRadioTrafficStats...");
}

/**
* @brief Test suit for function wifi_getSSIDName
*
* This test verifies the wifi_getSSIDName API. The function is supposed to return the SSID name of the given network identifier.@n
* The API is tested for a positive test case where a valid identifier is provided and the SSID string is successfully returned.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 135 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console. @n
* 
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking wifi_getSSIDName with valid radioIndex and buffer | radioIndex = 1, output_string = valid buffer | RETURN_OK | Should be successful |
*/
void test_l1_wifi_common_hal_positive1_wifi_getSSIDName(void) {	
    UT_LOG("Entering test_l1_wifi_common_hal_positive1_wifi_getSSIDName...\n");
	
    INT ssidIndex = 1;   
    CHAR output_string[50];
    INT ret_val;
	
    UT_LOG("Invoking wifi_getSSIDName with ssidIndex: 1.");
    ret_val = wifi_getSSIDName(ssidIndex, output_string);
	UT_LOG("Returned status : %d", ret_val);    
    UT_ASSERT_EQUAL(ret_val, RETURN_OK);
    
    UT_LOG("Exiting test_l1_wifi_common_hal_positive1_wifi_getSSIDName...\n");
}

/**
* @brief Validates the error handling of wifi_getSSIDName API 
*
* This test validates the error handling of wifi_getSSIDName API when invoked with ssidIndex as 2. 
* The main focus is to ensure the API returns an error when invoked with ssidIndex as 2.@n
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 136@n
* **Priority:** High@n@n
* 
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console@n
* 
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke the API wifi_getSSIDName with ssidIndex = 2 | ssidIndex = 2, output_string = valid buffer | RETURN_ERR | Should fail |
*/
void test_l1_wifi_common_hal_negative1_wifi_getSSIDName(void) {
    UT_LOG("Entering test_l1_wifi_common_hal_negative1_wifi_getSSIDName...\n");	
	INT ssidIndex = 2;
    CHAR output_string[50];
    INT ret_val;    

    UT_LOG("Invoking wifi_getSSIDName with ssidIndex: 2. Checking for error return status.\n");
    ret_val = wifi_getSSIDName(ssidIndex, output_string);
	UT_LOG("Returned status : %d", ret_val);
    UT_ASSERT_EQUAL(ret_val, RETURN_ERR);
    
    UT_LOG("Exiting test_l1_wifi_common_hal_negative1_wifi_getSSIDName...\n");
}

/** 
* @brief This unit test aims to validate the negative scenario in wifi_getSSIDName function call.
* 
* This test performs error-checking on wifi_getSSIDName function,
* specifically checking how function behaves when NULL is provided as an output buffer.@n
* 
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 137 @n
* **Priority:** High @n@n
* 
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If the user chose to run the test in interactive mode, then the test case has to be selected via console @n
* 
* **Test Procedure:**@n
* | Variation / Step | Description                                   | Test Data                            | Expected Result               | Notes                      |
* | :----:           | ---------                                     | ----------                           |--------------                 | -----                      |
* | 01               | Invoke wifi_getSSIDName   | ssidIndex = 1, output_string: NULL  | RETURN_ERR     | Should fail |
*/
void test_l1_wifi_common_hal_negative2_wifi_getSSIDName(void) {
    UT_LOG("Entering test_l1_wifi_common_hal_negative2_wifi_getSSIDName...\n");	
	INT ssidIndex = 1;
    INT ret_val;
	
    UT_LOG("Invoking wifi_getSSIDName with a NULL output_string. Checking for error return status.\n");  
    ret_val = wifi_getSSIDName(ssidIndex, NULL);    
	UT_LOG("Returned status : %d", ret_val);
    UT_ASSERT_EQUAL(ret_val, RETURN_ERR);
    
    UT_LOG("Exiting test_l1_wifi_common_hal_negative2_wifi_getSSIDName...\n");
}

/**
* @brief Test the return status of wifi_getSSIDName API when wifi_init call is omitted
*
* This test function is designed to ensure wifi_getSSIDName API returns an error status when wifi_init function is not invoked before invoking wifi_getSSIDName API. This is important to identify any issues in error handling in such scenarios @n
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 138@n
* **Priority:** High@n@n
* 
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console@n
* 
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke function wifi_getSSIDName after omitting wifi_init | ssidindex = 1, output_string = valid buffer | RETURN_ERR | Should fail |
*/
void test_l1_wifi_common_hal_negative3_wifi_getSSIDName(void) {
    UT_LOG("Entering test_l1_wifi_common_hal_negative3_wifi_getSSIDName...\n");
    
    //Omitted wifi_init() call
    INT ssidIndex = 1;    
    CHAR output_string[50];
    INT ret_val;
	
    WiFi_UnInitPosReq();
    UT_LOG("Invoking wifi_getSSIDName without wifi_init(). Checking for error return status.\n");
    ret_val = wifi_getSSIDName(ssidIndex, output_string);
    
	UT_LOG("Returned status : %d", ret_val);
	WiFi_InitPreReq();
    UT_ASSERT_EQUAL(ret_val, RETURN_ERR);
    
    UT_LOG("Exiting test_l1_wifi_common_hal_negative3_wifi_getSSIDName...\n");
}

/**
* @brief Test to probe the boundary conditions while getting SSID names.
*
* This test is designed to probe boundary conditions of the function wifi_getSSIDName by supplying it with an output buffer of size greater than the maximum possible SSID in an attempt to ensure robustness of the code.@n
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 139@n
* **Priority:** High@n@n
* 
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.@n
* 
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_getSSIDName with an output buffer of size greater than the maximum possible SSID | radioIndex = 1, output_string = buffer of size 513 | RETURN_OK | Should be successful |
*/
void test_l1_wifi_common_hal_boundary1_wifi_getSSIDName(void) {
    UT_LOG("Entering test_l1_wifi_common_hal_boundary1_wifi_getSSIDName...\n");
	INT ssidIndex = 1;
    CHAR output_string[513];
    INT ret_val;	
	
    UT_LOG("Invoking wifi_getSSIDName with output_string of size greater than longest possible SSID. Checking for valid return status.\n");
    ret_val = wifi_getSSIDName(ssidIndex, output_string);

	UT_LOG("Returned status : %d", ret_val);
    UT_ASSERT_EQUAL(ret_val, RETURN_OK);

    UT_LOG("Exiting test_l1_wifi_common_hal_boundary1_wifi_getSSIDName...\n");
}

/**
* @brief This test case tests the wifi_getBaseBSSID API
*
* This test case tests if the wifi_getBaseBSSID API is able to obtain the base BSSID correctly and return the correct status. It's crucial for obtaining BSSID in wifi related operations.
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 140@n
* **Priority:** High@n@n
* 
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.@n
* 
* **Test Procedure:**
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_getBaseBSSID with ssidIndex = 1 and valid output_string buffer | ssidIndex=1, output_string = valid buffer | RETURN_OK | Should be successful |
*/
void test_l1_wifi_common_hal_positive1_wifi_getBaseBSSID( void )
{
    UT_LOG("Entering test_l1_wifi_common_hal_positive1_wifi_getBaseBSSID...");

    INT ssidIndex = 1;
    CHAR output_string[50];
    INT status;
    UT_LOG("Invoking wifi_getBaseBSSID with ssidIndex = 1 and a valid output_string buffer.");

    status = wifi_getBaseBSSID(ssidIndex, output_string);
    UT_LOG("Return status = %d , ssidIndex = %d", status , ssidIndex);
    UT_ASSERT_EQUAL(status, RETURN_OK);
    UT_LOG("Exiting test_l1_wifi_common_hal_positive1_wifi_getBaseBSSID...");
}    

/**
* @brief This test is designed to check the negative case of the function wifi_getBaseBSSID
*
* This Unit Test is used to validate the wifi_getBaseBSSID API by providing an invalid SSID Index. It checks if the API is robust enough to handle invalid inputs and return the corresponding error code accordingly. @n
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 141@n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console@n
* 
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke the wifi_getBaseBSSID() API with invalid SSID Index | ssidIndex=2, output_string = valid string buffer | RETURN_ERR | Should return error |
*/
void test_l1_wifi_common_hal_negative1_wifi_getBaseBSSID(void) 
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative1_wifi_getBaseBSSID...");

    INT ssidIndex = 2;
    CHAR output_string[50];
    INT status;
    UT_LOG("Invoking wifi_getBaseBSSID with invalid ssidIndex = 2 and a valid output_string buffer. ");

    status = wifi_getBaseBSSID(ssidIndex, output_string);  
    UT_LOG("ssidIndex = %d and Return status = %d", ssidIndex, status); 
    UT_ASSERT_EQUAL(status, RETURN_ERR);
    UT_LOG("Exiting test_l1_wifi_common_hal_negative1_wifi_getBaseBSSID...");
}

/**
* @brief This unit test checks wifi_getBaseBSSID's ability to handle invalid arguments.
*
* This test case checks if the wifi_getBaseBSSID function can handle invalid arguments specifically a NULL output_string. The purpose of this test is to ensure the function can adequately handle unexpected or invalid input.@n
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 142@n
* **Priority:** High@n@n
* 
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.@n
* 
* **Test Procedure:**@n
* The function is called with an invalid output buffer. The assertions then verify if the function returned the expected error code.@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_getBaseBSSID with a null output buffer.| ssidIndex = 1, output_string = NULL | RETURN_ERR | Should fail |
*
*/
void test_l1_wifi_common_hal_negative2_wifi_getBaseBSSID(void) 
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative2_wifi_getBaseBSSID...");

    INT ssidIndex = 1;
    CHAR* output_string = NULL;
    INT status;
 
    UT_LOG("Invoking wifi_getBaseBSSID with ssidIndex = 1 and a NULL output_string buffer.");
    status = wifi_getBaseBSSID(ssidIndex, output_string);  
    UT_LOG("ssidIndex = %d and Return status = %d", ssidIndex, status);  
    UT_ASSERT_EQUAL(status, RETURN_ERR);
    UT_LOG("Exiting test_l1_wifi_common_hal_negative2_wifi_getBaseBSSID...");
}

/**
* @brief The test is designed to evaluate the response of wifi_getBaseBSSID API when wifi is not initialized.
*
* This test is used to validate if the wifi_getBaseBSSID API returns an error when invoked without wifi initialization.@n
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 143@n
* **Priority:** High@n@n
* 
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console@n
* 
* **Test Procedure:**@n
* | Variation / Step | Description                                                    | Test Data                                           | Expected Result | Notes |
* | :--------------: | -------------------------------------------------------------- | --------------------------------------------------- | --------------- | ----- |
* | 01               | Call wifi_getBaseBSSID with ssidIndex = 1 and valid output buffer before calling wifi_init | ssidIndex = 1, output_string = allocated buffer | RETURN_ERR  | Should fail |
*/
void test_l1_wifi_common_hal_negative3_wifi_getBaseBSSID(void) 
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative3_wifi_getBaseBSSID...");

    INT ssidIndex = 1;
    CHAR output_string[50];
    INT status;
	
	WiFi_UnInitPosReq();
    UT_LOG("Invoking wifi_getBaseBSSID with ssidIndex = 1 and a valid output_string buffer without wifi initialization.");   
    status = wifi_getBaseBSSID(ssidIndex, output_string);  
    UT_LOG("Return status = %d", status);
    WiFi_InitPreReq();
    UT_ASSERT_EQUAL(status, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative3_wifi_getBaseBSSID...");
}

/**
* @brief This test verifies the wifi_getSSIDMACAddress function
*
* This test invokes wifi_getSSIDMACAddress API with valid inputs of SSID index and a valid output buffer. The reason for this test is to validate the proper functioning of the API when correct parameters are provided.@n
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 144@n
* **Priority:** High@n@n
* 
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console@n
* 
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_getSSIDMACAddress with valid SSID index and output buffer | ssidIndex=1, output_string = valid buffer | RETURN_OK | API should succeed and return the correct MAC address |
*/
void test_l1_wifi_common_hal_positive1_wifi_getSSIDMACAddress( void )
{
    UT_LOG("Entering test_l1_wifi_common_hal_positive1_wifi_getSSIDMACAddress...");

    INT ssidIndex = 1;
    CHAR output_string[20];
    INT result;
	
    UT_LOG("Invoking wifi_getSSIDMACAddress with valid inputs. SSID index: 1. Output buffer is valid.");
    result = wifi_getSSIDMACAddress(ssidIndex, output_string);

    UT_LOG("Return status: %d and MAC address: %s", result, output_string);
    UT_ASSERT_EQUAL(result, RETURN_OK);
    UT_LOG("Exiting test_l1_wifi_common_hal_positive1_wifi_getSSIDMACAddress...");
}


/**
* @brief Test if the function wifi_getSSIDMACAddress returns the correct value when passed a null pointer for the output buffer
*
* This function is testing if the wifi_getSSIDMACAddress function can handle being passed a null pointer and return an error message. This is important to ensure that the wifi_getSSIDMACAddress function can handle abnormal input.@n
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 145@n
* **Priority:** High@n@n
* 
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console@n
* 
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data | Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking wifi_getSSIDMACAddress with NULL pointer for output buffer. | ssidIndex = 1, output_ptr = NULL | RETURN_ERR | The function should return an error as the output buffer pointer is NULL |
*/
void test_l1_wifi_common_hal_negative1_wifi_getSSIDMACAddress( void )
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative1_wifi_getSSIDMACAddress...");

    INT ssidIndex = 1;
    INT result;	
	
    UT_LOG("Invoking wifi_getSSIDMACAddress with NULL pointer for output buffer. SSID index: 1.");
    result = wifi_getSSIDMACAddress(ssidIndex, NULL);

    UT_LOG("Return status: %d", result);
    UT_ASSERT_EQUAL(result, RETURN_ERR);
    UT_LOG("Exiting test_l1_wifi_common_hal_negative1_wifi_getSSIDMACAddress...");
}

/**
* @brief Test for function wifi_getSSIDMACAddress
*
* This test case tests the negative scenarios for the function wifi_getSSIDMACAddress in L1 Wifi API. It verifies if the correct error is returned when the API is given an invalid SSID Index.
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 146@n
* **Priority:** High@n
* @n
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console@n
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_getSSIDMACAddress with invalid SSID index 2 | ssidIndex = 2, output_string = valid buffer | RETURN_ERR | The function should return an error |
*/
void test_l1_wifi_common_hal_negative2_wifi_getSSIDMACAddress( void )
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative2_wifi_getSSIDMACAddress...");

    INT ssidIndex = 2;
    CHAR output_string[20];
    INT result;	
	
    UT_LOG("Invoking wifi_getSSIDMACAddress with SSID index: 2. Expected to return error.");
    result = wifi_getSSIDMACAddress(ssidIndex, output_string);

    UT_LOG("Return status: %d", result);
    UT_ASSERT_EQUAL(result, RETURN_ERR);
    UT_LOG("Exiting test_l1_wifi_common_hal_negative2_wifi_getSSIDMACAddress...");
}

/**
* @brief This is a CUnit test for wifi_getSSIDMACAddress API functionality.
*
* This test checks whether the wifi_getSSIDMACAddress API returns an error when called before initializing wifi using either wifi_init() or wifi_initWithConfig() API.
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 147@n
* **Priority:** High@n
* @n
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_getSSIDMACAddress before calling wifi_init() or wifi_initWithConfig() | ssidIndex = 1, output_string = valid buffer | RETURN_ERR | The function should fail |
*/
void test_l1_wifi_common_hal_negative3_wifi_getSSIDMACAddress( void )
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative3_wifi_getSSIDMACAddress...");
   
    INT ssidIndex = 1;
    CHAR output_string[20];
    INT result;	
	
    WiFi_UnInitPosReq();
    UT_LOG("Invoking wifi_getSSIDMACAddress before calling wifi_init() or wifi_initWithConfig(). Expected to return error.");    
    result = wifi_getSSIDMACAddress(ssidIndex, output_string);    
    UT_LOG("Return status: %d", result);
    WiFi_InitPreReq();
	
    UT_ASSERT_EQUAL(result, RETURN_ERR);    
    UT_LOG("Exiting test_l1_wifi_common_hal_negative3_wifi_getSSIDMACAddress...");
}

/**
* @brief This test verifies the functionality of the 'wifi_getSSIDTrafficStats' function in positive scenarios.
*
* The 'wifi_getSSIDTrafficStats' function is tested for its capability to provide the traffic statistics of a given SSID index. 
* The importance of this test lies in ensuring that the SSID based traffic statistics can be retrieved correctly, which is crucial for WiFi operations.@n
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 148@n
* **Priority:** High@n@n
* 
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.@n
* 
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_getSSIDTrafficStats with valid output_struct and SSID index | ssidIndex = 1, output_string = valid buffer | RETURN_OK | Should be successful|
*/
void test_l1_wifi_common_hal_positive1_wifi_getSSIDTrafficStats(void)
{
    UT_LOG("Entering test_l1_wifi_common_hal_positive1_wifi_getSSIDTrafficStats...");
	INT ssidIndex = 1;
    INT status;
	
    wifi_ssidTrafficStats_t *output_struct = (wifi_ssidTrafficStats_t*)malloc(sizeof(wifi_ssidTrafficStats_t));
    if(output_struct != NULL)
    {
        UT_LOG("Invoking wifi_getSSIDTrafficStats with valid ssidIndex and output_struct pointer.");
        status = wifi_getSSIDTrafficStats(ssidIndex, output_struct);
    
        UT_LOG("Returrn Status: %d", status);
        UT_ASSERT_EQUAL(status, RETURN_OK);

        UT_LOG("ssid traffic status structure holds the values: ssid_BytesSent = %lu, ssid_BytesReceived = %lu, ssid_PacketsSent = %lu, ssid_PacketsReceived = %lu, ssid_RetransCount = %lu, ssid_FailedRetransCount = %lu, ssid_RetryCount = %lu, ssid_MultipleRetryCount = %lu, ssid_ACKFailureCount = %lu, ssid_AggregatedPacketCount = %lu, ssid_ErrorsSent = %lu, ssid_ErrorsReceived = %lu, ssid_UnicastPacketsSent = %lu, ssid_UnicastPacketsReceived = %lu, ssid_DiscardedPacketsSent = %lu, ssid_DiscardedPacketsReceived = %lu, ssid_MulticastPacketsSent = %lu, ssid_MulticastPacketsReceived = %lu, ssid_BroadcastPacketsSent = %lu, ssid_BroadcastPacketsRecevied = %lu, ssid_UnknownPacketsReceived = %lu", output_struct->ssid_BytesSent, output_struct->ssid_BytesReceived, output_struct->ssid_PacketsSent, output_struct->ssid_PacketsReceived, output_struct->ssid_RetransCount, output_struct->ssid_FailedRetransCount, output_struct->ssid_RetryCount, output_struct->ssid_MultipleRetryCount, output_struct->ssid_ACKFailureCount, output_struct->ssid_AggregatedPacketCount, output_struct->ssid_ErrorsSent, output_struct->ssid_ErrorsReceived, output_struct->ssid_UnicastPacketsSent, output_struct->ssid_UnicastPacketsReceived, output_struct->ssid_DiscardedPacketsSent, output_struct->ssid_DiscardedPacketsReceived, output_struct->ssid_MulticastPacketsSent, output_struct->ssid_MulticastPacketsReceived, output_struct->ssid_BroadcastPacketsSent, output_struct->ssid_BroadcastPacketsRecevied, output_struct->ssid_UnknownPacketsReceived);

        if (output_struct->ssid_BytesSent >= 0 && output_struct->ssid_BytesSent <= 18446744073709551615)
        {
            UT_LOG("ssid_BytesSent is %lu which is a valid value", output_struct->ssid_BytesSent);
            UT_PASS("ssid_BytesSent validation success");
        }
        else
        {
            UT_LOG("ssid_BytesSent is %lu which is an invalid value", output_struct->ssid_BytesSent);
            UT_FAIL("ssid_BytesSent validation failed");
        }

        if (output_struct->ssid_BytesReceived >= 0 && output_struct->ssid_BytesReceived <= 18446744073709551615)
        {
            UT_LOG("ssid_BytesReceived is %lu which is a valid value", output_struct->ssid_BytesReceived);
            UT_PASS("ssid_BytesReceived validation success");
        }
        else
        {
            UT_LOG("ssid_BytesReceived is %lu which is an invalid value", output_struct->ssid_BytesReceived);
            UT_FAIL("ssid_BytesReceived validation failed");
        }

        if (output_struct->ssid_PacketsSent >= 0 && output_struct->ssid_PacketsSent <= 18446744073709551615)
        {
            UT_LOG("ssid_PacketsSent is %lu which is a valid value", output_struct->ssid_PacketsSent);
            UT_PASS("ssid_PacketsSent validation success");
        }
        else
        {
            UT_LOG("ssid_PacketsSent is %lu which is an invalid value", output_struct->ssid_PacketsSent);
            UT_FAIL("ssid_PacketsSent validation failed");
        }

        if (output_struct->ssid_PacketsReceived >= 0 && output_struct->ssid_PacketsReceived <= 18446744073709551615)
        {
            UT_LOG("ssid_PacketsReceived is %lu which is a valid value", output_struct->ssid_PacketsReceived);
            UT_PASS("ssid_PacketsReceived validation success");
        }
        else
        {
            UT_LOG("ssid_PacketsReceived is %lu which is an invalid value", output_struct->ssid_PacketsReceived);
            UT_FAIL("ssid_PacketsReceived validation failed");
        }

        if (output_struct->ssid_RetransCount >= 0 && output_struct->ssid_RetransCount <= 4294967295)
        {
            UT_LOG("ssid_RetransCount is %lu which is a valid value", output_struct->ssid_RetransCount);
            UT_PASS("ssid_RetransCount validation success");
        }
        else
        {
            UT_LOG("ssid_RetransCount is %lu which is an invalid value", output_struct->ssid_RetransCount);
            UT_FAIL("ssid_RetransCount validation failed");
        }

        if (output_struct->ssid_FailedRetransCount >= 0 && output_struct->ssid_FailedRetransCount <= 4294967295)
        {
            UT_LOG("ssid_FailedRetransCount is %lu which is a valid value", output_struct->ssid_FailedRetransCount);
            UT_PASS("ssid_FailedRetransCount validation success");
        }
        else
        {
            UT_LOG("ssid_FailedRetransCount is %lu which is an invalid value", output_struct->ssid_FailedRetransCount);
            UT_FAIL("ssid_FailedRetransCount validation failed");
        }

        if (output_struct->ssid_RetryCount >= 0 && output_struct->ssid_RetryCount <= 4294967295)
        {
            UT_LOG("ssid_RetryCount is %lu which is a valid value", output_struct->ssid_RetryCount);
            UT_PASS("ssid_RetryCount validation success");
        }
        else
        {
            UT_LOG("ssid_RetryCount is %lu which is an invalid value", output_struct->ssid_RetryCount);
            UT_FAIL("ssid_RetryCount validation failed");
        }

        if (output_struct->ssid_MultipleRetryCount >= 0 && output_struct->ssid_MultipleRetryCount <= 4294967295)
        {
            UT_LOG("ssid_MultipleRetryCount is %lu which is a valid value", output_struct->ssid_MultipleRetryCount);
            UT_PASS("ssid_MultipleRetryCount validation success");
        }
        else
        {
            UT_LOG("ssid_MultipleRetryCount is %lu which is an invalid value", output_struct->ssid_MultipleRetryCount);
            UT_FAIL("ssid_MultipleRetryCount validation failed");
        }

        if (output_struct->ssid_ACKFailureCount >= 0 && output_struct->ssid_ACKFailureCount <= 4294967295)
        {
            UT_LOG("ssid_ACKFailureCount is %lu which is a valid value", output_struct->ssid_ACKFailureCount);
            UT_PASS("ssid_ACKFailureCount validation success");
        }
        else
        {
            UT_LOG("ssid_ACKFailureCount is %lu which is an invalid value", output_struct->ssid_ACKFailureCount);
            UT_FAIL("ssid_ACKFailureCount validation failed");
        }

        if (output_struct->ssid_AggregatedPacketCount >= 0 && output_struct->ssid_AggregatedPacketCount <= 4294967295)
        {
            UT_LOG("ssid_AggregatedPacketCount is %lu which is a valid value", output_struct->ssid_AggregatedPacketCount);
            UT_PASS("ssid_AggregatedPacketCount validation success");
        }
        else
        {
            UT_LOG("ssid_AggregatedPacketCount is %lu which is an invalid value", output_struct->ssid_AggregatedPacketCount);
            UT_FAIL("ssid_AggregatedPacketCount validation failed");
        }

        if (output_struct->ssid_ErrorsSent >= 0 && output_struct->ssid_ErrorsSent <= 4294967295)
        {
            UT_LOG("ssid_ErrorsSent is %lu which is a valid value", output_struct->ssid_ErrorsSent);
            UT_PASS("ssid_ErrorsSent validation success");
        }
        else
        {
            UT_LOG("ssid_ErrorsSent is %lu which is an invalid value", output_struct->ssid_ErrorsSent);
            UT_FAIL("ssid_ErrorsSent validation failed");
        }

        if (output_struct->ssid_ErrorsReceived >= 0 && output_struct->ssid_ErrorsReceived <= 4294967295)
        {
            UT_LOG("ssid_ErrorsReceived is %lu which is a valid value", output_struct->ssid_ErrorsReceived);
            UT_PASS("ssid_ErrorsReceived validation success");
        }
        else
        {
            UT_LOG("ssid_ErrorsReceived is %lu which is an invalid value", output_struct->ssid_ErrorsReceived);
            UT_FAIL("ssid_ErrorsReceived validation failed");
        }

        if (output_struct->ssid_UnicastPacketsSent >= 0 && output_struct->ssid_UnicastPacketsSent <= 18446744073709551615)
        {
            UT_LOG("ssid_UnicastPacketsSent is %lu which is a valid value", output_struct->ssid_UnicastPacketsSent);
            UT_PASS("ssid_UnicastPacketsSent validation success");
        }
        else
        {
            UT_LOG("ssid_UnicastPacketsSent is %lu which is an invalid value", output_struct->ssid_UnicastPacketsSent);
            UT_FAIL("ssid_UnicastPacketsSent validation failed");
        }

        if (output_struct->ssid_UnicastPacketsReceived >= 0 && output_struct->ssid_UnicastPacketsReceived <= 18446744073709551615)
        {
            UT_LOG("ssid_UnicastPacketsReceived  is %lu which is a valid value", output_struct->ssid_UnicastPacketsReceived);
            UT_PASS("ssid_UnicastPacketsReceived validation success");
        }
        else
        {
            UT_LOG("ssid_UnicastPacketsReceived  is %lu which is an invalid value", output_struct->ssid_UnicastPacketsReceived);
            UT_FAIL("ssid_UnicastPacketsReceived validation failed");
        }

        if (output_struct->ssid_DiscardedPacketsSent >= 0 && output_struct->ssid_DiscardedPacketsSent <= 4294967295)
        {
            UT_LOG("ssid_DiscardedPacketsSent  is %lu which is a valid value", output_struct->ssid_DiscardedPacketsSent);
            UT_PASS("ssid_DiscardedPacketsSent validation success");
        }
        else
        {
            UT_LOG("ssid_DiscardedPacketsSent  is %lu which is an invalid value", output_struct->ssid_DiscardedPacketsSent);
            UT_FAIL("ssid_DiscardedPacketsSent validation failed");
        }

        if (output_struct->ssid_DiscardedPacketsReceived >= 0 && output_struct->ssid_DiscardedPacketsReceived <= 4294967295)
        {
            UT_LOG("ssid_DiscardedPacketsReceived  is %lu which is a valid value", output_struct->ssid_DiscardedPacketsReceived);
            UT_PASS("ssid_DiscardedPacketsReceived validation success");
        }
        else
        {
            UT_LOG("ssid_DiscardedPacketsReceived  is %lu which is an invalid value", output_struct->ssid_DiscardedPacketsReceived);
            UT_FAIL("ssid_DiscardedPacketsReceived validation failed");
        }

        if (output_struct->ssid_MulticastPacketsSent >= 0 && output_struct->ssid_MulticastPacketsSent <= 18446744073709551615)
        {
            UT_LOG("ssid_MulticastPacketsSent is %lu which is a valid value", output_struct->ssid_MulticastPacketsSent);
            UT_PASS("ssid_MulticastPacketsSent validation success");
        }
        else
        {
            UT_LOG("ssid_MulticastPacketsSent is %lu which is an invalid value", output_struct->ssid_MulticastPacketsSent);
            UT_FAIL("ssid_MulticastPacketsSent validation failed");
        }

        if (output_struct->ssid_MulticastPacketsReceived >= 0 && output_struct->ssid_MulticastPacketsReceived <= 18446744073709551615)
        {
            UT_LOG("ssid_MulticastPacketsReceived is %lu which is a valid value", output_struct->ssid_MulticastPacketsReceived);
            UT_PASS(" ssid_MulticastPacketsReceived validation success");
        }
        else
        {
            UT_LOG("ssid_MulticastPacketsReceived is %lu which is an invalid value", output_struct->ssid_MulticastPacketsReceived);
            UT_FAIL(" ssid_MulticastPacketsReceived validation failed");
        }

        if (output_struct->ssid_BroadcastPacketsSent >= 0 && output_struct->ssid_BroadcastPacketsSent <= 18446744073709551615)
        {
            UT_LOG("ssid_BroadcastPacketsSent is %lu which is a valid value", output_struct->ssid_BroadcastPacketsSent);
            UT_PASS("ssid_BroadcastPacketsSent validation success");
        }
        else
        {
            UT_LOG("ssid_BroadcastPacketsSent is %lu which is an invalid value", output_struct->ssid_BroadcastPacketsSent);
            UT_FAIL("ssid_BroadcastPacketsSent validation failed");
        }

        if (output_struct->ssid_BroadcastPacketsRecevied >= 0 && output_struct->ssid_BroadcastPacketsRecevied <= 18446744073709551615)
        {
            UT_LOG("ssid_BroadcastPacketsRecevied is %lu which is a valid value", output_struct->ssid_BroadcastPacketsRecevied);
            UT_PASS("ssid_BroadcastPacketsRecevied validation success");
        }
        else
        {
            UT_LOG("ssid_BroadcastPacketsRecevied is %lu which is an invalid value", output_struct->ssid_BroadcastPacketsRecevied);
            UT_FAIL("ssid_BroadcastPacketsRecevied validation failed");
        }

        if (output_struct->ssid_UnknownPacketsReceived >= 0 && output_struct->ssid_UnknownPacketsReceived <= 4294967295)
        {
            UT_LOG("ssid_UnknownPacketsReceived is %lu which is a valid value", output_struct->ssid_UnknownPacketsReceived);
            UT_PASS("ssid_UnknownPacketsReceived validation success");
        }
        else
        {
            UT_LOG("ssid_UnknownPacketsReceived is %lu which is an invalid value", output_struct->ssid_UnknownPacketsReceived);
            UT_FAIL("ssid_UnknownPacketsReceived validation failed");
        }
		free(output_struct);
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }

    UT_LOG("Exiting test_l1_wifi_common_hal_positive1_wifi_getSSIDTrafficStats...");
}

/**
* @brief This test is designed to verify the behavior of wifi_getSSIDTrafficStats() API when invoked with an invalid ssidIndex.
*
* This test case is focused on checking the error handling capabilities of the wifi_getSSIDTrafficStats. It will 
* aim to simulate a negative scenario where a non-existent SSID index is supplied to the function.@n
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 149@n
* **Priority:** High@n@n
* 
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.@n
* 
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_getSSIDTrafficStats API with invalid ssidIndex | ssidIndex = 2, output_string = valid buffer | RETURN_ERR | Should fail |
*/
void test_l1_wifi_common_hal_negative1_wifi_getSSIDTrafficStats(void)
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative1_wifi_getSSIDTrafficStats...");
	
	INT ssidIndex = 2;
    INT status;	
	
    wifi_ssidTrafficStats_t *output_struct = (wifi_ssidTrafficStats_t*)malloc(sizeof(wifi_ssidTrafficStats_t));
    if(output_struct != NULL)
	{
        UT_LOG("Invoking wifi_getSSIDTrafficStats with invalid ssidIndex.");	
        status = wifi_getSSIDTrafficStats(ssidIndex, output_struct);
    
        UT_LOG("Return Status: %d", status);
		free(output_struct);
        UT_ASSERT_EQUAL(status, RETURN_ERR);
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }
    UT_LOG("Exiting test_l1_wifi_common_hal_negative1_wifi_getSSIDTrafficStats...");
}

/**
* @brief Test to validate wifi_getSSIDTrafficStats API for invalid input
*
* This test case validates the behavior of wifi_getSSIDTrafficStats API when NULL pointer is given as output struct.@n
* It expects that API should handle invalid inputs and return appropriate failure code.
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 150@n
* **Priority:** High@n
* @n
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_getSSIDTrafficStats API with NULL output buffer | ssid index = 1, output struct = NULL | RETURN_ERR | Should fail |
*/
void test_l1_wifi_common_hal_negative2_wifi_getSSIDTrafficStats(void)
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative2_wifi_getSSIDTrafficStats...");
    wifi_ssidTrafficStats_t *output_struct = NULL;
	INT ssidIndex = 1;
    INT status;
    
    UT_LOG("Invoking wifi_getSSIDTrafficStats with NULL output_struct pointer");
    status = wifi_getSSIDTrafficStats(ssidIndex, output_struct);
    
    UT_LOG("Return Status: %d", status);
    UT_ASSERT_EQUAL(status, RETURN_ERR);
    
    UT_LOG("Exiting test_l1_wifi_common_hal_negative2_wifi_getSSIDTrafficStats...");
}

/**
* @brief Test to verify the functionality of 'wifi_getSSIDTrafficStats' function in a negative scenario.
*
* This test verifies if the function 'wifi_getSSIDTrafficStats' returns an error when invoked without prior
* calls to functions wifi_init() or wifi_initWithConfig(). This scenario tests the robustness of the function 
* when called in inappropriate sequence.@n
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 151@n
* **Priority:** High@n
* @n
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke 'wifi_getSSIDTrafficStats' without prior 'wifi_init' or 'wifi_initWithConfig' calls. | index = 1, output_struct = pointer to wifi_ssidTrafficStats_t structure | RETURN_ERR | API should return an error because it was called in inappropriate sequence |
*/
void test_l1_wifi_common_hal_negative3_wifi_getSSIDTrafficStats(void)
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative3_wifi_getSSIDTrafficStats...");
	INT ssidIndex = 1;
	INT status;
	
    wifi_ssidTrafficStats_t *output_struct = (wifi_ssidTrafficStats_t*)malloc(sizeof(wifi_ssidTrafficStats_t));
	
    if(output_struct != NULL)
    {
		
	   WiFi_UnInitPosReq();    
       UT_LOG("Invoking wifi_getSSIDTrafficStats without prior wifi_init() or wifi_initWithConfig() calls."); 
       status = wifi_getSSIDTrafficStats(ssidIndex, output_struct);
    
       UT_LOG("Return Status: %d", status);
	   WiFi_InitPreReq();
	   free(output_struct);
	   UT_ASSERT_EQUAL(status, RETURN_ERR);
       
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }
    UT_LOG("Exiting test_l1_wifi_common_hal_negative3_wifi_getSSIDTrafficStats...");
}

/**
* @brief Test objective: Verify the behavior of wifi_getSSIDTrafficStats when invoked with ssidIndex less than 1
*
* This test aims to verify the functionality of the wifi_getSSIDTrafficStats API when invoked with an invalid input, specifically with a zero ssidIndex. It expects the return status to be an error. This ensures that the API has proper input validation and error handling mechanism.@n
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 152@n
* **Priority:** High@n
* @n
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.
* @n
* **Test Procedure:**@n
* | Variation / Step | Description                                      | Test Data                              | Expected Result                   | Notes                     |
* | :--------------: | ---------------------------------------------- | ----------------------------------- | ------------------------------ | --------------------- |
* | 01               | Invoke wifi_getSSIDTrafficStats with invalid ssidIndex of 0 | ssidIndex = 0, output_struct = valid buffer of type wifi_ssidTrafficStats_t | RETURN_ERR | Should fail |
*/
void test_l1_wifi_common_hal_negative4_wifi_getSSIDTrafficStats(void)
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative4_wifi_getSSIDTrafficStats...");
	INT ssidIndex = 0;	
	INT status;
    wifi_ssidTrafficStats_t *output_struct = (wifi_ssidTrafficStats_t*)malloc(sizeof(wifi_ssidTrafficStats_t));
    if(output_struct != NULL)
    {
        UT_LOG("Invoking wifi_getSSIDTrafficStats with ssidIndex 0");
        status = wifi_getSSIDTrafficStats(ssidIndex, output_struct);
    
        UT_LOG("Retrun Status: %d", status);
		free(output_struct);
        UT_ASSERT_EQUAL(status, RETURN_ERR);
    }
    else
    {
        UT_LOG("Malloc operation failed");
        UT_FAIL("Memory allocation with malloc failed");
    }
    UT_LOG("Exiting test_l1_wifi_common_hal_negative4_wifi_getSSIDTrafficStats...");
}

/**
* @brief Test to verify 'wifi_getNeighboringWiFiDiagnosticResult' API for positive scenario
*
* This tests checks the wifi_getNeighboringWiFiDiagnosticResult function for a positive case where a valid radio index is passed and checks if the expected return value is returned.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 153 @n
* **Priority:** High @n
* @n
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invocation of wifi_getNeighboringWiFiDiagnosticResult with valid radio index | radioIndex = 1, neighbor_ap_array = valid pointer , output_array_size = valid buffer | RETURN_OK | The function should successfully return the neighboring WiFi diagnostic result |
*/
void test_l1_wifi_common_hal_positive1_wifi_getNeighboringWiFiDiagnosticResult( void )
{
    UT_LOG("Entering test_l1_wifi_common_hal_positive1_wifi_getNeighboringWiFiDiagnosticResult...");

    INT radioIndex = 1;
    UINT output_array_size = 512;
	INT result;
	
    wifi_neighbor_ap_t *neighbor_ap_array ;

	UT_LOG("Invoking wifi_getNeighboringWiFiDiagnosticResult with input radioIndex = 1. Expect RETURN_OK.");
	result = wifi_getNeighboringWiFiDiagnosticResult(radioIndex, &neighbor_ap_array, &output_array_size);

	UT_LOG("return status = %d", result);
	UT_ASSERT_EQUAL(result, RETURN_OK);

	UT_LOG("Array of neighboring access points contains the values: ap_SSID = %s, ap_BSSID = %s, ap_Mode = %s, ap_Channel = %d, ap_SignalStrength = %d, ap_SecurityModeEnabled =%s, ap_EncryptionMode = %s, ap_OperatingFrequencyBand = %s, ap_SupportedStandards = %s, ap_OperatingStandards = %s, ap_OperatingChannelBandwidth = %s, ap_BeaconPeriod = %d, ap_Noise = %s, ap_BasicDataTransferRates = %s, ap_SupportedDataTransferRates = %s, ap_DTIMPeriod = %d, ap_ChannelUtilization = %d", neighbor_ap_array->ap_SSID, neighbor_ap_array->ap_BSSID, neighbor_ap_array->ap_Mode, neighbor_ap_array->ap_Channel, neighbor_ap_array->ap_SignalStrength, neighbor_ap_array->ap_SecurityModeEnabled, neighbor_ap_array->ap_EncryptionMode, neighbor_ap_array->ap_OperatingFrequencyBand, neighbor_ap_array->ap_SupportedStandards, neighbor_ap_array->ap_OperatingStandards, neighbor_ap_array->ap_OperatingChannelBandwidth, neighbor_ap_array->ap_BeaconPeriod, neighbor_ap_array->ap_Noise, neighbor_ap_array->ap_BasicDataTransferRates, neighbor_ap_array->ap_SupportedDataTransferRates, neighbor_ap_array->ap_DTIMPeriod, neighbor_ap_array->ap_ChannelUtilization);
	UT_LOG("output_array_size = %d", output_array_size);
	if(!strcmp(neighbor_ap_array->ap_SSID,"") || !strcmp(neighbor_ap_array->ap_SSID,"valid_value"))   /*TODO need to replace with to valid value*/
	{
		UT_LOG("ap_SSID %s which is an valid value", neighbor_ap_array->ap_SSID);
		UT_PASS("ap_SSID validation success");
	}
	else
	{
		UT_LOG("ap_SSID %s which is a invalid value", neighbor_ap_array->ap_SSID);
		UT_FAIL("ap_SSID validation failed");
	}

	if(!strcmp(neighbor_ap_array->ap_Mode,"AdHoc") || !strcmp(neighbor_ap_array->ap_Mode,"Infrastructure"))  
	{
		UT_LOG("ap_Mode %s which is an valid value", neighbor_ap_array->ap_Mode);
		UT_PASS("ap_Mode validation success");
	}
	else
	{
		UT_LOG("ap_Mode %s which is a invalid value", neighbor_ap_array->ap_Mode);
		UT_FAIL("ap_Mode validation failed");
	}

	if ((neighbor_ap_array->ap_Channel >= 1 && neighbor_ap_array->ap_Channel <= 13 )|| (neighbor_ap_array->ap_Channel >= 36 && neighbor_ap_array->ap_Channel <= 64) ||(neighbor_ap_array->ap_Channel >= 100 && neighbor_ap_array->ap_Channel <= 165))
	{
		UT_LOG("ap_Channel is %d which is a valid value", neighbor_ap_array->ap_Channel);
		UT_PASS("ssid_UnknownPacketsReceived validation success");
	}
	else
	{
		UT_LOG("ap_Channel is %d which is an invalid value", neighbor_ap_array->ap_Channel);
		UT_FAIL("ap_Channel validation failed");
	}

	if (neighbor_ap_array->ap_SignalStrength >= -200 && neighbor_ap_array->ap_SignalStrength <= 0)
	{
		UT_LOG("ap_SignalStrength is %d which is a valid value", neighbor_ap_array->ap_SignalStrength);
		UT_PASS("ap_SignalStrength validation success");
	}
	else
	{
		UT_LOG("ap_SignalStrength is %d which is an invalid value", neighbor_ap_array->ap_SignalStrength);
		UT_FAIL("ap_SignalStrength validation failed");
	}
	if(!strcmp(neighbor_ap_array->ap_SecurityModeEnabled,"None") || !strcmp(neighbor_ap_array->ap_SecurityModeEnabled,"WEP")|| !strcmp(neighbor_ap_array->ap_SecurityModeEnabled,"WPA")|| !strcmp(neighbor_ap_array->ap_SecurityModeEnabled,"WPA2")|| !strcmp(neighbor_ap_array->ap_SecurityModeEnabled,"WPA3")|| !strcmp(neighbor_ap_array->ap_SecurityModeEnabled,"WPA-WPA2")|| !strcmp(neighbor_ap_array->ap_SecurityModeEnabled,"WPA2-WPA3")|| !strcmp(neighbor_ap_array->ap_SecurityModeEnabled,"WPA-Enterprise")|| !strcmp(neighbor_ap_array->ap_SecurityModeEnabled,"WPA2-Enterprise")|| !strcmp(neighbor_ap_array->ap_SecurityModeEnabled,"WPA-WPA2-Enterprise"))
	{
		UT_LOG("ap_SecurityModeEnabled is %s which is an valid value", neighbor_ap_array->ap_SecurityModeEnabled);
		UT_PASS("ap_SecurityModeEnabled validation success");
	}
	else
	{
		UT_LOG("ap_SecurityModeEnabled is %s which is a invalid value", neighbor_ap_array->ap_SecurityModeEnabled);
		UT_FAIL("ap_SecurityModeEnabled validation failed");
	}

	if(!strcmp(neighbor_ap_array->ap_EncryptionMode,"TKIP") || !strcmp(neighbor_ap_array->ap_EncryptionMode,"AES"))  
	{
		UT_LOG("ap_EncryptionMode is %s which is an valid value", neighbor_ap_array->ap_EncryptionMode);
		UT_PASS("ap_EncryptionMode validation success");
	}
	else
	{
		UT_LOG("ap_EncryptionMode is %s which is a invalid value", neighbor_ap_array->ap_EncryptionMode);
		UT_FAIL("ap_EncryptionMode validation failed");
	}

	if(!strcmp(neighbor_ap_array->ap_OperatingFrequencyBand,"2.4GHz") || !strcmp(neighbor_ap_array->ap_OperatingFrequencyBand,"5GHz"))  
	{
		UT_LOG("ap_OperatingFrequencyBand is %s which is an valid value", neighbor_ap_array->ap_OperatingFrequencyBand);
		UT_PASS("ap_OperatingFrequencyBand validation success");
	}
	else
	{
		UT_LOG("ap_OperatingFrequencyBand is %s which is a invalid value", neighbor_ap_array->ap_OperatingFrequencyBand);
		UT_FAIL("ap_OperatingFrequencyBand validation failed");
	}

	if(!strcmp(neighbor_ap_array->ap_SupportedStandards,"a") || !strcmp(neighbor_ap_array->ap_SupportedStandards,"b") || !strcmp(neighbor_ap_array->ap_SupportedStandards,"g") || !strcmp(neighbor_ap_array->ap_SupportedStandards,"n") || !strcmp(neighbor_ap_array->ap_SupportedStandards,"ac"))  
	{
		UT_LOG("ap_SupportedStandards is %s which is an valid value", neighbor_ap_array->ap_SupportedStandards);
		UT_PASS("ap_SupportedStandards validation success");
	}
	else
	{
		UT_LOG("ap_SupportedStandards is %s which is a invalid value", neighbor_ap_array->ap_SupportedStandards);
		UT_FAIL("ap_SupportedStandards validation failed");
	}
	if(!strcmp(neighbor_ap_array->ap_OperatingStandards,"a") || !strcmp(neighbor_ap_array->ap_OperatingStandards,"b") || !strcmp(neighbor_ap_array->ap_OperatingStandards,"g") || !strcmp(neighbor_ap_array->ap_OperatingStandards,"n") || !strcmp(neighbor_ap_array->ap_OperatingStandards,"ac"))  
	{
		UT_LOG("ap_OperatingStandards is %s which is an valid value", neighbor_ap_array->ap_OperatingStandards);
		UT_PASS("ap_OperatingStandards validation success");
	}
	else
	{
		UT_LOG("ap_OperatingStandards is %s which is a invalid value", neighbor_ap_array->ap_OperatingStandards);
		UT_FAIL("ap_OperatingStandards validation failed");
	}
	if(!strcmp(neighbor_ap_array->ap_OperatingChannelBandwidth,"20MHz") || !strcmp(neighbor_ap_array->ap_OperatingChannelBandwidth,"40MHz") || !strcmp(neighbor_ap_array->ap_OperatingChannelBandwidth,"80MHz") || !strcmp(neighbor_ap_array->ap_OperatingChannelBandwidth,"160MHz") || !strcmp(neighbor_ap_array->ap_OperatingChannelBandwidth,"Auto"))  
	{
		UT_LOG("ap_OperatingChannelBandwidth is %s which is an valid value", neighbor_ap_array->ap_OperatingChannelBandwidth);
		UT_PASS("ap_OperatingChannelBandwidth validation success");
	}
	else
	{
		UT_LOG("ap_OperatingChannelBandwidth is %s which is a invalid value", neighbor_ap_array->ap_OperatingChannelBandwidth);
		UT_FAIL("ap_OperatingChannelBandwidth validation failed");
	}
	if (neighbor_ap_array->ap_BeaconPeriod >= 0 && neighbor_ap_array->ap_BeaconPeriod <= 4294967295)
	{
		UT_LOG("ap_BeaconPeriod is %d which is a valid value", neighbor_ap_array->ap_BeaconPeriod);
		UT_PASS("ap_BeaconPeriod validation success");
	}
	else
	{
		UT_LOG("ap_BeaconPeriod is %d which is an invalid value", neighbor_ap_array->ap_BeaconPeriod);
		UT_FAIL("ap_BeaconPeriod validation failed");
	}
	if (neighbor_ap_array->ap_Noise >= -200 && neighbor_ap_array->ap_Noise <= 0)
	{
		UT_LOG("ap_Noise is %d which is a valid value", neighbor_ap_array->ap_Noise);
		UT_PASS("ap_Noise validation success");
	}
	else
	{
		UT_LOG("ap_Noise is %d which is an invalid value", neighbor_ap_array->ap_Noise);
		UT_FAIL("ap_Noise validation failed");
	}
	if(!strcmp(neighbor_ap_array->ap_BasicDataTransferRates,"1") || !strcmp(neighbor_ap_array->ap_BasicDataTransferRates,"2") || !strcmp(neighbor_ap_array->ap_BasicDataTransferRates,"5.5") || !strcmp(neighbor_ap_array->ap_BasicDataTransferRates,"6") || !strcmp(neighbor_ap_array->ap_BasicDataTransferRates,"9") || !strcmp(neighbor_ap_array->ap_BasicDataTransferRates,"12")|| !strcmp(neighbor_ap_array->ap_BasicDataTransferRates,"18") || !strcmp(neighbor_ap_array->ap_BasicDataTransferRates,"24") || !strcmp(neighbor_ap_array->ap_BasicDataTransferRates,"36") || !strcmp(neighbor_ap_array->ap_BasicDataTransferRates,"48")|| !strcmp(neighbor_ap_array->ap_BasicDataTransferRates,"54"))  
	{
		UT_LOG("ap_BasicDataTransferRates is %s which is an valid value", neighbor_ap_array->ap_BasicDataTransferRates);
		UT_PASS("ap_BasicDataTransferRates validation success");
	}
	else
	{
		UT_LOG("ap_BasicDataTransferRates is %s which is a invalid value", neighbor_ap_array->ap_BasicDataTransferRates);
		UT_FAIL("ap_BasicDataTransferRates validation failed");
	}
	if(!strcmp(neighbor_ap_array->ap_SupportedDataTransferRates,"1") || !strcmp(neighbor_ap_array->ap_SupportedDataTransferRates,"2") || !strcmp(neighbor_ap_array->ap_SupportedDataTransferRates,"5.5") || !strcmp(neighbor_ap_array->ap_SupportedDataTransferRates,"6") || !strcmp(neighbor_ap_array->ap_SupportedDataTransferRates,"9") || !strcmp(neighbor_ap_array->ap_SupportedDataTransferRates,"12")|| !strcmp(neighbor_ap_array->ap_SupportedDataTransferRates,"18") || !strcmp(neighbor_ap_array->ap_SupportedDataTransferRates,"24") || !strcmp(neighbor_ap_array->ap_SupportedDataTransferRates,"36") || !strcmp(neighbor_ap_array->ap_SupportedDataTransferRates,"48")|| !strcmp(neighbor_ap_array->ap_SupportedDataTransferRates,"54"))  
	{
		UT_LOG("ap_SupportedDataTransferRates is %s which is an valid value", neighbor_ap_array->ap_SupportedDataTransferRates);
		UT_PASS("ap_SupportedDataTransferRates validation success");
	}
	else
	{
		UT_LOG("ap_SupportedDataTransferRates is %s which is a invalid value", neighbor_ap_array->ap_SupportedDataTransferRates);
		UT_FAIL("ap_SupportedDataTransferRates validation failed");
	}
	if (neighbor_ap_array->ap_DTIMPeriod >= 0 && neighbor_ap_array->ap_DTIMPeriod <= 4294967295)
	{
		UT_LOG("ap_DTIMPeriod is %d which is a valid value", neighbor_ap_array->ap_DTIMPeriod);
		UT_PASS("ap_Noise validation success");
	}
	else
	{
		UT_LOG("ap_DTIMPeriod is %d which is an invalid value", neighbor_ap_array->ap_DTIMPeriod);
		UT_FAIL("ap_DTIMPeriod validation failed");
	}
	for (int i = 0; i < sizeof(neighbor_ap_array->ap_ChannelUtilization) / sizeof(neighbor_ap_array->ap_ChannelUtilization[0]); i++) {
		if (neighbor_ap_array->ap_ChannelUtilization[i] >= 0 && neighbor_ap_array->ap_ChannelUtilization[i] <= 100) 
		{
			UT_LOG("ap_ChannelUtilization is %s which is a valid value", neighbor_ap_array->ap_ChannelUtilization[i]);
			UT_PASS("ap_ChannelUtilization validation success");
		}
		else
		{
			UT_LOG("ap_ChannelUtilizationis %s which is a invalid value", neighbor_ap_array->ap_ChannelUtilization[i]);
			UT_FAIL("ap_ChannelUtilization validation failed");
		}
	}
	if (output_array_size >= 0 && output_array_size <= 512)
	{
		UT_LOG("output_array_size is %d which is a valid value", output_array_size);
		UT_PASS("output_array_size success");
	}
	else
	{
		UT_LOG("output_array_size is %d which is an invalid value",output_array_size);
		UT_FAIL("output_array_size validation failed");
	}
    free(neighbor_ap_array);
    UT_LOG("Exiting test_l1_wifi_common_hal_positive1_wifi_getNeighboringWiFiDiagnosticResult...");
}

/**
* @brief Test for wifi_getNeighboringWiFiDiagnosticResult API when invoked with invalid arguments.
*
* The purpose of this test is to verify that when the function 'wifi_getNeighboringWiFiDiagnosticResult' is invoked with invalid arguments, 
* it returns the expected error code. This is important for ensuring robust error handling in the system.
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 154@n
* **Priority:** High@n
* @n
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_getNeighboringWiFiDiagnosticResult with invalid neighbor_ap_array and output_array_size. | radioIndex = 0 , neighbor_ap_array = valid , output_array_size = NULL | Function should return RETURN_ERR | Should fail |
*/
void test_l1_wifi_common_hal_negative1_wifi_getNeighboringWiFiDiagnosticResult( void )
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative1_wifi_getNeighboringWiFiDiagnosticResult...");

    INT radioIndex = 1;
    UINT *output_array_size = NULL;
    INT result;	
    wifi_neighbor_ap_t *neighbor_ap_array;
	
	UT_LOG("Invoking wifi_getNeighboringWiFiDiagnosticResult with invalid input radioIndex = 0, neighbor_ap_array = valid ,NULL. Expect RETURN_ERR.");
	result = wifi_getNeighboringWiFiDiagnosticResult(radioIndex, &neighbor_ap_array, output_array_size);
	UT_LOG("Returned status : %d", result);
    free(neighbor_ap_array);
	UT_ASSERT_EQUAL(result, RETURN_ERR);
    UT_LOG("Exiting test_l1_wifi_common_hal_negative1_wifi_getNeighboringWiFiDiagnosticResult...");
}

/**
* @brief Negative test for function wifi_getNeighboringWiFiDiagnosticResult
*
* This unit test case is written to verify the negative scenario of the wifi_getNeighboringWiFiDiagnosticResult function. It checks if the function correctly handles the invalid input and returns appropriate error code.@n
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 155@n
* **Priority:** High@n
* @n
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke function wifi_getNeighboringWiFiDiagnosticResult with invalid radioIndex, neighbor_ap_array and output_array_size | radioIndex = 2, neighbor_ap_array = NULL , output_array_size = NULL | RETURN_ERR | The function should handle invalid inputs and return error |
*/
void test_l1_wifi_common_hal_negative2_wifi_getNeighboringWiFiDiagnosticResult( void )
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative2_wifi_getNeighboringWiFiDiagnosticResult...");

    INT radioIndex = 1;
    UINT output_array_size = 512;
    wifi_neighbor_ap_t *neighbor_ap_array = NULL;
    INT result;
    
    UT_LOG("Invoking wifi_getNeighboringWiFiDiagnosticResult with invalid input radioIndex = 1,output_array_size = 512,neighbor_ap_array = NULL");
    result = wifi_getNeighboringWiFiDiagnosticResult(radioIndex, &neighbor_ap_array, &output_array_size);

    UT_LOG("Returned status : %d", result);
	free(neighbor_ap_array);
    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative2_wifi_getNeighboringWiFiDiagnosticResult...");
}

/**
* @brief This test is to check the behavior of the `wifi_getNeighboringWiFiDiagnosticResult` function when passed with null parameters
*
* In this test, `wifi_getNeighboringWiFiDiagnosticResult` function is invoked with null `neighbor_ap_array` and `output_array_size` parameters. The expectation is that the function should return `RETURN_ERR`.
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 156@n
* **Priority:** High@n
* @n
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console@n
* 
* **Test Procedure:**@n
* | Variation / Step | Description                         | Test Data                                             | Expected Result     | Notes |
* | :----: | ------------------------------------ | ---------------------------------------------------| ------------------ | ------ |
* | 01    | Invoke wifi_getNeighboringWiFiDiagnosticResult with null neighbor_ap_array and null output_array_size  | radioIndex = 1, neighbor_ap_array = NULL, output_array_size = NULL | RETURN_ERR | Should fail |
*/
void test_l1_wifi_common_hal_negative3_wifi_getNeighboringWiFiDiagnosticResult(void)
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative3_wifi_getNeighboringWiFiDiagnosticResult...");

    INT radioIndex = 3;
    UINT output_array_size = 512;
    wifi_neighbor_ap_t *neighbor_ap_array;
    INT result;
	
	UT_LOG("Invoking wifi_getNeighboringWiFiDiagnosticResult with radioIndex = 3 ,null neighbour_ap_array and output_array_size");
	result = wifi_getNeighboringWiFiDiagnosticResult(radioIndex, &neighbor_ap_array, &output_array_size);
    free(neighbor_ap_array);
	UT_LOG("Returned status : %d", result);
	UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative3_wifi_getNeighboringWiFiDiagnosticResult...");
}

/**
* @brief This unit test verifies the handling of incorrect usage of wifi_getNeighboringWiFiDiagnosticResult
*
* The test simulates a negative test case where the wifi_getNeighboringWiFiDiagnosticResult API is not used properly. The API is invoked without prior calls to initialisation functions- wifi_init() or wifi_initWithConfig() . The test validates that the API handles this error case correctly and returns the expected error value.@n
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 157@n
* **Priority:** High@n
* @n
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_getNeighboringWiFiDiagnosticResult without calling wifi_init() or wifi_initWithConfig()  | radioIndex = 1, neighbor_ap_array = NULL, output_array_size = NULL | RETURN_ERR | Should return error |
*/
void test_l1_wifi_common_hal_negative4_wifi_getNeighboringWiFiDiagnosticResult( void )
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative4_wifi_getNeighboringWiFiDiagnosticResult...");

    INT radioIndex = 1;
    UINT output_array_size = 512;
    wifi_neighbor_ap_t *neighbor_ap_array;

	WiFi_UnInitPosReq();

	UT_LOG("Invoking wifi_getNeighboringWiFiDiagnosticResult without calling wifi_init() or wifi_initWithConfig()");
	INT result = wifi_getNeighboringWiFiDiagnosticResult(radioIndex, &neighbor_ap_array, &output_array_size);

	UT_LOG("Returned status : %d", result);
	WiFi_InitPreReq();
    free(neighbor_ap_array);
	UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative4_wifi_getNeighboringWiFiDiagnosticResult...");
}


/**
* @brief This is a test case to validate the wifi_getSpecificSSIDInfo API for valid inputs
*
* This test case will call wifi_getSpecificSSIDInfo API with a valid SSID and a valid frequency band to validate the functionality of the API with positive inputs.
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 158@n
* **Priority:** High@n
* @n
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_getSpecificSSIDInfo API with valid SSID and frequency band | SSID = "valid_ssid", band = WIFI_HAL_FREQ_BAND_24GHZ | RETURN_OK | Should be successful |
*/
void test_l1_wifi_common_hal_positive1_wifi_getSpecificSSIDInfo( void )
{
    UT_LOG("Entering test_l1_wifi_common_hal_positive1_wifi_getSpecificSSIDInfo...\n");

    const char *SSID = "valid_ssid";                          /*Need to replace with valid value*/
    WIFI_HAL_FREQ_BAND band = WIFI_HAL_FREQ_BAND_24GHZ;
    UINT output_array_size = 0;
    wifi_neighbor_ap_t *neighbor_ap_array;
	INT ret;

	UT_LOG("Invoking wifi_getSpecificSSIDInfo with valid SSID and frequency band");
	ret = wifi_getSpecificSSIDInfo(SSID, band, &neighbor_ap_array, &output_array_size);

	UT_LOG("Return status: %d\n", ret);
	UT_ASSERT_EQUAL(ret, RETURN_OK);

	UT_LOG("Array of neighboring access points contains the values: ap_SSID = %s, ap_BSSID = %s, ap_Mode = %s, ap_Channel = %d, ap_SignalStrength = %d, ap_SecurityModeEnabled =%s, ap_EncryptionMode = %s, ap_OperatingFrequencyBand = %s, ap_SupportedStandards = %s, ap_OperatingStandards = %s, ap_OperatingChannelBandwidth = %s, ap_BeaconPeriod = %d, ap_Noise = %d, ap_BasicDataTransferRates = %s, ap_SupportedDataTransferRates = %s, ap_DTIMPeriod = %d, ap_ChannelUtilization = %d", neighbor_ap_array->ap_SSID, neighbor_ap_array->ap_BSSID, neighbor_ap_array->ap_Mode, neighbor_ap_array->ap_Channel, neighbor_ap_array->ap_SignalStrength, neighbor_ap_array->ap_SecurityModeEnabled, neighbor_ap_array->ap_EncryptionMode, neighbor_ap_array->ap_OperatingFrequencyBand, neighbor_ap_array->ap_SupportedStandards, neighbor_ap_array->ap_OperatingStandards, neighbor_ap_array->ap_OperatingChannelBandwidth, neighbor_ap_array->ap_BeaconPeriod, neighbor_ap_array->ap_Noise, neighbor_ap_array->ap_BasicDataTransferRates, neighbor_ap_array->ap_SupportedDataTransferRates, neighbor_ap_array->ap_DTIMPeriod, neighbor_ap_array->ap_ChannelUtilization);
	UT_LOG("output_array_size = %d", output_array_size);
	if(!strcmp(neighbor_ap_array->ap_SSID,"") || !strcmp(neighbor_ap_array->ap_SSID,"valid_value"))   /*TODO need to replace with to valid value*/
	{
		UT_LOG("ap_SSID %s which is an valid value", neighbor_ap_array->ap_SSID);
		UT_PASS("ap_SSID validation success");
	}
	else
	{
		UT_LOG("ap_SSID %s which is a invalid value", neighbor_ap_array->ap_SSID);
		UT_FAIL("ap_SSID validation failed");
	}

	if(!strcmp(neighbor_ap_array->ap_Mode,"AdHoc") || !strcmp(neighbor_ap_array->ap_Mode,"Infrastructure"))  
	{
		UT_LOG("ap_Mode %s which is an valid value", neighbor_ap_array->ap_Mode);
		UT_PASS("ap_Mode validation success");
	}
	else
	{
		UT_LOG("ap_Mode %s which is a invalid value", neighbor_ap_array->ap_Mode);
		UT_FAIL("ap_Mode validation failed");
	}

	if ((neighbor_ap_array->ap_Channel >= 1 && neighbor_ap_array->ap_Channel <= 13 )||( neighbor_ap_array->ap_Channel >= 36 && neighbor_ap_array->ap_Channel <= 64) || (neighbor_ap_array->ap_Channel >= 100 && neighbor_ap_array->ap_Channel <= 165))
	{
		UT_LOG("ap_Channel is %d which is a valid value", neighbor_ap_array->ap_Channel);
		UT_PASS("ssid_UnknownPacketsReceived validation success");
	}
	else
	{
		UT_LOG("ap_Channel is %d which is an invalid value", neighbor_ap_array->ap_Channel);
		UT_FAIL("ap_Channel validation failed");
	}

	if (neighbor_ap_array->ap_SignalStrength >= -200 && neighbor_ap_array->ap_SignalStrength <= 0)
	{
		UT_LOG("ap_SignalStrength is %d which is a valid value", neighbor_ap_array->ap_SignalStrength);
		UT_PASS("ap_SignalStrength validation success");
	}
	else
	{
		UT_LOG("ap_SignalStrength is %d which is an invalid value", neighbor_ap_array->ap_SignalStrength);
		UT_FAIL("ap_SignalStrength validation failed");
	}

	if(!strcmp(neighbor_ap_array->ap_SecurityModeEnabled,"None") || !strcmp(neighbor_ap_array->ap_SecurityModeEnabled,"WEP")|| !strcmp(neighbor_ap_array->ap_SecurityModeEnabled,"WPA")|| !strcmp(neighbor_ap_array->ap_SecurityModeEnabled,"WPA2")|| !strcmp(neighbor_ap_array->ap_SecurityModeEnabled,"WPA3")|| !strcmp(neighbor_ap_array->ap_SecurityModeEnabled,"WPA-WPA2")|| !strcmp(neighbor_ap_array->ap_SecurityModeEnabled,"WPA2-WPA3")|| !strcmp(neighbor_ap_array->ap_SecurityModeEnabled,"WPA-Enterprise")|| !strcmp(neighbor_ap_array->ap_SecurityModeEnabled,"WPA2-Enterprise")|| !strcmp(neighbor_ap_array->ap_SecurityModeEnabled,"WPA-WPA2-Enterprise"))  
	{
		UT_LOG("ap_SecurityModeEnabled is %s which is an valid value", neighbor_ap_array->ap_SecurityModeEnabled);
		UT_PASS("ap_SecurityModeEnabled validation success");
	}
	else
	{
		UT_LOG("ap_SecurityModeEnabled is %s which is a invalid value", neighbor_ap_array->ap_SecurityModeEnabled);
		UT_FAIL("ap_SecurityModeEnabled validation failed");
	}

	if(!strcmp(neighbor_ap_array->ap_EncryptionMode,"TKIP") || !strcmp(neighbor_ap_array->ap_EncryptionMode,"AES"))  
	{
		UT_LOG("ap_EncryptionMode is %s which is an valid value", neighbor_ap_array->ap_EncryptionMode);
		UT_PASS("ap_EncryptionMode validation success");
	}
	else
	{
		UT_LOG("ap_EncryptionMode is %s which is a invalid value", neighbor_ap_array->ap_EncryptionMode);
		UT_FAIL("ap_EncryptionMode validation failed");
	}

	if(!strcmp(neighbor_ap_array->ap_OperatingFrequencyBand,"2.4GHz") || !strcmp(neighbor_ap_array->ap_OperatingFrequencyBand,"5GHz"))  
	{
		UT_LOG("ap_OperatingFrequencyBand is %s which is an valid value", neighbor_ap_array->ap_OperatingFrequencyBand);
		UT_PASS("ap_OperatingFrequencyBand validation success");
	}
	else
	{
		UT_LOG("ap_OperatingFrequencyBand is %s which is a invalid value", neighbor_ap_array->ap_OperatingFrequencyBand);
		UT_FAIL("ap_OperatingFrequencyBand validation failed");
	}

	if(!strcmp(neighbor_ap_array->ap_SupportedStandards,"a") || !strcmp(neighbor_ap_array->ap_SupportedStandards,"b") || !strcmp(neighbor_ap_array->ap_SupportedStandards,"g") || !strcmp(neighbor_ap_array->ap_SupportedStandards,"n") || !strcmp(neighbor_ap_array->ap_SupportedStandards,"ac"))  
	{
		UT_LOG("ap_SupportedStandards is %s which is an valid value", neighbor_ap_array->ap_SupportedStandards);
		UT_PASS("ap_SupportedStandards validation success");
	}
	else
	{
		UT_LOG("ap_SupportedStandards is %s which is a invalid value", neighbor_ap_array->ap_SupportedStandards);
		UT_FAIL("ap_SupportedStandards validation failed");
	}
	if(!strcmp(neighbor_ap_array->ap_OperatingStandards,"a") || !strcmp(neighbor_ap_array->ap_OperatingStandards,"b") || !strcmp(neighbor_ap_array->ap_OperatingStandards,"g") || !strcmp(neighbor_ap_array->ap_OperatingStandards,"n") || !strcmp(neighbor_ap_array->ap_OperatingStandards,"ac"))  
	{
		UT_LOG("ap_OperatingStandards is %s which is an valid value", neighbor_ap_array->ap_OperatingStandards);
		UT_PASS("ap_OperatingStandards validation success");
	}
	else
	{
		UT_LOG("ap_OperatingStandards is %s which is a invalid value", neighbor_ap_array->ap_OperatingStandards);
		UT_FAIL("ap_OperatingStandards validation failed");
	}
	if(!strcmp(neighbor_ap_array->ap_OperatingChannelBandwidth,"20MHz") || !strcmp(neighbor_ap_array->ap_OperatingChannelBandwidth,"40MHz") || !strcmp(neighbor_ap_array->ap_OperatingChannelBandwidth,"80MHz") || !strcmp(neighbor_ap_array->ap_OperatingChannelBandwidth,"160MHz") || !strcmp(neighbor_ap_array->ap_OperatingChannelBandwidth,"Auto"))  
	{
		UT_LOG("ap_OperatingChannelBandwidth is %s which is an valid value", neighbor_ap_array->ap_OperatingStandards);
		UT_PASS("ap_OperatingChannelBandwidth validation success");
	}
	else
	{
		UT_LOG("ap_OperatingChannelBandwidth is %s which is a invalid value", neighbor_ap_array->ap_OperatingStandards);
		UT_FAIL("ap_OperatingChannelBandwidth validation failed");
	}
	if (neighbor_ap_array->ap_BeaconPeriod >= 0 && neighbor_ap_array->ap_BeaconPeriod <= 4294967295)
	{
		UT_LOG("ap_BeaconPeriod is %d which is a valid value", neighbor_ap_array->ap_BeaconPeriod);
		UT_PASS("ap_BeaconPeriod validation success");
	}
	else
	{
		UT_LOG("ap_BeaconPeriod is %d which is an invalid value", neighbor_ap_array->ap_BeaconPeriod);
		UT_FAIL("ap_BeaconPeriod validation failed");
	}
	if (neighbor_ap_array->ap_Noise >= -200 && neighbor_ap_array->ap_Noise <= 0)
	{
		UT_LOG("ap_Noise is %d which is a valid value", neighbor_ap_array->ap_Noise);
		UT_PASS("ap_Noise validation success");
	}
	else
	{
		UT_LOG("ap_Noise is %d which is an invalid value", neighbor_ap_array->ap_Noise);
		UT_FAIL("ap_Noise validation failed");
	}
	if(!strcmp(neighbor_ap_array->ap_BasicDataTransferRates,"1") || !strcmp(neighbor_ap_array->ap_BasicDataTransferRates,"2") || !strcmp(neighbor_ap_array->ap_BasicDataTransferRates,"5.5") || !strcmp(neighbor_ap_array->ap_BasicDataTransferRates,"6") || !strcmp(neighbor_ap_array->ap_BasicDataTransferRates,"9") || !strcmp(neighbor_ap_array->ap_BasicDataTransferRates,"12")|| !strcmp(neighbor_ap_array->ap_BasicDataTransferRates,"18") || !strcmp(neighbor_ap_array->ap_BasicDataTransferRates,"24") || !strcmp(neighbor_ap_array->ap_BasicDataTransferRates,"36") || !strcmp(neighbor_ap_array->ap_BasicDataTransferRates,"48")|| !strcmp(neighbor_ap_array->ap_BasicDataTransferRates,"54"))  
	{
		UT_LOG("ap_BasicDataTransferRates is %s which is an valid value", neighbor_ap_array->ap_BasicDataTransferRates);
		UT_PASS("ap_BasicDataTransferRates validation success");
	}
	else
	{
		UT_LOG("ap_BasicDataTransferRates is %s which is a invalid value", neighbor_ap_array->ap_BasicDataTransferRates);
		UT_FAIL("ap_BasicDataTransferRates validation failed");
	}
	if(!strcmp(neighbor_ap_array->ap_SupportedDataTransferRates,"1") || !strcmp(neighbor_ap_array->ap_SupportedDataTransferRates,"2") || !strcmp(neighbor_ap_array->ap_SupportedDataTransferRates,"5.5") || !strcmp(neighbor_ap_array->ap_SupportedDataTransferRates,"6") || !strcmp(neighbor_ap_array->ap_SupportedDataTransferRates,"9") || !strcmp(neighbor_ap_array->ap_SupportedDataTransferRates,"12")|| !strcmp(neighbor_ap_array->ap_SupportedDataTransferRates,"18") || !strcmp(neighbor_ap_array->ap_SupportedDataTransferRates,"24") || !strcmp(neighbor_ap_array->ap_SupportedDataTransferRates,"36") || !strcmp(neighbor_ap_array->ap_SupportedDataTransferRates,"48")|| !strcmp(neighbor_ap_array->ap_SupportedDataTransferRates,"54"))  
	{
		UT_LOG("ap_SupportedDataTransferRates is %s which is an valid value", neighbor_ap_array->ap_SupportedDataTransferRates);
		UT_PASS("ap_SupportedDataTransferRates validation success");
	}
	else
	{
		UT_LOG("ap_SupportedDataTransferRates is %s which is a invalid value", neighbor_ap_array->ap_SupportedDataTransferRates);
		UT_FAIL("ap_SupportedDataTransferRates validation failed");
	}
	if (neighbor_ap_array->ap_DTIMPeriod >= 0 && neighbor_ap_array->ap_DTIMPeriod <= 4294967295)
	{
		UT_LOG("ap_DTIMPeriod is %d which is a valid value", neighbor_ap_array->ap_DTIMPeriod);
		UT_PASS("ap_Noise validation success");
	}
	else
	{
		UT_LOG("ap_DTIMPeriod is %d which is an invalid value", neighbor_ap_array->ap_DTIMPeriod);
		UT_FAIL("ap_DTIMPeriod validation failed");
	}
	for (int i = 0; i < sizeof(neighbor_ap_array->ap_ChannelUtilization) / sizeof(neighbor_ap_array->ap_ChannelUtilization[0]); i++) {
		if (neighbor_ap_array->ap_ChannelUtilization[i] >= 0 && neighbor_ap_array->ap_ChannelUtilization[i] <= 100) 
		{
			UT_LOG("ap_ChannelUtilization is %s which is a valid value", neighbor_ap_array->ap_ChannelUtilization[i]);
			UT_PASS("ap_ChannelUtilization validation success");
		}
		else
		{
			UT_LOG("ap_ChannelUtilizationis %s which is a invalid value", neighbor_ap_array->ap_ChannelUtilization[i]);
			UT_FAIL("ap_ChannelUtilization validation failed");
		}
	}
	if (output_array_size >= 0 && output_array_size <= 512)
	{
		UT_LOG("output_array_size is %d which is a valid value", output_array_size);
		UT_PASS("output_array_size success");
	}
	else
	{
		UT_LOG("output_array_size is %d which is an invalid value",output_array_size);
		UT_FAIL("output_array_size validation failed");
	}
	free(neighbor_ap_array);
    UT_LOG("Exiting test_l1_wifi_common_hal_positive1_wifi_getSpecificSSIDInfo...\n");
}

/**
* @brief Test the wifi_getSpecificSSIDInfo API with NULL SSID
*
* The objective of this test is to verify the negative scenario when wifi_getSpecificSSIDInfo is invoked with NULL SSID. The API is expected to handle such incorrect inputs gracefully and return appropriate error status. This will validate the robustness of the API against incorrect input data.@n
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 159@n
* **Priority:** High@n
* @n
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | ---------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_getSpecificSSIDInfo API with NULL SSID | SSID = NULL, band = WIFI_HAL_FREQ_BAND_5GHZ, ap_array = valid pointer, output_array_size = valid number | RETURN_ERR | Should be unsuccessful |
*/
void test_l1_wifi_common_hal_negative1_wifi_getSpecificSSIDInfo( void )
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative1_wifi_getSpecificSSIDInfo...\n");

    const char *SSID = NULL;
    WIFI_HAL_FREQ_BAND band = WIFI_HAL_FREQ_BAND_5GHZ;
    UINT output_array_size = 0;
    wifi_neighbor_ap_t *neighbor_ap_array;
	INT ret;
	
	UT_LOG("Invoking wifi_getSpecificSSIDInfo with NULL SSID");	
	ret = wifi_getSpecificSSIDInfo(SSID, band, &neighbor_ap_array, &output_array_size);

	UT_LOG("Return status: %d\n", ret);
	free(neighbor_ap_array);
	UT_ASSERT_EQUAL(ret, RETURN_ERR);
    
    UT_LOG("Exiting test_l1_wifi_common_hal_negative1_wifi_getSpecificSSIDInfo...\n");
}

/**
 * @brief This test verifies the wifi_getSpecificSSIDInfo API for invalid band inputs
 *
 * This function tests the robustness of wifi_getSpecificSSIDInfo API when provided incorrect band type, expecting 
 * the function to return an error. The aim is to ensure that the function properly handles incorrect inputs.@n
 *
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 160@n
 * **Priority:** High@n
 * @n
 * **Pre-Conditions:** None@n
 * **Dependencies:** None@n
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
 * @n
 * **Test Procedure:**@n
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Invoke the wifi_getSpecificSSIDInfo API with invalid band type | SSID = "valid_ssid", band = WIFI_HAL_FREQ_BAND_NONE, ap_array = valid pointer, output_array_size = valid number | RETURN_ERR | Should fail |
 */
void test_l1_wifi_common_hal_negative2_wifi_getSpecificSSIDInfo( void )
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative2_wifi_getSpecificSSIDInfo...\n");

    const char *SSID = "valid_ssid";        /*Need to replace with valid value*/
    WIFI_HAL_FREQ_BAND band = 5;
    UINT output_array_size = 0;
    wifi_neighbor_ap_t *neighbor_ap_array;

	UT_LOG("Invoking wifi_getSpecificSSIDInfo with invalid frequency band");
	INT ret = wifi_getSpecificSSIDInfo(SSID, band, &neighbor_ap_array, &output_array_size);

	UT_LOG("Return status: %d\n", ret);
	free(neighbor_ap_array);
	UT_ASSERT_EQUAL(ret, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative2_wifi_getSpecificSSIDInfo...\n");
}

/**
* @brief This is a test case to validate the wifi_getSpecificSSIDInfo API when ap_array = NULL
*
* This test case will call wifi_getSpecificSSIDInfo API with a invalid ap_array expecting RETURN_ERR.
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 161@n
* **Priority:** High@n
* @n
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_getSpecificSSIDInfo API with valid SSID, frequency band and invalid ap_array| SSID = "valid_ssid", band = WIFI_HAL_FREQ_BAND_24GHZ , *ap_array = NULL, output_array_size = valid number  | RETURN_ERR | Should be fail |
*/
void test_l1_wifi_common_hal_negative3_wifi_getSpecificSSIDInfo( void )
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative3_wifi_getSpecificSSIDInfo...\n");

    const char *SSID = "valid_ssid";                      /*Need to replace with valid calue*/
    WIFI_HAL_FREQ_BAND band = WIFI_HAL_FREQ_BAND_24GHZ;
    UINT output_array_size = 0;
	wifi_neighbor_ap_t *neighbor_ap_array = NULL;
    INT ret;
    
    UT_LOG("Invoking wifi_getSpecificSSIDInfo with invalid ap_array ");
    ret = wifi_getSpecificSSIDInfo(SSID, band, &neighbor_ap_array, &output_array_size);

    UT_LOG("Return status: %d\n", ret);
	free(neighbor_ap_array);
    UT_ASSERT_EQUAL(ret, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative3_wifi_getSpecificSSIDInfo...\n");
}

/**
* @brief This is a test case to validate the wifi_getSpecificSSIDInfo API when output_array_size = NULL
*
* This test case will call wifi_getSpecificSSIDInfo API with a invalid output_array_size expecting RETURN_ERR.
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 162@n
* **Priority:** High@n
* @n
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_getSpecificSSIDInfo API with valid SSID, frequency band, valid ap_array and invalid output_array_size| SSID = "valid_ssid", band = WIFI_HAL_FREQ_BAND_24GHZ , *ap_array = valid , output_array_size = NULL | RETURN_ERR | Should be fail |
*/
void test_l1_wifi_common_hal_negative4_wifi_getSpecificSSIDInfo( void )
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative4_wifi_getSpecificSSIDInfo...\n");
    const char *SSID = "valid_ssid";                               /*Need to replace with valid calue*/
    WIFI_HAL_FREQ_BAND band = WIFI_HAL_FREQ_BAND_24GHZ;
    UINT output_array_size = 0;
    wifi_neighbor_ap_t *neighbor_ap_array;
	INT ret;
	
	WiFi_UnInitPosReq();
	UT_LOG("Invoking wifi_getSpecificSSIDInfo before wifi_init() or wifi_initWithConfig()");
	ret = wifi_getSpecificSSIDInfo(SSID, band, &neighbor_ap_array, &output_array_size);

	UT_LOG("Return status: %d\n", ret);
	free(neighbor_ap_array);	
    WiFi_InitPreReq();
	UT_ASSERT_EQUAL(ret, RETURN_ERR);



    UT_LOG("Exiting test_l1_wifi_common_hal_negative4_wifi_getSpecificSSIDInfo...\n");
}

/**
* @brief To Verify the functionality of the function wifi_setRadioScanningFreqList
*
* In this test, wifi_setRadioScanningFreqList function is tested for its successful execution and its equivalence with RETURN_OK. The test is designed to assert the functionality of the function and validate its robustness.@n
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 164@n
* **Priority:** High@n
* @n
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console@n
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking wifi_setRadioScanningFreqList with radioIndex set to 1 and freqList = "2412 2437 2452 2467 2482" | radioIndex = 1, freqList = "2412 2437 2452 2467 2482" | RETURN_OK | Should be successful |
*/
void test_l1_wifi_common_hal_positive1_wifi_setRadioScanningFreqList(void) {
    
    UT_LOG("Entering test_l1_wifi_common_hal_positive1_wifi_setRadioScanningFreqList...");
    INT radioIndex = 1;
    CHAR *freqList = "2412 2437 2452 2467 2482";
    INT result;
    
    UT_LOG("Invoking wifi_setRadioScanningFreqList with valid input parameters");
    result = wifi_setRadioScanningFreqList(radioIndex, freqList);
    
    UT_LOG("Returned status : %d", result);
    UT_ASSERT_EQUAL(result, RETURN_OK);

    UT_LOG("Exiting test_l1_wifi_common_hal_positive1_wifi_setRadioScanningFreqList...");
}


/**
* @brief Test the wifi_setRadioScanningFreqList function with negative scenarios
*
* This test case is designed to verify the wifi_setRadioScanningFreqList function with invalid parameters, negative scenarios.@n
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 165@n
* **Priority:** High@n
* @n
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.
* @n
* **Test Procedure:**@n
* | Variation / Step | Description                                         | Test Data                                                     |Expected Result     |Notes |
* | :----:           | ---------                                           | ----------                                                    |--------------      | ----- |
* | 01               | Test wifi_setRadioScanningFreqList with invalid data| radioIndex = 2, freqList = "2412 2437 2452 2467 2482" | RETURN_ERR | Return the appropriate error code |
*
*/
void test_l1_wifi_common_hal_negative1_wifi_setRadioScanningFreqList(void) {
    UT_LOG("Entering test_l1_wifi_common_hal_negative1_wifi_setRadioScanningFreqList...");
    
    INT radioIndex = 2;
    CHAR *freqList = "2412 2437 2452 2467 2482";
    INT result;
	
    UT_LOG("Invoking wifi_setRadioScanningFreqList with invalid radioIndex");
    result = wifi_setRadioScanningFreqList(radioIndex, freqList);
    
    UT_LOG("Returned status : %d", result);
    UT_ASSERT_EQUAL(result, RETURN_ERR);
    
    UT_LOG("Exiting test_l1_wifi_common_hal_negative1_wifi_setRadioScanningFreqList...");
}

/**
* @brief To test the failure case scenario for the function wifi_setRadioScanningFreqList
*
* The test is designed to verify that the wifi_setRadioScanningFreqList function handles incorrect input (a wrong frequency list format) and returns an error. This is crucial for ensuring robustness and error handling of the API.@n
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 166@n
* **Priority:** High@n
* @n
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | The function wifi_setRadioScanningFreqList is called with an incorrectly formatted freqList | radioIndex = 1, freqList = "2412,2437,2452,2467,2482" | The function must return an error RETURN_ERR | The frequency list uses the wrong separator, it should fail |
*/
void test_l1_wifi_common_hal_negative2_wifi_setRadioScanningFreqList(void) {
    
    UT_LOG("Entering test_l1_wifi_common_hal_negative2_wifi_setRadioScanningFreqList...");
    INT radioIndex = 1;
    CHAR *freqList = "2412:2437:2452:2467:2482";
    INT result;
    
    UT_LOG("Invoking wifi_setRadioScanningFreqList with invalid separator");
    result = wifi_setRadioScanningFreqList(radioIndex, freqList);

    UT_LOG("Returned : %d", result);
    UT_ASSERT_EQUAL(result, RETURN_ERR);
    
    UT_LOG("Exiting test_l1_wifi_common_hal_negative2_wifi_setRadioScanningFreqList...");
}

/**
* @brief Test the wifi_setRadioScanningFreqList function with freqList containing one invalid frequency
* This test case is designed to verify the wifi_setRadioScanningFreqList function with invalid parameters, negative scenarios. Return should be RETURN_ERR @n
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 167@n
* **Priority:** High@n
* @n
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.
* @n
* **Test Procedure:**@n
* | Variation / Step | Description                                         | Test Data                                                     |Expected Result     |Notes |
* | :----:           | ---------                                           | ----------                                                    |--------------      | ----- |
* | 01               | Test wifi_setRadioScanningFreqList with invalid freqList | radioIndex = 1, freqList = "5555 2437 2452 2467 2482"        | RETURN_ERR  | The function should return the appropriate error code |
*
*/
void test_l1_wifi_common_hal_negative3_wifi_setRadioScanningFreqList(void) {
    UT_LOG("Entering test_l1_wifi_common_hal_negative3_wifi_setRadioScanningFreqList...");
    
    INT radioIndex = 1;
    CHAR *freqList = "5555 2437 2452 2467 2482";
    INT result;
    
    UT_LOG("Invoking wifi_setRadioScanningFreqList with freqList containing one invalid frequency");
    result = wifi_setRadioScanningFreqList(radioIndex, freqList);
    
    UT_LOG("Returned status : %d", result);
    UT_ASSERT_EQUAL(result, RETURN_ERR);
    
    UT_LOG("Exiting test_l1_wifi_common_hal_negative3_wifi_setRadioScanningFreqList...");
}

/**
* @brief Test the wifi_setRadioScanningFreqList function with freqList = NULL
* This test case is designed to verify the wifi_setRadioScanningFreqList function with freqList = NULL, negative scenarios. Return should be RETURN_ERR @n
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 168@n
* **Priority:** High@n
* @n
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.
* @n
* **Test Procedure:**@n
* | Variation / Step | Description                                         | Test Data                                                     |Expected Result     |Notes |
* | :----:           | ---------                                           | ----------                                                    |--------------      | ----- |
* | 01               | Test wifi_setRadioScanningFreqList with invalid freqList | radioIndex = 1, freqList = NULL | RETURN_ERR | The function should return the appropriate error code |
*
*/
void test_l1_wifi_common_hal_negative4_wifi_setRadioScanningFreqList(void) {
    UT_LOG("Entering test_l1_wifi_common_hal_negative4_wifi_setRadioScanningFreqList...");
    INT radioIndex = 1;
    CHAR *freqList = NULL;
    INT result;
    
    UT_LOG("Invoking wifi_setRadioScanningFreqList with freqList = NULL ");
    result = wifi_setRadioScanningFreqList(radioIndex, freqList);
    
    UT_LOG("Returned status : %d", result);
    UT_ASSERT_EQUAL(result, RETURN_ERR);
    
    UT_LOG("Exiting test_l1_wifi_common_hal_negative4_wifi_setRadioScanningFreqList...");
}

/**
* @brief To Verify the functionality of the function wifi_setRadioScanningFreqList before wifi_init() or wifi_initWithConfig()
*
* In this test, wifi_setRadioScanningFreqList function is tested before wifi_init() or wifi_initWithConfig() and its equivalence with RETURN_ERR. @n
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 169@n
* **Priority:** High@n
* @n
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console@n
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking wifi_setRadioScanningFreqList  before wifi_init() or wifi_initWithConfig() | radioIndex = 1, freqList = "2412 2437 2452 2467 2482" | Result should be equal to RETURN_ERR | Should be failure |
*/
void test_l1_wifi_common_hal_negative5_wifi_setRadioScanningFreqList(void) {
    UT_LOG("Entering test_l1_wifi_common_hal_negative5_wifi_setRadioScanningFreqList...");
    INT radioIndex = 1;
    CHAR *freqList = "2412 2437 2452 2467 2482";
    INT result;
	
	WiFi_UnInitPosReq();
	
    UT_LOG("Invoking wifi_setRadioScanningFreqList before wifi_init() or wifi_initWithConfig()");
    result = wifi_setRadioScanningFreqList(radioIndex, freqList);
    
    UT_LOG("Returned status : %d", result);
	WiFi_InitPreReq();
    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative5_wifi_setRadioScanningFreqList...");
}

/**
* @brief To Verify the functionality of the function wifi_setRadioScanningFreqList with empty freqList 
*
* In this test, wifi_setRadioScanningFreqList function is tested with empty freqList  and its equivalence with RETURN_ERR. @n
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 170@n
* **Priority:** High@n
* @n
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console@n
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking wifi_setRadioScanningFreqList  with empty freqList  | radioIndex = 1, freqList = " " | Result should be equal to RETURN_ERR | Should be failure |
*/
void test_l1_wifi_common_hal_negative6_wifi_setRadioScanningFreqList(void) {
    UT_LOG("Entering test_l1_wifi_common_hal_negative6_wifi_setRadioScanningFreqList...");
    INT radioIndex = 1;
    CHAR *freqList = " ";
    INT result;
	
    UT_LOG("Invoking wifi_setRadioScanningFreqList with empty freqList ");
    result = wifi_setRadioScanningFreqList(radioIndex, freqList);
    
    UT_LOG("Returned status : %d", result);
    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_wifi_common_hal_negative6_wifi_setRadioScanningFreqList...");
}

/**
* @brief This function tests the API: wifi_getDualBandSupport() for retrieving wifi dual band support status.
*
* The functionality of the wifi_getDualBandSupport() API from WiFi Common HAL is tested in this test. The objective is to check if the API retrieves the correct status for dual band support.@n
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 172@n
* **Priority:** High@n
* @n
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.@n
* 
* **Test Procedure:**@n
* | Variation / Step | Description                                 | Test Data           |Expected Result                                                          |Notes                 |
* | :----:            | ---------                                   | ----------          |--------------                                                          | -----                |
* | 01                | Invoke the wifi_getDualBandSupport API      | None | Retrun value should be 0 or 1, where 0 implies dual band not supported and 1 implies dual band supported | Success condition can vary with different devices |
*/
void test_l1_wifi_common_hal_positive1_getDualBandSupport(void)
{
   UT_LOG("Entering test function: test_l1_wifi_common_hal_positive1_getDualBandSupport...");

   INT return_val;
   
   UT_LOG("Invoking wifi_getDualBandSupport");
   return_val = wifi_getDualBandSupport();
   UT_LOG("Returned status : %d", return_val);   
   if(return_val == 1)
   {
	   UT_LOG("dual band support enabled");
	   UT_ASSERT_EQUAL(return_val, 1); 
   }
   else
   {
	   UT_LOG("dual band support disabled");
	   UT_ASSERT_EQUAL(return_val, 0);
   }	   
   UT_LOG("Exiting test function: test_l1_wifi_common_hal_positive1_getDualBandSupport...");
}


/**
* @brief Test for positive confirmation of wifi scan results availability
*
* This test is designed to validate the behavior of the wifi_waitForScanResults API when called after initiating a wifi scan. The wifi_waitForScanResults API is expected to return with a RETURN_OK signal indicating that scan results are available for fetch.
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 174@n
* **Priority:** High@n@n
*
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.@n
*
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke wifi_waitForScanResults and verify if it succeeds  | None | RETURN_OK | Should be successful |
*/
void test_l1_wifi_common_hal_positive1_wifi_waitForScanResults(void) 
{
    UT_LOG("Entering test_l1_wifi_common_hal_positive1_wifi_waitForScanResults...");
    INT retValue;

    UT_LOG("Invoking wifi_waitForScanResults. Expected return value is #RETURN_OK.");
    retValue = wifi_waitForScanResults();

	UT_LOG("Returned status : %d", retValue);
    UT_ASSERT_EQUAL(retValue, RETURN_OK);  

    UT_LOG("Exiting test_l1_wifi_common_hal_positive1_wifi_waitForScanResults...");
}

/**
* @brief Testing the method wifi_waitForScanResults when wifi_init or wifi_initWithConfig is not called
*
* This test is designed to assert that the wifi_waitForScanResults function should fail if wifi_init or wifi_initWithConfig was not previously called. This guarantees that wifi_waitForScanResults is not used inappropriately in the application.@n
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 175@n
* **Priority:** High@n
* @n
* **Pre-Conditions:** None@n
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.
* @n
* **Test Procedure:**@n
* In this test case, wifi_waitForScanResults is called before calling wifi_init or wifi_initWithConfig. That is, wifi_waitForScanResults is called with wifi not initialized.@n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Call wifi_waitForScanResults before calling wifi_init or wifi_initWithConfig | None | Should return RETURN_ERR | Should fail |
*/
void test_l1_wifi_common_hal_negative1_wifi_waitForScanResults(void)
{
    UT_LOG("Entering test_l1_wifi_common_hal_negative1_wifi_waitForScanResults...");
	
    INT retValue;
	
    WiFi_UnInitPosReq();
    UT_LOG("Invoking wifi_waitForScanResults without calling wifi_init or wifi_initWithConfig. Expected return value is #RETURN_ERR.");
    retValue = wifi_waitForScanResults();	
    UT_LOG("Returned status : %d", retValue);
    UT_ASSERT_EQUAL(retValue, RETURN_ERR);
    WiFi_InitPreReq();
	
    UT_LOG("Exiting test_l1_wifi_common_hal_negative1_wifi_waitForScanResults...");
}

static UT_test_suite_t * pSuite = NULL;

/**
 * @brief Register the main tests for this module
 *
 * @return int - 0 on success, otherwise failure
 */

int test_wifi_common_hal_register(void)
{
    // Create the test suite
    pSuite = UT_add_suite("[L1 wifi_common_hal]", NULL, NULL);
    if (pSuite == NULL) {
        return -1;
    }
    // List of test function names and strings
   const char* list1[] = {"l1_wifi_common_hal_positive1_wifi_getHalVersion", "l1_wifi_common_hal_negative1_wifi_getHalVersion", "l1_wifi_common_hal_positive1_wifi_init", "l1_wifi_common_hal_positive1_wifi_initWithConfig", "l1_wifi_common_hal_negative1_wifi_initWithConfig", "l1_wifi_common_hal_negative2_wifi_initWithConfig", "l1_wifi_common_hal_negative3_wifi_initWithConfig", "l1_wifi_common_hal_positive1_wifi_down", "l1_wifi_common_hal_negative1_wifi_down","l1_wifi_common_hal_positive1_wifi_uninit", "l1_wifi_common_hal_positive2_wifi_uninit", "l1_wifi_common_hal_negative1_wifi_uninit", "l1_wifi_common_hal_positive1_getStats", "l1_wifi_common_hal_negative1_getStats", "l1_wifi_common_hal_negative2_getStats", "l1_wifi_common_hal_negative3_getStats", "l1_wifi_common_hal_positive1_wifi_getRadioNumberOfEntries", "l1_wifi_common_hal_negative1_wifi_getRadioNumberOfEntries", "l1_wifi_common_hal_negative2_wifi_getRadioNumberOfEntries", "l1_wifi_common_hal_positive1_wifi_getSSIDNumberOfEntries", "l1_wifi_common_hal_negative1_wifi_getSSIDNumberOfEntries", "l1_wifi_common_hal_negative2_wifi_getSSIDNumberOfEntries", "l1_wifi_common_hal_positive1_wifi_getRadioEnable", "l1_wifi_common_hal_positive2_wifi_getRadioEnable", "l1_wifi_common_hal_positive3_wifi_getRadioEnable", "l1_wifi_common_hal_negative1_wifi_getRadioEnable", "l1_wifi_common_hal_negative2_wifi_getRadioEnable", "l1_wifi_common_hal_negative3_wifi_getRadioEnable","l1_wifi_common_hal_negative4_wifi_getRadioEnable", "l1_wifi_common_hal_positive1_wifi_getRadioStatus", "l1_wifi_common_hal_negative1_wifi_getRadioStatus", "l1_wifi_common_hal_negative2_wifi_getRadioStatus", "l1_wifi_common_hal_negative3_wifi_getRadioStatus","l1_wifi_common_hal_positive1_wifi_getRadioIfName","l1_wifi_common_hal_negative1_wifi_getRadioIfName","l1_wifi_common_hal_negative2_wifi_getRadioIfName","l1_wifi_common_hal_negative3_wifi_getRadioIfName","l1_wifi_common_hal_negative4_wifi_getRadioIfName","l1_wifi_common_hal_negative5_wifi_getRadioIfName", "l1_wifi_common_hal_positive1_wifi_getRadioMaxBitRate", "l1_wifi_common_hal_negative1_wifi_getRadioMaxBitRate", "l1_wifi_common_hal_negative2_wifi_getRadioMaxBitRate", "l1_wifi_common_hal_negative3_wifi_getRadioMaxBitRate", "l1_wifi_common_hal_positive1_wifi_getRadioSupportedFrequencyBands", "l1_wifi_common_hal_negative1_wifi_getRadioSupportedFrequencyBands", "l1_wifi_common_hal_negative2_wifi_getRadioSupportedFrequencyBands", "l1_wifi_common_hal_negative3_wifi_getRadioSupportedFrequencyBands", "l1_wifi_common_hal_negative4_wifi_getRadioSupportedFrequencyBands", "l1_wifi_common_hal_positive1_wifi_getRadioOperatingFrequencyBand", "l1_wifi_common_hal_negative1_wifi_getRadioOperatingFrequencyBand", "l1_wifi_common_hal_negative2_wifi_getRadioOperatingFrequencyBand", "l1_wifi_common_hal_negative3_wifi_getRadioOperatingFrequencyBand", "l1_wifi_common_hal_positive1_wifi_getRadioSupportedStandards", "l1_wifi_common_hal_negative1_wifi_getRadioSupportedStandards", "l1_wifi_common_hal_negative2_wifi_getRadioSupportedStandards", "l1_wifi_common_hal_negative3_wifi_getRadioSupportedStandards", "l1_wifi_common_hal_positive1_wifi_getRadioStandard", "l1_wifi_common_hal_negative1_wifi_getRadioStandard", "l1_wifi_common_hal_negative2_wifi_getRadioStandard", "l1_wifi_common_hal_negative3_wifi_getRadioStandard", "l1_wifi_common_hal_positive1_wifi_getRadioPossibleChannels", "l1_wifi_common_hal_negative1_wifi_getRadioPossibleChannels", "l1_wifi_common_hal_negative2_wifi_getRadioPossibleChannels", "l1_wifi_common_hal_negative3_wifi_getRadioPossibleChannels", "l1_wifi_common_hal_negative4_wifi_getRadioPossibleChannels", "l1_wifi_common_hal_positive1_wifi_getRadioChannelsInUse", "l1_wifi_common_hal_negative1_wifi_getRadioChannelsInUse", "l1_wifi_common_hal_negative2_wifi_getRadioChannelsInUse", "l1_wifi_common_hal_negative3_wifi_getRadioChannelsInUse", "l1_wifi_common_hal_negative4_wifi_getRadioChannelsInUse", "l1_wifi_common_hal_positive1_wifi_getRadioChannel", "l1_wifi_common_hal_negative1_wifi_getRadioChannel", "l1_wifi_common_hal_negative2_wifi_getRadioChannel", "l1_wifi_common_hal_negative3_wifi_getRadioChannel", "l1_wifi_common_hal_positive1_wifi_getRadioAutoChannelSupported", "l1_wifi_common_hal_negative1_wifi_getRadioAutoChannelSupported", "l1_wifi_common_hal_negative2_wifi_getRadioAutoChannelSupported", "l1_wifi_common_hal_negative3_wifi_getRadioAutoChannelSupported", "l1_wifi_common_hal_positive2_wifi_getRadioAutoChannelSupported", "l1_wifi_common_hal_positive1_wifi_getRadioAutoChannelEnable", "l1_wifi_common_hal_negative1_wifi_getRadioAutoChannelEnable", "l1_wifi_common_hal_negative2_wifi_getRadioAutoChannelEnable", "l1_wifi_common_hal_negative3_wifi_getRadioAutoChannelEnable", "l1_wifi_common_hal_positive1_getRadioAutoChannelRefreshPeriod", "l1_wifi_common_hal_negative1_getRadioAutoChannelRefreshPeriod", "l1_wifi_common_hal_negative2_getRadioAutoChannelRefreshPeriod", "l1_wifi_common_hal_positive2_getRadioAutoChannelRefreshPeriod", "l1_wifi_common_hal_negative3_getRadioAutoChannelRefreshPeriod", "l1_wifi_common_hal_positive1_wifi_getRadioGuardInterval", "l1_wifi_common_hal_negative1_wifi_getRadioGuardInterval", "l1_wifi_common_hal_negative2_wifi_getRadioGuardInterval", "l1_wifi_common_hal_negative3_wifi_getRadioGuardInterval", "l1_wifi_common_hal_negative4_wifi_getRadioGuardInterval", "l1_wifi_common_hal_positive1_wifi_getRadioOperatingChannelBandwidth", "l1_wifi_common_hal_negative1_wifi_getRadioOperatingChannelBandwidth", "l1_wifi_common_hal_negative2_wifi_getRadioOperatingChannelBandwidth", "l1_wifi_common_hal_negative3_wifi_getRadioOperatingChannelBandwidth", "l1_wifi_common_hal_negative4_wifi_getRadioOperatingChannelBandwidth", "l1_wifi_common_hal_positive1_wifi_getRadioExtChannel", "l1_wifi_common_hal_negative1_wifi_getRadioExtChannel", "l1_wifi_common_hal_negative2_wifi_getRadioExtChannel", "l1_wifi_common_hal_negative3_wifi_getRadioExtChannel", "l1_wifi_common_hal_negative4_wifi_getRadioExtChannel", "l1_wifi_common_hal_positive1_wifi_getRadioMCS", "l1_wifi_common_hal_negative1_wifi_getRadioMCS", "l1_wifi_common_hal_negative2_wifi_getRadioMCS", "l1_wifi_common_hal_negative3_wifi_getRadioMCS", "l1_wifi_common_hal_positive1_wifi_getRadioTransmitPowerSupported", "l1_wifi_common_hal_negative1_wifi_getRadioTransmitPowerSupported", "l1_wifi_common_hal_negative2_wifi_getRadioTransmitPowerSupported", "l1_wifi_common_hal_negative3_wifi_getRadioTransmitPowerSupported","l1_wifi_common_hal_negative4_wifi_getRadioTransmitPowerSupported", "l1_wifi_common_hal_positive1_wifi_getRadioTransmitPower", "l1_wifi_common_hal_negative1_wifi_getRadioTransmitPower", "l1_wifi_common_hal_negative2_wifi_getRadioTransmitPower","l1_wifi_common_hal_negative3_wifi_getRadioTransmitPower","l1_wifi_common_hal_negative4_wifi_getRadioTransmitPower", "l1_wifi_common_hal_positive_1_wifi_getRadioIEEE80211hSupported", "l1_wifi_common_hal_negative_1_wifi_getRadioIEEE80211hSupported", "l1_wifi_common_hal_negative_2_wifi_getRadioIEEE80211hSupported", "l1_wifi_common_hal_negative_3_wifi_getRadioIEEE80211hSupported", "l1_wifi_common_hal_positive1_wifi_getRadioIEEE80211hEnabled", "l1_wifi_common_hal_negative1_wifi_getRadioIEEE80211hEnabled", "l1_wifi_common_hal_negative2_wifi_getRadioIEEE80211hEnabled", "l1_wifi_common_hal_negative3_wifi_getRadioIEEE80211hEnabled", "l1_wifi_common_hal_positive1_wifi_getRegulatoryDomain", "l1_wifi_common_hal_negative1_wifi_getRegulatoryDomain", "l1_wifi_common_hal_negative2_wifi_getRegulatoryDomain", "l1_wifi_common_hal_negative3_wifi_getRegulatoryDomain", "l1_wifi_common_hal_negative4_wifi_getRegulatoryDomain", "l1_wifi_common_hal_negative5_wifi_getRegulatoryDomain", "l1_wifi_common_hal_negative6_wifi_getRegulatoryDomain", "l1_wifi_common_hal_positive1_wifi_getRadioTrafficStats", "l1_wifi_common_hal_negative1_wifi_getRadioTrafficStats", "l1_wifi_common_hal_negative2_wifi_getRadioTrafficStats", "l1_wifi_common_hal_negative3_wifi_getRadioTrafficStats", "l1_wifi_common_hal_positive1_wifi_getSSIDName", "l1_wifi_common_hal_negative1_wifi_getSSIDName", "l1_wifi_common_hal_negative2_wifi_getSSIDName", "l1_wifi_common_hal_negative3_wifi_getSSIDName", "l1_wifi_common_hal_boundary1_wifi_getSSIDName", "l1_wifi_common_hal_positive1_wifi_getBaseBSSID", "l1_wifi_common_hal_negative1_wifi_getBaseBSSID", "l1_wifi_common_hal_negative2_wifi_getBaseBSSID", "l1_wifi_common_hal_negative3_wifi_getBaseBSSID", "l1_wifi_common_hal_positive1_wifi_getSSIDMACAddress", "l1_wifi_common_hal_negative1_wifi_getSSIDMACAddress", "l1_wifi_common_hal_negative2_wifi_getSSIDMACAddress", "l1_wifi_common_hal_negative3_wifi_getSSIDMACAddress", "l1_wifi_common_hal_positive1_wifi_getSSIDTrafficStats", "l1_wifi_common_hal_negative1_wifi_getSSIDTrafficStats", "l1_wifi_common_hal_negative2_wifi_getSSIDTrafficStats", "l1_wifi_common_hal_negative3_wifi_getSSIDTrafficStats", "l1_wifi_common_hal_negative4_wifi_getSSIDTrafficStats", "l1_wifi_common_hal_positive1_wifi_getNeighboringWiFiDiagnosticResult", "l1_wifi_common_hal_negative1_wifi_getNeighboringWiFiDiagnosticResult", "l1_wifi_common_hal_negative2_wifi_getNeighboringWiFiDiagnosticResult", "l1_wifi_common_hal_negative3_wifi_getNeighboringWiFiDiagnosticResult", "l1_wifi_common_hal_negative4_wifi_getNeighboringWiFiDiagnosticResult", "l1_wifi_common_hal_positive1_wifi_getSpecificSSIDInfo", "l1_wifi_common_hal_negative1_wifi_getSpecificSSIDInfo", "l1_wifi_common_hal_negative2_wifi_getSpecificSSIDInfo","l1_wifi_common_hal_negative3_wifi_getSpecificSSIDInfo","l1_wifi_common_hal_negative4_wifi_getSpecificSSIDInfo", "l1_wifi_common_hal_positive1_wifi_setRadioScanningFreqList", "l1_wifi_common_hal_negative1_wifi_setRadioScanningFreqList", "l1_wifi_common_hal_negative2_wifi_setRadioScanningFreqList","l1_wifi_common_hal_negative3_wifi_setRadioScanningFreqList", "l1_wifi_common_hal_negative4_wifi_setRadioScanningFreqList", "l1_wifi_common_hal_negative5_wifi_setRadioScanningFreqList", "l1_wifi_common_hal_negative6_wifi_setRadioScanningFreqList", "l1_wifi_common_hal_positive1_getDualBandSupport", "l1_wifi_common_hal_positive1_wifi_waitForScanResults", "l1_wifi_common_hal_negative1_wifi_waitForScanResults" };
   void (*list2[])() = {test_l1_wifi_common_hal_positive1_wifi_getHalVersion, test_l1_wifi_common_hal_negative1_wifi_getHalVersion, test_l1_wifi_common_hal_positive1_wifi_init, test_l1_wifi_common_hal_positive1_wifi_initWithConfig, test_l1_wifi_common_hal_negative1_wifi_initWithConfig, test_l1_wifi_common_hal_negative2_wifi_initWithConfig, test_l1_wifi_common_hal_negative3_wifi_initWithConfig, test_l1_wifi_common_hal_positive1_wifi_down,test_l1_wifi_common_hal_negative1_wifi_down,test_l1_wifi_common_hal_positive1_wifi_uninit, test_l1_wifi_common_hal_positive2_wifi_uninit, test_l1_wifi_common_hal_negative1_wifi_uninit, test_l1_wifi_common_hal_positive1_getStats, test_l1_wifi_common_hal_negative1_getStats, test_l1_wifi_common_hal_negative2_getStats, test_l1_wifi_common_hal_negative3_getStats, test_l1_wifi_common_hal_positive1_wifi_getRadioNumberOfEntries, test_l1_wifi_common_hal_negative1_wifi_getRadioNumberOfEntries, test_l1_wifi_common_hal_negative2_wifi_getRadioNumberOfEntries, test_l1_wifi_common_hal_positive1_wifi_getSSIDNumberOfEntries, test_l1_wifi_common_hal_negative1_wifi_getSSIDNumberOfEntries, test_l1_wifi_common_hal_negative2_wifi_getSSIDNumberOfEntries, test_l1_wifi_common_hal_positive1_wifi_getRadioEnable, test_l1_wifi_common_hal_positive2_wifi_getRadioEnable, test_l1_wifi_common_hal_positive3_wifi_getRadioEnable, test_l1_wifi_common_hal_negative1_wifi_getRadioEnable, test_l1_wifi_common_hal_negative2_wifi_getRadioEnable, test_l1_wifi_common_hal_negative3_wifi_getRadioEnable, test_l1_wifi_common_hal_negative4_wifi_getRadioEnable, test_l1_wifi_common_hal_positive1_wifi_getRadioStatus, test_l1_wifi_common_hal_negative1_wifi_getRadioStatus, test_l1_wifi_common_hal_negative2_wifi_getRadioStatus, test_l1_wifi_common_hal_negative3_wifi_getRadioStatus,test_l1_wifi_common_hal_positive1_wifi_getRadioIfName,test_l1_wifi_common_hal_negative1_wifi_getRadioIfName,test_l1_wifi_common_hal_negative2_wifi_getRadioIfName,test_l1_wifi_common_hal_negative3_wifi_getRadioIfName,test_l1_wifi_common_hal_negative4_wifi_getRadioIfName,test_l1_wifi_common_hal_negative5_wifi_getRadioIfName, test_l1_wifi_common_hal_positive1_wifi_getRadioMaxBitRate, test_l1_wifi_common_hal_negative1_wifi_getRadioMaxBitRate, test_l1_wifi_common_hal_negative2_wifi_getRadioMaxBitRate, test_l1_wifi_common_hal_negative3_wifi_getRadioMaxBitRate, test_l1_wifi_common_hal_positive1_wifi_getRadioSupportedFrequencyBands, test_l1_wifi_common_hal_negative1_wifi_getRadioSupportedFrequencyBands, test_l1_wifi_common_hal_negative2_wifi_getRadioSupportedFrequencyBands, test_l1_wifi_common_hal_negative3_wifi_getRadioSupportedFrequencyBands, test_l1_wifi_common_hal_negative4_wifi_getRadioSupportedFrequencyBands, test_l1_wifi_common_hal_positive1_wifi_getRadioOperatingFrequencyBand, test_l1_wifi_common_hal_negative1_wifi_getRadioOperatingFrequencyBand, test_l1_wifi_common_hal_negative2_wifi_getRadioOperatingFrequencyBand, test_l1_wifi_common_hal_negative3_wifi_getRadioOperatingFrequencyBand, test_l1_wifi_common_hal_positive1_wifi_getRadioSupportedStandards, test_l1_wifi_common_hal_negative1_wifi_getRadioSupportedStandards, test_l1_wifi_common_hal_negative2_wifi_getRadioSupportedStandards, test_l1_wifi_common_hal_negative3_wifi_getRadioSupportedStandards, test_l1_wifi_common_hal_positive1_wifi_getRadioStandard, test_l1_wifi_common_hal_negative1_wifi_getRadioStandard, test_l1_wifi_common_hal_negative2_wifi_getRadioStandard, test_l1_wifi_common_hal_negative3_wifi_getRadioStandard, test_l1_wifi_common_hal_positive1_wifi_getRadioPossibleChannels, test_l1_wifi_common_hal_negative1_wifi_getRadioPossibleChannels, test_l1_wifi_common_hal_negative2_wifi_getRadioPossibleChannels, test_l1_wifi_common_hal_negative3_wifi_getRadioPossibleChannels, test_l1_wifi_common_hal_negative4_wifi_getRadioPossibleChannels, test_l1_wifi_common_hal_positive1_wifi_getRadioChannelsInUse, test_l1_wifi_common_hal_negative1_wifi_getRadioChannelsInUse, test_l1_wifi_common_hal_negative2_wifi_getRadioChannelsInUse, test_l1_wifi_common_hal_negative3_wifi_getRadioChannelsInUse, test_l1_wifi_common_hal_negative4_wifi_getRadioChannelsInUse, test_l1_wifi_common_hal_positive1_wifi_getRadioChannel, test_l1_wifi_common_hal_negative1_wifi_getRadioChannel, test_l1_wifi_common_hal_negative2_wifi_getRadioChannel,  test_l1_wifi_common_hal_negative3_wifi_getRadioChannel, test_l1_wifi_common_hal_positive1_wifi_getRadioAutoChannelSupported, test_l1_wifi_common_hal_negative1_wifi_getRadioAutoChannelSupported, test_l1_wifi_common_hal_negative2_wifi_getRadioAutoChannelSupported, test_l1_wifi_common_hal_negative3_wifi_getRadioAutoChannelSupported, test_l1_wifi_common_hal_positive2_wifi_getRadioAutoChannelSupported, test_l1_wifi_common_hal_positive1_wifi_getRadioAutoChannelEnable, test_l1_wifi_common_hal_negative1_wifi_getRadioAutoChannelEnable, test_l1_wifi_common_hal_negative2_wifi_getRadioAutoChannelEnable, test_l1_wifi_common_hal_negative3_wifi_getRadioAutoChannelEnable, test_l1_wifi_common_hal_positive1_getRadioAutoChannelRefreshPeriod, test_l1_wifi_common_hal_negative1_getRadioAutoChannelRefreshPeriod, test_l1_wifi_common_hal_negative2_getRadioAutoChannelRefreshPeriod, test_l1_wifi_common_hal_positive2_getRadioAutoChannelRefreshPeriod, test_l1_wifi_common_hal_negative3_getRadioAutoChannelRefreshPeriod, test_l1_wifi_common_hal_positive1_wifi_getRadioGuardInterval, test_l1_wifi_common_hal_negative1_wifi_getRadioGuardInterval, test_l1_wifi_common_hal_negative2_wifi_getRadioGuardInterval, test_l1_wifi_common_hal_negative3_wifi_getRadioGuardInterval, test_l1_wifi_common_hal_negative4_wifi_getRadioGuardInterval, test_l1_wifi_common_hal_positive1_wifi_getRadioOperatingChannelBandwidth, test_l1_wifi_common_hal_negative1_wifi_getRadioOperatingChannelBandwidth, test_l1_wifi_common_hal_negative2_wifi_getRadioOperatingChannelBandwidth, test_l1_wifi_common_hal_negative3_wifi_getRadioOperatingChannelBandwidth, test_l1_wifi_common_hal_negative4_wifi_getRadioOperatingChannelBandwidth, test_l1_wifi_common_hal_positive1_wifi_getRadioExtChannel, test_l1_wifi_common_hal_negative1_wifi_getRadioExtChannel, test_l1_wifi_common_hal_negative2_wifi_getRadioExtChannel, test_l1_wifi_common_hal_negative3_wifi_getRadioExtChannel, test_l1_wifi_common_hal_negative4_wifi_getRadioExtChannel, test_l1_wifi_common_hal_positive1_wifi_getRadioMCS, test_l1_wifi_common_hal_negative1_wifi_getRadioMCS, test_l1_wifi_common_hal_negative2_wifi_getRadioMCS, test_l1_wifi_common_hal_negative3_wifi_getRadioMCS, test_l1_wifi_common_hal_positive1_wifi_getRadioTransmitPowerSupported, test_l1_wifi_common_hal_negative1_wifi_getRadioTransmitPowerSupported, test_l1_wifi_common_hal_negative2_wifi_getRadioTransmitPowerSupported, test_l1_wifi_common_hal_negative3_wifi_getRadioTransmitPowerSupported, test_l1_wifi_common_hal_negative4_wifi_getRadioTransmitPowerSupported, test_l1_wifi_common_hal_positive1_wifi_getRadioTransmitPower, test_l1_wifi_common_hal_negative1_wifi_getRadioTransmitPower, test_l1_wifi_common_hal_negative2_wifi_getRadioTransmitPower, test_l1_wifi_common_hal_negative3_wifi_getRadioTransmitPower, test_l1_wifi_common_hal_negative4_wifi_getRadioTransmitPower, test_l1_wifi_common_hal_positive_1_wifi_getRadioIEEE80211hSupported, test_l1_wifi_common_hal_negative_1_wifi_getRadioIEEE80211hSupported, test_l1_wifi_common_hal_negative_2_wifi_getRadioIEEE80211hSupported, test_l1_wifi_common_hal_negative_3_wifi_getRadioIEEE80211hSupported, test_l1_wifi_common_hal_positive1_wifi_getRadioIEEE80211hEnabled, test_l1_wifi_common_hal_negative1_wifi_getRadioIEEE80211hEnabled, test_l1_wifi_common_hal_negative2_wifi_getRadioIEEE80211hEnabled, test_l1_wifi_common_hal_negative3_wifi_getRadioIEEE80211hEnabled, test_l1_wifi_common_hal_positive1_wifi_getRegulatoryDomain, test_l1_wifi_common_hal_negative1_wifi_getRegulatoryDomain, test_l1_wifi_common_hal_negative2_wifi_getRegulatoryDomain, test_l1_wifi_common_hal_negative3_wifi_getRegulatoryDomain, test_l1_wifi_common_hal_negative4_wifi_getRegulatoryDomain, test_l1_wifi_common_hal_negative5_wifi_getRegulatoryDomain, test_l1_wifi_common_hal_negative6_wifi_getRegulatoryDomain, test_l1_wifi_common_hal_positive1_wifi_getRadioTrafficStats, test_l1_wifi_common_hal_negative1_wifi_getRadioTrafficStats, test_l1_wifi_common_hal_negative2_wifi_getRadioTrafficStats, test_l1_wifi_common_hal_negative3_wifi_getRadioTrafficStats, test_l1_wifi_common_hal_positive1_wifi_getSSIDName, test_l1_wifi_common_hal_negative1_wifi_getSSIDName, test_l1_wifi_common_hal_negative2_wifi_getSSIDName, test_l1_wifi_common_hal_negative3_wifi_getSSIDName, test_l1_wifi_common_hal_boundary1_wifi_getSSIDName, test_l1_wifi_common_hal_positive1_wifi_getBaseBSSID, test_l1_wifi_common_hal_negative1_wifi_getBaseBSSID, test_l1_wifi_common_hal_negative2_wifi_getBaseBSSID, test_l1_wifi_common_hal_negative3_wifi_getBaseBSSID, test_l1_wifi_common_hal_positive1_wifi_getSSIDMACAddress, test_l1_wifi_common_hal_negative1_wifi_getSSIDMACAddress, test_l1_wifi_common_hal_negative2_wifi_getSSIDMACAddress, test_l1_wifi_common_hal_negative3_wifi_getSSIDMACAddress, test_l1_wifi_common_hal_positive1_wifi_getSSIDTrafficStats, test_l1_wifi_common_hal_negative1_wifi_getSSIDTrafficStats, test_l1_wifi_common_hal_negative2_wifi_getSSIDTrafficStats, test_l1_wifi_common_hal_negative3_wifi_getSSIDTrafficStats, test_l1_wifi_common_hal_negative4_wifi_getSSIDTrafficStats, test_l1_wifi_common_hal_positive1_wifi_getNeighboringWiFiDiagnosticResult, test_l1_wifi_common_hal_negative1_wifi_getNeighboringWiFiDiagnosticResult, test_l1_wifi_common_hal_negative2_wifi_getNeighboringWiFiDiagnosticResult, test_l1_wifi_common_hal_negative3_wifi_getNeighboringWiFiDiagnosticResult, test_l1_wifi_common_hal_negative4_wifi_getNeighboringWiFiDiagnosticResult, test_l1_wifi_common_hal_positive1_wifi_getSpecificSSIDInfo, test_l1_wifi_common_hal_negative1_wifi_getSpecificSSIDInfo, test_l1_wifi_common_hal_negative2_wifi_getSpecificSSIDInfo, test_l1_wifi_common_hal_negative3_wifi_getSpecificSSIDInfo, test_l1_wifi_common_hal_negative4_wifi_getSpecificSSIDInfo, test_l1_wifi_common_hal_positive1_wifi_setRadioScanningFreqList, test_l1_wifi_common_hal_negative1_wifi_setRadioScanningFreqList, test_l1_wifi_common_hal_negative2_wifi_setRadioScanningFreqList, test_l1_wifi_common_hal_negative3_wifi_setRadioScanningFreqList, test_l1_wifi_common_hal_negative4_wifi_setRadioScanningFreqList, test_l1_wifi_common_hal_negative5_wifi_setRadioScanningFreqList, test_l1_wifi_common_hal_negative6_wifi_setRadioScanningFreqList, test_l1_wifi_common_hal_positive1_getDualBandSupport, test_l1_wifi_common_hal_positive1_wifi_waitForScanResults, test_l1_wifi_common_hal_negative1_wifi_waitForScanResults };
    // Add tests to the suite
    for (int i = 0; i < sizeof(list1) / sizeof(list1[0]); i++) {
        UT_add_test(pSuite, list1[i], list2[i]);
    }
    return 0;
}
 