/* -*- c++ -*- */
/*
 * Copyright 2022 gr-bench author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "head_null_sink_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace bench {

head_null_sink::sptr head_null_sink::make(size_t sizeof_stream_item, size_t nitems)
{
    return gnuradio::make_block_sptr<head_null_sink_impl>(sizeof_stream_item, nitems);
}


/*
 * The private constructor
 */
head_null_sink_impl::head_null_sink_impl(size_t sizeof_stream_item, size_t nitems)
    : gr::sync_block("head_null_sink",
                     gr::io_signature::make(1, 1, sizeof_stream_item),
                     gr::io_signature::make(0, 0, 0)),
      d_nitems(nitems)
{
}

/*
 * Our virtual destructor.
 */
head_null_sink_impl::~head_null_sink_impl() {}

int head_null_sink_impl::work(int noutput_items,
                              gr_vector_const_void_star& input_items,
                              gr_vector_void_star& output_items)
{
    if (d_ncopied_items >= d_nitems)
        return -1; // Done!

    unsigned n = std::min(d_nitems - d_ncopied_items, (uint64_t)noutput_items);

    if (n == 0)
        return 0;

    // memcpy(output_items[0], input_items[0], n *
    // input_signature()->sizeof_stream_item(0));
    d_ncopied_items += n;

    if (d_ncopied_items >= d_nitems)
        return -1; // Done!

    // Tell runtime system how many output items we produced.
    return n;
}

} /* namespace bench */
} /* namespace gr */
