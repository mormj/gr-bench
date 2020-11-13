/* -*- c++ -*- */
/*
 * Copyright 2020 Josh Morman.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "extract_burst_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace bench {

extract_burst::sptr extract_burst::make(const size_t burst_length, const size_t throwaway)
{
    return gnuradio::make_block_sptr<extract_burst_impl>(burst_length, throwaway);
}


/*
 * The private constructor
 */
extract_burst_impl::extract_burst_impl(const size_t burst_length, const size_t throwaway)
    : gr::block("extract_burst",
                gr::io_signature::make2(2, 2, sizeof(gr_complex), sizeof(char)),
                gr::io_signature::make(1, 1, sizeof(gr_complex))),
      d_burst_len(burst_length),
      d_throwaway(throwaway)
{
    set_output_multiple(d_burst_len);
}

/*
 * Our virtual destructor.
 */
extract_burst_impl::~extract_burst_impl() {}

void extract_burst_impl::forecast(int noutput_items, gr_vector_int& ninput_items_required)
{
    if (d_burst_q.size() > 0) {
        ninput_items_required[0] = ninput_items_required[1] = d_burst_len - d_s_idx[0];
    } else {
        ninput_items_required[0] = ninput_items_required[1] =
            noutput_items; // - d_frame_buf_cnt;
    }
}

int extract_burst_impl::general_work(int noutput_items,
                                     gr_vector_int& ninput_items,
                                     gr_vector_const_void_star& input_items,
                                     gr_vector_void_star& output_items)
{
    const gr_complex* in = reinterpret_cast<const gr_complex*>(input_items[0]);
    const char* peaks = reinterpret_cast<const char*>(input_items[1]);
    gr_complex* out = reinterpret_cast<gr_complex*>(output_items[0]);

    int nin = ninput_items[0];
    if (ninput_items[1] < nin)
        nin = ninput_items[1];

    int no = 0; // how many outputs have we produced
    int ni = 0; // how many inputs have we consumed
    uint64_t nw = nitems_written(0);
    uint64_t nr = nitems_read(0);

    // Finish filling the queue of unfinished bursts
    for (int i = 0; i < d_burst_q.size(); i++) {
        if (d_s_idx[i] != 0) {
            int samples_left = nin;
            if (samples_left > d_burst_len - d_s_idx[i]) {
                samples_left = d_burst_len - d_s_idx[i];
            }
            memcpy(
                d_burst_q[i].data() + d_s_idx[i], in, sizeof(gr_complex) * samples_left);
            d_s_idx[i] += samples_left;
        }
    }

    // Clear the output buffers
    int frames_produced = 0;
    for (int i = 0; i < d_burst_q.size(); i++) {
        if (no + d_burst_len > noutput_items) {
            break; // no room to output samples
        }

        auto s = d_s_idx.front();
        auto frame = d_burst_q.front();

        if (s > d_burst_len)
            std::cout << "ERROR: overfull buffer" << std::endl;

        if (s >= d_burst_len) {
            memcpy(out + no, frame.data(), sizeof(gr_complex) * d_burst_len);
            no += d_burst_len;
            frames_produced++;
        } else {
            break;
        }
    }
    for (int i = 0; i < frames_produced; i++) {
        d_burst_q.pop_front();
        d_s_idx.pop_front();
    }

    if (d_burst_q.size() < s_queue_size) {
        // Look for peaks in the input
        for (int i = 0; i < nin; i++) {
            if (peaks[i] == 1) {
                d_last_peak = nr + i;
                if (d_burst_cnt > d_throwaway) {
                    // start a new burst
                    d_burst_q.emplace_back(d_burst_len);

                    int samples_left = nin - i;
                    if (d_burst_len < samples_left) {
                        samples_left = d_burst_len;
                    }

                    memcpy(d_burst_q.back().data(),
                           in + i,
                           sizeof(gr_complex) * samples_left);
                    d_s_idx.push_back(samples_left);
                } else {
                    d_burst_cnt++;
                }
            }
        }

        consume_each(nin);
    }


    // Tell runtime system how many output items we produced.
    return no;
}

} /* namespace bench */
} /* namespace gr */
