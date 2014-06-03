/**
 * \file test_wave_path.h
 * \brief Wave path tests.
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
#ifndef __TEST_WAVE_PATH_H__
#define __TEST_WAVE_PATH_H__

#include <CUnit/CUnit.h>

#include "wave_path.h"

////////////////////////////////////////////////////////////////////////////////
// Suite related functions.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief wave_path test suite initialization.
 * \return Success or error code.
 * \todo implementation
 */
int test_wave_path_suite_init (void);

/**
 * \brief wave_path test suite cleaning.
 * \return Success or error code.
 * \todo implementation
 */
int test_wave_path_suite_clean (void);

////////////////////////////////////////////////////////////////////////////////
// Allocation and free tests.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Test wave_path_allocator().
 * \test wave_path_allocator()
 * \todo implementation
 */
void test_wave_path_allocator (void);

/**
 * \brief Test wave_path_free().
 * \test wave_path_free()
 * \todo implementation
 */
void test_wave_path_free (void);

////////////////////////////////////////////////////////////////////////////////
// Getters tests.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Test wave_path_has_next().
 * \test wave_path_has_next()
 * \todo implementation
 */
void test_wave_path_has_next (void);

/**
 * \brief Tet wave_path_get_move().
 * \test wave_path_get_move()
 * \todo implementation
 */
void test_wave_path_get_move (void);

/**
 * \brief Test wave_path_get_part().
 * \test wave_path_get_part()
 * \todo implementation
 */
void test_wave_path_get_part (void);

/**
 * \brief Test wave_path_get_repeat_type().
 * \test wave_path_get_repeat_type()
 * \todo implementation
 */
void test_wave_path_get_repeat_type (void);

/**
 * \brief Test wave_path_get_repeat_number().
 * \test wave_path_get_repeat_number()
 * \todo implementation
 */
void test_wave_path_get_repeat_number (void);

/**
 * \brief Test wave_path_get_repeat_path().
 * \test wave_path_get_repeat_path()
 * \todo implementation
 */
void test_wave_path_get_repeat_path (void);

/**
 * \brief Test wave_path_get_next().
 * \test wave_path_get_next()
 * \todo implementation
 */
void test_wave_path_get_next (void);

////////////////////////////////////////////////////////////////////////////////
// Setters tests.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Test wave_path_set_move().
 * \test wave_path_set_move()
 * \todo implementation
 */
void test_wave_path_set_move (void);

/**
 * \brief Test wave_path_add_path().
 * \test wave_path_add_path()
 * \todo implementation
 */
void test_wave_path_add_path (void);

/**
 * \brief Test wave_path_set_part().
 * \test wave_path_set_part()
 * \todo implementation
 */
void test_wave_path_set_part (void);

/**
 * \brief Test wave_path_set_repeat_type().
 * \test wave_path_set_repeat_path()
 * \todo implementation
 */
void test_wave_path_set_repeat_type (void);

/**
 * \brief Test wave_path_set_repeat_number().
 * \test wave_path_set_repeat_number()
 * \todo implementation
 */
void test_wave_path_set_repeat_number (void);

/**
 * \brief Test wave_path_set_repeat_path().
 * \test wave_path_set_repeat_path()
 * \todo implementation
 */
void test_wave_path_set_repeat_path (void);

#endif /* __TEST_WAVE_PATH_H__ */
