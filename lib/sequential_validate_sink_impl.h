/* -*- c++ -*- */
/*
 * Copyright 2020 Josh Morman.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_BENCH_SEQUENTIAL_VALIDATE_SINK_IMPL_H
#define INCLUDED_BENCH_SEQUENTIAL_VALIDATE_SINK_IMPL_H

#include <bench/sequential_validate_sink.h>

namespace gr {
namespace bench {

template <class T>
class sequential_validate_sink_impl : public sequential_validate_sink<T>
{
private:
    bool d_valid = true;
    float d_eps = .000001;
    T d_prev_value;
    T d_rollover_value;

public:
    sequential_validate_sink_impl(int rollover_value);

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);

    T diff_value();

    // bool valid() const override { return d_valid; };
    // void reset() override { 
    //     d_valid = true;
    //     d_prev_value = d_rollover_value;
    // }
};


} // namespace bench
} // namespace gr

#endif /* INCLUDED_BENCH_SEQUENTIAL_VALIDATE_SINK_IMPL_H */
