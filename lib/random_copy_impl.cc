/* -*- c++ -*- */
/*
 * Copyright 2020 gr-bench author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "random_copy_impl.h"
#include <gnuradio/io_signature.h>
#include <random>

namespace gr {
namespace bench {

random_copy::sptr random_copy::make(size_t itemsize)
{
    return gnuradio::make_block_sptr<random_copy_impl>(itemsize);
}

random_copy_impl::random_copy_impl(size_t itemsize)
    : block("random_copy",
            io_signature::make(1, -1, itemsize),
            io_signature::make(1, -1, itemsize)),
      d_itemsize(itemsize),
      d_enabled(true)
{
    // message_port_register_in(pmt::mp("en"));
    // set_msg_handler(pmt::mp("en"), [this](pmt::pmt_t msg) { this->handle_enable(msg); });
}

random_copy_impl::~random_copy_impl() {}


void random_copy_impl::forecast(int noutput_items, gr_vector_int& ninput_items_required)
{
    unsigned ninputs = ninput_items_required.size();
    for (unsigned i = 0; i < ninputs; i++)
        ninput_items_required[i] = noutput_items;
}

bool random_copy_impl::check_topology(int ninputs, int noutputs) { return ninputs == noutputs; }

int random_copy_impl::general_work(int noutput_items,
                            gr_vector_int& ninput_items,
                            gr_vector_const_void_star& input_items,
                            gr_vector_void_star& output_items)
{
    const uint8_t** in = (const uint8_t**)&input_items[0];
    uint8_t** out = (uint8_t**)&output_items[0];

    // double r = ((double) rand() / (RAND_MAX));

    // int new_n = (int) ( r * noutput_items );
    std::uniform_int_distribution<int> distribution(0, noutput_items);
    int new_n = distribution(d_generator);

    int n = 0;
    if (d_enabled) {
        int ninputs = input_items.size();
        for (int i = 0; i < ninputs; i++) {
            memcpy(out[i], in[i], new_n * d_itemsize);
        }
        n = new_n;
    }

    consume_each(new_n);
    return n;
}


} /* namespace bench */
} /* namespace gr */
