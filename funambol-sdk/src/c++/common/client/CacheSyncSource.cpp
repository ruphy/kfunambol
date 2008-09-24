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

#include "spds/SyncSource.h"
#include "base/Log.h"
#include "client/SyncClient.h"
#include "spds/spdsutils.h"
#include "spds/SyncSourceConfig.h"
#include "client/CacheSyncSource.h"
#include "base/util/KeyValuePair.h"
#include "base/util/PropertyFile.h"
#include "base/util/ArrayListEnumeration.h"

BEGIN_NAMESPACE

CacheSyncSource::CacheSyncSource(const WCHAR* sourceName, AbstractSyncSourceConfig *sc, KeyValueStore* cache) :
                    SyncSource(sourceName, sc) {
   
    allKeys = NULL;
    newKeys = NULL; 
    updatedKeys = NULL; 
    deletedKeys = NULL;   

    if (cache) {
        this->cache = cache;
    } else {
        // get the default directory of the 
        StringBuffer completeName = getCacheDirectory();;
        completeName += "/";
        completeName += CACHE_FILE_NAME;   

        this->cache = new PropertyFile(completeName);
    }
}

/**
 * Release dynamically allocated resources
 */
CacheSyncSource::~CacheSyncSource() {   

    if (newKeys)     { delete newKeys;     } 
    if (updatedKeys) { delete updatedKeys; } 
    if (deletedKeys) { delete deletedKeys; } 
    if (allKeys)     { delete allKeys;     }
    if (cache)       { delete cache;       }
}

/**
* Fill a key value pair object and set into the partialModification array list.
* This is used to set the changes in the cache or in the listener based sync source.
* If there is an error this error is reported in the saving procedure and there
* it is decided how procede
*/
void CacheSyncSource::setItemStatus(const WCHAR* key, int status, const char* command) {
    
    KeyValuePair vp;
    switch (status) {
        
        case 200:
        case 201:
        case 418: 
            {
             LOG.info("[%s], Received success status code from server for %s on item with key %s - code: %d", getName(), command, key, status);
             char* k = toMultibyte(key);             
             vp.setKey(k);
             StringBuffer v(k);
             StringBuffer sb = getItemSignature(v);
             vp.setValue(sb);             
             delete [] k;
            }   
            break;
        case 500:        
        default:
            LOG.info("[%s], Received failed status code from server for %s on item with key %s - code: %d", getName(), command, key, status);
            // error. it doesn't update the cache
            break;
    }
    if (vp.getKey()) {
        updateInCache(vp, command);
    }

}

/**
* Get the signature of an item given the value and the size. 
* The signature could be a crc computation or a timestamp or whatever can identify uniquely the
* content of an item. It is used by the implementation of the ItemHandler
* and it need the getItemContent too. The default implementation uses a 
* crc computation of the value
*
* @param key        the value on which signature must be calculated
* @param size       the size of the value
*/

StringBuffer CacheSyncSource::getItemSignature(StringBuffer& key) {

    void* content       = NULL;
    size_t size         = 0;
    
    if (key.length() <= 0) {
        return NULL;
    }
    
    LOG.debug("[%s] Getting signature for item with key %s", getName(), key.c_str());
    
    content = getItemContent(key, &size);                      
    StringBuffer s;
    s.sprintf("%ld", calculateCRC(content, size));
    if (content) { delete [] (char*)content; content = NULL; }    
    return s;
}



SyncItem* CacheSyncSource::fillSyncItem(StringBuffer* key) {
    
    SyncItem* syncItem  = NULL;    
    size_t size         = 0;
    void* content       = NULL;
    
    if (!key) {
        return NULL;
    }
    
    LOG.debug("[%s] Filling item with key %s", getName(), key->c_str());
    
    content = getItemContent((*key), &size);
    
    WCHAR* wkey = toWideChar(key->c_str());
    syncItem = new SyncItem(wkey);
    syncItem->setData(content, size);
    
    if (wkey) { delete [] wkey; wkey = NULL; }
    if (content) { delete [] (char*)content; content = NULL; }

    return syncItem;

}

/**
 * Return the first SyncItem of all.
 * It is used in case of slow sync and retrieve the entire 
 * data source content.
 */
SyncItem* CacheSyncSource::getFirstItem() {
    
    allKeys = getAllItemList();      
    return getNextItem();

};

 /**
 * Return the next SyncItem of all.
 * It is used in case of slow sync
 * and retrieve the entire data source content.
 */
SyncItem* CacheSyncSource::getNextItem() {
    
    SyncItem* syncItem = NULL;
    if (allKeys && allKeys->hasMoreElement()) {
        StringBuffer* s     = (StringBuffer*)allKeys->getNextElement();    
        syncItem = fillSyncItem(s);
    }
    if (!syncItem) {
        LOG.info("There are no more items to be exchanged. Return NULL");     
    }
    return syncItem;

}
/**
 * Return the first new SyncItem. It is used in case of fast sync
 * and retrieve the new data source content.
 */
SyncItem* CacheSyncSource::getFirstNewItem() {    
    fillItemModifications();   
    return getNextNewItem();    

}

/**
 * Return the next SyncItem of new one. It is used in case of fast sync
 * and retrieve the new data source content.
 */
SyncItem* CacheSyncSource::getNextNewItem() {
    
    SyncItem* syncItem = NULL;
    if (newKeys && newKeys->hasMoreElement()) {
        StringBuffer* s     = (StringBuffer*)newKeys->getNextElement();    
        syncItem = fillSyncItem(s);
    }
    if (!syncItem) {
        LOG.info("There are no more new items to be exchanged. Return NULL");     
    }
    return syncItem;   
}

/**
 * Return the first SyncItem of updated one. It is used in case of fast sync
 * and retrieve the new data source content.
 */
SyncItem* CacheSyncSource::getFirstUpdatedItem() {
       
    return getNextUpdatedItem();
}


SyncItem* CacheSyncSource::getNextUpdatedItem() {

    SyncItem* syncItem = NULL;
    if (updatedKeys && updatedKeys->hasMoreElement()) {
        StringBuffer* s     = (StringBuffer*)updatedKeys->getNextElement();    
        syncItem = fillSyncItem(s);
    }
    if (!syncItem) {
        LOG.info("There are no more updated items to be exchanged. Return NULL");     
    }    
    return syncItem;    
}

SyncItem* CacheSyncSource::getFirstDeletedItem() {
       
    return getNextDeletedItem();
}


/**
 * Return the next SyncItem of updated one. It is used in case of fast sync
 * and retrieve the new data source content.
 */
SyncItem* CacheSyncSource::getNextDeletedItem() {
    
    SyncItem* syncItem = NULL;
    if (deletedKeys && deletedKeys->hasMoreElement()) {
        StringBuffer* s     = (StringBuffer*)deletedKeys->getNextElement();  
        if (!s) {
            return NULL;
        }
        WCHAR* wkey = toWideChar(s->c_str());
        syncItem = new SyncItem(wkey); 
        if (wkey) { delete [] wkey; wkey = NULL; }  
    }
    if (!syncItem) {
        LOG.info("There are no more deleted items to be exchanged. Return NULL");     
    }    
         
    return syncItem;
}

int CacheSyncSource::endSync() {            
    saveCache();    
    return 0;
}

/**
* The way to calculate the cache is the follow:
* loop on the current element against an array list
* that has the cache. It is the copy of the original cache.
* When an current element is found in the cache, it is removed
* from the cache copy. At the end the remained element
* in the cache are the deleted ones.
*/
bool CacheSyncSource::fillItemModifications() {
    
    // all the current items keys list
    Enumeration* items = (Enumeration*)getAllItemList();

    if (!items) {
        LOG.error("Error in fillItemModification");
        return false;
    }

    // all the action are done on the copy so we can delete
    // the element found. The remained are the deleted by the user.        
    Enumeration& e = cache->getProperties();
    ArrayList cacheCopy;
    while(e.hasMoreElement()) {
        cacheCopy.add(*e.getNextElement());
    }        
    //if (e) {
    //    delete e;
    //}

    StringBuffer* key;
    KeyValuePair* kvp;

    ArrayListEnumeration *newitems = new ArrayListEnumeration(),
                         *moditems = new ArrayListEnumeration();

    if (items) {
        while(items->hasMoreElement()) {
            key = (StringBuffer*)items->getNextElement();
            int size = cacheCopy.size();
            bool foundnew = true;

            for (int i = 0; i < size; i++) {
                kvp = (KeyValuePair*)(cacheCopy[i]);
                if (strcmp(kvp->getKey(), key->c_str()) == 0) {
                    foundnew = false;
                    // see if it is updated.
                    StringBuffer sign = getItemSignature(*key);
                    if (sign != kvp->getValue()) {
                        // there is an update. if equal nothing to do...
                        moditems->add(*key);                      
                    }
                    cacheCopy.removeElementAt(i);
                    break;
                }
            }
            if (foundnew) {
                newitems->add(*key);
            }
        }
    }
        
    newKeys = newitems;
    updatedKeys = moditems;           
    deletedKeys = new ArrayListEnumeration(cacheCopy);    
    
    delete items; 
    return true;
}

/**
* Save the current status of the cache arrayList
* 
*/
int CacheSyncSource::saveCache() {
    
    LOG.debug("[%s] Saving cache", getName());
    
    int ret = cache->save();
    return ret;

}

int CacheSyncSource::updateInCache(KeyValuePair& k, const char* action) {

    if (strcmp(action, ADD    ) == 0 ||
        strcmp(action, REPLACE) == 0) {        
        cache->setPropertyValue(k.getKey(), k.getValue());
    } else if (strcmp(action, DEL) == 0) {
        cache->removeProperty(k.getKey());
    }
    return 0;
}

void CacheSyncSource::getKeyAndSignature(SyncItem& item, KeyValuePair& kvp) {
    
    char* t = toMultibyte(item.getKey());
    StringBuffer s(t);
    StringBuffer sign = getItemSignature(s);
    kvp.setKey(t);
    kvp.setValue(sign);
    delete [] t;
    
}

int CacheSyncSource::addItem(SyncItem& item) {
    int ret = insertItem(item);
    switch (ret) {        
        case 200:
        case 201:
        case 418: {
            LOG.info("[%s] Successful add of item with key %s - code %d", getName(), item.getKey(), ret);
            KeyValuePair k;
            getKeyAndSignature(item, k);
            insertInCache(k);
        }
        break;
        default:
            LOG.error("[%s] Failed add of item with key %s - code %d", getName(), item.getKey(), ret);
        break;
    }
    return ret;
}


int CacheSyncSource::updateItem(SyncItem& item) {
    int ret = modifyItem(item);
    switch (ret) {        
        case 200:
        case 201:
        case 418: {
            LOG.info("[%s] Successful update of item with key %s - code %d", getName(), item.getKey(), ret);
            KeyValuePair k;
            getKeyAndSignature(item, k);
            updateInCache(k);
        }
        break;
        default:
            LOG.error("[%s] Failed update of item with key %s - code %d", getName(), item.getKey(), ret);
        break;
    }
    return ret;
}

int CacheSyncSource::deleteItem(SyncItem& item) {
    int ret = removeItem(item);
    switch (ret) {        
        case 200:
        case 201:
        case 418: {
            LOG.info("[%s] Successful delete of item with key %s - code %d", getName(), item.getKey(), ret);  
            char* t = toMultibyte(item.getKey());
            KeyValuePair k (t, "");
            removeFromCache(k);
            delete [] t;
        }
        break;
        default:
            LOG.error("[%s] Failed delete of item with key %s - code %d", getName(), item.getKey(), ret);
        break;
    }
    
    return ret;
} 

END_NAMESPACE
