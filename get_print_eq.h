#ifndef GET_PRINT_EQ_H
#define GET_PRINT_EQ_H

//-----------------------------------------------------
/**
 * @enum InputErrs
*/
enum InputErrs {
    ERR_OVERFLOW_INPUT = 1, ///< if too many mistakes 
    ERR_EOF = 2             ///< if EOF occures
};

//-----------------------------------------------------
/**
 * @brief gets coeffs for quadratic equation from input
 * @param [out] eq struct equation, which has all the necessary information about the equation (coefs, roots, number of roots)
 * 
 * @details
 * uses scanf to get coefficients from standart input,\n
 * scanf accepts only 3 double numbers separated by '\n' or ' ' or '\t'\n
 * if it cannot scan the numbers       it asks user to try again and increases counter of mistakes\n
 * if user does too many mistakes      it stops the program by returning enums which stop program in main\n
 * or if it is the EOF\n                 
 * if user mistakes during the input   it does not read the rest of the line and asks to try again\n
 * (for example types in a letter)\n
*/
int readCoefs (struct equation *eq);

//-----------------------------------------------------
/**
 * @brief prints how much solution does the equation eq has ans the roots
 * @param [out] eq struct equation, which has all the necessary information about the equation (coefs, roots, number of roots)
 * @details
 * if 0 roots               it prints *no solutions*\n
 * if 1 root                it prints *1 solution:* and the root\n
 * if 2 roots               it prints *2 solutions:*, the smaller root and then the bigger root\n
 * if roots are infinite    it prints *infinite solutions*\n
*/
void printResult(struct equation *eq);

#endif
