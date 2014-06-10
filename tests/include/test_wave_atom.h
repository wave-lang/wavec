/**
 * \file test_wave_atom.h
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
#ifndef __TEST_WAVE_ATOM_H__
#define __TEST_WAVE_ATOM_H__

#include <stdbool.h>
#include <CUnit/CUnit.h>

#include "wave_atom.h"

////////////////////////////////////////////////////////////////////////////////
// Suite related functions.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief wave_atom test suite initialization.
 * \return Success or error code.
 * \todo implementation
 */
int test_wave_atom_suite_init (void);

/**
 * \brief wave_atom test suite cleaning.
 * \return Success or error code.
 * \todo implementation
 */
int test_wave_atom_suite_clean (void);

////////////////////////////////////////////////////////////////////////////////
// Initialization tests.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Test wave_atom_alloc().
 * \test wave_atom_init()
 * \todo implementation
 */
void test_wave_atom_init (void);

////////////////////////////////////////////////////////////////////////////////
// Allocation, free tests.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Test wave_atom_alloc().
 * \test wave_atom_alloc()
 * \todo implementation
 */
void test_wave_atom_alloc (void);

/**
 * \brief Test wave_atom_free().
 * \test wave_atom_free()
 * \todo implementation
 */
void test_wave_atom_free (void);

////////////////////////////////////////////////////////////////////////////////
// Builders tests.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Test wave_atom_from_int().
 * \test wave_atom_from_int()
 * \todo implementation
 */
void test_wave_atom_from_int (void);

/**
 * \brief Test wave_atom_from_float().
 * \test wave_atom_from_float()
 * \todo implementation
 */
void test_wave_atom_from_float (void);

/**
 * \brief Test wave_atom_from_char().
 * \test wave_atom_from_char()
 * \todo implementation
 */
void test_wave_atom_from_char (void);

/**
 * \brief Test wave_atom_from_bool().
 * \test wave_atom_from_bool()
 * \todo implementation
 */
void test_wave_atom_from_bool (void);

/**
 * \brief Test wave_atom_from_string().
 * \test wave_atom_from_string()
 * \todo implementation
 */
void test_wave_atom_from_string (void);

/**
 * \brief Test wave_atom_from_path().
 * \test wave_atom_from_path()
 * \todo implementation
 */
void test_wave_atom_from_path (void);

/**
 * \brief Test wave_atom_from_operator().
 * \test wave_atom_from_operator()
 * \todo implementation
 */
void test_wave_atom_from_operator (void);

////////////////////////////////////////////////////////////////////////////////
// Getters tests.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Test wave_atom_get_type().
 * \test wave_atom_get_type()
 * \todo implementation
 */
void test_wave_atom_get_type (void);

/**
 * \brief Test wave_atom_get_int().
 * \test wave_atom_get_int()
 * \todo implementation
 */
void test_wave_atom_get_int (void);

/**
 * \brief Test wave_atom_get_float().
 * \test wave_atom_get_float()
 * \todo implementation
 */
void test_wave_atom_get_float (void);

/**
 * \brief Test wave_atom_get_char().
 * \test wave_atom_get_char()
 * \todo implementation
 */
void test_wave_atom_get_char (void);

/**
 * \brief Test wave_atom_get_bool().
 * \test wave_atom_get_bool()
 * \todo implementation
 */
void test_wave_atom_get_bool (void);

/**
 * \brief Test wave_atom_get_string().
 * \test wave_atom_get_string()
 * \todo implementation
 */
void test_wave_atom_get_string (void);

/**
 * \brief Test wave_atom_get_operator().
 * \test wave_atom_get_operator()
 * \todo implementation
 */
void test_wave_atom_get_operator (void);

/**
 * \brief Test wave_atom_get_path().
 * \test wave_atom_get_path()
 * \todo implementation
 */
void test_wave_atom_get_path (void);

////////////////////////////////////////////////////////////////////////////////
// Setters tests.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Test wave_atom_set_int().
 * \test wave_atom_set_int()
 * \todo implementation
 */
void test_wave_atom_set_int (void);

/**
 * \brief Test wave_atom_set_float().
 * \test wave_atom_set_float()
 * \todo implementation
 */
void test_wave_atom_set_float (void);

/**
 * \brief Test wave_atom_set_bool().
 * \test wave_atom_set_bool()
 * \todo implementation
 */
void test_wave_atom_set_bool (void);

/**
 * \brief Test wave_atom_set_char().
 * \test wave_atom_set_char()
 * \todo implementation
 */
void test_wave_atom_set_char (void);

/**
 * \brief Test wave_atom_set_string().
 * \test wave_atom_set_string()
 * \todo implementation
 */
void test_wave_atom_set_string (void);

/**
 * \brief Test wave_atom_set_path().
 * \test wave_atom_set_path()
 * \todo implementation
 */
void test_wave_atom_set_path (void);

/**
 * \brief Test wave_atom_set_operator().
 * \test wave_atom_set_operator()
 * \todo implementation
 */
void test_wave_atom_set_operator (void);

#endif /* __TEST_WAVE_ATOM_H__ */
