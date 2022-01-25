/*
 * Copyright 2020 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include <pybind11/pybind11.h>

#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <numpy/arrayobject.h>

namespace py = pybind11;

// Headers for binding functions
/**************************************/
/* The following comment block is used for
/* gr_modtool to insert function prototypes
/* Please do not delete
/**************************************/
// BINDING_FUNCTION_PROTOTYPES(
void bind_extract_burst(py::module& m);
    void bind_nop(py::module& m);
    void bind_nop_source(py::module& m);
    void bind_nop_head(py::module& m);
    void bind_random_copy(py::module& m);
    void bind_sequential_validate_sink(py::module& m);
    void bind_seqval_c(py::module& m);
    void bind_time_tag_injector(py::module& m);
    void bind_latency_meas_sink(py::module& m);
    void bind_msg_forward(py::module& m);
// ) END BINDING_FUNCTION_PROTOTYPES


// We need this hack because import_array() returns NULL
// for newer Python versions.
// This function is also necessary because it ensures access to the C API
// and removes a warning.
void* init_numpy()
{
    import_array();
    return NULL;
}

PYBIND11_MODULE(bench_python, m)
{
    // Initialize the numpy C API
    // (otherwise we will see segmentation faults)
    init_numpy();

    // Allow access to base block methods
    py::module::import("gnuradio.gr");

    /**************************************/
    /* The following comment block is used for
    /* gr_modtool to insert binding function calls
    /* Please do not delete
    /**************************************/
    // BINDING_FUNCTION_CALLS(
    bind_extract_burst(m);
    bind_nop(m);
    bind_nop_source(m);
    bind_nop_head(m);
    bind_random_copy(m);
    bind_sequential_validate_sink(m);
    bind_seqval_c(m);
    bind_time_tag_injector(m);
    bind_latency_meas_sink(m);
    bind_msg_forward(m);
    // ) END BINDING_FUNCTION_CALLS
}