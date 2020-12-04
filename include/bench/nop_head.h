/* -*- c++ -*- */
/*
 * Copyright 2020 Josh Morman.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_BENCH_NOP_HEAD_H
#define INCLUDED_BENCH_NOP_HEAD_H

#include <gnuradio/sync_block.h>
#include <bench/api.h>

namespace gr {
namespace bench {

/*!
 * \brief <+description of block+>
 * \ingroup bench
 *
 */
class BENCH_API nop_head : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<nop_head> sptr;

    static sptr make(size_t sizeof_stream_item, uint64_t nitems);

    virtual void reset() = 0;
    virtual void set_length(uint64_t nitems) = 0;
};

} // namespace bench
} // namespace gr

#endif /* INCLUDED_BENCH_NOP_HEAD_H */
