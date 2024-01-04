# Unit Testing Suite For RDK-V WiFi HAL

## Table of Contents

- [Acronyms, Terms and Abbreviations](#acronyms-terms-and-abbreviations)
- [Description](#description)
- [Reference Documents](#reference-documents)
- [Notes](#notes)

## Acronyms, Terms and Abbreviations

- `L1` - Functional Tests
- `HAL`- Hardware Abstraction Layer

## Description

This repository contains the Unit Test Suites (L1) for RDK-V WiFi `HAL`.

## Reference Documents

<!-- Need to update links to rdkcentral and point to branch main-->
|SNo|Document Name|Document Description|Document Link|
|---|-------------|--------------------|-------------|
|1|`HAL` Specification Document|This document provides specific information on the APIs for which tests are written in this module|[rdkv-wifi_halSpec.md -v2.0.0](https://github.com/rdkcentral/rdkv-halif-wifi/blob/2.0.0/docs/pages/rdkv-wifi_halSpec.md "rdkv-wifi_halSpec.md")|
|2|`L1` Tests |`L1` Test Case File for this module |[test_L1_wifi_client_hal.c -v1.0.0](https://github.com/rdkcentral/rdkv-halif-test-wifi/blob/1.0.0/src/test_L1_wifi_client_hal.c "test_L1_wifi_client_hal.c")|

## Notes

- All APIs need to be implemented in this current version. If any API is not supported, please add stub implementation with return type WIFI_HAL_SUCCESS for the same.
- Building against the actual library may introduce SOC dependencies. Hence, a template SKELETON library is created without SOC dependencies. On the real platform (target), it can be mounted, copied and bound with the actual library.