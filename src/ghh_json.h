#ifndef GHH_JSON_H
#define GHH_JSON_H

#ifdef __cplusplus
extern "C"
{
#endif

    // licensing info at end of file.

#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>

    typedef enum json_type
    {
        JSON_OBJECT,
        JSON_ARRAY,
        JSON_STRING,
        JSON_NUMBER,
        JSON_TRUE,
        JSON_FALSE,
        JSON_NULL
    } json_type_e;

    typedef struct json_object
    {
        union json_obj_data
        {
            struct json_hmap *hmap;
            struct json_vec *vec;
            char *string;
            double number;
        } data;

        json_type_e type;
    } json_object_t;

    typedef struct json
    {
        json_object_t *root;

        // allocators
        struct json_tptr **tracked;      // fat pointer array of tracked pointers
        char **pages;                    // fat pointer
        size_t cur_tracked, tracked_cap; // tracks tracked pointers
        size_t cur_page, page_cap;       // tracks allocator pages
        size_t used;                     // tracks current page stack
    } json_t;

    void json_load(json_t *, char *text);
    void json_load_empty(json_t *);
    void json_load_file(json_t *, const char *filepath);
    void json_unload(json_t *);

    // returns a string allocated with JSON_MALLOC
    char *json_serialize(json_object_t *, bool mini, int indent, size_t *out_len);

    // take an object, retrieve data and cast
    json_object_t *json_get_object(json_object_t *, char *key);
    // returns actual, mutable array pointer
    json_object_t **json_get_array(json_object_t *, char *key, size_t *out_size);
    char *json_get_string(json_object_t *, char *key);
    double json_get_number(json_object_t *, char *key);
    bool json_get_bool(json_object_t *, char *key);

    // cast an object to a data type
    json_object_t **json_to_array(json_object_t *, size_t *out_size);
    char *json_to_string(json_object_t *);
    double json_to_number(json_object_t *);
    bool json_to_bool(json_object_t *);

    // remove a json_object from another json_object (unordered)
    json_object_t *json_pop(json_t *, json_object_t *, char *key);
    // pop but ordered, this is O(n) rather than O(1) removal time
    json_object_t *json_pop_ordered(json_t *, json_object_t *, char *key);

    // add a json_object to another json_object
    void json_put(json_t *, json_object_t *, char *key, json_object_t *child);

    // equivalent to calling json_new_type() and then json_put().
    // return the new object
    json_object_t *json_put_object(json_t *, json_object_t *, char *key);
    void json_put_array(
        json_t *, json_object_t *, char *key, json_object_t **objects, size_t size);
    void json_put_string(json_t *, json_object_t *, char *key, char *string);
    void json_put_number(json_t *, json_object_t *, char *key, double number);
    void json_put_bool(json_t *, json_object_t *, char *key, bool value);
    void json_put_null(json_t *, json_object_t *, char *key);

    // create a json data type on a json_t memory context
    json_object_t *json_new_object(json_t *);
    json_object_t *json_new_array(json_t *, json_object_t **objects, size_t size);
    json_object_t *json_new_string(json_t *, char *string);
    json_object_t *json_new_number(json_t *, double number);
    json_object_t *json_new_bool(json_t *, bool value);
    json_object_t *json_new_null(json_t *);

#ifdef __cplusplus
}
#endif

#endif // GHH_JSON_H

/*

The MIT License (MIT)

Copyright (c) 2021 garrisonhh / Garrison Hinson-Hasty

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the “Software”), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/
