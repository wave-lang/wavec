/**
 * \file wave_struct_def.c
 * \brief Wave struct def.
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
#include "wave/common/wave_struct_def.h"

wave_data_type wave_data_get_type (const wave_data * data)
{
    return data->_type;
}

void wave_data_set_int (wave_data * data, wave_int i)
{
    data->_type = WAVE_DATA_INT;
    data->_content._int = i;
}

void wave_data_set_float (wave_data * data, wave_float f)
{
    data->_type = WAVE_DATA_FLOAT;
    data->_content._float = f;
}

void wave_data_set_char (wave_data * data, wave_char c)
{
    data->_type = WAVE_DATA_CHAR;
    data->_content._char = c;
}

void wave_data_set_bool (wave_data * data, wave_bool b)
{
    data->_type = WAVE_DATA_BOOL;
    data->_content._bool = b;
}

void wave_data_set_string (wave_data * data, wave_string s)
{
    data->_type = WAVE_DATA_STRING;
    data->_content._string = s;
}

static wave_int (* const _unary_int_to_int []) (wave_int) =
{
    [WAVE_OP_UNARY_PLUS] = wave_int_unary_plus,
    [WAVE_OP_UNARY_MINUS] = wave_int_unary_minus,
    [WAVE_OP_UNARY_INCREMENT] = wave_int_increment,
    [WAVE_OP_UNARY_DECREMENT] = wave_int_decrement,
};

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

static wave_operator _int_defined [] =
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

static wave_operator _float_defined [] =
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

static wave_operator _char_defined [] =
{
    WAVE_OP_BINARY_PLUS, WAVE_OP_BINARY_MIN, WAVE_OP_BINARY_MAX,
    WAVE_OP_BINARY_EQUALS, WAVE_OP_BINARY_DIFFERS,
    WAVE_OP_BINARY_LESSER_OR_EQUALS, WAVE_OP_BINARY_GREATER_OR_EQUALS,
    WAVE_OP_BINARY_GREATER, WAVE_OP_BINARY_LESSER,
    WAVE_OP_UNKNOWN,
};

static wave_operator _string_defined [] =
{
    WAVE_OP_BINARY_PLUS, WAVE_OP_BINARY_MIN, WAVE_OP_BINARY_MAX,
    WAVE_OP_BINARY_EQUALS, WAVE_OP_BINARY_DIFFERS,
    WAVE_OP_BINARY_LESSER_OR_EQUALS, WAVE_OP_BINARY_GREATER_OR_EQUALS,
    WAVE_OP_BINARY_GREATER, WAVE_OP_BINARY_LESSER,
    WAVE_OP_UNKNOWN,
};


static wave_operator _bool_defined [] =
{
    WAVE_OP_UNARY_NOT, WAVE_OP_BINARY_AND, WAVE_OP_BINARY_OR,
    WAVE_OP_UNKNOWN,
};

static bool _is_defined_tab (wave_operator tab [], wave_operator op)
{
    bool found = false;
    for (unsigned int i = 0; ! found && tab[i] != WAVE_OP_UNKNOWN; ++i)
        if (tab[i] == op)
            found = true;

    return found;
}

static wave_operator * _defined_operators [] =
{
    [WAVE_DATA_INT] = _int_defined,
    [WAVE_DATA_FLOAT] = _float_defined,
    [WAVE_DATA_CHAR] = _char_defined,
    [WAVE_DATA_STRING] = _string_defined,
    [WAVE_DATA_BOOL] = _bool_defined,
    NULL,
};

static bool _is_defined (wave_data_type t, wave_operator op)
{
    return _is_defined_tab (_defined_operators[t], op);
}

void wave_data_unary (const wave_data * operand, wave_data * result, wave_operator op)
{
    wave_data_type t = wave_data_get_type (operand);
    if (! _is_defined (t, op))
    {
        fprintf (stderr, "Error, trying to use an operator on the wrong type.\n");
        exit (EX_DATAERR);
    }

    if (t == WAVE_DATA_INT)
    {
        if (op == WAVE_OP_UNARY_PLUS || op == WAVE_OP_UNARY_MINUS
            || op == WAVE_OP_UNARY_INCREMENT || op == WAVE_OP_UNARY_DECREMENT)
            wave_data_set_int (result, _unary_int_to_int[op] (operand->_content._int));
        else
            wave_data_set_float (result, _unary_int_to_float[op] (operand->_content._int));
    }
    else if (t == WAVE_DATA_FLOAT)
    {
        wave_data_set_float (result, _unary_float_to_float[op] (operand->_content._float));
    }
}

void wave_data_binary (const wave_data * left, const wave_data * right, wave_data * result, wave_operator op)
{
    (void) left; (void) right; (void) result; (void) op;
}
