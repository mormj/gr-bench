/* -*- c++ -*- */
/*
 * Copyright 2023 Peraton Labs, Inc.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_BENCH_HEAD_NOP_LATENCY_SINK_H
#define INCLUDED_BENCH_HEAD_NOP_LATENCY_SINK_H

#include <gnuradio/sync_block.h>
#include <bench/api.h>

namespace gr {
namespace bench {

/*!
 * \brief <+description of block+>
 * \ingroup bench
 *
 */
class BENCH_API head_nop_latency_sink : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<head_nop_latency_sink> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of bench::head_nop_latency_sink.
     *
     * To avoid accidental use of raw pointers, bench::head_nop_latency_sink's
     * constructor is in a private implementation
     * class. bench::head_nop_latency_sink::make is the public interface for
     * creating new instances.
     */
    static sptr make(size_t sizeof_stream_item,
                     size_t nitems,
                     const std::string& timestamp_pathname,
                     size_t period,
                     size_t offset = 0);
};

} // namespace bench
} // namespace gr

#endif /* INCLUDED_BENCH_HEAD_NOP_LATENCY_SINK_H */
