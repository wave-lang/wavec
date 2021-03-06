/**
 * \file wave_data.c
 * \brief Wave data.
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
#include "wave/common/wave_data.h"

////////////////////////////////////////////////////////////////////////////////
// Static utilities for getters.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Get a wave_char from a data and turn it into a wave_string.
 * \param data Data of interest.
 * \return String composed of the character stored in the data.
 * \warning \c data must be not \c NULL.
 */
static inline wave_string _char_data_to_string (const wave_data * const data)
{
    wave_string s = wave_garbage_alloc (2 * sizeof (wave_char));
    s[0] = wave_data_get_char (data);
    s[1] = '\0';
    return s;
}

////////////////////////////////////////////////////////////////////////////////
// Static utilities for operations.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Determine whether a data holds a constant value.
 * \param t Type of the data.
 * \retval true if the data holds a constant.
 * \retval false otherwise.
 */
static inline bool _is_constant (wave_data_type t)
{
    return t <= WAVE_DATA_BOOL;
}

/**
 * \brief Print an error on type errors (ie. the types of the operands do not fit the
 * operator).
 * \param left Left operand.
 * \param right Right operand.
 * \param op Operator.
 *
 * Pass NULL as the second operator for unary operation type errors.
 */
static inline void _operator_type_error (const wave_data * const left, const wave_data * const right, wave_operator op)
{
    fprintf (stderr, "Error: bad operator use.\noperator: ");
    wave_operator_fprint (stderr, op);
    fprintf (stderr, "\n%soperand: ", right == NULL ? "" : "left ");
    wave_data_fprint (stderr, left);
    if (right != NULL)
    {
        fprintf (stderr, "\nright operand: ");
        wave_data_fprint (stderr, right);
    }
    fprintf (stderr, "\n");
    exit (EX_DATAERR);
}

////////////////////////////////////////////////////////////////////////////////
// Static utilities for operations checking.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Tab of valid operations for wave_int values.
 */
static const wave_operator _int_defined [] =
{
    WAVE_OP_UNARY_PLUS, WAVE_OP_UNARY_MINUS, WAVE_OP_UNARY_INCREMENT,
    WAVE_OP_UNARY_DECREMENT, WAVE_OP_UNARY_SQRT, WAVE_OP_UNARY_SIN,
    WAVE_OP_UNARY_COS, WAVE_OP_UNARY_LOG, WAVE_OP_UNARY_EXP, WAVE_OP_UNARY_CEIL,
    WAVE_OP_UNARY_FLOOR, WAVE_OP_UNARY_CHR,
    WAVE_OP_BINARY_PLUS, WAVE_OP_BINARY_MINUS,
    WAVE_OP_BINARY_MIN, WAVE_OP_BINARY_MAX, WAVE_OP_BINARY_TIMES,
    WAVE_OP_BINARY_DIVIDE, WAVE_OP_BINARY_MOD, WAVE_OP_BINARY_EQUALS,
    WAVE_OP_BINARY_DIFFERS, WAVE_OP_BINARY_LESSER_OR_EQUALS,
    WAVE_OP_BINARY_GREATER_OR_EQUALS, WAVE_OP_BINARY_GREATER,
    WAVE_OP_BINARY_LESSER,
    WAVE_OP_UNKNOWN,
};

/**
 * \brief Tab of valid operations for wave_float values.
 */
static const wave_operator _float_defined [] =
{
    WAVE_OP_UNARY_PLUS, WAVE_OP_UNARY_MINUS, WAVE_OP_UNARY_INCREMENT,
    WAVE_OP_UNARY_DECREMENT, WAVE_OP_UNARY_SQRT, WAVE_OP_UNARY_SIN,
    WAVE_OP_UNARY_COS, WAVE_OP_UNARY_LOG, WAVE_OP_UNARY_EXP, WAVE_OP_UNARY_CEIL,
    WAVE_OP_UNARY_FLOOR, WAVE_OP_BINARY_PLUS, WAVE_OP_BINARY_MINUS,
    WAVE_OP_BINARY_MIN, WAVE_OP_BINARY_MAX, WAVE_OP_BINARY_TIMES,
    WAVE_OP_BINARY_DIVIDE, WAVE_OP_BINARY_MOD, WAVE_OP_BINARY_EQUALS,
    WAVE_OP_BINARY_DIFFERS, WAVE_OP_BINARY_LESSER_OR_EQUALS,
    WAVE_OP_BINARY_GREATER_OR_EQUALS, WAVE_OP_BINARY_GREATER,
    WAVE_OP_BINARY_LESSER,
    WAVE_OP_UNKNOWN,
};

/**
 * \brief Tab of valid operations for wave_char values.
 */
static const wave_operator _char_defined [] =
{
    WAVE_OP_UNARY_CODE,
    WAVE_OP_BINARY_PLUS, WAVE_OP_BINARY_MIN, WAVE_OP_BINARY_MAX,
    WAVE_OP_BINARY_EQUALS, WAVE_OP_BINARY_DIFFERS,
    WAVE_OP_BINARY_LESSER_OR_EQUALS, WAVE_OP_BINARY_GREATER_OR_EQUALS,
    WAVE_OP_BINARY_GREATER, WAVE_OP_BINARY_LESSER,
    WAVE_OP_UNKNOWN,
};

/**
 * \brief Tab of valid operations for wave_string values.
 */
static const wave_operator _string_defined [] =
{
    WAVE_OP_BINARY_PLUS, WAVE_OP_BINARY_MIN, WAVE_OP_BINARY_MAX,
    WAVE_OP_BINARY_EQUALS, WAVE_OP_BINARY_DIFFERS,
    WAVE_OP_BINARY_LESSER_OR_EQUALS, WAVE_OP_BINARY_GREATER_OR_EQUALS,
    WAVE_OP_BINARY_GREATER, WAVE_OP_BINARY_LESSER,
    WAVE_OP_UNKNOWN,
};

/**
 * \brief Tab of valid operations for wave_bool values.
 */
static const wave_operator _bool_defined [] =
{
    WAVE_OP_UNARY_NOT, WAVE_OP_BINARY_AND, WAVE_OP_BINARY_OR,
    WAVE_OP_BINARY_EQUALS, WAVE_OP_BINARY_DIFFERS, WAVE_OP_BINARY_LESSER,
    WAVE_OP_BINARY_GREATER, WAVE_OP_BINARY_LESSER_OR_EQUALS,
    WAVE_OP_BINARY_GREATER_OR_EQUALS,
    WAVE_OP_UNKNOWN,
};

/**
 * \brief Tab of tabs of valid operations.
 */
static const wave_operator * _defined_operators [] =
{
    [WAVE_DATA_INT] = _int_defined,
    [WAVE_DATA_FLOAT] = _float_defined,
    [WAVE_DATA_CHAR] = _char_defined,
    [WAVE_DATA_STRING] = _string_defined,
    [WAVE_DATA_BOOL] = _bool_defined,
    NULL,
};

/**
 * \brief Scan through a WAVE_OP_UNKNOWN terminated tab and search an operation.
 * \param tab Tab.
 * \param op Operation.
 */
static bool _is_defined_tab (const wave_operator tab [], wave_operator op)
{
    bool found = false;
    for (unsigned int i = 0; ! found && tab[i] != WAVE_OP_UNKNOWN; ++i)
        if (tab[i] == op)
            found = true;

    return found;
}

/**
 * \brief Scan through the correct WAVE_OP_UNKNOWN terminated tab and search an operation.
 * \param t Data type.
 * \param op Operation.
 */
static bool _is_defined (wave_data_type t, wave_operator op)
{
    return _is_defined_tab (_defined_operators[t], op);
}

////////////////////////////////////////////////////////////////////////////////
// Static utilities for unary operations.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Tab of existing unary functions of type `wave_int -> wave_int`.
 */
static wave_int (* const _unary_int_to_int []) (wave_int) =
{
    [WAVE_OP_UNARY_PLUS] = wave_int_unary_plus,
    [WAVE_OP_UNARY_MINUS] = wave_int_unary_minus,
    [WAVE_OP_UNARY_INCREMENT] = wave_int_increment,
    [WAVE_OP_UNARY_DECREMENT] = wave_int_decrement,
};

/**
 * \brief Tab of existing unary functions of type `wave_float -> wave_float`.
 */
static wave_float (* const _unary_float_to_float []) (wave_float) =
{
    [WAVE_OP_UNARY_PLUS] = wave_float_unary_plus,
    [WAVE_OP_UNARY_MINUS] = wave_float_unary_minus,
    [WAVE_OP_UNARY_INCREMENT] = wave_float_increment,
    [WAVE_OP_UNARY_DECREMENT] = wave_float_decrement,
    [WAVE_OP_UNARY_SQRT] = wave_float_sqrt,
    [WAVE_OP_UNARY_SIN] = wave_float_sin,
    [WAVE_OP_UNARY_COS] = wave_float_cos,
    [WAVE_OP_UNARY_LOG] = wave_float_log,
    [WAVE_OP_UNARY_EXP] = wave_float_exp,
    [WAVE_OP_UNARY_CEIL] = wave_float_ceil,
    [WAVE_OP_UNARY_FLOOR] = wave_float_floor,
};

/**
 * \brief Tab of existing unary functions of type `wave_int -> wave_float`.
 */
static wave_float (* const _unary_int_to_float []) (wave_int) =
{
    [WAVE_OP_UNARY_SQRT] = wave_int_sqrt,
    [WAVE_OP_UNARY_SIN] = wave_int_sin,
    [WAVE_OP_UNARY_COS] = wave_int_cos,
    [WAVE_OP_UNARY_LOG] = wave_int_log,
    [WAVE_OP_UNARY_EXP] = wave_int_exp,
    [WAVE_OP_UNARY_CEIL] = wave_int_ceil,
    [WAVE_OP_UNARY_FLOOR] = wave_int_floor,
};

/**
 * \brief Map an unary operation on a parallel collection.
 */
static void _map_unary (const wave_data * const operand, wave_data * const result, wave_operator op)
{
    size_t size = operand->_content._collection._size;

    /* Prepare the destination storage for the result. */
    result->_type = WAVE_DATA_PAR;
    result->_content._collection._tab = wave_garbage_alloc (size * sizeof (wave_data));
    result->_content._collection._size = size;

    /* OpenMP requires *signed* integers ?! */
    long long int ll_size = (long long int) size;
    #pragma omp parallel for
        for (long long int i = 0; i < ll_size; ++i)
            wave_data_unary (& operand->_content._collection._tab[i], & result->_content._collection._tab[i], op);
}

/**
 * \brief Computed an unary operation on a constant.
 * \param operand_type Type of the operand.
 * \param operand Operand.
 * \param result Storage for the result.
 * \param op Operation.
 */
static inline void _unary_constant (wave_data_type operand_type, const wave_data * const operand, wave_data * const result, wave_operator op)
{
    /* Reminder: _operator_type_error() exits the program. */
    if (! _is_defined (operand_type, op))
        _operator_type_error (operand, NULL, op);

    if (operand_type == WAVE_DATA_INT)
    {
        wave_int int_value = wave_data_get_int (operand);
        if (op == WAVE_OP_UNARY_PLUS || op == WAVE_OP_UNARY_MINUS
            || op == WAVE_OP_UNARY_INCREMENT || op == WAVE_OP_UNARY_DECREMENT)
            wave_data_set_int (result, _unary_int_to_int[op] (int_value));
        else if (op == WAVE_OP_UNARY_CHR)
            wave_data_set_char (result, wave_int_chr (int_value));
        else
            wave_data_set_float (result, _unary_int_to_float[op] (int_value));
    }
    else if (operand_type == WAVE_DATA_FLOAT)
        wave_data_set_float (result, _unary_float_to_float[op] (wave_data_get_float (operand)));
    else if (operand_type == WAVE_DATA_BOOL)
        wave_data_set_bool (result, wave_bool_not (wave_data_get_bool (operand)));
    else if (operand_type == WAVE_DATA_CHAR)
        wave_data_set_int (result, wave_char_code (wave_data_get_char (operand)));
}

////////////////////////////////////////////////////////////////////////////////
// Static utilities for binary operations.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Tab of binary `(wave_int, wave_int) -> wave_int` functions.
 */
static wave_int (* const _binary_int []) (wave_int, wave_int) =
{
    [WAVE_OP_BINARY_PLUS] = wave_int_binary_plus,
    [WAVE_OP_BINARY_MINUS] = wave_int_binary_minus,
    [WAVE_OP_BINARY_MIN] = wave_int_min,
    [WAVE_OP_BINARY_MAX] = wave_int_max,
    [WAVE_OP_BINARY_TIMES] = wave_int_times,
    [WAVE_OP_BINARY_DIVIDE] = wave_int_divide,
    [WAVE_OP_BINARY_MOD] = wave_int_mod,
};

/**
 * \brief Tab of binary `(wave_int, wave_int) -> wave_bool` functions.
 */
static wave_bool (* const _binary_int_to_bool []) (wave_int, wave_int) =
{
    [WAVE_OP_BINARY_EQUALS] = wave_int_equals,
    [WAVE_OP_BINARY_DIFFERS] = wave_int_differs,
    [WAVE_OP_BINARY_LESSER_OR_EQUALS] = wave_int_lesser_or_equals,
    [WAVE_OP_BINARY_GREATER_OR_EQUALS] = wave_int_greater_or_equals,
    [WAVE_OP_BINARY_GREATER] = wave_int_greater,
    [WAVE_OP_BINARY_LESSER] = wave_int_lesser,
};

/**
 * \brief Tab of binary `(wave_float, wave_float) -> wave_float` functions.
 */
static wave_float (* const _binary_float []) (wave_float, wave_float) =
{
    [WAVE_OP_BINARY_PLUS] = wave_float_binary_plus,
    [WAVE_OP_BINARY_MINUS] = wave_float_binary_minus,
    [WAVE_OP_BINARY_MIN] = wave_float_min,
    [WAVE_OP_BINARY_MAX] = wave_float_max,
    [WAVE_OP_BINARY_TIMES] = wave_float_times,
    [WAVE_OP_BINARY_DIVIDE] = wave_float_divide,
    [WAVE_OP_BINARY_MOD] = wave_float_mod,
};

/**
 * \brief Tab of binary `(wave_float, wave_float) -> wave_bool` functions.
 */
static wave_bool (* const _binary_float_to_bool []) (wave_float, wave_float) =
{
    [WAVE_OP_BINARY_EQUALS] = wave_float_equals,
    [WAVE_OP_BINARY_DIFFERS] = wave_float_differs,
    [WAVE_OP_BINARY_LESSER_OR_EQUALS] = wave_float_lesser_or_equals,
    [WAVE_OP_BINARY_GREATER_OR_EQUALS] = wave_float_greater_or_equals,
    [WAVE_OP_BINARY_GREATER] = wave_float_greater,
    [WAVE_OP_BINARY_LESSER] = wave_float_lesser,
};

/**
 * \brief Tab of binary `(wave_char, wave_char) -> wave_char` functions.
 */
static wave_char (* const _binary_char []) (wave_char, wave_char) =
{
    [WAVE_OP_BINARY_MIN] = wave_char_min,
    [WAVE_OP_BINARY_MAX] = wave_char_max,
};

/**
 * \brief Tab of binary `(wave_float, wave_float) -> wave_bool` functions.
 */
static wave_bool (* const _binary_char_to_bool []) (wave_char, wave_char) =
{
    [WAVE_OP_BINARY_EQUALS] = wave_char_equals,
    [WAVE_OP_BINARY_DIFFERS] = wave_char_differs,
    [WAVE_OP_BINARY_LESSER_OR_EQUALS] = wave_char_lesser_or_equals,
    [WAVE_OP_BINARY_GREATER_OR_EQUALS] = wave_char_greater_or_equals,
    [WAVE_OP_BINARY_GREATER] = wave_char_greater,
    [WAVE_OP_BINARY_LESSER] = wave_char_lesser,
};

/**
 * \brief Tab of binary `(wave_string, wave_string) -> wave_string` functions.
 */
static wave_string (* const _binary_string []) (const_wave_string, const_wave_string) =
{
    [WAVE_OP_BINARY_PLUS] = wave_string_binary_plus,
    [WAVE_OP_BINARY_MIN] = wave_string_min,
    [WAVE_OP_BINARY_MAX] = wave_string_max,
};

/**
 * \brief Tab of binary `(wave_string, wave_string) -> wave_bool` functions.
 */
static wave_bool (* const _binary_string_to_bool []) (const_wave_string, const_wave_string) =
{
    [WAVE_OP_BINARY_EQUALS] = wave_string_equals,
    [WAVE_OP_BINARY_DIFFERS] = wave_string_differs,
    [WAVE_OP_BINARY_LESSER_OR_EQUALS] = wave_string_lesser_or_equals,
    [WAVE_OP_BINARY_GREATER_OR_EQUALS] = wave_string_greater_or_equals,
    [WAVE_OP_BINARY_GREATER] = wave_string_greater,
    [WAVE_OP_BINARY_LESSER] = wave_string_lesser,
};

/**
 * \brief Tab of binary `(wave_bool, wave_bool) -> wave_bool` functions.
 */
static wave_bool (* const _binary_bool []) (wave_bool, wave_bool) =
{
    [WAVE_OP_BINARY_AND] = wave_bool_and,
    [WAVE_OP_BINARY_OR] = wave_bool_or,
};

/**
 * \brief Compute the result of a binary operation on wave_bool values.
 * \param left Left operand.
 * \param right Right operand.
 * \param result Storage for the result.
 * \param op Operation.
 */
static inline void _set_binary_both_bool (const wave_data * const left, const wave_data * const right, wave_data * const result, wave_operator op)
{
    wave_bool left_value = wave_data_get_bool (left);
    wave_bool right_value = wave_data_get_bool (right);
    wave_data_set_bool (result, _binary_bool[op] (left_value, right_value));
}

/**
 * \brief Compute the result of a binary operation on wave_int values.
 * \param left Left operand.
 * \param right Right operand.
 * \param result Storage for the result.
 * \param op Operation.
 */
static inline void _set_binary_both_int (const wave_data * const left, const wave_data * const right, wave_data * const result, wave_operator op)
{
    wave_int left_value = wave_data_get_int (left);
    wave_int right_value = wave_data_get_int (right);
    if (wave_operator_is_test (op))
        wave_data_set_bool (result, _binary_int_to_bool[op] (left_value, right_value));
    else
        wave_data_set_int (result, _binary_int[op] (left_value, right_value));
}

/**
 * \brief Compute the result of a binary operation on wave_float values.
 * \param left Left operand.
 * \param right Right operand.
 * \param result Storage for the result.
 * \param op Operation.
 */
static inline void _set_binary_both_float (const wave_data * const left, const wave_data * const right, wave_data * const result, wave_operator op)
{
    wave_float left_value = wave_data_get_float (left);
    wave_float right_value = wave_data_get_float (right);
    if (wave_operator_is_test (op))
        wave_data_set_bool (result, _binary_float_to_bool[op] (left_value, right_value));
    else
        wave_data_set_float (result, _binary_float[op] (left_value, right_value));
}

/**
 * \brief Compute the result of a binary operation on wave_char values.
 * \param left Left operand.
 * \param right Right operand.
 * \param result Storage for the result.
 * \param op Operation.
 */
static inline void _set_binary_both_char (const wave_data * const left, const wave_data * const right, wave_data * const result, wave_operator op)
{
    wave_char left_value = wave_data_get_char (left);
    wave_char right_value = wave_data_get_char (right);
    if (wave_operator_is_test (op))
        wave_data_set_bool (result, _binary_char_to_bool[op] (left_value, right_value));
    else if (op == WAVE_OP_BINARY_PLUS)
    {
        /* `plus` on wave_char returns a dynaically allocated wave_string ! */
        wave_data_set_string (result, wave_char_binary_plus (left_value, right_value));
        wave_garbage_register (result->_content._string);
    }
    else
        wave_data_set_char (result, _binary_char[op] (left_value, right_value));
}

/**
 * \brief Compute the result of a binary operation on wave_string values.
 * \param left Left operand.
 * \param right Right operand.
 * \param result Storage for the result.
 * \param op Operation.
 */
static inline void _set_binary_both_string (const wave_data * const left, const wave_data * const right, wave_data * const result, wave_operator op)
{
    wave_string left_value = wave_data_get_string (left);
    wave_string right_value = wave_data_get_string (right);
    if (wave_operator_is_test (op))
        wave_data_set_bool (result, _binary_string_to_bool[op] (left_value, right_value));
    else
    {
        /* Beware: binary operations on wave_string values return dynamically
         * allocated wave_string values.
         */
        wave_data_set_string (result, _binary_string[op] (left_value, right_value));
        wave_garbage_register (result->_content._string);
    }
}

/* Tab of functions for binary operations in cases where both operands are of
 * the same type.
 */
static void (* _set_binary_same_types []) (const wave_data *, const wave_data *, wave_data *, wave_operator) =
{
    [WAVE_DATA_BOOL] = _set_binary_both_bool,
    [WAVE_DATA_INT] = _set_binary_both_int,
    [WAVE_DATA_FLOAT] = _set_binary_both_float,
    [WAVE_DATA_CHAR] = _set_binary_both_char,
    [WAVE_DATA_STRING] = _set_binary_both_string,
    [WAVE_DATA_SEQ] = NULL,
    [WAVE_DATA_PAR] = NULL,
    [WAVE_DATA_OPERATOR] = NULL,
    [WAVE_DATA_UNKNOWN] = NULL,
};

/* Operations on mixed operands are accepted for:
 * - wave_int / wave_float
 * - wave_char / wave_string
 */

/**
 * \brief Compute a binary operation on mixed wave_int / wave_float values.
 * \param left Left operand.
 * \param right Right operand.
 * \param result Storage for the result.
 * \param op Operation.
 */
static void _set_binary_int_float (const wave_data * const left, const wave_data * const right, wave_data * const result, wave_operator op)
{
    wave_float left_value = wave_data_get_float (left);
    wave_float right_value = wave_data_get_float (right);
    if (wave_operator_is_test (op))
        wave_data_set_bool (result, _binary_float_to_bool[op] (left_value, right_value));
    else
        wave_data_set_float (result, _binary_float[op] (left_value, right_value));
}

/**
 * \brief Compute a binary operation on mixed wave_char / wave_string values.
 * \param left Left operand.
 * \param right Right operand.
 * \param result Storage for the result.
 * \param op Operation.
 */
static void _set_binary_char_string (const wave_data * const left, const wave_data * const right, wave_data * const result, wave_operator op)
{
    wave_string left_value = wave_data_get_string (left);
    wave_string right_value = wave_data_get_string (right);
    if (wave_operator_is_test (op))
        wave_data_set_bool (result, _binary_string[op] (left_value, right_value));
    else
    {
        wave_data_set_string (result, _binary_string[op] (left_value, right_value));
        wave_garbage_register (result->_content._string);
    }
}

/**
 * \brief Map a binary operation on two parallel collections.
 * \param left Left operand.
 * \param right Right operand.
 * \param result Storage for the result.
 * \param op Operation.
 */
static void _map_binary (const wave_data * const left, const wave_data * const right, wave_data * const result, wave_operator op)
{
    size_t size = left->_content._collection._size;

    /* Prepare the destination storage for the result. */
    result->_type = WAVE_DATA_PAR;
    result->_content._collection._tab = wave_garbage_alloc (size * sizeof (wave_data));
    result->_content._collection._size = size;

    /* Variables for easier processing. */
    const wave_data * const tab_left = left->_content._collection._tab;
    const wave_data * const tab_right = right->_content._collection._tab;
    wave_data * const tab_result = result->_content._collection._tab;

    /* OpenMP requires *signed* integers ?! */
    long long int ll_size = (long long int) size;
    #pragma omp parallel for
        for (long long int i = 0; i < ll_size; ++i)
            wave_data_binary (& tab_left[i], & tab_right[i], & tab_result[i], op);
}

/**
 * \brief Compute a binary operation on constants.
 * \param left_type Type of the left operand.
 * \param right_type Type of the right operand.
 * \param left Left operand.
 * \param right Right operand.
 * \param result Storage for the result.
 * \param op Operator.
 */
static inline void _binary_operation_constants (wave_data_type left_type, wave_data_type right_type, const wave_data * const left, const wave_data * const right, wave_data * const result, wave_operator op)
{
    /* Reminder: _operator_type_error() exits the program. */
    if (! _is_defined (left_type, op) || ! _is_defined (right_type, op))
        _operator_type_error (left, right, op);

    if (left_type == right_type)
        _set_binary_same_types[left_type] (left, right, result, op);
    else if ((left_type == WAVE_DATA_FLOAT && right_type == WAVE_DATA_INT) || (left_type == WAVE_DATA_INT && right_type == WAVE_DATA_FLOAT))
        _set_binary_int_float (left, right, result, op);
    else if ((left_type == WAVE_DATA_CHAR && right_type == WAVE_DATA_STRING) || (left_type == WAVE_DATA_STRING && right_type == WAVE_DATA_CHAR))
        _set_binary_char_string (left, right, result, op);
}

/**
 * \brief Compute a binary operation on parallel collections.
 * \param left_type Type of the left operand.
 * \param right_type Type of the right operand.
 * \param left Left operand.
 * \param right Right operand.
 * \param result Storage for the result.
 * \param op Operator.
 */
static inline void _binary_operation_parallels (const wave_data * const left, const wave_data * const right, wave_data * const result, wave_operator op)
{
    size_t left_size = left->_content._collection._size;
    size_t right_size = right->_content._collection._size;

    if (left_size == right_size)
        _map_binary (left, right, result, op);
    else
        _operator_type_error (left, right, op);
        /* Reminder: _operator_type_error() exits the program. */
}

////////////////////////////////////////////////////////////////////////////////
// Static utilities for printing.
////////////////////////////////////////////////////////////////////////////////
/** \cond Doxygen ignore. */

/**
 * \brief Macro to save the hassle to write the simple printers.
 * \param data_type Data type.
 */
#define _def_data_printer_simple(data_type) \
    static void _data_ ## data_type ## _fprint (FILE * const stream, const wave_data * const data) \
    { \
        wave_ ## data_type ## _fprint (stream, data->_content._ ## data_type); \
    }

/* Create:
 * - _data_int_fprint
 * - _data_float_fprint
 * - _data_bool_fprint
 */
_def_data_printer_simple (int)
_def_data_printer_simple (float)
_def_data_printer_simple (bool)

#undef _def_data_printer_simple

/**
 * \brief Macro to save the hassle to write the char / string printers.
 * \param data_type Data type.
 * \param delimiter Delimiter (most likely single or double quotes).
 */
#define _def_data_printer_char_string(data_type, delimiter) \
    static void _data_ ## data_type ## _fprint (FILE * const stream, const wave_data * const data) \
    { \
        fprintf (stream, "%c", delimiter); \
        wave_ ## data_type ## _fprint (stream, data->_content._ ## data_type); \
        fprintf (stream, "%c", delimiter); \
    }
/*
 * The function will print the data's content while surrounding it with
 * the `delimiter` string.
 */

/* Create:
 * - _data_char_fprint
 * - _data_string_fprint
 */
_def_data_printer_char_string (char, '\'')
_def_data_printer_char_string (string, '\"')

#undef _def_data_printer_char_string

/** \endcond Doxygen ignore. */

/**
 * \brief Print a collection to a stream.
 * \param stream Stream.
 * \param data Data holding the collection of interest.
 * \param separator Delimiter.
 *
 * \c separator will be used to separate the elements of the collection.
 */
static void _data_collection_fprint (FILE * const stream, const wave_data * const data, const char * const separator)
{
    fprintf (stream, "(");
    size_t size = data->_content._collection._size;

    /* Print all elements of the collection, except the last one.
     * (In order to correctly print the separator: the last element does not
     * need a trailing separator.)
     */
    for (size_t i = 0; i < size - 1; ++i)
    {
        wave_data_fprint (stream, & data->_content._collection._tab[i]);
        fprintf (stream, "%s", separator);
    }
    /* Print the last element. */
    wave_data_fprint (stream, & data->_content._collection._tab[size - 1]);

    fprintf (stream, ")");
}

/**
 * \brief Print a sequential collection to a stream.
 * \param stream Stream.
 * \param data Data holding the collection of interest.
 */
static void _data_seq_fprint (FILE * const stream, const wave_data * const data)
{
    _data_collection_fprint (stream, data, ";");
}

/**
 * \brief Print a parallel collection to a stream.
 * \param stream Stream.
 * \param data Data holding the collection of interest.
 */
static void _data_par_fprint (FILE * const stream, const wave_data * const data)
{
    _data_collection_fprint (stream, data, "||");
}

/* Tab of functions used to print a data depending on its type. */
static void (* const _data_print_functions []) (FILE *, const wave_data *) =
{
    [WAVE_DATA_INT] = _data_int_fprint,
    [WAVE_DATA_FLOAT] = _data_float_fprint,
    [WAVE_DATA_CHAR] = _data_char_fprint,
    [WAVE_DATA_STRING] = _data_string_fprint,
    [WAVE_DATA_BOOL] = _data_bool_fprint,
    [WAVE_DATA_SEQ] = _data_seq_fprint,
    [WAVE_DATA_PAR] = _data_par_fprint,
    [WAVE_DATA_OPERATOR] = NULL,
    [WAVE_DATA_UNKNOWN] = NULL,
};

////////////////////////////////////////////////////////////////////////////////
// Getters.
////////////////////////////////////////////////////////////////////////////////

wave_data_type wave_data_get_type (const wave_data * const data)
{
    return data->_type;
}

wave_int wave_data_get_int (const wave_data * const data)
{
    return data->_content._int;
}

wave_float wave_data_get_float (const wave_data * const data)
{
    wave_float f;
    if (wave_data_get_type (data) == WAVE_DATA_INT)
        /* Convert the wave_int to a wave_float. */
        f = wave_float_from_wave_int (wave_data_get_int (data));
    else
        f = data->_content._float;

    return f;
}

wave_char wave_data_get_char (const wave_data * const data)
{
    return data->_content._char;
}

wave_bool wave_data_get_bool (const wave_data * const data)
{
    return data->_content._bool;
}

wave_string wave_data_get_string (const wave_data * const data)
{
    wave_string s;
    if (wave_data_get_type (data) == WAVE_DATA_CHAR)
        s = _char_data_to_string (data);
    else
        s = data->_content._string;

    return s;
}

////////////////////////////////////////////////////////////////////////////////
// Properties.
////////////////////////////////////////////////////////////////////////////////

wave_bool wave_data_is_atom (const wave_data * data)
{
    return data->_type <= WAVE_DATA_BOOL;
}

////////////////////////////////////////////////////////////////////////////////
// Setters.
////////////////////////////////////////////////////////////////////////////////

void wave_data_set_int (wave_data * const data, wave_int i)
{
    data->_type = WAVE_DATA_INT;
    data->_content._int = i;
}

void wave_data_set_float (wave_data * const data, wave_float f)
{
    data->_type = WAVE_DATA_FLOAT;
    data->_content._float = f;
}

void wave_data_set_char (wave_data * const data, wave_char c)
{
    data->_type = WAVE_DATA_CHAR;
    data->_content._char = c;
}

void wave_data_set_bool (wave_data * const data, wave_bool b)
{
    data->_type = WAVE_DATA_BOOL;
    data->_content._bool = b;
}

void wave_data_set_string (wave_data * const data, wave_string s)
{
    data->_type = WAVE_DATA_STRING;
    data->_content._string = s;
}

////////////////////////////////////////////////////////////////////////////////
// Operations.
////////////////////////////////////////////////////////////////////////////////

void wave_data_unary (const wave_data * const operand, wave_data * const result, wave_operator op)
{
    if (op != WAVE_OP_SPECIFIC_ATOM)
    {
        wave_data_type t = wave_data_get_type (operand);
        if (_is_constant (t))
            _unary_constant (t, operand, result, op);
        else if (t == WAVE_DATA_PAR)
            _map_unary (operand, result, op);
        else
            _operator_type_error (operand, NULL, op);
            /* Reminder: _operator_type_error() exits the program. */
    }
    else
        wave_data_set_bool (result, wave_data_is_atom (operand));
}

void wave_data_binary (const wave_data * const left, const wave_data * const right, wave_data * const result, wave_operator op)
{
    wave_data_type left_type = wave_data_get_type (left);
    wave_data_type right_type = wave_data_get_type (right);
    if (_is_constant (left_type) && _is_constant (right_type))
        _binary_operation_constants (left_type, right_type, left, right, result, op);
    else if (left_type == WAVE_DATA_PAR && right_type == WAVE_DATA_PAR)
        _binary_operation_parallels (left, right, result, op);
    else
        _operator_type_error (left, right, op);
        /* Reminder: _operator_type_error() exits the program. */
}

////////////////////////////////////////////////////////////////////////////////
// Printing.
////////////////////////////////////////////////////////////////////////////////

void wave_data_fprint (FILE * const stream, const wave_data * const data)
{
    wave_data_type t = wave_data_get_type (data);
    if (t < WAVE_DATA_UNKNOWN && _data_print_functions[t] != NULL)
        _data_print_functions[t] (stream, data);
}
