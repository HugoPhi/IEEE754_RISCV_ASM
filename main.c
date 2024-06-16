#include <stdio.h> 
#include "./include/headers.h"

int main() {
    int choice;
    float num1, num2;
    
    while (1) {
        printf("Select the operation:\n");
        printf("\033[0m\033[1;32m1.\033[0m Convert decimal to IEEE 754\n");
        printf("\033[0m\033[1;32m2.\033[0m Add two floating-point numbers\n");
        printf("\033[0m\033[1;32m3.\033[0m Sub two floating-point numbers\n");
        printf("\033[0m\033[1;32m4.\033[0m Mult two floating-point numbers\n");
        printf("\033[0m\033[1;32m5.\033[0m Div two floating-point numbers\n");
        printf("\033[0m\033[1;32m6.\033[0m Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        __clear__();
        
        
        uint32_t a, b, c;
        switch (choice) {
            case 1:
                printf("Enter a decimal number: ");
                scanf("%f", &num1);
                // printf("%d", decimalToIEEE754(num1));
                printf("\n\033[0m\033[1;32mBinary\033[0m is: ");
                printBinary(decimalToIEEE754(num1));
                printf("\n\033[0m\033[1;32mHex\033[0m    is: ");
                printHex(decimalToIEEE754(num1));
                printf("\n");
                break;
            case 2:  // addition 
                printf("Enter two floating-point numbers:\n");
                scanf("%f %f", &num1, &num2);
                a = decimalToIEEE754(num1);
                b = decimalToIEEE754(num2);
                // printBinary(a);
                // printf("\n");
                // printBinary(b);
                c = add(a, b);
                // printf("\n");
                // printBinary(c);
                printf("\n= \033[0m\033[1;32m%f\033[0m", IEEE754ToDecimal(c));
                break;
            case 3:  // subtraction
                printf("Enter two floating-point numbers:\n");
                scanf("%f %f", &num1, &num2);
                num2 = -num2;
                a = decimalToIEEE754(num1);
                b = decimalToIEEE754(num2);
                c = add(a, b);
                printf("\n= \033[0m\033[1;32m%f\033[0m", IEEE754ToDecimal(c));
                break;
            case 4:  // multiplies
                printf("Enter two floating-point numbers:\n");
                scanf("%f %f", &num1, &num2);
                a = decimalToIEEE754(num1);
                b = decimalToIEEE754(num2);
                c = multi(a, b);
                printf("\n= \033[0m\033[1;32m%f\033[0m", IEEE754ToDecimal(c));
                break;
            case 5:  // division
                printf("Enter two floating-point numbers:\n");
                scanf("%f %f", &num1, &num2);
                a = decimalToIEEE754(num1);
                b = decimalToIEEE754(num2);
                c = divi(a, b);
                printf("\n= \033[0m\033[1;32m%f\033[0m", IEEE754ToDecimal(c));
                break;
            case 6:
                return 0;
            default:
                printf("\033[0m\033[1;31mInvalid choice. Please try again.\033[0m\n");
        }
        __pause__();
        __clear__();
    }
    
    return 0;
}

