/* -*- c++ -*- */
/*
 * Copyright 2022 Josh Morman.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_BENCH_PDU_PROCESS_IMPL_H
#define INCLUDED_BENCH_PDU_PROCESS_IMPL_H

#include <bench/pdu_process.h>

namespace gr {
namespace bench {

template <class T>
class pdu_process_impl : public pdu_process<T>
{
private:
// Nothing to declare in this block.
    void handle_msg(pmt::pmt_t pdu);

public:
    pdu_process_impl();
    ~pdu_process_impl();
};

} // namespace bench
} // namespace gr

#endif /* INCLUDED_BENCH_PDU_PROCESS_IMPL_H */
