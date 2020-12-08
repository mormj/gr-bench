/* -*- c++ -*- */
/*
 * Copyright 2020 gr-bench author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_BENCH_RANDOM_COPY_IMPL_H
#define INCLUDED_BENCH_RANDOM_COPY_IMPL_H

#include <bench/random_copy.h>
#include <random>

namespace gr {
namespace bench {

class random_copy_impl : public random_copy
{
private:
    const size_t d_itemsize;
    bool d_enabled;

    std::default_random_engine d_generator;


public:
    random_copy_impl(size_t itemsize);
    ~random_copy_impl() override;

    void forecast(int noutput_items, gr_vector_int& ninput_items_required) override;
    bool check_topology(int ninputs, int noutputs) override;

    int general_work(int noutput_items,
                     gr_vector_int& ninput_items,
                     gr_vector_const_void_star& input_items,
                     gr_vector_void_star& output_items) override;
};

} // namespace bench
} // namespace gr

#endif /* INCLUDED_BENCH_RANDOM_COPY_IMPL_H */
