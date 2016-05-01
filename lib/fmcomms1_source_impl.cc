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

#include <cstdio>

#include <gnuradio/io_signature.h>
#include "fmcomms1_source_impl.h"

namespace gr {
  namespace iio {

    fmcomms1_source::sptr
    fmcomms1_source::make(const std::string &host, unsigned long long frequency,
		    unsigned long samplerate, unsigned long decimation,
		    unsigned long bandwidth,
		    bool ch1_en, bool ch2_en,
		    unsigned long buffer_size, double gain)
    {
      return gnuradio::get_initial_sptr
        (new fmcomms1_source_impl(host, frequency, samplerate,
				  decimation, bandwidth,
				  ch1_en, ch2_en, buffer_size,
				  gain));
    }

    std::vector<std::string> fmcomms1_source_impl::get_channels_vector(
		    bool ch1_en, bool ch2_en)
    {
	    std::vector<std::string> channels;
	    if (ch1_en)
		    channels.push_back("voltage0");
	    if (ch2_en)
		    channels.push_back("voltage1");
	    return channels;
    }

    fmcomms1_source_impl::fmcomms1_source_impl(const std::string &host,
		    unsigned long long frequency, unsigned long samplerate,
		    unsigned long decimation, unsigned long bandwidth,
		    bool ch1_en, bool ch2_en,
		    unsigned long buffer_size,
		    double gain)
      : gr::sync_block("fmcomms1_source",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(1, -1, sizeof(short)))
      , device_source_impl(host, "cf-ad9643-core-lpc",
		      get_channels_vector(ch1_en, ch2_en),
		      "cf-ad9643-core-lpc", std::vector<std::string>(),
		      buffer_size, decimation)
    {
	    device_lo = new device_misc_impl(host, "adf4351-rx-lpc", "adf4351-rx-lpc", std::vector<std::string>());
	    device_clk = new device_misc_impl(host, "ad9523-lpc", "ad9523-lpc", std::vector<std::string>());
	    device_gain = new device_misc_impl(host, "ad8366-lpc", "ad8366-lpc", std::vector<std::string>());

	    set_params(frequency, samplerate, bandwidth, gain);
    }

    void fmcomms1_source_impl::set_params(unsigned long long frequency,
		    unsigned long samplerate, unsigned long bandwidth,
		    double gain)
    {
	    std::vector<std::string> params_adc, params_lo, params_clk, params_gain;

	    params_adc.push_back("in_voltage_sampling_frequency=" +
			    boost::to_string(samplerate));
	    //in_voltage_scale

	    params_clk.push_back("out_altvoltage9_RX_LO_REF_CLK_frequency=" +
			    boost::to_string(122880000));
	    params_clk.push_back("out_altvoltage2_ADC_CLK_frequency=" +
			    boost::to_string(bandwidth));

	    params_lo.push_back("out_altvoltage0_refin_frequency=" +
			    boost::to_string(122880000));
	    params_lo.push_back("out_altvoltage0_frequency=" +
			    boost::to_string(frequency));

	    params_gain.push_back("out_voltage0_hardwaregain=" +
			    boost::to_string(gain));
	    params_gain.push_back("out_voltage1_hardwaregain=" +
			    boost::to_string(gain));

	    device_clk->set_params(params_clk);
	    device_lo->set_params(params_lo);
	    device_gain->set_params(params_gain);
	    device_source_impl::set_params(params_adc);
    }

  } /* namespace iio */
} /* namespace gr */
