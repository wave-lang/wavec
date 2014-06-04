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

#include "preproc_utils.h"

char* preproc_concat_two_strings(const char* str1, const char* str2){
    size_t len1, len2;
    len1 = strlen(str1);
    len2 = strlen(str2);
    char* new_one = calloc(len1 + len2 + 1, sizeof(char));
    if( new_one != NULL )
        new_one = strcpy(new_one, str1);
        new_one = strcat(new_one, str2);
    return new_one;
}

char* preproc_concat_two_strings_with_destroy(char* str1, char* str2){
    char* ret_string = preproc_concat_two_strings_with_destroy(str1, str2);
    if( ret_string != NULL ){
        free(str1);
        free(str2);
    }
    return ret_string;
}
