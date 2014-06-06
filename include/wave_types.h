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
 * \class wave_bool
 * \brief Wave boolean.
 */
/**
 * \brief Wave boolean.
 */
typedef bool wave_bool;

/**
 * \brief Wave bool true.
 * \relatesalso wave_bool
 */
static const wave_bool WAVE_BOOL_TRUE = true;
/**
 * \brief Wave bool false.
 * \relatesalso wave_bool
 */
static const wave_bool WAVE_BOOL_FALSE = false;

/**
 * \brief \c and operation for wave_bool.
 * \param a First wave_bool.
 * \param b Second wave_bool.
 * \retval true if both wave_bool are \c true.
 * \retval false otherwise.
 * \relatesalso wave_bool
 */
wave_bool wave_bool_and (wave_bool a, wave_bool b);

/**
 * \brief \c or operation for wave_bool.
 * \param a First wave_bool.
 * \param b Second wave_bool.
 * \retval true if at least one of the arguments is \c true.
 * \retval false otherwise.
 * \relatesalso wave_bool
 */
wave_bool wave_bool_or (wave_bool a, wave_bool b);

/**
 * \brief \c not operation for wave_bool.
 * \param b bool.
 * \retval true if \c b is false
 * \retval false otherwise.
 * \relatesalso wave_bool
 */
wave_bool wave_bool_not (wave_bool b);

////////////////////////////////////////////////////////////////////////////////
// wave_int
////////////////////////////////////////////////////////////////////////////////

/**
 * \class wave_int
 * \brief Wave integer.
 */
/**
 * \brief Wave integer.
 */
typedef int wave_int;

/**
 * \brief Wave integer minimum value.
 * \relatesalso wave_int
 */
static const wave_int WAVE_INT_MIN = INT_MIN;

/**
 * \brief Wave integer maximum value.
 * \relatesalso wave_int
 */
static const wave_int WAVE_INT_MAX = INT_MAX;

/**
 * \brief \c min operation for wave_int.
 * \param a First wave_int.
 * \param b Second wave_int.
 * \return The minimum of \c a and \c b.
 * \relatesalso wave_int
 */
wave_int wave_int_min (wave_int a, wave_int b);

/**
 * \brief \c max operation for wave_int.
 * \param a First wave_int.
 * \param b Second wave_int.
 * \return The maximum of \c a and \c b.
 * \relatesalso wave_int
 */
wave_int wave_int_max (wave_int a, wave_int b);

////////////////////////////////////////////////////////////////////////////////
// wave_float
////////////////////////////////////////////////////////////////////////////////

/**
 * \class wave_float
 * \brief Wave float.
 */
/**
 * \brief Wave float.
 */
typedef float wave_float;

/**
 * \brief \c sqrt operation for wave_float.
 * \param f float.
 * \return Square root of \c f.
 * \relatesalso wave_float
 */
wave_float wave_float_sqrt (wave_float f);

/**
 * \brief \c sin operation for wave_float.
 * \param f float.
 * \return Sinus of \c f.
 * \relatesalso wave_float
 */
wave_float wave_float_sin (wave_float f);

/**
 * \brief \c cos operation for wave_float.
 * \param f float.
 * \return Cosinus of \c f.
 * \relatesalso wave_float
 */
wave_float wave_float_cos (wave_float f);

/**
 * \brief \c log operation for wave_float.
 * \param f float.
 * \return Logarithm of \c f.
 * \relatesalso wave_float
 */
wave_float wave_float_log (wave_float f);

/**
 * \brief \c exp operation for wave_float.
 * \param f float.
 * \return Exponential of \c f.
 * \relatesalso wave_float
 */
wave_float wave_float_exp (wave_float f);

/**
 * \brief \c ceil operation for wave_float.
 * \param f float.
 * \return Ceiling of \c f.
 * \relatesalso wave_float
 */
wave_float wave_float_ceil (wave_float f);

/**
 * \brief \c floor operation for wave_float.
 * \param f float.
 * \return Floor of \c f.
 * \relatesalso wave_float
 */
wave_float wave_float_floor (wave_float f);

/**
 * \brief \c min operation for wave_float.
 * \param a First wave_float.
 * \param b Second wave_float.
 * \return Minimum of \c a and \c b.
 * \relatesalso wave_float
 */
wave_float wave_float_min (wave_float a, wave_float b);

/**
 * \brief \c max operation for wave_float.
 * \param a First wave_float.
 * \param b Second wave_float.
 * \return Maximum of \c a and \c b.
 * \relatesalso wave_float
 */
wave_float wave_float_max (wave_float a, wave_float b);

////////////////////////////////////////////////////////////////////////////////
// wave_char
////////////////////////////////////////////////////////////////////////////////

/**
 * \class wave_char
 * \brief Wave character.
 */
/**
 * \brief Wave character.
 */
typedef char wave_char;

/**
 * \brief Number of bits in a type wave_char.
 * \relatesalso wave_char
 */
#define WAVE_CHAR_BIT CHAR_BIT

/**
 * \brief Wave character maximum value.
 * \relatesalso wave_char
 */
static const wave_char WAVE_CHAR_MAX = CHAR_MAX;

/**
 * \brief Wave character minimum value.
 * \relatesalso wave_char
 */
static const wave_char WAVE_CHAR_MIN = CHAR_MIN;

/**
 * \brief \c min operation for wave_char.
 * \param a First wave_char.
 * \param b Second wave_char.
 * \return Minimum of \c a and \c b.
 * \relatesalso wave_char
 */
wave_char wave_char_min (wave_char a, wave_char b);

/**
 * \brief \c max operation for wave_char.
 * \param a First wave_char.
 * \param b Second wave_char.
 * \return Maximum of \c a and \c b.
 * \relatesalso wave_char
 */
wave_char wave_char_max (wave_char a, wave_char b);

#endif /* __WAVE_TYPES_H__ */
