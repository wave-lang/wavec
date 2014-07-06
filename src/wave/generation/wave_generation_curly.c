/**
 * \file wave_generation_curly.h
 * \brief Wave code generation, curly.
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
#include "wave/generation/wave_generation_curly.h"

/**
 * \brief Curly “stack”.
 */
static unsigned long long int _curly_count = 0;

void fprintf_closing_curly (FILE * stream, unsigned long long int number)
{
    for (unsigned long long int i = 0; i < number; ++i)
        fprintf (stream, "}\n");
}

void wave_generate_stack_curly (void)
{
    _curly_count++;
}

void wave_generate_flush_curly (FILE * stream)
{
    fprintf_closing_curly (stream, _curly_count);
    _curly_count = 0;
}

unsigned long long int wave_generate_backup_curly (void)
{
    return _curly_count;
}

void wave_generate_restore_curly (unsigned long long int count)
{
    _curly_count = count;
}
