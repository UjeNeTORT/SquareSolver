//-----------------------------------------------------
/**
 * @struct test_reference
 * @brief used to store number of the test_case  and answers to it (number of roots of equation and roots themselves x1, x2) 
*/
//-----------------------------------------------------
struct test_reference {
    int nTest;      ///< number of testcase
    double x1, x2;  ///< x1 - smaller solution to the equation, x2 - bigger one (reference)
    int nRoots;     ///< number of roots (reference)
};

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
void testSolveSquare(void);

//-----------------------------------------------------
/**
 * @brief resets eq to initial value
 * @param [out] eq struct equation, which has all the necessary information about the equation (coefs, roots, number of roots)
*/
//-----------------------------------------------------
void resetEq(struct equation *eq);

//-----------------------------------------------------
/**
 * @brief resets testRef to initial value
 * @param [out] testRef pointer to struct test_reference variable testRef
*/
//-----------------------------------------------------
void resetTestRef(struct test_reference *testRef);
