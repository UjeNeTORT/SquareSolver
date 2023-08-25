#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "equation.h"
#include "get_print_eq.h"
#include "square_solver.h"
#include "tester.h"

//-----------------------------------------------------
/**
 * @brief processes cmd-line args and sets flags
 * 
 * @param [in] argc               copy of param *argc* from main
 * @param [in] argv               copy of param *argv* from main
 * 
 * @param [out] testModeFLag      is set to 1 if -test typed in\n
 *                                (later it is used to start testing), initial value is 0
 * 
 * @param [out] printInfoFlag     is set to 1 if  -info typed in\n
 *                                (later it is used to print info about the program(, initial value is 0
 * 
 * @param [out] printHelpFLag     is set to 1 if -help typed in\n
 * 
 * 
 * @details 
 * Iterates through argv array while first symbol of the next argument is '-'.\n
 * It sets flagValue equal to the rest of the current argument (without '-').\n\n
 * 
 * if (flagValue == "-test")\n     sets testModeFLag to 1\n\n
 * if (flagValue == "-info")\n     sets printInfoFlag to 1\n\n
 * if (flagValuse == "-help")\n    sets printHelpFlag to 1\n\n
 * else\n                          prints error message\n\n
 * 
 * 
*/
static void getCmdFlags(int argc, char *argv[], int *testModeFlag, int *printInfoFlag, int *printHelpFlag);

//-----------------------------------------------------
/**
 * @brief prints info message: name of the program, author and year before the rest of program
*/
static void printInfo(void);

/**
 * @brief prints info message about possible custom compilation flags\n 
*/
static void printHelp();


//-----------------------------------------------------
/**
 * @brief main-function
 * @details
 * depending on what cmd-line arguments are it can:\n
 * --test        runs all the unit-tests from the test_cases file\n
 * --info        print the info about the program before its launch\n
 * --help        print the help message about the cmd flags (does not launch program)\n
 * 
 * 
 * @returns 0 - default\n
 *          1 - if user typed in too much shit\n
 *          2 - if EOF\n
*/
int main(int argc, char *argv[]) {

    int launchDefaultFlag = 1;
    
    int testModeFlag = 0, printInfoFlag = 0, printHelpFlag = 0;

    getCmdFlags(argc, argv, &testModeFlag, &printInfoFlag, &printHelpFlag);

    if (printInfoFlag) {
        printInfo();
    }

    if (printHelpFlag) {
        printHelp();
        launchDefaultFlag = 0;
    }
    
    if (testModeFlag) {
        testSolveSquare();
        launchDefaultFlag = 0;
    }

    if (launchDefaultFlag) {

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

static void getCmdFlags(int argc, char *argv[], int *testModeFlag, int *printInfoFlag, int *printHelpFlag) {
    char *flagValue;

    while (--argc > 0 && **++argv == '-') {
        flagValue = ++*argv;

        if (strcmp(flagValue, "-test") == 0)
            *testModeFlag = 1;
        else if (strcmp(flagValue, "-info") == 0)
            *printInfoFlag = 1;
        else if (strcmp(flagValue, "-help") == 0)
            *printHelpFlag = 1;
        else
            printf("Invalid command line argument \"%s\"\n"
                   "To learn about possible flags use --help flag\n\n", flagValue);
    }
}

static void printInfo() {
    printf("# Square equation solver\n"
           "# (copyright concretno) Yaroslav, 2023\n\n");
}

static void printHelp() {
    printf("Options:\n"
           "--help   prints info about compilation flags\n"
           "--info   shows info about the program, its author and year of publishing\n"
           "--test   starts unit-testing and prints info about it results\n\n");
}
