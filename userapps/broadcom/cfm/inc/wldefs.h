/*****************************************************************************
//
//  Copyright (c) 2000-2002  Broadcom Corporation
//  All Rights Reserved
//  No portions of this material may be reproduced in any form without the
//  written permission of:
//          Broadcom Corporation
//          16215 Alton Parkway
//          Irvine, California 92619
//  All information contained in this document is Broadcom Corporation
//  company private, proprietary, and trade secret.
//
******************************************************************************
//
//  Filename:       wldefs.h
//  Author:         Peter T. Tran
//  Creation Date:  10/17/02
//
******************************************************************************
//  Description:
//      Define the WlDefs functions.
//
*****************************************************************************/

#ifndef __WL_DEFS_H__
#define __WL_DEFS_H__

/********************** Include Files ***************************************/

#include <stdio.h>
#include <netinet/in.h>

/********************** Global Constants ************************************/

#define WL_NUM_SSID    2
#define WL_SIZE_2_MAX    2  
#define WL_SIZE_4_MAX    4  
#define WL_SIZE_8_MAX    8  
#define WL_SIZE_132_MAX  132
#define WL_SM_SIZE_MAX   16
#define WL_MID_SIZE_MAX  32
#define WL_SSID_SIZE_MAX 48
#define WL_MIN_PSK_LEN	8
#define WL_MAX_PSK_LEN	64
#define WL_WPA_PSK_SIZE_MAX  72  // max 64 hex or 63 char
#define WL_RADIUS_KEY_SIZE_MAX  88 // max is 80, limited by nas_wksp.h.  IAS allow up to 128 char
#define WL_LG_SIZE_MAX   1024
#define WL_MAC_ADDR_SIZE_MAX	18 // USR9108
#define WL_KEY_NUM       4
#define WL_WDS_NUM       4
#define WL_MIN_FRAGMENTATION_THRESHOLD  256
#define WL_MAX_FRAGMENTATION_THRESHOLD  2346
#define WL_MIN_RTS_THRESHOLD            0
#define WL_MAX_RTS_THRESHOLD            2347
#define WL_MIN_DTIM                     1
#define WL_MAX_DTIM                     255
#define WL_MIN_BEACON_INTERVAL          1
#define WL_MAX_BEACON_INTERVAL          65535
#define WL_KEY64_SIZE_HEX               10
#define WL_KEY64_SIZE_CHAR              5
#define WL_KEY128_SIZE_HEX              26
#define WL_KEY128_SIZE_CHAR             13

#define WL_FLT_MAC_OFF   "disabled"
#define WL_FLT_MAC_ALLOW "allow"
#define WL_FLT_MAC_DENY  "deny"

#define WL_BRIDGE_RESTRICT_ENABLE      0
#define WL_BRIDGE_RESTRICT_DISABLE     1
#define WL_BRIDGE_RESTRICT_ENABLE_SCAN 2

/* authentication mode */
#define WL_AUTH_OPEN     		"open"
#define WL_AUTH_SHARED   		"shared"
#define WL_AUTH_RADIUS   		"radius"
#define WL_AUTH_WPA      		"wpa"
#define WL_AUTH_WPA_PSK  		"psk"
#define WL_AUTH_WPA2     		"wpa2"
#define WL_AUTH_WPA2_PSK 		"psk2"
#define WL_AUTH_WPA2_MIX 		"wpa2mix"
#define WL_AUTH_WPA2_PSK_MIX 	"psk2mix"
#define WL_WPA_AUTH_DISABLED		0x0000	/* Legacy (i.e., non-WPA) */
#define WL_WPA_AUTH_NONE			0x0001	/* none (IBSS) */
#define WL_WPA_AUTH_UNSPECIFIED		0x0002	/* over 802.1x */
#define WL_WPA_AUTH_PSK				0x0004	/* Pre-shared key */
#define WL_WPA_AUTH_8021X 			0x0020	/* 802.1x, reserved */
#define WL_WPA2_AUTH_UNSPECIFIED	0x0040	/* over 802.1x */
#define WL_WPA2_AUTH_PSK			0x0080	/* Pre-shared key */

/* wireless security bitvec */
#define WEP_ENABLED      1
#define TKIP_ENABLED     2
#define AES_ENABLED      4
#define WSEC_SWFLAG      8

#define	WPA_CAP_WPA2_PREAUTH		1

#define WL_BIT_KEY_128   0
#define WL_BIT_KEY_64    1

#define WL_PHY_TYPE_A    "a"
#define WL_PHY_TYPE_B    "b"
#define WL_PHY_TYPE_G    "g"

#define WL_BASIC_RATE_DEFAULT    "default"
#define WL_BASIC_RATE_ALL        "all"
#define WL_BASIC_RATE_1_2        "12"
#define WL_BASIC_RATE_WIFI_2     "wifi2"

#define WL_MODE_G_AUTO           1
#define WL_MODE_G_PERFORMANCE    4
#define WL_MODE_G_LRS            5
#define WL_MODE_B_ONLY           0

#define WL_AUTO                  "auto"
#define WL_OFF                   "off"
#define WL_ON                    "on"
#define WL_DISABLED              "disabled"
#define WL_ENABLED               "enabled"

#define WL_WME_ON		 		1 
#define WL_WME_OFF		 		0

#define WL_PREAUTH_ON			1
#define WL_PREAUTH_OFF			0

#define BAND_A                   1
#define BAND_B                   2

#define WIRELESS_APPID          "WirelessCfg"
#define WL_VARS_ID              1
#define WL_MSSID_VARS_NUM_ID    2
#define WL_MSSID_VARS_TBL_ID    3
#define WL_FLT_MAC_NUM_ID       4
#define WL_FLT_MAC_TBL_ID       5
#define WL_WDS_MAC_NUM_ID       6
#define WL_WDS_MAC_TBL_ID       7
#define WL_SCAN_WDS_MAC_NUM_ID  8
#define WL_SCAN_WDS_MAC_TBL_ID  9

#define RESET_WLAN	"/var/reset.wlan"


#define MAP_FROM_NVRAM	0
#define MAP_TO_NVRAM	1
#define WL_SES_ENTRY	99
#define MAX_NVPARSE 100
#define SES_WDS_MODE_DISABLED           0 /* disabled */
#define SES_WDS_MODE_AUTO               1 /* dynamic cf/cl selection */
#define SES_WDS_MODE_ENABLED_ALWAYS     2 /* enabled always */
#define SES_WDS_MODE_ENABLED_EXCL       3 /* WDS-only i.e no regular STAs */
#define SES_WDS_MODE_CLIENT             4 /* always wds client mode */
#define REG_MODE_OFF                    0 /* disabled 11h/d mode */
#define REG_MODE_H                      1 /* use 11h mode */
#define REG_MODE_D                      2 /* use 11d mode */
/********************** Global Structs ****************************************/

typedef enum {
   WL_STS_OK = 0,
   WL_STS_ERR_GENERAL,
   WL_STS_ERR_MEMORY,
   WL_STS_ERR_OBJECT_NOT_FOUND
} WL_STATUS;

typedef enum {
   WL_SETUP_ALL = 0,
   WL_SETUP_BASIC,
   WL_SETUP_SECURITY,
   WL_SETUP_MAC_FILTER,
   WL_SETUP_WDS,
   WL_SETUP_ADVANCED,
   WL_SETUP_SES /*SUPPORT_SES*/
} WL_SETUP_TYPE;

typedef struct {
   int wlSsidIdx;
   char wlMode[WL_SM_SIZE_MAX];
   char wlCountry[WL_SM_SIZE_MAX];
   char wlFltMacMode[WL_SM_SIZE_MAX];
   char wlPhyType[WL_SIZE_2_MAX];
   char wlBasicRate[WL_SIZE_8_MAX];
   char wlProtection[WL_SIZE_8_MAX];
   char wlPreambleType[WL_SM_SIZE_MAX];
   char wlAfterBurnerEn[WL_SIZE_8_MAX];
   char wlFrameBurst[WL_SIZE_4_MAX];
   char wlWlanIfName[WL_SIZE_4_MAX];
   char wlWds[WL_WDS_NUM][WL_MID_SIZE_MAX];
   int  wlCoreRev;
   int  wlHide;
   int  wlEnbl;
   int  wlChannel;
   int  wlFrgThrshld;
   int  wlRtsThrshld;
   int  wlDtmIntvl;
   int  wlBcnIntvl;
   long wlRate;
   int  wlgMode;
   int  wlLazyWds;
   int  wlAPIsolation;
   int  wlBand;
   int  wlMCastRate;
   int  ezc_version;
   int  ezc_enable;
   int  wlInfra;
   int  wlAntDiv;
   int	wlWme;
   int  wlWmeNoAck;
#ifdef SUPPORT_SES   
   int	wlSesEnable;
   int  wlSesEvent;
   char wlSesStates[WL_SIZE_8_MAX];
   char wlSesSsid[WL_SSID_SIZE_MAX];
   char wlSesWpaPsk[WL_WPA_PSK_SIZE_MAX];  
   int  wlSesHide;
   int  wlSesAuth; 
   char wlSesAuthMode[WL_SIZE_8_MAX]; 
   char wlSesWep[WL_SM_SIZE_MAX];   
   char wlSesWpa[WL_SM_SIZE_MAX];      
   int  wlSesWdsMode;      
   int	wlSesClEnable;   
   int  wlSesClEvent;   
   char wlWdsWsec[WL_SIZE_132_MAX];      
#endif   
   int  wlTxPwrPcnt;
   int  wlRegMode;
   int  wlDfsPreIsm;
   int  wlDfsPostIsm; 
   int  wlTpcDb;       
} WIRELESS_VAR, *PWIRELESS_VAR;

typedef struct {
   char wlSsid[WL_SSID_SIZE_MAX];
   char wlKeys128[WL_KEY_NUM][WL_MID_SIZE_MAX];
   char wlKeys64[WL_KEY_NUM][WL_SM_SIZE_MAX];
   char wlWpaPsk[WL_WPA_PSK_SIZE_MAX];
   char wlRadiusKey[WL_RADIUS_KEY_SIZE_MAX];
   char wlWep[WL_SM_SIZE_MAX];
   char wlWpa[WL_SM_SIZE_MAX];
   struct in_addr wlRadiusServerIP;
   char wlAuthMode[WL_SIZE_8_MAX];
   int  wlWpaGTKRekey;
   int  wlRadiusPort;
   int  wlAuth;
   int  wlEnblSsid;
   int  wlKeyIndex128;
   int  wlKeyIndex64;
   int  wlKeyBit;
   int  is_default;
   int  is_modified;
   int  wlPreauth;
   int  wlNetReauth;
   int  wlNasWillrun; /*runtime*/
   char wlSecurity[WL_SSID_SIZE_MAX];	// USR9108 Quick setup security.
} WIRELESS_MSSID_VAR, *PWIRELESS_MSSID_VAR;


typedef struct {
   char *varName;
   char *varValue;
} WIRELESS_ITEM, *PWIRELESS_ITEM;

typedef struct {
   char macAddress[WL_MID_SIZE_MAX];
   char ssid[WL_SSID_SIZE_MAX];
} WL_FLT_MAC_ENTRY, *PWL_FLT_MAC_ENTRY;

typedef struct { // don't want store ssid
   char macAddress[WL_MID_SIZE_MAX];
} WL_FLT_MAC_STORE_ENTRY, *PWL_FLT_MAC_STORE_ENTRY;

typedef struct {
   char macAddress[WL_MID_SIZE_MAX];
   char associated;
   char authorized;
} WL_STATION_LIST_ENTRY, *PWL_STATION_LIST_ENTRY;


#endif
