#include <stdio.h>
#include <math.h>
int main(void) {
    double x, result;

    printf("Enter a value between 0 and 1 :");
    scanf("%lf", &x);

    if (x <= 0.0 || x >= 1.0) 
    {
        printf("Invalid input. Value must be >0 and <1.\n");
        return 1; 
    }

    result = sin(x);

    printf("The sine of %lf is %lf\n", x, result);

    return 0;
}
