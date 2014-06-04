/**
 * \file test_wave_atom.c
 * \brief Wave atom tests.
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
#include "test_wave_atom.h"

////////////////////////////////////////////////////////////////////////////////
// Static variables.
////////////////////////////////////////////////////////////////////////////////

static bool must_free_atoms = true;
#define WAVE_ATOM_NUMBER 10
static wave_atom * atoms[WAVE_ATOM_NUMBER];
static wave_atom_type WAVE_ATOM_TYPES[] =
{
    WAVE_ATOM_LITERAL_INT,
    WAVE_ATOM_LITERAL_FLOAT,
    WAVE_ATOM_LITERAL_BOOL,
    WAVE_ATOM_LITERAL_CHAR,
    WAVE_ATOM_LITERAL_STRING,
    WAVE_ATOM_OPERATOR,
    WAVE_ATOM_PATH,
    WAVE_ATOM_UNKNOWN,
};
static wave_operator WAVE_OPERATORS[] =
{
    WAVE_OP_UNARY_PLUS,
    WAVE_OP_UNARY_MINUS,
    WAVE_OP_UNARY_INCREMENT,
    WAVE_OP_UNARY_DECREMENT,
    WAVE_OP_UNARY_SQRT,
    WAVE_OP_UNARY_SIN,
    WAVE_OP_UNARY_COS,
    WAVE_OP_UNARY_NOT,
    WAVE_OP_UNARY_LOG,
    WAVE_OP_UNARY_EXP,
    WAVE_OP_UNARY_CEIL,
    WAVE_OP_UNARY_FLOOR,
    WAVE_OP_BINARY_PLUS,
    WAVE_OP_BINARY_MINUS,
    WAVE_OP_BINARY_MIN,
    WAVE_OP_BINARY_MAX,
    WAVE_OP_BINARY_TIMES,
    WAVE_OP_BINARY_DIVIDE,
    WAVE_OP_BINARY_MOD,
    WAVE_OP_BINARY_EQUALS,
    WAVE_OP_BINARY_DIFFERS,
    WAVE_OP_BINARY_LESSER_OR_EQUALS,
    WAVE_OP_BINARY_GREATER_OR_EQUALS,
    WAVE_OP_BINARY_GREATER,
    WAVE_OP_BINARY_LESSER,
    WAVE_OP_BINARY_AND,
    WAVE_OP_BINARY_OR,
    WAVE_OP_BINARY_GET,
    WAVE_OP_SPECIFIC_ATOM,
    WAVE_OP_SPECIFIC_STOP,
    WAVE_OP_SPECIFIC_CUT,
    WAVE_OP_SPECIFIC_READ,
    WAVE_OP_SPECIFIC_PRINT,
    WAVE_OP_UNKNOWN,
};

////////////////////////////////////////////////////////////////////////////////
// Suite related functions.
////////////////////////////////////////////////////////////////////////////////

void _test_init (void)
{
    for (unsigned int i = 0; i < WAVE_ATOM_NUMBER; ++i)
        atoms[i] = malloc (sizeof * atoms[i]);
    char * string_4 = malloc ((strlen ("abcde") + 1) * sizeof * string_4);
    strcpy (string_4, "abcde");

    * atoms[0] = (wave_atom) { ._type = WAVE_ATOM_LITERAL_INT, ._content._int = 1 };
    * atoms[1] = (wave_atom) { ._type = WAVE_ATOM_LITERAL_FLOAT, ._content._float = 0.2f };
    * atoms[2] = (wave_atom) { ._type = WAVE_ATOM_LITERAL_BOOL, ._content._bool = true };
    * atoms[3] = (wave_atom) { ._type = WAVE_ATOM_LITERAL_CHAR, ._content._char = 'a' };
    * atoms[4] = (wave_atom) { ._type = WAVE_ATOM_LITERAL_STRING, ._content._string = string_4 };
    * atoms[5] = (wave_atom) { ._type = WAVE_ATOM_OPERATOR, ._content._operator = WAVE_OP_BINARY_PLUS };
}

void _test_clean (void)
{
    if (must_free_atoms)
        for (unsigned int i = 0; i < WAVE_ATOM_NUMBER; ++i)
            free (atoms[i]);
    must_free_atoms = true;
}

int test_wave_atom_suite_init (void)
{
    return 0;
}

int test_wave_atom_suite_clean (void)
{
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
// Allocation, free tests.
////////////////////////////////////////////////////////////////////////////////

void test_wave_atom_allocator (void)
{
    _test_init ();
    wave_atom * a = wave_atom_allocator ();
    CU_ASSERT_PTR_NOT_NULL (a)
    free (a);
    _test_clean ();
}

void test_wave_atom_free (void)
{
    _test_init ();
    for (unsigned int i = 0; i < WAVE_ATOM_NUMBER; ++i)
        wave_atom_free (atoms[i]);
    must_free_atoms = false;
    _test_clean ();
}

////////////////////////////////////////////////////////////////////////////////
// Builders tests.
////////////////////////////////////////////////////////////////////////////////

void test_wave_atom_from_int (void)
{
    _test_init ();
    int value = 10;
    wave_atom atom = wave_atom_from_int (value);
    CU_ASSERT_EQUAL (atom._type, WAVE_ATOM_LITERAL_INT)
    CU_ASSERT_EQUAL (atom._content._int, value)
    _test_clean ();
}

void test_wave_atom_from_float (void)
{
    _test_init ();
    float value = 0.2f;
    wave_atom atom = wave_atom_from_float (value);
    CU_ASSERT_EQUAL (atom._type, WAVE_ATOM_LITERAL_FLOAT)
    CU_ASSERT_DOUBLE_EQUAL (atom._content._float, value, 1e-5)
    _test_clean ();
}

void test_wave_atom_from_char (void)
{
    _test_init ();
    char value = 'a';
    wave_atom atom = wave_atom_from_char (value);
    CU_ASSERT_EQUAL (atom._type, WAVE_ATOM_LITERAL_CHAR)
    CU_ASSERT_EQUAL (atom._content._char, value)
    _test_clean ();
}

void test_wave_atom_from_bool (void)
{
    _test_init ();
    bool value = true;
    wave_atom atom = wave_atom_from_bool (value);
    CU_ASSERT_EQUAL (atom._type, WAVE_ATOM_LITERAL_BOOL)
    CU_ASSERT_EQUAL (atom._content._bool, value)
    _test_clean ();
}

void test_wave_atom_from_string (void)
{
    _test_init ();
    _test_clean ();
}

void test_wave_atom_from_path (void)
{
    _test_init ();
    _test_clean ();
}

void test_wave_atom_from_operator (void)
{
    _test_init ();
    _test_clean ();
}

////////////////////////////////////////////////////////////////////////////////
// Getters tests.
////////////////////////////////////////////////////////////////////////////////

void test_wave_atom_get_type (void)
{
    _test_init ();
    _test_clean ();
}

void test_wave_atom_get_int (void)
{
    _test_init ();
    _test_clean ();
}

void test_wave_atom_get_float (void)
{
    _test_init ();
    _test_clean ();
}

void test_wave_atom_get_char (void)
{
    _test_init ();
    _test_clean ();
}

void test_wave_atom_get_bool (void)
{
    _test_init ();
    _test_clean ();
}

void test_wave_atom_get_string (void)
{
    _test_init ();
    _test_clean ();
}

void test_wave_atom_get_operator (void)
{
    _test_init ();
    _test_clean ();
}

void test_wave_atom_get_path (void)
{
    _test_init ();
    _test_clean ();
}

////////////////////////////////////////////////////////////////////////////////
// Setters tests.
////////////////////////////////////////////////////////////////////////////////

void test_wave_atom_set_int (void)
{
    _test_init ();
    _test_clean ();
}

void test_wave_atom_set_float (void)
{
    _test_init ();
    _test_clean ();
}

void test_wave_atom_set_bool (void)
{
    _test_init ();
    _test_clean ();
}

void test_wave_atom_set_char (void)
{
    _test_init ();
    _test_clean ();
}

void test_wave_atom_set_string (void)
{
    _test_init ();
    _test_clean ();
}

void test_wave_atom_set_path (void)
{
    _test_init ();
    _test_clean ();
}

void test_wave_atom_set_operator (void)
{
    _test_init ();
    _test_clean ();
}
