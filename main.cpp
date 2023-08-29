#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "cmdLine.h"
#include "equation.h"
#include "get_print_eq.h"
#include "square_solver.h"
#include "tester.h"

#define DEBUG_V 1

//-----------------------------------------------------
/**
 * @brief main-function
 * @details
 * depending on what cmd-line arguments are it can:\n
 * --test        runs all the unit-tests from the test_cases file\n
 * --help        print the info about the program and print the help message about the cmd flags (does not launch program)\n
 *
 *
 * @returns 0 - default\n
 *          1 - if user typed in too much shit\n
 *          2 - if EOF\n
*/
int main(int argc, const char *argv[]) {

    int launchDefaultFlag = 1;

    #if DEBUG_V == 1
    processCmdFlags(argc, argv, &launchDefaultFlag);
    #endif

    if (launchDefaultFlag) {

        struct equation eq = {0, 0, 0, 0, 0, -1};

        int resGetCoefs = readCoefs(&eq);

        if (resGetCoefs == ERR_OVERFLOW_INPUT)
        {
            fprintf(stderr, "Program can't run further: input overflow\n");
            return 1;
        }
        else if (resGetCoefs == ERR_EOF)
        {
            fprintf(stderr, "Program cant run further: end of the file\n");
            return 2;
        }

        solveSquare(&eq);

        printResult(&eq);
    }

    return 0;
}


