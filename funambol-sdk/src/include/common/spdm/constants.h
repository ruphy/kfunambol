/*
 * Funambol is a mobile platform developed by Funambol, Inc. 
 * Copyright (C) 2003 - 2007 Funambol, Inc.
 * 
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Affero General Public License version 3 as published by
 * the Free Software Foundation with the addition of the following permission 
 * added to Section 15 as permitted in Section 7(a): FOR ANY PART OF THE COVERED
 * WORK IN WHICH THE COPYRIGHT IS OWNED BY FUNAMBOL, FUNAMBOL DISCLAIMS THE 
 * WARRANTY OF NON INFRINGEMENT  OF THIRD PARTY RIGHTS.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 * 
 * You should have received a copy of the GNU Affero General Public License 
 * along with this program; if not, see http://www.gnu.org/licenses or write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301 USA.
 * 
 * You can contact Funambol, Inc. headquarters at 643 Bair Island Road, Suite 
 * 305, Redwood City, CA 94063, USA, or at email address info@funambol.com.
 * 
 * The interactive user interfaces in modified source and object code versions
 * of this program must display Appropriate Legal Notices, as required under
 * Section 5 of the GNU Affero General Public License version 3.
 * 
 * In accordance with Section 7(b) of the GNU Affero General Public License
 * version 3, these Appropriate Legal Notices must retain the display of the
 * "Powered by Funambol" logo. If the display of the logo is not reasonably 
 * feasible for technical reasons, the Appropriate Legal Notices must display
 * the words "Powered by Funambol".
 */

#ifndef INCL_SPDM_CONSTANTS
#define INCL_SPDM_CONSTANTS
/** @cond DEV */

#define DIM_MANAGEMENT_PATH 512
#define DIM_PROPERTY_NAME    64

#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 512


#define PROPERTY_USERNAME              "username"
#define PROPERTY_PASSWORD              "password"
#define PROPERTY_FIRST_TIME_SYNC_MODE  "firstTimeSyncMode"
#define PROPERTY_USE_PROXY             "useProxy"
#define PROPERTY_PROXY_HOST            "proxyHost"
#define PROPERTY_PROXY_PORT            "proxyPort"
#define PROPERTY_PROXY_USERNAME        "proxyUsername"
#define PROPERTY_PROXY_PASSWORD        "proxyPassword"
#define PROPERTY_SERVER_NAME           "serverName"
#define PROPERTY_SYNC_URL              "syncUrl"
#define PROPERTY_SYNC_BEGIN            "begin"
#define PROPERTY_SYNC_END              "end"
#define PROPERTY_SOURCE_NAME           "name"
#define PROPERTY_SOURCE_URI            "uri"
#define PROPERTY_SOURCE_SYNC_MODES     "syncModes"
#define PROPERTY_SOURCE_TYPE           "type"
#define PROPERTY_SOURCE_VERSION        "version"
#define PROPERTY_SOURCE_SYNC           "sync"
#define PROPERTY_SOURCE_LAST_SYNC      "last"
#define PROPERTY_SOURCE_CTCAP          "ctCap"
#define PROPERTY_SERVER_NONCE          "serverNonce"
#define PROPERTY_CLIENT_NONCE          "clientNonce"
#define PROPERTY_SERVER_ID             "serverID"
#define PROPERTY_SERVER_PWD            "serverPWD"
#define PROPERTY_CLIENT_AUTH_TYPE      "clientAuthType"
#define PROPERTY_SERVER_AUTH_TYPE      "serverAuthType"
#define PROPERTY_IS_SERVER_REQUIRED    "isServerAuthRequired"
#define PROPERTY_MAX_MSG_SIZE          "maxMsgSize"
#define PROPERTY_SOURCE_DOWNLOAD_AGE   "downloadAge"
#define PROPERTY_SOURCE_BODY_SIZE      "bodySize"
#define PROPERTY_SOURCE_ATTACH_SIZE    "attachSize"
#define PROPERTY_SOURCE_INBOX          "Inbox"
#define PROPERTY_SOURCE_OUTBOX         "Outbox"
#define PROPERTY_SOURCE_DRAFT          "Draft"
#define PROPERTY_SOURCE_TRASH          "Trash"
#define PROPERTY_SOURCE_SENT           "Sent"
#define PROPERTY_SOURCE_ENCODING       "encoding"
#define PROPERTY_SOURCE_SUPP_TYPES     "supportedTypes"
#define PROPERTY_READ_BUFFER_SIZE      "readBufferSize"
#define PROPERTY_USER_AGENT            "userAgent"
#define PROPERTY_CHECK_CONN            "checkConn"
#define PROPERTY_RESPONSE_TIMEOUT      "responseTimeout"
#define PROPERTY_SOURCE_SCHEDULE       "schedule"
#define PROPERTY_SOURCE_ENCRYPTION     "encryption"
#define PROPERTY_ENABLE_COMPRESSION    "enableCompression"

// Push related
#define PROPERTY_PUSH_NOTIFICATION     "push"
#define PROPERTY_POLLING_NOTIFICATION  "polling"

// DeviceConfig properties
#define PROPERTY_VER_DTD                    "verDTD"
#define PROPERTY_MANUFACTURER               "man"
#define PROPERTY_MODEL                      "mod"
#define PROPERTY_OEM                        "oem"
#define PROPERTY_FIRMWARE_VERSION           "fwv"
#define PROPERTY_SOFTWARE_VERSION           "swv"
#define PROPERTY_HARDWARE_VERSION           "hwv"
#define PROPERTY_DEVICE_ID                  "devID"
#define PROPERTY_DEVICE_TYPE                "devType"
#define PROPERTY_DS_VERSION                 "dsV"
#define PROPERTY_UTC                        "utc"
#define PROPERTY_LARGE_OBJECT_SUPPORT       "loSupport"
#define PROPERTY_NUMBER_OF_CHANGES_SUPPORT  "nocSupport"
#define PROPERTY_LOG_LEVEL                  "logLevel"
#define PROPERTY_MAX_OBJ_SIZE               "maxObjSize"
#define PROPERTY_DEVINF_HASH                "devInfHash"



#define DIRTY_USERNAME                 0x00001
#define DIRTY_PASSWORD                 0x00002
#define DIRTY_DEVICE_ID                0x00004
#define DIRTY_FIRST_TIME_SYNC_MODE     0x00008
#define DIRTY_USE_PROXY                0x00010
#define DIRTY_PROXY_HOST               0x00020
#define DIRTY_PROXY_PORT               0x00040
#define DIRTY_SERVER_NAME              0x00080
#define DIRTY_SYNC_URL                 0x00100
#define DIRTY_SYNC_BEGIN               0x00200
#define DIRTY_SYNC_END                 0x00400
#define DIRTY_SYNC_SOURCE              0x00800
#define DIRTY_CLIENT_NONCE             0x01000
#define DIRTY_SERVER_NONCE             0x02000
#define DIRTY_SERVERID                 0x04000
#define DIRTY_SERVERPWD                0x08000
#define DIRTY_CLIENTAUTHTYPE           0x10000
#define DIRTY_SERVERAUTH_REQUIRED      0x20000
#define DIRTY_DEV_INF_HASH             0x40000


/** @endcond */
#endif
