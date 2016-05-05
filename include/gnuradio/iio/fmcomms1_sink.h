/* -*- c++ -*- */
/* 
 * Author: Juan Pablo Tettamanti
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


#ifndef INCLUDED_IIO_FMCOMMS1_SINK_H
#define INCLUDED_IIO_FMCOMMS1_SINK_H

#include <gnuradio/iio/api.h>
#include <gnuradio/sync_block.h>

#include "device_sink.h"

namespace gr {
  namespace iio {

    class IIO_API fmcomms1_sink : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<fmcomms1_sink> sptr;

      static sptr make(const std::string &host, unsigned long long frequency,
		    unsigned long samplerate, unsigned long interpolation,
		    unsigned long bandwidth,
		    bool ch1_en, bool ch2_en,
		    unsigned long buffer_size, bool cyclic);

      virtual void set_params(unsigned long long frequency,
		      unsigned long samplerate, unsigned long bandwidth) = 0;
    };

  } // namespace iio
} // namespace gr

#endif /* INCLUDED_IIO_FMCOMMS1_SINK_H */

