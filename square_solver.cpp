#include "equation.h"
#include "square_solver.h"
#include <assert.h>
#include <math.h>

//-----------------------------------------------------
/**
 * @brief swaps doubles a and b
 * @param [out] a a-variable
 * @param [out] b b-variable
 * @details 
 * swaps doubles a and b using temporary variable temp 
*/
static void swapDbl(double *a, double *b);

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
    assert (isfinite (b));
    assert (isfinite (c));
    assert (!isEqual(a, 0));

    assert (x1); 
    assert (x2);
    assert (nRoots);
    assert (x1 != x2);

    double discriminant = b * b - 4 * a * c;

    if (isEqual(discriminant, 0)) {
        *x1 = *x2 = -b / (2 * a);
        *nRoots = 1;
    } else if (discriminant < 0) {
        *nRoots = 0;
    } else {
        double sqrtDiscriminant = 0;

        if (isEqual(c, 0)) 
            sqrtDiscriminant = b;
        else
            sqrtDiscriminant = sqrt(discriminant); 

        *x1 = (-b - sqrtDiscriminant) / (2 * a);
        *x2 = (-b + sqrtDiscriminant) / (2 * a);

        *nRoots = 2; 

        if (*x1 > *x2)
            swapDbl(x1, x2);
    }
}

void solveLinEq (const double a, const double b, double *x, int *nRoots) {
    assert (isfinite (a));
    assert (isfinite (b));

    assert (x);
    assert (nRoots);


    if (!isEqual(a, 0)) {
        *x = -b / a;
        *nRoots = 1;
    } else if (isEqual(b, 0)) {
        *nRoots = ROOTS_INF;
    } else {
        *nRoots = 0;
    }

}

static void swapDbl(double *a, double *b) {
    assert (a);
    assert (b);
    double temp = *a;
    *a = *b;
    *b = temp;
}

int isEqual(const double a, const double b) {
    // check if not infinity or nan
    assert (isfinite(a));
    assert (isfinite(b));

    return (fabs(a - b) < EPS);
}
