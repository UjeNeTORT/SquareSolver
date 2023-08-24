#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include "equation.h"
#include "tester.h"
#include "square_solver.h"


void testSolveSquare(void) {
    
    FILE *fp = fopen("test_cases.txt", "r");

    struct equation testEq = {.a = 0, .b = 0, .c = 0, .x1 = 0, .x2 = 0, .nRoots = -1};
    struct test_reference testRef = {.nTest = 0, .x1 = 0, .x2 = 0, .nRoots = 0};
    
    int testsPassed = 0, nLastTest = 0;

    while (fscanf(fp, "%d. %lf %lf %lf | %d %lf %lf\n", 
                    &testRef.nTest, &testEq.a, &testEq.b, &testEq.c, &testRef.nRoots, &testRef.x1, &testRef.x2) == 7) {

        solveSquare(&testEq);

        // TODO moshneyshiy print
        if (testEq.nRoots != testRef.nRoots)
            printf("Test %-4d FAILED:\n"
                   "wrong nRoots: expected %d, received %d\n", testRef.nTest, testRef.nRoots, testEq.nRoots);
        else if (!isEqual(testRef.x1, testRef.x2) && isEqual(testEq.x1, testRef.x2) && isEqual(testEq.x2, testRef.x1))
            printf("Test %-4d FAILED: wrong order\n", testRef.nTest);
        else if (!isEqual(testEq.x1, testRef.x1)) 
            printf("Test %-4d FAILED:\n"
                   "x1: expected %lf, received %lf\n", testRef.nTest, testRef.x1, testEq.x1);
        else if (!isEqual(testEq.x2, testRef.x2))
            printf("Test %-4d FAILED:\n"
                   "x2: expected %lf, received %lf\n", testRef.nTest, testRef.x2, testEq.x2);
        else {
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
    *eq = {.a = 0, .b = 0, .c = 0, .x1 = 0, .x2 = 0, .nRoots = -1};
}

void resetTestRef(struct test_reference *testRef) {
    *testRef = {.nTest = 0, .x1 = 0, .x2 = 0, .nRoots = 0};
}
