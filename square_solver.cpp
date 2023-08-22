#include <stdio.h>
#include <math.h>
#include <assert.h>

enum roots_num {
    ROOTS_0 = 0, 
    ROOTS_1 = 1, 
    ROOTS_2 = 2,
    ROOTS_INF = 3,
    ROOTS_ERR = 4
};

enum error_names {
    ERR_TOO_MANY_MISTAKES = 1,
    ERR_EOF = 2  
};

struct equation {
    double a, b, c; 
    double x1, x2;
    int n_roots;
}; 

void solveInput (struct equation *eq);

void solveQuadrEq (const double a, const double b, const double c, double* x1, double* x2, int* n_roots);
void solveLinEq (const double b, const double c, double* x, int* n_roots);
void solveInfRoots (int* n_roots);
void handleCoefError (int* n_roots);

int getCoefs (struct equation *eq);
void print_result(struct equation *eq);

int isEqual(const double a, const double b);

int main() {
    printf("# Square equation solver\n"
           "# (copyright concretno) Yaroslav, 2023\n\n");

    struct equation eq = {0.0, 0.0, 0.0, 0.0, 0.0, -1};

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
    
    return 0;
}

void solveInput(struct equation *eq) {
    if (isEqual(eq->a, 0) && isEqual(eq->b, 0) && isEqual(eq->c, 0)) 
        solveInfRoots(&eq->n_roots);
    else if (!isEqual(eq->a, 0.0))
        solveQuadrEq(eq->a, eq->b, eq->c, &eq->x1, &eq->x2, &eq->n_roots);
    else if (!isEqual(eq->b, 0.0))
        solveLinEq(eq->b, eq->c, &eq->x1, &eq->n_roots);
    else
        handleCoefError(&eq->n_roots);
}

int getCoefs(struct equation *eq) {
    assert (eq);

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

void solveQuadrEq(const double a, const double b, const double c, double* x1, double* x2, int* n_roots) {
    assert (isfinite (a));
    assert (isfinite (b));
    assert (isfinite (c));

    assert (x1); /* != NULL */
    assert (x2); /* != NULL */
    assert (n_roots); /* != NULL */
    assert (x1 != x2);

    double discriminant = b * b - 4 * a * c;
    double sqrt_discriminant = sqrt(discriminant);

    if (discriminant < 0) {
        *n_roots = ROOTS_0;
    }
    else if (isEqual(discriminant, 0.0)) {
        *x1 = *x2 = -b / (2 * a);
        *n_roots = ROOTS_1;
    }
    else {
        *x1 = (-b - sqrt_discriminant) / (2 * a);
        *x2 = (-b + sqrt_discriminant) / (2 * a);
        *n_roots = ROOTS_2;
    }
}

void solveLinEq (const double b, const double c, double* x, int* n_roots) {
    assert (isfinite (b));
    assert (isfinite (c));

    assert (x);       // != NULL
    assert (n_roots); // != NULL

    *x = -c / b;
    *n_roots = ROOTS_1;
}

void solveInfRoots (int* n_roots) {
    *n_roots = ROOTS_INF;
}

void handleCoefError (int* n_roots) {
    *n_roots = ROOTS_ERR;
}

int isEqual(const double a, const double b) {
    static const double EPS = 1e-6;
    return (fabs(a-b) < EPS);
}
