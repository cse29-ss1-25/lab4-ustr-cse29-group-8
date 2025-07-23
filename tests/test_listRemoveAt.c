#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

int main()
{
    UStr a = new_ustr("apple");
    UStr b = new_ustr("banana");
    UStr c = new_ustr("carrot");

    UStr arr[3] = {a, b, c};
    List list = new_list_from_array(arr, 3);

    listRemoveAt(&list, 1); // remove "banana"

    for (int i = 0; i < list.size; i++)
    {
        print_ustr(list.data[i]);
        printf("\n");
    }

    // Clean up
    for (int i = 0; i < list.size; i++)
    {
        free_ustr(list.data[i]);
    }
    free(list.data);

    return 0;
}
