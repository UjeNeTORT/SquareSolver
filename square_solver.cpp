#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include "equation.h"
#include "square_solver.h"


//-----------------------------------------------------
/**
 * @brief given the equation coeffs it decides which function to use to solve the equation
 * @param [out] eq struct equation, which has all the necessary information about the equation (coefs, roots, number of roots)
 * 
 * @details
 * in equation ax^2 + bx + c = 0 we know a, b, c coeffs (from eq)\n
 * 
 * based on what these coeffs are, it solves the equation:\n
 * 
 * if (a == 0 && b == 0 && c == 0) calls func solveInfRoots(...)\n
 * else if (a != 0)                calls func solveQuadrEq(...)\n
 * else if (a != 0 && b != 0)      calls func solveLinEq(...) and sets x2 = x1 (as we need it for tests)\n
 * else                            sets nRoots to ROOTS_0\n
*/
//-----------------------------------------------------
void solveSquare(struct equation *eq) {
    assert (eq);

    if (isEqual(eq->a, 0) && isEqual(eq->b, 0) && isEqual(eq->c, 0)) 
        eq->nRoots = ROOTS_INF;
    else if (!isEqual(eq->a, 0.0)) 
        solveQuadrEq(eq->a, eq->b, eq->c, &eq->x1, &eq->x2, &eq->nRoots);
    else if (!isEqual(eq->b, 0.0)) {
        solveLinEq(eq->b, eq->c, &eq->x1, &eq->nRoots);
        eq->x2 = eq->x1;
    }
    else 
        eq->nRoots = ROOTS_0;
}

//-----------------------------------------------------
/**
 * @brief solves quadratic equation ax^2 + bx + c = 0
 * @param [in]  a a-coefficient
 * @param [in]  b b-coefficient
 * @param [in]  c c-coefficient
 * @param [out] x1 smaller root
 * @param [out] x2 bigger root
 * @param [out] nRoots number of roots of the equation
 * 
 * @details
 * if equation has no roots, nRoots = 0, x1 = 0, x2 = 0\n
 * if equation has 1 root,   nRoots = 1, x1 = x2 = *root of equation*\n
 * if equation has 2 roots,  nRoots = 2, x1 = *smaller root*, x2 = *bigger root*
*/
//-----------------------------------------------------
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
        *nRoots = ROOTS_2;
    }
}


//-----------------------------------------------------
/**
 * @brief solves linear equation ax + b = 0 
 * @param [in] a a-coefficient, a != 0
 * @param [in] b b-coefficient
 * @param [out] x solution of the equation
*/
//-----------------------------------------------------
void solveLinEq (const double a, const double b, double *x, int *nRoots) {
    assert (isfinite (a));
    assert (!isEqual(a, 0));
    assert (isfinite (b));

    assert (x);      
    assert (nRoots);

    *x = -b / a;
    *nRoots = ROOTS_1;
}

//-----------------------------------------------------
/**
 * @brief compares two double values, returns 1 if equal, 0 if not
 * @param [in] a a-variable
 * @param [in] b b-variable
 * 
 * @details
 * a == b if |a-b| < EPS,
 * where EPS is const and defined outside the function
*/
//-----------------------------------------------------
int isEqual(const double a, const double b) {
    return (fabs(a-b) < EPS);
}
