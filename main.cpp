#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "equation.h"
#include "get_print_eq.h"
#include "square_solver.h"
#include "tester.h"


struct cmdLineFlags {
    int launchDefaultFlag;  ///< if 1 - default mode, if 0 - stops execution after flag-connected stuff
    int testModeFlag;       ///< if 1 - program launches in test mode
    int printHelpFlag;      ///< if 1 - prints info about the program and cmd line args possible
};
//-----------------------------------------------------
/**
 * @brief processes cmd-line args and sets flags
 * 
 * @param [in] argc               copy of param *argc* from main
 * @param [in] argv               copy of param *argv* from main
 * 
 * @param [out] flags             stores all the cmd line flags 
 * 
 * @details 
 * Iterates through argv array while first symbol of the next argument is '-'.\n
 * It sets flagValue equal to the rest of the current argument (without '-').\n\n
 * 
 * if (flagValue == "-test")\n     sets flags.testModeFLag to 1\n\n
 * if (flagValue == "-info")\n     sets flags.printInfoFlag to 1\n\n
 * if (flagValuse == "-help")\n    sets flags.printHelpFlag to 1\n\n
 * else\n                          prints error message\n\n
 * 
 * 
*/
static void getCmdFlags(int argc, char *argv[], struct cmdLineFlags *flags);

/**
 * @brief prints info message about the program author and possible custom compilation flags\n 
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
    
    struct cmdLineFlags flags = {1, 0, 0};

    getCmdFlags(argc, argv, &flags);

    if (flags.printHelpFlag) {
        printHelp();
        flags.launchDefaultFlag = 0;
    }
    
    if (flags.testModeFlag) {
        testSolveSquare();
        flags.launchDefaultFlag = 0;
    }

    if (flags.launchDefaultFlag) {

        struct equation eq = {0, 0, 0, 0, 0, -1};

        int resGetCoefs = readCoefs(&eq);

        if (resGetCoefs == ERR_OVERFLOW_INPUT) {
            printf("Program cant run further: input overflow\n");
            return 1;
        } else if (resGetCoefs == ERR_EOF) {
            printf("Program cant run further: end of the file\n");
            return 2;
        }

        solveSquare(&eq);

        printResult(&eq);
    }

    return 0;
}

static void getCmdFlags(int argc, char *argv[], struct cmdLineFlags *flags) {
    char *flagValue;

    while (--argc > 0 && **++argv == '-') {
        flagValue = ++*argv;

        if (strcmp(flagValue, "-test") == 0)
            flags->testModeFlag = 1;
        else if (strcmp(flagValue, "-help") == 0)
            flags->printHelpFlag = 1;
        else
            printf("Invalid command line argument \"%s\"\n"
                   "To learn about possible flags use --help flag\n\n", flagValue);
    }
}

static void printHelp() {
    printf("# Square equation solver\n"
           "# (copyright) Yaroslav, 2023\n\n"
           "Options:\n"
           "--help   prints info about compilation flags\n"
           "--info   shows info about the program, its author and year of publishing\n"
           "--test   starts unit-testing and prints info about it results\n\n");
}
