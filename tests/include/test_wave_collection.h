/**
 * \file test_wave_collection.h
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
#ifndef __TEST_WAVE_COLLECTION_H__
#define __TEST_WAVE_COLLECTION_H__

#include <CUnit/CUnit.h>

#include "wave_collection.h"

////////////////////////////////////////////////////////////////////////////////
// Suite related functions.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief wave_collection test suite initialization.
 * \return Success or error code.
 * \todo implementation
 */
int test_wave_collection_suite_init (void);

/**
 * \brief wave_collection test suite cleaning.
 * \return Success or error code.
 * \todo implementation
 */
int test_wave_collection_suite_clean (void);

////////////////////////////////////////////////////////////////////////////////
// Allocation, free tests.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Test wave_collection_allocator().
 * \test wave_collection_allocator()
 * \todo implementation
 */
void test_wave_collection_allocator (void);

/**
 * \brief Test wave_collection_free().
 * \test wave_collection_free()
 * \todo implementation
 */
void test_wave_collection_free (void);

////////////////////////////////////////////////////////////////////////////////
// Getters tests.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Test wave_collection_has_next().
 * \test wave_collection_has_next()
 * \todo implementation
 */
void test_wave_collection_has_next (void);

/**
 * \brief Test wave_collection_get_type().
 * \test wave_collection_get_type()
 * \todo implementation
 */
void test_wave_collection_get_type (void);

/**
 * \brief Test wave_collection_get_atom().
 * \test wave_collection_get_atom()
 * \todo implementation
 */
void test_wave_collection_get_atom (void);

/**
 * \brief Test wave_collection_get_list().
 * \test wave_collection_get_list()
 * \todo implementation
 */
void test_wave_collection_get_list (void);

/**
 * \brief Test wave_collection_get_repetition_list().
 * \test wave_collection_get_repetition_list()
 * \todo implementation
 */
void test_wave_collection_get_repetition_list (void);

/**
 * \brief Test wave_collection_get_repetition_path().
 * \test wave_collection_get_repetition_path()
 * \todo implementation
 */
void test_wave_collection_get_repetition_path (void);

/**
 * \brief Test wave_collection_get_cyclic_list().
 * \test wave_collection_get_cyclic_list()
 * \todo implementation
 */
void test_wave_collection_get_cyclic_list (void);

/**
 * \brief Test wave_collection_get_cyclic_cycle().
 * \test wave_collection_get_cyclic_cycle()
 * \todo implementation
 */
void test_wave_collection_get_cyclic_cycle (void);

/**
 * \brief Test wave_collection_get_next().
 * \test wave_collection_get_next()
 * \todo implementation
 */
void test_wave_collection_get_next (void);

////////////////////////////////////////////////////////////////////////////////
// Setters tests.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Test wave_collection_add_collection().
 * \test wave_collection_add_collection()
 * \todo implementation
 */
void test_wave_collection_add_collection (void);

/**
 * \brief Test wave_collection_set_type().
 * \test wave_collection_set_type()
 * \todo implementation
 */
void test_wave_collection_set_type (void);

/**
 * \brief Test wave_collection_set_atom().
 * \test wave_collection_set_atom()
 * \todo implementation
 */
void test_wave_collection_set_atom (void);

/**
 * \brief Test wave_collection_set_list().
 * \test wave_collection_set_list()
 * \todo implementation
 */
void test_wave_collection_set_list (void);

/**
 * \brief Test wave_collection_set_repetition_list().
 * \test wave_collection_set_repetition_list()
 * \todo implementation
 */
void test_wave_collection_set_repetition_list (void);

/**
 * \brief Test wave_collection_set_repetition_path().
 * \test wave_collection_set_repetition_path()
 * \todo implementation
 */
void test_wave_collection_set_repetition_path (void);

/**
 * \brief Test wave_collection_set_cyclic_list().
 * \test wave_collection_set_cyclic_list()
 * \todo implementation
 */
void test_wave_collection_set_cyclic_list (void);

/**
 * \brief Test wave_collection_set_cyclic_cyle()
 * \test wave_collection_set_cyclic_cycle()
 * \todo implementation
 */
void test_wave_collection_set_cyclic_cycle (void);

#endif /* __TEST_WAVE_COLLECTION_H__ */
