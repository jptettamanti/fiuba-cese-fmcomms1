/* -*- c++ -*- */
/* 
 * Copyright 2016 Analog Devices Inc.
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

#ifndef INCLUDED_GR_IIO_MATH_IMPL_H
#define INCLUDED_GR_IIO_MATH_IMPL_H

#include <vector>

#include <gnuradio/iio/math.h>

extern "C" {
#include "parser.h"

int yyparse(yyscan_t scanner);
void *yy_scan_string(const char *str, yyscan_t scanner);
void yy_delete_buffer(void *buf, yyscan_t scanner);
}

namespace gr {
	namespace iio {
		class iio_math_impl : public iio_math
		{
		public:
			iio_math_impl(const std::string &function);
			~iio_math_impl();

			struct block;

			void register_block(struct block *block);

		private:
			std::vector<struct block *> blocks;
		};
	}
}

#endif /* INCLUDED_GR_IIO_MATH_IMPL_H */