/* -*- c++ -*- */
/*
 * Copyright 2020 Josh Morman.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_BENCH_NOP_IMPL_H
#define INCLUDED_BENCH_NOP_IMPL_H

#include <bench/nop.h>

namespace gr {
namespace bench {

class nop_impl : public nop
{
private:
    size_t _nproduce;

public:
    nop_impl(size_t sizeof_stream_item, size_t nproduce=0);
    ~nop_impl() override;

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace bench
} // namespace gr

#endif /* INCLUDED_BENCH_NOP_IMPL_H */
