/**
 * \file wave_atom.c
 * \brief Atom.
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
#include "wave_atom.h"

////////////////////////////////////////////////////////////////////////////////
// Static utilities (wave_atom_content).
////////////////////////////////////////////////////////////////////////////////

/* "_wave_atom_content_get_*" : functions to get the content of a
 * wave_atom_content, once the wave_atom_type is known.
 */
static inline int _wave_atom_content_get_int (const wave_atom_content * atom)
{
    return atom->_int;
}

static inline float _wave_atom_content_get_float (const wave_atom_content * atom)
{
    return atom->_float;
}

static inline bool _wave_atom_content_get_bool (const wave_atom_content * atom)
{
    return atom->_bool;
}

static inline char _wave_atom_content_get_char (const wave_atom_content * atom)
{
    return atom->_char;
}

static inline char * _wave_atom_content_get_string (const wave_atom_content * atom)
{
    return atom->_string;
}

static inline wave_operator _wave_atom_content_get_operator (const wave_atom_content * atom)
{
    return atom->_operator;
}

static inline wave_path * _wave_atom_content_get_path (const wave_atom_content * atom)
{
    return atom->_path;
}

/* "_wave_atom_content_from_*" : functions to create a wave_atom_content from
 * a constant value, operator or a path.
 */
static inline wave_atom_content _wave_atom_content_from_int (wave_int i)
{
    return (wave_atom_content) { ._int = i };
}

static inline wave_atom_content _wave_atom_content_from_float (wave_float f)
{
    return (wave_atom_content) { ._float = f };
}

static inline wave_atom_content _wave_atom_content_from_bool (wave_bool b)
{
    return (wave_atom_content) { ._bool = b };
}

static inline wave_atom_content _wave_atom_content_from_char (wave_char c)
{
    return (wave_atom_content) { ._char = c };
}

static inline wave_atom_content _wave_atom_content_from_string (const wave_char * string)
{
    wave_char * content_string = malloc ((strlen (string) + 1) * sizeof * content_string);
    strcpy (content_string, string);
    return (wave_atom_content) { ._string = content_string };
}

static inline wave_atom_content _wave_atom_content_from_operator (wave_operator operator)
{
    return (wave_atom_content) { ._operator = operator };
}

static inline wave_atom_content _wave_atom_content_from_path (wave_path * path)
{
    return (wave_atom_content) { ._path = path };
}

/* "_wave_atom_content_fprint_*": functions to print a wave_atom_content once
 * the wave_atom_type is known.
 */
static inline void _wave_atom_content_fprint_int (FILE * stream, const wave_atom_content * c)
{
    fprintf (stream, "%d", c->_int);
}

static inline void _wave_atom_content_fprint_float (FILE * stream, const wave_atom_content * c)
{
    fprintf (stream, "%f", c->_float);
}

static inline void _wave_atom_content_fprint_bool (FILE * stream, const wave_atom_content * c)
{
    fprintf (stream, "%s", c->_bool ? "true" : "false");
}

static inline void _wave_atom_content_fprint_char (FILE * stream, const wave_atom_content * c)
{
    fprintf (stream, "\'%c\'", c->_char);
}

static inline void _wave_atom_content_fprint_string (FILE * stream, const wave_atom_content * c)
{
    fprintf (stream, "\"%s\"", c->_string);
}

static inline void _wave_atom_content_fprint_operator (FILE * stream, const wave_atom_content * c)
{
    wave_operator_fprint (stream, c->_operator);
}

static inline void _wave_atom_content_fprint_path (FILE * stream, const wave_atom_content * c)
{
    fprintf (stream, "@");
    wave_path_fprint (stream, c->_path);
}

/* Tab of functions used to print a wave_atom_content. */
static void (* const _wave_atom_content_fprint_functions []) (FILE *, const wave_atom_content *) =
{
    [WAVE_ATOM_LITERAL_INT]     = _wave_atom_content_fprint_int,
    [WAVE_ATOM_LITERAL_FLOAT]   = _wave_atom_content_fprint_float,
    [WAVE_ATOM_LITERAL_BOOL]    = _wave_atom_content_fprint_bool,
    [WAVE_ATOM_LITERAL_CHAR]    = _wave_atom_content_fprint_char,
    [WAVE_ATOM_LITERAL_STRING]  = _wave_atom_content_fprint_string,
    [WAVE_ATOM_OPERATOR]        = _wave_atom_content_fprint_operator,
    [WAVE_ATOM_PATH]            = _wave_atom_content_fprint_path,
    [WAVE_ATOM_UNKNOWN]         = NULL,
};

static inline void _wave_atom_content_fprint (FILE * stream, const wave_atom_content * c, wave_atom_type t)
{
    if (t >= 0 && t < WAVE_ATOM_UNKNOWN)
        _wave_atom_content_fprint_functions[t] (stream, c);
}

////////////////////////////////////////////////////////////////////////////////
// Static utilities (wave_atom).
////////////////////////////////////////////////////////////////////////////////

static inline wave_atom _wave_atom_build (wave_atom_type atom_type, wave_atom_content content)
{
    return (wave_atom) { ._type = atom_type, ._content = content };
}

static inline void _wave_atom_set_type (wave_atom * const atom, wave_atom_type atom_type)
{
    atom->_type = atom_type;
}

static inline void _wave_atom_set_content (wave_atom * const atom, wave_atom_content content)
{
    atom->_content = content;
}

static inline const wave_atom_content * _wave_atom_get_content (const wave_atom * atom)
{
    return & atom->_content;
}

////////////////////////////////////////////////////////////////////////////////
// Allocation, free.
////////////////////////////////////////////////////////////////////////////////

void * wave_atom_alloc (void)
{
    wave_atom * const atom = malloc (sizeof * atom);
    if (atom == NULL)
        perror ("malloc");
    else
        atom->_type = WAVE_ATOM_UNKNOWN;
    return atom;
}

void * wave_atom_free (wave_atom * atom)
{
    if (atom != NULL)
    {
        wave_atom_type atom_type = wave_atom_get_type (atom);
        if (atom_type == WAVE_ATOM_LITERAL_STRING)
            free (atom->_content._string);
        else if (atom_type == WAVE_ATOM_PATH)
            wave_path_free (atom->_content._path);
        free (atom);
        atom = NULL;
    }
    return NULL;
}

////////////////////////////////////////////////////////////////////////////////
// Builders.
////////////////////////////////////////////////////////////////////////////////

wave_atom wave_atom_from_int (wave_int i)
{
    wave_atom_content content = _wave_atom_content_from_int (i);
    return _wave_atom_build (WAVE_ATOM_LITERAL_INT, content);
}

wave_atom wave_atom_from_float (wave_float f)
{
    wave_atom_content content = _wave_atom_content_from_float (f);
    return _wave_atom_build (WAVE_ATOM_LITERAL_FLOAT, content);
}

wave_atom wave_atom_from_char (wave_char c)
{
    wave_atom_content content = _wave_atom_content_from_char (c);
    return _wave_atom_build (WAVE_ATOM_LITERAL_CHAR, content);
}

wave_atom wave_atom_from_bool (wave_bool b)
{
    wave_atom_content content = _wave_atom_content_from_bool (b);
    return _wave_atom_build (WAVE_ATOM_LITERAL_BOOL, content);
}

wave_atom wave_atom_from_string (const wave_char * string)
{
    wave_atom_content content = _wave_atom_content_from_string (string);
    return _wave_atom_build (WAVE_ATOM_LITERAL_STRING, content);
}

wave_atom wave_atom_from_path (wave_path * path)
{
    wave_atom_content content = _wave_atom_content_from_path (path);
    return _wave_atom_build (WAVE_ATOM_PATH, content);
}

wave_atom wave_atom_from_operator (wave_operator op)
{
    wave_atom_content content = _wave_atom_content_from_operator (op);
    return _wave_atom_build (WAVE_ATOM_OPERATOR, content);
}

////////////////////////////////////////////////////////////////////////////////
// Getters.
////////////////////////////////////////////////////////////////////////////////

wave_atom_type wave_atom_get_type (const wave_atom * atom)
{
    return atom->_type;
}

wave_int wave_atom_get_int (const wave_atom * const atom)
{
    const wave_atom_content * const content = _wave_atom_get_content (atom);
    return _wave_atom_content_get_int (content);
}

wave_float wave_atom_get_float (const wave_atom * const atom)
{
    const wave_atom_content * const content = _wave_atom_get_content (atom);
    return _wave_atom_content_get_float (content);
}

wave_char wave_atom_get_char (const wave_atom * const atom)
{
    const wave_atom_content * const content = _wave_atom_get_content (atom);
    return _wave_atom_content_get_char (content);
}

wave_bool wave_atom_get_bool (const wave_atom * const atom)
{
    const wave_atom_content * const content = _wave_atom_get_content (atom);
    return _wave_atom_content_get_bool (content);
}

wave_char * wave_atom_get_string (const wave_atom * const atom)
{
    const wave_atom_content * const content = _wave_atom_get_content (atom);
    return _wave_atom_content_get_string (content);
}

wave_operator wave_atom_get_operator (const wave_atom * const atom)
{
    const wave_atom_content * const content = _wave_atom_get_content (atom);
    return _wave_atom_content_get_operator (content);
}

wave_path * wave_atom_get_path (const wave_atom * const atom)
{
    const wave_atom_content * const content = _wave_atom_get_content (atom);
    return _wave_atom_content_get_path (content);
}

////////////////////////////////////////////////////////////////////////////////
// Setters.
////////////////////////////////////////////////////////////////////////////////

void wave_atom_set_path (wave_atom * const atom, wave_path * path)
{
    _wave_atom_set_type (atom, WAVE_ATOM_PATH);
    _wave_atom_set_content (atom, _wave_atom_content_from_path (path));
}

void wave_atom_set_operator (wave_atom * const atom, wave_operator op)
{
    _wave_atom_set_type (atom, WAVE_ATOM_OPERATOR);
    _wave_atom_set_content (atom, _wave_atom_content_from_operator (op));
}

void wave_atom_set_int (wave_atom * const atom, wave_int i)
{
    _wave_atom_set_type (atom, WAVE_ATOM_LITERAL_INT);
    _wave_atom_set_content (atom, _wave_atom_content_from_int (i));
}

void wave_atom_set_float (wave_atom * const atom, wave_float f)
{
    _wave_atom_set_type (atom, WAVE_ATOM_LITERAL_FLOAT);
    _wave_atom_set_content (atom, _wave_atom_content_from_float (f));
}

void wave_atom_set_bool (wave_atom * const atom, wave_bool b)
{
    _wave_atom_set_type (atom, WAVE_ATOM_LITERAL_BOOL);
    _wave_atom_set_content (atom, _wave_atom_content_from_bool (b));
}

void wave_atom_set_char (wave_atom * const atom, wave_char c)
{
    _wave_atom_set_type (atom, WAVE_ATOM_LITERAL_CHAR);
    _wave_atom_set_content (atom, _wave_atom_content_from_char (c));
}

void wave_atom_set_string (wave_atom * const atom, wave_char * string)
{
    _wave_atom_set_type (atom, WAVE_ATOM_LITERAL_STRING);
    _wave_atom_set_content (atom, _wave_atom_content_from_string (string));
}

////////////////////////////////////////////////////////////////////////////////
// Printing.
////////////////////////////////////////////////////////////////////////////////

void wave_atom_fprint (FILE * stream, const wave_atom * a)
{
    wave_atom_type atom_type = wave_atom_get_type (a);
    const wave_atom_content * const content = _wave_atom_get_content (a);
    _wave_atom_content_fprint (stream, content, atom_type);
}

void wave_atom_print (const wave_atom * a)
{
    wave_atom_fprint (stdout, a);
}
