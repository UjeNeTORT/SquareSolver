#include <stdio.h>
#include <math.h>
#include <ctype.h>

const int MISTAKE = 1000;
const double EPS = 1e-6;

int solve (double *coef, double *sol);
int is_equal(double a, double b);

int main() {
    int c;

    /* array of a b c coeffs */
    double coef[3] = {0.0, 0.0, 0.0};

    /* array of solutions */
    double sol[2] = {0.0, 0.0};

    printf("Please, enter a, b, c coefs:\n");
    
    int res;
    int junk;
    while ((res = scanf("%lf %lf %lf", &coef[0], &coef[1], &coef[2])) != 3) {
        junk = getchar();
        printf("Incorrect input \"%c\", try again\n", junk);
    }

    switch(c = solve(coef, sol)) {
        case 0:
            printf("no solutions\n");
            break;
        case 1: 
            printf("1 solution:\n"
            "%.3lf\n", sol[0]);
            break;
        case 2:
            printf("2 solutions:\n"
            "%.3lf , %.3lf\n", sol[0], sol[1]);
            break;
        default:
            printf("solve returned breeeed\n");
            break;
    }
    
    return 0;
}

/* returns number of solutions */
int solve(double *coef, double *sol) {
    if (is_equal(coef[0], 0.0) == 1) {
        /* x = -c / b*/
        *sol = ((-1) * coef[2]) / coef[1];
        return 1;
    }
    
    double d, sd;

    /* d = b^2 - 4ac */
    d = coef[1]*coef[1] - 4*coef[0]*coef[2];
    sd = sqrt(d);

    if (d < 0) 
        return 0;
    else if (is_equal(d,0.0) == 1) {
        *sol = -coef[1] / (2 * coef[0]);
        return 1;
    }

    /* BASED solution v lob */
    *sol++ = (-coef[1] - sd) / (2 * coef[0]);
    *sol = (-coef[1] + sd) / (2 * coef[0]);
    return 2;
}

/* doubles are equal if |a-b| < EPS */
int is_equal(double a, double b) {
    return (a > b) ? (a - b < EPS) : (b - a < EPS);
}
