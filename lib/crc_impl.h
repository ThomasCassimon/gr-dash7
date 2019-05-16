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

#ifndef INCLUDED_DASH7_CRC_IMPL_H
#define INCLUDED_DASH7_CRC_IMPL_H

#include <dash7/crc.h>

#define CRC_DONE    0x01
#define CRC_CALC    0x02

namespace gr {
    namespace dash7 {

        class crc_impl : public crc {
        private:
            void update_crc(uint8_t x);

            uint16_t crc;
            uint8_t state;
            uint8_t length;
            uint8_t count;

        public:
            crc_impl();

            ~crc_impl();

            // Where all the action really happens
            int work(int noutput_items,
                     gr_vector_const_void_star &input_items,
                     gr_vector_void_star &output_items);
        };

    } // namespace dash7
} // namespace gr

#endif /* INCLUDED_DASH7_CRC_IMPL_H */

