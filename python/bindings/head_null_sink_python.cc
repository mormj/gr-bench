/*
 * Copyright 2022 Free Software Foundation, Inc.
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
/* BINDTOOL_HEADER_FILE(head_null_sink.h)                                        */
/* BINDTOOL_HEADER_FILE_HASH(0161763037be68289c076f1bcffbe210)                     */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <bench/head_null_sink.h>
// pydoc.h is automatically generated in the build directory
#include <head_null_sink_pydoc.h>

void bind_head_null_sink(py::module& m)
{

    using head_null_sink = ::gr::bench::head_null_sink;


    py::class_<head_null_sink,
               gr::sync_block,
               gr::block,
               gr::basic_block,
               std::shared_ptr<head_null_sink>>(m, "head_null_sink", D(head_null_sink))

        .def(py::init(&head_null_sink::make),
             py::arg("sizeof_stream_item"),
             py::arg("nitems"),
             D(head_null_sink, make))


        ;
}