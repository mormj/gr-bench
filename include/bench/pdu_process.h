/* -*- c++ -*- */
/*
 * Copyright 2022 Josh Morman.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_BENCH_PDU_PROCESS_H
#define INCLUDED_BENCH_PDU_PROCESS_H

#include <gnuradio/block.h>
#include <bench/api.h>

namespace gr {
namespace bench {

/*!
 * \brief <+description of block+>
 * \ingroup bench
 *
 */
template <class T>
class BENCH_API pdu_process : virtual public gr::block
{
public:
    typedef std::shared_ptr<pdu_process> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of bench::pdu_process.
     *
     * To avoid accidental use of raw pointers, bench::pdu_process's
     * constructor is in a private implementation
     * class. bench::pdu_process::make is the public interface for
     * creating new instances.
     */
    static sptr make();
};

} // namespace bench
} // namespace gr

#endif /* INCLUDED_BENCH_PDU_PROCESS_H */
