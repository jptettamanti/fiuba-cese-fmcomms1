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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <cstdio>

#include <gnuradio/io_signature.h>
#include "fmcomms1_sink_impl.h"
#include "device_source_impl.h"

namespace gr {
  namespace iio {

    fmcomms1_sink::sptr
    fmcomms1_sink::make(const std::string &host, unsigned long long frequency,
		    unsigned long samplerate, unsigned long interpolation,
		    unsigned long bandwidth,
		    bool ch1_en, bool ch2_en,
		    unsigned long buffer_size, bool cyclic)
    {
      return gnuradio::get_initial_sptr(
	    new fmcomms1_sink_impl(host, frequency, samplerate,
		    interpolation, bandwidth, ch1_en, ch2_en,
		    buffer_size, cyclic));
    }

    std::vector<std::string> fmcomms1_sink_impl::get_channels_vector(
		    bool ch1_en, bool ch2_en)
    {
	    std::vector<std::string> channels;
	    if (ch1_en)
		    channels.push_back("voltage0");
	    if (ch2_en)
		    channels.push_back("voltage1");
	    return channels;
    }

    fmcomms1_sink_impl::fmcomms1_sink_impl(const std::string &host,
		    unsigned long long frequency, unsigned long samplerate,
		    unsigned long interpolation, unsigned long bandwidth,
		    bool ch1_en, bool ch2_en,
		    unsigned long buffer_size, bool _cyclic)
	    : gr::sync_block("fmcomms1_sink",
			    gr::io_signature::make(1, -1, sizeof(short)),
			    gr::io_signature::make(0, 0, 0))
	    , device_sink_impl(host, "cf-ad9122-core-lpc",
			    get_channels_vector(ch1_en, ch2_en),
			    "cf-ad9122-core-lpc", std::vector<std::string>(),
			    buffer_size, interpolation, _cyclic)
    {
	    device_lo = new device_misc_impl(host, "adf4351-tx-lpc", "adf4351-tx-lpc", std::vector<std::string>());
	    device_clk = new device_misc_impl(host, "ad9523-lpc", "ad9523-lpc", std::vector<std::string>());

	    cyclic = _cyclic;
	    set_params(frequency, samplerate, bandwidth);
    }

    void fmcomms1_sink_impl::set_params(unsigned long long frequency,
		    unsigned long samplerate, unsigned long bandwidth)
    {
	    std::vector<std::string> params_dac, params_lo, params_clk;

	    params_dac.push_back("out_altvoltage_sampling_frequency=" +
			    boost::to_string(samplerate));

	    params_clk.push_back("out_altvoltage5_TX_LO_REF_CLK_frequency=" +
			    boost::to_string(122880000));
	    params_clk.push_back("out_altvoltage12_DAC_CLK_frequency=" +
			    boost::to_string(bandwidth));
	    params_clk.push_back("out_altvoltage10_DAC_REF_CLK_frequency=" +
			    boost::to_string(bandwidth / 8));

	    params_lo.push_back("out_altvoltage0_refin_frequency=" +
			    boost::to_string(122880000));
	    params_lo.push_back("out_altvoltage0_frequency=" +
			    boost::to_string(frequency));

	    device_clk->set_params(params_clk);
	    device_lo->set_params(params_lo);
	    device_source_impl::set_params(this->phy, params_dac);
    }

    int fmcomms1_sink_impl::work(int noutput_items,
		    gr_vector_const_void_star &input_items,
		    gr_vector_void_star &output_items)
    {
	    int ret = device_sink_impl::work(noutput_items, input_items,
			    output_items);
	    if (ret < 0 || !cyclic)
		    return ret;
	    else
		    return WORK_DONE;
    }
  } /* namespace iio */
} /* namespace gr */
