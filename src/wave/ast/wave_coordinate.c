/**
 * \file wave_coordinate.c
 * \brief Wave coordinate
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
#include "wave/ast/wave_coordinate.h"

void wave_coordinate_init (wave_coordinate * c)
{
    c->_type = WAVE_COORD_UNKNOWN;
    c->_content._binary._left = NULL;
    c->_content._binary._right = NULL;
}

static inline void _wave_coordinate_free_binary (wave_coordinate * const c)
{
    wave_coordinate_free (c->_content._binary._left);
    wave_coordinate_free (c->_content._binary._right);
}

static inline void _wave_coordinate_free_var (wave_coordinate * const c)
{
    wave_int_list_free (c->_content._var);
}

void wave_coordinate_clean (wave_coordinate * const c)
{
    if (c->_type == WAVE_COORD_PLUS || c->_type == WAVE_COORD_TIMES)
        _wave_coordinate_free_binary (c);
    else if (c->_type == WAVE_COORD_VAR)
        _wave_coordinate_free_var (c);
}

////////////////////////////////////////////////////////////////////////////////
// Allocation, free.
////////////////////////////////////////////////////////////////////////////////

void * wave_coordinate_alloc (void)
{
    wave_coordinate * c = malloc (sizeof * c);
    if (c != NULL)
        wave_coordinate_init (c);

    return c;
}

void wave_coordinate_free (wave_coordinate * const c)
{
    if (c != NULL)
    {
        wave_coordinate_clean (c);
        free (c);
    }
}

static inline void _wave_coordinate_copy_binary (wave_coordinate * const destination, const wave_coordinate * const source)
{
    destination->_content._binary._left = wave_coordinate_copy (source->_content._binary._left);
    destination->_content._binary._right = wave_coordinate_copy (source->_content._binary._right);

}

static inline void _wave_coordinate_copy_var (wave_coordinate * destination, const wave_coordinate * const source)
{
    destination->_content._var = wave_int_list_copy (source->_content._var);
}

void * wave_coordinate_copy (const wave_coordinate * const c)
{
    wave_coordinate * copy = wave_coordinate_alloc ();
    * copy = * c;
    if (c->_type == WAVE_COORD_PLUS || c->_type == WAVE_COORD_TIMES)
        _wave_coordinate_copy_binary (copy, c);
    else if (c->_type == WAVE_COORD_VAR)
        _wave_coordinate_copy_var (copy, c);

    return copy;
}
////////////////////////////////////////////////////////////////////////////////
// Getters.
////////////////////////////////////////////////////////////////////////////////

wave_coordinate_type wave_coordinate_get_type (const wave_coordinate * const c)
{
    return c->_type;
}

wave_int_list * wave_coordinate_get_list (const wave_coordinate * const c)
{
    return c->_content._var;
}

int wave_coordinate_get_constant (const wave_coordinate * const c)
{
    return c->_content._constant;
}

wave_coordinate * wave_coordinate_get_left (const wave_coordinate * const c)
{
    return c->_content._binary._left;
}

wave_coordinate * wave_coordinate_get_right (const wave_coordinate * const c)
{
    return c->_content._binary._right;
}

////////////////////////////////////////////////////////////////////////////////
// Setters.
////////////////////////////////////////////////////////////////////////////////

static inline void _wave_coordinate_set_type (wave_coordinate * const c, wave_coordinate_type t)
{
    c->_type = t;
}

void wave_coordinate_set_constant (wave_coordinate * const c, int constant)
{
    _wave_coordinate_set_type (c, WAVE_COORD_CONSTANT);
    c->_content._constant = constant;
}

void wave_coordinate_set_list (wave_coordinate * const c, wave_int_list * const list)
{
    _wave_coordinate_set_type (c, WAVE_COORD_VAR);
    c->_content._var = list;
}

void wave_coordinate_set_plus_left (wave_coordinate * const c, wave_coordinate * const left)
{
    _wave_coordinate_set_type (c, WAVE_COORD_PLUS);
    c->_content._binary._left = left;
}

void wave_coordinate_set_plus_right (wave_coordinate * c, wave_coordinate * right)
{
    _wave_coordinate_set_type (c, WAVE_COORD_PLUS);
    c->_content._binary._right = right;
}

void wave_coordinate_set_times_left (wave_coordinate * c, wave_coordinate * left)
{
    _wave_coordinate_set_type (c, WAVE_COORD_TIMES);
    c->_content._binary._left = left;
}

void wave_coordinate_set_times_right (wave_coordinate * c, wave_coordinate * right)
{
        _wave_coordinate_set_type (c, WAVE_COORD_TIMES);
    c->_content._binary._right = right;
}

static inline bool _both_are_constants (const wave_coordinate * left, const wave_coordinate * right)
{
    wave_coordinate_type t_left = wave_coordinate_get_type (left);
    wave_coordinate_type t_right = wave_coordinate_get_type (right);

    return t_left == WAVE_COORD_CONSTANT && t_right == WAVE_COORD_CONSTANT;
}

/* Should be called only for t == WAVE_COORD_PLUS or t == WAVE_COORD_TIMES ! */
static inline int _compute_constant (wave_coordinate * left, wave_coordinate * right, wave_coordinate_type t)
{
    int left_value = wave_coordinate_get_constant (left);
    int right_value = wave_coordinate_get_constant (right);

    return t == WAVE_COORD_PLUS ? left_value + right_value : left_value * right_value;
}

static inline void _compute_set_and_free (wave_coordinate * c, wave_coordinate * left, wave_coordinate * right, wave_coordinate_type t)
{
    int constant = _compute_constant (left, right, t);
    wave_coordinate_set_constant (c, constant);
    wave_coordinate_free (left);
    wave_coordinate_free (right);
}

static inline void _set_left_and_right (wave_coordinate * c, wave_coordinate * left, wave_coordinate * right, wave_coordinate_type t)
{
    _wave_coordinate_set_type (c, t);
    c->_content._binary._left = left;
    c->_content._binary._right = right;
}

static inline void _wave_coordinate_set_binary (wave_coordinate * c, wave_coordinate * left, wave_coordinate * right, wave_coordinate_type t)
{
    if (_both_are_constants (left, right))
        _compute_set_and_free (c, left, right, t);
    else
        _set_left_and_right (c, left, right, t);
}

void wave_coordinate_set_plus_left_and_right (wave_coordinate * c, wave_coordinate * left, wave_coordinate * right)
{
    _wave_coordinate_set_binary (c, left, right, WAVE_COORD_PLUS);
}

void wave_coordinate_set_times_left_and_right (wave_coordinate * c, wave_coordinate * left, wave_coordinate * right)
{
    _wave_coordinate_set_binary (c, left, right, WAVE_COORD_TIMES);
}

////////////////////////////////////////////////////////////////////////////////
// Printing.
////////////////////////////////////////////////////////////////////////////////

void _wave_coordinate_constant_fprint (FILE * stream, const wave_coordinate * c)
{
    fprintf (stream, "%d", wave_coordinate_get_constant (c));
}

void _wave_coordinate_var_fprint (FILE * stream, const wave_coordinate * c)
{
    fprintf (stream, "var");
    wave_int_list * list = wave_coordinate_get_list (c);
    for (wave_int_list_element * e = list->_first; e != NULL; e = e->_next_element)
        fprintf (stream, "%d", e->_content);
}

static const char _plus_symbol = '+';
static const char _times_symbol = '*';
static const char _opening_parenthesis ='(';
static const char _closing_parenthesis =')';

void _wave_coordinate_times_fprint (FILE * stream, const wave_coordinate * c)
{
    fprintf (stream, "%c", _opening_parenthesis);
    wave_coordinate_fprint (stream, wave_coordinate_get_left (c));
    fprintf (stream, "%c %c %c", _opening_parenthesis, _times_symbol, _closing_parenthesis);
    wave_coordinate_fprint (stream, wave_coordinate_get_right (c));
    fprintf (stream, "%c", _closing_parenthesis);
}

void _wave_coordinate_plus_fprint (FILE * stream, const wave_coordinate * c)
{
    wave_coordinate_fprint (stream, wave_coordinate_get_left (c));
    fprintf (stream, " %c ", _plus_symbol);
    wave_coordinate_fprint (stream, wave_coordinate_get_right (c));
}

static void (* _wave_coordinate_fprint_functions []) (FILE *, const wave_coordinate *) =
{
    [WAVE_COORD_CONSTANT] = _wave_coordinate_constant_fprint,
    [WAVE_COORD_VAR] = _wave_coordinate_var_fprint,
    [WAVE_COORD_TIMES] = _wave_coordinate_times_fprint,
    [WAVE_COORD_PLUS] = _wave_coordinate_plus_fprint,
    [WAVE_COORD_UNKNOWN] = NULL,
};

void wave_coordinate_fprint (FILE * stream, const wave_coordinate * c)
{
    wave_coordinate_type t = wave_coordinate_get_type (c);
    if (t >= 0 && t < WAVE_COORD_UNKNOWN)
        _wave_coordinate_fprint_functions [t] (stream, c);
}

void wave_coordinate_print (const wave_coordinate * c)
{
    wave_coordinate_fprint (stdout, c);
}
