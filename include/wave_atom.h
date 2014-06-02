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

#include "wave_types.h"
#include "wave_path.h"
#include "wave_operator.h"

////////////////////////////////////////////////////////////////////////////////
// Enums, Structs, Typedefs.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Atom type.
 */
typedef enum wave_atom_type
{
    WAVE_ATOM_LITERAL,     /**<- The atom is a const value. */
    WAVE_ATOM_OPERATOR,  /**<- The atom is an operator. */
    WAVE_ATOM_PATH,      /**<- The atom is a path. */
    WAVE_ATOM_UNKNOWN    /**<- Unknown. */
} wave_atom_type;

typedef enum wave_literal_type
{
    WAVE_LITERAL_INT,
    WAVE_LITERAL_FLOAT,
    WAVE_LITERAL_BOOL,
    WAVE_LITERAL_CHAR,
    WAVE_LITERAL_STRING
} wave_literal_type;

/**
 * \brief Atom content.
 */
typedef union wave_atom_content
{
    wave_operator _operator;    /**<- Operator of the atom. */
    wave_path _path;            /**<- Path of the atom. */
    wave_int _int;                   /**<- Integer. */
    wave_float _float;               /**<- Float. */
    wave_bool _bool;                 /**<- Boolean. */
    wave_char _char;                 /**<- Character. */
    wave_char * _string;             /**<- String. */
} wave_atom_content;

/**
 * \brief Atom.
 */
typedef struct wave_atom
{
    wave_atom_type _type;            /**<- The atom's type. */
    wave_atom_content _content;      /**<- The atom's content. */
} wave_atom;

////////////////////////////////////////////////////////////////////////////////
// Allocation, free.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Allocator for atoms.
 * \return Atom.
 * \relatesalso wave_atom
 */
void * wave_atom_allocator (void);

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
 * \brief Get an atom which will yeld the provided integer.
 * \param int Int.
 * \return atom.
 * \relatesalso wave_atom
 */
wave_atom wave_atom_from_int (wave_int i);

/**
 * \brief Get an atom which will yeld the provided float.
 * \param f Float.
 * \return atom.
 * \relatesalso wave_atom
 */
wave_atom wave_atom_from_float (float f);

/**
 * \brief Get an atom which will yeld the provided character.
 * \param c Char.
 * \return atom.
 * \relatesalso wave_atom
 */
wave_atom wave_atom_from_char (char c);

/**
 * \brief Get an atom which will yeld the provided bool.
 * \param b Bool.
 * \return atom.
 * \relatesalso wave_atom
 */
wave_atom wave_atom_from_bool (bool b);

/**
 * \brief Get an atom which will yeld the provided string.
 * \param string String.
 * \return atom.
 * \relatesalso wave_atom
 */
wave_atom wave_atom_from_string (char * string);

/**
 * \brief Get an atom which will yeld the provided path.
 * \param path Path.
 * \return atom.
 * \relatesalso wave_atom
 */
wave_atom wave_atom_from_path (wave_path path);

/**
 * \brief Get an atom which will yeld the provided operator.
 * \param op Operator.
 * \return atom.
 * \relatesalso wave_atom
 * \note The atom's type will be set to WAVE_ATOM_OPERATOR.
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
 */
wave_atom_type wave_atom_get_type (const wave_atom * const atom);

/**
 * \brief Get an atom's int.
 * \param atom Atom.
 * \return The atom's int value.
 * \relatesalso wave_atom
 */
wave_int wave_atom_get_int (const wave_atom * const atom);

/**
 * \brief Get an atom's float.
 * \param a Atom.
 * \return The atom's float value.
 * \relatesalso wave_atom
 */
wave_float wave_atom_get_float (const wave_atom * const atom);

/**
 * \brief Get an atom's char.
 * \param atom Atom.
 * \return The atom's char value.
 * \relatesalso wave_atom
 */
char wave_atom_get_char (const wave_atom * const atom);

/**
 * \brief Get an atom's bool
 * \param atom Atom.
 * \return The atom's bool value.
 * \relatesalso wave_atom
 */
bool wave_atom_get_bool (const wave_atom * const atom);

/**
 * \brief Get an atom's string
 * \param atom Atom.
 * \return The atom's string
 * \pre atom_get_type (atom) == ATOM_LITERAL
 * \relatesalso wave_atom
 */
char * wave_atom_get_string (const wave_atom * const atom);

/**
 * \brief Get an atom's operator.
 * \param atom Atom.
 * \return The atom's operator.
 * \pre atom_get_type (atom) == ATOM_OPERATOR.
 * \relatesalso wave_atom
 */
wave_operator wave_atom_get_operator (const wave_atom * const atom);

/**
 * \brief Get an atom's path.
 * \param atom Atom.
 * \return The atom's path.
 * \pre atom_get_type (atom) == ATOM_PATH.
 * \relatesalso wave_atom
 */
wave_path wave_atom_get_path (const wave_atom * const atom);

////////////////////////////////////////////////////////////////////////////////
// Setters.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Set an atom's int value.
 * \param atom Atom.
 * \param i Int value.
 * \note The atom's type will be set to WAVE_ATOM_LITERAL.
 * \relatesalso wave_atom
 */
void wave_atom_set_int (wave_atom * const atom, wave_int i);

/**
 * \brief Set an atom's float value.
 * \param atom Atom.
 * \param f Float value.
 * \note The atom's type will be set to WAVE_ATOM_LITERAL.
 * \relatesalso wave_atom
 */
void wave_atom_set_float (wave_atom * const atom, wave_float f);

/**
 * \brief Set an atom's int value.
 * \param atom Atom.
 * \param b Bool value.
 * \note The atom's type will be set to WAVE_ATOM_LITERAL.
 * \relatesalso wave_atom
 */
void wave_atom_set_bool (wave_atom * const atom, wave_bool b);

/**
 * \brief Set an atom's int value.
 * \param atom Atom.
 * \param c Char value.
 * \note The atom's type will be set to WAVE_ATOM_LITERAL.
 * \relatesalso wave_atom
 */
void wave_atom_set__char (wave_atom * const atom, wave_char c);

/**
 * \brief Set an atom's int value.
 * \param atom Atom.
 * \param string String value.
 * \note The atom's type will be set to WAVE_ATOM_LITERAL.
 * \relatesalso wave_atom
 */
void wave_atom_set_string (wave_atom * const atom, wave_char * string);

/**
 * \brief Set an atom's value.
 * \param atom Atom.
 * \param path Path.
 * \relatesalso wave_atom
 */
void wave_atom_set_path (wave_atom * const atom, wave_path path);

/**
 * \brief Set atomn atom's value.
 * \param atom Atom.
 * \param op Operator.
 * \relatesalso wave_atom
 */
void wave_atom_set_operator (wave_atom * const atom, wave_operator op);

#endif /* __WAVE_ATOM_H__ */
