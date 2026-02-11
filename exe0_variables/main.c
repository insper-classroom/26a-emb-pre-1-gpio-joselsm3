#include "stdio.h"

int a = 0; // var global
int b = 0; // var global

void foo(void) {
    a = a + 1; // acessa variavel global
}

void main(void) {
    while (1) {
        foo();
        
        if (a > 5) {
            b = 1;
        }
    }
}
