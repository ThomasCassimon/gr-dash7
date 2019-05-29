/* -*- c++ -*- */
/* 
 * Copyright 2019 gr-dash7 author.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "crc_impl.h"

namespace gr {
    namespace dash7 {

        crc::sptr
        crc::make() {
            return gnuradio::get_initial_sptr
                    (new crc_impl());
        }

        /*
         * The private constructor
         */
        crc_impl::crc_impl() : gr::sync_block("crc",
                                         gr::io_signature::make(1, 1, sizeof(uint8_t)),
                                         gr::io_signature::make(1, 1, sizeof(uint8_t))) {
            state = CRC_DONE;
        }

        /*
         * Our virtual destructor.
         */
        crc_impl::~crc_impl() {
        }

        int
        crc_impl::work(int noutput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items) {
            const auto *in = (const uint8_t *) input_items[0];
            auto *out = (uint8_t *) output_items[0];

            for (size_t i = 0; i < noutput_items; i++) {
                switch (state) {
                    case CRC_DONE:
                        // First byte is length, also reset the crc
                        length = in[i];
                        crc = 0xffff;
                        out[i] = reverse(in[i]);
                        count = 0;
                        state = CRC_CALC;
                        pn9_state = PN9_STATE;
                        pn9_shift = PN9_SHIFT;
                        //printf("reset %d\n", length);
                        break;
                    case CRC_CALC:
                        // 2 bytes crc (included), 1 byte length (not included)
                        if (count == length - 2) {
                            out[i] = (uint8_t) ((crc & 0xff00) >> 8);
                        } else if (count == length - 1) {
                            out[i] = (uint8_t) (crc & 0x00ff);
                            state = CRC_DONE;
                        } else {
                            update_crc(in[i]);
                            out[i] = in[i];
                        }
                        //out[i] = pn9_encoder(&pn9_state, &pn9_shift, out[i]);
                        count++;
                        break;
                    default:
                        out[i] = in[i];
                        state = CRC_DONE;
                        break;
                }
            }

            // Tell runtime system how many output items we produced.
            return noutput_items;
        }

        void crc_impl::update_crc(uint8_t x) {
            uint16_t crc_new = (uint8_t) (crc >> 8) | (crc << 8);
            crc_new ^= x;
            crc_new ^= (uint8_t) (crc_new & 0xff) >> 4;
            crc_new ^= crc_new << 12;
            crc_new ^= (crc_new & 0xff) << 5;
            crc = crc_new;
        }

        uint8_t crc_impl::reverse(uint8_t b) {
            b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
            b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
            b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
            return b;
        }

        uint8_t crc_impl::pn9_encoder(uint8_t *initalState, uint8_t *shiftValue, uint8_t src) {
            uint8_t dest = src ^ * initalState;
            uint8_t registerState;

            for(int i = 0; i < 8; i++) {
                registerState = (*initalState & 1) ^ ((*initalState & (1 << 5)) >> 5);
                * initalState = (*initalState >> 1) | (*shiftValue << 7);
                * shiftValue = registerState;
            }
            return dest;
        }

    } /* namespace dash7 */
} /* namespace gr */