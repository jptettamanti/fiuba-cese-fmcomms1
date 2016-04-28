/* -*- c++ -*- */
/* 
 * Copyright 2014 Analog Devices Inc.
 * Author: Paul Cercueil <paul.cercueil@analog.com>
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
#include "device_misc_impl.h"
#include "device_source_impl.h"

#include <cstdio>
#include <iostream>
#include <string>

namespace gr {
  namespace iio {

    device_misc::sptr
    device_misc::make(const std::string &host, const std::string &device,
		    const std::string &device_phy,
		    const std::vector<std::string> &params)
    {
      return gnuradio::get_initial_sptr
        (new device_misc_impl(host, device, device_phy, params));
    }

    void device_misc_impl::set_params(const std::vector<std::string> &params)
    {
	    device_source_impl::set_params(this->phy, params);
    }

    /*
     * The private constructor
     */
    device_misc_impl::device_misc_impl(const std::string &host,
		    const std::string &device,
		    const std::string &device_phy,
		    const std::vector<std::string> &params)
      : gr::sync_block("device_misc",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(1, -1, sizeof(short)))
    {
	    unsigned short vid, pid;

	    if (host.empty()) {
		    ctx = iio_create_default_context();
		    if (!ctx)
			    ctx = iio_create_network_context(NULL);
	    } else {
		    ctx = iio_create_network_context(host.c_str());
	    }
	    if (ctx) {
		    dev = iio_context_find_device(ctx, device.c_str());
		    phy = iio_context_find_device(ctx, device_phy.c_str());
	    }
	    if (ctx && (!dev || !phy)) {
		    iio_context_destroy(ctx);
		    throw std::runtime_error("Device not found");
	    }

	    set_params(params);
    }

    /*
     * Our virtual destructor.
     */
    device_misc_impl::~device_misc_impl()
    {
	    iio_context_destroy(ctx);
	    std::cout << "Buffer destroyed\n";
    }

    /*
     * Fake method.
     */
    int
    device_misc_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
	return 0;
    }

  } /* namespace iio */
} /* namespace gr */
