/**
 * \file wave_operator.c
 * \brief Wave operators.
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
#include "wave/common/wave_operator.h"

////////////////////////////////////////////////////////////////////////////////
// Static utilities.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Strings for the operators.
 */
static char * _operator_characters[] =
{
    [WAVE_OP_UNARY_PLUS] = "~+",
    [WAVE_OP_UNARY_MINUS] = "~-",
    [WAVE_OP_UNARY_INCREMENT] = "++",
    [WAVE_OP_UNARY_DECREMENT] = "--",
    [WAVE_OP_UNARY_SQRT] = "sqrt",
    [WAVE_OP_UNARY_SIN] = "sin",
    [WAVE_OP_UNARY_COS] = "cos",
    [WAVE_OP_UNARY_NOT] = "not",
    [WAVE_OP_UNARY_LOG] = "log",
    [WAVE_OP_UNARY_EXP] = "exp",
    [WAVE_OP_UNARY_CEIL] = "ceil",
    [WAVE_OP_UNARY_FLOOR] = "floor",
    [WAVE_OP_UNARY_CHR] = "chr",
    [WAVE_OP_UNARY_CODE] = "code",
    [WAVE_OP_BINARY_PLUS] = "+",
    [WAVE_OP_BINARY_MINUS] = "-",
    [WAVE_OP_BINARY_MIN] = "min",
    [WAVE_OP_BINARY_MAX] = "max",
    [WAVE_OP_BINARY_TIMES] = "*",
    [WAVE_OP_BINARY_DIVIDE] = "/",
    [WAVE_OP_BINARY_MOD] = "mod",
    [WAVE_OP_BINARY_EQUALS] = "=",
    [WAVE_OP_BINARY_DIFFERS] = "<>",
    [WAVE_OP_BINARY_LESSER_OR_EQUALS] = "<=",
    [WAVE_OP_BINARY_GREATER_OR_EQUALS] = ">=",
    [WAVE_OP_BINARY_GREATER] = ">",
    [WAVE_OP_BINARY_LESSER] = "<",
    [WAVE_OP_BINARY_AND] = "and",
    [WAVE_OP_BINARY_OR] = "or",
    [WAVE_OP_BINARY_GET] = "get",
    [WAVE_OP_SPECIFIC_ATOM] = "atom",
    [WAVE_OP_SPECIFIC_STOP] = "?",
    [WAVE_OP_SPECIFIC_CUT] = "!",
    [WAVE_OP_SPECIFIC_READ] = "read",
    [WAVE_OP_SPECIFIC_PRINT] = "print",
    [WAVE_OP_UNKNOWN] = "",
};

////////////////////////////////////////////////////////////////////////////////
// Category testing.
////////////////////////////////////////////////////////////////////////////////

bool wave_operator_is_test (wave_operator op)
{
    return op >= WAVE_OP_BINARY_EQUALS && op <= WAVE_OP_BINARY_LESSER;
}

bool wave_operator_is_unary (wave_operator op)
{
    return op >= WAVE_OP_UNARY_PLUS && op <= WAVE_OP_UNARY_CODE;
}

bool wave_operator_is_binary (wave_operator op)
{
    return op >= WAVE_OP_BINARY_PLUS && op <= WAVE_OP_BINARY_GET;
}

bool wave_operator_is_specific (wave_operator op)
{
    return op >= WAVE_OP_SPECIFIC_ATOM && op <= WAVE_OP_SPECIFIC_PRINT;
}

////////////////////////////////////////////////////////////////////////////////
// Printing.
////////////////////////////////////////////////////////////////////////////////

void wave_operator_fprint (FILE * stream, wave_operator op)
{
    if (op >= WAVE_OP_UNKNOWN || op < 0)
        fprintf (stream, "%s", _operator_characters[WAVE_OP_UNKNOWN]);
    else
        fprintf (stream, "%s", _operator_characters[op]);
}

void wave_operator_print (wave_operator op)
{
    wave_operator_fprint (stdout, op);
}
