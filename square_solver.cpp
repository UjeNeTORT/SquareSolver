#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>


enum roots_num {
    ROOTS_0 = 0,
    ROOTS_1 = 1,
    ROOTS_2 = 2,
    ROOTS_INF = 3,
    ROOTS_ERR = 4
};

enum input_errs {
    ERR_TOO_MANY_MISTAKES = 1,
    ERR_EOF = 2  
};

/**
 * @brief structure which stores the information about the equation 
 * 
*/
struct equation {
    double a, b, c; 
    double x1, x2;
    int n_roots;
}; 

struct test_answer {
    int n_test;
    double x1, x2;
    int n_roots;
};


void solveInput (struct equation *eq);

void solveQuadrEq (const double a, const double b, const double c, double *x1, double *x2, int *n_roots);
void solveLinEq (const double b, const double c, double *x, int *n_roots);
void solveInfRoots (int *n_roots);
void handleCoefError (int *n_roots);

void test_solveInput(void);

int getCoefs (struct equation *eq);
void print_result(struct equation *eq);

void resetEq(struct equation *eq);
void resetTestAns(struct test_answer *test_ans);

int isEqual(const double a, const double b);


int main(int argc, char *argv[]) {

    int test_mode = 0, show_header = 0;

    while (--argc > 0 && **++argv == '-') {
        char *flag_name = ++*argv;

        if (strcmp(flag_name, "test") == 0)
            test_mode = 1;
        else if (strcmp(flag_name, "h") == 0)
            show_header = 1;
        else 
            printf("Invalid arguments\n");
    }
        

    if (show_header)
        printf("# Square equation solver\n"
               "# (copyright concretno) Yaroslav, 2023\n\n");

    if (test_mode) 
        test_solveInput();
    else {

        struct equation eq = {0, 0, 0, 0, 0, -1};

        printf("# Please, enter a, b, c coefs:\n"); 

        int res_getCoefs = getCoefs(&eq); 

        if (res_getCoefs == ERR_EOF) {
            printf("end of the file\n");
            return 1;
        } else if (res_getCoefs == ERR_TOO_MANY_MISTAKES) {
            printf("too many mistakes\n");
            return 1;
        }

        solveInput(&eq);

        print_result(&eq);
    }
    return 0;
}

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
 * if (a != 0)                     calls func solveQuadrEq(...)\n
 * if (a != 0 && b != 0)           calls func solveLinEq(...)\n
 * else                            calls func handleCoefError(...)\n
*/
//-----------------------------------------------------
void solveInput(struct equation *eq) {
    assert (eq);

    if (isEqual(eq->a, 0) && isEqual(eq->b, 0) && isEqual(eq->c, 0)) 
        solveInfRoots(&eq->n_roots);
    else if (!isEqual(eq->a, 0.0)) 
        solveQuadrEq(eq->a, eq->b, eq->c, &eq->x1, &eq->x2, &eq->n_roots);
    else if (!isEqual(eq->b, 0.0)) {
        solveLinEq(eq->b, eq->c, &eq->x1, &eq->n_roots);
        eq->x2 = eq->x1;
    }
    else
        handleCoefError(&eq->n_roots);
}

//-----------------------------------------------------
/**
 * @brief function-tester which tests solveInput function and prints the test result in std output
 * @details
 * reads test cases from a file specified in fopen(...)\n
 * 
 * initializes struct equation test_eq, later fills it with a, b, c coefs from test cases file\n
 * initializes struct test_answer test_ans, later fills it with test answers and test number\n
 * 
 * test_eq and test_ans are reset to their initial value at the end of each iteration\n
 * 
 * defines two variables (tests_passed, n_last_test) which are used later for printing test results\n
 * if test passed it prints it\n
 * if test failed it prints what is wrong\n
 * 
*/
//-----------------------------------------------------
void test_solveInput(void) {
    
    FILE *fp = fopen("test_cases.txt", "r");

    struct equation test_eq = {0, 0, 0, 0, 0, -1};
    struct test_answer test_ans = {0, 0, 0, 0};
    
    int tests_passed = 0, n_last_test = 0;

    while (fscanf(fp, "%d. %lf %lf %lf | %d %lf %lf\n", 
                     &test_ans.n_test, &test_eq.a, &test_eq.b, &test_eq.c, &test_ans.n_roots, &test_ans.x1, &test_ans.x2) == 7) {

        solveInput(&test_eq);

        if (test_eq.n_roots != test_ans.n_roots)
            printf("Test %d FAILED: wrong n_roots\n", test_ans.n_test);
        else if (!isEqual(test_eq.x1, test_ans.x1))
            printf("Test %d FAILED: wrong x1\n", test_ans.n_test);
        else if (!isEqual(test_eq.x2, test_ans.x2))
            printf("Test %d FAILED: wrong x2\n", test_ans.n_test);
        else {
            printf("Test %d PASSED\n", test_ans.n_test);
            tests_passed++;
        }

        n_last_test = test_ans.n_test;

        resetEq(&test_eq);
        resetTestAns(&test_ans);
    }
    fclose(fp);

    printf("##########################\n"
           "TESTING FINISHED\n"
           "PASSED [%d/%d] %.lf %%\n"
           "##########################\n", tests_passed, n_last_test, (double) tests_passed / n_last_test * 100);
}

//-----------------------------------------------------
/**
 * @brief gets coeffs for quadratic equation from input
 * @param [out] eq struct equation, which has all the necessary information about the equation (coefs, roots, number of roots)
 * 
 * @details
 * uses scanf to get coefficients from standart input,\n
 * acanf accepts only 3 double numbers separated by '\n' or ' ' or '\t'
 * if it cannot scan the numbers       it asks user to try again and increases counter of mistakes\n
 * if user does too many mistakes      it stops the program by returning enums which stop program in main\n
 * or if it is the EOF\n                 
 * if user mistakes during the input   it does not read the rest of the line and asks to try again\n
 * (for ex. types in a letter)\n
*/
//-----------------------------------------------------
int getCoefs(struct equation *eq) {
    assert (eq);

    static const unsigned MAX_MISTAKES = 10; 
    unsigned garbage = 0, cnt_mistakes = 0;
    while (scanf("%lf %lf %lf", &eq->a, &eq->b, &eq->c) != 3) {
        garbage = getchar();
        while (garbage != '\n' && garbage != EOF)
            garbage = getchar();
        if (garbage == EOF)
            return ERR_EOF;
        printf("Incorrect input, try again\n");
        if (cnt_mistakes++ >= MAX_MISTAKES)
            return ERR_TOO_MANY_MISTAKES;
    }
    return 0;
}

//-----------------------------------------------------
/**
 * @brief prints how much solution does the equation eq has ans the roots
 * @param [out] eq struct equation, which has all the necessary information about the equation (coefs, roots, number of roots)
 * @details
 * if 0 roots it prints *no solutions*\n
 * if 1 root  it prints *1 solution:* and the root\n
 * if 2 roots it prints *2 solutions:* and the smaller root and then bigger root\n
 * if roots are infinite it prints *infinite solutions*\n
*/
//-----------------------------------------------------
void print_result(struct equation *eq) {
    assert (eq);

    switch(eq->n_roots) {
        case ROOTS_ERR:
            printf("no solutions\n");
            break;
        case ROOTS_0:
            printf("no solutions\n");
            break;
        case ROOTS_1: 
            printf("1 solution:\n"
                   "%.3lf\n", eq->x1);
            break;
        case ROOTS_2:
            printf("2 solutions:\n"
                   "%.3lf , %.3lf\n", eq->x1, eq->x2);
            break;
        case ROOTS_INF:
            printf("infinite solutions\n");
            break;
        default:
            printf("print_result: solveQuadrEq returned breeeed\n");
            break;
    }
}

//-----------------------------------------------------
/**
 * @brief solves quadratic equation ax^2 + bx + c = 0
 * @param [in]  a a-coefficient
 * @param [in]  b b-coefficient
 * @param [in]  c c-coefficient
 * @param [out] x1 smaller root
 * @param [out] x2 bigger root
 * @param [out] n_roots number of roots of the equation
 * 
 * @details
 * if equation has no roots, n_roots = 0, x1 = 0, x2 = 0\n
 * if equation has 1 root,   n_roots = 1, x1 = x2 = *root of equation*\n
 * if equation has 2 roots,  n_roots = 2, x1 = *smaller root*, x2 = *bigger root*
*/
//-----------------------------------------------------
void solveQuadrEq(const double a, const double b, const double c, double *x1, double *x2, int *n_roots) {
    assert (isfinite (a));
    assert (a);
    assert (isfinite (b));
    assert (isfinite (c));

    assert (x1); 
    assert (x2); 
    assert (n_roots); 
    assert (x1 != x2);

    double discriminant = b * b - 4 * a * c;
    double sqrt_discriminant = sqrt(discriminant); 

    if (discriminant < 0) {
        *n_roots = ROOTS_0;
    } else if (isEqual(discriminant, 0)) {
        *x1 = *x2 = -b / (2 * a);
        *n_roots = ROOTS_1;
    } else {
        *x1 = (-b - sqrt_discriminant) / (2 * a);
        *x2 = (-b + sqrt_discriminant) / (2 * a);
        *n_roots = ROOTS_2;
    }
}

//-----------------------------------------------------
/**
 * @brief solves linear equation ax + b = 0 
 * @param [in] a a-coefficient
 * @param [in] b b-coefficient
 * @param [out] x solution of the equation
*/
//-----------------------------------------------------
void solveLinEq (const double a, const double b, double *x, int *n_roots) {
    assert (isfinite (a));
    assert (a);
    assert (isfinite (b));

    assert (x);      
    assert (n_roots);

    *x = -b / a;
    *n_roots = ROOTS_1;
}

//-----------------------------------------------------
/**
 * @brief sets n_roots to ROOTS_INF
 * @param [out] n_roots pointer to int variable
*/
//-----------------------------------------------------
void solveInfRoots (int *n_roots) {
    *n_roots = ROOTS_INF;
}

//-----------------------------------------------------
/**
 * @brief sets n_roots to ROOTS_ERR
 * @param [out] n_roots pointer to int variable 
*/
//-----------------------------------------------------
void handleCoefError (int *n_roots) {
    *n_roots = ROOTS_ERR;
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
 * @brief resets test_ans to initial value
 * @param [out] test_ans pointer to struct test_answer variable test_ans
*/
//-----------------------------------------------------
void resetTestAns(struct test_answer *test_ans) {
    *test_ans = {0, 0, 0, 0};
}

//-----------------------------------------------------
/**
 * @brief compares two double values, returns 1 if equal, 0 if not
 * @param [in] a a-variable
 * @param [in] b b-variable
 * 
 * @details
 * a == b if |a-b| < EPS,
 * where EPS is const and defined inside the function
*/
//-----------------------------------------------------
int isEqual(const double a, const double b) {
    static const double EPS = 1e-6;
    return (fabs(a-b) < EPS);
}

// TODO:
// - documentation to structs and enums
// - learn how to output coloured strings
// 