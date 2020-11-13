/* -*- c++ -*- */
/*
 * Copyright 2020 Josh Morman.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_BENCH_EXTRACT_BURST_H
#define INCLUDED_BENCH_EXTRACT_BURST_H

#include <gnuradio/block.h>
#include <bench/api.h>

namespace gr {
namespace bench {

/*!
 * \brief Output a fixed number of samples when the supplied peak signal is 1
 * \ingroup bench
 *
 */
class BENCH_API extract_burst : virtual public gr::block
{
public:
    typedef std::shared_ptr<extract_burst> sptr;
    static sptr make(const size_t burst_length, const size_t throwaway = 0);
};

} // namespace bench
} // namespace gr

#endif /* INCLUDED_BENCH_EXTRACT_BURST_H */
