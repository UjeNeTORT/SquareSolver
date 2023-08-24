#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include "equation.h"
#include "square_solver.h"


void solveSquare(struct equation *eq) {
    assert (eq);
        
    if (!isEqual(eq->a, 0.0)) {
        solveQuadrEq(eq->a, eq->b, eq->c, &eq->x1, &eq->x2, &eq->nRoots);
    } else {
        solveLinEq(eq->b, eq->c, &eq->x1, &eq->nRoots);
        if (eq->nRoots == 1)
            eq->x2 = eq->x1;
    }
}

void solveQuadrEq(const double a, const double b, const double c, double *x1, double *x2, int *nRoots) {
    assert (isfinite (a));
    assert (!isEqual(a, 0));
    assert (isfinite (b));
    assert (isfinite (c));

    assert (x1); 
    assert (x2);
    assert (nRoots);
    assert (x1 != x2);

    double discriminant = b * b - 4 * a * c;

    if (isEqual(discriminant, 0)) {
        *x1 = *x2 = -b / (2 * a);
        *nRoots = ROOTS_1;
    } else if (discriminant < 0) {
        *nRoots = ROOTS_0;
    } else {
        double sqrtDiscriminant = 0;

        if (isEqual(c, 0)) 
            sqrtDiscriminant = b;
        else
            sqrtDiscriminant = sqrt(discriminant); 

        *x1 = (-b - sqrtDiscriminant) / (2 * a);
        *x2 = (-b + sqrtDiscriminant) / (2 * a);

        *nRoots = ROOTS_2;

        if (*x1 > *x2)
            swapDbl(x1, x2);
    }
}

void solveLinEq (const double a, const double b, double *x, int *nRoots) {
    assert (isfinite (a));
    assert (isfinite (b));

    assert (x);


    if (!isEqual(a, 0)) {
        *x = -b / a;
        *nRoots = ROOTS_1;
    } else if (isEqual(b, 0)) {
        *nRoots = ROOTS_INF;
    } else {
        *nRoots = ROOTS_0;
    }

}

void swapDbl(double *a, double *b) {
    assert (a);
    assert (b);
    double temp = *a;
    *a = *b;
    *b = temp;
}

int isEqual(const double a, const double b) {
    return (fabs(a - b) < EPS);
}
