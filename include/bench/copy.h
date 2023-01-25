/* -*- c++ -*- */
/*
 * Copyright 2023 gr-bench author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_BENCH_COPY_H
#define INCLUDED_BENCH_COPY_H

#include <gnuradio/sync_block.h>
#include <bench/api.h>

namespace gr {
namespace bench {

/*!
 * \brief <+description of block+>
 * \ingroup bench
 *
 */
class BENCH_API copy : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<copy> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of bench::copy.
     *
     * To avoid accidental use of raw pointers, bench::copy's
     * constructor is in a private implementation
     * class. bench::copy::make is the public interface for
     * creating new instances.
     */
    static sptr make(size_t sizeof_stream_item, bool use_memcpy=false, size_t nproduce=0);
};

} // namespace bench
} // namespace gr

#endif /* INCLUDED_BENCH_COPY_H */
