/* -*- c++ -*- */
/*
 * Copyright 2021 Josh Morman.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_BENCH_LATENCY_MEAS_SINK_IMPL_H
#define INCLUDED_BENCH_LATENCY_MEAS_SINK_IMPL_H

#include <bench/latency_meas_sink.h>

namespace gr {
namespace bench {

class latency_meas_sink_impl : public latency_meas_sink
{
private:
    unsigned int d_samp_rate;
    bool d_blocking = true;

    std::vector<int64_t> d_latency_estimates;
    double d_avg_latency = 0.0;
    int64_t d_num_latency = 0;
    bool d_started = false;
    std::chrono::duration<double> d_sample_period;
    uint64_t d_total_samples = 0;
    std::chrono::time_point<std::chrono::steady_clock> d_start;

public:
    latency_meas_sink_impl(unsigned int samp_rate, bool blocking);
    ~latency_meas_sink_impl();


    virtual double avg_latency()
    {
        return d_avg_latency;
    }
    virtual std::vector<int64_t> latency_samples()
    {
        return d_latency_estimates;
    }

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace bench
} // namespace gr

#endif /* INCLUDED_BENCH_LATENCY_MEAS_SINK_IMPL_H */
