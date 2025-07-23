#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ustr.h"
#include "list.h"

int main()
{
    UStr s = new_ustr("apple==banana==carrot==");
    UStr sep = new_ustr("==");

    List parts = split(s, sep);

    for (int i = 0; i < parts.size; i++)
    {
        print_ustr(parts.data[i]);
        printf("\n");
        free_ustr(parts.data[i]);
    }

    free_ustr(s);
    free_ustr(sep);
    free(parts.data);

    return 0;
}
