/**
 * \file wave_operator.h
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
#ifndef __WAVE_OPERATOR_H__
#define __WAVE_OPERATOR_H__

#include <stdlib.h>
#include <stdio.h>

/**
 * \brief Wave operators.
 * \ingroup wave_ast_group
 */
typedef enum wave_operator
{
    WAVE_OP_UNARY_PLUS = 0,             /**< Unary plus. */
    WAVE_OP_UNARY_MINUS,                /**< Unary minus. */
    WAVE_OP_UNARY_INCREMENT,            /**< Increment. */
    WAVE_OP_UNARY_DECREMENT,            /**< Decrement. */
    WAVE_OP_UNARY_SQRT,                 /**< Square root. */
    WAVE_OP_UNARY_SIN,                  /**< Sinus. */
    WAVE_OP_UNARY_COS,                  /**< Cosinus. */
    WAVE_OP_UNARY_NOT,                  /**< Not. */
    WAVE_OP_UNARY_LOG,                  /**< Logarithm. */
    WAVE_OP_UNARY_EXP,                  /**< Exponential. */
    WAVE_OP_UNARY_CEIL,                 /**< Ceilling. */
    WAVE_OP_UNARY_FLOOR,                /**< Floor. */
    WAVE_OP_UNARY_CHR,                  /**< Chr. */
    WAVE_OP_UNARY_CODE,                 /**< Code. */
    WAVE_OP_BINARY_PLUS,                /**< Binary plus. */
    WAVE_OP_BINARY_MINUS,               /**< Binary minus. */
    WAVE_OP_BINARY_MIN,                 /**< Minimum. */
    WAVE_OP_BINARY_MAX,                 /**< Maximum. */
    WAVE_OP_BINARY_TIMES,               /**< Times. */
    WAVE_OP_BINARY_DIVIDE,              /**< Divide. */
    WAVE_OP_BINARY_MOD,                 /**< Mod. */
    WAVE_OP_BINARY_EQUALS,              /**< Equals. */
    WAVE_OP_BINARY_DIFFERS,             /**< Differs. */
    WAVE_OP_BINARY_LESSER_OR_EQUALS,    /**< Lesser than or equals. */
    WAVE_OP_BINARY_GREATER_OR_EQUALS,   /**< Greater than or equals. */
    WAVE_OP_BINARY_GREATER,             /**< Greater than. */
    WAVE_OP_BINARY_LESSER,              /**< Lesser than. */
    WAVE_OP_BINARY_AND,                 /**< And. */
    WAVE_OP_BINARY_OR,                  /**< Or. */
    WAVE_OP_BINARY_GET,                 /**< Get. */
    WAVE_OP_SPECIFIC_ATOM,              /**< Atom. */
    WAVE_OP_SPECIFIC_STOP,              /**< Stop. */
    WAVE_OP_SPECIFIC_CUT,               /**< Cut. */
    WAVE_OP_SPECIFIC_READ,              /**< Read. */
    WAVE_OP_SPECIFIC_PRINT,             /**< Print. */
    WAVE_OP_UNKNOWN,                    /**< Unknown. */
} wave_operator;

////////////////////////////////////////////////////////////////////////////////
// Printing.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Print a wave_operator to a stream.
 * \param stream Stream.
 * \param op Operator.
 */
void wave_operator_fprint (FILE * stream, wave_operator op);

/**
 * \brief Print a wave_operator to \c stdout.
 * \param op Operator.
 */
void wave_operator_print (wave_operator op);

#endif /* __WAVE_OPERATOR_H__ */
