/**
 * \file wave_types.h
 * \brief Wave types.
 * \author RAZANAJATO RANAIVOARIVONY Harenome
 * \author SCHMITT Maxime
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

#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>

////////////////////////////////////////////////////////////////////////////////
// Typedefs.
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
 * \class wave_int
 * \brief Wave integer.
 */
/**
 * \brief Wave integer.
 */
typedef int wave_int;

/**
 * \class wave_float
 * \brief Wave float.
 */
/**
 * \brief Wave float.
 */
typedef float wave_float;

/**
 * \class wave_char
 * \brief Wave character.
 */
/**
 * \brief Wave character.
 */
typedef char wave_char;

/**
 * \class wave_string
 * \brief Wave string.
 */
/**
 * \brief Wave string.
 */
typedef wave_char * wave_string;

/**
 * \brief Const wave_string.
 */
typedef const wave_char * const_wave_string;

////////////////////////////////////////////////////////////////////////////////
// wave_bool
////////////////////////////////////////////////////////////////////////////////

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

/**
 * \brief Convert a null terminated string to wave_bool.
 * \param s String.
 * \retval true if the string starts with true.
 * \retval false otherwise.
 * \relatesalso wave_bool
 */
wave_bool wave_bool_from_string (const char * s);

////////////////////////////////////////////////////////////////////////////////
// wave_int
////////////////////////////////////////////////////////////////////////////////

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
 * \brief Cast from wave_int to wave_float.
 * \param f A wave_float.
 * \return The floor of the float.
 * \relatesalso wave_int
 * \relatesalso wave_float
 */
wave_int wave_int_from_wave_float (wave_float f);

/**
 * \brief Convert a null terminated string to a wave_int.
 * \param str A null terminated string.
 * \return The wave_int associated.
 * \relatesalso wave_int
 */
wave_int wave_int_from_string (const char * str);

/**
 * \brief The \c unary \c plus operation.
 * \param a A wave_int.
 * \return +a.
 * \relatesalso wave_int
 */
wave_int wave_int_unary_plus (wave_int a);

/**
 * \brief The \c unary \c minus operation.
 * \param a A wave_int.
 * \return -a.
 * \relatesalso wave_int
 */
wave_int wave_int_unary_minus (wave_int a);

/**
 * \brief \c Increment an wave_int.
 * \param a A wave_int.
 * \return a+1.
 * \relatesalso wave_int
 */
wave_int wave_int_increment (wave_int a);

/**
 * \brief \c Decrement an wave_int.
 * \param a A wave_int.
 * \return a-1.
 * \relatesalso wave_int
 */
wave_int wave_int_decrement (wave_int a);

/**
 * \brief The \c square \c root of an wave_int.
 * \param a A wave_int.
 * \return sqrt(a).
 * \relatesalso wave_int
 * \relatesalso wave_float
 */
wave_float wave_int_sqrt (wave_int a);

/**
 * \brief The \c sin of an wave_int.
 * \param a A wave_int.
 * \return sin(a).
 * \relatesalso wave_int
 * \relatesalso wave_float
 */
wave_float wave_int_sin (wave_int a);

/**
 * \brief The \c cos of an wave_int.
 * \param a A wave_int.
 * \return cos(a).
 * \relatesalso wave_int
 * \relatesalso wave_float
 */
wave_float wave_int_cos (wave_int a);

/**
 * \brief The \c log of an wave_int.
 * \param a A wave_int.
 * \return log(a).
 * \relatesalso wave_int
 * \relatesalso wave_float
 */
wave_float wave_int_log (wave_int a);

/**
 * \brief The \c exp of an wave_int.
 * \param a A wave_int.
 * \return exp(a).
 * \relatesalso wave_int
 * \relatesalso wave_float
 */
wave_float wave_int_exp (wave_int a);

/**
 * \brief The \c ceil of an wave_int.
 * \param a A wave_int.
 * \return ceil(a).
 * \relatesalso wave_int
 * \relatesalso wave_float
 */
wave_float wave_int_ceil (wave_int a);

/**
 * \brief The \c floor of an wave_int.
 * \param a A wave_int.
 * \return floor(a).
 * \relatesalso wave_int
 * \relatesalso wave_float
 */
wave_float wave_int_floor (wave_int a);

/**
 * \brief The \c addition of two wave_int.
 * \param a A wave_int.
 * \param b A wave_int.
 * \return a + b.
 * \relatesalso wave_int
 */
wave_int wave_int_binary_plus (wave_int a, wave_int b);

/**
 * \brief The subtract of two wave_int.
 * \param a A wave_int.
 * \param b A wave_int.
 * \return a - b.
 * \relatesalso wave_int
 */
wave_int wave_int_binary_minus (wave_int a, wave_int b);

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

/**
 * \brief \c Multiplication operation for wave_int.
 * \param a First wave_int.
 * \param b Second wave_int.
 * \return a * b.
 * \relatesalso wave_int
 */
wave_int wave_int_times (wave_int a, wave_int b);

/**
 * \brief Division operation for wave_int.
 * \param a First wave_int.
 * \param b Second wave_int.
 * \return a / b.
 * \relatesalso wave_int
 */
wave_int wave_int_divide (wave_int a, wave_int b);

/**
 * \brief \c mod operation for wave_int.
 * \param a First wave_int.
 * \param b Second wave_int.
 * \return a mod(b).
 * \relatesalso wave_int
 */
wave_int wave_int_mod (wave_int a, wave_int b);

/**
 * \brief \c equals operation for wave_int.
 * \param a First wave_int.
 * \param b Second wave_int.
 * \return a == b.
 * \retval true True.
 * \retval false False.
 * \relatesalso wave_int
 * \relatesalso wave_bool
 */
wave_bool wave_int_equals (wave_int a, wave_int b);

/**
 * \brief \c differs operation for wave_int.
 * \param a First wave_int.
 * \param b Second wave_int.
 * \return a != b
 * \retval true True.
 * \retval false False.
 * \relatesalso wave_int
 * \relatesalso wave_bool
 */
wave_bool wave_int_differs (wave_int a, wave_int b);

/**
 * \brief \c lesser \c or \c equals operation for wave_int.
 * \param a First wave_int.
 * \param b Second wave_int.
 * \return a <= b.
 * \retval true True.
 * \retval false False.
 * \relatesalso wave_int
 * \relatesalso wave_bool
 */
wave_bool wave_int_lesser_or_equals (wave_int a, wave_int b);

/**
 * \brief \c greater \c or \c equals operation for wave_int.
 * \param a First wave_int.
 * \param b Second wave_int.
 * \return a >= b.
 * \retval true True.
 * \retval false False.
 * \relatesalso wave_int
 * \relatesalso wave_bool
 */
wave_bool wave_int_greater_or_equals (wave_int a, wave_int b);

/**
 * \brief \c greater operation for wave_int.
 * \param a First wave_int.
 * \param b Second wave_int.
 * \return a > b.
 * \retval true True.
 * \retval false False.
 * \relatesalso wave_int
 * \relatesalso wave_bool
 */
wave_bool wave_int_greater (wave_int a, wave_int b);

/**
 * \brief \c lesser operation for wave_int.
 * \param a First wave_int.
 * \param b Second wave_int.
 * \return a < b.
 * \retval true True.
 * \retval false False.
 * \relatesalso wave_int
 * \relatesalso wave_bool
 */
wave_bool wave_int_lesser (wave_int a, wave_int b);

////////////////////////////////////////////////////////////////////////////////
// wave_float
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief The cast from wave_float to wave_int.
 * \param i The wave_int.
 * \return A wave_float.
 * \relatesalso wave_int
 * \relatesalso wave_float
 */
wave_float wave_float_from_wave_int (wave_int i);

/**
 * \brief The unary plus of a.
 * \param a The wave_float.
 * \return +a.
 * \relatesalso wave_float
 */
wave_float wave_float_unary_plus (wave_float a);

/**
 * \brief The unary minus of a.
 * \param a The wave_float.
 * \return +a.
 * \relatesalso wave_float
 */
wave_float wave_float_unary_minus (wave_float a);

/**
 * \brief Increment a float.
 * \param a The wave_float.
 * \return a+1.0.
 * \relatesalso wave_float
 */
wave_float wave_float_increment (wave_float a);

/**
 * \brief Decrement a float.
 * \param a The wave_float.
 * \return a-1.0.
 * \relatesalso wave_float
 */
wave_float wave_float_decrement (wave_float a);

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
 * \brief The \c addition of two wave_float.
 * \param a A wave_float.
 * \param b A wave_float.
 * \return a + b.
 * \relatesalso wave_float
 */
wave_float wave_float_binary_plus (wave_float a, wave_float b);

/**
 * \brief The \c subtract of two wave_float.
 * \param a A wave_float.
 * \param b A wave_float.
 * \return a - b.
 * \relatesalso wave_float
 */
wave_float wave_float_binary_minus (wave_float a, wave_float b);

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

/**
 * \brief \c multiplication operation for wave_float.
 * \param a First wave_float.
 * \param b Second wave_float.
 * \return a * b.
 * \relatesalso wave_float
 */
wave_float wave_float_times (wave_float a, wave_float b);

/**
 * \brief \c division operation for wave_float.
 * \param a First wave_float.
 * \param b Second wave_float.
 * \return a / b.
 * \relatesalso wave_float
 */
wave_float wave_float_divide (wave_float a, wave_float b);

/**
 * \brief \c mod operation for wave_float.
 * \param a First wave_float.
 * \param b Second wave_float.
 * \return a mod(b).
 * \relatesalso wave_float
 */
wave_float wave_float_mod (wave_float a, wave_float b);

/**
 * \brief \c equals operation for wave_float.
 * \param a First wave_float.
 * \param b Second wave_float.
 * \return a == b.
 * \relatesalso wave_float
 * \relatesalso wave_bool
 */
wave_bool wave_float_equals (wave_float a, wave_float b);

/**
 * \brief \c differs operation for wave_float.
 * \param a First wave_float.
 * \param b Second wave_float.
 * \return a != b.
 * \relatesalso wave_float
 * \relatesalso wave_bool
 */
wave_bool wave_float_differs (wave_float a, wave_float b);

/**
 * \brief \c lesser \c or \c equals operation for wave_float.
 * \param a First wave_float.
 * \param b Second wave_float.
 * \return a <= b.
 * \relatesalso wave_float
 * \relatesalso wave_bool
 */
wave_bool wave_float_lesser_or_equals (wave_float a, wave_float b);

/**
 * \brief \c greater \c or \c equals operation for wave_float.
 * \param a First wave_float.
 * \param b Second wave_float.
 * \return a >= b.
 * \relatesalso wave_float
 * \relatesalso wave_bool
 */
wave_bool wave_float_greater_or_equals (wave_float a, wave_float b);

/**
 * \brief \c greater operation for wave_float.
 * \param a First wave_float.
 * \param b Second wave_float.
 * \return a > b.
 * \relatesalso wave_float
 * \relatesalso wave_bool
 */
wave_bool wave_float_greater (wave_float a, wave_float b);

/**
 * \brief \c lesset operation for wave_float.
 * \param a First wave_float.
 * \param b Second wave_float.
 * \return a < b.
 * \relatesalso wave_float
 * \relatesalso wave_bool
 */
wave_bool wave_float_lesser (wave_float a, wave_float b);

/**
 * \brief Convert a null terminated string to a wave_float.
 * \param str A null terminated string.
 * \return The wave_float associated.
 * \relatesalso wave_float
 */
wave_float wave_float_from_string (const char * str);

////////////////////////////////////////////////////////////////////////////////
// wave_char
////////////////////////////////////////////////////////////////////////////////

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
 * \brief Concatenation of two chars.
 * \param a A wave_char
 * \param b A wave_char
 * \return The wave_string.
 */
wave_string wave_char_plus (wave_char a, wave_char b);

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

/**
 * \brief \c equals operation for wave_char.
 * \param a First wave_char.
 * \param b Second wave_char.
 * \return a == b
 * \relatesalso wave_char
 * \relatesalso wave_bool
 */
wave_bool wave_char_equals (wave_char a, wave_char b);

/**
 * \brief \c differs operation for wave_char.
 * \param a First wave_char.
 * \param b Second wave_char.
 * \return a != b
 * \relatesalso wave_char
 * \relatesalso wave_bool
 */
wave_bool wave_char_differs (wave_char a, wave_char b);

/**
 * \brief \c lesser \c or \c equals operation for wave_char.
 * \param a First wave_char.
 * \param b Second wave_char.
 * \return a <= b
 * \relatesalso wave_char
 * \relatesalso wave_bool
 */
wave_bool wave_char_lesser_or_equals (wave_char a, wave_char b);

/**
 * \brief \c greater \c or \c equals operation for wave_char.
 * \param a First wave_char.
 * \param b Second wave_char.
 * \return a >= b
 * \relatesalso wave_char
 * \relatesalso wave_bool
 */
wave_bool wave_char_greater_or_equals (wave_char a, wave_char b);

/**
 * \brief \c greater operation for wave_char.
 * \param a First wave_char.
 * \param b Second wave_char.
 * \return a > b
 * \relatesalso wave_char
 * \relatesalso wave_bool
 */
wave_bool wave_char_greater (wave_char a, wave_char b);

/**
 * \brief \c lesser operation for wave_char.
 * \param a First wave_char.
 * \param b Second wave_char.
 * \return a < b
 * \relatesalso wave_char
 * \relatesalso wave_bool
 */
wave_bool wave_char_lesser (wave_char a, wave_char b);

/**
 * \brief Get a wave_char from a code.
 * \param code Code.
 * \return wave_char.
 * \relatesalso wave_char
 * \sa wave_char_code
 */
wave_char wave_char_from_wave_int (wave_int code);

/**
 * \brief Get the code of a wave_char.
 * \param c Character.
 * \return Code.
 * \relatesalso wave_char
 * \sa wave_char_from_wave_int
 */
wave_int wave_char_code (wave_char c);

////////////////////////////////////////////////////////////////////////////////
// wave_string
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Concatenate two wave_string.
 * \param a A wave_string.
 * \param b A wave_string.
 * \return "ab"
 * \relatesalso wave_string
 */
wave_string wave_string_plus (const_wave_string a, const_wave_string b);

/**
 * \brief \c min of two wave_string.
 * \param a A wave_string.
 * \param b A wave_string.
 * \return min(a,b)
 * \relatesalso wave_string
 */
wave_string wave_string_min (const_wave_string a, const_wave_string b);

/**
 * \brief \c max of two wave_string.
 * \param a A wave_string.
 * \param b A wave_string.
 * \return max(a,b)
 * \relatesalso wave_string
 */
wave_string wave_string_max (const_wave_string a, const_wave_string b);

/**
 * \brief \c equality of two wave_string.
 * \param a A wave_string.
 * \param b A wave_string.
 * \return a == b
 * \relatesalso wave_string
 * \relatesalso wave_bool
 */
wave_bool wave_string_equals (const_wave_string a, const_wave_string b);

/**
 * \brief \c differs of two wave_string.
 * \param a A wave_string.
 * \param b A wave_string.
 * \return a != b
 * \relatesalso wave_string
 * \relatesalso wave_bool
 */
wave_bool wave_string_differs (const_wave_string a, const_wave_string b);

/**
 * \brief \c lesser \c or \c equals of two wave_string.
 * \param a A wave_string.
 * \param b A wave_string.
 * \return a <= b
 * \relatesalso wave_string
 * \relatesalso wave_bool
 */
wave_bool wave_string_lesser_or_equals (const_wave_string a, const_wave_string b);

/**
 * \brief \c greater \c or \c equals of two wave_string.
 * \param a A wave_string.
 * \param b A wave_string.
 * \return a >= b
 * \relatesalso wave_string
 * \relatesalso wave_bool
 */
wave_bool wave_string_greater_or_equals (const_wave_string a, const_wave_string b);

/**
 * \brief \c greater of two wave_string.
 * \param a A wave_string.
 * \param b A wave_string.
 * \return a > b
 * \relatesalso wave_string
 * \relatesalso wave_bool
 */
wave_bool wave_string_greater (const_wave_string a, const_wave_string b);

/**
 * \brief \c lesser of two wave_string.
 * \param a A wave_string.
 * \param b A wave_string.
 * \return a < b
 * \relatesalso wave_string
 * \relatesalso wave_bool
 */
wave_bool wave_string_lesser (const_wave_string a, const_wave_string b);

/**
 * \brief Concatenate two wave_string.
 * \param destination Destination.
 * \param source Source.
 * \return pointer to the resulting string \c destination.
 * \warning \c destination must have enough space for the result.
 * \warning The strings may not overlap.
 * This function mimics \c strcat from \c string.h, please read its manual for further information.
 */
wave_string wave_string_cat (wave_string restrict destination, const_wave_string restrict source);

/**
 * \brief Compare two wave_string.
 * \param a First string.
 * \param b Second string.
 * \return a wave_int less than, equal to, or greater than \c 0 if \c a is found, respectively, to be less than, to match, or be grater than \c b.
 * This function mimics \c strcmp from \c string.h, please read its manual for further information.
 */
wave_int wave_string_compare (const_wave_string a, const_wave_string b);

/**
 * \brief Copy a wave_string.
 * \param destination Destination.
 * \param source Source.
 * \return pointer to the resulting string \c destination.
 * \warning \c destination must have enough space for the result.
 * \warning The strings may not overlap.
 * This function mimics \c strcpy from \c string.h, please read its manual for further information.
 */
wave_string wave_string_copy (wave_string restrict destination, const_wave_string restrict source);

/**
 * \brief Calculate the length of a wave_string.
 * \param s string.
 * \return The size of the string, excluding the terminating null character.
 * This function mimics \c strlen from \c string.h, please read its manual for further information.
 */
size_t wave_string_length (const_wave_string s);

/**
 * \brief Locate the first occurence of a character in a wave_string.
 * \param s string.
 * \param c character.
 * \retval NULL if the character is not found.
 * \return pointer to the matched character if found.
 * This function mimics \c strchr from \c string.h, please read its manual for further information.
 */
wave_string wave_string_first_character (const_wave_string s, wave_char c);

/**
 * \brief Locate the last occurence of a character in a wave_string.
 * \param s string.
 * \param c character.
 * \retval NULL if the character is not found.
 * \return pointer to the matched character if found.
 * This function mimics \c strrchr from \c string.h, please read its manual for further information.
 */
wave_string wave_string_last_character (const_wave_string s, wave_char c);

/**
 * \brief Locate a substring in a wave_string.
 * \param haystack Haystack.
 * \param needle Needle.
 * \retval NULL if the substring is not found.
 * \return pointer to the beginning of the substring if found.
 * This function mimics \c strstr from \c string.h, please read its manual for further information.
 */
wave_string wave_string_sub_string (const_wave_string haystack, const_wave_string needle);

/**
 * \brief Duplicate a wave_string.
 * \param s String.
 * \retval NULL if the allocation of new memory failed
 * \return pointer to the duplicate in case of success.
 * \note The memory for the duplicate is obtained using \c malloc and thus shall be freed using \c free.
 */
wave_string wave_string_duplicate (const_wave_string s);

#endif /* __WAVE_TYPES_H__ */
