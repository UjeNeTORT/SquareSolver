#include <math.h>
#include <assert.h>
#include "equation.h"
#include "square_solver.h"


//-----------------------------------------------------
/**
 * @brief solves quadratic equation ax^2 + bx + c = 0
 * @param [in]  a      a-coefficient
 * @param [in]  b      b-coefficient
 * @param [in]  c      c-coefficient
 * @param [out] x1     smaller root
 * @param [out] x2     bigger root
 * @param [out] nRoots number of roots of the equation
 * 
 * @details
 * if equation has no roots, nRoots = 0, x1 = 0, x2 = 0\n
 * if equation has 1 root,   nRoots = 1, x1 = x2 = *root of equation*\n
 * if equation has 2 roots,  nRoots = 2, x1 = *smaller root*, x2 = *bigger root*
*/
static void solveQuadrEq(const double a, const double b, const double c, double *x1, double *x2, int *nRoots);

//-----------------------------------------------------
/**
 * @brief solves linear equation ax + b = 0 
 * @param [in]  a       a-coefficient
 * @param [in]  b       b-coefficient
 * @param [out] x       solution of the equation
 * @param [out] nRoots  number of roots of equation
*/
static void solveLinEq (const double a, const double b, double *x, int *nRoots);

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

static void solveQuadrEq(const double a, const double b, const double c, double *x1, double *x2, int *nRoots) {
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

static void solveLinEq (const double a, const double b, double *x, int *nRoots) {
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
    return (fabs(a - b) < EPS);
}
