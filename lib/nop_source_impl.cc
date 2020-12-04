/* -*- c++ -*- */
/*
 * Copyright 2020 Josh Morman.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "nop_source_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace bench {

nop_source::sptr nop_source::make(size_t sizeof_stream_item)
{
    return gnuradio::make_block_sptr<nop_source_impl>(sizeof_stream_item);
}

nop_source_impl::nop_source_impl(size_t sizeof_stream_item)
    : sync_block("nop_source",
                 io_signature::make(0, 0, 0),
                 io_signature::make(1, -1, sizeof_stream_item))
{
}

nop_source_impl::~nop_source_impl() {}

int nop_source_impl::work(int noutput_items,
                           gr_vector_const_void_star& input_items,
                           gr_vector_void_star& output_items)
{
    // void* optr;
    // for (size_t n = 0; n < input_items.size(); n++) {
    //     optr = (void*)output_items[n];
    //     memset(optr, 0, noutput_items * output_signature()->sizeof_stream_item(n));
    // }
    return noutput_items;
}
} /* namespace bench */
} /* namespace gr */
