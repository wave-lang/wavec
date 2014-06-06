/**
 * \file unit_tests.c
 * \brief Unit tests.
 * \author razanajato ranaivoarivony harenome
 * \date 2014
 * \copyright mit license
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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <CUnit/Console.h>
#include <CUnit/CUCurses.h>

#include "wave_test_suites.h"

/**
 * \brief Main.
 */
int main (int argc, char ** argv)
{
    CU_ErrorCode error = CU_initialize_registry ();

    if (error != CUE_SUCCESS)
        return CU_get_error ();

    error = CU_register_suites (wave_test_suites);

    if (error == CUE_SUCCESS)
    {
        if (argc == 1)
        {
            CU_basic_set_mode (CU_BRM_VERBOSE);
            CU_basic_run_tests ();
        }
        else
        {
            CU_console_run_tests ();
        }
    }

    CU_cleanup_registry ();

    return CU_get_error ();
}
