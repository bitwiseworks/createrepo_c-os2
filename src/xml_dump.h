/* createrepo_c - Library of routines for manipulation with repodata
 * Copyright (C) 2012  Tomas Mlcoch
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
 * USA
 */

#ifndef __C_CREATEREPOLIB_XML_DUMP_H__
#define __C_CREATEREPOLIB_XML_DUMP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "package.h"

/** \defgroup   xml_dump        XML dump API.
 */

/**@{*/
/** Default namespace for primary.xml */
#define XML_COMMON_NS           "http://linux.duke.edu/metadata/common"
/** Default namespace for filelists.xml */
#define XML_FILELISTS_NS        "http://linux.duke.edu/metadata/filelists"
/** Default namespace for other.xml */
#define XML_OTHER_NS            "http://linux.duke.edu/metadata/other"
/** Namespace used in primary.xml */
#define XML_RPM_NS              "http://linux.duke.edu/metadata/rpm"
/**@}*/


/** \ingroup xml_dump
 * Xml chunks for primary.xml, filelists.xml and other.xml.
 */
struct XmlStruct{
    char *primary;      /*!< XML chunk for primary.xml */
    char *filelists;    /*!< XML chunk for filelists.xml */
    char *other;        /*!< XML chunk for other.xml */
};

/** \ingroup xml_dump
 * Generate primary xml chunk from Package.
 * @param package       Package
 * @return              xml chunk string or NULL on error
 */
char *xml_dump_primary(Package *package);

/** \ingroup xml_dump
 * Generate filelists xml chunk from Package.
 * @param package       Package
 * @return              xml chunk string or NULL on error
 */
char *xml_dump_filelists(Package *package);

/** \ingroup xml_dump
 * Generate other xml chunk from Package.
 * @param package       Package
 * @return              xml chunk string or NULL on error
 */
char *xml_dump_other(Package *package);

/** \ingroup xml_dump
 * Generate all three xml chunks (primary, filelists, other) from Package.
 * @param package       Package
 * @return              XmlStruct
 */
struct XmlStruct xml_dump(Package *package);

#ifdef __cplusplus
}
#endif

#endif /* __C_CREATEREPOLIB_XML_DUMP_H__ */
