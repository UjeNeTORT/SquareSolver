#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "equation.h"
#include "get_print_eq.h"
#include "square_solver.h"
#include "tester.h"


//-----------------------------------------------------
/**
 * @brief processes cmd-line args and sets flags
 * 
 * @param [in] argc                 copy of param *argc* from main
 * @param [in] argv                 copy of param *argv* from main
 * 
 * @param [out] launchDefaultFlag   1 - if after flags handling we should run the main program, 0 - if not 
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
static void getCmdFlags(int argc, char *argv[], int *launchDefaultFlag);

//-----------------------------------------------------
/**
 * @brief prints info message about the program author and possible custom compilation flags\n 
*/
static void printHelp();

//-----------------------------------------------------
/**
 * @brief prints error message if flag was incorrect 
 * @param [out] flagValue flag itself
*/
static void printFlagErr(const char *flagValue);

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

    getCmdFlags(argc, argv, &launchDefaultFlag);

    if (launchDefaultFlag) {

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

static void getCmdFlags(int argc, char *argv[], int *launchDefaultFlag) {
    char *flagValue;

    while (--argc > 0) {
        flagValue = *++argv;
        if (strcmp(flagValue, "--test") == 0) {
            *launchDefaultFlag = 0;

            argv++;

            if (!*argv || !isalnum(**argv)) {
                testSolveSquare("default");
                argv--;
            } else {
                testSolveSquare(*argv);
            }
        } else if (strcmp(flagValue, "--help") == 0) {
            printHelp();
            *launchDefaultFlag = 0;
        } else {
            printFlagErr(flagValue);
        }
    }
}

static void printHelp() {
    printf("# Square equation solver\n"
           "# (copyright) Yaroslav, 2023\n\n"
           "Options:\n"
           "--help   prints info about program, its author and compilation flags\n"
           "--test   starts unit-testing and prints info about it results\n\n");
}

static void printFlagErr(const char *flagValue) {
    printf("Invalid command line argument \"%s\"\n"
           "To learn about possible flags use --help flag\n\n", flagValue);    
}
