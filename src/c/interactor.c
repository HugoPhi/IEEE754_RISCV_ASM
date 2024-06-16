#include "../../include/headers.h"

void performAddition(float num1, float num2) {
    float result = num1 + num2; 
    printf("Result: %f\n", result);
}


uint32_t decimalToIEEE754(float decimal) {
    union {
        float f;
        uint32_t u;
    } converter;
    converter.f = decimal;
    return converter.u;
}

float IEEE754ToDecimal(uint32_t ieee754) {
    union {
        uint32_t u;
        float f;
    } converter;
    converter.u = ieee754;
    return converter.f;
}

void printHex(uint32_t num) {
    printf("0x%08x", num);
}

void printBinary(uint32_t num) {
    for (int i = 31; i >= 0; i--) {  // print by decimal 
        printf("%d", (num >> i) & 1);
        if (i % 8 == 0 && i != 0) printf(" ");
    }
}


void __clear__() {
    printf("\033[2J\033[H");
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void __pause__() {
    printf("\nPress Enter to continue...");
    clearInputBuffer(); 
    getchar();
}
