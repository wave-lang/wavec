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
#ifndef __WAVE_GENERATION_CURLY_H__
#define __WAVE_GENERATION_CURLY_H__

#include <stdlib.h>
#include <stdio.h>

/**
 * \brief Print closing curlys to a stream..
 * \param stream Stream.
 * \param number Requested number of curlys.
 */
void fprintf_closing_curly (FILE * stream, unsigned long long int number);

/**
 * \brief Add a curly to the curly stack.
 */
void wave_generate_stack_curly (void);

/**
 * \brief Flush the curly stack to a stream.
 */
void wave_generate_flush_curly (FILE * stream);

/**
 * \brief Backup the current curly stack.
 * \return Current curly stack.
 */
unsigned long long int wave_generate_backup_curly (void);

/**
 * \brief Restore a curly stack.
 * \param count Previous curly stack.
 */
void wave_generate_restore_curly (unsigned long long int count);

#endif /* __WAVE_GENERATION_CURLY_H__ */
