#ifndef SCAN_TOKEN_H
#define SCAN_TOKEN_H

#include <stdbool.h>

bool scan_token(const char **p_input, const char *delimiters,
                char buf[], size_t buflen);

#endif //SCAN_TOKEN_H
