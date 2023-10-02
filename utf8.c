#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int to_utf8(unsigned short code_point, unsigned char utf8_bytes[]) {
    if (code_point < 0x80) {
        // 1-byte sequence
        utf8_bytes[0] = code_point;
        return 1;
    } else if (code_point < 0x800) {
        // 2-byte sequence
        utf8_bytes[0] = 0xC0 | (code_point >> 6);
        utf8_bytes[1] = 0x80 | (code_point & 0x3F);
        return 2;
    } else {
        // 3-byte sequence
        utf8_bytes[0] = 0xE0 | (code_point >> 12);
        utf8_bytes[1] = 0x80 | ((code_point >> 6) & 0x3F);
        utf8_bytes[2] = 0x80 | (code_point & 0x3F);
        return 3;
    }
}

// ------- DO NOT EDIT ANY CODE BELOW THIS LINE -------

void print_utf8(unsigned short cp, unsigned char seq[], int len)
{
    int i;
    printf("U+%04X   Hex:", cp);
    for (i = 0; i < len; i++)
       printf(" %02x", seq[i]);
    for ( ; i < 4; i++) printf("   ");
    seq[len] = '\0';
    printf("Character: %s  \n", seq);  
}

unsigned short convert_arg(const char *str,
                           unsigned short low, 
                           unsigned short high)
{
    char *end;
    long n = strtol(str, &end, 0);
    if (*end != '\0')
        error(1, 0, "Invalid code point '%s'", str);
    if (n < low || n > high)
        error(1, 0, "Code point %s not in range [%u, %u]", str, low, high);
    return n;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
        error(1, 0, "Missing argument. Please supply one or more unicode code"
                    " points in decimal or hex.");
    
    for (int i = 1; i < argc; i++) {
        unsigned short cp = convert_arg(argv[i], 0, USHRT_MAX);
        unsigned char seq[4];
        int len = to_utf8(cp, seq);
        print_utf8(cp, seq, len);  
    }
    return 0;
}
