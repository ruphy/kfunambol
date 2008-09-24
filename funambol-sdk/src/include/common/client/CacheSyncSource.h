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

#ifndef INCL_CACHE_SYNC_SOURCE
#define INCL_CACHE_SYNC_SOURCE
/** @cond API */
/** @addtogroup Client */
/** @{ */

#include "base/fscapi.h"
#include "base/ErrorHandler.h"
#include "base/util/ArrayElement.h"
#include "filter/SourceFilter.h"
#include "spds/constants.h"
#include "spds/SyncItem.h"
#include "spds/SyncStatus.h"
#include "spds/AbstractSyncSourceConfig.h"
#include "spds/SyncSourceReport.h"
#include "spds/SyncSource.h"
#include "syncml/core/TagNames.h"
#include "base/util/Enumeration.h"
#include "base/util/KeyValueStore.h"
#include "base/util/KeyValuePair.h"

BEGIN_NAMESPACE

#define CACHE_FILE_NAME     "cache_items.dat"

/**
 * This is an extension of the basic SyncSource that a SyncML client developer could implement
 * to let the sync engine access the client's data. It provides the logic to retrieve 
 * the item modification to be exchanged with the server
 */
class CacheSyncSource : public SyncSource {

private:
         
    /**
    * Used to store a KeyValuePair containing the key and the command
    * associated to the item. It stores the cache:
    * - during the slow sync. After the allKeys is populated, for every
    * item status sent back by the server, the cache is populated. It is possible
    * to write down when needed.
    * - during the two-way sync it is populated at the beginning to understand
    * the modification. This action populates the newKeys, updatedKeys and deletedKeys.
    * For every item status sent back by the server the cache is updated
    *    
    */    
    KeyValueStore* cache; 
       
    /**
    * Enumeration of the new keys
    */
    Enumeration*   newKeys;
    /**
    * Enumeration of the updated keys
    */
    Enumeration*   updatedKeys;
    /**
    * Enumeration of the deleted keys
    */
    Enumeration*   deletedKeys;       
    
    /**
     * Used to store the keys of all items for a slow based sync
     * It is an enumeration of StringBuffer keys
     */
    Enumeration* allKeys;

    /**
    * Fills the sync item given the key. It is used by the method getXXXItem to
    * complete the SyncItem.
    */
    SyncItem* fillSyncItem(StringBuffer* key);       

    /**
    * The way to calculate the cache is the follow:
    * loop on the current element against an array list
    * that has the cache. It is the copy of the original cache.
    * When an current element is found in the cache, it is removed
    * from the cache copy. At the end the remained element
    * in the cache are the deleted ones.
    * Called when the two-way sync is requested
    */
    bool fillItemModifications();

    /**
    * Utility private method that populates the keyValuePair with 
    * the couple key/signature starting from the SyncItem.
    * Used in the addItem and updateItem
    *
    * @param item - IN:  the SyncItem
    * @param kvp  - OUT: the KeyValuePair to be populate
    */
    void getKeyAndSignature(SyncItem& item, KeyValuePair& kvp);

protected:
  
    /**
     * Save the current cache in what is implemented by KeyValueStore (a file or wathever).    
     */
    int saveCache();
  
    /**
     * Called by the sync engine to add an item that the server has sent.
     * The implementation calls the insertItem method that must be implemented
     * by the user. Also used to update the item 
     */
    int addItem(SyncItem& item);

    /**
     * Called by the sync engine to update an item that the source already
     * should have. The item's key is the local key of that item.
     *
     * @param item    the item as sent by the server
     * @return SyncML status code
     */
    int updateItem(SyncItem& item);

    /**
     * Called by the sync engine to update an item that the source already
     * should have. The item's key is the local key of that item, no data is
     * provided.
     *
     * @param item    the item as sent by the server
     */
    int deleteItem(SyncItem& item);

    /**
    * Used to update the cache adding, replacing or deleting. 
    * The KeyValuePair contains the pair UID/signature. It is provided
    * by the proper method who calls this. It udpates the cache 
    * that is in memory.
    * The action by default is Replace. 
    */
    int updateInCache(KeyValuePair& k, const char* action = REPLACE);
        
    /**
    * To insert in the cache. 
    */
    int insertInCache(KeyValuePair& k) {
        return updateInCache(k, ADD);
    }
    
    /**
    * To remove from cache
    */
    int removeFromCache(KeyValuePair& k) {
        return updateInCache(k, DEL);
    }    

public:

    /**
     * Constructor: create a CacheSyncSource with the specified name
     *
     * @param name   the name of the SyncSource
     * @param sc     configuration for the sync source: the instance
     *               must remain valid throughout the lifetime of the
     *               sync source because it keeps a reference to it
     *               and uses it as its own. A NULL pointer is allowed
     *               for unit testing outside of the sync framework;
     *               the sync source then references a global config
     *               instance to avoid crashes, but modifying that config
     *               will not make much sense. The pointer may also be
     *               set directly after creating the SyncSource, which
     *               is useful when a derived class creates the config
     *               in its own constructor.
     * @param cache  the store for the cache. Released by the CacheSyncSource
     *                
     */
    CacheSyncSource(const WCHAR* name, AbstractSyncSourceConfig* sc, 
                        KeyValueStore* cache = NULL);
        
    // Destructor
    virtual ~CacheSyncSource();         
                               
    /**
     * called by the sync engine with the status returned by the
     * server for a certain item that the client sent to the server.
     * It contains also the proper command associated to the item.
     * It is used to update the current array of cache.
     *
     * @param key      - the local key of the item
     * @param status   - the SyncML status returned by the server
     * @param command  - the SyncML command associated to the item
     * 
     */
    void setItemStatus(const WCHAR* key, int status, const char* command);       
    
    /**
     * Return the key of the first SyncItem of all.
     * It is used in case of refresh sync
     * and retrieve all the keys of the data source.
     * @deprecated no more used. use removeAllItems instead.
     */
    SyncItem* getFirstItemKey() { return NULL; };

    /**
     * Return the key of the next SyncItem of all.
     * It is used in case of refresh sync
     * and retrieve all the keys of the data source.
     * @deprecated no more used. use removeAllItems instead. 
     */
    SyncItem* getNextItemKey() { return NULL; };

    /**
     * Return the first SyncItem of all.
     * It is used in case of slow sync
     * and retrieve the entire data source content.
     */
    SyncItem* getFirstItem();

    /**
     * Return the next SyncItem of all.
     * It is used in case of slow sync
     * and retrieve the entire data source content.
     */
    SyncItem* getNextItem();

    /**
     * Return the first SyncItem of new one. It is used in case of fast sync
     * and retrieve the new data source content.
     */
    SyncItem* getFirstNewItem();

    /**
     * Return the next SyncItem of new one. It is used in case of fast sync
     * and retrieve the new data source content.
     */
    SyncItem* getNextNewItem();

    /**
     * Return the first SyncItem of updated one. It is used in case of fast sync
     * and retrieve the new data source content.
     */
    SyncItem* getFirstUpdatedItem();

    /**
     * Return the next SyncItem of updated one. It is used in case of fast sync
     * and retrieve the new data source content.
     */
    SyncItem* getNextUpdatedItem();

    /**
     * Return the first SyncItem of updated one. It is used in case of fast sync
     * and retrieve the new data source content.
     */
    SyncItem* getFirstDeletedItem();

    /**
     * Return the next SyncItem of updated one. It is used in case of fast sync
     * and retrieve the new data source content.
     */
    SyncItem* getNextDeletedItem();
    
     /**
    * Indicates that all the server status of the current package 
    * of the client items has been processed by the engine.
    * This signal can be useful to update the modification arrays
    * NOT USED at the moment
    */
    void serverStatusPackageEnded() {};    
    
    /**
    * Indicates that all the client status of the current package 
    * of the server items that has been processed by the client and 
    * are going to be sent to the server.
    * This signal can be useful to update the modification arrays
    * NOT USED at the moment
    */
    void clientStatusPackageEnded() {};        

    /**
    * In the first implementatation, in which serverStatusPackageEnded and 
    * clientStatusPackageEnded are not yet impelemented, the end sync
    * will udpate the whole cache status persistently.
    */
    int endSync();       
    
    /**
    * Get the signature of an item given the key. The signature could be
    * a crc computation or a timestamp or whatever can identify uniquely the
    * content of an item. The default implementation uses a 
    * crc computation of the value. Overriding implementation could provide
    * something different like the timestamp or other...
    *
    * @param key    the key of the item. 
    * @return       the signature of the selected item
    */    
    virtual StringBuffer getItemSignature(StringBuffer& key);

    /**
    * Get the content of an item given the key. It is used to populate
    * the SyncItem before the engine uses it in the usual flow of the sync.      
    *
    * @param key      the local key of the item
    * @param size     OUT: the size of the content
    */
    virtual void* getItemContent(StringBuffer& key, size_t* size) = 0;
    
            
    /**
    * Get an array list containing all the StringBuffer keys of all items. 
    * Used for the sync requiring and exchange of all items and
    * for the sync that need to calculate the modification.
    * It has to return a new allocated Enumeration that is
    * freed by the CacheSyncSource
    */
    virtual Enumeration* getAllItemList() = 0;      
    
    /**
     * Called by the sync engine to add an item that the server has sent.
     * The sync source is expected to add it to its database, then set the
     * key to the local key assigned to the new item. Alternatively
     * the sync source can match the new item against one of the existing
     * items and return that key.
     *
     * @param item    the item as sent by the server
     * @return SyncML status code
     */
    virtual int insertItem(SyncItem& item) = 0;

    /**
     * Called by the sync engine to update an item that the source already
     * should have. The item's key is the local key of that item.
     *
     * @param item    the item as sent by the server
     * @return SyncML status code
     */
    virtual int modifyItem(SyncItem& item) = 0;

    /**
     * Called by the sync engine to update an item that the source already
     * should have. The item's key is the local key of that item, no data is
     * provided.
     *
     * @param item    the item as sent by the server
     */
    virtual int removeItem(SyncItem& item) = 0;
   
   
};

END_NAMESPACE

/** @} */
/** @endcond */
#endif
