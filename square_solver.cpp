#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>

const double EPS = 1e-6;

//-----------------------------------------------------
/**
 * @enum roots_num
*/
//-----------------------------------------------------
enum roots_num {
    ROOTS_0 = 0,
    ROOTS_1 = 1,
    ROOTS_2 = 2,
    ROOTS_INF = 3,
};

//-----------------------------------------------------
/**
 * @struct equation
 * @brief used to store info about quadratic equation ax^2 + bx + c = 0
*/
//-----------------------------------------------------
struct equation {
    double a, b, c; 
    double x1, x2;
    int nRoots;
}; 

//-----------------------------------------------------
/**
 * @struct test_reference
 * @brief used to store number of the test_case  and answers to it (number of roots of equation and roots themselves x1, x2) 
*/
//-----------------------------------------------------
struct test_reference {
    int nTest;
    double x1, x2;
    int nRoots;
};


void solveSquare (struct equation *eq);

void solveQuadrEq (const double a, const double b, const double c, double *x1, double *x2, int *nRoots);
void solveLinEq (const double b, const double c, double *x, int *nRoots);
void solveInfRoots (int *nRoots);
void handleCoefError (int *nRoots);

void testSolveInput(void);

void resetEq(struct equation *eq);
void resetTestRef(struct test_reference *testRef);

int isEqual(const double a, const double b);

//-----------------------------------------------------
/**
 * @brief given the equation coeffs it decides which function to use to solve the equation
 * @param [out] eq struct equation, which has all the necessary information about the equation (coefs, roots, number of roots)
 * 
 * @details
 * in equation ax^2 + bx + c = 0 we know a, b, c coeffs (from eq)\n
 * 
 * based on what these coeffs are, it solves the equation:\n
 * 
 * if (a == 0 && b == 0 && c == 0) calls func solveInfRoots(...)\n
 * else if (a != 0)                calls func solveQuadrEq(...)\n
 * else if (a != 0 && b != 0)      calls func solveLinEq(...)\n
 * else                            calls func handleCoefError(...)\n
*/
//-----------------------------------------------------
void solveSquare(struct equation *eq) {
    assert (eq);

    if (isEqual(eq->a, 0) && isEqual(eq->b, 0) && isEqual(eq->c, 0)) 
        eq->nRoots = ROOTS_INF;
    else if (!isEqual(eq->a, 0.0)) 
        solveQuadrEq(eq->a, eq->b, eq->c, &eq->x1, &eq->x2, &eq->nRoots);
    else if (!isEqual(eq->b, 0.0)) {
        solveLinEq(eq->b, eq->c, &eq->x1, &eq->nRoots);
        eq->x2 = eq->x1;
    }
    else 
        eq->nRoots = ROOTS_0;
}

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
 * @brief solves quadratic equation ax^2 + bx + c = 0
 * @param [in]  a a-coefficient
 * @param [in]  b b-coefficient
 * @param [in]  c c-coefficient
 * @param [out] x1 smaller root
 * @param [out] x2 bigger root
 * @param [out] nRoots number of roots of the equation
 * 
 * @details
 * if equation has no roots, nRoots = 0, x1 = 0, x2 = 0\n
 * if equation has 1 root,   nRoots = 1, x1 = x2 = *root of equation*\n
 * if equation has 2 roots,  nRoots = 2, x1 = *smaller root*, x2 = *bigger root*
*/
//-----------------------------------------------------
void solveQuadrEq(const double a, const double b, const double c, double *x1, double *x2, int *nRoots) {
    assert (isfinite (a));
    assert (a);
    assert (isfinite (b));
    assert (isfinite (c));

    assert (x1); 
    assert (x2); 
    assert (nRoots); 
    assert (x1 != x2);

    double discriminant = b * b - 4 * a * c;
    double sqrtDiscriminant = sqrt(discriminant); 

    if (discriminant < 0) {
        *nRoots = ROOTS_0;
    } else if (isEqual(discriminant, 0)) {
        *x1 = *x2 = -b / (2 * a);
        *nRoots = ROOTS_1;
    } else {
        *x1 = (-b - sqrtDiscriminant) / (2 * a);
        *x2 = (-b + sqrtDiscriminant) / (2 * a);
        *nRoots = ROOTS_2;
    }
}
// strerror()
// errnoelse 
//-----------------------------------------------------
/**
 * @brief solves linear equation ax + b = 0 
 * @param [in] a a-coefficient
 * @param [in] b b-coefficient
 * @param [out] x solution of the equation
*/
//-----------------------------------------------------
void solveLinEq (const double a, const double b, double *x, int *nRoots) {
    assert (isfinite (a));
    assert (a);
    assert (isfinite (b));

    assert (x);      
    assert (nRoots);

    *x = -b / a;
    *nRoots = ROOTS_1;
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

//-----------------------------------------------------
/**
 * @brief compares two double values, returns 1 if equal, 0 if not
 * @param [in] a a-variable
 * @param [in] b b-variable
 * 
 * @details
 * a == b if |a-b| < EPS,
 * where EPS is const and defined outside the function
*/
//-----------------------------------------------------
int isEqual(const double a, const double b) {
    return (fabs(a-b) < EPS);
}

// TODO:
// - documentation to structs and enums
// - learn how to output coloured strings
// 