/* -*- c++ -*- */
/*
 * Copyright 2020 Josh Morman.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_BENCH_NOP_SOURCE_H
#define INCLUDED_BENCH_NOP_SOURCE_H

#include <gnuradio/sync_block.h>
#include <bench/api.h>

namespace gr {
namespace bench {

/*!
 * \brief <+description of block+>
 * \ingroup bench
 *
 */
class BENCH_API nop_source : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<nop_source> sptr;

    /*!
     * Build a nop source block.
     *
     * \param sizeof_stream_item size of the stream items in bytes.
     */
    static sptr make(size_t sizeof_stream_item);
};

} // namespace bench
} // namespace gr

#endif /* INCLUDED_BENCH_NOP_SOURCE_H */
