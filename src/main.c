/**
 * \file main.c
 * \brief Main.
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
#include <stdlib.h>
#include <stdio.h>
#include <sysexits.h>

#include "wave_compiler_version.h"

/**
 * \brief Main.
 * \param argc Command line arguments number.
 * \param argv Command line arguments.
 * \return Exit code.
 */
int main (int argc, char ** argv)
{
    if (argc > 1)
    {
        fprintf (stderr, "Too many arguments.\n");
        fprintf (stderr, "Usage: %s\n", argv[0]);
        exit (EX_USAGE);
    }

    printf
    (
        "Wave compiler, version %d.%d.%d\n",
        WAVE_COMPILER_VERSION_MAJOR,
        WAVE_COMPILER_VERSION_MINOR,
        WAVE_COMPILER_VERSION_PATCH
    );

    return 0;
}
