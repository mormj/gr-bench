/* -*- c++ -*- */
/*
 * Copyright 2023 Peraton Labs, Inc.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_BENCH_NOP_LATENCY_SOURCE_IMPL_H
#define INCLUDED_BENCH_NOP_LATENCY_SOURCE_IMPL_H

#include <bench/nop_latency_source.h>

#include <chrono>

namespace gr {
namespace bench {

class nop_latency_source_impl : public nop_latency_source
{
private:
    size_t _nproduce;
    std::string _timestamp_pathname;

    std::vector<std::chrono::time_point<std::chrono::steady_clock>> _timepoints;

    size_t _period;
    size_t _offset;

    size_t _sample_counter = 0;
    size_t _timestamp_counter;


public:
    nop_latency_source_impl(size_t sizeof_stream_item,
                            const std::string& timestamp_pathname,
                            size_t period,
                            size_t offset,
                            size_t nproduce = 0);
    ~nop_latency_source_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);

    bool stop();
};

} // namespace bench
} // namespace gr

#endif /* INCLUDED_BENCH_NOP_LATENCY_SOURCE_IMPL_H */
