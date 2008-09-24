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
#ifndef INCL_DEVICE_CONFIG
#define INCL_DEVICE_CONFIG
/** @cond DEV */

#include "base/fscapi.h"
#include "spds/constants.h"
#include "syncml/core/VerDTD.h"
#include "base/Log.h"
#include "base/globalsdef.h"

BEGIN_NAMESPACE

/*
 * ---------------------------- DeviceConfig class -------------------------------
 * This class groups all configuration properties related to the device.
 * Most of DeviceConfig properties are used to generate the
 * <DevInf> element for client capabilities.
 * DeviceConfig is a part of SyncManagerConfig (along with AccessConfig
 * and an array of SyncSourceConfig).
 */
class DeviceConfig {

    private:

        char*         man          ;
        char*         mod          ;
        char*         oem          ;
        char*         fwv          ;
        char*         swv          ;
        char*         hwv          ;
        char*         devID        ;
        char*         devType      ;
        char*         dsV          ;
        bool          utc          ;
        bool          loSupport    ;
        bool          nocSupport   ;
        LogLevel      logLevel     ;
        unsigned int  maxObjSize   ;
        char*         devInfHash   ;


        /**
         * Sets the given buffer with the given value, dealing correctly with
         * NULL values. If a NULL value is passed, the empty string is used.
         *
         * @param buf the destination buffer
         * @param v the new value (CAN BE NULL)
         */
        void set(char* * buf, const char*  v);


    public:

        DeviceConfig();
        DeviceConfig(DeviceConfig& s);
        ~DeviceConfig();


        /**
         * Methods to get/set data values.
         * -----------------------------------------------------
         * get: return the internal value.
         *      The caller MUST NOT release the memory itself.
         *
         * set: set the internal value.
         *      The given data are copied in an internal
         *      buffer so that the caller is assured that the
         *      given address can be released after the call.
         */
        const char*  getMan() const            ;
        void setMan(const char*  v)            ;

        const char*  getMod() const            ;
        void setMod(const char*  v)            ;

        const char*  getOem() const            ;
        void setOem(const char*  v)            ;

        const char*  getFwv() const            ;
        void setFwv(const char*  v)            ;

        const char*  getSwv() const            ;
        void setSwv(const char*  v)            ;

        const char*  getHwv() const            ;
        void setHwv(const char*  v)            ;

        const char*  getDevID() const          ;
        void setDevID(const char*  v)          ;

        const char*  getDevType() const        ;
        void setDevType(const char*  v)        ;

        const char*  getDsV() const            ;
        void setDsV(const char*  v)            ;

        bool getUtc() const                    ;
        void setUtc(bool v)                    ;

        bool getLoSupport() const              ;
        void setLoSupport(bool v)              ;

        bool getNocSupport() const             ;
        void setNocSupport(bool v)             ;

        LogLevel getLogLevel() const           ;
        void setLogLevel(LogLevel v)           ;

        unsigned int getMaxObjSize() const     ;
        void setMaxObjSize(unsigned int v)     ;

        const char*  getDevInfHash() const     ;
        void setDevInfHash(const char *v)     ;

        /**
         * Sets the values of this object with with the values from the given
         * DeviceConfig source object.
         *
         * @param s: the deviceConfig reference.
         */
        void assign(const DeviceConfig& s);

        /*
         * Assign operator
         */
        DeviceConfig& operator = (const DeviceConfig& dc) {
            assign(dc);
            return *this;
        }
};


END_NAMESPACE

/** @endcond */
#endif
