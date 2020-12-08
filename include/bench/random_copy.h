/* -*- c++ -*- */
/*
 * Copyright 2020 gr-bench author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_BENCH_RANDOM_COPY_H
#define INCLUDED_BENCH_RANDOM_COPY_H

#include <gnuradio/block.h>
#include <bench/api.h>

namespace gr {
namespace bench {

/*!
 * \brief <+description of block+>
 * \ingroup bench
 *
 */
class BENCH_API random_copy : virtual public gr::block
{
public:
    typedef std::shared_ptr<random_copy> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of bench::random_copy.
     *
     * To avoid accidental use of raw pointers, bench::random_copy's
     * constructor is in a private implementation
     * class. bench::random_copy::make is the public interface for
     * creating new instances.
     */
    static sptr make(size_t itemsize);

};

} // namespace bench
} // namespace gr

#endif /* INCLUDED_BENCH_RANDOM_COPY_H */
