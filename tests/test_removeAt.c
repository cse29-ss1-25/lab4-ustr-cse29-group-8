#include <stdio.h>
#include "../ustr.h"

int main()
{
    UStr s = new_ustr("abc🍎def");
    UStr result = removeAt(s, 3); // removes 🍎

    print_ustr(result); // Should print: abcdef [codepoints: 6 | bytes: 6 or 7]

    free_ustr(s);
    free_ustr(result);
    return 0;
}