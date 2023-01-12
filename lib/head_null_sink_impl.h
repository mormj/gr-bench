/* -*- c++ -*- */
/*
 * Copyright 2022 gr-bench author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_BENCH_HEAD_NULL_SINK_IMPL_H
#define INCLUDED_BENCH_HEAD_NULL_SINK_IMPL_H

#include <bench/head_null_sink.h>

namespace gr {
namespace bench {

class head_null_sink_impl : public head_null_sink
{
private:
    size_t d_ncopied_items = 0;
    size_t d_nitems;

public:
    head_null_sink_impl(size_t sizeof_stream_item, size_t nitems);
    ~head_null_sink_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace bench
} // namespace gr

#endif /* INCLUDED_BENCH_HEAD_NULL_SINK_IMPL_H */
