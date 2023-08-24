#ifndef EQUATION_H
#define EQUATION_H

//-----------------------------------------------------
/**
 * @struct equation
 * @brief used to store info about quadratic equation ax^2 + bx + c = 0
*/
struct equation {
    double a, b, c;  ///< quadratic equation coefficients
    double x1, x2;   ///< quadratic equation roots (x1-smaller. x2-bigger)
    int    nRoots;   ///< number of roots
};

//-----------------------------------------------------
/**
 * @enum RootsNum
*/
enum RootsNum {
    ROOTS_0   = 0,   ///< no roots 
    ROOTS_1   = 1,   ///< 1 root
    ROOTS_2   = 2,   ///< 2 roots
    ROOTS_INF = 3,   ///< infinite roots
};

#endif
