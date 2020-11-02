INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_BENCH bench)

FIND_PATH(
    BENCH_INCLUDE_DIRS
    NAMES bench/api.h
    HINTS $ENV{BENCH_DIR}/include
        ${PC_BENCH_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    BENCH_LIBRARIES
    NAMES gnuradio-bench
    HINTS $ENV{BENCH_DIR}/lib
        ${PC_BENCH_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
          )

include("${CMAKE_CURRENT_LIST_DIR}/benchTarget.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(BENCH DEFAULT_MSG BENCH_LIBRARIES BENCH_INCLUDE_DIRS)
MARK_AS_ADVANCED(BENCH_LIBRARIES BENCH_INCLUDE_DIRS)
