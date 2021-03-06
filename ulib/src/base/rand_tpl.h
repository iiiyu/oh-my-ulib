/* The MIT License

   Copyright (C) 2011 Zilong Tan (tzlloch@gmail.com)

   Permission is hereby granted, free of charge, to any person obtaining
   a copy of this software and associated documentation files (the
   "Software"), to deal in the Software without restriction, including
   without limitation the rights to use, copy, modify, merge, publish,
   distribute, sublicense, and/or sell copies of the Software, and to
   permit persons to whom the Software is furnished to do so, subject to
   the following conditions:

   The above copyright notice and this permission notice shall be
   included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
   NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
   BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
   ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
   CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
*/

#ifndef __ULIB_RAND_TPL_H
#define __ULIB_RAND_TPL_H

#include <stdlib.h>
#include "common.h"
#include "bit.h"

#define RAND_XORSHIFT(x, a, b, c) do {		\
		(x) ^= (x) << (a);		\
		(x) ^= (x) >> (b);		\
		(x) ^= (x) << (c);		\
	} while (0)

#define RAND_XORSHIFT_R(x, a, b, c) do {	\
		(x) ^= (x) >> (a);		\
		(x) ^= (x) << (b);		\
		(x) ^= (x) >> (c);		\
	} while (0)

#define RAND_XORSHIFT32(x) RAND_XORSHIFT(x, 13, 17, 5)

#define RAND_XORSHIFT64(x) RAND_XORSHIFT(x, 21, 35, 4)

#define RAND_NR_XS64(x)	   RAND_XORSHIFT_R(x, 17, 31, 8)

#define RAND_NR_LC64(x)							\
	((x) =  (x) * 2862933555777941757LL + 7046029254386353087LL)

#define RAND_NR_MWC64(x)					\
	((x) = 4294957665U * ((x) & 0xffffffff) + ((x) >> 32))

#define RAND_NR_COMBINE(u, v, w) ({		\
			typeof(u) _r = (u);	\
			RAND_XORSHIFT64(_r);	\
			(_r + (v)) ^ (w); })

#define RAND_NR_MIX(u, v, w) do {		\
		RAND_NR_LC64(u);		\
		RAND_NR_XS64(v);		\
		RAND_NR_MWC64(w);		\
	} while (0)

#define RAND_NR_INIT(u, v, w, iv) do {			\
		(u) = (iv) ^ 4101842887655102017LL;	\
		RAND_NR_LC64(u);			\
		(v) = (u);				\
		RAND_NR_LC64(u);			\
		RAND_NR_XS64(v);			\
		(w) = (v);				\
		RAND_NR_MIX(u, v, w);			\
	} while (0)

#define RAND_NR_NEXT(u, v, w) ({			\
			RAND_NR_MIX(u, v, w);		\
			RAND_NR_COMBINE(u, v, w); })

#define RAND_NR_DOUBLE(x)			\
	(5.42101086242752217E-20 * (x))

#define RAND_SAMPLE(_n, _r, _buf) do {					\
		/* reference:						\
		   http://code.activestate.com/recipes/272884/ */	\
		int _i, _k, _pop = (_n);				\
		for (_i = (int)(_r), _k = 0; _i >= 0; --_i) {		\
			double _z = 1., _x = drand48();			\
			while (_x < _z) _z -= _z * _i / (_pop--);	\
			if (_k != (_n) - _pop - 1)			\
				swap((_buf)[_k], (_buf)[(_n) - _pop - 1]); \
			++_k;						\
		}							\
	} while (0)

#define RAND_INT_MIX64(h) ({			\
			(h) += ~((h) << 32);	\
			(h) ^= ((h) >> 22);	\
			(h) += ~((h) << 13);	\
			(h) ^= ((h) >> 8);	\
			(h) += ((h) << 3);	\
			(h) ^= ((h) >> 15);	\
			(h) += ~((h) << 27);	\
			(h) ^= ((h) >> 31); })

#define RAND_INT2_MIX64(h) ({				\
			(h)  = (~(h)) + ((h) << 21);	\
			(h) ^= ROR64(h, 24);		\
			(h) *= 265UL;			\
			(h) ^= ROR64(h, 14);		\
			(h) *= 21UL;			\
			(h) ^= ROR64(h, 28);		\
			(h) *= 2147483649UL; })

#endif
