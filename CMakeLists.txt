# project

cmake_minimum_required (VERSION 2.8)

# -- Set project name
set(PROJ_NAME cbase)

project (${PROJ_NAME})

# -- Set install dirs
if (DEFINED ENV{INSTALL_BASE_DIR})
  set(PROJ_INSTALL_DIR $ENV{INSTALL_BASE_DIR})
else()
  set(PROJ_INSTALL_DIR ${CMAKE_SOURCE_DIR}/install)
endif()

set(CPACK_PACKAGE_VERSION "0.1.1")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "1")
set(CPACK_PACKAGE_VERSION_PATCH "1")
set(CPACK_PACKAGE_CONTACT )

set(PROJ_LICENSE_FILE COPYING)
set(PROJ_README_FILE  README.txt)

# -- Include the tests in the bin folder?
set(INCLUDE_TEST_IN_BIN FALSE)

# -- Include the magic ProjTools
include("cmake/ProjTools.cmake")

# --------------------------------------- #
# cbase                                   #
# --------------------------------------- #

set(CBASE cbase)

set(CBASE_PUB_HDRS
    buildsym.h;
    lib.h;
    ints.h;
    buffer.h)

set(CBASE_INT_HDRS
    )

set(CBASE_LIB_SRCS
    lib.c)

# Lib version
set(CBASE_VERSION_MAJOR 0.1)
set(CBASE_VERSION_MINOR 1)
set(CBASE_VERSION ${CBASE_VERSION_MAJOR}.${CBASE_VERSION_MINOR})

# -- Add the cbase library
add_lib(${CBASE} SHARED ${CBASE_PUB_HDRS} ${CBASE_INT_HDRS} ${CBASE_LIB_SRCS})
add_lib_build_def(${CBASE} CBASE_BUILD)
add_lib_build_def(${CBASE} "CBASE_LIB_VERSION=\"${CBASE_VERSION}\"")
link_libs(${CBASE} )
set_tgt_ver(${CBASE} ${CBASE_VERSION} ${CBASE_VERSION_MAJOR})

if (WIN32)
  add_lib_build_def(${CBASE} "_CONSOLE")
  add_link_flag(${CBASE} "/SUBSYSTEM:CONSOLE")
endif()

add_hdrs_tgt_ide(public ${CBASE_PUB_HDRS})
add_hdrs_tgt_ide(internal ${CBASE_INT_HDRS})
add_hdrs_tgt_ide(all ${CBASE_PUB_HDRS} ${CBASE_INT_HDRS})

# -- Install targets
install_hdr(${CBASE_PUB_HDRS})
install_tgt(${CBASE})
# install(FILES README.md DESTINATION .)

# --------------------------------------- #
# end cbase                               #
# --------------------------------------- #

# -- Add the subdirectories
set(PROJ_SUBDIRS  unittest; doc; tools; test)

# add all subdirs
foreach(subdir ${PROJ_SUBDIRS})
  add_subdirectory(${subdir})
endforeach(subdir)

