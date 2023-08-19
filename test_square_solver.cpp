#include <stdio.h>
#include <math.h>

int solve(struct equation *eqp);
int is_equal(double a, double b);

enum {SOL_0, SOL_1, SOL_2};

const int MAX_TEXT = 1000;
const double EPS = 1e-6;

struct equation {
    double a,b,c,sol_1,sol_2;
    int sol_n;
} test_value = {0.0, 0.0, 0.0, 0.0, 0.0, NULL};

struct test_answer {
    double ans_1, ans_2;
} ta = {0.0, 0.0};

int main() {
    FILE *fp;
    fp = fopen("test_cases.txt", "r");

    int test_num = 0;
    int sol_n = 0; // number of solutions which "solve" has returned

    while (fscanf(fp, "####### test %d #######\n"
    "%lf %lf %lf answer: %d %lf %lf\n", &test_num, &test_value.a, &test_value.b, &test_value.c, &sol_n, &ta.ans_1, &ta.ans_2) == 7) {
        solve(&test_value);
        if (test_value.sol_n == sol_n && is_equal(ta.ans_1, test_value.sol_1) && is_equal(ta.ans_2, test_value.sol_2) )
            printf("Test %d passed\n", test_num);
        else if (test_value.sol_n == sol_n)
            printf("Test %d FAILED: (%lf %lf) received instead of (%lf %lf)\n", test_num, test_value.sol_1, test_value.sol_2, ta.ans_1, ta.ans_2);
        else 
            printf("Test %d FAILED: %d received instead of %d", test_num, test_value.sol_n, sol_n);
        test_value = {0.0, 0.0, 0.0, 0.0, 0.0, NULL};
    }
    fclose(fp);
    return 0;
}

/* returns number of solutions */
int solve(struct equation *eqp) {
    if (is_equal((eqp->a), 0.0) == 1) {
        /* x = -c / b*/
        eqp->sol_1 = ((-1) * (eqp->c)) / (eqp->b);
        eqp->sol_n = 1;
        return SOL_1;
    }
    
    double d, sd;

    /* d = b^2 - 4ac */
    d = (eqp->b)*(eqp->b) - 4*(eqp->a)*(eqp->c);
    sd = sqrt(d);

    if (d < 0) {
        eqp->sol_n = 0;
        return SOL_0;
    }
    else if (is_equal(d,0.0) == 1) {
        eqp->sol_1 = -(eqp->b) / (2 * (eqp->a));
        eqp->sol_n = 1;
        return SOL_1;
    }

    /* BASED solution v lob */
    eqp->sol_1 = (-(eqp->b) - sd) / (2 * (eqp->a));
    eqp->sol_2 = (-(eqp->b) + sd) / (2 * (eqp->a));
    eqp->sol_n = 2;
    return SOL_2;
}

/* doubles are equal if |a-b| < EPS */
int is_equal(double a, double b) {
    return (a > b) ? (a - b < EPS) : (b - a < EPS);
}
