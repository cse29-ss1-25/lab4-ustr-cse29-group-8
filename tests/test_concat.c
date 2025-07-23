#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ustr.h"
#include "pset1.h"

int main()
{
    UStr s1 = new_ustr("abc ");
    UStr s2 = new_ustr("🍎def");

    UStr combined = concat(s1, s2);
    print_ustr(combined); // Should print: "abc 🍎def [codepoints: 7 | bytes: ...]"

    // Clean up
    free_ustr(s1);
    free_ustr(s2);
    free_ustr(combined);

    return 0;
}