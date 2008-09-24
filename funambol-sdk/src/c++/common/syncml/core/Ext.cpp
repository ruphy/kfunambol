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

#include "base/util/utils.h"
#include "syncml/core/Ext.h"
#include "base/globalsdef.h"

USE_NAMESPACE


Ext::Ext(){
    initialize();
}
Ext::~Ext() {
    if (xNam) {
        delete [] xNam; xNam = NULL;
    }

    if (xVal) {
        xVal->clear(); //delete xVal;        xVal = NULL;
    }
}

/**
* Creates a new Ext object with the given name and value
*
*  @param xNam corresponds to the &lt;XNam&gt; element - NOT NULL
*  @param xVal an array of parameters that corresponds to the &ltXVal&gt
*                  element
*
*/
Ext::Ext(char* xNam, ArrayList* xVal) {
    initialize();
    setXNam(xNam);
    setXVal(xVal);
}

void Ext::initialize() {
    xNam = NULL;
    xVal = new ArrayList();   // String[]
}

/**
* Gets the name of the extension
*
* @return the name of the extension
*/
const char* Ext::getXNam() {
    return xNam;
}

/**
* Sets the name of extension
*
* @param xNam the name of extension
*
*/
void Ext::setXNam(const char*xNam) {
    if (this->xNam) {
        delete [] this->xNam; this->xNam = NULL;
    }
    this->xNam = stringdup(xNam);

}

/**
* Gets an array of extension values, if exist
*
* @return an array of extension values, if exist
*/
ArrayList* Ext::getXVal() {
    return xVal;
}

/**
* Sets the array of extension value
*
* @param xVal the array of extension value
*
*/
void Ext::setXVal(ArrayList* xVal) {
    if (this->xVal) {
        this->xVal->clear();
    }
    this->xVal = xVal->clone();
}

ArrayElement* Ext::clone() {
    Ext* ret = new Ext(xNam, xVal);
    return ret;
}
