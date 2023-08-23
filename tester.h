void testSolveInput(void);
void resetEq(struct equation *eq);
void resetTestRef(struct test_reference *testRef);

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