/**
 * \file wave_coordinate.h
 * \brief Wave coordinate
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
#ifndef __WAVE_COORDINATE_H__
#define __WAVE_COORDINATE_H__

#include <stdlib.h>
#include <stdio.h>

#include "wave/ast/wave_int_list.h"
#include "wave/ast/wave_queue.h"


/**
 * \defgroup wave_coordinate_group Wave Coordinate
 * \ingroup wave_collection_info_group
 */

////////////////////////////////////////////////////////////////////////////////
// Enums, Structs, Typedefs.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Wave coordinate type.
 * \ingroup wave_coordinate_group
 */
typedef enum wave_coordinate_type
{
    WAVE_COORD_CONSTANT,        /**< Constant. */
    WAVE_COORD_PLUS,            /**< Plus. */
    WAVE_COORD_TIMES,           /**< Times. */
    WAVE_COORD_VAR,             /**< Var. */
    WAVE_COORD_UNKNOWN,         /**< Unknown. */
} wave_coordinate_type;

/**
 * \brief Wave coordinate.
 * \ingroup wave_coordinate_group
 * \warning The setters functions assume the coordinate is clean, if necessary,
 * it is up to the user to properly clean the coordinate before using a setter
 * function.
 *
 * Wave coordinates are used as annotations to the Wave AST. This structure
 * actually is used to represent both the “coordinates” of a collection and its
 * length.
 *
 * The coordinate of a collection usually is computed as the sum of the previous
 * collection's coordinate and length, hence the use of the same structure for
 * coordinates and lengths.
 *
 * # Coordinate creation and destruction
 * Coordinates can be dynamically created using wave_coordinate_alloc(). Such
 * coordinates should be freed using wave_coordinate_free().
 *
 * # Coordinate type
 * ## Existing types
 * A coordinate (or a “length”) can be:
 *
 * Coordinate content               | Corresponding coordinate type
 * ---------------------------------|------------------------------
 * a constant                       | #WAVE_COORD_CONSTANT
 * a variable                       | #WAVE_COORD_VAR
 * the sum of two coordinates       | #WAVE_COORD_PLUS
 * the product of two coordinates   | #WAVE_COORD_TIMES
 * nothing                          | #WAVE_COORD_UNKNOWN
 *
 * ### Constants
 * Constant coordinates represent constant coordinates.
 *
 * ### Variable
 * A “variable” coordinate is used to represent unknown (at compile time) lengths.
 * Internally, it is stored as a list of integers. This list represents the list
 * of the indexes of the collection of interest whithin the AST.
 * For instance, in the following collection:
 *
 *      1;(2;3);4
 *
 * \c 3's index list would be 1,1.
 *
 * ### Sums and products
 * Sum and products of coordinates represent sum and products that cannot be
 * computed yet because at least one of the operands is “variable”. These
 * operands are saved internally as “left” and “right” operands.
 *
 * Note that since addition and multiplication are commutative, there is no
 * special meaning in a coordinate being the left operand rather than the right
 * operand.
 *
 * ### Nothing
 * A coordinate of type #WAVE_COORD_UNKNOWN is a coordinate that has not been used
 * yet (meaning it does not represent any coordinate or length).
 *
 * ## Getting a coordinate's type
 * In order to know a coordinate's type, one must use wave_coordinate_get_type().
 * It is also possible whether a coordinate's type corresponds to a specific type
 * using one of the following functions:
 *
 * Coordinate type          | Test function
 * -------------------------|------------------------------
 * #WAVE_COORD_CONSTANT     | wave_coordinate_is_constant()
 * #WAVE_COORD_VAR          | wave_coordinate_is_var()
 * #WAVE_COORD_PLUS         | wave_coordinate_is_plus()
 * #WAVE_COORD_TIMES        | wave_coordinate_is_times()
 * #WAVE_COORD_UNKNOWN      | wave_coordinate_is_unknown()
 *
 * # Coordinate content access
 * To get a coordinate's content, one can use one of the following functions:
 *
 * Coordinate type                          | Getter function
 * -----------------------------------------|------------------------------
 * #WAVE_COORD_CONSTANT                     | wave_coordinate_get_constant()
 * #WAVE_COORD_VAR                          | wave_coordinate_get_list()
 * #WAVE_COORD_PLUS and #WAVE_COORD_TIMES   | wave_coordinate_get_right()
 * #WAVE_COORD_PLUS and #WAVE_COORD_TIMES   | wave_coordinate_get_left()
 * #WAVE_COORD_UNKNOWN                      | NOTHING
 *
 * One should first determine the coordinate's type before trying to get its
 * content.
 *
 * #WAVE_COORD_PLUS and #WAVE_COORD_TIMES coordinates actually hold two
 * coordinates in order to represent its operands. To get these operands, one
 * can use wave_coordinate_get_right() and wave_coordinate_get_left().
 *
 * # Coordinate modification
 * Coordinates can be modified using one of the following functions:
 * - wave_coordinate_set_constant()
 * - wave_coordinate_set_list()
 * - wave_coordinate_set_plus()
 * - wave_coordinate_set_times()
 *
 * Please note that these functions automatically set the coordinate's type
 * appropriately.
 *
 * When setting a sum or a product, the setters will attempt to “shrink” the
 * result: operations that can already be computed (ie. operations on constants)
 * will be computed.
 *
 * # Coordinate display
 * It is possible to print a coordinate to a stream using wave_coordinate_fprint()
 * or directly to standard output using wave_coordinate_print().
 *
 * \sa wave_int_list
 */
typedef struct wave_coordinate
{
    wave_coordinate_type _type;                 /**< The coordinate's type. */
    union
    {
        int _constant;                          /**< The coordinate's constant. */
        wave_int_list * _var;                   /**< The coordinate's var. */
        struct
        {
            struct wave_coordinate * _left;     /**< Left value. */
            struct wave_coordinate * _right;    /**< Right value. */
        } _binary;                              /**< Binary operands. */
    } _content;                                 /**< Content. */
} wave_coordinate;

////////////////////////////////////////////////////////////////////////////////
// Initialization, clean.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Initialize a wave_coordinate.
 * \param c Coordinate.
 * \relatesalso wave_coordinate
 * \warning \c c must be not \c NULL.
 */
void wave_coordinate_init (wave_coordinate * c);

/**
 * \brief Clean a wave_coordinate.
 * \param c Coordinate.
 * \relatesalso wave_coordinate
 * \warning \c c must be not \c NULL.
 */
void wave_coordinate_clean (wave_coordinate * c);

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

/**
 * \brief Copy a wave_coordinate.
 * \param c Coordinate
 * \relatesalso wave_coordinate
 * \warning \c c must be not \c NULL.
 */
void * wave_coordinate_copy (const wave_coordinate * c);

////////////////////////////////////////////////////////////////////////////////
// Coordinate type information.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Get a wave_coordinate type.
 * \param c Coordinate.
 * \return Type.
 * \relatesalso wave_coordinate
 * \warning \c c must be not \c NULL.
 */
wave_coordinate_type wave_coordinate_get_type (const wave_coordinate * c);

/**
 * \brief Determine whether a wave_coordinate is a constant.
 * \param c Coordinate.
 * \retval true if the coordinate is a constant.
 * \retval false otherwise.
 * \relatesalso wave_coordinate
 * \warning \c c must be not \c NULL.
 */
bool wave_coordinate_is_constant (const wave_coordinate * c);

/**
 * \brief Determine whether a wave_coordinate is a var.
 * \param c Coordinate.
 * \retval true if the coordinate is a var.
 * \retval false otherwise.
 * \relatesalso wave_coordinate
 * \warning \c c must be not \c NULL.
 */
bool wave_coordinate_is_var (const wave_coordinate * c);

/**
 * \brief Determine whether a wave_coordinate is a “plus” (or sum).
 * \param c Coordinate.
 * \retval true if the coordinate is a “plus”.
 * \retval false otherwise.
 * \relatesalso wave_coordinate
 * \warning \c c must be not \c NULL.
 */
bool wave_coordinate_is_plus (const wave_coordinate * c);

/**
 * \brief Determine whether a wave_coordinate is a “times” (or product).
 * \param c Coordinate.
 * \retval true if the coordinate is a “times”.
 * \retval false otherwise.
 * \relatesalso wave_coordinate
 * \warning \c c must be not \c NULL.
 */
bool wave_coordinate_is_times (const wave_coordinate * c);

/**
 * \brief Determine whether a wave_coordinate is unknown.
 * \param c Coordinate.
 * \retval true if the coordinate is unknown.
 * \retval false otherwise.
 * \relatesalso wave_coordinate
 * \warning \c c must be not \c NULL.
 */
bool wave_coordinate_is_unknown (const wave_coordinate * c);

////////////////////////////////////////////////////////////////////////////////
// Getters.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Get a wave_coordinate list.
 * \param c Coordinate.
 * \return List
 * \relatesalso wave_coordinate
 * \warning \c c must be not \c NULL.
 */
wave_int_list * wave_coordinate_get_list (const wave_coordinate * c);

/**
 * \brief Get a wave_coordinate's constant.
 * \param c Coordinate.
 * \return constant.
 * \relatesalso wave_coordinate
 * \warning \c c must be not \c NULL.
 */
int wave_coordinate_get_constant (const wave_coordinate * c);

/**
 * \brief Get a wave_coordinate's left.
 * \param c Coordinate.
 * \return left.
 * \relatesalso wave_coordinate
 * \warning \c c must be not \c NULL.
 */
wave_coordinate * wave_coordinate_get_left (const wave_coordinate * c);

/**
 * \brief Get a wave_coordinate's right.
 * \param c Coordinate.
 * \return right.
 * \relatesalso wave_coordinate
 * \warning \c c must be not \c NULL.
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
 * \warning \c c must be not \c NULL.
 */
void wave_coordinate_set_constant (wave_coordinate * c, int constant);

/**
 * \brief Set a coordinate's list.
 * \param c Coordinate.
 * \param list List.
 * \relatesalso wave_coordinate
 * \warning \c c must be not \c NULL.
 */
void wave_coordinate_set_list (wave_coordinate * c, wave_int_list * list);

/**
 * \brief Set a coordinate's addition left and right operands
 * \param c Coordinate.
 * \param left Left.
 * \param right Right.
 * \relatesalso wave_coordinate
 * \warning \c c must be not \c NULL.
 * \note Since addition is commutative, \c left and \c right can be switched.
 */
void wave_coordinate_set_plus (wave_coordinate * c, wave_coordinate * left, wave_coordinate * right);

/**
 * \brief Set a coordinate's multiplication left and right operands.
 * \param c Coordinate.
 * \param left Left.
 * \param right Right.
 * \relatesalso wave_coordinate
 * \warning \c c must be not \c NULL.
 * \note Since multiplication is commutative, \c left and \c right can be switched.
 */
void wave_coordinate_set_times (wave_coordinate * c, wave_coordinate * left, wave_coordinate * right);

////////////////////////////////////////////////////////////////////////////////
// Printing.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Print wave_coordinate to a stream.
 * \param stream Stream.
 * \param c Coordinate.
 * \warning \c c must be not \c NULL.
 */
void wave_coordinate_fprint (FILE * stream, const wave_coordinate * c);

/**
 * \brief Print wave_coordinate.
 * \param c Coordinate.
 * \warning \c c must be not \c NULL.
 */
void wave_coordinate_print (const wave_coordinate * c);

#endif /* __WAVE_COORDINATE_H__ */
