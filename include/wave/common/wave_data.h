/**
 * \file wave_data.h
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
#ifndef __WAVE_DATA_H__
#define __WAVE_DATA_H__

#include "sysexits.h"

#include "wave/common/wave_types.h"
#include "wave/common/wave_operator.h"
#include "wave/common/wave_garbage.h"

////////////////////////////////////////////////////////////////////////////////
// Enums, Structs, Typedefs.
////////////////////////////////////////////////////////////////////////////////

/**
 * \class wave_data_type
 * \brief Used inside the \c wave_data structure to know wich data is being stored inside.
 * \sa wave_types_group
 */
typedef enum wave_data_type
{
    WAVE_DATA_INT = 0,          /**< An integer value */
    WAVE_DATA_FLOAT,            /**< A floating point value */
    WAVE_DATA_CHAR,             /**< A character value */
    WAVE_DATA_STRING,           /**< A string value */
    WAVE_DATA_BOOL,             /**< A boolean value */
    WAVE_DATA_SEQ,              /**< A sequential collection. */
    WAVE_DATA_PAR,              /**< A parallel collection. */
    WAVE_DATA_OPERATOR,         /**< An operator */
    WAVE_DATA_UNKNOWN,          /**< Used when no type is set yet */
} wave_data_type;

/**
 * \brief Storage of wave data.
 * \sa wave_types_group
 */
typedef struct wave_data
{
    wave_data_type _type;                  /**< The type of the current data. */
    union
    {
        wave_int _int;                     /**< The stored integer value. */
        wave_float _float;                 /**< The stored floating point value.*/
        wave_char _char;                   /**< The stored character value. */
        wave_string _string;               /**< The stored string value. */
        wave_bool _bool;                   /**< The stored boolean value. */
        struct
        {
            struct wave_data * _tab;       /**< The stored collection. */
            size_t _size;                  /**< The size of the stored collection. */
        } _collection;                     /**< The stored collection and its size. */
    } _content;                            /**< The union to store multiple data values */
    size_t _index;
    struct wave_data * _up;                /**< The upper wave_data */
} wave_data;

////////////////////////////////////////////////////////////////////////////////
// Getters.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Get the type.
 * \param data Data of interest.
 * \return Type.
 * \relatesalso wave_data
 * \warning \c data must be not \c NULL.
 */
wave_data_type wave_data_get_type (const wave_data * data);

/**
 * \brief Get the integer value stored within the data of interest.
 * \param data Data of interest.
 * \return The integer value.
 * \warning \c data must be not \c NULL.
 * \relatesalso wave_data
 */
wave_int wave_data_get_int (const wave_data * data);

/**
 * \brief Get the floating point value stored within the data of interest.
 * \param data Data of interest.
 * \return The floating point value.
 * \warning \c data must be not \c NULL.
 * \relatesalso wave_data
 */
wave_float wave_data_get_float (const wave_data * data);

/**
 * \brief Get the character value stored within the data of interest.
 * \param data Data of interest.
 * \return The character value.
 * \warning \c data must be not \c NULL.
 * \relatesalso wave_data
 */
wave_char wave_data_get_char (const wave_data * data);

/**
 * \brief Get the string value stored within the data of interest.
 * \param data Data of interest.
 * \return The string value.
 * \warning \c data must be not \c NULL.
 * \relatesalso wave_data
 */
wave_string wave_data_get_string (const wave_data * data);

/**
 * \brief Get the boolean value stored within the data of interest.
 * \param data Data of interest.
 * \return The boolean value.
 * \warning \c data must be not \c NULL.
 * \relatesalso wave_data
 */
wave_bool wave_data_get_bool (const wave_data * data);

////////////////////////////////////////////////////////////////////////////////
// Properties.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Determine whether the data holds an atom.
 * \param data Data of interest.
 * \retval true if the data holds an atom.
 * \retval false otherwise.
 * \relatesalso wave_data
 * \warning \c data must be not \c NULL.
 */
wave_bool wave_data_is_atom (const wave_data * data);

////////////////////////////////////////////////////////////////////////////////
// Setters.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Store an integer value inside a data.
 * \param data Storage.
 * \param i Integer value.
 * \relatesalso wave_data
 * \warning \c data must be not \c NULL.
 */
void wave_data_set_int (wave_data * data, wave_int i);

/**
 * \brief Store a floating point value inside a data.
 * \param data Storage.
 * \param i Floating point value.
 * \relatesalso wave_data
 * \warning \c data must be not \c NULL.
 */
void wave_data_set_float (wave_data * data, wave_float f);

/**
 * \brief Store a character value inside a data.
 * \param data Storage.
 * \param i Character value.
 * \relatesalso wave_data
 * \warning \c data must be not \c NULL.
 */
void wave_data_set_char (wave_data * data, wave_char c);

/**
 * \brief Store a boolean value inside a data.
 * \param data Storage.
 * \param i Boolean value.
 * \relatesalso wave_data
 * \warning \c data must be not \c NULL.
 */
void wave_data_set_bool (wave_data * data, wave_bool b);

/**
 * \brief Store a string value inside a data.
 * \param data Storage.
 * \param i String value.
 * \relatesalso wave_data
 * \warning \c data must be not \c NULL.
 */
void wave_data_set_string (wave_data * data, wave_string s);

////////////////////////////////////////////////////////////////////////////////
// Operations.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Compute the result of an unary operation.
 * \param operand Operand supplied to the operation.
 * \param result Storage for the result.
 * \param op Operation.
 * \relatesalso wave_data
 * \warning \c operand and \c result must be not \c NULL.
 */
void wave_data_unary (const wave_data * operand, wave_data * result, wave_operator op);

/**
 * \brief Compute the result of a binary operation.
 * \param left Left operand supplied to the operation.
 * \param right Right operand supplied to the operation.
 * \param result Storage for the result.
 * \param op Operation.
 * \relatesalso wave_data
 * \warning \c left, \c right and \c result must be not \c NULL.
 */
void wave_data_binary (const wave_data * left, const wave_data * right, wave_data * result, wave_operator op);

////////////////////////////////////////////////////////////////////////////////
// Printing.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Print a data to a stream.
 * \param stream Stream.
 * \param data Data of interest.
 * \relatesalso wave_data
 * \warning \c data must be not \c NULL.
 */
void wave_data_fprint (FILE * stream, const wave_data * data);

#endif /* __WAVE_DATA_H__ */
