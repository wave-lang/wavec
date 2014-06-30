/**
 * \file wave_generation_operators.c
 * \brief Wave code generation for operators.
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
#include "wave/generation/wave_generation_operators.h"

static void _print_tab_minus (FILE * code_file, const wave_int_list * list, const wave_coordinate * c, int shift)
{
    wave_coordinate * minus = wave_coordinate_alloc ();
    wave_coordinate_set_constant  (minus, shift);
    wave_coordinate * shifted = wave_coordinate_alloc ();
    wave_coordinate * copy = wave_coordinate_copy (c);
    wave_coordinate_set_plus (shifted, minus, copy);
    wave_code_generation_fprint_tab_with_init(code_file, list, shifted, "");
    wave_coordinate_free (shifted);
}

static inline void _print_operator_prelude (FILE * code_file, const wave_int_list * list, const wave_coordinate * c, wave_atom_type t, const char * type_string, const char * op)
{
    wave_generate_type_assignement (code_file, list, c, t);
    wave_generate_content_assignement (code_file, list, c, t);
    fprintf (code_file, " = wave_%s_%s (", type_string, op);
}

static inline void _print_arg (FILE * code_file, const wave_int_list * list, const wave_coordinate * c, wave_atom_type t, int shift)
{
    _print_tab_minus (code_file, list, c, shift);
    fprintf (code_file, "._content.%s", wave_generation_atom_type_string (t));
}

static void _print_unary (FILE * code_file, const wave_int_list * list, const wave_coordinate * c, wave_atom_type t, const char * type_string, const char * op)
{
    _print_operator_prelude (code_file, list, c, t, type_string, op);
    _print_arg (code_file, list, c, t, -1);
    fprintf (code_file, ");\n");
}

static void _print_binary (FILE * code_file, const wave_int_list * list, const wave_coordinate * c, wave_atom_type destination, wave_atom_type left, wave_atom_type right, const char * type_string, const char * op)
{
    _print_operator_prelude (code_file, list, c, destination, type_string, op);
    _print_arg (code_file, list, c, left, -2);
    fprintf (code_file, ", ");
    _print_arg (code_file, list, c, right, -1);
    fprintf (code_file, ");\n");
}

static void _int_float_for_unary (FILE * code_file, const wave_coordinate * c, wave_atom_type t, wave_int_list * indexes, const char * op)
{
    if (t == WAVE_ATOM_LITERAL_INT)
        _print_unary (code_file, indexes, c, t, "int", op);
    else if (t == WAVE_ATOM_LITERAL_FLOAT)
        _print_unary (code_file, indexes, c, t, "float", op);
    else
    {
        fprintf (stderr, "Error: trying to use an operator on non valid types.\n");
        exit (1);
    }
}

static void _bool (FILE * code_file, const wave_coordinate * c, wave_atom_type t, wave_int_list * indexes, const char * op)
{
    if (t == WAVE_ATOM_LITERAL_BOOL)
        _print_unary (code_file, indexes, c, t, "bool", op);
    else
    {
        fprintf (stderr, "Error: trying to use a boolean operator on a non boolean value.\n");
        exit (1);
    }
}

static void _unary (FILE * code_file, const wave_collection * collection, const char * op, void (* fun) (FILE *, const wave_coordinate *, wave_atom_type, wave_int_list *, const char *))
{
    if (wave_collection_has_previous (collection))
    {
        wave_collection * previous = wave_collection_get_previous (collection);
        wave_collection_type tc = wave_collection_get_type (previous);
        if (tc == WAVE_COLLECTION_ATOM)
        {
            wave_atom * a = wave_collection_get_atom (previous);
            wave_atom_type ta = wave_atom_get_type (a);
            wave_int_list * indexes = wave_collection_get_full_indexes (wave_collection_get_parent(collection));
            wave_coordinate * c = wave_collection_get_coordinate (collection);
            fun (code_file, c, ta, indexes, op);
        }
    }
    else
    {
        fprintf (stderr, "Error: no operand supplied to the operator.\n");
        exit (1);
    }
}

static void _int_float_for_binary (FILE * code_file, const wave_coordinate * c, wave_atom_type left, wave_atom_type right, wave_int_list * indexes, const char * op)
{
    if (left == right)
    {
        if (left == WAVE_ATOM_LITERAL_INT)
            _print_binary (code_file, indexes, c, left, left, right, "int", op);
        else if (left == WAVE_ATOM_LITERAL_FLOAT)
            _print_binary (code_file, indexes, c, left, left, right, "float", op);
        else
        {
            fprintf (stderr, "Error: trying to use an operator on non valid types.\n");
            exit (1);
        }
    }
    else
    {
        if (left == WAVE_ATOM_LITERAL_INT && right == WAVE_ATOM_LITERAL_FLOAT)
            _print_binary (code_file, indexes, c, WAVE_ATOM_LITERAL_FLOAT, left, right, "float", op);
        else if (left == WAVE_ATOM_LITERAL_FLOAT && right == WAVE_ATOM_LITERAL_INT)
            _print_binary (code_file, indexes, c, WAVE_ATOM_LITERAL_FLOAT, left, right, "float", op);
        else
        {
            fprintf (stderr, "Error: trying to use an operator on non valid types.\n");
            exit (1);
        }
    }
}

static void _binary (FILE * code_file, const wave_collection * collection, const char * op, void (* fun) (FILE *, const wave_coordinate *, wave_atom_type,  wave_atom_type, wave_int_list *, const char *))
{
    if (wave_collection_has_previous (collection) && wave_collection_has_previous (wave_collection_get_previous (collection)))
    {
        wave_collection * right = wave_collection_get_previous (collection);
        wave_collection * left = wave_collection_get_previous (right);
        wave_collection_type tc_right = wave_collection_get_type (right);
        wave_collection_type tc_left = wave_collection_get_type (left);
        if (tc_right == WAVE_COLLECTION_ATOM && tc_left == WAVE_COLLECTION_ATOM)
        {
            wave_atom * a_right = wave_collection_get_atom (right);
            wave_atom * a_left = wave_collection_get_atom (left);
            wave_atom_type ta_right = wave_atom_get_type (a_right);
            wave_atom_type ta_left = wave_atom_get_type (a_left);
            wave_int_list * indexes = wave_collection_get_full_indexes (wave_collection_get_parent(collection));
            wave_coordinate * c = wave_collection_get_coordinate (collection);
            fun (code_file, c, ta_left, ta_right, indexes, op);
        }
    }
    else
    {
        fprintf (stderr, "Error: no operand supplied to the operator.\n");
        exit (1);
    }
}

static void _unary_int_float (FILE * code_file, const wave_collection * collection, const char * op)
{
    _unary (code_file, collection, op, _int_float_for_unary);
}

static void _unary_plus (FILE * code_file, const wave_collection * collection)
{
    _unary_int_float (code_file, collection, "unary_plus");
}

static void _unary_minus (FILE * code_file, const wave_collection * collection)
{
    _unary_int_float (code_file, collection, "unary_minus");
}

static void _unary_increment (FILE * code_file, const wave_collection * collection)
{
    _unary_int_float (code_file, collection, "increment");
}

static void _unary_decrement (FILE * code_file, const wave_collection * collection)
{
    _unary_int_float (code_file, collection, "decrement");
}

static void _unary_sqrt (FILE * code_file, const wave_collection * collection)
{
    _unary_int_float (code_file, collection, "sqrt");
}

static void _unary_sin (FILE * code_file, const wave_collection * collection)
{
    _unary_int_float (code_file, collection, "sin");
}

static void _unary_cos (FILE * code_file, const wave_collection * collection)
{
    _unary_int_float (code_file, collection, "cos");
}

static void _unary_log (FILE * code_file, const wave_collection * collection)
{
    _unary_int_float (code_file, collection, "log");
}

static void _unary_exp (FILE * code_file, const wave_collection * collection)
{
    _unary_int_float (code_file, collection, "exp");
}

static void _unary_ceil (FILE * code_file, const wave_collection * collection)
{
    _unary_int_float (code_file, collection, "ceil");
}

static void _unary_floor (FILE * code_file, const wave_collection * collection)
{
    _unary_int_float (code_file, collection, "floor");
}

static void _unary_not (FILE * code_file, const wave_collection * collection)
{
    _unary (code_file, collection, "not", _bool);
}

static void _binary_int_float (FILE * code_file, const wave_collection * collection, const char * op)
{
    _binary (code_file, collection, op, _int_float_for_binary);
}

static void _binary_minus (FILE * code_file, const wave_collection * collection)
{
    _binary_int_float (code_file, collection, "binary_minus");
}

static void _binary_times (FILE * code_file, const wave_collection * collection)
{
    _binary_int_float (code_file, collection, "times");
}

static void _binary_divide (FILE * code_file, const wave_collection * collection)
{
    _binary_int_float (code_file, collection, "divide");
}

static void (* const _operator_functions[]) (FILE *, const wave_collection *) =
{
    [WAVE_OP_UNARY_PLUS]                = _unary_plus,
    [WAVE_OP_UNARY_MINUS]               = _unary_minus,
    [WAVE_OP_UNARY_INCREMENT]           = _unary_increment,
    [WAVE_OP_UNARY_DECREMENT]           = _unary_decrement,
    [WAVE_OP_UNARY_SQRT]                = _unary_sqrt,
    [WAVE_OP_UNARY_SIN]                 = _unary_sin,
    [WAVE_OP_UNARY_COS]                 = _unary_cos,
    [WAVE_OP_UNARY_NOT]                 = _unary_not,
    [WAVE_OP_UNARY_LOG]                 = _unary_log,
    [WAVE_OP_UNARY_EXP]                 = _unary_exp,
    [WAVE_OP_UNARY_CEIL]                = _unary_ceil,
    [WAVE_OP_UNARY_FLOOR]               = _unary_floor,
    [WAVE_OP_BINARY_PLUS]               = NULL,
    [WAVE_OP_BINARY_MINUS]              = _binary_minus,
    [WAVE_OP_BINARY_MIN]                = NULL,
    [WAVE_OP_BINARY_MAX]                = NULL,
    [WAVE_OP_BINARY_TIMES]              = _binary_times,
    [WAVE_OP_BINARY_DIVIDE]             = _binary_divide,
    [WAVE_OP_BINARY_MOD]                = NULL,
    [WAVE_OP_BINARY_EQUALS]             = NULL,
    [WAVE_OP_BINARY_DIFFERS]            = NULL,
    [WAVE_OP_BINARY_LESSER_OR_EQUALS]   = NULL,
    [WAVE_OP_BINARY_GREATER_OR_EQUALS]  = NULL,
    [WAVE_OP_BINARY_GREATER]            = NULL,
    [WAVE_OP_BINARY_LESSER]             = NULL,
    [WAVE_OP_BINARY_AND]                = NULL,
    [WAVE_OP_BINARY_OR]                 = NULL,
    [WAVE_OP_BINARY_GET]                = NULL,
    [WAVE_OP_SPECIFIC_ATOM]             = NULL,
    [WAVE_OP_SPECIFIC_STOP]             = NULL,
    [WAVE_OP_SPECIFIC_CUT]              = NULL,
    [WAVE_OP_SPECIFIC_READ]             = NULL,
    [WAVE_OP_SPECIFIC_PRINT]            = NULL,
    [WAVE_OP_UNKNOWN]                   = NULL,
};

void wave_code_generation_fprint_operator (FILE * code_file, const wave_collection * collection)
{
    wave_atom * a = wave_collection_get_atom (collection);
    wave_operator o = wave_atom_get_operator (a);
    if (o >= 0 && o < WAVE_OP_UNKNOWN)
        if (_operator_functions[o] != NULL)
            _operator_functions[o] (code_file, collection);
}
