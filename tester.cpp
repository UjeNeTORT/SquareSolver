#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include "equation.h"
#include "tester.h"
#include "square_solver.h"


void testSolveSquare(const char *fname) {

    FILE *fp = NULL;

    if (strcmp(fname, "default") == 0)
        fp = fopen(DFLT_TEST_FILE, "r");
    else
        fp = fopen(fname, "r");

    if (fp == NULL) {
        printf("Unable to open the %s file, check if it's name is correct\n", fname);
        return ;
    }


    struct equation testEq = {0, 0, 0, 0, 0, -1};
    struct testReference testRef = {0, 0, 0, 0};
    
    int testsPassed = 0, nLastTest = 0;

    while (fscanf(fp, "%d. %lf %lf %lf | %d %lf %lf\n", 
                    &testRef.nTest, &testEq.a, &testEq.b, &testEq.c, &testRef.nRoots, &testRef.x1, &testRef.x2) == 7) {

        solveSquare(&testEq);

        if (testEq.nRoots != testRef.nRoots) {
            printf("Test %-4d FAILED\n"
                   "Wrong nRoots: expected %d, received %d\n", testRef.nTest, testRef.nRoots, testEq.nRoots);
        } else if (!isEqual(testRef.x1, testRef.x2) && isEqual(testEq.x1, testRef.x2) && isEqual(testEq.x2, testRef.x1)) {
            printf("Test %-4d FAILED\n"
                   "Wrong order: expected (%lf %lf), received (%lf %lf)\n", testRef.nTest, testRef.x1, testRef.x2, testEq.x1, testEq.x2);
        } else if (!isEqual(testEq.x1, testRef.x1)) {
            printf("Test %-4d FAILED\n"
                   "x1: expected %lf, received %lf\n", testRef.nTest, testRef.x1, testEq.x1);
        } else if (!isEqual(testEq.x2, testRef.x2)) {
            printf("Test %-4d FAILED\n"
                   "x2: expected %lf, received %lf\n", testRef.nTest, testRef.x2, testEq.x2);
        } else {
            printf("Test %-4d PASSED\n", testRef.nTest);
            testsPassed++;
        }

        nLastTest = testRef.nTest;

        resetEq(&testEq);
        resetTestRef(&testRef);
    }

    fclose(fp);

    printf("##########################\n"
           "TESTING FINISHED\n"
           "PASSED [%d/%d] %.lf %%\n"
           "##########################\n", testsPassed, nLastTest, (double) testsPassed / nLastTest * 100);
}

void resetEq(struct equation *eq) {
    *eq = {0, 0, 0, 0, 0, -1};
}

void resetTestRef(struct testReference *testRef) {
    *testRef = {0, 0, 0, 0};
}
