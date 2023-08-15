#include <stdio.h>
#include <math.h>
#include <ctype.h>

int solve (float *, float *);
float getfloat(void);

int main() {
    int c;

    float coef[3];
    float *cp = coef;

    float sol[2];
    float *sp = sol;

    printf("enter a,b,c coefs:\n");

    for (int i = 0; i < 3; i++) 
        *cp++ = getfloat();

    if ((c = solve(coef, sp)) == 0)
        printf("\tno solutions\n");
    else if (c == 1) 
        printf("\t1 solution:\n%.3f", sol[0]);
    else if (c == 2)
        printf("\t2 solutions:\n%.3f\n%.3f\n", sol[0], sol[1]);
    
    return 0;
}

/* returns number of solutions */
int solve(float *coef, float *sol) {
    if (coef[0] == 0.0) {
        printf("solve: \'a\' must not be 0\n");
        return 0;
    }
    
    float d;

    /* d = b^2 - 4ac */
    d = coef[1]*coef[1] - 4*coef[0]*coef[2];

    if (d < 0) 
        return 0;
    else if (d == 0) {
        *sol = (float)(-1) * coef[1] / (2 * coef[0]);
        return 1;
    }

    /* BASED solution v lob */
    *sol++ = (float)((-coef[1] - sqrt(d)) / (2 * coef[0]));
    *sol = (float)((-coef[1] + sqrt(d)) / (2 * coef[0]));
    return 2;
}


float getfloat(void) {
    int c, denom = 10;
    int negative = 0;
    float num = 0.0;

    /* skip all the blanks between numbers */
    while (isspace(c = getchar()))
        ;
    
    if (c == '-') {
        negative = 1;
        c = getchar();
    }
    /* get integer part of a number */
    while (isdigit(c)) {
        num *= 10;
        num += (float)(c - '0');
        c = getchar();
    }

    /* get fractional part of a number */
    if (c == '.')
        while (isdigit(c = getchar())) {
            num += ((float)(c - '0')) / denom;
            denom *= 10;
        }

    if (!isspace(c)) 
        printf("getfloat: invalid number \'%c\'\n", c);

    if (negative) 
        num *= (-1.0);
    return num;
}
