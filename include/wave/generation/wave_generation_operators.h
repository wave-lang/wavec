/**
 * \file wave_generation_operators.h
 * \brief Wave code generation for operators.
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
#ifndef __WAVE_GENERATION_OPERATORS_H__
#define __WAVE_GENERATION_OPERATORS_H__

#include <stdio.h>
#include <stdbool.h>

#include "wave/common/wave_types.h"
#include "wave/common/wave_operator.h"
#include "wave/ast/wave_collection.h"
#include "wave/generation/wave_generation_common.h"

/**
 * \brief Generate C source code giving an operator atom.
 * \param code_file The file where the C code will be written.
 * \param collection The collection containing the value.
 * \pre code_file and collection must not be NULL.
 * \relatesalso wave_atom
 * \relatesalso wave_collection_info
 */
void wave_code_generation_fprint_operator (FILE * code_file, const wave_collection * collection);

#endif /* __WAVE_GENERATION_OPERATORS_H__ */
