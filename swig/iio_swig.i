/* -*- c++ -*- */

#define IIO_API

%include "gnuradio.i"

%{
#include "gnuradio/iio/device_source.h"
#include "gnuradio/iio/device_sink.h"
#include "gnuradio/iio/device_misc.h"
#include "gnuradio/iio/fmcomms2_source.h"
#include "gnuradio/iio/fmcomms2_sink.h"
#include "gnuradio/iio/fmcomms5_source.h"
#include "gnuradio/iio/fmcomms5_sink.h"
%}

%include "gnuradio/iio/device_source.h"
%include "gnuradio/iio/device_sink.h"
%include "gnuradio/iio/device_misc.h"
%include "gnuradio/iio/fmcomms2_source.h"
%include "gnuradio/iio/fmcomms2_sink.h"
%include "gnuradio/iio/fmcomms5_source.h"
%include "gnuradio/iio/fmcomms5_sink.h"

GR_SWIG_BLOCK_MAGIC2(iio, device_source);
GR_SWIG_BLOCK_MAGIC2(iio, device_sink);
GR_SWIG_BLOCK_MAGIC2(iio, device_misc);
GR_SWIG_BLOCK_MAGIC2(iio, fmcomms2_source);
GR_SWIG_BLOCK_MAGIC2(iio, fmcomms2_sink);
GR_SWIG_BLOCK_MAGIC2(iio, fmcomms5_source);
GR_SWIG_BLOCK_MAGIC2(iio, fmcomms5_sink);
