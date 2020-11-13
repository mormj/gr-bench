/* -*- c++ -*- */
/*
 * Copyright 2020 Josh Morman.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_BENCH_EXTRACT_BURST_IMPL_H
#define INCLUDED_BENCH_EXTRACT_BURST_IMPL_H

#include <bench/extract_burst.h>
#include <deque>
#include <vector>
namespace gr {
namespace bench {

class extract_burst_impl : public extract_burst
{
private:
    static const int s_queue_size = 10;
    int d_burst_len;
    int d_throwaway;
    std::deque<std::vector<gr_complex>> d_burst_q;
    std::deque<int> d_s_idx;
    int d_burst_cnt = 0;
    uint64_t d_last_peak = 0;

public:
    extract_burst_impl(const size_t burst_length, const size_t throwaway = 0);
    ~extract_burst_impl();

    // Where all the action really happens
    void forecast(int noutput_items, gr_vector_int& ninput_items_required);

    int general_work(int noutput_items,
                     gr_vector_int& ninput_items,
                     gr_vector_const_void_star& input_items,
                     gr_vector_void_star& output_items);
};

} // namespace bench
} // namespace gr

#endif /* INCLUDED_BENCH_EXTRACT_BURST_IMPL_H */
