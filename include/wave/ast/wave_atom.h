/**
 * \file wave_atom.h
 * \brief Wave atom.
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
#ifndef __WAVE_ATOM_H__
#define __WAVE_ATOM_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "wave/common/wave_types.h"
#include "wave/common/wave_operator.h"
#include "wave/ast/wave_path.h"

/**
 * \defgroup wave_atom_group Wave Atom
 * \ingroup wave_ast_group
 */

////////////////////////////////////////////////////////////////////////////////
// Enums, Structs, Typedefs.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Atom type.
 * \ingroup wave_atom_group
 *
 * Wave atoms can hold several types of values. This enumeration is used to
 * determine the type of the value.
 *
 * \sa wave_atom
 */
typedef enum wave_atom_type
{
    WAVE_ATOM_LITERAL_INT = 0,  /**< The atom is a constant integer. */
    WAVE_ATOM_LITERAL_FLOAT,    /**< The atom is a constant float. */
    WAVE_ATOM_LITERAL_BOOL,     /**< The atom is a constant boolean. */
    WAVE_ATOM_LITERAL_CHAR,     /**< The atom is a constant character. */
    WAVE_ATOM_LITERAL_STRING,   /**< The atom is a constant string. */
    WAVE_ATOM_OPERATOR,         /**< The atom is an operator. */
    WAVE_ATOM_PATH,             /**< The atom is a path. */
    WAVE_ATOM_UNKNOWN,          /**< Unknown. */
} wave_atom_type;

/**
 * \ingroup wave_atom_group
 * \brief Atom content.
 *
 * Wave atoms can hold several types of values. However, it can only hold one
 * value at a time, hence this union.
 *
 * \sa wave_atom
 */
typedef union wave_atom_content
{
    wave_int _int;                  /**< Integer. */
    wave_float _float;              /**< Float. */
    wave_bool _bool;                /**< Boolean. */
    wave_char _char;                /**< Character. */
    wave_char * _string;            /**< String. */
    wave_operator _operator;        /**< Operator of the atom. */
    wave_path * _path;              /**< Path of the atom. */
} wave_atom_content;

/**
 * \brief Atom.
 * \note The setter functions automatically set the atom's type appropriately.
 * \warning Atoms not obtained using wave_atom_alloc() must be initialized
 * using wave_atom_init() !
 * \warning The setters functions do not clean the atom prior modification !
 * \ingroup wave_atom_group
 *
 * # Atom creation and destruction
 * An atom can be dynamically created using wave_atom_alloc().
 * Atoms created this way must be freed using wave_atom_free().
 *
 * # Atom type
 * ## Possible types
 * An atom can hold:
 *
 * Atom content               | Corresponding atom type
 * ---------------------------|-------------------------
 * a constant integer value   | #WAVE_ATOM_LITERAL_INT
 * a constant float value     | #WAVE_ATOM_LITERAL_CHAR
 * a constant boolean value   | #WAVE_ATOM_LITERAL_BOOL
 * a constant character value | #WAVE_ATOM_LITERAL_FLOAT
 * a constant string value    | #WAVE_ATOM_LITERAL_STRING
 * an operator                | #WAVE_ATOM_PATH
 * a path                     | #WAVE_ATOM_OPERATOR
 *
 * An atom that does not yet (or does not anymore) hold a value is of type
 * #WAVE_ATOM_UNKNOWN. Sane users should not attempt to get the content of such
 * atoms.
 *
 * ## Getting an atom's type
 * In order to determine the type of an atom, one must use wave_atom_get_type().
 * It is also possible to directly test an atom for a specific type:
 *
 * Atom type                  | Test function.
 * ---------------------------|-------------------------
 * #WAVE_ATOM_LITERAL_INT     | wave_atom_is_int()
 * #WAVE_ATOM_LITERAL_CHAR    | wave_atom_is_float()
 * #WAVE_ATOM_LITERAL_BOOL    | wave_atom_is_char()
 * #WAVE_ATOM_LITERAL_FLOAT   | wave_atom_is_bool()
 * #WAVE_ATOM_LITERAL_STRING  | wave_atom_is_string()
 * #WAVE_ATOM_PATH            | wave_atom_is_path()
 * #WAVE_ATOM_OPERATOR        | wave_atom_is_operator()
 * #WAVE_ATOM_UNKNOWN         | wave_atom_is_unknown()
 *
 * # Atom content access
 * Once the type is known, one can use one of the following functions to get
 * the atom's content:
 *
 * Atom type                  | Getter function
 * ---------------------------|-------------------------
 * #WAVE_ATOM_LITERAL_INT     | wave_atom_get_int()
 * #WAVE_ATOM_LITERAL_CHAR    | wave_atom_get_float()
 * #WAVE_ATOM_LITERAL_BOOL    | wave_atom_get_char()
 * #WAVE_ATOM_LITERAL_FLOAT   | wave_atom_get_bool()
 * #WAVE_ATOM_LITERAL_STRING  | wave_atom_get_string()
 * #WAVE_ATOM_PATH            | wave_atom_get_path()
 * #WAVE_ATOM_OPERATOR        | wave_atom_get_operator()
 * #WAVE_ATOM_UNKNOWN         | NOTHING
 *
 * One should not try to get the content of a #WAVE_ATOM_UNKNOWN atom.
 *
 * # Atom modification
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
 *
 * Do not forget that these functions do not clean the atom's content.
 * If the atom already holds a value, it should first be cleaned using
 * wave_atom_clean() before using one of these setters.
 *
 * # Atom display
 * It is possible to print an atom to a stream using wave_atom_fprint() or to
 * the standard output using wave_atom_print().
 *
 * \sa wave_atom_type, wave_atom_content
 */
typedef struct wave_atom
{
    wave_atom_type _type;           /**<- The atom's type. */
    wave_atom_content _content;     /**<- The atom's content. */
} wave_atom;

////////////////////////////////////////////////////////////////////////////////
// Initialization, cleaning.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Initialize a wave_atom.
 * \param atom Atom.
 * \relatesalso wave_atom
 * \warning \c atom must be not \c NULL.
 */
void wave_atom_init (wave_atom * atom);

/**
 * \brief Clean a wave_atom.
 * \param atom Atom.
 * \relatesalso wave_atom
 * \warning \c atom must be not \c NULL.
 */
void wave_atom_clean (wave_atom * atom);

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

/**
 * \brief Copy an atom.
 * \param atom Atom.
 * \return Copy.
 * \relatesalso wave_atom
 */
void * wave_atom_copy (const wave_atom * atom);

////////////////////////////////////////////////////////////////////////////////
// Atom type information.
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
 * \brief Determine whether a wave_atom holds an integer litteral.
 * \param atom Atom.
 * \retval true if the atom holds an integer value.
 * \retval false otherwise.
 * \relatesalso wave_atom
 * \warning \c atom must be not \c NULL.
 */
bool wave_atom_is_int (const wave_atom * atom);

/**
 * \brief Determine whether a wave_atom holds a floating point litteral.
 * \param atom Atom.
 * \retval true if the atom holds a floating point value.
 * \retval false otherwise.
 * \relatesalso wave_atom
 * \warning \c atom must be not \c NULL.
 */
bool wave_atom_is_float (const wave_atom * atom);

/**
 * \brief Determine whether a wave_atom holds a character litteral.
 * \param atom Atom.
 * \retval true if the atom holds a character value.
 * \retval false otherwise.
 * \relatesalso wave_atom
 * \warning \c atom must be not \c NULL.
 */
bool wave_atom_is_char (const wave_atom * atom);

/**
 * \brief Determine whether a wave_atom holds a boolean litteral.
 * \param atom Atom.
 * \retval true if the atom holds a boolean value.
 * \retval false otherwise.
 * \relatesalso wave_atom
 * \warning \c atom must be not \c NULL.
 */
bool wave_atom_is_bool (const wave_atom * atom);

/**
 * \brief Determine whether a wave_atom holds a string litteral.
 * \param atom Atom.
 * \retval true if the atom holds a string value.
 * \retval false otherwise.
 * \relatesalso wave_atom
 * \warning \c atom must be not \c NULL.
 */
bool wave_atom_is_string (const wave_atom * atom);

/**
 * \brief Determine whether a wave_atom holds a path.
 * \param atom Atom.
 * \retval true if the atom holds a path.
 * \retval false otherwise.
 * \relatesalso wave_atom
 * \warning \c atom must be not \c NULL.
 */
bool wave_atom_is_path (const wave_atom * atom);

/**
 * \brief Determine whether a wave_atom holds an operator.
 * \param atom Atom.
 * \retval true if the atom holds an operator.
 * \retval false otherwise.
 * \relatesalso wave_atom
 * \warning \c atom must be not \c NULL.
 */
bool wave_atom_is_operator (const wave_atom * atom);

/**
 * \brief Determine whether a wave_atom holds nothing.
 * \param atom Atom.
 * \retval true if the atom holds nothing.
 * \retval false otherwise.
 * \relatesalso wave_atom
 * \warning \c atom must be not \c NULL.
 */
bool wave_atom_is_unknown (const wave_atom * atom);


////////////////////////////////////////////////////////////////////////////////
// Getters.
////////////////////////////////////////////////////////////////////////////////

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
const_wave_string wave_atom_get_string (const wave_atom * atom);

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
 * \warning If the atom already holds a value, it might be necessary to use
 * wave_atom_clean() first.
 * \post wave_atom_get_type() == #WAVE_ATOM_LITERAL_INT
 */
void wave_atom_set_int (wave_atom * atom, wave_int i);

/**
 * \brief Set an atom's float value.
 * \param atom Atom.
 * \param f Float value.
 * \relatesalso wave_atom
 * \warning \c atom must be not \c NULL.
 * \warning If the atom already holds a value, it might be necessary to use
 * wave_atom_clean() first.
 * \post wave_atom_get_type() == #WAVE_ATOM_LITERAL_FLOAT
 */
void wave_atom_set_float (wave_atom * atom, wave_float f);

/**
 * \brief Set an atom's int value.
 * \param atom Atom.
 * \param b Bool value.
 * \relatesalso wave_atom
 * \warning \c atom must be not \c NULL.
 * \warning If the atom already holds a value, it might be necessary to use
 * wave_atom_clean() first.
 * \post wave_atom_get_type() == #WAVE_ATOM_LITERAL_BOOL
 */
void wave_atom_set_bool (wave_atom * atom, wave_bool b);

/**
 * \brief Set an atom's int value.
 * \param atom Atom.
 * \param c Char value.
 * \relatesalso wave_atom
 * \warning \c atom must be not \c NULL.
 * \warning If the atom already holds a value, it might be necessary to use
 * wave_atom_clean() first.
 * \post wave_atom_get_type() == #WAVE_ATOM_LITERAL_CHAR
 */
void wave_atom_set_char (wave_atom * atom, wave_char c);

/**
 * \brief Set an atom's int value.
 * \param atom Atom.
 * \param string String value.
 * \relatesalso wave_atom
 * \warning \c atom must be not \c NULL.
 * \warning If the atom already holds a value, it might be necessary to use
 * wave_atom_clean() first.
 * \post wave_atom_get_type() == #WAVE_ATOM_LITERAL_STRING
 */
void wave_atom_set_string (wave_atom * atom, const_wave_string string);

/**
 * \brief Set an atom's value.
 * \param atom Atom.
 * \param path Path.
 * \relatesalso wave_atom
 * \warning \c atom must be not \c NULL.
 * \warning If the atom already holds a value, it might be necessary to use
 * wave_atom_clean() first.
 * \post wave_atom_get_type() == #WAVE_ATOM_PATH
 */
void wave_atom_set_path (wave_atom * atom, wave_path * path);

/**
 * \brief Set atomn atom's value.
 * \param atom Atom.
 * \param op Operator.
 * \relatesalso wave_atom
 * \warning \c atom must be not \c NULL.
 * \warning If the atom already holds a value, it might be necessary to use
 * wave_atom_clean() first.
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
