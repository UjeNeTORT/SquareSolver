#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "cmdLine.h"
#include "equation.h"
#include "tester.h"

//-----------------------------------------------------
/**
 * @brief prints info message about the program author and possible custom compilation flags\n
*/
static void printHelp(void);

//-----------------------------------------------------
/**
 * @brief prints error message if flag was incorrect
 * @param [out] flagValue flag itself
*/
static void printFlagErr(const char *flagValue);

void processCmdFlags(int argc, const char *argv[], int *launchDefaultFlag) {
    const char *flagValue = NULL;

    while (--argc > 0) {
        flagValue = *++argv;

        if (strcmp(flagValue, FLG_TEST) == 0) {
            *launchDefaultFlag = 0;

            argv++;

            if (argc > 0 || !isalnum(**argv)) {
                testSolveSquare(DFLT_TEST_FILE);
                argv--;
            } else {
                testSolveSquare(*argv);
            }

        } else if (strcmp(flagValue, FLG_HELP) == 0) {
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
    assert (flagValue);

    fprintf(stderr, "Invalid command line argument \"%s\"\n"
                    "To learn about possible flags use --help flag\n\n", flagValue);
}
