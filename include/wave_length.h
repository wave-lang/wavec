/**
 * \file wave_length.h
 * \brief Wave length.
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
#ifndef __WAVE_LENGTH_H__
#define __WAVE_LENGTH_H__

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "wave_int_list.h"

////////////////////////////////////////////////////////////////////////////////
// Enums, Structs, Typedefs.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Wave length type.
 */
typedef enum wave_length_type
{
    WAVE_LENGTH_CONSTANT,       /**<- Constant. */
    WAVE_LENGTH_VAR,            /**<- Var. */
    WAVE_LENGTH_UNKNOWN,        /**<- Unknown. */
} wave_length_type;

/**
 * \brief Wave length
 */
typedef struct wave_length
{
    wave_length_type _type;     /**<- Wave length type. */
    union
    {
        int _constant;          /**<- Constant. */
        wave_int_list _var;     /**<- Var. */
    }
} wave_length;

////////////////////////////////////////////////////////////////////////////////
// Allocation, free.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Allocation for wave_length.
 * \relatesalso wave_length
 * \return pointer to a wave_length.
 */
void * wave_length_alloc (void);

/**
 * \brief Free a wave_length.
 * \param l Length.
 * \relatesalso wave_length
 */
void wave_length_free (wave_length * l);

////////////////////////////////////////////////////////////////////////////////
// Getters.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Get a wave_length type.
 * \param l Length.
 * \return Length type.
 * \relatesalso wave_length
 */
wave_length_type wave_length_get_type (const wave_length * l);

/**
 * \brief Get wave_length constant.
 * \param l Length.
 * \return Constant.
 * \relatesalso wave_length
 */
int wave_length_get_constant (const wave_length * l);

/**
 * \brief Get a wave_length var.
 * \param l Length.
 * \return var
 * \relatesalso wave_length
 */
wave_int_list * wave_length_get_list (const wave_length * l);

////////////////////////////////////////////////////////////////////////////////
// Setters.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Set a wave_length constant.
 * \param l Length.
 * \param c Constant.
 * \relatesalso wave_length
 */
void wave_length_set_constant (wave_length * l, int c);

/**
 * \brief Set a wave_length list.
 * \param l Length.
 * \param list List.
 * \relatesalso wave_length
 */
void wave_length_set_list (wave_length * l, wave_int_list * list);

#endif /* __WAVE_LENGTH_H__ */
