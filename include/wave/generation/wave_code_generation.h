/**
 * \file wave_code_generation.h
 * \brief Wave code generation.
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
#ifndef __WAVE_CODE_GENERATION_H
#define __WAVE_CODE_GENERATION_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "wave/common/wave_types.h"
#include "wave/ast/wave_phrase.h"
#include "wave/generation/wave_headers.h"
#include "wave/generation/wave_generation_common.h"
#include "wave/generation/wave_generation_atom.h"
#include "wave/generation/wave_generation_curly.h"

/**
 * \brief Generate C source code giving a wave AST.
 * \param output_file The file where the C code will be written.
 * \param phrases The structure containing the AST for the wave language.
 * \pre output_file and phrases must not be NULL.
 * \relatesalso wave_phrase
 * \note  Collections in phrases must have already been indexed.
 */
void wave_code_generation_generate (FILE * output_file, const wave_phrase * phrases);

/**
 * \brief Generate C source code giving a collection.
 * \param output_file The file where the C code will be written.
 * \param collection The collection to translate into C code.
 * \pre output_file and collection must not be NULL.
 * \relatesalso wave_collection
 * \note  Collections in phrases must have already been indexed.
 */
void wave_code_generation_collection (FILE * const code_file, FILE * const alloc_file, const wave_collection * collection);

#endif // ( __WAVE_CODE_GENERATION_H )
