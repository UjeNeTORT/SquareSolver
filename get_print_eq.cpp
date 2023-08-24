#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "equation.h"
#include "get_print_eq.h"


int getCoefs(struct equation *eq) {
    assert (eq);
     
    static const unsigned MAX_MISTAKES = 10; 
    unsigned garbage = 0, cntWrngLines = 0;

    printf("# Please, enter a, b, c coefs:\n");

    while (scanf("%lf %lf %lf", &eq->a, &eq->b, &eq->c) != 3) {
        garbage = getchar();
        while (garbage != '\n' && garbage != EOF)
            garbage = getchar();
        if (garbage == EOF)
            return ERR_EOF;
        printf("Incorrect input, try again\n");
        if (cntWrngLines++ >= MAX_MISTAKES)
            return ERR_OVERFLOW_INPUT;
    }
    return 0;
}

void printResult(struct equation *eq) {
    assert (eq);

    switch(eq->nRoots) {
        case ROOTS_0:
            printf("no solutions\n");
            break;
        case ROOTS_1: 
            printf("1 solution:\n"
                   "%.6lf\n", eq->x1);
            break;
        case ROOTS_2:
            printf("2 solutions:\n"
                   "%.6lf , %.6lf\n", eq->x1, eq->x2);
            break;
        case ROOTS_INF:
            printf("infinite solutions\n");
            break;
        default:
            printf("printResult: solveQuadrEq returned breeeed\n");
            break;
    }
}
