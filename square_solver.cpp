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

void print_result(struct equation *eq) {
    assert (eq);

    switch(eq->n_roots) {
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
        case ROOTS_ERR:
            printf("impossible coefs\n");
            break;
        default:
            printf("print_result: solveQuadrEq returned breeeed\n");
            break;
    }
}

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

void solveLinEq (const double a, const double b, double *x, int *n_roots) {
    assert (isfinite (a));
    assert (a);
    assert (isfinite (b));

    assert (x);      
    assert (n_roots);

    *x = -b / a;
    *n_roots = ROOTS_1;
}

void solveInfRoots (int *n_roots) {
    *n_roots = ROOTS_INF;
}

void handleCoefError (int *n_roots) {
    *n_roots = ROOTS_ERR;
}

void resetEq(struct equation *eq) {
    *eq = {0, 0, 0, 0, 0, -1};
}


void resetTestAns(struct test_answer *test_ans) {
    *test_ans = {0, 0, 0, 0};
}

int isEqual(const double a, const double b) {
    static const double EPS = 1e-6;
    return (fabs(a-b) < EPS);
}
