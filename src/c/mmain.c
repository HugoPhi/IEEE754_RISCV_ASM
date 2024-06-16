#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


void displayBinary(unsigned int num);
uint32_t decimalToIEEE754(float decimal);
float IEEE754ToDecimal(uint32_t ieee754);
void printHex(uint32_t num);
void printBinary(uint32_t num);

extern uint32_t add(uint32_t num1, uint32_t num2);
uint32_t multi(uint32_t num1, uint32_t num2);
uint32_t divi(uint32_t num1, uint32_t num2);

void __clear__();
void clearInputBuffer();
void __pause__();


int main() {
    int choice;
    float num1, num2;
    
    while (1) {
        printf("Select the operation:\n");
        printf("1. Convert decimal to IEEE 754\n");
        printf("2. Add two floating-point numbers\n");
        printf("3. Sub two floating-point numbers\n");
        printf("4. Mult two floating-point numbers\n");
        printf("5. Div two floating-point numbers\n");
        printf("6. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        __clear__();
        

        uint32_t a, b, c;
        switch (choice) {
            case 1:
                printf("Enter a decimal number: ");
                scanf("%f", &num1);
                // printf("%d", decimalToIEEE754(num1));
                printf("\nBinary is: ");
                printBinary(decimalToIEEE754(num1));
                printf("\nHex is: ");
                printHex(decimalToIEEE754(num1));
                printf("\n");
                printf("%f", IEEE754ToDecimal(decimalToIEEE754(num1)));
                break;
            case 2:  // addition 
                printf("Enter two floating-point numbers:\n");
                scanf("%f %f", &num1, &num2);
                a = decimalToIEEE754(num1);
                b = decimalToIEEE754(num2);
                printBinary(a);
                printf("\n");
                printBinary(b);
                c = add(a, b);
                printf("\n");
                printBinary(c);
                printf("\n= %f", IEEE754ToDecimal(c));
                break;
            case 3:  // subtraction
                printf("Enter two floating-point numbers:\n");
                scanf("%f %f", &num1, &num2);
                num2 = -num2;
                a = decimalToIEEE754(num1);
                b = decimalToIEEE754(num2);
                c = add(a, b);
                printf("= %f", IEEE754ToDecimal(c));
                break;
            case 4:  // multiplies
                printf("Enter two floating-point numbers:\n");
                scanf("%f %f", &num1, &num2);
                a = decimalToIEEE754(num1);
                b = decimalToIEEE754(num2);
                c = multi(a, b);
                printf("= %f", IEEE754ToDecimal(c));
                break;
            case 5:  // division
                printf("Enter two floating-point numbers:\n");
                scanf("%f %f", &num1, &num2);
                a = decimalToIEEE754(num1);
                b = decimalToIEEE754(num2);
                c = divi(a, b);
                printf("= %f", IEEE754ToDecimal(c));
                break;
            case 6:
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
        __pause__();
        __clear__();
    }
    
    return 0;
}



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

////////////////////////////////////////////
uint32_t multi(uint32_t num1, uint32_t num2) {
    return num1 * num2;
}

uint32_t divi(uint32_t num1, uint32_t num2) {
    return num1 / num2;
}


