#include <error.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "scan_token.h"


int main(int argc, char *argv[])
{
    if (argc < 3) error(1, 0,
                        "Missing argument(s). "
                        "Please supply delimiters and string to tokenize.");

    const char *delim = argv[1];
    const char *input = argv[2];

    char buf[10];
    const char *remaining = input;
    printf("Tokenized: { ");
    while (scan_token(&remaining, delim, buf, sizeof(buf))) {
        printf("\"%s\" ", buf);
    }
    printf("}\n");

    return 0;
}
