/* -*- c++ -*- */
/*
 * Copyright 2020 Josh Morman.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_BENCH_SEQUENTIAL_VALIDATE_SINK_H
#define INCLUDED_BENCH_SEQUENTIAL_VALIDATE_SINK_H

#include <gnuradio/sync_block.h>
#include <bench/api.h>

namespace gr {
namespace bench {

/*!
 * \brief Validates that incoming samples were sequential with wraparound
 * \ingroup bench
 *
 */
template <class T>
class BENCH_API sequential_validate_sink : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<sequential_validate_sink<T>> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of bench::sequential_validate_sink.
     *
     * To avoid accidental use of raw pointers, bench::sequential_validate_sink's
     * constructor is in a private implementation
     * class. bench::sequential_validate_sink::make is the public interface for
     * creating new instances.
     */
    static sptr make(int rollover_value);

    // virtual bool valid() const = 0;
    // virtual void reset() = 0;
};

typedef sequential_validate_sink<std::int16_t> sequential_validate_sink_s;
// typedef sequential_validate_sink<std::int32_t> sequential_validate_sink_i;
// typedef sequential_validate_sink<gr_complex> sequential_validate_sink_c;
// typedef sequential_validate_sink<float> sequential_validate_sink_f;

} // namespace bench
} // namespace gr

#endif /* INCLUDED_BENCH_SEQUENTIAL_VALIDATE_SINK_H */
