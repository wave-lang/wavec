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

static const char * const _operator_enum_strings[] =
{
    [WAVE_OP_UNARY_PLUS              ] = "WAVE_OP_UNARY_PLUS",
    [WAVE_OP_UNARY_MINUS             ] = "WAVE_OP_UNARY_MINUS",
    [WAVE_OP_UNARY_INCREMENT         ] = "WAVE_OP_UNARY_INCREMENT",
    [WAVE_OP_UNARY_DECREMENT         ] = "WAVE_OP_UNARY_DECREMENT",
    [WAVE_OP_UNARY_SQRT              ] = "WAVE_OP_UNARY_SQRT",
    [WAVE_OP_UNARY_SIN               ] = "WAVE_OP_UNARY_SIN",
    [WAVE_OP_UNARY_COS               ] = "WAVE_OP_UNARY_COS",
    [WAVE_OP_UNARY_NOT               ] = "WAVE_OP_UNARY_NOT",
    [WAVE_OP_UNARY_LOG               ] = "WAVE_OP_UNARY_LOG",
    [WAVE_OP_UNARY_EXP               ] = "WAVE_OP_UNARY_EXP",
    [WAVE_OP_UNARY_CEIL              ] = "WAVE_OP_UNARY_CEIL",
    [WAVE_OP_UNARY_FLOOR             ] = "WAVE_OP_UNARY_FLOOR",
    [WAVE_OP_BINARY_PLUS             ] = "WAVE_OP_BINARY_PLUS",
    [WAVE_OP_BINARY_MINUS            ] = "WAVE_OP_BINARY_MINUS",
    [WAVE_OP_BINARY_MIN              ] = "WAVE_OP_BINARY_MIN",
    [WAVE_OP_BINARY_MAX              ] = "WAVE_OP_BINARY_MAX",
    [WAVE_OP_BINARY_TIMES            ] = "WAVE_OP_BINARY_TIMES",
    [WAVE_OP_BINARY_DIVIDE           ] = "WAVE_OP_BINARY_DIVIDE",
    [WAVE_OP_BINARY_MOD              ] = "WAVE_OP_BINARY_MOD",
    [WAVE_OP_BINARY_EQUALS           ] = "WAVE_OP_BINARY_EQUALS",
    [WAVE_OP_BINARY_DIFFERS          ] = "WAVE_OP_BINARY_DIFFERS",
    [WAVE_OP_BINARY_LESSER_OR_EQUALS ] = "WAVE_OP_BINARY_LESSER_OR_EQUALS",
    [WAVE_OP_BINARY_GREATER_OR_EQUALS] = "WAVE_OP_BINARY_GREATER_OR_EQUALS",
    [WAVE_OP_BINARY_GREATER          ] = "WAVE_OP_BINARY_GREATER",
    [WAVE_OP_BINARY_LESSER           ] = "WAVE_OP_BINARY_LESSER",
    [WAVE_OP_BINARY_AND              ] = "WAVE_OP_BINARY_AND",
    [WAVE_OP_BINARY_OR               ] = "WAVE_OP_BINARY_OR",
    [WAVE_OP_BINARY_GET              ] = "WAVE_OP_BINARY_GET",
    [WAVE_OP_SPECIFIC_ATOM           ] = "WAVE_OP_SPECIFIC_ATOM",
    [WAVE_OP_SPECIFIC_STOP           ] = "WAVE_OP_SPECIFIC_STOP",
    [WAVE_OP_SPECIFIC_CUT            ] = "WAVE_OP_SPECIFIC_CUT",
    [WAVE_OP_SPECIFIC_READ           ] = "WAVE_OP_SPECIFIC_READ",
    [WAVE_OP_SPECIFIC_PRINT          ] = "WAVE_OP_SPECIFIC_PRINT",
    [WAVE_OP_UNKNOWN                 ] = "WAVE_OP_UNKNOWN",
};

static const char * const _operator_functions_strings[] =
{
    [WAVE_OP_UNARY_PLUS              ] = "unary_plus",
    [WAVE_OP_UNARY_MINUS             ] = "unary_minus",
    [WAVE_OP_UNARY_INCREMENT         ] = "increment",
    [WAVE_OP_UNARY_DECREMENT         ] = "decrement",
    [WAVE_OP_UNARY_SQRT              ] = "sqrt",
    [WAVE_OP_UNARY_SIN               ] = "sin",
    [WAVE_OP_UNARY_COS               ] = "cos",
    [WAVE_OP_UNARY_NOT               ] = "not",
    [WAVE_OP_UNARY_LOG               ] = "log",
    [WAVE_OP_UNARY_EXP               ] = "exp",
    [WAVE_OP_UNARY_CEIL              ] = "ceil",
    [WAVE_OP_UNARY_FLOOR             ] = "floor",
    [WAVE_OP_BINARY_PLUS             ] = "binary_plus",
    [WAVE_OP_BINARY_MINUS            ] = "binary_minus",
    [WAVE_OP_BINARY_MIN              ] = "min",
    [WAVE_OP_BINARY_MAX              ] = "max",
    [WAVE_OP_BINARY_TIMES            ] = "times",
    [WAVE_OP_BINARY_DIVIDE           ] = "divide",
    [WAVE_OP_BINARY_MOD              ] = "mod",
    [WAVE_OP_BINARY_EQUALS           ] = "equals",
    [WAVE_OP_BINARY_DIFFERS          ] = "differs",
    [WAVE_OP_BINARY_LESSER_OR_EQUALS ] = "lesser_or_equals",
    [WAVE_OP_BINARY_GREATER_OR_EQUALS] = "greater_or_equals",
    [WAVE_OP_BINARY_GREATER          ] = "greater",
    [WAVE_OP_BINARY_LESSER           ] = "lesser",
    [WAVE_OP_BINARY_AND              ] = "and",
    [WAVE_OP_BINARY_OR               ] = "or",
    [WAVE_OP_BINARY_GET              ] = "binary_get",
    [WAVE_OP_SPECIFIC_ATOM           ] = "specific_atom",
    [WAVE_OP_SPECIFIC_STOP           ] = "specific_stop",
    [WAVE_OP_SPECIFIC_CUT            ] = "specific_cut",
    [WAVE_OP_SPECIFIC_READ           ] = "specific_read",
    [WAVE_OP_SPECIFIC_PRINT          ] = "specific_print",
    [WAVE_OP_UNKNOWN                 ] = "unknown",
};

static inline void _type_error (FILE * code_file)
{
    wave_code_generate_error (code_file, "trying to use an operator on non valid types.", "EX_DATAERR");
}

static inline void _operand_error (FILE * code_file)
{
    wave_code_generate_error (code_file, "no operand supplied to the operator.", "EX_DATAERR");
}

static inline void _print_tab_minus (FILE * code_file, const wave_int_list * list, const wave_coordinate * c, int shift)
{
    wave_coordinate * minus = wave_coordinate_alloc ();
    wave_coordinate_set_constant  (minus, shift);
    wave_coordinate * shifted = wave_coordinate_alloc ();
    wave_coordinate * copy = wave_coordinate_copy (c);
    wave_coordinate_set_plus (shifted, minus, copy);
    wave_code_generation_fprint_tab_with_init(code_file, list, shifted, "");
    wave_coordinate_free (shifted);
}

static void _print_register_string (FILE * code_file, const wave_int_list * indexes, const wave_coordinate * c)
{
    fprintf (code_file, "wave_garbage_register (");
    wave_generate_content_assignement (code_file, indexes, c, WAVE_ATOM_LITERAL_STRING);
    fprintf (code_file, ");\n");
}

static inline void _print_operator_prelude (FILE * code_file, const wave_int_list * list, const wave_coordinate * c, wave_atom_type t, wave_operator op)
{
    wave_generate_type_assignement (code_file, list, c, t);
    wave_generate_content_assignement (code_file, list, c, t);
    fprintf (code_file, " = wave_%s_%s", wave_generation_atom_type_string (t), _operator_functions_strings[op]);
}

static inline void _print_arg (FILE * code_file, const wave_int_list * list, const wave_coordinate * c, wave_atom_type t, int shift)
{
    _print_tab_minus (code_file, list, c, shift);
    fprintf (code_file, "._content._%s", wave_generation_atom_type_string (t));
}

static void _print_unary (FILE * code_file, const wave_int_list * list, const wave_coordinate * c, wave_atom_type t, wave_operator op)
{
    _print_operator_prelude (code_file, list, c, t, op);
    fprintf (code_file, " (");
    _print_arg (code_file, list, c, t, -1);
    fprintf (code_file, ");\n");
}

static void _print_args_binary (FILE * code_file, const wave_int_list * list, const wave_coordinate * c, wave_atom_type left, wave_atom_type right)
{
    _print_arg (code_file, list, c, left, -2);
    fprintf (code_file, ", ");
    _print_arg (code_file, list, c, right, -1);
    fprintf (code_file, ");\n");
}

static void _print_binary (FILE * code_file, const wave_int_list * list, const wave_coordinate * c, wave_atom_type destination, wave_atom_type left, wave_atom_type right, wave_operator op)
{
    _print_operator_prelude (code_file, list, c, destination, op);
    fprintf (code_file, " (");
    _print_args_binary (code_file, list, c, left, right);
    if (destination == WAVE_ATOM_LITERAL_STRING)
        _print_register_string (code_file, list, c);
}

static void _print_binary_char_string (FILE * code_file, const wave_int_list * list, const wave_coordinate * c, wave_atom_type destination, wave_atom_type left, wave_atom_type right, wave_operator op)
{
    _print_operator_prelude (code_file, list, c, destination, op);
    fprintf (code_file, "_char_%s", left == WAVE_ATOM_LITERAL_CHAR ? "left" : "right");
    fprintf (code_file, " (");
    _print_args_binary (code_file, list, c, left, right);
    if (destination == WAVE_ATOM_LITERAL_STRING)
        _print_register_string (code_file, list, c);
}

static void _int_float_for_unary (FILE * code_file, const wave_coordinate * c, wave_atom_type t, wave_int_list * indexes, wave_operator op)
{
    if (t == WAVE_ATOM_LITERAL_INT || t == WAVE_ATOM_LITERAL_FLOAT)
        _print_unary (code_file, indexes, c, t, op);
    else
        _type_error (code_file);
}

static void _bool (FILE * code_file, const wave_coordinate * c, wave_atom_type t, wave_int_list * indexes, wave_operator op)
{
    if (t == WAVE_ATOM_LITERAL_BOOL)
        _print_unary (code_file, indexes, c, t, op);
    else
        _type_error (code_file);
}

static void _print_dynamic_unary (FILE * code_file, wave_int_list * indexes, wave_coordinate * c, wave_operator op)
{
    fprintf (code_file, "wave_data_unary (& ");
    _print_tab_minus (code_file, indexes, c, -1);
    fprintf (code_file, ", & ");
    wave_code_generation_fprint_tab_with_init(code_file, indexes, c, "");
    fprintf (code_file, ", %s);\n", _operator_enum_strings[op]);
}

static void _print_dynamic_binary (FILE * code_file, wave_int_list * indexes, wave_coordinate * c, wave_operator op)
{
    fprintf (code_file, "wave_data_binary (& ");
    _print_tab_minus (code_file, indexes, c, -2);
    fprintf (code_file, ", & ");
    _print_tab_minus (code_file, indexes, c, -1);
    fprintf (code_file, ", & ");
    wave_code_generation_fprint_tab_with_init(code_file, indexes, c, "");
    fprintf (code_file, ", %s);\n", _operator_enum_strings[op]);
}

static void _unary (FILE * code_file, const wave_collection * collection, wave_operator op, void (* fun) (FILE *, const wave_coordinate *, wave_atom_type, wave_int_list *, wave_operator))
{
    if (wave_collection_has_previous (collection))
    {
        wave_collection * previous = wave_collection_get_previous (collection);
        wave_collection_type tc = wave_collection_get_type (previous);
        wave_int_list * indexes = wave_collection_get_full_indexes (wave_collection_get_parent(collection));
        wave_coordinate * c = wave_collection_get_coordinate (collection);
        if (tc == WAVE_COLLECTION_ATOM)
        {
            wave_atom * a = wave_collection_get_atom (previous);
            wave_atom_type ta = wave_atom_get_type (a);
            if (ta == WAVE_ATOM_OPERATOR || ta == WAVE_ATOM_PATH)
                _print_dynamic_unary (code_file, indexes, c, op);
            else
                fun (code_file, c, ta, indexes, op);
        }
        else if (tc == WAVE_COLLECTION_PAR)
            _print_dynamic_unary (code_file, indexes, c, op);
        else
            _type_error (code_file);
        wave_int_list_free (indexes);
    }
    else
        _operand_error (code_file);
}

static void _int_float_for_binary (FILE * code_file, const wave_coordinate * c, wave_atom_type left, wave_atom_type right, wave_int_list * indexes, wave_operator op)
{
    if (left == right)
    {
        if (left == WAVE_ATOM_LITERAL_INT)
            _print_binary (code_file, indexes, c, left, left, right, op);
        else if (left == WAVE_ATOM_LITERAL_FLOAT)
            _print_binary (code_file, indexes, c, left, left, right, op);
        else
            _type_error (code_file);
    }
    else
    {
        if (left == WAVE_ATOM_LITERAL_INT && right == WAVE_ATOM_LITERAL_FLOAT)
            _print_binary (code_file, indexes, c, WAVE_ATOM_LITERAL_FLOAT, left, right, op);
        else if (left == WAVE_ATOM_LITERAL_FLOAT && right == WAVE_ATOM_LITERAL_INT)
            _print_binary (code_file, indexes, c, WAVE_ATOM_LITERAL_FLOAT, left, right, op);
        else
            _type_error (code_file);
    }
}

static void _all_for_binary (FILE * code_file, const wave_coordinate * c, wave_atom_type left, wave_atom_type right, wave_int_list * indexes, wave_operator op)
{
    if (left == right)
        _print_binary (code_file, indexes, c, left, left, right, op);
    else
    {
        if ((left == WAVE_ATOM_LITERAL_INT && right == WAVE_ATOM_LITERAL_FLOAT)
            || (left == WAVE_ATOM_LITERAL_FLOAT && right == WAVE_ATOM_LITERAL_INT))
            _print_binary (code_file, indexes, c, WAVE_ATOM_LITERAL_FLOAT, left, right, op);
        else if ((left == WAVE_ATOM_LITERAL_CHAR && right == WAVE_ATOM_LITERAL_STRING)
            || (left == WAVE_ATOM_LITERAL_STRING && right == WAVE_ATOM_LITERAL_CHAR))
            _print_binary_char_string (code_file, indexes, c, WAVE_ATOM_LITERAL_STRING, left, right, op);
        else
            _type_error (code_file);
    }
}

static void _print_char_plus (FILE * code_file, const wave_int_list * indexes, const wave_coordinate * c)
{
    wave_generate_type_assignement (code_file, indexes, c, WAVE_ATOM_LITERAL_STRING);
    wave_generate_content_assignement (code_file, indexes, c, WAVE_ATOM_LITERAL_STRING);
    fprintf (code_file, " = wave_%s_%s", wave_generation_atom_type_string (WAVE_ATOM_LITERAL_CHAR), _operator_functions_strings[WAVE_OP_BINARY_PLUS]);
    fprintf (code_file, " (");
    _print_args_binary (code_file, indexes, c, WAVE_ATOM_LITERAL_CHAR, WAVE_ATOM_LITERAL_CHAR);
    _print_register_string (code_file, indexes, c);

}

static void _plus_for_binary (FILE * code_file, const wave_coordinate * c, wave_atom_type left, wave_atom_type right, wave_int_list * indexes, wave_operator op)
{
    if (left != WAVE_ATOM_LITERAL_BOOL && right != WAVE_ATOM_LITERAL_BOOL)
    {
        if (left == right)
        {
            if (left == WAVE_ATOM_LITERAL_CHAR)
                _print_char_plus (code_file, indexes, c);
            else
                _print_binary (code_file, indexes, c, left, left, right, op);
        }
        else
        {
            if ((left == WAVE_ATOM_LITERAL_INT && right == WAVE_ATOM_LITERAL_FLOAT)
                || (left == WAVE_ATOM_LITERAL_FLOAT && right == WAVE_ATOM_LITERAL_INT))
                _print_binary (code_file, indexes, c, WAVE_ATOM_LITERAL_FLOAT, left, right, op);
            else if ((left == WAVE_ATOM_LITERAL_CHAR && right == WAVE_ATOM_LITERAL_STRING)
                || (left == WAVE_ATOM_LITERAL_STRING && right == WAVE_ATOM_LITERAL_CHAR))
                _print_binary_char_string (code_file, indexes, c, WAVE_ATOM_LITERAL_STRING, left, right, op);
            else
                _type_error (code_file);
        }
    }
    else
        _type_error (code_file);
}

static void _bool_for_binary (FILE * code_file, const wave_coordinate * c, wave_atom_type left, wave_atom_type right, wave_int_list * indexes, wave_operator op)
{
    if (left == WAVE_ATOM_LITERAL_BOOL && right == WAVE_ATOM_LITERAL_BOOL)
        _print_binary (code_file, indexes, c, left, left, right, op);
    else
        _type_error (code_file);
}

static void _binary (FILE * code_file, const wave_collection * collection, wave_operator op, void (* fun) (FILE *, const wave_coordinate *, wave_atom_type,  wave_atom_type, wave_int_list *, wave_operator))
{
    if (wave_collection_has_previous (collection) && wave_collection_has_previous (wave_collection_get_previous (collection)))
    {
        wave_collection * right = wave_collection_get_previous (collection);
        wave_collection * left = wave_collection_get_previous (right);
        wave_collection_type tc_right = wave_collection_get_type (right);
        wave_collection_type tc_left = wave_collection_get_type (left);
        wave_coordinate * c = wave_collection_get_coordinate (collection);
        wave_int_list * indexes = wave_collection_get_full_indexes (wave_collection_get_parent(collection));
        if (tc_right == WAVE_COLLECTION_ATOM && tc_left == WAVE_COLLECTION_ATOM)
        {
            wave_atom * a_right = wave_collection_get_atom (right);
            wave_atom * a_left = wave_collection_get_atom (left);
            wave_atom_type ta_right = wave_atom_get_type (a_right);
            wave_atom_type ta_left = wave_atom_get_type (a_left);
            if (ta_left == WAVE_ATOM_PATH || ta_left == WAVE_ATOM_OPERATOR
                || ta_right == WAVE_ATOM_PATH || ta_right == WAVE_ATOM_OPERATOR)
                _print_dynamic_binary (code_file, indexes, c, op);
            else
                fun (code_file, c, ta_left, ta_right, indexes, op);
        }
        else if (tc_left == tc_right && tc_left == WAVE_COLLECTION_PAR)
            _print_dynamic_binary (code_file, indexes, c, op);
        else if (tc_right == WAVE_COLLECTION_ATOM && tc_left == WAVE_COLLECTION_PAR)
        {
            wave_atom * a = wave_collection_get_atom (right);
            wave_atom_type ta = wave_atom_get_type (a);
            if (ta == WAVE_ATOM_PATH || ta == WAVE_ATOM_OPERATOR)
                _print_dynamic_binary (code_file, indexes, c, op);
            else
                _type_error (code_file);
        }
        else if (tc_left == WAVE_COLLECTION_ATOM && tc_right == WAVE_COLLECTION_PAR)
        {
            wave_atom * a = wave_collection_get_atom (left);
            wave_atom_type ta = wave_atom_get_type (a);
            if (ta == WAVE_ATOM_PATH || ta == WAVE_ATOM_OPERATOR)
                _print_dynamic_binary (code_file, indexes, c, op);
            else
                _type_error (code_file);
        }
        else
            _type_error (code_file);
        wave_int_list_free (indexes);
    }
    else
        _operand_error (code_file);
}

#define _def_operator_function(function_name, generic_function) \
    static void function_name (FILE * code_file, const wave_collection * collection, wave_operator op) \
    { \
        generic_function (code_file, collection, op); \
    }

static inline void _unary_int_float (FILE * code_file, const wave_collection * collection, wave_operator op)
{
    _unary (code_file, collection, op, _int_float_for_unary);
}

static inline void _binary_int_float (FILE * code_file, const wave_collection * collection, wave_operator op)
{
    _binary (code_file, collection, op, _int_float_for_binary);
}

static inline void _binary_all (FILE * code_file, const wave_collection * collection, wave_operator op)
{
    _binary (code_file, collection, op, _all_for_binary);
}

static inline void _binary_bool (FILE * code_file, const wave_collection * collection, wave_operator op)
{
    _binary (code_file, collection, op, _bool_for_binary);
}

_def_operator_function (_unary_plus, _unary_int_float)
_def_operator_function (_unary_minus, _unary_int_float)
_def_operator_function (_unary_increment, _unary_int_float)
_def_operator_function (_unary_decrement, _unary_int_float)
_def_operator_function (_unary_sqrt, _unary_int_float)
_def_operator_function (_unary_sin, _unary_int_float)
_def_operator_function (_unary_cos, _unary_int_float)
_def_operator_function (_unary_log, _unary_int_float)
_def_operator_function (_unary_exp, _unary_int_float)
_def_operator_function (_unary_ceil, _unary_int_float)
_def_operator_function (_unary_floor, _unary_int_float)

static void _unary_not (FILE * code_file, const wave_collection * collection, wave_operator op)
{
    _unary (code_file, collection, op, _bool);
}

_def_operator_function (_binary_minus, _binary_int_float)
_def_operator_function (_binary_times, _binary_int_float)
_def_operator_function (_binary_divide, _binary_int_float)
_def_operator_function (_binary_mod, _binary_int_float)

_def_operator_function (_binary_min, _binary_all)
_def_operator_function (_binary_max, _binary_all)
_def_operator_function (_binary_equals, _binary_all)
_def_operator_function (_binary_differs, _binary_all)
_def_operator_function (_binary_lesser_or_equals, _binary_all)
_def_operator_function (_binary_greater_or_equals, _binary_all)
_def_operator_function (_binary_greater, _binary_all)
_def_operator_function (_binary_lesser, _binary_all)

_def_operator_function (_binary_and, _binary_bool)
_def_operator_function (_binary_or, _binary_bool)

static void _binary_plus (FILE * code_file, const wave_collection * collection, wave_operator op)
{
    _binary (code_file, collection, op, _plus_for_binary);
}

static void _unknown_error (FILE * code_file, const wave_collection * collection, wave_operator op)
{
    (void) collection; (void) op;
    wave_code_generate_error_unknown (code_file);
}

#undef _def_operator_function

static void _specific_print (FILE * const code_file, const wave_collection * const collection, wave_operator op)
{
    (void) op;

    if (wave_collection_has_previous (collection))
    {
        wave_int_list * indexes = wave_collection_get_full_indexes (wave_collection_get_parent(collection));
        wave_coordinate * c = wave_collection_get_coordinate (collection);
        fprintf (code_file, "wave_data_fprint (stdout, & ");
        _print_tab_minus (code_file, indexes, c, -1);
        fprintf (code_file, ");\nprintf(\"\\n\");\n");
        wave_int_list_free (indexes);
    }
    else
        _operand_error (code_file);
}

static void (* const _operator_functions[]) (FILE *, const wave_collection *, wave_operator) =
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
    [WAVE_OP_BINARY_PLUS]               = _binary_plus,
    [WAVE_OP_BINARY_MINUS]              = _binary_minus,
    [WAVE_OP_BINARY_MIN]                = _binary_min,
    [WAVE_OP_BINARY_MAX]                = _binary_max,
    [WAVE_OP_BINARY_TIMES]              = _binary_times,
    [WAVE_OP_BINARY_DIVIDE]             = _binary_divide,
    [WAVE_OP_BINARY_MOD]                = _binary_mod,
    [WAVE_OP_BINARY_EQUALS]             = _binary_equals,
    [WAVE_OP_BINARY_DIFFERS]            = _binary_differs,
    [WAVE_OP_BINARY_LESSER_OR_EQUALS]   = _binary_lesser_or_equals,
    [WAVE_OP_BINARY_GREATER_OR_EQUALS]  = _binary_greater_or_equals,
    [WAVE_OP_BINARY_GREATER]            = _binary_greater,
    [WAVE_OP_BINARY_LESSER]             = _binary_lesser,
    [WAVE_OP_BINARY_AND]                = _binary_and,
    [WAVE_OP_BINARY_OR]                 = _binary_or,
    [WAVE_OP_BINARY_GET]                = NULL,
    [WAVE_OP_SPECIFIC_ATOM]             = NULL,
    [WAVE_OP_SPECIFIC_STOP]             = NULL,
    [WAVE_OP_SPECIFIC_CUT]              = NULL,
    [WAVE_OP_SPECIFIC_READ]             = NULL,
    [WAVE_OP_SPECIFIC_PRINT]            = _specific_print,
    [WAVE_OP_UNKNOWN]                   = _unknown_error,
};

void wave_code_generation_fprint_operator (FILE * code_file, const wave_collection * collection)
{
    /* We already know the current collection is an atom containing an operator */
    wave_atom * atom = wave_collection_get_atom (collection);
    wave_operator op = wave_atom_get_operator (atom);
    if (op >= 0 && op < WAVE_OP_UNKNOWN && _operator_functions[op] != NULL)
        _operator_functions[op] (code_file, collection, op);
}
