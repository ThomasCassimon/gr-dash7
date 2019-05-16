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


#ifndef INCLUDED_DASH7_CRC_H
#define INCLUDED_DASH7_CRC_H

#include <dash7/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace dash7 {

      /*!
       * \brief Calculate crc for byte stream, first byte should be length (exluding length byte).
       * The crc will be calculated for the next length - 2 bytes. The last 2 bytes will be replaced by the crc.
       * \ingroup dash7
       */
    class DASH7_API crc : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<crc> sptr;

      /*!
       * \brief Calculate crc for byte stream, first byte should be length (exluding length byte).
       * The crc will be calculated for the next length - 2 bytes. The last 2 bytes will be replaced by the crc.
       */
      static sptr make();
    };

  } // namespace dash7
} // namespace gr

#endif /* INCLUDED_DASH7_CRC_H */

