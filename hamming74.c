#include <assert.h>
#include <error.h>
#include <memory.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

uint8_t getBit(uint8_t byte, uint8_t position) {
    return (byte >> position) & 1;
}

uint8_t setBit(uint8_t byte, uint8_t position, uint8_t value) {
    return (value) ? (byte | (1 << position)) : (byte & ~(1 << position));
}

uint8_t computeError(const uint8_t code) {
    uint8_t errIdx = 7;
    if (getBit(code, 6) ^ getBit(code, 4) ^ getBit(code, 2) ^ getBit(code, 0)) { errIdx -= 1; }
    if (getBit(code, 5) ^ getBit(code, 4) ^ getBit(code, 1) ^ getBit(code, 0)) { errIdx -= 2; }
    if (getBit(code, 3) ^ getBit(code, 2) ^ getBit(code, 1) ^ getBit(code, 0)) { errIdx -= 4; }
    return errIdx;
}

uint8_t encodeByte(uint8_t byte) {
    uint8_t hammingCode = 0;
    uint8_t d1 = getBit(byte, 3);
    uint8_t d2 = getBit(byte, 2);
    uint8_t d3 = getBit(byte, 1);
    uint8_t d4 = getBit(byte, 0);

    uint8_t p1 = d1 ^ d2 ^ d4;
    uint8_t p2 = d1 ^ d3 ^ d4;
    uint8_t p3 = d2 ^ d3 ^ d4;

    hammingCode = setBit(hammingCode, 6, p1);
    hammingCode = setBit(hammingCode, 5, p2);
    hammingCode = setBit(hammingCode, 4, d1);
    hammingCode = setBit(hammingCode, 3, p3);
    hammingCode = setBit(hammingCode, 2, d2);
    hammingCode = setBit(hammingCode, 1, d3);
    hammingCode = setBit(hammingCode, 0, d4);

    return hammingCode;
}

uint8_t decodeByte(uint8_t code) {
    int errIdx = computeError(code);
    if (errIdx != 7) {
        code ^= 1 << errIdx;
    }

    uint8_t byte = 0;
    byte |= getBit(code, 0);
    byte |= getBit(code, 1) << 1;
    byte |= getBit(code, 2) << 2;
    byte |= getBit(code, 4) << 3;

    return byte;
}

void encodeDouble(uint8_t byte, uint8_t* buffer) {
    buffer[0] = encodeByte(byte >> 4);
    buffer[1] = encodeByte(byte & 0x0F);
}

uint8_t decodeDouble(const uint8_t* buffer) {
    uint8_t upper = decodeByte(buffer[0]);
    uint8_t lower = decodeByte(buffer[1]);

    if (upper == 0xFF || lower == 0xFF) {
        return 0xFF;
    }

    return (upper << 4) | lower;
}

// ... rest of your code including main function remains same.
