/* -*- c++ -*- */
/*
 * Copyright 2020 Josh Morman.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "nop_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace bench {

nop::sptr nop::make(size_t sizeof_stream_item)
{
    return gnuradio::make_block_sptr<nop_impl>(sizeof_stream_item);
}

nop_impl::nop_impl(size_t sizeof_stream_item)
    : sync_block("nop",
            io_signature::make(0, -1, sizeof_stream_item),
            io_signature::make(0, -1, sizeof_stream_item))
{
}

/*
 * Our virtual destructor.
 */
nop_impl::~nop_impl() {}

int nop_impl::work(int noutput_items,
                   gr_vector_const_void_star& input_items,
                   gr_vector_void_star& output_items)
{
    return noutput_items;
}

} /* namespace bench */
} /* namespace gr */
