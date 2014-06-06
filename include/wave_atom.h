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

#include "wave_types.h"
#include "wave_path.h"
#include "wave_operator.h"

////////////////////////////////////////////////////////////////////////////////
// Enums, Structs, Typedefs.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Atom type.
 * \sa wave_atom
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
 *
 * An atom can hold:
 * - a constant integer value
 * - a constant float value
 * - a constant boolean value
 * - a constant character value
 * - a constant string value
 * - an operator
 * - a path
 * \sa wave_atom_type, wave_atom_content
 */
typedef struct wave_atom
{
    wave_atom_type _type;           /**<- The atom's type. */
    wave_atom_content _content;     /**<- The atom's content. */
} wave_atom;

////////////////////////////////////////////////////////////////////////////////
// Allocation, free.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Alloc for atoms.
 * \return Atom.
 * \relatesalso wave_atom
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
