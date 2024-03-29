/*
 * Copyright 2023 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

/***********************************************************************************/
/* This file is automatically generated using bindtool and can be manually edited  */
/* The following lines can be configured to regenerate this file during cmake      */
/* If manual edits are made, the following tags should be modified accordingly.    */
/* BINDTOOL_GEN_AUTOMATIC(0)                                                       */
/* BINDTOOL_USE_PYGCCXML(0)                                                        */
/* BINDTOOL_HEADER_FILE(head_nop_latency_sink.h)                                        */
/* BINDTOOL_HEADER_FILE_HASH(0d427af904a69b6942e08e2ceb3b760e)                     */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <bench/head_nop_latency_sink.h>
// pydoc.h is automatically generated in the build directory
#include <head_nop_latency_sink_pydoc.h>

void bind_head_nop_latency_sink(py::module& m)
{

    using head_nop_latency_sink = ::gr::bench::head_nop_latency_sink;


    py::class_<head_nop_latency_sink,
               gr::sync_block,
               gr::block,
               gr::basic_block,
               std::shared_ptr<head_nop_latency_sink>>(
        m, "head_nop_latency_sink", D(head_nop_latency_sink))

        .def(py::init(&head_nop_latency_sink::make),
             py::arg("sizeof_stream_item"),
             py::arg("nitems"),
             py::arg("timestamp_pathname"),
             py::arg("period"),
             py::arg("offset") = 0,
             D(head_nop_latency_sink, make))


        ;
}
