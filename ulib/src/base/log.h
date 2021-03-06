/* The MIT License

   Copyright (C) 2012 Zilong Tan (tzlloch@gmail.com)

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

#ifndef __ULIB_LOG_H
#define __ULIB_LOG_H

#include <stdio.h>

#define ULIB_LOG(level, fmt, ...)						\
	fprintf(level, "[%s:%d] " fmt "\n", __FUNCTION__, __LINE__,  ##__VA_ARGS__)

#ifdef UNDEBUG
#define ULIB_DEBUG(fmt, ...)
#else
#define ULIB_DEBUG(fmt, ...)				\
	ULIB_LOG(stdout, "DEBUG  " fmt, ##__VA_ARGS__)
#endif

#define ULIB_NOTICE(fmt, ...)				\
	ULIB_LOG(stdout, "NOTICE " fmt, ##__VA_ARGS__)
#define ULIB_WARNING(fmt, ...)				\
	ULIB_LOG(stderr, "WARN   " fmt, ##__VA_ARGS__)
#define ULIB_FATAL(fmt, ...)				\
	ULIB_LOG(stderr, "FATAL  " fmt, ##__VA_ARGS__)

#endif
