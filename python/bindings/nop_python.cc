/*
 * Copyright 2020 Free Software Foundation, Inc.
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
/* BINDTOOL_HEADER_FILE(nop.h)                                        */
/* BINDTOOL_HEADER_FILE_HASH(c342d804db9727c99f886c2e35ab4218)                     */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <bench/nop.h>
// pydoc.h is automatically generated in the build directory
#include <nop_pydoc.h>

void bind_nop(py::module& m)
{

    using nop    = ::gr::bench::nop;


    py::class_<nop, gr::sync_block, gr::block, gr::basic_block,
        std::shared_ptr<nop>>(m, "nop", D(nop))

        .def(py::init(&nop::make),
           py::arg("sizeof_stream_item"),
           D(nop,make)
        )
        



        ;




}








