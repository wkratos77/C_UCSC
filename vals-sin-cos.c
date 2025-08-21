#include <stdio.h>
#include <math.h>

void print_table(void) {
    double x;
    for (x = 0.0; x <= 1.0; x += 0.1) {
        printf("x = %.1f\t sin(x) = %f\t cos(x) = %f\n", x, sin(x), cos(x));
    }
}

int main(void) {
    print_table();
    return 0;
}
