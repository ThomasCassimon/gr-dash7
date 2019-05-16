/* -*- c++ -*- */

#define DASH7_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "dash7_swig_doc.i"

%{
#include "dash7/crc.h"
%}


%include "dash7/crc.h"
GR_SWIG_BLOCK_MAGIC2(dash7, crc);
