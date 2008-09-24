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


#ifndef INCL_PARSER
#define INCL_PARSER
/** @cond DEV */

#include "base/fscapi.h"
#include "base/util/utils.h"
#include "base/util/XMLProcessor.h"
#include "base/util/ArrayList.h"
#include "syncml/core/ObjectDel.h"
#include "base/globalsdef.h"

BEGIN_NAMESPACE

class Parser {

    // ---------------------------------------------------------- Public data
    public:
        static SyncML*          getSyncML           (const char* xml);
        static SyncHdr*         getSyncHdr          (const char* xml);
        static SyncBody*        getSyncBody         (const char* xml);
        static SessionID*       getSessionID        (const char* xml);
        static VerDTD*          getVerDTD           (const char* xml);
        static VerProto*        getVerProto         (const char* xml);
        static Target*          getTarget           (const char* xml);
        static Source*          getSource           (const char* xml);
        static Cred*            getCred             (const char* xml);
        static Anchor*          getAnchor           (const char* xml);
        static NextNonce*       getNextNonce        (const char* xml);
        static Mem*             getMem              (const char* xml);
        static ArrayList*       getEMI              (const char* xml);
        static Meta*            getMeta             (const char* xml);
        static MetInf*          getMetInf           (const char* xml);
        static Authentication*  getAuthentication   (const char* xml);
        static ArrayList*       getCommands         (const char* xml);
        static Alert*           getAlert            (const char* xml);
        static bool             getFinalMsg         (const char* xml);
        static int              getDataCode         (const char* xml);
        static Data*            getData             (const char* xml);
        static bool             getNoResp           (const char* xml);
        static bool             getNoResults        (const char* xml);
        static CmdID*           getCmdID            (const char* xml);
        static Item*            getItem             (const char* xml, const char* command = NULL);
        static ArrayList*       getItems            (const char* xml, const char* command = NULL);
        static ComplexData*     getComplexData      (const char* xml, const char* command = NULL);
        static bool             getMoreData         (const char* xml);
        static Status*          getStatus           (const char* xml);
        static DevInf*          getDevInf           (const char* xml);
        static TargetRef*       getTargetRef        (const char* xml);
        static SourceRef*       getSourceRef        (const char* xml);
        static ArrayList*       getTargetRefs       (const char* xml);
        static ArrayList*       getSourceRefs       (const char* xml);
        static Chal*            getChal             (const char* xml);
        static Map*             getMap              (const char* xml);
        static MapItem*         getMapItem          (const char* xml);
        static ArrayList*       getMapItems         (const char* xml);
        static Add*             getAdd              (const char* xml);
        static Sync*            getSync             (const char* xml);
        static Replace*         getReplace          (const char* xml);
        static Delete*          getDelete           (const char* xml);
        static Copy*            getCopy             (const char* xml);
        static Sequence*        getSequence         (const char* xml);
        static Atomic*          getAtomic           (const char* xml);
        static ArrayList*       getAdds             (const char* xml, const char* except);
        static ArrayList*       getReplaces         (const char* xml, const char* except);
        static ArrayList*       getDels             (const char* xml, const char* except);
        static ArrayList*       getCopies           (const char* xml, const char* except);
        static ArrayList*       getCommonCommandList(const char* xml, const char* except);
        static Get*             getGet              (const char* xml);
        static Put*             getPut              (const char* xml);
        static DataStore*       getDataStore        (const char* xml);
        static ContentTypeInfo* getContentTypeInfo  (const char* xml);
        static DSMem*           getDSMem            (const char* xml);
        static SyncCap*         getSyncCap          (const char* xml);
        static SyncType*        getSyncType         (const char* xml);
        static CTCap*           getCTCap            (const char* xml);
        static Ext*             getExt              (const char* xml);
        static Results*         getResult           (const char* xml);
        static Exec*            getExec             (const char* xml);
        static Search*          getSearch           (const char* xml);
        static ArrayList*       getSources          (const char* xml);
};


END_NAMESPACE

/** @endcond */
#endif




