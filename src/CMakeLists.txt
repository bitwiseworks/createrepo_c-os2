SET (createrepo_c_SRCS
     checksum.c
     compression_wrapper.c
     createrepo_shared.c
     deltarpms.c
     dumper_thread.c
     error.c
     helpers.c
     load_metadata.c
     locate_metadata.c
     misc.c
     modifyrepo_shared.c
     package.c
     parsehdr.c
     parsepkg.c
     repomd.c
     sqlite.c
     threads.c
     updateinfo.c
     xml_dump.c
     xml_dump_deltapackage.c
     xml_dump_filelists.c
     xml_dump_other.c
     xml_dump_primary.c
     xml_dump_repomd.c
     xml_dump_updateinfo.c
     xml_file.c
     xml_parser.c
     xml_parser_filelists.c
     xml_parser_other.c
     xml_parser_primary.c
     xml_parser_repomd.c
     xml_parser_updateinfo.c
     xml_parser_main_metadata_together.c
     koji.c)

SET(headers
    checksum.h
    compression_wrapper.h
    constants.h
    mergerepo_c.h
    createrepo_c.h
    createrepo_shared.h
    deltarpms.h
    error.h
    helpers.h
    load_metadata.h
    locate_metadata.h
    misc.h
    modifyrepo_shared.h
    package.h
    parsehdr.h
    parsepkg.h
    repomd.h
    sqlite.h
    threads.h
    updateinfo.h
    version.h
    xml_dump.h
    xml_file.h
    koji.h
    xml_parser.h)

# glibc needs _XOPEN_SOURCE >= 500 defined in order to expose nftw(),
# other systems do not need this macro defined.  If necessary, set the
# macro to 700 since that's the 7th revision which is what the Python
# pieces will want.
INCLUDE (CheckSymbolExists)
CHECK_SYMBOL_EXISTS(nftw ftw.h HAVE_NFTW)
IF (NOT HAVE_NFTW)
    LIST(APPEND CMAKE_REQUIRED_DEFINITIONS -D_XOPEN_SOURCE=700)
    CHECK_SYMBOL_EXISTS(nftw ftw.h HAVE_NFTW_XOPEN)

    IF (HAVE_NFTW_XOPEN)
        ADD_COMPILE_DEFINITIONS(_XOPEN_SOURCE=700)
    ELSE ()
        ERROR("unable to find nftw() definition")
    ENDIF ()
ENDIF ()

IF (BUILD_LIBCREATEREPO_C_SHARED)
  SET (createrepo_c_library_type SHARED)
ELSE ()
  SET (createrepo_c_library_type STATIC)
ENDIF ()
ADD_LIBRARY(libcreaterepo_c ${createrepo_c_library_type} ${createrepo_c_SRCS})
TARGET_LINK_LIBRARIES(libcreaterepo_c ${BZIP2_LIBRARIES})
TARGET_LINK_LIBRARIES(libcreaterepo_c ${CURL_LIBRARY})
TARGET_LINK_LIBRARIES(libcreaterepo_c ${GLIB2_LIBRARIES})
TARGET_LINK_LIBRARIES(libcreaterepo_c ${GIO_LIBRARIES})
TARGET_LINK_LIBRARIES(libcreaterepo_c ${LIBMODULEMD_LIBRARIES})
TARGET_LINK_LIBRARIES(libcreaterepo_c ${LIBXML2_LIBRARIES})
TARGET_LINK_LIBRARIES(libcreaterepo_c ${LZMA_LIBRARIES})
TARGET_LINK_LIBRARIES(libcreaterepo_c ${OPENSSL_LIBRARIES})
TARGET_LINK_LIBRARIES(libcreaterepo_c ${RPM_LIBRARIES})
TARGET_LINK_LIBRARIES(libcreaterepo_c ${SQLITE3_LIBRARIES})
TARGET_LINK_LIBRARIES(libcreaterepo_c ${ZLIB_LIBRARY})
TARGET_LINK_LIBRARIES(libcreaterepo_c ${ZCK_LIBRARIES})
TARGET_LINK_LIBRARIES(libcreaterepo_c ${DRPM_LIBRARIES})
TARGET_LINK_LIBRARIES(libcreaterepo_c ${ZSTD_LIBRARIES})

SET_TARGET_PROPERTIES(libcreaterepo_c PROPERTIES
                      OUTPUT_NAME "createrepo_c"
                      SOVERSION ${CR_MAJOR}
                      VERSION "${VERSION}"
                      COMPILE_DEFINITIONS "G_LOG_DOMAIN=\"${G_LOG_DOMAIN}\"")

if(OS2)
    set_target_properties(libcreaterepo_c PROPERTIES
        OS2_DEF_VENDOR "$ENV{VENDOR}"
        OS2_DEF_PATCH "${CR_PATCH}"
        OS2_DEF_VERSION "${VERSION}"
        TARGET_SHORT crtrepo)
endif()

ADD_EXECUTABLE(createrepo_c createrepo_c.c cmd_parser.c)
TARGET_LINK_LIBRARIES(createrepo_c
                        libcreaterepo_c
                        ${GLIB2_LIBRARIES}
                        ${GTHREAD2_LIBRARIES})
if(OS2)
    set_target_properties(createrepo_c PROPERTIES
        OS2_DEF_VENDOR "$ENV{VENDOR}"
        OS2_DEF_PATCH "${CR_PATCH}"
        OS2_DEF_VERSION "${VERSION}")
endif()

ADD_EXECUTABLE(mergerepo_c mergerepo_c.c)
TARGET_LINK_LIBRARIES(mergerepo_c
                        libcreaterepo_c
                        ${GLIB2_LIBRARIES}
                        ${GTHREAD2_LIBRARIES}
                        ${LIBMODULEMD_LIBRARIES})

if(OS2)
    set_target_properties(mergerepo_c PROPERTIES
        OS2_DEF_VENDOR "$ENV{VENDOR}"
        OS2_DEF_PATCH "${CR_PATCH}"
        OS2_DEF_VERSION "${VERSION}")
endif()

ADD_EXECUTABLE(modifyrepo_c modifyrepo_c.c)
TARGET_LINK_LIBRARIES(modifyrepo_c
                        libcreaterepo_c
                        ${GLIB2_LIBRARIES}
                        ${GTHREAD2_LIBRARIES})

if(OS2)
    set_target_properties(modifyrepo_c PROPERTIES
        OS2_DEF_VENDOR "$ENV{VENDOR}"
        OS2_DEF_PATCH "${CR_PATCH}"
        OS2_DEF_VERSION "${VERSION}")
endif()

ADD_EXECUTABLE(sqliterepo_c sqliterepo_c.c)
TARGET_LINK_LIBRARIES(sqliterepo_c
                        libcreaterepo_c
                        ${GLIB2_LIBRARIES}
                        ${GTHREAD2_LIBRARIES})

if(OS2)
    set_target_properties(sqliterepo_c PROPERTIES
        OS2_DEF_VENDOR "$ENV{VENDOR}"
        OS2_DEF_PATCH "${CR_PATCH}"
        OS2_DEF_VERSION "${VERSION}")
endif()

CONFIGURE_FILE("createrepo_c.pc.cmake" "${CMAKE_SOURCE_DIR}/src/createrepo_c.pc" @ONLY)
CONFIGURE_FILE("version.h.in" "${CMAKE_CURRENT_SOURCE_DIR}/version.h" @ONLY)
CONFIGURE_FILE("deltarpms.h.in" "${CMAKE_CURRENT_SOURCE_DIR}/deltarpms.h" @ONLY)

IF (CREATEREPO_C_INSTALL_DEVELOPMENT OR "${createrepo_c_library_type}" STREQUAL "SHARED")
    INSTALL(
        TARGETS libcreaterepo_c
        RUNTIME DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT RuntimeLibraries
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT RuntimeLibraries
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT Development
        )
ENDIF (CREATEREPO_C_INSTALL_DEVELOPMENT OR "${createrepo_c_library_type}" STREQUAL "SHARED")

IF (CREATEREPO_C_INSTALL_DEVELOPMENT)
    INSTALL(FILES ${headers} DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/createrepo_c")
    INSTALL(FILES "createrepo_c.pc" DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig")
ENDIF (CREATEREPO_C_INSTALL_DEVELOPMENT)

IF (NOT DEFINED BIN_INSTALL_DIR)
    SET(BIN_INSTALL_DIR "bin/")
ENDIF (NOT DEFINED BIN_INSTALL_DIR)
INSTALL(
    TARGETS
        createrepo_c
        mergerepo_c
        modifyrepo_c
        sqliterepo_c
    RUNTIME DESTINATION ${BIN_INSTALL_DIR} COMPONENT Runtime
    )

IF (ENABLE_PYTHON)
    ADD_SUBDIRECTORY(python)
ENDIF (ENABLE_PYTHON)
