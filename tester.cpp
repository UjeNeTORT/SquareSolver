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

    struct equation testEq = {0, 0, 0, 0, 0, -1};
    struct test_reference testRef = {0, 0, 0, 0};
    
    int testsPassed = 0, nLastTest = 0;

    while (fscanf(fp, "%d. %lf %lf %lf | %d %lf %lf\n", 
                    &testRef.nTest, &testEq.a, &testEq.b, &testEq.c, &testRef.nRoots, &testRef.x1, &testRef.x2) == 7) {

        solveSquare(&testEq);

        if (testEq.nRoots != testRef.nRoots)
            printf("Test %d FAILED: wrong nRoots\n", testRef.nTest);
        else if (!isEqual(testEq.x1, testRef.x1))
            printf("Test %d FAILED: wrong x1\n", testRef.nTest);
        else if (!isEqual(testEq.x2, testRef.x2))
            printf("Test %d FAILED: wrong x2\n", testRef.nTest);
        else {
            printf("Test %d PASSED\n", testRef.nTest);
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

void resetTestRef(struct test_reference *testRef) {
    *testRef = {0, 0, 0, 0};
}
