/* -*- c++ -*- */
/*
 * Copyright 2021 Josh Morman.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "latency_meas_sink_impl.h"
#include <gnuradio/io_signature.h>

#include <chrono>
#include <thread>

namespace gr {
namespace bench {

using input_type = gr_complex;
latency_meas_sink::sptr latency_meas_sink::make(unsigned int samp_rate, bool blocking)
{
    return gnuradio::make_block_sptr<latency_meas_sink_impl>(samp_rate, blocking);
}


/*
 * The private constructor
 */
latency_meas_sink_impl::latency_meas_sink_impl(unsigned int samp_rate, bool blocking)
    : gr::sync_block("latency_meas_sink",
                     gr::io_signature::make(
                         1 /* min inputs */, 1 /* max inputs */, sizeof(input_type)),
                     gr::io_signature::make(0, 0, 0)),
      d_samp_rate(samp_rate),
      d_blocking(blocking)
{
    d_sample_period = std::chrono::duration<double>((double)1.0 / samp_rate);
}

/*
 * Our virtual destructor.
 */
latency_meas_sink_impl::~latency_meas_sink_impl() {}

int latency_meas_sink_impl::work(int noutput_items,
                                 gr_vector_const_void_star& input_items,
                                 gr_vector_void_star& output_items)
{
    auto now = std::chrono::system_clock::now();
    if (!d_started) {
        d_start = std::chrono::steady_clock::now();
        d_started = true;
    } else {
        if (d_blocking) {
            auto now = std::chrono::steady_clock::now();
            auto expected_time = d_start + d_sample_period * d_total_samples;

            // wait until the last batch would have finished up processing
            if (expected_time > now) {
                auto limit_duration =
                    std::chrono::duration<double>(std::numeric_limits<long>::max());
                if (expected_time - now > limit_duration) {
                    GR_LOG_ALERT(d_logger,
                                 "WARNING: Throttle sleep time overflow! You "
                                 "are probably using a very low sample rate.");
                }
                std::this_thread::sleep_until(expected_time);
            }
        }
    }

    const input_type* in = reinterpret_cast<const input_type*>(input_items[0]);

    std::vector<tag_t> tags;
    get_tags_in_window(tags, 0, 0, noutput_items);
    for (auto& t : tags) {

        auto microseconds =
            std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch())
                .count();
        // std::cout << microseconds << std::endl;
        auto diff = microseconds - pmt::to_long(t.value);
        diff = diff + (int64_t)((1e6 * (t.offset - nitems_read(0))) / d_samp_rate);
        d_latency_estimates.push_back(diff);
        d_num_latency++;
        auto a = 1.0 / (double)d_num_latency;
        d_avg_latency = a * (double)diff  + (1.0 - a) * d_avg_latency;

        std::cout << "time passed is " << diff << " microseconds" << std::endl;
    }

    d_total_samples += noutput_items;
    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace bench */
} /* namespace gr */
