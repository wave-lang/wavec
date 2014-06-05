/**
 * \file wave_types.h
 * \brief Wave types.
 * \author RAZANAJATO RANAIVOARIVONY Harenome
 * \date 2014
 * \copyright MIT License
 */
/* The MIT License (MIT)
 *
 * Copyright (c) 2014 Éric VIOLARD, Maxime SCHMITT, Harenome RAZANAJATO RANAIVOARIVONY
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef __WAVE_TYPES_H__
#define __WAVE_TYPES_H__

#include <stdbool.h>
#include <limits.h>
#include <math.h>
#include <sys/types.h>

////////////////////////////////////////////////////////////////////////////////
// wave_bool
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Wave bool.
 */
typedef bool wave_bool;

/**
 * \brief Wave bool true.
 */
static const wave_bool WAVE_BOOL_TRUE = true;
/**
 * \brief Wave bool false.
 */
static const wave_bool WAVE_BOOL_FALSE = false;

////////////////////////////////////////////////////////////////////////////////
// wave_int
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Wave int.
 */
typedef int wave_int;

/**
 * \brief Wave integer minimum value.
 */
static const wave_int WAVE_INT_MIN = INT_MIN;

/**
 * \brief Wave integer maximum value.
 */
static const wave_int WAVE_INT_MAX = INT_MAX;

wave_int wave_int_min (wave_int a, wave_int b);
wave_int wave_int_max (wave_int a, wave_int b);

////////////////////////////////////////////////////////////////////////////////
// wave_float
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Wave float.
 */
typedef float wave_float;

wave_float wave_float_sqrt (wave_float f);
wave_float wave_float_sin (wave_float f);
wave_float wave_float_cos (wave_float f);
wave_float wave_float_log (wave_float f);
wave_float wave_float_exp (wave_float f);
wave_float wave_float_ceil (wave_float f);
wave_float wave_float_floor (wave_float f);
wave_float wave_float_min (wave_float a, wave_float b);
wave_float wave_float_max (wave_float a, wave_float b);

////////////////////////////////////////////////////////////////////////////////
// wave_char
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Wave char.
 */
typedef char wave_char;

/**
 * \brief Number of bits in a type wave_char.
 */
#define WAVE_CHAR_BIT CHAR_BIT

/**
 * \brief Wave character maximum value.
 */
static const wave_char WAVE_CHAR_MAX = CHAR_MAX;

/**
 * \brief Wave character minimum value.
 */
static const wave_char WAVE_CHAR_MIN = CHAR_MIN;

wave_char wave_char_min (wave_char a, wave_char b);
wave_char wave_char_max (wave_char a, wave_char b);

#endif /* __WAVE_TYPES_H__ */
