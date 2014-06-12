/**
 * \file wave_types.c
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
#include "wave_types.h"

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

static inline void _string_to_lower (char * s)
{
    for (int i = 0; s[i]; ++i)
        s[i] = tolower (s[i]);
}

wave_bool wave_bool_from_string (const char * s)
{
    char word[5] = { '\0' };
    strncpy (word, s, 4);
    _string_to_lower (word);
    return strcmp (word, "true") == 0;
}

////////////////////////////////////////////////////////////////////////////////
// wave_int
////////////////////////////////////////////////////////////////////////////////

wave_int wave_int_min (wave_int a, wave_int b)
{
    return a < b ? a : b;
}

wave_int wave_int_max (wave_int a, wave_int b)
{
    return a > b ? a : b;
}

wave_int wave_int_from_string (const char * str)
{
    return atoi (str);
}

////////////////////////////////////////////////////////////////////////////////
// wave_float
////////////////////////////////////////////////////////////////////////////////

wave_float wave_float_sqrt (wave_float f)
{
    return sqrtf (f);
}

wave_float wave_float_sin (wave_float f)
{
    return sinf (f);
}

wave_float wave_float_cos (wave_float f)
{
    return cosf (f);
}

wave_float wave_float_log (wave_float f)
{
    return logf (f);
}

wave_float wave_float_exp (wave_float f)
{
    return expf (f);
}

wave_float wave_float_ceil (wave_float f)
{
    return ceilf (f);
}

wave_float wave_float_floor (wave_float f)
{
    return floorf (f);
}

wave_float wave_float_min (wave_float a, wave_float b)
{
    return fminf (a, b);
}

wave_float wave_float_max (wave_float a, wave_float b)
{
    return fmaxf (a, b);
}

wave_float wave_float_from_string (const char * str)
{
    return strtof (str, NULL);
}

////////////////////////////////////////////////////////////////////////////////
// wave_char
////////////////////////////////////////////////////////////////////////////////

wave_char wave_char_min (wave_char a, wave_char b)
{
    return a < b ? a : b;
}

wave_char wave_char_max (wave_char a, wave_char b)
{
    return a > b ? a : b;
}

wave_char wave_char_from_wave_int (wave_int code)
{
    return code;
}

wave_int wave_char_code (wave_char c)
{
    return c;
}

////////////////////////////////////////////////////////////////////////////////
// wave_string
////////////////////////////////////////////////////////////////////////////////

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
