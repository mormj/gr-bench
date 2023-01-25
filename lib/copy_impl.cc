/* -*- c++ -*- */
/*
 * Copyright 2023 gr-bench author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "copy_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace bench {


copy::sptr copy::make(size_t sizeof_stream_item, bool use_memcpy, size_t nproduce)
{
    return gnuradio::make_block_sptr<copy_impl>(sizeof_stream_item, use_memcpy, nproduce);
}


/*
 * The private constructor
 */
copy_impl::copy_impl(size_t sizeof_stream_item, bool use_memcpy, size_t nproduce)
    : gr::sync_block("copy",
                     gr::io_signature::make(1, 1, sizeof_stream_item),
                     gr::io_signature::make(1, 1, sizeof_stream_item)),
      _itemsize(sizeof_stream_item),
      _use_memcpy(use_memcpy),
      _nproduce(nproduce)
{
    if (_nproduce) {
        set_output_multiple(_nproduce);
    }
}

/*
 * Our virtual destructor.
 */
copy_impl::~copy_impl() {}

int copy_impl::work(int noutput_items,
                    gr_vector_const_void_star& input_items,
                    gr_vector_void_star& output_items)
{
    int n;
    if (_nproduce) {
        n = _nproduce;
    } else {
        n = noutput_items;
    }

    if (_use_memcpy) {
        auto* in = static_cast<const uint8_t*>(input_items[0]);
        auto* out = static_cast<uint8_t*>(output_items[0]);
        memcpy(out, in, n * _itemsize);
    } else {
        // This block is clearly not type safe, but for benchmarking
        // would do this as a templated block
        if (_itemsize == sizeof(float)) {
            auto* in = static_cast<const float*>(input_items[0]);
            auto* out = static_cast<float*>(output_items[0]);

            for (size_t ii = 0; ii < n; ii++) {
                out[ii] = in[ii];
            }

        } else {
            auto* in = static_cast<const uint8_t*>(input_items[0]);
            auto* out = static_cast<uint8_t*>(output_items[0]);

            for (size_t ii = 0; ii < n * _itemsize; ii++) {
                out[ii] = in[ii];
            }
        }
    }

    return n;
}

} /* namespace bench */
} /* namespace gr */
