/* -*- c++ -*- */
/*
 * Copyright 2020 Josh Morman.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_BENCH_NOP_HEAD_IMPL_H
#define INCLUDED_BENCH_NOP_HEAD_IMPL_H

#include <bench/nop_head.h>

namespace gr {
namespace bench {

class nop_head_impl : public nop_head
{
private:
    uint64_t d_nitems;
    uint64_t d_ncopied_items;

public:
    nop_head_impl(size_t sizeof_stream_item, uint64_t nitems);
    ~nop_head_impl() override;

    void reset() override { d_ncopied_items = 0; }
    void set_length(uint64_t nitems) override { d_nitems = nitems; }

    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items) override;
};

} // namespace bench
} // namespace gr

#endif /* INCLUDED_BENCH_NOP_nop_head_IMPL_H */
