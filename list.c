#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ustr.h"
#include "list.h"

/*
Returns an empty list of initial_capacity
*/
List new_list(int32_t initial_capacity)
{
    List list;
    list.size = 0;
    list.capacity = initial_capacity;
    list.data = malloc(initial_capacity * sizeof(struct UStr));
    return list;
}

/*
Initializes an list of length size with elements from array
*/
List new_list_from_array(struct UStr *array, int32_t size)
{
    List list = new_list(size);
    for (int32_t i = 0; i < size; i++)
    {
        list.data[i] = array[i];
    }
    list.size = size;
    return list;
}

/*
Given a list of strings and a separator string, returns a single string
containing all the strings in list joined by the separator.
*/
UStr join(List *list, UStr separator)
{
    // TODO: implement this
    if (list->size == 0)
    {
        return new_ustr("");
    }
    int total_bytes = 0;
    for (int i = 0; i < list->size; i++)
    {
        total_bytes += list->data[i].bytes;
    }
    total_bytes += separator.bytes * (list->size - 1);
    char *buffer = malloc(total_bytes + 1);
    if (!buffer)
        return new_ustr("");
    int offset = 0;
    for (int i = 0; i < list->size; i++)
    {
        memcpy(buffer + offset, list->data[i].contents, list->data[i].bytes);
        offset += list->data[i].bytes;
        if (i < list->size - 1)
        {
            memcpy(buffer + offset, separator.contents, separator.bytes);
            offset += separator.bytes;
        }
    }
    buffer[offset] = '\0';
    UStr result = new_ustr(buffer);
    free(buffer);
    return result;
}

/*
Inserts string s into list at index s, shifting elements to the right.
Expands the list's capacity if necessary (double the capacity, or set to 1 if 0).

Returns 1 on success, 0 if the index is invalid (out of bounds).
*/
int8_t insert(List *list, UStr s, int32_t index)
{
    // TODO: implement this
    if (index < 0 || index > list->size)
    {
        return 0;
    }
    // Expand capacity
    if (list->size >= list->capacity)
    {
        int32_t new_capacity = list->capacity == 0 ? 1 : list->capacity * 2;
        UStr *new_data = realloc(list->data, new_capacity * sizeof(UStr));
        if (new_data == NULL)
        {
            return 0;
        }
        list->data = new_data;
        list->capacity = new_capacity;
    }
    // Shift right
    for (int32_t i = list->size; i > index; i--)
    {
        list->data[i] = list->data[i - 1];
    }
    list->data[index] = s;
    list->size++;
    return 1;
}

/*
Removes the element at the given index and shifts all subsequent elements left.

Returns 1 on success, 0 if the index is invalid (out of bounds).
*/
int8_t listRemoveAt(List *list, int32_t index)
{
    // TODO: implement this
    if (index < 0 || index >= list->size)
    {
        return 0;
    }

    free_ustr(list->data[index]);

    // Shift left
    for (int i = index; i < list->size - 1; i++)
    {
        list->data[i] = list->data[i + 1];
    }

    list->data[list->size - 1].contents = NULL;

    list->size--;

    return 1;
}

/*
Splits the given string s into substrings separated by the given delimiter string.

Returns a List of String objects, each containing a segment between delimiters.

If the delimiter is the empty string, return a list containing the original
string as a single element.

If the input string ends with the delimiter, include an empty string at the
end of the result.

Note that the delimiter could be of a length of more than 1 character
*/
List split(UStr s, UStr separator)
{
    // TODO: implement this
    if (separator.bytes == 0)
    {

        UStr *single = malloc(sizeof(UStr));
        *single = new_ustr(s.contents);
        return new_list_from_array(single, 1);
    }

    UStr *result_array = malloc(sizeof(UStr) * (s.codepoints + 1));
    int32_t count = 0;
    int32_t start = 0;
    int32_t i = 0;

    while (i <= s.bytes - separator.bytes)
    {
        int match = 1;
        for (int j = 0; j < separator.bytes; j++)
        {
            if (s.contents[i + j] != separator.contents[j])
            {
                match = 0;
                break;
            }
        }

        if (match)
        {

            int segment_len = i - start;
            char *buffer = malloc(segment_len + 1);
            int write = 0;
            for (int k = start; k < i; k++)
            {
                buffer[write++] = s.contents[k];
            }
            buffer[write] = '\0';
            result_array[count++] = new_ustr(buffer);
            free(buffer);

            i += separator.bytes;
            start = i;
        }
        else
        {
            i++;
        }
    }

    char *buffer = malloc(s.bytes - start + 1);
    int write = 0;
    for (int k = start; k < s.bytes; k++)
    {
        buffer[write++] = s.contents[k];
    }
    buffer[write] = '\0';
    result_array[count++] = new_ustr(buffer);
    free(buffer);

    return new_list_from_array(result_array, count);
}
