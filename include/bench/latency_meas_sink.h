/* -*- c++ -*- */
/*
 * Copyright 2021 Josh Morman.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_BENCH_LATENCY_MEAS_SINK_H
#define INCLUDED_BENCH_LATENCY_MEAS_SINK_H

#include <gnuradio/sync_block.h>
#include <bench/api.h>

namespace gr {
namespace bench {

/*!
 * \brief <+description of block+>
 * \ingroup bench
 *
 */
class BENCH_API latency_meas_sink : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<latency_meas_sink> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of bench::latency_meas_sink.
     *
     * To avoid accidental use of raw pointers, bench::latency_meas_sink's
     * constructor is in a private implementation
     * class. bench::latency_meas_sink::make is the public interface for
     * creating new instances.
     */
    static sptr make(unsigned int samp_rate, bool blocking = true);

    virtual double avg_latency() = 0;
    virtual std::vector<int64_t> latency_samples() = 0;

};

} // namespace bench
} // namespace gr

#endif /* INCLUDED_BENCH_LATENCY_MEAS_SINK_H */
