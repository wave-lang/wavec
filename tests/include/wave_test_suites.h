/**
 * \file wave_test_suites.h
 * \brief Wave test suites.
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
#ifndef __WAVE_TEST_SUITES_H__
#define __WAVE_TEST_SUITES_H__

#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>

#include "test_wave_path.h"
#include "test_wave_atom.h"
#include "test_wave_collection.h"

/**
 * \brief Test suite for wave_path.
 */
static CU_TestInfo test_wave_path_info [] =
{
    { "Test wave_path_init",                test_wave_path_init                 },
    { "Test wave_path_alloc",               test_wave_path_alloc                },
    { "Test wave_path_free",                test_wave_path_free                 },
    { "Test wave_path_has_next",            test_wave_path_has_next             },
    { "Test wave_path_has_previous",        test_wave_path_has_previous         },
    { "Test wave_path_get_move",            test_wave_path_get_move             },
    { "Test wave_path_get_part",            test_wave_path_get_part             },
    { "Test wave_path_get_repeat_type",     test_wave_path_get_repeat_type      },
    { "Test wave_path_get_repeat_number",   test_wave_path_get_repeat_number    },
    { "Test wave_path_get_repeat_path",     test_wave_path_get_repeat_path      },
    { "Test wave_path_get_next",            test_wave_path_get_next             },
    { "Test wave_path_set_move",            test_wave_path_set_move             },
    { "Test wave_path_add_path",            test_wave_path_add_path             },
    { "Test wave_path_set_part",            test_wave_path_set_part             },
    { "Test wave_path_set_repeat_type",     test_wave_path_set_repeat_type      },
    { "Test wave_path_set_repeat_number",   test_wave_path_set_repeat_number    },
    { "Test wave_path_set_repeat_path",     test_wave_path_set_repeat_path      },
    CU_TEST_INFO_NULL,
};

/**
 * \brief Test suite for wave_atom.
 */
static CU_TestInfo test_wave_atom_info [] =
{
    { "Test wave_atom_alloc",           test_wave_atom_alloc            },
    { "Test wave_atom_free",            test_wave_atom_free             },
    { "Test wave_atom_get_type",        test_wave_atom_get_type         },
    { "Test wave_atom_get_int",         test_wave_atom_get_int          },
    { "Test wave_atom_get_float",       test_wave_atom_get_float        },
    { "Test wave_atom_get_char",        test_wave_atom_get_char         },
    { "Test wave_atom_get_bool",        test_wave_atom_get_bool         },
    { "Test wave_atom_get_string",      test_wave_atom_get_string       },
    { "Test wave_atom_get_operator",    test_wave_atom_get_operator     },
    { "Test wave_atom_get_path",        test_wave_atom_get_path         },
    { "Test wave_atom_set_int",         test_wave_atom_set_int          },
    { "Test wave_atom_set_float",       test_wave_atom_set_float        },
    { "Test wave_atom_set_bool",        test_wave_atom_set_bool         },
    { "Test wave_atom_set__char",       test_wave_atom_set_char         },
    { "Test wave_atom_set_string",      test_wave_atom_set_string       },
    { "Test wave_atom_set_path",        test_wave_atom_set_path         },
    { "Test wave_atom_set_operator",    test_wave_atom_set_operator     },
    CU_TEST_INFO_NULL,
};

/**
 * \brief Test suite for wave_collection.
 */
static CU_TestInfo test_wave_collection_info [] =
{
    { "Test wave_collection_alloc",                 test_wave_collection_alloc                },
    { "Test wave_collection_free",                  test_wave_collection_free                 },
    { "Test wave_collection_has_next",              test_wave_collection_has_next             },
    { "Test wave_collection_get_type",              test_wave_collection_get_type             },
    { "Test wave_collection_get_atom",              test_wave_collection_get_atom             },
    { "Test wave_collection_get_list",              test_wave_collection_get_list             },
    { "Test wave_collection_get_repetition_list",   test_wave_collection_get_repetition_list  },
    { "Test wave_collection_get_repetition_path",   test_wave_collection_get_repetition_path  },
    { "Test wave_collection_get_cyclic_list",       test_wave_collection_get_cyclic_list      },
    { "Test wave_collection_get_cyclic_cycle",      test_wave_collection_get_cyclic_cycle     },
    { "Test wave_collection_get_next",              test_wave_collection_get_next             },
    { "Test wave_collection_add_collection",        test_wave_collection_add_collection       },
    { "Test wave_collection_set_type",              test_wave_collection_set_type             },
    { "Test wave_collection_set_atom",              test_wave_collection_set_atom             },
    { "Test wave_collection_set_list",              test_wave_collection_set_list             },
    { "Test wave_collection_set_repetition_list",   test_wave_collection_set_repetition_list  },
    { "Test wave_collection_set_repetition_path",   test_wave_collection_set_repetition_path  },
    { "Test wave_collection_set_cyclic_list",       test_wave_collection_set_cyclic_list      },
    { "Test wave_collection_set_cyclic_cycle",      test_wave_collection_set_cyclic_cycle     },
    CU_TEST_INFO_NULL,
};

/**
 * \brief Test suites.
 */
static CU_SuiteInfo wave_test_suites [] =
{
    { "Test wave_path", test_wave_path_suite_init, test_wave_path_suite_clean, test_wave_path_suite_test_setup, test_wave_path_suite_test_teardown, test_wave_path_info },
    { "Test wave_atom", test_wave_atom_suite_init, test_wave_atom_suite_clean, NULL, NULL, test_wave_atom_info },
    { "Test wave_collection", test_wave_collection_suite_init, test_wave_collection_suite_clean, NULL, NULL, test_wave_collection_info },
    CU_SUITE_INFO_NULL,
};

#endif /* __WAVE_TEST_SUITES_H__ */
