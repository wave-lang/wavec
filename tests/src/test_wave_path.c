/**
 * \file test_wave_path.c
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
#include "test_wave_path.h"

////////////////////////////////////////////////////////////////////////////////
// Static variables.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Number of paths for the tests.
 */
#define WAVE_PATH_NUMBER 12
static bool must_free_paths = true;
static wave_path * paths[WAVE_PATH_NUMBER];
static wave_move_type WAVE_MOVES[] =
{
    WAVE_MOVE_UP,
    WAVE_MOVE_DOWN,
    WAVE_MOVE_PRE,
    WAVE_MOVE_SUC,
    WAVE_MOVE_REWIND,
    WAVE_MOVE_PART,
    WAVE_MOVE_REP,
    WAVE_MOVE_UNKNOWN,
};

////////////////////////////////////////////////////////////////////////////////
// Suite related functions.
////////////////////////////////////////////////////////////////////////////////

void test_wave_path_suite_test_setup (void)
{
    for (unsigned int i = 0; i < WAVE_PATH_NUMBER; ++i)
        paths[i] = malloc (sizeof * paths[i]);

    * paths[0] = (wave_path) { ._move = WAVE_MOVE_UP, ._previous_path = NULL, ._next_path = paths[1] };
    * paths[1] = (wave_path) { ._move = WAVE_MOVE_PRE, ._previous_path = paths[0], ._next_path = paths[2] };
    * paths[2] = (wave_path) { ._move = WAVE_MOVE_DOWN,._previous_path = paths[1],  ._next_path = paths[3] };
    * paths[3] = (wave_path) { ._move = WAVE_MOVE_SUC, ._previous_path = paths[2], ._next_path = paths[4] };
    * paths[4] = (wave_path) { ._move = WAVE_MOVE_SUC, ._previous_path = paths[3], ._next_path = NULL };

    * paths[5] = (wave_path) { ._move = WAVE_MOVE_UP, ._previous_path = NULL, ._next_path = paths[6] };
    * paths[6] = (wave_path) {
        ._move = WAVE_MOVE_REP,
        ._complex_move._repeat =
        {
            ._type = WAVE_PATH_REPEAT_CONSTANT,
            ._number = 10,
            ._path = paths[7]
        },
        ._previous_path = paths[5],
        ._next_path = paths[9]
    };
    * paths[7] = (wave_path) { ._move = WAVE_MOVE_UP, ._previous_path = NULL, ._next_path = paths[8] };
    * paths[8] = (wave_path) { ._move = WAVE_MOVE_DOWN, ._previous_path = paths[7], ._next_path = NULL };
    * paths[9] = (wave_path) { ._move = WAVE_MOVE_UP, ._previous_path = paths[6], ._next_path = NULL };
    * paths[10] = (wave_path) { ._move = WAVE_MOVE_PART, ._complex_move._part = paths[0], ._previous_path = NULL, ._next_path = NULL };
    * paths[11] = (wave_path) { ._move = WAVE_MOVE_REWIND, ._previous_path = NULL, ._next_path = NULL };
}

void test_wave_path_suite_test_teardown (void)
{
    if (must_free_paths)
        for (unsigned int i = 0; i < WAVE_PATH_NUMBER; ++i)
            free (paths[i]);
    must_free_paths = true;
}

int test_wave_path_suite_init (void)
{
    return 0;
}

int test_wave_path_suite_clean (void)
{
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
// Initialization tests.
////////////////////////////////////////////////////////////////////////////////

void test_wave_path_init (void)
{
    wave_path w;
    wave_path_init (& w);

    CU_ASSERT_EQUAL (w._move, WAVE_MOVE_UNKNOWN);
    CU_ASSERT_PTR_NULL (w._next_path);
    CU_ASSERT_PTR_NULL (w._previous_path);
}

////////////////////////////////////////////////////////////////////////////////
// Allocation and free tests.
////////////////////////////////////////////////////////////////////////////////

void test_wave_path_alloc (void)
{
    wave_path * w = wave_path_alloc ();
    CU_ASSERT_PTR_NOT_NULL (w);
    free (w);
}

void test_wave_path_free (void)
{
    CU_ASSERT_PTR_NULL (wave_path_free (paths[0]))
    CU_ASSERT_PTR_NULL (wave_path_free (paths[5]))
    must_free_paths = false;
}

////////////////////////////////////////////////////////////////////////////////
// Getters tests.
////////////////////////////////////////////////////////////////////////////////

void test_wave_path_has_next (void)
{
    CU_ASSERT_TRUE (wave_path_has_next (paths[0]))
    CU_ASSERT_TRUE (wave_path_has_next (paths[1]))
    CU_ASSERT_TRUE (wave_path_has_next (paths[2]))
    CU_ASSERT_TRUE (wave_path_has_next (paths[3]))
    CU_ASSERT_FALSE (wave_path_has_next (paths[4]))

    CU_ASSERT_TRUE (wave_path_has_next (paths[5]))
    CU_ASSERT_TRUE (wave_path_has_next (paths[6]))
    CU_ASSERT_TRUE (wave_path_has_next (paths[7]))
    CU_ASSERT_FALSE (wave_path_has_next (paths[8]))
    CU_ASSERT_FALSE (wave_path_has_next (paths[9]))
    CU_ASSERT_FALSE (wave_path_has_next (paths[10]))
    CU_ASSERT_FALSE (wave_path_has_next (paths[11]))
}

void test_wave_path_has_previous (void)
{
    CU_ASSERT_FALSE (wave_path_has_previous (paths[0]))
    CU_ASSERT_TRUE (wave_path_has_previous (paths[1]))
    CU_ASSERT_TRUE (wave_path_has_previous (paths[2]))
    CU_ASSERT_TRUE (wave_path_has_previous (paths[3]))
    CU_ASSERT_TRUE (wave_path_has_previous (paths[4]))

    CU_ASSERT_FALSE (wave_path_has_previous (paths[5]))
    CU_ASSERT_TRUE (wave_path_has_previous (paths[6]))
    CU_ASSERT_FALSE (wave_path_has_previous (paths[7]))
    CU_ASSERT_TRUE (wave_path_has_previous (paths[8]))
    CU_ASSERT_TRUE (wave_path_has_previous (paths[9]))
    CU_ASSERT_FALSE (wave_path_has_previous (paths[10]))
    CU_ASSERT_FALSE (wave_path_has_previous (paths[11]))
}

void test_wave_path_get_move (void)
{
    CU_ASSERT_EQUAL (wave_path_get_move (paths[0]), WAVE_MOVE_UP)
    CU_ASSERT_EQUAL (wave_path_get_move (paths[1]), WAVE_MOVE_PRE)
    CU_ASSERT_EQUAL (wave_path_get_move (paths[2]), WAVE_MOVE_DOWN)
    CU_ASSERT_EQUAL (wave_path_get_move (paths[3]), WAVE_MOVE_SUC)
    CU_ASSERT_EQUAL (wave_path_get_move (paths[4]), WAVE_MOVE_SUC)

    CU_ASSERT_EQUAL (wave_path_get_move (paths[5]), WAVE_MOVE_UP)
    CU_ASSERT_EQUAL (wave_path_get_move (paths[6]), WAVE_MOVE_REP)
    CU_ASSERT_EQUAL (wave_path_get_move (paths[7]), WAVE_MOVE_UP)
    CU_ASSERT_EQUAL (wave_path_get_move (paths[8]), WAVE_MOVE_DOWN)
    CU_ASSERT_EQUAL (wave_path_get_move (paths[9]), WAVE_MOVE_UP)
    CU_ASSERT_EQUAL (wave_path_get_move (paths[10]), WAVE_MOVE_PART)
    CU_ASSERT_EQUAL (wave_path_get_move (paths[11]), WAVE_MOVE_REWIND)
}

void test_wave_path_get_part (void)
{
    CU_ASSERT_EQUAL (wave_path_get_part (paths[10]), paths[0])
}

void test_wave_path_get_repeat_type (void)
{
    CU_ASSERT_EQUAL (wave_path_get_repeat_type (paths[6]), WAVE_PATH_REPEAT_CONSTANT)
}

void test_wave_path_get_repeat_number (void)
{
    CU_ASSERT_EQUAL (wave_path_get_repeat_number (paths[6]), 10)
}

void test_wave_path_get_repeat_path (void)
{
    CU_ASSERT_PTR_EQUAL (wave_path_get_repeat_path (paths[6]), paths[7])
}

void test_wave_path_get_next (void)
{
    CU_ASSERT_PTR_EQUAL (wave_path_get_next (paths[0]), paths[1])
    CU_ASSERT_PTR_EQUAL (wave_path_get_next (paths[1]), paths[2])
    CU_ASSERT_PTR_EQUAL (wave_path_get_next (paths[2]), paths[3])
    CU_ASSERT_PTR_EQUAL (wave_path_get_next (paths[3]), paths[4])
    CU_ASSERT_PTR_NULL (wave_path_get_next (paths[4]))
    CU_ASSERT_PTR_EQUAL (wave_path_get_next (paths[5]), paths[6])
    CU_ASSERT_PTR_EQUAL (wave_path_get_next (paths[6]), paths[9])
    CU_ASSERT_PTR_EQUAL (wave_path_get_next (paths[7]), paths[8])
    CU_ASSERT_PTR_NULL (wave_path_get_next (paths[8]))
    CU_ASSERT_PTR_NULL (wave_path_get_next (paths[9]))
    CU_ASSERT_PTR_NULL (wave_path_get_next (paths[10]))
}


////////////////////////////////////////////////////////////////////////////////
// Setters tests.
////////////////////////////////////////////////////////////////////////////////

void test_wave_path_set_move (void)
{
    for (int i = 0; WAVE_MOVES[i] != WAVE_MOVE_UNKNOWN; ++i)
    {
        wave_path_set_move (paths[0], WAVE_MOVES[i]);
        CU_ASSERT_EQUAL (paths[0]->_move, WAVE_MOVES[i])
    }
}

void test_wave_path_add_path (void)
{
    wave_path p[2];

    wave_path_init (& p[0]);
    wave_path_init (& p[1]);
    wave_path_add_path(& p[0], & p[1]);

    CU_ASSERT_TRUE (wave_path_has_next (& p[0]))
    CU_ASSERT_TRUE (wave_path_has_previous (& p[1]))
    CU_ASSERT_FALSE (wave_path_has_previous (& p[0]))
    CU_ASSERT_FALSE (wave_path_has_next (& p[1]))
}

void test_wave_path_set_part (void)
{
    wave_path p[4];
    wave_path_init (& p[0]);
    wave_path_init (& p[1]);
    wave_path_init (& p[2]);
    wave_path_init (& p[3]);
    wave_path_add_path (& p[1], & p[2]);
    wave_path_add_path (& p[1], & p[3]);
    wave_path_set_move (& p[1], WAVE_MOVE_UP);
    wave_path_set_move (& p[2], WAVE_MOVE_PRE);
    wave_path_set_move (& p[3], WAVE_MOVE_DOWN);
    wave_path_set_part (& p[0], & p[1]);

    CU_ASSERT_FALSE (wave_path_has_next (& p[0]))
    CU_ASSERT_FALSE (wave_path_has_previous (& p[0]))
    CU_ASSERT_EQUAL (wave_path_get_move (& p[0]), WAVE_MOVE_PART)
    CU_ASSERT_PTR_EQUAL (wave_path_get_part (& p[0]), & p[1])
}

void test_wave_path_set_repeat_type (void)
{
    wave_path p[2];
    wave_path_init (& p[0]);
    wave_path_init (& p[1]);

    wave_path_set_repeat_type (& p[0], WAVE_PATH_REPEAT_CONSTANT);
    wave_path_set_repeat_type (& p[1], WAVE_PATH_REPEAT_INFINITE);

    CU_ASSERT_EQUAL (wave_path_get_move (& p[0]), WAVE_MOVE_REP)
    CU_ASSERT_EQUAL (wave_path_get_repeat_type (& p[0]), WAVE_PATH_REPEAT_CONSTANT)
    CU_ASSERT_EQUAL (wave_path_get_move (& p[1]), WAVE_MOVE_REP)
    CU_ASSERT_EQUAL (wave_path_get_repeat_type (& p[1]), WAVE_PATH_REPEAT_INFINITE)
}

void test_wave_path_set_repeat_number (void)
{
    wave_path p;
    wave_path_init (& p);
    wave_path_set_repeat_number (& p, 10);

    CU_ASSERT_EQUAL (wave_path_get_move (& p), WAVE_MOVE_REP)
    CU_ASSERT_EQUAL (wave_path_get_repeat_type (& p), WAVE_PATH_REPEAT_CONSTANT)
    CU_ASSERT_EQUAL (wave_path_get_repeat_number (& p), 10)
}

void test_wave_path_set_repeat_path (void)
{
    wave_path p;
    wave_path_init (& p);
    wave_path_set_repeat_path (& p, paths[0]);

    CU_ASSERT_EQUAL (wave_path_get_move (& p), WAVE_MOVE_REP)
    CU_ASSERT_PTR_EQUAL (wave_path_get_repeat_path (& p), paths[0])
}
