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

#ifndef INCLUDED_IIO_FMCOMMS1_SOURCE_IMPL_H
#define INCLUDED_IIO_FMCOMMS1_SOURCE_IMPL_H

#include <string>
#include <vector>

#include <gnuradio/iio/fmcomms1_source.h>

#include "device_source_impl.h"
#include "device_misc_impl.h"

namespace gr {
  namespace iio {

    class fmcomms1_source_impl : public fmcomms1_source
			       , public device_source_impl
    {
     private:
      std::vector<std::string> get_channels_vector(
		      bool ch1_en, bool ch2_en);

     protected:
      device_misc_impl *device_clk;
      device_misc_impl *device_lo;
      device_misc_impl *device_gain;

     public:
      fmcomms1_source_impl(const std::string &host,
		    unsigned long long frequency, unsigned long samplerate,
		    unsigned long decimation, unsigned long bandwidth,
		    bool ch1_en, bool ch2_en,
		    unsigned long buffer_size,
		    double gain);

      void set_params(unsigned long long frequency,
		      unsigned long samplerate, unsigned long bandwidth,
		      double gain);
    };

  } // namespace iio
} // namespace gr

#endif /* INCLUDED_IIO_FMCOMMS1_SOURCE_IMPL_H */
