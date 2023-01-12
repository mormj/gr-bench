/* -*- c++ -*- */
/*
 * Copyright 2023 Peraton Labs, Inc.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "nop_latency_source_impl.h"
#include <gnuradio/io_signature.h>

#include <fstream>
#include <iostream>


namespace gr {
namespace bench {

nop_latency_source::sptr nop_latency_source::make(size_t sizeof_stream_item,
                                                  const std::string& timestamp_pathname,
                                                  size_t period,
                                                  size_t offset,
                                                  size_t nproduce)
{
    return gnuradio::make_block_sptr<nop_latency_source_impl>(
        sizeof_stream_item, timestamp_pathname, period, offset, nproduce);
}


/*
 * The private constructor
 */
nop_latency_source_impl::nop_latency_source_impl(size_t sizeof_stream_item,
                                                 const std::string& timestamp_pathname,
                                                 size_t period,
                                                 size_t offset,
                                                 size_t nproduce)
    : gr::sync_block("nop_latency_source",
                     io_signature::make(0, 0, 0),
                     io_signature::make(1, -1, sizeof_stream_item)),
      _timestamp_pathname(timestamp_pathname),
      _nproduce(nproduce),
      _period(period),
      _offset(offset)
{
    _timestamp_counter = offset;

    if (_nproduce)
        set_output_multiple(_nproduce);

    _timepoints.reserve(1e6);
}

/*
 * Our virtual destructor.
 */
nop_latency_source_impl::~nop_latency_source_impl() {}

int nop_latency_source_impl::work(int noutput_items,
                                  gr_vector_const_void_star& input_items,
                                  gr_vector_void_star& output_items)
{
    auto work_time = std::chrono::steady_clock::now();

    // are we due for a timestamp
    auto n = _nproduce ? _nproduce : noutput_items;

    while (_timestamp_counter < _sample_counter + n) {
        _timestamp_counter += _period;
        _timepoints.push_back(work_time);
    }

    _sample_counter += n;
    return n;
}

bool nop_latency_source_impl::stop()
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
