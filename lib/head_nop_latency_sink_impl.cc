/* -*- c++ -*- */
/*
 * Copyright 2023 Peraton Labs, Inc.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "head_nop_latency_sink_impl.h"
#include <gnuradio/io_signature.h>

#include <fstream>
#include <iostream>


namespace gr {
namespace bench {

head_nop_latency_sink::sptr
head_nop_latency_sink::make(size_t sizeof_stream_item,
                            size_t nitems,
                            const std::string& timestamp_pathname,
                            size_t period,
                            size_t offset)
{
    return gnuradio::make_block_sptr<head_nop_latency_sink_impl>(
        sizeof_stream_item, nitems, timestamp_pathname, period, offset);
}


/*
 * The private constructor
 */
head_nop_latency_sink_impl::head_nop_latency_sink_impl(
    size_t sizeof_stream_item,
    size_t nitems,
    const std::string& timestamp_pathname,
    size_t period,
    size_t offset)
    : gr::sync_block("head_null_sink",
                     gr::io_signature::make(1, 1, sizeof_stream_item),
                     gr::io_signature::make(0, 0, 0)),
      d_nitems(nitems),
      _timestamp_pathname(timestamp_pathname),
      _period(period),
      _offset(offset)
{
    _timestamp_counter = offset;
}

/*
 * Our virtual destructor.
 */
head_nop_latency_sink_impl::~head_nop_latency_sink_impl() {}

int head_nop_latency_sink_impl::work(int noutput_items,
                                     gr_vector_const_void_star& input_items,
                                     gr_vector_void_star& output_items)
{
    if (d_ncopied_items >= d_nitems)
        return -1; // Done!

    unsigned n = std::min(d_nitems - d_ncopied_items, (uint64_t)noutput_items);

    if (n == 0)
        return 0;


    auto work_time = std::chrono::steady_clock::now();

    while (_timestamp_counter < d_ncopied_items + n) {
        _timestamp_counter += _period;
        _timepoints.push_back(work_time);
    }

    // memcpy(output_items[0], input_items[0], n *
    // input_signature()->sizeof_stream_item(0));
    d_ncopied_items += n;

    if (d_ncopied_items >= d_nitems)
        return -1; // Done!

    // Tell runtime system how many output items we produced.
    return n;
}

bool head_nop_latency_sink_impl::stop()
{

    // save it to a file
    std::ofstream out(_timestamp_pathname.c_str());
    for (auto ts : _timepoints) {
        out << std::chrono::duration_cast<std::chrono::nanoseconds>(ts.time_since_epoch())
                   .count()
            << std::endl;
    }
    out.close();
    return true;
}

} /* namespace bench */
} /* namespace gr */
