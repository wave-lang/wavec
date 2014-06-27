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
#ifndef __WAVE_GENERATION_COMMON_H__
#define __WAVE_GENERATION_COMMON_H__

#include "wave/common/wave_types.h"
#include "wave/ast/wave_atom.h"
#include "wave/ast/wave_int_list.h"
#include "wave/ast/wave_coordinate.h"

void wave_code_generation_fprint_tab_with_init(FILE* file, const wave_int_list* list, const wave_coordinate * coord ,const char* struct_field);

void wave_generate_content_assignement (FILE * const code_file, const wave_int_list * const list, const wave_coordinate * const c, wave_atom_type t);

void wave_generate_type_assignement (FILE * const code_file, const wave_int_list * const list, const wave_coordinate * const c, wave_atom_type t);

const char * wave_generation_atom_type_string (wave_atom_type t);
const char * wave_generation_atom_type_data_string (wave_atom_type t);

#endif /* __WAVE_GENERATION_COMMON_H__ */
