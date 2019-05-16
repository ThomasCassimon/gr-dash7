/* -*- c++ -*- */
/* 
 * Copyright 2019 .
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
#include "cca_impl.h"
#include <cstdint>


namespace gr {
  namespace dash7 {

	const std::size_t cca_impl::MAX_CHANNELS = 280;
	const std::size_t cca_impl::QUEUE_LEN = 5;
	const std::size_t cca_impl::CONGESTION_TIMEOUT = 1;
	const std::size_t cca_impl::INITIAL_TIMEOUT = 15;

    cca::sptr
    cca::make()
    {
      return gnuradio::get_initial_sptr
        (new cca_impl());
    }

    /*
     * The private constructor
     */
    cca_impl::cca_impl()
      : gr::block("cca",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(1, 1, sizeof(int))),
		channel_queue(QUEUE_LEN)
    {
		for (int& channel: this->channel_queue)
		{
			channel = rand() % 280;
		}	
	}

    /*
     * Our virtual destructor.
     */
    cca_impl::~cca_impl()
    {
    }

    void
    cca_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      ninput_items_required[0] = noutput_items;
    }

    int
    cca_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const float *in = (const float *) input_items[0];
      int *out = (int *) output_items[0];

		
		for (int i = 0; i < noutput_items; ++i)
		{
			if (this->channel_queue.empty())
			{
				out[i] = 0;
			}
			else
			{
				out[i] = 1;
			}
		}

      consume_each (noutput_items);

      return noutput_items;
    }

  } /* namespace dash7 */
} /* namespace gr */

