#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "equation.h"
#include "get_print_eq.h"
#include "square_solver.h"
#include "tester.h"

static void getCmdFlags(int argc, char *argv[], int *testModeFlag, int *printInfoFlag);
static void printInfo(void);

//-----------------------------------------------------
/**
 * @brief main-function
 * @details
 * depending on what cmd-line arguments are it can:\n
 * -h           print the header before\n
 * -test        enables test-mode (runs all the tests from the test_cases file)\n
 * 
 * @returns 0 - default\n
 *          1 - if user typed in too much shit\n
 *          2 - if EOF\n
*/
//-----------------------------------------------------
int main(int argc, char *argv[]) {

    int testModeFlag = 0, printInfoFlag = 0;

    getCmdFlags(argc, argv, &testModeFlag, &printInfoFlag);

    if (printInfoFlag) {
        printInfo();
    }

    if (testModeFlag) {
        testSolveSquare();
    } else {

        struct equation eq = {0, 0, 0, 0, 0, -1};

        int resGetCoefs = getCoefs(&eq);

        if (resGetCoefs == ERR_OVERFLOW_INPUT) {
            printf("too many mistakes\n");
            return 1;
        } else if (resGetCoefs == ERR_EOF) {
            printf("end of the file\n");
            return 2;
        }

        solveSquare(&eq);

        printResult(&eq);
    }

    return 0;
}


/**
 * @brief processes cmd-line args and sets flags
 * 
 * @param [in] argc               copy of param *argc* from main
 * @param [in] argv               copy of param *argv* from main
 * 
 * @param [out] testModeFLag      is set to 1 if -test typed in\n
 *                                (later it is used to start testing), initial value is 0
 * 
 * @param [out] printInfoFlag     is set to 1 if  -h typed in\n
 *                                (later it is used to print info about the program(, initial value is 0
 * 
 * @details 
 * Iterates through argv array while first symbol of the next argument is '-'.\n
 * It sets flagValue equal to the rest of the current argument (without '-').\n\n
 * 
 * if (flagValue == "test")\n      sets testModeFLag to 1\n\n
 * if (flagValue == "h")\n         sets printInfoFlag to 1\n\n
 * else\n                          prints error message\n\n
 * 
 * 
*/
static void getCmdFlags(int argc, char *argv[], int *testModeFlag, int *printInfoFlag) {
    char *flagValue;

    while (--argc > 0 && **++argv == '-') {
        flagValue = ++*argv;

        if (strcmp(flagValue, "test") == 0)
            *testModeFlag = 1;
        else if (strcmp(flagValue, "h") == 0)
            *printInfoFlag = 1;
        else
            printf("Invalid arguments \"%s\"\n"
                   "Launch in solve-equation mode\n\n", flagValue);
    }
}

//-----------------------------------------------------
/**
 * @brief prints info message: name of the program, author and year before the rest of program
*/
//-----------------------------------------------------
static void printInfo(void) {
    printf("# Square equation solver\n"
           "# (copyright concretno) Yaroslav, 2023\n\n");
}
