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
extern uint32_t multi(uint32_t num1, uint32_t num2);
extern uint32_t divi(uint32_t num1, uint32_t num2);

void __clear__();
void clearInputBuffer();
void __pause__();


