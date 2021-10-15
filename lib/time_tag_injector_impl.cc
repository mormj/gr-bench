/* -*- c++ -*- */
/*
 * Copyright 2021 Josh Morman.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "time_tag_injector_impl.h"
#include <gnuradio/io_signature.h>
#include <thread>

namespace gr {
namespace bench {

using input_type = gr_complex;
using output_type = gr_complex;
time_tag_injector::sptr time_tag_injector::make(double interval, double offset_secs)
{
    return gnuradio::make_block_sptr<time_tag_injector_impl>(interval, offset_secs);
}


/*
 * The private constructor
 */
time_tag_injector_impl::time_tag_injector_impl(double interval, double offset_secs)
    : gr::sync_block("time_tag_injector",
                     gr::io_signature::make(
                         1, 1 , sizeof(input_type)),
                     gr::io_signature::make(
                         1, 1, sizeof(output_type)))
{
    d_sample_period = std::chrono::duration<double>(interval);
}

/*
 * Our virtual destructor.
 */
time_tag_injector_impl::~time_tag_injector_impl() {}

int time_tag_injector_impl::work(int noutput_items,
                                 gr_vector_const_void_star& input_items,
                                 gr_vector_void_star& output_items)
{
    const input_type* in = reinterpret_cast<const input_type*>(input_items[0]);
    output_type* out = reinterpret_cast<output_type*>(output_items[0]);


    auto now = std::chrono::steady_clock::now();
    auto next_tag = d_start + d_sample_period;

    if (now > next_tag) {
        d_start = std::chrono::steady_clock::now();
        // Drop a tag right in the middle of the buffer
        const auto p1 = std::chrono::system_clock::now();
        auto diff = std::chrono::duration_cast<std::chrono::microseconds>(
                        p1.time_since_epoch()).count();

        std::cout << "adding tag at " << nitems_written(0) << " with val " << diff << std::endl;
        add_item_tag(0,
                    nitems_written(0), // + noutput_items / 2,
                    pmt::string_to_symbol("time"),
                    pmt::from_long(diff));
        
    }

    std::memcpy(out, in, noutput_items * sizeof(gr_complex));

    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace bench */
} /* namespace gr */
