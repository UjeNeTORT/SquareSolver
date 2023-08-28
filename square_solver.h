#ifndef SQUARE_SOLVER_H
#define SQUARE_SOLVER_H

static const double EPS = 1e-6;

//-----------------------------------------------------
/**
 * @brief given the equation coeffs it solves the equation
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
void solveSquare (struct equation *eq);

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
void solveQuadrEq(const double a, const double b, const double c, double *x1, double *x2, int *nRoots);

//-----------------------------------------------------
/**
 * @brief solves linear equation ax + b = 0 
 * @param [in]  a       a-coefficient
 * @param [in]  b       b-coefficient
 * @param [out] x       solution of the equation
 * @param [out] nRoots  number of roots of equation
*/
void solveLinEq (const double a, const double b, double *x, int *nRoots);

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
int isEqual(const double a, const double b);

#endif
