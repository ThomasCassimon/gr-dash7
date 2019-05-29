#!/usr/bin/env python
# -*- coding: utf-8 -*-
# 
# Copyright 2019 gr-dash7 author.
# 
# This is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
# 
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this software; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
# 

from gnuradio import gr, gr_unittest
from gnuradio import blocks
import dash7_swig as dash7

class qa_crc (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_t (self):
        # set up test data
        src_data = (0x06, 0x1, 0xa, 0x8, 0x4, 0x0, 0x0)
        expected = (0x60, 0xfe, 0xeb, 0x15, 0x9e, 0x11, 0x1d)
        crc = dash7.crc()

        # Calculate crc
        self.tb.run ()
        src = blocks.vector_source_b(src_data, vlen=1)
        dst = blocks.vector_sink_b(vlen=1)
        self.tb.connect(src, crc, dst)
        self.tb.run()
        result_data = dst.data()
        print(result_data)
        assert(result_data == expected)


if __name__ == '__main__':
    gr_unittest.run(qa_crc, "qa_crc.xml")
