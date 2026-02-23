#include <stdio.h>
#include <stdlib.h>

#define NUM_ELEMENTS 5

int multiplyNumbers(int x, int y) {
    int product = x * y;
    return product;
}

int main(void) {
    int a = 0, b = 5; //uninitvar, legacyUninitvar
    int result = multiplyNumbers(a, b);

    int arr[NUM_ELEMENTS];
    int sum = 0;
    for (int i = 0; i < NUM_ELEMENTS; i++) { //arrayIndexOutOfBounds
        arr[i] = i;
        sum += arr[i];
    }

    (void)arr;
    (void)sum;
    (void)result;

    return 0;
}