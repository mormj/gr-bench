/* -*- c++ -*- */
/*
 * Copyright 2020 Josh Morman.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_BENCH_SEQVAL_C_H
#define INCLUDED_BENCH_SEQVAL_C_H

#include <gnuradio/sync_block.h>
#include <bench/api.h>

namespace gr {
namespace bench {

/*!
 * \brief <+description of block+>
 * \ingroup bench
 *
 */
class BENCH_API seqval_c : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<seqval_c> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of bench::seqval_c.
     *
     * To avoid accidental use of raw pointers, bench::seqval_c's
     * constructor is in a private implementation
     * class. bench::seqval_c::make is the public interface for
     * creating new instances.
     */
    static sptr make(int rollover_val);

    virtual bool valid() const = 0;
};

} // namespace bench
} // namespace gr

#endif /* INCLUDED_BENCH_SEQVAL_C_H */
