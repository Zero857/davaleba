#include <string.h>
#include <stdbool.h>

bool scan_token(const char **p_input, const char *delimiters, char buf[], size_t buflen) {
    // Check for NULL pointers
    if (!p_input || !*p_input || !delimiters || !buf) {
        return false;
    }

    const char *start = *p_input;
    const char *end = start + strcspn(start, delimiters);  // Find the end of the token
    size_t token_len = end - start;  // Calculate token length

    if (token_len >= buflen) {  // Ensure there's room for the token and a null terminator
        return false;  // Not enough space in the buffer
    }

    // Copy token to buffer
    strncpy(buf, start, token_len);
    buf[token_len] = '\0';  // Null-terminate the copied token

    *p_input = (*end == '\0') ? end : end + 1;  // Update the input pointer position
    return true;
}

int main(void) {
    const char *input = "Hello, World!";
    const char *delimiters = ", ";
    char buf[10];
    bool success = scan_token(&input, delimiters, buf, sizeof(buf));

    // Output: success: 1, buf: "Hello", remaining input: "World!"
    printf("success: %d, buf: \"%s\", remaining input: \"%s\"\n", success, buf, input);
    return 0;
}
