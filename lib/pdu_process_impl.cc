/* -*- c++ -*- */
/*
 * Copyright 2022 Josh Morman.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "pdu_process_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace bench {

template <class T>
typename pdu_process<T>::sptr pdu_process<T>::make()
{
    return gnuradio::make_block_sptr<pdu_process_impl<T>>();
}


/*
 * The private constructor
 */
template <class T>
pdu_process_impl<T>::pdu_process_impl()
    : gr::block(
          "pdu_process", gr::io_signature::make(0, 0, 0), gr::io_signature::make(0, 0, 0))
{
    this->message_port_register_out(pmt::mp("out"));
    this->message_port_register_in(pmt::mp("in"));
    this->set_msg_handler(pmt::mp("in"), [this](pmt::pmt_t msg) { this->handle_msg(msg); });
}

/*
 * Our virtual destructor.
 */
template <class T>
pdu_process_impl<T>::~pdu_process_impl()
{
}

template <>
void pdu_process_impl<gr_complex>::handle_msg(pmt::pmt_t pdu)
{
    auto p = pmt::cdr(pdu);
    size_t len;
    auto ptr = c32vector_elements(p, len);
    auto newmsg = pmt::cons(pmt::car(pdu), pmt::init_c32vector(len, ptr));

    this->message_port_pub(pmt::mp("out"), newmsg);
}

template <>
void pdu_process_impl<float>::handle_msg(pmt::pmt_t pdu)
{
    auto p = pmt::cdr(pdu);
    size_t len;
    auto ptr = f32vector_elements(p, len);
    auto newmsg = pmt::cons(pmt::car(pdu), pmt::init_f32vector(len, ptr));

    this->message_port_pub(pmt::mp("out"), newmsg);
}

template <>
void pdu_process_impl<int32_t>::handle_msg(pmt::pmt_t pdu)
{
    auto p = pmt::cdr(pdu);
    size_t len;
    auto ptr = s32vector_elements(p, len);
    auto newmsg = pmt::cons(pmt::car(pdu), pmt::init_s32vector(len, ptr));

    this->message_port_pub(pmt::mp("out"), newmsg);
}

template <>
void pdu_process_impl<int16_t>::handle_msg(pmt::pmt_t pdu)
{
    auto p = pmt::cdr(pdu);
    size_t len;
    auto ptr = s16vector_elements(p, len);
    auto newmsg = pmt::cons(pmt::car(pdu), pmt::init_s16vector(len, ptr));

    this->message_port_pub(pmt::mp("out"), newmsg);
}

template <>
void pdu_process_impl<uint8_t>::handle_msg(pmt::pmt_t pdu)
{
    auto p = pmt::cdr(pdu);
    size_t len;
    auto ptr = u8vector_elements(p, len);
    auto newmsg = pmt::cons(pmt::car(pdu), pmt::init_u8vector(len, ptr));

    this->message_port_pub(pmt::mp("out"), newmsg);
}


template class pdu_process<std::uint8_t>;
template class pdu_process<std::int16_t>;
template class pdu_process<std::int32_t>;
template class pdu_process<gr_complex>;
template class pdu_process<float>;

} /* namespace bench */
} /* namespace gr */
