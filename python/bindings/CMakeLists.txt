# Copyright 2020 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

########################################################################
# Check if there is C++ code at all
########################################################################
if(NOT bench_sources)
    MESSAGE(STATUS "No C++ sources... skipping python bindings")
    return()
endif(NOT bench_sources)

########################################################################
# Check for pygccxml
########################################################################
GR_PYTHON_CHECK_MODULE_RAW(
    "pygccxml"
    "import pygccxml"
    PYGCCXML_FOUND
    )

include(GrPybind)

########################################################################
# Python Bindings
########################################################################
list(APPEND bench_python_files
    extract_burst_python.cc
    nop_python.cc
    nop_source_python.cc
    nop_head_python.cc
    random_copy_python.cc
    sequential_validate_sink_python.cc
    seqval_c_python.cc
    time_tag_injector_python.cc
    latency_meas_sink_python.cc
    msg_forward_python.cc
    # pdu_process_python.cc 
    python_bindings.cc)

GR_PYBIND_MAKE_OOT(bench 
   ../..
   gr::bench
   "${bench_python_files}")

install(TARGETS bench_python DESTINATION ${GR_PYTHON_DIR}/bench COMPONENT pythonapi)
