/*
 * Copyright 2021 Free Software Foundation, Inc.
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
/* BINDTOOL_HEADER_FILE(time_tag_injector.h)                                        */
/* BINDTOOL_HEADER_FILE_HASH(a6b21b7cd395fde5e5bfb2c4fe8e0217)                     */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <bench/time_tag_injector.h>
// pydoc.h is automatically generated in the build directory
#include <time_tag_injector_pydoc.h>

void bind_time_tag_injector(py::module& m)
{

    using time_tag_injector    = ::gr::bench::time_tag_injector;


    py::class_<time_tag_injector, gr::sync_block, gr::block, gr::basic_block,
        std::shared_ptr<time_tag_injector>>(m, "time_tag_injector", D(time_tag_injector))

        .def(py::init(&time_tag_injector::make),
           py::arg("interval"),
           py::arg("offset_secs") = 0,
           D(time_tag_injector,make)
        )
        



        ;




}








