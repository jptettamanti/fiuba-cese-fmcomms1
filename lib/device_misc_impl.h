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

#ifndef INCLUDED_IIO_DEVICE_MISC_IMPL_H
#define INCLUDED_IIO_DEVICE_MISC_IMPL_H

#include <string>
#include <vector>

#include <iio.h>
#include <gnuradio/iio/device_misc.h>

namespace gr {
  namespace iio {

    class device_misc_impl : public device_misc
    {
     protected:
	     struct iio_context *ctx;
	     struct iio_device *dev, *phy;

     public:
      device_misc_impl(const std::string &host, const std::string &device,
		      const std::string &device_phy,
		      const std::vector<std::string> &params);
      ~device_misc_impl();

      void set_params(const std::vector<std::string> &params);

      // Where all the action really happens
      int work(int noutput_items,
	       gr_vector_const_void_star &input_items,
	       gr_vector_void_star &output_items);
    };

  } // namespace iio
} // namespace gr

#endif /* INCLUDED_IIO_DEVICE_MISC_IMPL_H */
