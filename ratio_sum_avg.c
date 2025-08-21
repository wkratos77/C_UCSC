#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int num;  // numerator
    int den;  // denominator
} Rational;

// Function prototypes
Rational add(Rational a, Rational b);
Rational subtract(Rational a, Rational b);
Rational multiply(Rational a, Rational b);
Rational divide(Rational a, Rational b);
void printRational(Rational r);

// Main program
int main() 
{
    FILE* fp = fopen("rationals.txt", "r"); // file with rational numbers
    if (!fp) 
    {
        printf("Failed to open file.\n");
        return 1;
    }

    int n;
    fscanf(fp, "%d", &n); // read the first integer: number of rationals

    Rational* data = malloc(n * sizeof(Rational));
    if (!data) 
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Read the numerators and denominators
    for (int i = 0; i < n; i++) 
    {
        fscanf(fp, "%d %d", &data[i].num, &data[i].den);
    }
    fclose(fp);

    // Compute sum
    Rational sum = data[0];
    for (int i = 1; i < n; i++) 
    {
        sum = add(sum, data[i]);
    }

    // Compute average
    Rational avg;
    avg.num = sum.num;
    avg.den = sum.den * n; // divide sum by n
    avg = reduce(avg);

    printf("Sum of all rationals: ");
    printRational(sum);

    printf("Average of all rationals: ");
    printRational(avg);

    free(data);
    return 0;
}

// Add two rationals
Rational add(Rational a, Rational b) 
{
    Rational r;
    r.num = a.num * b.den + b.num * a.den;
    r.den = a.den * b.den;
    return reduce(r);
}

// Subtract b from a
Rational subtract(Rational a, Rational b) 
{
    Rational r;
    r.num = a.num * b.den - b.num * a.den;
    r.den = a.den * b.den;
    return reduce(r);
}

// Multiply two rationals
Rational multiply(Rational a, Rational b) 
{
    Rational r;
    r.num = a.num * b.num;
    r.den = a.den * b.den;
    return reduce(r);
}

// Divide a by b
Rational divide(Rational a, Rational b) 
{
    Rational r;
    r.num = a.num * b.den;
    r.den = a.den * b.num;
    return reduce(r);
}

// Print rational as num/den
void printRational(Rational r) 
{
    printf("%d/%d\n", r.num, r.den);
}

// Reduce fraction to simplest form
Rational reduce(Rational r) 
{
    int a = r.num, b = r.den, temp;
    if (b < 0) { a = -a; b = -b; } // keep denominator positive

    // Euclidean algorithm for gcd
    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }
    int gcd = (a < 0) ? -a : a;
    r.num /= gcd;
    r.den /= gcd;
    return r;
}
