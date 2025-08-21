#include <stdio.h>
#define PI 3.14159

int main(void)
{
    double radius;
    double volume;

    printf("Enter radius: ");
    scanf("%lf", &radius);

    volume = (4.0 / 3.0) * PI * radius * radius * radius;

    printf("Volume is: %lf\n", volume);

    return 0;
}
