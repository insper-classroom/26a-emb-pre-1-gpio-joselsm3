#include "stdio.h"

static int a = 0; // var global
static int b = 0; // var global

void foo(void) {
    a = a + 1; // acessa variavel global
}

int main(void) {
    while (1) {
        foo();
        
        if (a > 5) {
            b = 1;
        }
    }
}