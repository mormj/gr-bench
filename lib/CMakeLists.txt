# Copyright 2011,2012,2016,2018,2019 Free Software Foundation, Inc.
#
# This file was generated by gr_modtool, a tool from the GNU Radio framework
# This file is a part of gr-bench
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

########################################################################
# Setup library
########################################################################
include(GrPlatform) #define LIB_SUFFIX
list(APPEND bench_sources
    extract_burst_impl.cc
    nop_impl.cc
    nop_source_impl.cc
    nop_head_impl.cc
    random_copy_impl.cc
    sequential_validate_sink_impl.cc
    seqval_c_impl.cc
    time_tag_injector_impl.cc
    latency_meas_sink_impl.cc
    msg_forward_impl.cc
    pdu_process_impl.cc
    head_null_sink_impl.cc
    nop_latency_source_impl.cc
    head_nop_latency_sink_impl.cc
    copy_impl.cc )

set(bench_sources "${bench_sources}" PARENT_SCOPE)
if(NOT bench_sources)
    MESSAGE(STATUS "No C++ sources... skipping lib/")
    return()
endif(NOT bench_sources)

add_library(gnuradio-bench SHARED ${bench_sources})
target_link_libraries(gnuradio-bench gnuradio::gnuradio-runtime)
target_include_directories(gnuradio-bench
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
    PUBLIC $<INSTALL_INTERFACE:include>
  )
set_target_properties(gnuradio-bench PROPERTIES DEFINE_SYMBOL "gnuradio_bench_EXPORTS")

if(APPLE)
    set_target_properties(gnuradio-bench PROPERTIES
        INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/lib"
    )
endif(APPLE)

########################################################################
# Install built library files
########################################################################
include(GrMiscUtils)
GR_LIBRARY_FOO(gnuradio-bench)

########################################################################
# Print summary
########################################################################
message(STATUS "Using install prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "Building for version: ${VERSION} / ${LIBVER}")

########################################################################
# Build and register unit test
########################################################################
include(GrTest)

# If your unit tests require special include paths, add them here
#include_directories()
# List all files that contain Boost.UTF unit tests here
list(APPEND test_bench_sources
)
# Anything we need to link to for the unit tests go here
list(APPEND GR_TEST_TARGET_DEPS gnuradio-bench)

if(NOT test_bench_sources)
    MESSAGE(STATUS "No C++ unit tests... skipping")
    return()
endif(NOT test_bench_sources)

foreach(qa_file ${test_bench_sources})
    GR_ADD_CPP_TEST("bench_${qa_file}"
        ${CMAKE_CURRENT_SOURCE_DIR}/${qa_file}
    )
endforeach(qa_file)
