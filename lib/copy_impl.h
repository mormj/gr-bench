/* -*- c++ -*- */
/*
 * Copyright 2023 gr-bench author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_BENCH_COPY_IMPL_H
#define INCLUDED_BENCH_COPY_IMPL_H

#include <bench/copy.h>

namespace gr {
namespace bench {

class copy_impl : public copy
{
private:
    size_t _itemsize;
    bool _use_memcpy;
    size_t _nproduce;

public:
    copy_impl(size_t sizeof_stream_item, bool use_memcpy=false, size_t nproduce=0);
    ~copy_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace bench
} // namespace gr

#endif /* INCLUDED_BENCH_COPY_IMPL_H */
