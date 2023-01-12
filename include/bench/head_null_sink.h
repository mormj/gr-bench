/* -*- c++ -*- */
/*
 * Copyright 2022 gr-bench author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_BENCH_HEAD_NULL_SINK_H
#define INCLUDED_BENCH_HEAD_NULL_SINK_H

#include <gnuradio/sync_block.h>
#include <bench/api.h>

namespace gr {
namespace bench {

/*!
 * \brief <+description of block+>
 * \ingroup bench
 *
 */
class BENCH_API head_null_sink : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<head_null_sink> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of bench::head_null_sink.
     *
     * To avoid accidental use of raw pointers, bench::head_null_sink's
     * constructor is in a private implementation
     * class. bench::head_null_sink::make is the public interface for
     * creating new instances.
     */
    static sptr make(size_t sizeof_stream_item, size_t nitems);
};

} // namespace bench
} // namespace gr

#endif /* INCLUDED_BENCH_HEAD_NULL_SINK_H */
