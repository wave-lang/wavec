/**
 * \file wave_coordinate.h
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
#ifndef __WAVE_COORDINATE_H__
#define __WAVE_COORDINATE_H__

#include "wave_int_list.h"

////////////////////////////////////////////////////////////////////////////////
// Enums, Structs, Typedefs.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Wave coordinate type.
 */
typedef enum wave_coordinate_type
{
    WAVE_COORD_CONSTANT,        /**<- Constant. */
    WAVE_COORD_PLUS,            /**<- Plus. */
    WAVE_COORD_VAR,             /**<- Var. */
    WAVE_COORD_UNKNOWN,         /**<- Unknown. */
} wave_coordinate_type;

/**
 * \brief Wave coordinate.
 */
typedef struct wave_coordinate
{
    wave_coordinate_type _type;                 /**<- Type. */
    union
    {
        int _constant;                          /**<- Constant. */
        wave_int_list _var;                     /**<- Var. */
        struct
        {
            struct wave_coordinate * _left;     /**<- Plus left value. */
            struct wave_coordinate * _right;    /**<- Plus right value. */
        } _plus;                                /**<- Plus. */
    } _content;                                 /**<- Content. */
} wave_coordinate;

////////////////////////////////////////////////////////////////////////////////
// Allocation, free.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Allocation for wave_coordinate
 * \return pointer to a wave_coordinate
 * \relatesalso wave_coordinate
 */
void * wave_coordinate_alloc (void);

/**
 * \brief Free a wave_coordinate
 * \param c Coordinate
 * \relatesalso wave_coordinate
 */
void wave_coordinate_free (wave_coordinate * c);

////////////////////////////////////////////////////////////////////////////////
// Getters.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Get a wave_coordinate type.
 * \param c Coordinate.
 * \return Type.
 * \relatesalso wave_coordinate
 */
wave_coordinate_type wave_coordinate_get_type (const wave_coordinate * c);

/**
 * \brief Get a wave_coordinate list.
 * \param c Coordinate.
 * \return List
 * \relatesalso wave_coordinate
 */
wave_int_list * wave_coordinate_get_list (const wave_coordinate * c);

/**
 * \brief Get a wave_coordinate's constant.
 * \param c Coordinate.
 * \return constant.
 * \relatesalso wave_coordinate
 */
int wave_coordinate_get_constant (const wave_coordinate * c);

/**
 * \brief Get a wave_coordinate's left.
 * \param c Coordinate.
 * \return left.
 * \relatesalso wave_coordinate
 */
wave_coordinate * wave_coordinate_get_left (const wave_coordinate * c);

/**
 * \brief Get a wave_coordinate's right.
 * \param c Coordinate.
 * \return right.
 * \relatesalso wave_coordinate
 */
wave_coordinate * wave_coordinate_get_right (const wave_coordinate * c);

////////////////////////////////////////////////////////////////////////////////
// Setters.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Set a coordinate's constant.
 * \param c Coordinate.
 * \param constant Constant.
 * \relatesalso wave_coordinate
 */
void wave_coordinate_set_constant (wave_coordinate * c, int constant);

/**
 * \brief Set a coordinate's list.
 * \param c Coordinate.
 * \param list List.
 * \relatesalso wave_coordinate
 */
void wave_coordinate_set_list (wave_coordinate * c, const wave_int_list * list);

/**
 * \brief Set a coordinate's left.
 * \param c Coordinate.
 * \param left Left.
 * \relatesalso wave_coordinate
 */
void wave_coordinate_set_left (wave_coordinate * c, wave_coordinate * left);

/**
 * \brief Set a coordinate's right.
 * \param c Coordinate.
 * \param right Right.
 * \relatesalso wave_coordinate
 */
void wave_coordinate_set_right (wave_coordinate * c, wave_coordinate * right);

#endif /* __WAVE_COORDINATE_H__ */
