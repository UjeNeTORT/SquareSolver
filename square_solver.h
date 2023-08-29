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
 * @brief compares two double values, returns 1 if equal, 0 if not
 * @param [in] a a-variable
 * @param [in] b b-variable
 *
 * @details
 * a == b if |a-b| < EPS,
 * where EPS is const and defined outside the function
*/
int isEqual(const double a, const double b);

#endif // SQUARE_SOLVER_H
