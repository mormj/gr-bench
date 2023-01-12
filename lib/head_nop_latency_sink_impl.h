/* -*- c++ -*- */
/*
 * Copyright 2023 Peraton Labs, Inc.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_BENCH_HEAD_NOP_LATENCY_SINK_IMPL_H
#define INCLUDED_BENCH_HEAD_NOP_LATENCY_SINK_IMPL_H

#include <bench/head_nop_latency_sink.h>

namespace gr {
namespace bench {

class head_nop_latency_sink_impl : public head_nop_latency_sink
{
private:
    size_t d_ncopied_items = 0;
    size_t d_nitems;

    std::string _timestamp_pathname;
    std::vector<std::chrono::time_point<std::chrono::steady_clock>> _timepoints;

    size_t _period;
    size_t _offset;

    size_t _sample_counter = 0;
    size_t _timestamp_counter;

public:
    head_nop_latency_sink_impl(size_t sizeof_stream_item,
                     size_t nitems,
                     const std::string& timestamp_pathname,
                     size_t period,
                     size_t offset = 0);
    ~head_nop_latency_sink_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);

    bool stop() override;
};

} // namespace bench
} // namespace gr

#endif /* INCLUDED_BENCH_HEAD_NOP_LATENCY_SINK_IMPL_H */
