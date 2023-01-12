/* -*- c++ -*- */
/*
 * Copyright 2023 Peraton Labs, Inc.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_BENCH_NOP_LATENCY_SOURCE_H
#define INCLUDED_BENCH_NOP_LATENCY_SOURCE_H

#include <gnuradio/sync_block.h>
#include <bench/api.h>

namespace gr {
namespace bench {

/*!
 * \brief <+description of block+>
 * \ingroup bench
 *
 */
class BENCH_API nop_latency_source : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<nop_latency_source> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of bench::nop_latency_source.
     *
     * To avoid accidental use of raw pointers, bench::nop_latency_source's
     * constructor is in a private implementation
     * class. bench::nop_latency_source::make is the public interface for
     * creating new instances.
     */
    static sptr make(size_t sizeof_stream_item,
                     const std::string& timestamp_pathname,
                     size_t period,
                     size_t offset = 0,
                     size_t nproduce = 0);
};

} // namespace bench
} // namespace gr

#endif /* INCLUDED_BENCH_NOP_LATENCY_SOURCE_H */
