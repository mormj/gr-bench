/* -*- c++ -*- */
/*
 * Copyright 2020 Josh Morman.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_BENCH_SEQVAL_C_IMPL_H
#define INCLUDED_BENCH_SEQVAL_C_IMPL_H

#include <bench/seqval_c.h>

namespace gr {
namespace bench {

class seqval_c_impl : public seqval_c
{
private:
    bool d_valid = true;
    float d_eps = .000001;
    gr_complex d_prev_value;
    gr_complex d_rollover_value;

public:
    seqval_c_impl(int rollover_val);
    ~seqval_c_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);

    bool valid() const override { return d_valid; };
};

} // namespace bench
} // namespace gr

#endif /* INCLUDED_BENCH_SEQVAL_C_IMPL_H */
