#include <stdio.h>
#include <math.h>

enum roots_num {
    ROOTS_NUM_0 = 0, 
    ROOTS_NUM_1 = 1, 
    ROOTS_NUM_2 = 2,
    ROOTS_NUM_INF = 3,
    ROOTS_NUM_ERR = 4
};

enum error_names {
    ERR_TOO_MANY_MISTAKES = 1,
    ERR_EOF = 2  
};

struct equation {
    double a, b, c; 
    double x1, x2;
    int number_roots;
}; 

void solve_input(struct equation *eq);

void solve_quadr_eq (struct equation *eq);
void solve_lin_eq (struct equation *eq);
void solve_inf_roots (struct equation *eq);
void handle_coef_error (struct equation *eq);

int get_coefs(struct equation *eq);
void print_result(struct equation *eq);

int is_equal(const double a, const double b);

int main() {

    struct equation eq = {0.0, 0.0, 0.0, 0.0, 0.0, -1};

    printf("Please, enter a, b, c coefs:\n"); 

    int res_get_coefs = -1;

    if ((res_get_coefs =  get_coefs(&eq)) == ERR_TOO_MANY_MISTAKES) {
        printf("too many mistakes\n");
        return 1;
    } else if (res_get_coefs == ERR_EOF) {
        printf("end of the file\n");
        return 1;
    }   
    

    solve_input(&eq);

    print_result(&eq);
    
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

int get_coefs(struct equation *eq) {
    static const int MAX_MISTAKES = 10; 
    int garbage = 0, cnt_mistakes = 0;
    while (scanf("%lf %lf %lf", &eq->a, &eq->b, &eq->c) != 3) {
        garbage = getchar();
        if (cnt_mistakes++ >= MAX_MISTAKES)
            return ERR_TOO_MANY_MISTAKES;
        if (garbage == EOF)
            return ERR_EOF;
        printf("Incorrect input \"%c\", try again\n", garbage);
    }
    return 0;
}

void print_result(struct equation *eq) {
    switch(eq->number_roots) {
        case ROOTS_NUM_0:
            printf("no solutions\n");
            break;
        case ROOTS_NUM_1: 
            printf("1 solution:\n"
                   "%.3lf\n", eq->x1);
            break;
        case ROOTS_NUM_2:
            printf("2 solutions:\n"
                   "%.3lf , %.3lf\n", eq->x1, eq->x2);
            break;
        case ROOTS_NUM_INF:
            printf("infinite solutions\n");
            break;
        case ROOTS_NUM_ERR:
            printf("impossible coefs\n");
            break;
        default:
            printf("solve_quadr_eq returned breeeed\n");
            break;
    }
}

int is_equal(const double a, const double b) {
    static const double EPS = 1e-6;
    return (fabs(a-b) < EPS);
}
