#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "square_solver.cpp"

//-----------------------------------------------------
/**
 * @enum input_errors
*/
//-----------------------------------------------------
enum input_errs {
    ERR_OVERFLOW_INPUT = 1,
    ERR_EOF = 2  
};

int getCoefs (struct equation *eq);
void printResult(struct equation *eq);
void printInfo(void);

//-----------------------------------------------------
/**
 * @brief main-function
 * @details
 * depending on what cmd-line arguments are it can:\n
 * -h           print the header before\n
 * -test        enables test-mode (runs all the tests from the test_cases file)
*/
//-----------------------------------------------------
int main(int argc, char *argv[]) {

    int testModeFlag = 0, printInfoFlag = 0;
    char *flagName;

    while (--argc > 0 && **++argv == '-') {
        flagName = ++*argv;

        if (strcmp(flagName, "test") == 0)
            testModeFlag = 1;
        else if (strcmp(flagName, "h") == 0)
            printInfoFlag = 1;
        else 
            printf("Invalid arguments \"%s\"\n"
                   "Launch in solve-equation mode\n\n", flagName);
    }
    
    if (printInfoFlag)
        printInfo();

    if (testModeFlag) 
        testSolveInput();
        
    else {

        struct equation eq = {0, 0, 0, 0, 0, -1};

        int resGetCoefs = getCoefs(&eq); 

        if (resGetCoefs == ERR_EOF) {
            printf("end of the file\n");
            return 1;
        } else if (resGetCoefs == ERR_OVERFLOW_INPUT) {
            printf("too many mistakes\n");
            return 1;
        }

        solveSquare(&eq);

        printResult(&eq);
    }
    return 0;
}

//-----------------------------------------------------
/**
 * @brief gets coeffs for quadratic equation from input
 * @param [out] eq struct equation, which has all the necessary information about the equation (coefs, roots, number of roots)
 * 
 * @details
 * uses scanf to get coefficients from standart input,\n
 * acanf accepts only 3 double numbers separated by '\n' or ' ' or '\t'
 * if it cannot scan the numbers       it asks user to try again and increases counter of mistakes\n
 * if user does too many mistakes      it stops the program by returning enums which stop program in main\n
 * or if it is the EOF\n                 
 * if user mistakes during the input   it does not read the rest of the line and asks to try again\n
 * (for ex. types in a letter)\n
*/
//-----------------------------------------------------
int getCoefs(struct equation *eq) {
    assert (eq);
     
    static const unsigned MAX_MISTAKES = 10; 
    unsigned garbage = 0, cntWrngLines = 0;

    printf("# Please, enter a, b, c coefs:\n");

    while (scanf("%lf %lf %lf", &eq->a, &eq->b, &eq->c) != 3) {
        garbage = getchar();
        while (garbage != '\n' && garbage != EOF)
            garbage = getchar();
        if (garbage == EOF)
            return ERR_EOF;
        printf("Incorrect input, try again\n");
        if (cntWrngLines++ >= MAX_MISTAKES)
            return ERR_OVERFLOW_INPUT;
    }
    return 0;
}

//-----------------------------------------------------
/**
 * @brief prints how much solution does the equation eq has ans the roots
 * @param [out] eq struct equation, which has all the necessary information about the equation (coefs, roots, number of roots)
 * @details
 * if 0 roots               it prints *no solutions*\n
 * if 1 root                it prints *1 solution:* and the root\n
 * if 2 roots               it prints *2 solutions:* and the smaller root and then bigger root\n
 * if roots are infinite    it prints *infinite solutions*\n
*/
//-----------------------------------------------------
void printResult(struct equation *eq) {
    assert (eq);

    switch(eq->nRoots) {
        case ROOTS_0:
            printf("no solutions\n");
            break;
        case ROOTS_1: 
            printf("1 solution:\n"
                   "%.3lf\n", eq->x1);
            break;
        case ROOTS_2:
            printf("2 solutions:\n"
                   "%.3lf , %.3lf\n", eq->x1, eq->x2);
            break;
        case ROOTS_INF:
            printf("infinite solutions\n");
            break;
        default:
            printf("printResult: solveQuadrEq returned breeeed\n");
            break;
    }
}

//-----------------------------------------------------
/**
 * @brief prints info message: name of the program, author and year before the rest of program
*/
//-----------------------------------------------------
void printInfo(void) {
    printf("# Square equation solver\n"
           "# (copyright concretno) Yaroslav, 2023\n\n");
}

// TODO:
// - documentation to structs and enums
// - learn how to output coloured strings
// 