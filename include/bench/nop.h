/* -*- c++ -*- */
/*
 * Copyright 2020 Josh Morman.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_BENCH_NOP_H
#define INCLUDED_BENCH_NOP_H

#include <gnuradio/sync_block.h>
#include <bench/api.h>

namespace gr {
namespace bench {

/*!
 * \brief <+description of block+>
 * \ingroup bench
 *
 */
class BENCH_API nop : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<nop> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of bench::nop.
     *
     * To avoid accidental use of raw pointers, bench::nop's
     * constructor is in a private implementation
     * class. bench::nop::make is the public interface for
     * creating new instances.
     */
    static sptr make(size_t sizeof_stream_item, size_t nproduce=0);
};

} // namespace bench
} // namespace gr

#endif /* INCLUDED_BENCH_NOP_H */
