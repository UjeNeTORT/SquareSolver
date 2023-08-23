#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include "equation.h"
#include "tester.h"
#include "square_solver.h"


//-----------------------------------------------------
/**
 * @brief function-tester which tests solveSquare function and prints the test result in std output
 * @details
 * reads test cases from a file specified in fopen(...)\n
 * 
 * initializes struct equation testEq, later fills it with a, b, c coefs from test cases file\n
 * initializes struct test_reference testRef, later fills it with test answers and test number\n
 * 
 * testEq and testRef are reset to their initial value at the end of each iteration\n
 * 
 * defines two variables (testsPassed, nLastTest) which are used later for printing test results\n
 * if test passed it prints it\n
 * if test failed it prints what is wrong\n
 * 
*/
//-----------------------------------------------------
void testSolveInput(void) {
    
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

//-----------------------------------------------------
/**
 * @brief resets eq to initial value
 * @param [out] eq struct equation, which has all the necessary information about the equation (coefs, roots, number of roots)
*/
//-----------------------------------------------------
void resetEq(struct equation *eq) {
    *eq = {0, 0, 0, 0, 0, -1};
}

//-----------------------------------------------------
/**
 * @brief resets testRef to initial value
 * @param [out] testRef pointer to struct test_reference variable testRef
*/
//-----------------------------------------------------
void resetTestRef(struct test_reference *testRef) {
    *testRef = {0, 0, 0, 0};
}
