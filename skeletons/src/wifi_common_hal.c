#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include "wifi_common_hal.h"


INT wifi_getHalVersion(CHAR* output_string)
{
  /*TODO: Implement Me!*/
  (void)output_string;
  return (INT)0;
}

INT wifi_init(void)
{
  /*TODO: Implement Me!*/
  return (INT)0;
}

INT wifi_initWithConfig(wifi_halConfig_t* conf)
{
  /*TODO: Implement Me!*/
  (void)conf;
  return (INT)0;
}

INT wifi_down(void)
{
  /*TODO: Implement Me!*/
  return (INT)0;
}

INT wifi_uninit(void)
{
  /*TODO: Implement Me!*/
  return (INT)0;
}

void wifi_getStats(INT radioIndex, wifi_sta_stats_t* wifi_sta_stats)
{
  /*TODO: Implement Me!*/
  (void)radioIndex;
  (void)wifi_sta_stats;
}

INT wifi_getRadioNumberOfEntries(ULONG* output)
{
  /*TODO: Implement Me!*/
  (void)output;
  return (INT)0;
}

INT wifi_getSSIDNumberOfEntries(ULONG* output)
{
  /*TODO: Implement Me!*/
  (void)output;
  return (INT)0;
}

INT wifi_getRadioEnable(INT radioIndex, BOOL* output_bool)
{
  /*TODO: Implement Me!*/
  (void)radioIndex;
  (void)output_bool;
  return (INT)0;
}

INT wifi_getRadioStatus(INT radioIndex, CHAR* output_string)
{
  /*TODO: Implement Me!*/
  (void)radioIndex;
  (void)output_string;
  return (INT)0;
}

INT wifi_getRadioIfName(INT radioIndex, CHAR* output_string)
{
  /*TODO: Implement Me!*/
  (void)radioIndex;
  (void)output_string;
  return (INT)0;
}

INT wifi_getRadioMaxBitRate(INT radioIndex, CHAR* output_string)
{
  /*TODO: Implement Me!*/
  (void)radioIndex;
  (void)output_string;
  return (INT)0;
}

INT wifi_getRadioSupportedFrequencyBands(INT radioIndex, CHAR* output_string)
{
  /*TODO: Implement Me!*/
  (void)radioIndex;
  (void)output_string;
  return (INT)0;
}

INT wifi_getRadioOperatingFrequencyBand(INT radioIndex, CHAR* output_string)
{
  /*TODO: Implement Me!*/
  (void)radioIndex;
  (void)output_string;
  return (INT)0;
}

INT wifi_getRadioSupportedStandards(INT radioIndex, CHAR* output_string)
{
  /*TODO: Implement Me!*/
  (void)radioIndex;
  (void)output_string;
  return (INT)0;
}

INT wifi_getRadioStandard(INT radioIndex, CHAR* output_string, BOOL* gOnly, BOOL* nOnly, BOOL* acOnly)
{
  /*TODO: Implement Me!*/
  (void)radioIndex;
  (void)output_string;
  (void)gOnly;
  (void)nOnly;
  (void)acOnly;
  return (INT)0;
}

INT wifi_getRadioPossibleChannels(INT radioIndex, CHAR* output_string)
{
  /*TODO: Implement Me!*/
  (void)radioIndex;
  (void)output_string;
  return (INT)0;
}

INT wifi_getRadioChannelsInUse(INT radioIndex, CHAR* output_string)
{
  /*TODO: Implement Me!*/
  (void)radioIndex;
  (void)output_string;
  return (INT)0;
}

INT wifi_getRadioChannel(INT radioIndex, ULONG* output_ulong)
{
  /*TODO: Implement Me!*/
  (void)radioIndex;
  (void)output_ulong;
  return (INT)0;
}

INT wifi_getRadioAutoChannelSupported(INT radioIndex, BOOL* output_bool)
{
  /*TODO: Implement Me!*/
  (void)radioIndex;
  (void)output_bool;
  return (INT)0;
}

INT wifi_getRadioAutoChannelEnable(INT radioIndex, BOOL* output_bool)
{
  /*TODO: Implement Me!*/
  (void)radioIndex;
  (void)output_bool;
  return (INT)0;
}

INT wifi_getRadioAutoChannelRefreshPeriod(INT radioIndex, ULONG* output_ulong)
{
  /*TODO: Implement Me!*/
  (void)radioIndex;
  (void)output_ulong;
  return (INT)0;
}

INT wifi_getRadioGuardInterval(INT radioIndex, CHAR* output_string)
{
  /*TODO: Implement Me!*/
  (void)radioIndex;
  (void)output_string;
  return (INT)0;
}

INT wifi_getRadioOperatingChannelBandwidth(INT radioIndex, CHAR* output_string)
{
  /*TODO: Implement Me!*/
  (void)radioIndex;
  (void)output_string;
  return (INT)0;
}

INT wifi_getRadioExtChannel(INT radioIndex, CHAR* output_string)
{
  /*TODO: Implement Me!*/
  (void)radioIndex;
  (void)output_string;
  return (INT)0;
}

INT wifi_getRadioMCS(INT radioIndex, INT* output_INT)
{
  /*TODO: Implement Me!*/
  (void)radioIndex;
  (void)output_INT;
  return (INT)0;
}

INT wifi_getRadioTransmitPowerSupported(INT radioIndex, CHAR* output_list)
{
  /*TODO: Implement Me!*/
  (void)radioIndex;
  (void)output_list;
  return (INT)0;
}

INT wifi_getRadioTransmitPower(INT radioIndex, INT* output_INT)
{
  /*TODO: Implement Me!*/
  (void)radioIndex;
  (void)output_INT;
  return (INT)0;
}

INT wifi_getRadioIEEE80211hSupported(INT radioIndex, BOOL* Supported)
{
  /*TODO: Implement Me!*/
  (void)radioIndex;
  (void)Supported;
  return (INT)0;
}

INT wifi_getRadioIEEE80211hEnabled(INT radioIndex, BOOL* enable)
{
  /*TODO: Implement Me!*/
  (void)radioIndex;
  (void)enable;
  return (INT)0;
}

INT wifi_getRegulatoryDomain(INT radioIndex, CHAR* output_string)
{
  /*TODO: Implement Me!*/
  (void)radioIndex;
  (void)output_string;
  return (INT)0;
}

INT wifi_getRadioTrafficStats(INT radioIndex, wifi_radioTrafficStats_t* output_struct)
{
  /*TODO: Implement Me!*/
  (void)radioIndex;
  (void)output_struct;
  return (INT)0;
}

INT wifi_getSSIDName(INT ssidIndex, CHAR* output_string)
{
  /*TODO: Implement Me!*/
  (void)ssidIndex;
  (void)output_string;
  return (INT)0;
}

INT wifi_getBaseBSSID(INT ssidIndex, CHAR* output_string)
{
  /*TODO: Implement Me!*/
  (void)ssidIndex;
  (void)output_string;
  return (INT)0;
}

INT wifi_getSSIDMACAddress(INT ssidIndex, CHAR* output_string)
{
  /*TODO: Implement Me!*/
  (void)ssidIndex;
  (void)output_string;
  return (INT)0;
}

INT wifi_getSSIDTrafficStats(INT ssidIndex, wifi_ssidTrafficStats_t* output_struct)
{
  /*TODO: Implement Me!*/
  (void)ssidIndex;
  (void)output_struct;
  return (INT)0;
}

INT wifi_getNeighboringWiFiDiagnosticResult(INT radioIndex, wifi_neighbor_ap_t** neighbor_ap_array, UINT* output_array_size)
{
  /*TODO: Implement Me!*/
  (void)radioIndex;
  (void)neighbor_ap_array;
  (void)output_array_size;
  return (INT)0;
}

INT wifi_getSpecificSSIDInfo(const char* SSID, WIFI_HAL_FREQ_BAND band, wifi_neighbor_ap_t** ap_array, UINT* output_array_size)
{
  /*TODO: Implement Me!*/
  (void)SSID;
  (void)band;
  (void)ap_array;
  (void)output_array_size;
  return (INT)0;
}

INT wifi_setRadioScanningFreqList(INT radioIndex, const CHAR* freqList)
{
  /*TODO: Implement Me!*/
  (void)radioIndex;
  (void)freqList;
  return (INT)0;
}

INT wifi_getDualBandSupport(void)
{
  /*TODO: Implement Me!*/
  return (INT)0;
}

INT wifi_waitForScanResults(void)
{
  /*TODO: Implement Me!*/
  return (INT)0;
}

