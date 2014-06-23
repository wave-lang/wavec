/**
 * \file wave_atom.h
 * \brief Wave atom.
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
#ifndef __WAVE_ATOM_H__
#define __WAVE_ATOM_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "wave/common/wave_types.h"
#include "wave/ast/wave_path.h"
#include "wave/ast/wave_operator.h"

////////////////////////////////////////////////////////////////////////////////
// Enums, Structs, Typedefs.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Atom type.
 * \sa wave_atom
 *
 * Wave atoms can hold several types of values. This enumeration is used to
 * determine the type of the value.
 */
typedef enum wave_atom_type
{
    WAVE_ATOM_LITERAL_INT = 0,  /**<- The atom is a constant integer. */
    WAVE_ATOM_LITERAL_FLOAT,    /**<- The atom is a constant float. */
    WAVE_ATOM_LITERAL_BOOL,     /**<- The atom is a constant boolean. */
    WAVE_ATOM_LITERAL_CHAR,     /**<- The atom is a constant character. */
    WAVE_ATOM_LITERAL_STRING,   /**<- The atom is a constant string. */
    WAVE_ATOM_OPERATOR,         /**<- The atom is an operator. */
    WAVE_ATOM_PATH,             /**<- The atom is a path. */
    WAVE_ATOM_UNKNOWN,          /**<- Unknown. */
} wave_atom_type;

/**
 * \brief Atom content.
 * \sa wave_atom
 *
 * Wave atoms can hold several types of values. However, it can only hold one
 * value at a time, hence this union.
 */
typedef union wave_atom_content
{
    wave_int _int;                  /**<- Integer. */
    wave_float _float;              /**<- Float. */
    wave_bool _bool;                /**<- Boolean. */
    wave_char _char;                /**<- Character. */
    wave_char * _string;            /**<- String. */
    wave_operator _operator;        /**<- Operator of the atom. */
    wave_path * _path;              /**<- Path of the atom. */
} wave_atom_content;

/**
 * \brief Atom.
 * \sa wave_atom_type, wave_atom_content
 * \note The setter functions automatically set the atom's type appropriately.
 * \warning Atoms not obtained using wave_atom_alloc() must be initialized
 * using wave_atom_init() !
 *
 * # Description
 * An atom can hold:
 * - a constant integer value (#WAVE_ATOM_LITERAL_INT)
 * - a constant float value (#WAVE_ATOM_LITERAL_FLOAT)
 * - a constant boolean value (#WAVE_ATOM_LITERAL_BOOL)
 * - a constant character value (#WAVE_ATOM_LITERAL_CHAR)
 * - a constant string value (#WAVE_ATOM_LITERAL_STRING)
 * - an operator (#WAVE_ATOM_OPERATOR)
 * - a path (#WAVE_ATOM_PATH)
 *
 * An atom can be dynamically created using wave_atom_alloc().
 * Atoms created this way must be freed using wave_atom_free().
 *
 * Statically created atoms must be initialized using wave_atom_init().
 *
 * # Atom type
 * In order to determine the type of an atom, one must use wave_atom_get_type().
 * Once the type is known, one can use one of the following functions to get
 * the atom's content:
 * - wave_atom_get_int()
 * - wave_atom_get_float()
 * - wave_atom_get_char()
 * - wave_atom_get_bool()
 * - wave_atom_get_string()
 * - wave_atom_get_path()
 * - wave_atom_get_operator()
 *
 * An atom that does not yet (or does not anymore) hold a value is of type
 * #WAVE_ATOM_UNKNOWN. Sane users should not attempt to get the content of such
 * atoms.
 *
 * Atoms can be modified using one of the following functions:
 * - wave_atom_set_int()
 * - wave_atom_set_float()
 * - wave_atom_set_char()
 * - wave_atom_set_bool()
 * - wave_atom_set_string()
 * - wave_atom_set_path()
 * - wave_atom_set_operator()
 *
 * Please note that these functions automatically set the atom's type
 * appropriately.
 */
typedef struct wave_atom
{
    wave_atom_type _type;           /**<- The atom's type. */
    wave_atom_content _content;     /**<- The atom's content. */
} wave_atom;

////////////////////////////////////////////////////////////////////////////////
// Initialization.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Initialize a wave_atom.
 * \param atom Atom.
 * \relatesalso wave_atom
 */
void wave_atom_init (wave_atom * atom);

////////////////////////////////////////////////////////////////////////////////
// Allocation, free.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Alloc for atoms.
 * \return Atom.
 * \relatesalso wave_atom
 * \note Atoms obtained using wave_atom_alloc() are already initialized. It is not needed to use wave_atom_init().
 */
void * wave_atom_alloc (void);

/**
 * \brief Free atoms.
 * \param atom Atom.
 * \return NULL
 * \relatesalso wave_atom
 */
void * wave_atom_free (wave_atom * atom);

////////////////////////////////////////////////////////////////////////////////
// Builders.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Get an atom which will hold the provided integer.
 * \param i Int.
 * \return atom.
 * \relatesalso wave_atom
 * \post wave_atom_get_type() == #WAVE_ATOM_LITERAL_INT
 * \post wave_atom_get_int() == \c i
 */
wave_atom wave_atom_from_int (wave_int i);

/**
 * \brief Get an atom which will hold the provided float.
 * \param f Float.
 * \return atom.
 * \relatesalso wave_atom
 * \post wave_atom_get_type() == #WAVE_ATOM_LITERAL_FLOAT
 * \post wave_atom_get_float() == \c f
 */
wave_atom wave_atom_from_float (wave_float f);

/**
 * \brief Get an atom which will hold the provided character.
 * \param c Char.
 * \return atom.
 * \relatesalso wave_atom
 * \post wave_atom_get_type() == #WAVE_ATOM_LITERAL_CHAR
 * \post wave_atom_get_char() == \c c
 */
wave_atom wave_atom_from_char (wave_char c);

/**
 * \brief Get an atom which will hold the provided bool.
 * \param b Bool.
 * \return atom.
 * \relatesalso wave_atom
 * \post wave_atom_get_type() == #WAVE_ATOM_LITERAL_BOOL
 * \post wave_atom_get_bool() == \c b
 */
wave_atom wave_atom_from_bool (wave_bool b);

/**
 * \brief Get an atom which will hold the provided string.
 * \param string String.
 * \return atom.
 * \relatesalso wave_atom
 * \note The content of \c string will be copied, it is up to the user to free \c string, if needed.
 * \post wave_atom_get_type() == #WAVE_ATOM_LITERAL_STRING
 * \post strcmp (wave_atom_get_string(), string) == 0
 */
wave_atom wave_atom_from_string (const wave_char * string);

/**
 * \brief Get an atom which will hold the provided path.
 * \param path Path.
 * \return atom.
 * \relatesalso wave_atom
 * \post wave_atom_get_type() == #WAVE_ATOM_PATH
 */
wave_atom wave_atom_from_path (wave_path * path);

/**
 * \brief Get an atom which will hold the provided operator.
 * \param op Operator.
 * \return atom.
 * \relatesalso wave_atom
 * \post wave_atom_get_type() == #WAVE_ATOM_OPERATOR
 * \post wave_atom_get_operator() == \c op
 * \relatesalso wave_atom
 */
wave_atom wave_atom_from_operator (wave_operator op);

////////////////////////////////////////////////////////////////////////////////
// Getters.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Get an atom's type.
 * \param atom Atom.
 * \return The atom's type.
 * \relatesalso wave_atom
 * \warning \c atom must be not \c NULL.
 */
wave_atom_type wave_atom_get_type (const wave_atom * atom);

/**
 * \brief Get an atom's int.
 * \param atom Atom.
 * \return The atom's int value.
 * \relatesalso wave_atom
 * \warning \c atom must be not \c NULL.
 */
wave_int wave_atom_get_int (const wave_atom * atom);

/**
 * \brief Get an atom's float.
 * \param atom Atom.
 * \return The atom's float value.
 * \relatesalso wave_atom
 * \warning \c atom must be not \c NULL.
 */
wave_float wave_atom_get_float (const wave_atom * atom);

/**
 * \brief Get an atom's char.
 * \param atom Atom.
 * \return The atom's char value.
 * \relatesalso wave_atom
 * \warning \c atom must be not \c NULL.
 */
char wave_atom_get_char (const wave_atom * atom);

/**
 * \brief Get an atom's bool
 * \param atom Atom.
 * \return The atom's bool value.
 * \relatesalso wave_atom
 * \warning \c atom must be not \c NULL.
 */
bool wave_atom_get_bool (const wave_atom * atom);

/**
 * \brief Get an atom's string
 * \param atom Atom.
 * \return The atom's string
 * \pre atom_get_type (atom) == ATOM_LITERAL
 * \relatesalso wave_atom
 * \warning \c atom must be not \c NULL.
 */
char * wave_atom_get_string (const wave_atom * atom);

/**
 * \brief Get an atom's operator.
 * \param atom Atom.
 * \return The atom's operator.
 * \pre atom_get_type (atom) == ATOM_OPERATOR.
 * \relatesalso wave_atom
 * \warning \c atom must be not \c NULL.
 */
wave_operator wave_atom_get_operator (const wave_atom * atom);

/**
 * \brief Get an atom's path.
 * \param atom Atom.
 * \return The atom's path.
 * \pre atom_get_type (atom) == ATOM_PATH.
 * \relatesalso wave_atom
 * \warning \c atom must be not \c NULL.
 */
wave_path * wave_atom_get_path (const wave_atom * atom);

////////////////////////////////////////////////////////////////////////////////
// Setters.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Set an atom's int value.
 * \param atom Atom.
 * \param i Int value.
 * \relatesalso wave_atom
 * \warning \c atom must be not \c NULL.
 * \post wave_atom_get_type() == #WAVE_ATOM_LITERAL_INT
 */
void wave_atom_set_int (wave_atom * atom, wave_int i);

/**
 * \brief Set an atom's float value.
 * \param atom Atom.
 * \param f Float value.
 * \relatesalso wave_atom
 * \warning \c atom must be not \c NULL.
 * \post wave_atom_get_type() == #WAVE_ATOM_LITERAL_FLOAT
 */
void wave_atom_set_float (wave_atom * atom, wave_float f);

/**
 * \brief Set an atom's int value.
 * \param atom Atom.
 * \param b Bool value.
 * \relatesalso wave_atom
 * \warning \c atom must be not \c NULL.
 * \post wave_atom_get_type() == #WAVE_ATOM_LITERAL_BOOL
 */
void wave_atom_set_bool (wave_atom * atom, wave_bool b);

/**
 * \brief Set an atom's int value.
 * \param atom Atom.
 * \param c Char value.
 * \relatesalso wave_atom
 * \warning \c atom must be not \c NULL.
 * \post wave_atom_get_type() == #WAVE_ATOM_LITERAL_CHAR
 */
void wave_atom_set_char (wave_atom * atom, wave_char c);

/**
 * \brief Set an atom's int value.
 * \param atom Atom.
 * \param string String value.
 * \relatesalso wave_atom
 * \warning \c atom must be not \c NULL.
 * \post wave_atom_get_type() == #WAVE_ATOM_LITERAL_STRING
 */
void wave_atom_set_string (wave_atom * atom, wave_char * string);

/**
 * \brief Set an atom's value.
 * \param atom Atom.
 * \param path Path.
 * \relatesalso wave_atom
 * \warning \c atom must be not \c NULL.
 * \post wave_atom_get_type() == #WAVE_ATOM_PATH
 */
void wave_atom_set_path (wave_atom * atom, wave_path * path);

/**
 * \brief Set atomn atom's value.
 * \param atom Atom.
 * \param op Operator.
 * \relatesalso wave_atom
 * \warning \c atom must be not \c NULL.
 * \post wave_atom_get_type() == #WAVE_ATOM_OPERATOR
 */
void wave_atom_set_operator (wave_atom * atom, wave_operator op);

////////////////////////////////////////////////////////////////////////////////
// Printing.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Print a wave_atom to a stream.
 * \param stream Stream.
 * \param a Atom.
 */
void wave_atom_fprint (FILE * stream, const wave_atom * a);

/**
 * \brief Print a wave_atom to stdout.
 */
void wave_atom_print (const wave_atom * a);

#endif /* __WAVE_ATOM_H__ */
