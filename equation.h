#ifndef EQUATION_H
#define EQUATION_H

//-----------------------------------------------------
/**
 * @struct equation
 * @brief used to store info about quadratic equation ax^2 + bx + c = 0
*/
struct equation {
    double a;       ///< a-coefficient
    double b;       ///< b-coefficient
    double c;       ///< c-coefficient
    double x1;      ///< smaller equation root
    double x2;      ///< bigger equation root
    int nRoots;     ///< number of roots
};

//-----------------------------------------------------
/**
 * @enum RootsNum
*/
enum RootsNum {
    ROOTS_INF = 3,   ///< infinite roots
};

#endif
