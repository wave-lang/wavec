/**
 * \file wave_types.c
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
#include "wave/common/wave_types.h"

////////////////////////////////////////////////////////////////////////////////
// static utilities
////////////////////////////////////////////////////////////////////////////////

static const double _WAVE_FLOAT_EPSILON = 1.0e-5;

static inline wave_string _wave_string_alloc (size_t length)
{
    return calloc (length + 1, sizeof (wave_char));
}

static inline void _string_to_lower (char * s)
{
    for (int i = 0; s[i]; ++i)
        s[i] = (wave_char) tolower (s[i]);
}

////////////////////////////////////////////////////////////////////////////////
// wave_bool
////////////////////////////////////////////////////////////////////////////////

wave_bool wave_bool_and (wave_bool a, wave_bool b)
{
    return a && b;
}

wave_bool wave_bool_or (wave_bool a, wave_bool b)
{
    return a || b;
}

wave_bool wave_bool_not (wave_bool b)
{
    return ! b;
}

wave_bool wave_bool_equals (wave_bool a, wave_bool b)
{
    return a == b;
}

wave_bool wave_bool_differs (wave_bool a, wave_bool b)
{
    return a != b;
}

wave_bool wave_bool_lesser (wave_bool a, wave_bool b)
{
    wave_bool result = false;
    if (a == true && b == false)
        result = true;
    return result;
}

wave_bool wave_bool_greater (wave_bool a, wave_bool b)
{
    return wave_bool_lesser (b, a);
}

wave_bool wave_bool_lesser_or_equals (wave_bool a, wave_bool b)
{
    wave_bool result = wave_bool_equals (a, b);
    if (! result)
        result = wave_bool_lesser (a, b);

    return result;
}

wave_bool wave_bool_greater_or_equals (wave_bool a, wave_bool b)
{
    return wave_bool_lesser_or_equals (b, a);
}

wave_bool wave_bool_min (wave_bool a, wave_bool b)
{
    return wave_bool_lesser (a, b) ? a : b;
}

wave_bool wave_bool_max (wave_bool a, wave_bool b)
{
    return wave_bool_greater (a, b) ? a : b;
}

wave_bool wave_bool_from_string (const char * s)
{
    char word[5] = { '\0' };
    strncpy (word, s, 4);
    _string_to_lower (word);
    return strcmp (word, "true") == 0;
}

////////////////////////////////////////////////////////////////////////////////
// wave_int ////////////////////////////////////////////////////////////////////////////////

wave_int wave_int_from_wave_float (wave_float f)
{
    return (wave_int) f;
}

wave_int wave_int_from_string (const char * str)
{
    return atoi (str);
}

wave_int wave_int_unary_plus (wave_int a)
{
    return a;
}

wave_int wave_int_unary_minus (wave_int a)
{
    return - a;
}

wave_int wave_int_increment (wave_int a)
{
    return a + 1;
}

wave_int wave_int_decrement (wave_int a)
{
    return a - 1;
}

wave_float wave_int_sqrt (wave_int a)
{
    wave_float f = wave_float_from_wave_int (a);
    return wave_float_sqrt (f);
}

wave_float wave_int_sin (wave_int a)
{
    wave_float f = wave_float_from_wave_int (a);
    return wave_float_sin (f);
}

wave_float wave_int_cos (wave_int a)
{
    wave_float f = wave_float_from_wave_int (a);
    return wave_float_cos (f);
}

wave_float wave_int_log (wave_int a)
{
    wave_float f = wave_float_from_wave_int (a);
    return wave_float_log (f);
}

wave_float wave_int_exp (wave_int a)
{
    wave_float f = wave_float_from_wave_int (a);
    return wave_float_exp (f);
}

wave_float wave_int_ceil (wave_int a)
{
    wave_float f = wave_float_from_wave_int (a);
    return wave_float_ceil (f);
}

wave_float wave_int_floor (wave_int a)
{
    wave_float f = wave_float_from_wave_int (a);
    return wave_float_floor (f);
}

wave_int wave_int_binary_plus (wave_int a, wave_int b)
{
    return a + b;
}

wave_int wave_int_binary_minus (wave_int a, wave_int b)
{
    return a - b;
}

wave_int wave_int_min (wave_int a, wave_int b)
{
    return a < b ? a : b;
}

wave_int wave_int_max (wave_int a, wave_int b)
{
    return a > b ? a : b;
}

wave_int wave_int_times (wave_int a, wave_int b)
{
    return a * b;
}

wave_int wave_int_divide (wave_int a, wave_int b)
{
    return a / b;
}

wave_int wave_int_mod (wave_int a, wave_int b)
{
    return a % b; }

wave_bool wave_int_equals (wave_int a, wave_int b)
{
    return a == b;
}

wave_bool wave_int_differs (wave_int a, wave_int b)
{
    return ! wave_int_equals (a, b);
}

wave_bool wave_int_lesser_or_equals (wave_int a, wave_int b)
{
    return ! wave_int_greater (a, b);
}

wave_bool wave_int_greater_or_equals (wave_int a, wave_int b)
{
    return ! wave_int_lesser (a, b);
}

wave_bool wave_int_greater (wave_int a, wave_int b)
{
    return wave_int_lesser (b, a);
}

wave_bool wave_int_lesser (wave_int a, wave_int b)
{
    return a < b;
}

////////////////////////////////////////////////////////////////////////////////
// wave_float
////////////////////////////////////////////////////////////////////////////////

wave_float wave_float_from_wave_int (wave_int i)
{
    return (wave_float) i;
}

wave_float wave_float_unary_plus (wave_float a)
{
    return a;
}

wave_float wave_float_unary_minus (wave_float a)
{
    return - a;
}

wave_float wave_float_increment (wave_float a)
{
    return a + 1;
}

wave_float wave_float_decrement (wave_float a)
{
    return a - 1;
}

wave_float wave_float_sqrt (wave_float f)
{
    return sqrt (f);
}

wave_float wave_float_sin (wave_float f)
{
    return sin (f);
    }

wave_float wave_float_cos (wave_float f)
{
    return cos (f);
}

wave_float wave_float_log (wave_float f)
{
    return log (f);
}

wave_float wave_float_exp (wave_float f)
{
    return exp (f);
}

wave_float wave_float_ceil (wave_float f)
{
    return ceil (f);
}

wave_float wave_float_floor (wave_float f)
{
    return floor (f);
}

wave_float wave_float_binary_plus (wave_float a, wave_float b)
{
    return a + b;
}

wave_float wave_float_binary_minus (wave_float a, wave_float b)
{
    return a - b;
}

wave_float wave_float_min (wave_float a, wave_float b)
{
    return fmin (a, b);
}

wave_float wave_float_max (wave_float a, wave_float b)
{
    return fmax (a, b);
}

wave_float wave_float_times (wave_float a, wave_float b)
{
    return a * b;
}

wave_float wave_float_divide (wave_float a, wave_float b)
{
    return a / b;
}

wave_float wave_float_mod (wave_float a, wave_float b)
{
    wave_int a_int = wave_int_from_wave_float (a);
    wave_int b_int = wave_int_from_wave_float (b);
    wave_int result_int = wave_int_mod (a_int, b_int);

    return wave_float_from_wave_int (result_int);
}

wave_bool wave_float_equals (wave_float a, wave_float b)
{
    return fabs (a - b) < _WAVE_FLOAT_EPSILON;
}

wave_bool wave_float_differs (wave_float a, wave_float b)
{
    return ! wave_float_equals (a, b);
}

wave_bool wave_float_lesser_or_equals (wave_float a, wave_float b)
{
    return wave_float_equals (a, b) || wave_float_lesser (a, b);
}

wave_bool wave_float_greater_or_equals (wave_float a, wave_float b)
{
    return wave_float_equals (a, b) || wave_float_greater (a, b);
}

wave_bool wave_float_greater (wave_float a, wave_float b)
{
    return isgreater (a, b);
}

wave_bool wave_float_lesser (wave_float a, wave_float b)
{
    return isless (a, b);
}

wave_float wave_float_from_string (const char * str)
{
    return strtof (str, NULL);
}

////////////////////////////////////////////////////////////////////////////////
// wave_char
////////////////////////////////////////////////////////////////////////////////

wave_string wave_char_plus (wave_char a, wave_char b)
{
    wave_string string = _wave_string_alloc (2);
    string[0] = a;
    string[1] = b;
    string[2] = '\0';
    return string;
}

wave_char wave_char_min (wave_char a, wave_char b)
{
    return a < b ? a : b;
}

wave_char wave_char_max (wave_char a, wave_char b)
{
    return a > b ? a : b;
}

wave_bool wave_char_equals (wave_char a, wave_char b)
{
    return a == b;
}

wave_bool wave_char_differs (wave_char a, wave_char b)
{
    return ! wave_char_equals (a, b);
}

wave_bool wave_char_lesser_or_equals (wave_char a, wave_char b)
{
    return ! wave_char_greater (a, b);
}

wave_bool wave_char_greater_or_equals (wave_char a, wave_char b)
{
    return ! wave_char_lesser (a, b);
}

wave_bool wave_char_greater (wave_char a, wave_char b)
{
    return wave_char_lesser (b, a);
}

wave_bool wave_char_lesser (wave_char a, wave_char b)
{
    return a < b;
}

wave_char wave_char_from_wave_int (wave_int code)
{
    return (wave_char) code;
}

wave_int wave_char_code (wave_char c)
{
    return c;
}

////////////////////////////////////////////////////////////////////////////////
// wave_string
////////////////////////////////////////////////////////////////////////////////

wave_string wave_string_plus (const_wave_string a, const_wave_string b)
{
    size_t total_size = wave_string_length (a) + wave_string_length (b);
    wave_string new_string = _wave_string_alloc (total_size);
    wave_string_copy (new_string, a);
    wave_string_cat (new_string, b);
    return new_string;
}

wave_string wave_string_min (const_wave_string a, const_wave_string b)
{
    wave_int comparison = wave_string_compare (a, b);
    const_wave_string minimum = comparison < 0 ? a : b;
    wave_string new_string = _wave_string_alloc (wave_string_length (minimum));
    wave_string_copy (new_string, minimum);
    return new_string;
}

wave_string wave_string_max (const_wave_string a, const_wave_string b)
{
    wave_int comparison = wave_string_compare (a, b);
    const_wave_string maximum = comparison > 0 ? a : b;
    wave_string new_string = _wave_string_alloc (wave_string_length (maximum));
    wave_string_copy (new_string, maximum);
    return new_string;
}

wave_bool wave_string_equals (const_wave_string a, const_wave_string b)
{
    return wave_string_compare (a, b) == 0;
}

wave_bool wave_string_differs (const_wave_string a, const_wave_string b)
{
    return ! wave_string_equals (a, b);
}

wave_bool wave_string_lesser_or_equals (const_wave_string a, const_wave_string b)
{
    return ! wave_string_greater (a, b);
}

wave_bool wave_string_greater_or_equals (const_wave_string a, const_wave_string b)
{
    return ! wave_string_lesser (a, b);
}

wave_bool wave_string_greater (const_wave_string a, const_wave_string b)
{
    return wave_string_lesser (b, a);
}

wave_bool wave_string_lesser (const_wave_string a, const_wave_string b)
{
    return wave_string_compare (a, b) < 0;
}

#define _wave_string_char_op(return_type, function_name) \
    return_type function_name ## _char_left (wave_char a, const_wave_string b) \
    { \
        wave_char a_string[2] = { a, '\0' }; \
        return function_name (a_string, b); \
    } \
    \
    return_type function_name ## _char_right (const_wave_string a, wave_char b) \
    { \
        wave_char b_string[2] = { b, '\0' }; \
        return function_name (a, b_string); \
    }

_wave_string_char_op (wave_string, wave_string_plus)
_wave_string_char_op (wave_string, wave_string_min)
_wave_string_char_op (wave_string, wave_string_max)
_wave_string_char_op (wave_bool, wave_string_equals)
_wave_string_char_op (wave_bool, wave_string_differs)
_wave_string_char_op (wave_bool, wave_string_lesser_or_equals)
_wave_string_char_op (wave_bool, wave_string_greater_or_equals)
_wave_string_char_op (wave_bool, wave_string_lesser)
_wave_string_char_op (wave_bool, wave_string_greater)

#undef _wave_string_char_op

wave_string wave_string_cat (wave_string restrict destination, const_wave_string restrict source)
{
    return strcat (destination, source);
}

wave_int wave_string_compare (const_wave_string a, const_wave_string b)
{
    return strcmp (a, b);
}

wave_string wave_string_copy (wave_string restrict destination, const_wave_string restrict source)
{
    return strcpy (destination, source);
}

size_t wave_string_length (const_wave_string s)
{
    return strlen (s);
}

wave_string wave_string_first_character (const_wave_string s, wave_char c)
{
    return strchr (s, c);
}

wave_string wave_string_last_character (const_wave_string s, wave_char c)
{
    return strrchr (s, c);
}

wave_string wave_string_sub_string (const_wave_string haystack, const_wave_string needle)
{
    return strstr (haystack, needle);
}

wave_string wave_string_duplicate (const_wave_string s)
{
    /* strdup is not available in all C versions. */
    size_t length = wave_string_length (s) + 1;
    wave_string duplicate = malloc (length * sizeof * duplicate);
    wave_string_copy (duplicate, s);
    return duplicate;
}
