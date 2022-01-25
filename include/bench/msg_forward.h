/* -*- c++ -*- */
/*
 * Copyright 2022 gr-bench author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_BENCH_MSG_FORWARD_H
#define INCLUDED_BENCH_MSG_FORWARD_H

#include <gnuradio/block.h>
#include <bench/api.h>

namespace gr {
namespace bench {

/*!
 * \brief <+description of block+>
 * \ingroup bench
 *
 */
class BENCH_API msg_forward : virtual public gr::block
{
public:
    typedef std::shared_ptr<msg_forward> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of bench::msg_forward.
     *
     * To avoid accidental use of raw pointers, bench::msg_forward's
     * constructor is in a private implementation
     * class. bench::msg_forward::make is the public interface for
     * creating new instances.
     */
    static sptr make();
    virtual size_t message_count() = 0;
};

} // namespace bench
} // namespace gr

#endif /* INCLUDED_BENCH_MSG_FORWARD_H */
