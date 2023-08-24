#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include "equation.h"
#include "square_solver.h"


void solveSquare(struct equation *eq) {
    assert (eq);

    if (isEqual(eq->a, 0) && isEqual(eq->b, 0) && isEqual(eq->c, 0)) 
        eq->nRoots = ROOTS_INF;
    else if (!isEqual(eq->a, 0.0)) 
        solveQuadrEq(eq->a, eq->b, eq->c, &eq->x1, &eq->x2, &eq->nRoots);
    else if (!isEqual(eq->b, 0.0)) {
        solveLinEq(eq->b, eq->c, &eq->x1);
        eq->nRoots = ROOTS_1;
        eq->x2 = eq->x1;
    }
    else 
        eq->nRoots = ROOTS_0;
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

    if (isEqual(discriminant, 0))
        discriminant = 0;
    
    double sqrtDiscriminant = sqrt(discriminant); 

    // in case discriminant == -0:
    if (isEqual(discriminant, 0)) {
        *x1 = *x2 = -b / (2 * a);
        *nRoots = ROOTS_1;
    } else if (discriminant < 0) {
        *nRoots = ROOTS_0;
    } else {
        *x1 = (-b - sqrtDiscriminant) / (2 * a);
        *x2 = (-b + sqrtDiscriminant) / (2 * a);
        if (x1 > x2)
            swapDbl(x1, x2);
        *nRoots = ROOTS_2;
    }
}

void solveLinEq (const double a, const double b, double *x) {
    assert (isfinite (a));
    assert (!isEqual(a, 0));
    assert (isfinite (b));

    assert (x);

    *x = -b / a;
}

void swapDbl(double *a, double *b) {
    double temp = *a;
    *a = *b;
    *b = temp;
}

int isEqual(const double a, const double b) {
    return (fabs(a-b) < EPS);
}
