#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#define MISTAKESIZE 1000
#define EPS 1e-6

/* floats are equal if |a-b| < EPS */
#define isequal(a,b) (((a) > (b)) ? ((a)-(b) < EPS) : ((b)-(a) < EPS))


int solve (float *coef, float *sol);

int main() {
    int c;

    /* array of a b c coeffs */
    float coef[3];

    /* array of solutions */
    float sol[2];
    float *sp = sol;

    printf("enter a, b, c coefs:\n");
    
    int res;
    char *junk = (char *) malloc(MISTAKESIZE);
    while ((res = scanf("%f %f %f", &coef[0], &coef[1], &coef[2])) != 3) {
        scanf("%[^0-9.\n]", junk);
        printf("Incorrect input \"%s\", try again\n", junk);
    }

    if ((c = solve(coef, sp)) == 0)
        printf("\tno solutions\n");
    else if (c == 1) 
        printf("\t1 solution:\n%.3f", sol[0]);
    else if (c == 2)
        printf("\t2 solutions:\n%.3f\n%.3f", sol[0], sol[1]);
    
    return 0;
}

/* returns number of solutions */
int solve(float *coef, float *sol) {
    if (isequal(coef[0], 0.0) == 1) {
        /* x = -c / b*/
        *sol = ((-1) * coef[2]) / coef[1];
        return 1;
    }
    
    float d;

    /* d = b^2 - 4ac */
    d = coef[1]*coef[1] - 4*coef[0]*coef[2];

    if (d < 0) 
        return 0;
    else if (isequal(d,0.0) == 1) {
        *sol = (float)(-1) * coef[1] / (2 * coef[0]);
        return 1;
    }

    /* BASED solution v lob */
    *sol++ = (float)((-coef[1] - sqrt(d)) / (2 * coef[0]));
    *sol = (float)((-coef[1] + sqrt(d)) / (2 * coef[0]));
    return 2;
}
