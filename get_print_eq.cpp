#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "equation.h"
#include "get_print_eq.h"



int getCoefs(struct equation *eq) {
    assert (eq);

    static const unsigned MAX_MISTAKES = 10; 
    unsigned buffClearRes = 0, cntWrngLines = 0;

    printf("# Please, enter a, b, c coefs:\n");

    while (true) {
        buffClearRes = 0;
        if (scanf("%lf %lf %lf", &eq->a, &eq->b, &eq->c) == 3) {
            if (buffClearRes = clearBuff()) break;
        }

        printf("Incorrect input, try again\n");

        if (!buffClearRes)
            buffClearRes = clearBuff();

        if (buffClearRes == EOF)
            return ERR_EOF;

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
            printf("printResult: solveQuadrEq returned breeeed\n");             
            break;              
    }               
}               

int clearBuff(void) {
    int garbage = 0, notStumble = 1;
    
    while ((garbage = getchar()) != '\n' && garbage != EOF)
        if(!isspace(garbage))
            notStumble = 0;

    return (notStumble) ? garbage : 0; 
}
