#include <stdio.h>
#include <math.h>
#include <ctype.h>

enum {SOL_0, SOL_1, SOL_2};

const int MISTAKE = 1000;
const double EPS = 1e-6;

struct equation {
    double a;
    double b;
    double c;
    double sol_1;
    double sol_2;
} eq = {0.0, 0.0, 0.0, 0.0, 0.0};

int solve (struct equation *eq);
int is_equal(double a, double b);

int main() {
    int c;

    printf("Please, enter a, b, c coefs:\n");
    
    int res;
    int junk;
    while ((res = scanf("%lf %lf %lf", &eq.a, &eq.b, &eq.c)) != 3) {
        junk = getchar();
        printf("Incorrect input \"%c\", try again\n", junk);
    }

    switch(c = solve(&eq)) {
        case SOL_0:
            printf("no solutions\n");
            break;
        case SOL_1: 
            printf("1 solution:\n"
            "%.3lf\n", eq.sol_1);
            break;
        case SOL_2:
            printf("2 solutions:\n"
            "%.3lf , %.3lf\n", eq.sol_1, eq.sol_2);
            break;
        default:
            printf("solve returned breeeed\n");
            break;
    }
    
    return 0;
}

/* returns number of solutions */
int solve(struct equation *eqp) {
    if (is_equal((eqp->a), 0.0) == 1) {
        /* x = -c / b*/
        eqp->sol_1 = ((-1) * (eqp->c)) / (eqp->b);
        return SOL_1;
    }
    
    double d, sd;

    /* d = b^2 - 4ac */
    d = (eqp->b)*(eqp->b) - 4*(eqp->a)*(eqp->c);
    sd = sqrt(d);

    if (d < 0) 
        return SOL_0;
    else if (is_equal(d,0.0) == 1) {
        eqp->sol_1 = -(eqp->b) / (2 * (eqp->a));
        return SOL_1;
    }

    /* BASED solution v lob */
    eqp->sol_1 = (-(eqp->b) - sd) / (2 * (eqp->a));
    eqp->sol_2 = (-(eqp->b) + sd) / (2 * (eqp->a));
    return SOL_2;
}

/* doubles are equal if |a-b| < EPS */
int is_equal(double a, double b) {
    return (a > b) ? (a - b < EPS) : (b - a < EPS);
}
