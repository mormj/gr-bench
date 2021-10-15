/* -*- c++ -*- */
/*
 * Copyright 2021 Josh Morman.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_BENCH_TIME_TAG_INJECTOR_IMPL_H
#define INCLUDED_BENCH_TIME_TAG_INJECTOR_IMPL_H

#include <bench/time_tag_injector.h>
#include <chrono>


namespace gr {
namespace bench {

class time_tag_injector_impl : public time_tag_injector
{
private:
    unsigned long d_samp_rate;
    std::chrono::time_point<std::chrono::steady_clock> d_start;
    std::chrono::duration<double> d_sample_period;

public:
    time_tag_injector_impl(double interval, unsigned long samp_rate);
    ~time_tag_injector_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
    
    bool start() override
    {
        d_start = std::chrono::steady_clock::now();
        return true;
    }
};

} // namespace bench
} // namespace gr

#endif /* INCLUDED_BENCH_TIME_TAG_INJECTOR_IMPL_H */
