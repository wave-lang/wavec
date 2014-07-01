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
#include "wave/generation/wave_generation_common.h"

const char * const _atom_type_strings[] =
{
    [WAVE_ATOM_LITERAL_INT] = "int",
    [WAVE_ATOM_LITERAL_FLOAT] = "float",
    [WAVE_ATOM_LITERAL_BOOL] = "bool",
    [WAVE_ATOM_LITERAL_CHAR] = "char",
    [WAVE_ATOM_LITERAL_STRING] = "string",
    [WAVE_ATOM_OPERATOR] = "",
    [WAVE_ATOM_PATH] = "",
    [WAVE_ATOM_UNKNOWN] = "",
};

static const char * const _atom_type_data_strings[] =
{
    [WAVE_ATOM_LITERAL_INT] = "WAVE_DATA_INT",
    [WAVE_ATOM_LITERAL_FLOAT] = "WAVE_DATA_FLOAT",
    [WAVE_ATOM_LITERAL_BOOL] = "WAVE_DATA_BOOL",
    [WAVE_ATOM_LITERAL_CHAR] = "WAVE_DATA_CHAR",
    [WAVE_ATOM_LITERAL_STRING] = "WAVE_DATA_STRING",
};

void wave_code_generate_error (FILE * file, const char * error_message)
{
    fprintf (file, "fprintf (stderr, \"Error: %s\\n\");\nexit(1);\n", error_message);
}

void wave_code_generation_fprint_tab_with_init(FILE* file, const wave_int_list* list, const wave_coordinate * coord ,const char* struct_field){
    fprintf(file, "wave_tab");
    wave_int_list_fprint(file, list);
    fprintf(file, "[");
    wave_coordinate_fprint(file, coord);
    fprintf(file, "]%s", struct_field);
}

void wave_generate_content_assignement (FILE * const code_file, const wave_int_list * const list, const wave_coordinate * const c, wave_atom_type t)
{
    wave_code_generation_fprint_tab_with_init(code_file, list, c, "._content.");
    fprintf (code_file, "_%s", wave_generation_atom_type_string (t));
}

void wave_generate_type_assignement (FILE * const code_file, const wave_int_list * const list, const wave_coordinate * const c, wave_atom_type t)
{
    wave_code_generation_fprint_tab_with_init(code_file, list, c, "._type = ");
    fprintf (code_file, "%s;\n", _atom_type_data_strings[t]);
}

const char * wave_generation_atom_type_string (wave_atom_type t)
{
    return _atom_type_strings[t];
}

const char * wave_generation_atom_type_data_string (wave_atom_type t)
{
    return _atom_type_data_strings[t];
}
