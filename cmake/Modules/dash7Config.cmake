INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_DASH7 dash7)

FIND_PATH(
    DASH7_INCLUDE_DIRS
    NAMES dash7/api.h
    HINTS $ENV{DASH7_DIR}/include
        ${PC_DASH7_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    DASH7_LIBRARIES
    NAMES gnuradio-dash7
    HINTS $ENV{DASH7_DIR}/lib
        ${PC_DASH7_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(DASH7 DEFAULT_MSG DASH7_LIBRARIES DASH7_INCLUDE_DIRS)
MARK_AS_ADVANCED(DASH7_LIBRARIES DASH7_INCLUDE_DIRS)

