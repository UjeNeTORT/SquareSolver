#include <stdio.h>
#include <math.h>

enum roots_num {
    ROOTS_NUM_0 = 0, 
    ROOTS_NUM_1 = 1, 
    ROOTS_NUM_2 = 2,
    ROOTS_NUM_INF = 3,
    ROOTS_NUM_ERR = 4
};

enum test_results {
    FULL_MATCH = 0,
    INCORR_ROOTS = 1,
    INCORR_ROOT_NUM = 2
};

struct equation {
    double a, b, c; 
    double x1, x2;
    int number_roots;
}; 

struct test_answer {
    double x1, x2;
    int number_roots;
};

void solve_input(struct equation *eq);

void solve_quadr_eq (struct equation *eq);
void solve_lin_eq (struct equation *eq);
void solve_inf_roots (struct equation *eq);
void handle_coef_error (struct equation *eq);

int matches_test_case(struct equation *eq, struct test_answer *test_ans);
int fscanf_test_case(FILE *fp, int *test_num, struct equation *eq, struct test_answer *test_ans);
void print_test_res(int test_res, int test_num);

void reset_eq(struct equation *eq);
void reset_test_ans(struct test_answer *test_ans);

int is_equal(const double a, const double b);

int main() {

    struct equation eq;
    reset_eq(&eq);

    struct test_answer test_ans;
    reset_test_ans(&test_ans);

    int res_get_coefs = -1;
    int test_num = 0;
    int test_res;

    FILE *fp;
    fp = fopen("test_cases.txt", "r");

    while (fscanf_test_case(fp, &test_num, &eq, &test_ans) == 7)  {
        solve_input(&eq);
        test_res = matches_test_case(&eq, &test_ans);
        print_test_res(test_res, test_num);
        reset_eq(&eq);
        reset_test_ans(&test_ans);
    }

    fclose(fp);
    
    return 0;
}

void solve_input(struct equation *eq) {
    if (!is_equal(eq->a, 0.0) && !is_equal(eq->b, 0.0))
        solve_quadr_eq(eq);
    else if (!is_equal(eq->b, 0.0))
        solve_lin_eq(eq);
    else if (is_equal(eq->c, 0.0))
        solve_inf_roots(eq);
    else
        handle_coef_error(eq);
}

void solve_quadr_eq(struct equation *eq) {
    
    double discriminant = 0.0;
    double sqrt_discriminant = 0.0;

    /* discriminant = b^2 - 4ac */
    discriminant = (eq->b) * (eq->b) - 4 * (eq->a) * (eq->c);
    sqrt_discriminant = sqrt(discriminant);

    if (discriminant < 0) {
        eq->number_roots = ROOTS_NUM_0;
    }
    else if (is_equal(discriminant, 0.0)) {
        eq->x1 = -(eq->b) / (2 * (eq->a));
        eq->number_roots = ROOTS_NUM_1;
    }
    else {
        eq->x1 = (-(eq->b) - sqrt_discriminant) / (2 * (eq->a));
        eq->x2 = (-(eq->b) + sqrt_discriminant) / (2 * (eq->a));
        eq->number_roots = ROOTS_NUM_2;
    }
}

void solve_lin_eq (struct equation *eq) {
    eq->x1 = -(eq->c) / (eq->b);
    eq->number_roots = ROOTS_NUM_1;
}

void solve_inf_roots (struct equation *eq) {
    eq->number_roots = ROOTS_NUM_INF;
}

void handle_coef_error (struct equation *eq) {
    eq->number_roots = ROOTS_NUM_ERR;
}

int fscanf_test_case(FILE *fp, int *test_num, struct equation *eq, struct test_answer *test_ans) {
    return fscanf(fp, "%d. %lf %lf %lf : %d %lf %lf \n", test_num, &eq->a, &eq->b, &eq->c, &test_ans->number_roots, &test_ans->x1, &test_ans->x2);
}

int matches_test_case(struct equation *eq, struct test_answer *test_ans) {
    if (eq->number_roots != test_ans->number_roots)
        return INCORR_ROOT_NUM;
    if ((eq->x1 != test_ans->x1) || (eq->x2 != test_ans->x2))
        return INCORR_ROOTS;
    return FULL_MATCH;
}

void print_test_res(int test_res, int test_num) {
    if (test_res == FULL_MATCH)
            printf("Test %d passed\n", test_num);
    else 
        printf("Test %d failed\n", test_num);
}

void reset_eq(struct equation *eq) {
    eq->a = 0.0;
    eq->b = 0.0;
    eq->c = 0.0;
    eq->x1 = 0.0;
    eq->x2 = 0.0;
    eq->number_roots = -1;
}

void reset_test_ans (struct test_answer *test_ans) {
    test_ans->x1 = 0.0;
    test_ans->x2 = 0.0;
    test_ans->number_roots = -1;
}


int is_equal(const double a, const double b) {
    static const double EPS = 1e-6;
    return (fabs(a-b) < EPS);
}
