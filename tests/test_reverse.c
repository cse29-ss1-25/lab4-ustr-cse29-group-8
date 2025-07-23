#include <stdio.h>
#include "../ustr.h"

int main()
{
    UStr s = new_ustr("apples🍎 and bananas🍌");

    UStr r = reverse(s);

    print_ustr(r); // Expected: 🍌sananab dna 🍎selppa [codepoints: 20 | bytes: X]

    free_ustr(s);
    free_ustr(r);
    return 0;
}
