/* -*- c++ -*- */
/*
 * Copyright 2020 Josh Morman.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "seqval_c_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace bench {

seqval_c::sptr seqval_c::make(int rollover_val)
{
    return gnuradio::make_block_sptr<seqval_c_impl>(rollover_val);
}


/*
 * The private constructor
 */
seqval_c_impl::seqval_c_impl(int rollover_val)
    : gr::sync_block("seqval_c",
                     gr::io_signature::make(
                         1 /* min inputs */, 1 /* max inputs */, sizeof(gr_complex)),
                     gr::io_signature::make(0, 0, 0)),
      d_rollover_value(rollover_val, -rollover_val),
      d_prev_value(rollover_val,-rollover_val)
{
}

/*
 * Our virtual destructor.
 */
seqval_c_impl::~seqval_c_impl() {}

int seqval_c_impl::work(int noutput_items,
                        gr_vector_const_void_star& input_items,
                        gr_vector_void_star& output_items)
{
    const gr_complex* in = reinterpret_cast<const gr_complex*>(input_items[0]);

    for (int i=0; i<noutput_items; i++)
    {
        if (abs(in[i] - d_prev_value - gr_complex(1.0, -1.0)) > d_eps)
        {
            if (d_prev_value != d_rollover_value)
            {
                d_valid = false;
            }
        }

        d_prev_value = in[i];
    }

    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace bench */
} /* namespace gr */
