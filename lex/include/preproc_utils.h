/*
   The MIT License (MIT)

   Copyright (c) 2014 Éric VIOLARD, Maxime SCHMITT, Harenome RAZANAJATO RANAIVOARIVONY

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
   */

#ifndef __PREPROC_BUFFER_H
#define __PREPROC_BUFFER_H

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "base_hash_table.h"


char* preproc_concat_two_strings(const char* str1, const char* str2);

static inline void perror_and_quit(const char* message){
    perror(message);
    exit(errno);
}

void preproc_init(unsigned int size);

static inline int preproc_err_let(const unsigned int first_let, const unsigned int second_let){
    fprintf(stderr, "Error !\nFound a \"Let\", line %u, after a \"Let\", line %u, without a \"be\" between them.", second_let, first_let);
    return 1;
}

static inline int preproc_err_eof(const unsigned int line_previous_let){
    fprintf(stderr, "Error, found an \"Let\" line %u but no \"be\" detected before the end of file\n", line_previous_let);
    return 1;
}

static inline int preproc_err_double_id(void){
    fprintf(stderr, "Error, found two names for the Let definition. Exiting ...\n");
    return 1;
}

void preproc_new_identifier(const char* id);

char* preproc_get_actual_identifier(void);

int preproc_add_current_id_with_current_expression(void);

void preproc_clean(void);

int preproc_test_or_add_identifier(const char* id_or_not);

void preproc_add_to_current_expression(const char* str);

int preproc_check_identifier(char* identifier, char** associated_value);

#endif // ( __PREPROC_BUFFER_H )
