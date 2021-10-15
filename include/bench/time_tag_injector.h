/* -*- c++ -*- */
/*
 * Copyright 2021 Josh Morman.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_BENCH_TIME_TAG_INJECTOR_H
#define INCLUDED_BENCH_TIME_TAG_INJECTOR_H

#include <gnuradio/sync_block.h>
#include <bench/api.h>

namespace gr {
namespace bench {

/*!
 * \brief <+description of block+>
 * \ingroup bench
 *
 */
class BENCH_API time_tag_injector : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<time_tag_injector> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of bench::time_tag_injector.
     *
     * To avoid accidental use of raw pointers, bench::time_tag_injector's
     * constructor is in a private implementation
     * class. bench::time_tag_injector::make is the public interface for
     * creating new instances.
     */
    static sptr make(double interval, unsigned long samp_rate);
};

} // namespace bench
} // namespace gr

#endif /* INCLUDED_BENCH_TIME_TAG_INJECTOR_H */
