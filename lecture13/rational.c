#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    int numer;
    int denom;
} Rational;

// Returns a new Rational with the given numer and denom.
// If unable to allocate, prints an error message and exits.
Rational *make_rational(int numer, int denom) {
    Rational *rational= (Rational *) malloc(sizeof(Rational));
    if (rational == NULL)
    {
        (void) fprintf(stderr, "Failure to make rational.");
        exit(EXIT_FAILURE);
    }
    rational-> numer = numer;
    rational->denom = denom;
    return rational;
}

union{
    float d;
    int  l;
}u;


// Computes a floating-point approximation of a Rational.
double rational_to_double(Rational *rational) {
    //float frational= (float) malloc(sizeof(float));
    u.l= rational;

    return u.d;
}

// Multiplies two rational numbers; returns a new Rational.
Rational *mult_rational(Rational *r1, Rational *r2) {
    Rational *result= r1 * r2;
    return strdup(result);
}

// Frees a Rational.
void free_rational(Rational *rational) {
    free(rational);
}

// Prints a rational in fraction form.
void print_rational(Rational *rational) {
    printf("%d / %d\n", rational->numer, rational->denom);
}

int main(void)
{
    Rational *rational = make_rational(3, 7);
    print_rational(rational);

    double d = rational_to_double(rational);
    printf("%lf\n", d);

    Rational *square = mult_rational(rational, rational);
    print_rational(square);
	
    free_rational(rational);
    free_rational(square);

    return EXIT_SUCCESS;
}
