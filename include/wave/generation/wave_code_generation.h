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

#include <stdio.h>
#include <stdbool.h>

#include "wave/common/wave_types.h"
#include "wave/ast/wave_phrase.h"
#include "wave/generation/wave_headers.h"

/**
 * \brief Generate C source code giving a collection.
 * \param output_file The file where the C code will be written.
 * \param collection The collection to translate into C code.
 * \pre output_file and collection must not be NULL.
 * \relatesalso wave_collection
 * \note  Collections in phrases must have already been indexed.
 */
void wave_code_generation_collection(FILE* code_file, FILE * alloc_file, const wave_collection* collection);

static inline void file_cat (FILE * destination, FILE * source)
{
    bool end = false;
    char buffer[2048];

    while (! end)
    {
        int count = 0;
        fscanf (source, "%2047c%n", buffer, & count);
        end = count == 0;

        if (! end)
        {
            buffer[count] = '\0';
            fprintf (destination, "%s", buffer);
        }
    }
}

static inline void _current_phrase (FILE * output, wave_phrase * p, unsigned int phrase_count)
{
    fprintf (output, "void phrase_%d (void)\n{\n", phrase_count);
    FILE * code_file = tmpfile ();
    FILE * alloc_file = tmpfile ();

    wave_collection* collection = wave_phrase_get_collection(p);
    wave_collection_compute_indexes(collection);
    wave_collection_compute_length_and_coords(collection);
    wave_code_generation_collection(code_file, alloc_file, collection);

    fseek (alloc_file, 0, SEEK_SET);
    fseek (code_file, 0, SEEK_SET);

    file_cat (output, alloc_file);
    file_cat (output, code_file);

    fclose (code_file);
    fclose (alloc_file);
    fprintf (output, "}\n");
}

/**
 * \brief Generate C source code giving a wave AST.
 * \param output_file The file where the C code will be written.
 * \param phrases The structure containing the AST for the wave language.
 * \pre output_file and phrases must not be NULL.
 * \relatesalso wave_phrase
 * \note  Collections in phrases must have already been indexed.
 */
static inline void wave_code_generation_generate(FILE* output_file, wave_phrase* phrases){
    wave_code_generation_fprintf_headers (output_file);
    unsigned int count = 0;
    do{
        _current_phrase (output_file, phrases, count++);
    }
    while( wave_phrase_has_next(phrases) && ( phrases = wave_phrase_get_next(phrases) ) );
    fprintf (output_file, "int main(void)\n{\n");
    for (unsigned int i = 0; i < count; ++i)
        fprintf (output_file, "phrase_%d ();\n", i);
    fprintf (output_file, "return 0;\n}\n");
}

#endif // ( __WAVE_CODE_GENERATION_H )
