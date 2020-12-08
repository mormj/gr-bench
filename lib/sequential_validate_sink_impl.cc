/* -*- c++ -*- */
/*
 * Copyright 2020 Josh Morman.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "sequential_validate_sink_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace bench {

template <class T>
typename sequential_validate_sink<T>::sptr sequential_validate_sink<T>::make(int rollover_value)
{
    return gnuradio::make_block_sptr<sequential_validate_sink_impl<T>>(rollover_value);
}


template <class T>
sequential_validate_sink_impl<T>::sequential_validate_sink_impl(int rollover_value)
    : gr::sync_block("sequential_validate_sink",
                     gr::io_signature::make(
                         1 /* min inputs */, 1 /* max inputs */, sizeof(T)),
                     gr::io_signature::make(0, 0, 0)),
                     d_rollover_value(rollover_value)
{
}

// template <>
// sequential_validate_sink_impl<gr_complex>::sequential_validate_sink_impl(int rollover_val)
//     : gr::sync_block("sequential_validate_sink",
//                      gr::io_signature::make(
//                          1 /* min inputs */, 1 /* max inputs */, sizeof(gr_complex)),
//                      gr::io_signature::make(0, 0, 0)),
//                      d_rollover_value(rollover_val, -rollover_val)
// {
// }


template <class T>
T sequential_validate_sink_impl<T>::diff_value()
{
    return (T)1L;
}
// template <>
// gr_complex sequential_validate_sink_impl<gr_complex>::diff_value()
// {
//     return gr_complex(1.0, 1.0);
// }


template <class T>
int sequential_validate_sink_impl<T>::work(int noutput_items,
                                        gr_vector_const_void_star& input_items,
                                        gr_vector_void_star& output_items)
{
    const T* in = reinterpret_cast<const T*>(input_items[0]);

    for (int i=0; i<noutput_items; i++)
    {
        if ((in[i] - d_prev_value) != diff_value())
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

// template <>
// int sequential_validate_sink_impl<float>::work(int noutput_items,
//                                         gr_vector_const_void_star& input_items,
//                                         gr_vector_void_star& output_items)
// {
//     const float* in = reinterpret_cast<const float*>(input_items[0]);

//     for (int i=0; i<noutput_items; i++)
//     {
//         if (abs(in[i] - d_prev_value - diff_value()) < d_eps)
//         {
//             if (d_prev_value != d_rollover_value)
//             {
//                 d_valid = false;
//             }
//         }

//         d_prev_value = in[i];
//     }

//     // Tell runtime system how many output items we produced.
//     return noutput_items;
// }


// template <>
// int sequential_validate_sink_impl<gr_complex>::work(int noutput_items,
//                                         gr_vector_const_void_star& input_items,
//                                         gr_vector_void_star& output_items)
// {
//     const gr_complex* in = reinterpret_cast<const gr_complex*>(input_items[0]);

//     for (int i=0; i<noutput_items; i++)
//     {
//         if (abs(in[i] - d_prev_value - diff_value()) < d_eps)
//         {
//             if (d_prev_value != d_rollover_value)
//             {
//                 d_valid = false;
//             }
//         }

//         d_prev_value = in[i];
//     }

//     // Tell runtime system how many output items we produced.
//     return noutput_items;
// }


template class sequential_validate_sink_impl<std::int16_t>;
// template class sequential_validate_sink_impl<std::int32_t>;
// template class sequential_validate_sink_impl<gr_complex>;
// template class sequential_validate_sink_impl<float>;

} /* namespace bench */
} /* namespace gr */
